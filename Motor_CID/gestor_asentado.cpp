// CID-08-01 : Inclusión de la implementación del gestor de asentado del sistema CID.
#include "gestor_asentado.h"

// CID-08-02 : Inclusión de módulos conectados para bitácora, inyección de texto y superposición visual.
#include "bitacora_cid.h"
#include "inyeccion_texto.h"
#include "superposicion_cid.h"
#include "engine_context.h"
#include "platform.h"

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
// CID-08-09 : Estado y constantes de la adaptación inteligente del ritmo de auto-asentado.
static const double ALPHA = 0.20;
static const double FACTOR = 1.60;
static const int MARGEN_MS = 60;

static const int AUTO_MIN_MS = 120;
static const int AUTO_MAX_MS = 700;

static const int HISTERESIS_MS = 20;
static const int PASO_MAX_MS = 25;

// CID-08-10 : Decide si un delta temporal sirve para entrenar el ritmo sin contaminarlo con ruido o pausas.
static bool DeltaValidoParaRitmo(ULONGLONG delta)
{
    if (delta < 15) return false;
    if (delta > 1200) return false;
    return true;
}

// CID-08-11 : Ajusta el auto-asentado hacia un objetivo respetando histéresis, paso máximo y límites globales.
static void AjustarAutoMs_NoLock(int objetivo)
{
    if (AbsInt(objetivo - GCtx().auto_ms) < HISTERESIS_MS)
        return;

    if (objetivo > GCtx().auto_ms)
        GCtx().auto_ms += (objetivo - GCtx().auto_ms > PASO_MAX_MS) ? PASO_MAX_MS : (objetivo - GCtx().auto_ms);
    else
        GCtx().auto_ms -= (GCtx().auto_ms - objetivo > PASO_MAX_MS) ? PASO_MAX_MS : (GCtx().auto_ms - objetivo);

    GCtx().auto_ms = ClampInt(GCtx().auto_ms, AUTO_MIN_MS, AUTO_MAX_MS);

    Log(L"AUTO-ASENTADO: " + std::to_wstring(GCtx().auto_ms) +
        L" ms (promedio=" + std::to_wstring((int)GCtx().promedio_ms) + L" ms)");
}

// CID-08-12 : Aplica mayúscula a la primera letra alfabética encontrada en una cadena.
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

// CID-08-13 : Devuelve el último carácter no espaciador de una cadena para inferir el contexto de mayúsculas.
static wchar_t UltimoNoEspacio(const std::wstring& s)
{
    for (int i = (int)s.size() - 1; i >= 0; --i)
    {
        if (s[i] != L' ' && s[i] != L'\t')
            return s[i];
    }
    return 0;
}

// CID-08-14 : Inyecta una secuencia de retrocesos físicos para borrar texto previamente escrito.
static void InyectarBackspace(int n)
{
    if (n <= 0) return;

    std::vector<INPUT> inputs;
    inputs.reserve((size_t)n * 2);

    // CID-08-15 : Construye la secuencia down y up de Backspace tantas veces como caracteres haya que borrar.
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

    PlataformaCIDActual()->SendInputEvents((UINT)inputs.size(), inputs.data());
}

// CID-08-16 : Asienta la línea viva actual concatenando piezas, inyectando texto y cerrando la línea visual.
static void Asentar_NoLock()
{
    if (!GCtx().bitacora) return;

    std::vector<std::wstring> piezas = GCtx().bitacora->ObtenerCopia();
    if (piezas.empty()) return;

    // CID-08-17 : Construye la palabra final concatenando todas las piezas pendientes sin espacios internos.
    std::wstring palabra;
    for (const auto& p : piezas)
        palabra += p;

    // CID-08-18 : Aplica mayúscula inicial si el contexto interno indica inicio de frase o equivalente.
    if (GCtx().debe_mayuscula)
        AplicarMayusculaInicial(palabra);

    // CID-08-19 : Guarda el último texto inyectado incluyendo el espacio final para permitir su borrado exacto.
    GCtx().ultimo_inyectado = palabra + L" ";

    // CID-08-20 : Actualiza el estado textual visible de la superposición con la palabra asentada.
    Superposicion_SetUltimoAsentado(palabra);

    // CID-08-21 : Inyecta el texto real en el sistema marcando temporalmente la inyección como propia.
    MarcarInyeccionActiva(true);
    InyectarTextoUnicode(GCtx().ultimo_inyectado);
    MarcarInyeccionActiva(false);

    // CID-08-22 : Actualiza el contexto de mayúscula para la siguiente palabra según el signo final asentado.
    wchar_t last = UltimoNoEspacio(palabra);
    if (last == L'.' || last == L'!' || last == L'?')
        GCtx().debe_mayuscula = true;
    else
        GCtx().debe_mayuscula = false;

    // CID-08-23 : Cierra la línea actual en la bitácora y limpia los pendientes de la línea viva.
    GCtx().bitacora->CerrarLineaPorAsentado();

    // CID-08-24 : Refresca el panel visual tras completar el asentado real de la línea.
    RefrescarSuperposicionVisual_NoLock(GCtx().bitacora);
}

// CID-08-25 : Ejecuta el chequeo periódico de inactividad para disparar el auto-asentado cuando corresponda.
static void CALLBACK TimerCallback(PVOID, BOOLEAN)
{
    EnterCriticalSection(&GCtx().cs);

    // CID-08-26 : Sale sin hacer nada si no hay bitácora conectada sobre la que operar.
    if (!GCtx().bitacora)
    {
        LeaveCriticalSection(&GCtx().cs);
        return;
    }

    // CID-08-27 : Bloquea el auto-asentado mientras el pedal continúe físicamente pulsado.
    if (GCtx().pedal_abajo)
    {
        LeaveCriticalSection(&GCtx().cs);
        return;
    }

    // CID-08-28 : Sale sin actuar si no existen piezas pendientes en la línea viva.
    if (GCtx().bitacora->Tamano() == 0)
    {
        LeaveCriticalSection(&GCtx().cs);
        return;
    }

    // CID-08-29 : Calcula el tiempo de inactividad real desde la última actividad CID registrada.
    ULONGLONG ahora = PlataformaCIDActual()->NowMs();
    ULONGLONG delta = (ahora >= GCtx().ultimo_tick) ? (ahora - GCtx().ultimo_tick) : 0;

    // CID-08-30 : Dispara el asentado automático cuando la inactividad supera el umbral dinámico actual.
    if ((int)delta >= GCtx().auto_ms)
    {
        Asentar_NoLock();
        GCtx().ultimo_tick = ahora;
    }

    LeaveCriticalSection(&GCtx().cs);
}

// CID-08-31 : Inicializa el gestor de asentado, su temporización periódica y su estado base de contexto.
bool IniciarGestorAsentado(int auto_ms, BitacoraCID* bitacora)
{
    // CID-08-32 : Inicializa la sección crítica global del gestor la primera vez que se arranca.
    if (!GCtx().cs_iniciado)
    {
        InitializeCriticalSection(&GCtx().cs);
        GCtx().cs_iniciado = true;
    }

    EnterCriticalSection(&GCtx().cs);

    // CID-08-33 : Conecta la bitácora y restablece tiempos, pedal, contexto e inteligencia inicial.
    GCtx().bitacora = bitacora;
    GCtx().auto_ms = ClampInt(auto_ms, AUTO_MIN_MS, AUTO_MAX_MS);

    GCtx().pedal_abajo = false;

    GCtx().ultimo_tick = PlataformaCIDActual()->NowMs();
    GCtx().tick_anterior_ritmo = GCtx().ultimo_tick;

    GCtx().ultimo_inyectado.clear();
    GCtx().debe_mayuscula = true;

    GCtx().promedio_ms = (double)ClampInt(GCtx().auto_ms - MARGEN_MS, 80, 500);

    // CID-08-34 : Crea la cola de temporizadores del gestor si todavía no existe.
    if (!GCtx().timer_queue)
        GCtx().timer_queue = CreateTimerQueue();

    bool ok = (GCtx().timer_queue != nullptr);

    // CID-08-35 : Crea el temporizador periódico de chequeo solo si la cola existe y aún no había timer activo.
    if (ok && !GCtx().timer)
    {
        ok = CreateTimerQueueTimer(
            &GCtx().timer,
            GCtx().timer_queue,
            TimerCallback,
            nullptr,
            CHEQUEO_MS,
            CHEQUEO_MS,
            WT_EXECUTEDEFAULT
        );
    }

    // CID-08-36 : Publica el estado visual inicial si el arranque fue correcto y hay bitácora conectada.
    if (ok && GCtx().bitacora)
        RefrescarSuperposicionVisual_NoLock(GCtx().bitacora);

    LeaveCriticalSection(&GCtx().cs);

    // CID-08-37 : Informa del fallo si no pudo iniciarse la infraestructura temporal del gestor.
    if (!ok)
    {
        Log(L"ERROR: Gestor de asentado no pudo iniciar timer.");
        return false;
    }

    // CID-08-38 : Registra el arranque correcto del gestor y el auto-asentado inicial configurado.
    Log(L"Gestor de asentado iniciado. Auto-asentado inicial = " + std::to_wstring(GCtx().auto_ms) + L" ms.");
    return true;
}

// CID-08-39 : Detiene el gestor liberando temporizador, cola de temporización y sincronización global.
void DetenerGestorAsentado()
{
    // CID-08-40 : Elimina el temporizador periódico si todavía existe dentro de la cola del gestor.
    if (GCtx().timer && GCtx().timer_queue)
    {
        DeleteTimerQueueTimer(GCtx().timer_queue, GCtx().timer, INVALID_HANDLE_VALUE);
        GCtx().timer = nullptr;
    }

    // CID-08-41 : Elimina la cola de temporizadores completa al apagar el gestor.
    if (GCtx().timer_queue)
    {
        DeleteTimerQueueEx(GCtx().timer_queue, INVALID_HANDLE_VALUE);
        GCtx().timer_queue = nullptr;
    }

    // CID-08-42 : Libera la sección crítica global del gestor si había sido inicializada.
    if (GCtx().cs_iniciado)
    {
        DeleteCriticalSection(&GCtx().cs);
        GCtx().cs_iniciado = false;
    }

    Log(L"Gestor de asentado detenido.");
}

// CID-08-43 : Registra una actividad CID real y entrena el auto-asentado dinámico según el ritmo observado.
void NotificarActividadCID()
{
    if (!GCtx().cs_iniciado) return;

    EnterCriticalSection(&GCtx().cs);

    // CID-08-44 : Calcula el delta desde el último punto de ritmo y actualiza el último tick de actividad global.
    ULONGLONG ahora = PlataformaCIDActual()->NowMs();
    ULONGLONG delta = (ahora >= GCtx().tick_anterior_ritmo) ? (ahora - GCtx().tick_anterior_ritmo) : 0;

    GCtx().ultimo_tick = ahora;

    // CID-08-45 : Entrena el promedio rítmico solo cuando el pedal no está abajo y el delta es válido.
    if (!GCtx().pedal_abajo)
    {
        if (DeltaValidoParaRitmo(delta))
        {
            GCtx().promedio_ms = (ALPHA * (double)delta) + ((1.0 - ALPHA) * GCtx().promedio_ms);

            int objetivo = (int)(GCtx().promedio_ms * FACTOR) + MARGEN_MS;
            objetivo = ClampInt(objetivo, AUTO_MIN_MS, AUTO_MAX_MS);

            AjustarAutoMs_NoLock(objetivo);
        }
    }

    GCtx().tick_anterior_ritmo = ahora;

    LeaveCriticalSection(&GCtx().cs);
}

// CID-08-46 : Procesa la pulsación o liberación del pedal CID y asienta manualmente cuando corresponde.
void EventoTeclaCID_Key(bool presionada)
{
    if (!GCtx().cs_iniciado) return;

    EnterCriticalSection(&GCtx().cs);

    ULONGLONG ahora = PlataformaCIDActual()->NowMs();
    GCtx().ultimo_tick = ahora;

    // CID-08-47 : Al pulsar el pedal bloquea auto-asentado y reinicia la referencia temporal del ritmo.
    if (presionada)
    {
        GCtx().pedal_abajo = true;
        GCtx().tick_anterior_ritmo = ahora;
        LeaveCriticalSection(&GCtx().cs);
        return;
    }

    // CID-08-48 : Al soltar el pedal reabre el ritmo normal y asienta manualmente si había contenido pendiente.
    GCtx().pedal_abajo = false;
    GCtx().tick_anterior_ritmo = ahora;

    if (GCtx().bitacora && GCtx().bitacora->Tamano() > 0)
        Asentar_NoLock();

    LeaveCriticalSection(&GCtx().cs);
}

// CID-08-49 : Borra el último texto asentado inyectando retrocesos y reabre su línea visual en la bitácora.
void BorrarUltimoAsentado()
{
    if (!GCtx().cs_iniciado) return;

    EnterCriticalSection(&GCtx().cs);

    // CID-08-50 : Sale sin actuar si no existe un texto asentado reciente que pueda borrarse.
    if (GCtx().ultimo_inyectado.empty())
    {
        LeaveCriticalSection(&GCtx().cs);
        return;
    }

    int n = (int)GCtx().ultimo_inyectado.size();

    // CID-08-51 : Borra físicamente del sistema el último asentado usando backspaces inyectados.
    MarcarInyeccionActiva(true);
    InyectarBackspace(n);
    MarcarInyeccionActiva(false);

    // CID-08-52 : Reabre visual y lógicamente la última línea asentada si existe bitácora conectada.
    if (GCtx().bitacora)
    {
        GCtx().bitacora->ReabrirUltimaLineaAsentada();
        RefrescarSuperposicionVisual_NoLock(GCtx().bitacora);
    }

    // CID-08-53 : Actualiza la superposición y borra el registro del último texto ya eliminado.
    Superposicion_SetUltimoAsentado(L"(borrado)");
    GCtx().ultimo_inyectado.clear();

    LeaveCriticalSection(&GCtx().cs);
}
