#include "detector_acorde.h"
#include "bitacora_cid.h"
#include "diccionario_cid.h"
#include "mapa_teclas_cid.h"
#include "calibracion_teclado.h"
#include "gestor_asentado.h"
#include "inyeccion_texto.h"
#include "superposicion_cid.h"
#include "teclado_cid.h"
#include "panel_contexto_texto.h"

#include <windows.h>
#include <vector>
#include <algorithm>
#include <string>

static void Log(const std::wstring& s)
{
    OutputDebugStringW((s + L"\n").c_str());
}

static CRITICAL_SECTION g_cs;
static bool g_cs_iniciado = false;

// Ahora indexamos por scanCode físico
static bool g_presionada[256] = { false };
static bool g_enVentana[256] = { false };

static int  g_ventana_ms = 60;

static bool g_ventana_activa = false;
static bool g_esperando_liberacion = false;

static HANDLE g_timerQueue = nullptr;
static HANDLE g_timer = nullptr;

static BitacoraCID* g_bitacora = nullptr;
static const DiccionarioCID* g_diccionario = nullptr;

// Doble toque de pedal principal => borrar último asentado (solo con bitácora vacía)
static ULONGLONG g_ultimo_pedal_principal_up = 0;
static const ULONGLONG DOBLE_TOQUE_MS = 250;

static bool HayAlgunaTeclaPresionada_NoLock()
{
    for (int i = 0; i < 256; ++i)
    {
        if (g_presionada[i])
            return true;
    }
    return false;
}

static void LimpiarVentana_NoLock()
{
    for (int i = 0; i < 256; ++i)
        g_enVentana[i] = false;
}

static bool EsPedalPrincipalCID(DWORD vk)
{
    return vk == VK_SPACE;
}

static bool EsPedalAuxiliarCID(DWORD scanCode)
{
    const wchar_t* nombre = NombreTeclaCID_PorScanCode(scanCode);
    return nombre != nullptr && EsPedalAuxiliar_PorNombre(nombre);
}

static bool EsCualquierPedalCID(DWORD vk, DWORD scanCode)
{
    return EsPedalPrincipalCID(vk) || EsPedalAuxiliarCID(scanCode);
}

static void MarcarTeclasFisicamentePresionadas_NoLock()
{
    // Repesca física: solo para teclas CID calibradas
    std::vector<std::pair<std::wstring, DWORD> > asignaciones = ObtenerAsignacionesCalibradas();

    for (size_t i = 0; i < asignaciones.size(); ++i)
    {
        DWORD sc = asignaciones[i].second;
        if (sc >= 256)
            continue;

        SHORT state = GetAsyncKeyState((int)MapVirtualKeyW(sc, MAPVK_VSC_TO_VK));
        if (state & 0x8000)
            g_enVentana[sc] = true;
    }
}

static std::wstring FormatearAcordeDesdeVentana_NoLock(std::vector<DWORD>& teclas_out)
{
    teclas_out.clear();
    teclas_out.reserve(8);

    for (DWORD sc = 0; sc < 256; ++sc)
    {
        const wchar_t* nombre = NombreTeclaCID_PorScanCode(sc);
        if (!nombre) continue;

        // Excluir pedales del acorde normal
        if (EsPedalPrincipal_PorNombre(nombre) || EsPedalAuxiliar_PorNombre(nombre))
            continue;

        if (g_enVentana[sc])
            teclas_out.push_back(sc);
    }

    std::sort(teclas_out.begin(), teclas_out.end(),
        [](DWORD a, DWORD b)
        {
            const wchar_t* na = NombreTeclaCID_PorScanCode(a);
            const wchar_t* nb = NombreTeclaCID_PorScanCode(b);
            return OrdenTeclaCID_PorNombre(na) < OrdenTeclaCID_PorNombre(nb);
        });

    std::wstring out;
    for (size_t i = 0; i < teclas_out.size(); ++i)
    {
        const wchar_t* nombre = NombreTeclaCID_PorScanCode(teclas_out[i]);
        if (!nombre) continue;

        if (!out.empty()) out += L"+";
        out += nombre;
    }

    return out;
}

static void RefrescarSuperposicionVisual_NoLock()
{
    if (!g_bitacora) return;
    Superposicion_SetEstadoVisual(g_bitacora->ObtenerEstadoVisual());
}

static void NotificarErrorAcordeVisual_NoLock()
{
    Superposicion_NotificarErrorAcorde();
}

static bool AplicarModificadorD10_NoLock()
{
    if (!g_bitacora || g_bitacora->Tamano() == 0)
    {
        Superposicion_SetUltimoAsentado(L"(nada que modificar)");
        return false;
    }

    std::wstring err;
    bool ok = g_bitacora->AplicarModificadorD10(&err);

    if (!ok)
    {
        Superposicion_SetUltimoAsentado(L"(D10 sin efecto)");
        return false;
    }

    // Log visual: el modificador sí se muestra como MOD.
    g_bitacora->AnotarTokenVisualMod();

    RefrescarSuperposicionVisual_NoLock();
    NotificarActividadCID();
    Superposicion_SetUltimoAsentado(L"(D10 aplicado)");
    return true;
}

void ConectarBitacora(BitacoraCID* bitacora)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_bitacora = bitacora;
    LeaveCriticalSection(&g_cs);

    if (bitacora)
        Superposicion_SetEstadoVisual(bitacora->ObtenerEstadoVisual());
}

void ConectarDiccionario(const DiccionarioCID* dic)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_diccionario = dic;
    LeaveCriticalSection(&g_cs);
}

bool IniciarDetectorAcorde(int ventana_ms)
{
    if (!g_cs_iniciado)
    {
        InitializeCriticalSection(&g_cs);
        g_cs_iniciado = true;
    }

    EnterCriticalSection(&g_cs);

    g_ventana_ms = (ventana_ms > 1) ? ventana_ms : 60;

    for (int i = 0; i < 256; ++i)
    {
        g_presionada[i] = false;
        g_enVentana[i] = false;
    }

    g_ventana_activa = false;
    g_esperando_liberacion = false;
    g_ultimo_pedal_principal_up = 0;

    if (!g_timerQueue)
        g_timerQueue = CreateTimerQueue();

    bool ok = (g_timerQueue != nullptr);

    LeaveCriticalSection(&g_cs);

    if (!ok)
    {
        Log(L"ERROR: Detector de acorde no pudo crear TimerQueue.");
        return false;
    }

    Log(L"Detector de acorde iniciado (ventana " + std::to_wstring(g_ventana_ms) + L" ms).");
    return true;
}

void DetenerDetectorAcorde()
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
}

static void CALLBACK TimerCallback(PVOID, BOOLEAN)
{
    EnterCriticalSection(&g_cs);

    g_ventana_activa = false;

    MarcarTeclasFisicamentePresionadas_NoLock();

    std::vector<DWORD> teclas;
    std::wstring acorde = FormatearAcordeDesdeVentana_NoLock(teclas);

    LimpiarVentana_NoLock();

    if (!teclas.empty())
    {
        if (teclas.size() > 3)
        {
            Log(L"ACORDE RECHAZADO (más de 3 teclas): " + acorde);
            Superposicion_SetUltimoAsentado(L"(acorde demasiado grande)");
            NotificarErrorAcordeVisual_NoLock();
        }
        else
        {
            // D10 sola = modificador sobre la última pieza
            if (teclas.size() == 1)
            {
                const wchar_t* nombre = NombreTeclaCID_PorScanCode(teclas[0]);
                if (nombre && EsMarcadoraTilde_PorNombre(nombre))
                {
                    AplicarModificadorD10_NoLock();
                    g_esperando_liberacion = HayAlgunaTeclaPresionada_NoLock();
                    g_timer = nullptr;
                    LeaveCriticalSection(&g_cs);
                    return;
                }
            }

            if (!g_diccionario)
            {
                Log(L"ERROR: Diccionario no conectado.");
                Superposicion_SetUltimoAsentado(L"(diccionario no conectado)");
            }
            else
            {
                EntradaDiccionarioCID entry;
                if (!g_diccionario->Buscar(acorde, entry))
                {
                    Log(L"ACORDE DESCONOCIDO: " + acorde);
                    NotificarErrorAcordeVisual_NoLock();
                }
                else
                {
                    if (g_bitacora)
                    {
                        // Lógica real pendiente
                        g_bitacora->Anotar(entry.resultado_crudo, entry.numero_tildal);

                        // Log visual de la línea actual
                        g_bitacora->AnotarTokenVisualPieza(entry.resultado_crudo);

                        // Refresco del panel visual real
                        RefrescarSuperposicionVisual_NoLock();
                    }

                    NotificarActividadCID();
                }
            }
        }
    }

    g_esperando_liberacion = HayAlgunaTeclaPresionada_NoLock();
    g_timer = nullptr;

    LeaveCriticalSection(&g_cs);
}

void RecibirEventoTeclaCID(DWORD vk, DWORD scanCode, bool presionada)
{
    if (!g_cs_iniciado) return;
    if (scanCode >= 256 && vk != VK_SPACE) return;

    if (InyeccionActiva())
        return;

    if (presionada)
        NotificarActividadEscribiblePanelContextoTexto();

    // Pedales CID:
    // - espacio = pedal principal + doble toque para borrar
    // - AUX_CID = pedal auxiliar sin doble toque especial
    if (EsCualquierPedalCID(vk, scanCode))
    {
        if (EsPedalPrincipalCID(vk))
        {
            ULONGLONG ahora = GetTickCount64();

            if (!presionada)
            {
                if (g_bitacora && g_bitacora->Tamano() == 0)
                {
                    if (g_ultimo_pedal_principal_up != 0 &&
                        (ahora - g_ultimo_pedal_principal_up) <= DOBLE_TOQUE_MS)
                    {
                        EventoTeclaCID_Key(false);
                        BorrarUltimoAsentado();
                        g_ultimo_pedal_principal_up = 0;
                        return;
                    }
                }

                g_ultimo_pedal_principal_up = ahora;
            }
        }

        EventoTeclaCID_Key(presionada);
        return;
    }

    const wchar_t* nombreCid = NombreTeclaCID_PorScanCode(scanCode);
    if (!nombreCid)
        return;

    // Excluir cualquier pedal calibrado del acorde normal
    if (EsPedalPrincipal_PorNombre(nombreCid) || EsPedalAuxiliar_PorNombre(nombreCid))
        return;

    EnterCriticalSection(&g_cs);

    g_presionada[scanCode] = presionada;

    if (g_esperando_liberacion)
    {
        if (!HayAlgunaTeclaPresionada_NoLock())
            g_esperando_liberacion = false;

        LeaveCriticalSection(&g_cs);
        return;
    }

    if (presionada)
    {
        if (!g_ventana_activa)
        {
            g_ventana_activa = true;
            LimpiarVentana_NoLock();
            g_enVentana[scanCode] = true;

            if (g_timerQueue)
            {
                BOOL ok = CreateTimerQueueTimer(
                    &g_timer,
                    g_timerQueue,
                    TimerCallback,
                    nullptr,
                    (DWORD)g_ventana_ms,
                    0,
                    WT_EXECUTEDEFAULT
                );

                if (!ok)
                {
                    g_ventana_activa = false;
                    g_timer = nullptr;
                    Log(L"ERROR: No se pudo crear el timer de ventana de acorde.");
                }
            }
            else
            {
                g_ventana_activa = false;
                Log(L"ERROR: TimerQueue no existe.");
            }
        }
        else
        {
            g_enVentana[scanCode] = true;
        }
    }

    LeaveCriticalSection(&g_cs);
}