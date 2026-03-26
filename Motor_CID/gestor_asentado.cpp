// CID-08-01 : Inclusión de la implementación del gestor de asentado del sistema CID.
#include "gestor_asentado.h"

// CID-08-02 : Inclusión de módulos conectados para bitácora, inyección de texto y superposición visual.
#include "bitacora_cid.h"
#include "inyeccion_texto.h"
#include "superposicion_cid.h"

// CID-08-03 : Inclusión de cabeceras del sistema y utilidades de texto, contenedores y caracteres.
#include <windows.h>
#include <string>
#include <vector>
#include <cwctype>

// CID-08-04 : Limita un entero a un rango cerrado usado por temporizaciones y parámetros internos.
static int ClampInt(int v, int lo, int hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

// CID-08-05 : Devuelve el valor absoluto entero usado por la lógica de histéresis del auto-asentado.
static int AbsInt(int x)
{
    return (x < 0) ? -x : x;
}

// CID-08-06 : Envía mensajes de depuración del gestor de asentado al visor de salida de Windows.
static void Log(const std::wstring& s)
{
    OutputDebugStringW((s + L"\n").c_str());
}

// CID-08-07 : Refresca la superposición visual usando el estado actual expuesto por la bitácora conectada.
static void RefrescarSuperposicionVisual_NoLock(BitacoraCID* bitacora)
{
    if (!bitacora) return;
    Superposicion_SetEstadoVisual(bitacora->ObtenerEstadoVisual());
}

// CID-08-08 : Estado global de sincronización para proteger el acceso concurrente al gestor de asentado.
static CRITICAL_SECTION g_cs;
static bool g_cs_iniciado = false;

// CID-08-09 : Referencia global a la bitácora activa sobre la que opera el asentado.
static BitacoraCID* g_bitacora = nullptr;

// CID-08-10 : Estado del pedal de asentado para bloquear auto-asentado mientras permanezca pulsado.
static bool g_pedal_abajo = false;

// CID-08-11 : Tiempo actual de auto-asentado dinámico en milisegundos.
static int g_auto_ms = 400;

// CID-08-12 : Recursos de temporización usados para el chequeo periódico de inactividad.
static HANDLE g_timerQueue = nullptr;
static HANDLE g_timer = nullptr;
static const DWORD CHEQUEO_MS = 50;

// CID-08-13 : Último instante de actividad CID real usado para medir inactividad antes del auto-asentado.
static ULONGLONG g_ultimo_tick = 0;

// CID-08-14 : Último texto inyectado realmente en el sistema para permitir su borrado posterior.
static std::wstring g_ultimo_inyectado;

// CID-08-15 : Contexto interno que decide si la siguiente palabra debe arrancar con mayúscula inicial.
static bool g_debe_mayuscula = true;

// CID-08-16 : Estado y constantes de la adaptación inteligente del ritmo de auto-asentado.
static double g_promedio_ms = 220.0;

static const double ALPHA = 0.20;
static const double FACTOR = 1.60;
static const int MARGEN_MS = 60;

static const int AUTO_MIN_MS = 120;
static const int AUTO_MAX_MS = 700;

static const int HISTERESIS_MS = 20;
static const int PASO_MAX_MS = 25;

static ULONGLONG g_tick_anterior_ritmo = 0;

// CID-08-17 : Decide si un delta temporal sirve para entrenar el ritmo sin contaminarlo con ruido o pausas.
static bool DeltaValidoParaRitmo(ULONGLONG delta)
{
    if (delta < 15) return false;
    if (delta > 1200) return false;
    return true;
}

// CID-08-18 : Ajusta el auto-asentado hacia un objetivo respetando histéresis, paso máximo y límites globales.
static void AjustarAutoMs_NoLock(int objetivo)
{
    if (AbsInt(objetivo - g_auto_ms) < HISTERESIS_MS)
        return;

    if (objetivo > g_auto_ms)
        g_auto_ms += (objetivo - g_auto_ms > PASO_MAX_MS) ? PASO_MAX_MS : (objetivo - g_auto_ms);
    else
        g_auto_ms -= (g_auto_ms - objetivo > PASO_MAX_MS) ? PASO_MAX_MS : (g_auto_ms - objetivo);

    g_auto_ms = ClampInt(g_auto_ms, AUTO_MIN_MS, AUTO_MAX_MS);

    Log(L"AUTO-ASENTADO: " + std::to_wstring(g_auto_ms) +
        L" ms (promedio=" + std::to_wstring((int)g_promedio_ms) + L" ms)");
}

// CID-08-19 : Aplica mayúscula a la primera letra alfabética encontrada en una cadena.
static void AplicarMayusculaInicial(std::wstring& s)
{
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (iswalpha(s[i]))
        {
            s[i] = (wchar_t)towupper(s[i]);
            return;
        }
    }
}

// CID-08-20 : Devuelve el último carácter no espaciador de una cadena para inferir el contexto de mayúsculas.
static wchar_t UltimoNoEspacio(const std::wstring& s)
{
    for (int i = (int)s.size() - 1; i >= 0; --i)
    {
        if (s[i] != L' ' && s[i] != L'\t')
            return s[i];
    }
    return 0;
}

// CID-08-21 : Inyecta una secuencia de retrocesos físicos para borrar texto previamente escrito.
static void InyectarBackspace(int n)
{
    if (n <= 0) return;

    std::vector<INPUT> inputs;
    inputs.reserve((size_t)n * 2);

    // CID-08-22 : Construye la secuencia down y up de Backspace tantas veces como caracteres haya que borrar.
    for (int i = 0; i < n; ++i)
    {
        INPUT down{};
        down.type = INPUT_KEYBOARD;
        down.ki.wVk = VK_BACK;
        inputs.push_back(down);

        INPUT up{};
        up.type = INPUT_KEYBOARD;
        up.ki.wVk = VK_BACK;
        up.ki.dwFlags = KEYEVENTF_KEYUP;
        inputs.push_back(up);
    }

    SendInput((UINT)inputs.size(), inputs.data(), sizeof(INPUT));
}

// CID-08-23 : Asienta la línea viva actual concatenando piezas, inyectando texto y cerrando la línea visual.
static void Asentar_NoLock()
{
    if (!g_bitacora) return;

    std::vector<std::wstring> piezas = g_bitacora->ObtenerCopia();
    if (piezas.empty()) return;

    // CID-08-24 : Construye la palabra final concatenando todas las piezas pendientes sin espacios internos.
    std::wstring palabra;
    for (const auto& p : piezas)
        palabra += p;

    // CID-08-25 : Aplica mayúscula inicial si el contexto interno indica inicio de frase o equivalente.
    if (g_debe_mayuscula)
        AplicarMayusculaInicial(palabra);

    // CID-08-26 : Guarda el último texto inyectado incluyendo el espacio final para permitir su borrado exacto.
    g_ultimo_inyectado = palabra + L" ";

    // CID-08-27 : Actualiza el estado textual visible de la superposición con la palabra asentada.
    Superposicion_SetUltimoAsentado(palabra);

    // CID-08-28 : Inyecta el texto real en el sistema marcando temporalmente la inyección como propia.
    MarcarInyeccionActiva(true);
    InyectarTextoUnicode(g_ultimo_inyectado);
    MarcarInyeccionActiva(false);

    // CID-08-29 : Actualiza el contexto de mayúscula para la siguiente palabra según el signo final asentado.
    wchar_t last = UltimoNoEspacio(palabra);
    if (last == L'.' || last == L'!' || last == L'?')
        g_debe_mayuscula = true;
    else
        g_debe_mayuscula = false;

    // CID-08-30 : Cierra la línea actual en la bitácora y limpia los pendientes de la línea viva.
    g_bitacora->CerrarLineaPorAsentado();

    // CID-08-31 : Refresca el panel visual tras completar el asentado real de la línea.
    RefrescarSuperposicionVisual_NoLock(g_bitacora);
}

// CID-08-32 : Ejecuta el chequeo periódico de inactividad para disparar el auto-asentado cuando corresponda.
static void CALLBACK TimerCallback(PVOID, BOOLEAN)
{
    EnterCriticalSection(&g_cs);

    // CID-08-33 : Sale sin hacer nada si no hay bitácora conectada sobre la que operar.
    if (!g_bitacora)
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    // CID-08-34 : Bloquea el auto-asentado mientras el pedal continúe físicamente pulsado.
    if (g_pedal_abajo)
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    // CID-08-35 : Sale sin actuar si no existen piezas pendientes en la línea viva.
    if (g_bitacora->Tamano() == 0)
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    // CID-08-36 : Calcula el tiempo de inactividad real desde la última actividad CID registrada.
    ULONGLONG ahora = GetTickCount64();
    ULONGLONG delta = (ahora >= g_ultimo_tick) ? (ahora - g_ultimo_tick) : 0;

    // CID-08-37 : Dispara el asentado automático cuando la inactividad supera el umbral dinámico actual.
    if ((int)delta >= g_auto_ms)
    {
        Asentar_NoLock();
        g_ultimo_tick = ahora;
    }

    LeaveCriticalSection(&g_cs);
}

// CID-08-38 : Inicializa el gestor de asentado, su temporización periódica y su estado base de contexto.
bool IniciarGestorAsentado(int auto_ms, BitacoraCID* bitacora)
{
    // CID-08-39 : Inicializa la sección crítica global del gestor la primera vez que se arranca.
    if (!g_cs_iniciado)
    {
        InitializeCriticalSection(&g_cs);
        g_cs_iniciado = true;
    }

    EnterCriticalSection(&g_cs);

    // CID-08-40 : Conecta la bitácora y restablece tiempos, pedal, contexto e inteligencia inicial.
    g_bitacora = bitacora;
    g_auto_ms = ClampInt(auto_ms, AUTO_MIN_MS, AUTO_MAX_MS);

    g_pedal_abajo = false;

    g_ultimo_tick = GetTickCount64();
    g_tick_anterior_ritmo = g_ultimo_tick;

    g_ultimo_inyectado.clear();
    g_debe_mayuscula = true;

    g_promedio_ms = (double)ClampInt(g_auto_ms - MARGEN_MS, 80, 500);

    // CID-08-41 : Crea la cola de temporizadores del gestor si todavía no existe.
    if (!g_timerQueue)
        g_timerQueue = CreateTimerQueue();

    bool ok = (g_timerQueue != nullptr);

    // CID-08-42 : Crea el temporizador periódico de chequeo solo si la cola existe y aún no había timer activo.
    if (ok && !g_timer)
    {
        ok = CreateTimerQueueTimer(
            &g_timer,
            g_timerQueue,
            TimerCallback,
            nullptr,
            CHEQUEO_MS,
            CHEQUEO_MS,
            WT_EXECUTEDEFAULT
        );
    }

    // CID-08-43 : Publica el estado visual inicial si el arranque fue correcto y hay bitácora conectada.
    if (ok && g_bitacora)
        RefrescarSuperposicionVisual_NoLock(g_bitacora);

    LeaveCriticalSection(&g_cs);

    // CID-08-44 : Informa del fallo si no pudo iniciarse la infraestructura temporal del gestor.
    if (!ok)
    {
        Log(L"ERROR: Gestor de asentado no pudo iniciar timer.");
        return false;
    }

    // CID-08-45 : Registra el arranque correcto del gestor y el auto-asentado inicial configurado.
    Log(L"Gestor de asentado iniciado. Auto-asentado inicial = " + std::to_wstring(g_auto_ms) + L" ms.");
    return true;
}

// CID-08-46 : Detiene el gestor liberando temporizador, cola de temporización y sincronización global.
void DetenerGestorAsentado()
{
    // CID-08-47 : Elimina el temporizador periódico si todavía existe dentro de la cola del gestor.
    if (g_timer && g_timerQueue)
    {
        DeleteTimerQueueTimer(g_timerQueue, g_timer, INVALID_HANDLE_VALUE);
        g_timer = nullptr;
    }

    // CID-08-48 : Elimina la cola de temporizadores completa al apagar el gestor.
    if (g_timerQueue)
    {
        DeleteTimerQueueEx(g_timerQueue, INVALID_HANDLE_VALUE);
        g_timerQueue = nullptr;
    }

    // CID-08-49 : Libera la sección crítica global del gestor si había sido inicializada.
    if (g_cs_iniciado)
    {
        DeleteCriticalSection(&g_cs);
        g_cs_iniciado = false;
    }

    Log(L"Gestor de asentado detenido.");
}

// CID-08-50 : Registra una actividad CID real y entrena el auto-asentado dinámico según el ritmo observado.
void NotificarActividadCID()
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);

    // CID-08-51 : Calcula el delta desde el último punto de ritmo y actualiza el último tick de actividad global.
    ULONGLONG ahora = GetTickCount64();
    ULONGLONG delta = (ahora >= g_tick_anterior_ritmo) ? (ahora - g_tick_anterior_ritmo) : 0;

    g_ultimo_tick = ahora;

    // CID-08-52 : Entrena el promedio rítmico solo cuando el pedal no está abajo y el delta es válido.
    if (!g_pedal_abajo)
    {
        if (DeltaValidoParaRitmo(delta))
        {
            g_promedio_ms = (ALPHA * (double)delta) + ((1.0 - ALPHA) * g_promedio_ms);

            int objetivo = (int)(g_promedio_ms * FACTOR) + MARGEN_MS;
            objetivo = ClampInt(objetivo, AUTO_MIN_MS, AUTO_MAX_MS);

            AjustarAutoMs_NoLock(objetivo);
        }
    }

    g_tick_anterior_ritmo = ahora;

    LeaveCriticalSection(&g_cs);
}

// CID-08-53 : Procesa la pulsación o liberación del pedal CID y asienta manualmente cuando corresponde.
void EventoTeclaCID_Key(bool presionada)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);

    ULONGLONG ahora = GetTickCount64();
    g_ultimo_tick = ahora;

    // CID-08-54 : Al pulsar el pedal bloquea auto-asentado y reinicia la referencia temporal del ritmo.
    if (presionada)
    {
        g_pedal_abajo = true;
        g_tick_anterior_ritmo = ahora;
        LeaveCriticalSection(&g_cs);
        return;
    }

    // CID-08-55 : Al soltar el pedal reabre el ritmo normal y asienta manualmente si había contenido pendiente.
    g_pedal_abajo = false;
    g_tick_anterior_ritmo = ahora;

    if (g_bitacora && g_bitacora->Tamano() > 0)
        Asentar_NoLock();

    LeaveCriticalSection(&g_cs);
}

// CID-08-56 : Borra el último texto asentado inyectando retrocesos y reabre su línea visual en la bitácora.
void BorrarUltimoAsentado()
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);

    // CID-08-57 : Sale sin actuar si no existe un texto asentado reciente que pueda borrarse.
    if (g_ultimo_inyectado.empty())
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    int n = (int)g_ultimo_inyectado.size();

    // CID-08-58 : Borra físicamente del sistema el último asentado usando backspaces inyectados.
    MarcarInyeccionActiva(true);
    InyectarBackspace(n);
    MarcarInyeccionActiva(false);

    // CID-08-59 : Reabre visual y lógicamente la última línea asentada si existe bitácora conectada.
    if (g_bitacora)
    {
        g_bitacora->ReabrirUltimaLineaAsentada();
        RefrescarSuperposicionVisual_NoLock(g_bitacora);
    }

    // CID-08-60 : Actualiza la superposición y borra el registro del último texto ya eliminado.
    Superposicion_SetUltimoAsentado(L"(borrado)");
    g_ultimo_inyectado.clear();

    LeaveCriticalSection(&g_cs);
}