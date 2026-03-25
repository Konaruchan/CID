// gestor_asentado.cpp — ASENTADO + AUTO-ASENTADO INTELIGENTE + PEDAL + BORRAR ÚLTIMO ASENTADO
#include "gestor_asentado.h"
#include "bitacora_cid.h"
#include "inyeccion_texto.h"
#include "superposicion_cid.h"

#include <windows.h>
#include <string>
#include <vector>
#include <cwctype>

// -------------------- Utilidades --------------------
static int ClampInt(int v, int lo, int hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static int AbsInt(int x)
{
    return (x < 0) ? -x : x;
}

static void Log(const std::wstring& s)
{
    OutputDebugStringW((s + L"\n").c_str());
}

static void RefrescarSuperposicionVisual_NoLock(BitacoraCID* bitacora)
{
    if (!bitacora) return;
    Superposicion_SetEstadoVisual(bitacora->ObtenerEstadoVisual());
}

// -------------------- Estado global --------------------
static CRITICAL_SECTION g_cs;
static bool g_cs_iniciado = false;

static BitacoraCID* g_bitacora = nullptr;

static bool g_pedal_abajo = false;

// Auto-asentado actual (ms) — valor dinámico
static int g_auto_ms = 400;

// Chequeo periódico
static HANDLE g_timerQueue = nullptr;
static HANDLE g_timer = nullptr;
static const DWORD CHEQUEO_MS = 50;

// Para inactividad (cuánto llevas sin actividad CID real)
static ULONGLONG g_ultimo_tick = 0;

// Último texto inyectado (para borrar)
static std::wstring g_ultimo_inyectado;

// Contexto interno para mayúscula inicial
static bool g_debe_mayuscula = true;

// -------------------- Inteligencia (simple y estable) --------------------
static double g_promedio_ms = 220.0;

static const double ALPHA = 0.20;     // suavizado
static const double FACTOR = 1.60;    // auto ≈ promedio * factor + margen
static const int    MARGEN_MS = 60;

static const int AUTO_MIN_MS = 120;
static const int AUTO_MAX_MS = 700;

static const int HISTERESIS_MS = 20;  // ignora cambios muy pequeños
static const int PASO_MAX_MS = 25;    // limita cambio por actualización

static ULONGLONG g_tick_anterior_ritmo = 0;

static bool DeltaValidoParaRitmo(ULONGLONG delta)
{
    if (delta < 15) return false;    // ruido
    if (delta > 1200) return false;  // pausa (no entrena)
    return true;
}

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

// -------------------- Texto: mayúscula inicial por contexto interno --------------------
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

static wchar_t UltimoNoEspacio(const std::wstring& s)
{
    for (int i = (int)s.size() - 1; i >= 0; --i)
    {
        if (s[i] != L' ' && s[i] != L'\t')
            return s[i];
    }
    return 0;
}

// -------------------- Inyectar Backspace N veces --------------------
static void InyectarBackspace(int n)
{
    if (n <= 0) return;

    std::vector<INPUT> inputs;
    inputs.reserve((size_t)n * 2);

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

// -------------------- ASENTAR --------------------
static void Asentar_NoLock()
{
    if (!g_bitacora) return;

    std::vector<std::wstring> piezas = g_bitacora->ObtenerCopia();
    if (piezas.empty()) return;

    // Palabra = concatenación pura (sin espacios entre piezas)
    std::wstring palabra;
    for (const auto& p : piezas)
        palabra += p;

    // Mayúscula inicial: se aplica DESPUÉS del tildado
    if (g_debe_mayuscula)
        AplicarMayusculaInicial(palabra);

    // Guardar último inyectado (incluye espacio final)
    g_ultimo_inyectado = palabra + L" ";

    // Footer / estado textual
    Superposicion_SetUltimoAsentado(palabra);

    // Inyectar texto real
    MarcarInyeccionActiva(true);
    InyectarTextoUnicode(g_ultimo_inyectado);
    MarcarInyeccionActiva(false);

    // Contexto para siguiente palabra
    wchar_t last = UltimoNoEspacio(palabra);
    if (last == L'.' || last == L'!' || last == L'?')
        g_debe_mayuscula = true;
    else
        g_debe_mayuscula = false;

    // Cerrar línea visual y limpiar pendientes de la línea viva
    g_bitacora->CerrarLineaPorAsentado();

    // Refrescar panel visual real
    RefrescarSuperposicionVisual_NoLock(g_bitacora);
}

// -------------------- Timer: chequeo de inactividad --------------------
static void CALLBACK TimerCallback(PVOID, BOOLEAN)
{
    EnterCriticalSection(&g_cs);

    if (!g_bitacora)
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    if (g_pedal_abajo)
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    if (g_bitacora->Tamano() == 0)
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    ULONGLONG ahora = GetTickCount64();
    ULONGLONG delta = (ahora >= g_ultimo_tick) ? (ahora - g_ultimo_tick) : 0;

    if ((int)delta >= g_auto_ms)
    {
        Asentar_NoLock();
        g_ultimo_tick = ahora;
    }

    LeaveCriticalSection(&g_cs);
}

// -------------------- API pública --------------------
bool IniciarGestorAsentado(int auto_ms, BitacoraCID* bitacora)
{
    if (!g_cs_iniciado)
    {
        InitializeCriticalSection(&g_cs);
        g_cs_iniciado = true;
    }

    EnterCriticalSection(&g_cs);

    g_bitacora = bitacora;
    g_auto_ms = ClampInt(auto_ms, AUTO_MIN_MS, AUTO_MAX_MS);

    g_pedal_abajo = false;

    g_ultimo_tick = GetTickCount64();
    g_tick_anterior_ritmo = g_ultimo_tick;

    g_ultimo_inyectado.clear();
    g_debe_mayuscula = true;

    g_promedio_ms = (double)ClampInt(g_auto_ms - MARGEN_MS, 80, 500);

    if (!g_timerQueue)
        g_timerQueue = CreateTimerQueue();

    bool ok = (g_timerQueue != nullptr);

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

    // Estado visual inicial
    if (ok && g_bitacora)
        RefrescarSuperposicionVisual_NoLock(g_bitacora);

    LeaveCriticalSection(&g_cs);

    if (!ok)
    {
        Log(L"ERROR: Gestor de asentado no pudo iniciar timer.");
        return false;
    }

    Log(L"Gestor de asentado iniciado. Auto-asentado inicial = " + std::to_wstring(g_auto_ms) + L" ms.");
    return true;
}

void DetenerGestorAsentado()
{
    if (g_timer && g_timerQueue)
    {
        DeleteTimerQueueTimer(g_timerQueue, g_timer, INVALID_HANDLE_VALUE);
        g_timer = nullptr;
    }

    if (g_timerQueue)
    {
        DeleteTimerQueueEx(g_timerQueue, INVALID_HANDLE_VALUE);
        g_timerQueue = nullptr;
    }

    if (g_cs_iniciado)
    {
        DeleteCriticalSection(&g_cs);
        g_cs_iniciado = false;
    }

    Log(L"Gestor de asentado detenido.");
}

void NotificarActividadCID()
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);

    ULONGLONG ahora = GetTickCount64();
    ULONGLONG delta = (ahora >= g_tick_anterior_ritmo) ? (ahora - g_tick_anterior_ritmo) : 0;

    g_ultimo_tick = ahora;

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

void EventoTeclaCID_Key(bool presionada)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);

    ULONGLONG ahora = GetTickCount64();
    g_ultimo_tick = ahora;

    if (presionada)
    {
        g_pedal_abajo = true;
        g_tick_anterior_ritmo = ahora;
        LeaveCriticalSection(&g_cs);
        return;
    }

    g_pedal_abajo = false;
    g_tick_anterior_ritmo = ahora;

    if (g_bitacora && g_bitacora->Tamano() > 0)
        Asentar_NoLock();

    LeaveCriticalSection(&g_cs);
}

void BorrarUltimoAsentado()
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);

    if (g_ultimo_inyectado.empty())
    {
        LeaveCriticalSection(&g_cs);
        return;
    }

    int n = (int)g_ultimo_inyectado.size();

    MarcarInyeccionActiva(true);
    InyectarBackspace(n);
    MarcarInyeccionActiva(false);

    if (g_bitacora)
    {
        g_bitacora->ReabrirUltimaLineaAsentada();
        RefrescarSuperposicionVisual_NoLock(g_bitacora);
    }

    Superposicion_SetUltimoAsentado(L"(borrado)");
    g_ultimo_inyectado.clear();

    LeaveCriticalSection(&g_cs);
}