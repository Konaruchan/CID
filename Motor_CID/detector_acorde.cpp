// CID-04-01 : Inclusión de la interfaz pública del detector de acordes CID.
#include "detector_acorde.h"

// CID-04-02 : Inclusión de módulos del motor usados para bitácora, diccionario, mapas, calibración y asentado.
#include "bitacora_cid.h"
#include "diccionario_cid.h"
#include "mapa_teclas_cid.h"
#include "calibracion_teclado.h"
#include "gestor_asentado.h"

// CID-04-03 : Inclusión de módulos auxiliares para inyección, superposición, modo de teclado y panel contextual.
#include "inyeccion_texto.h"
#include "superposicion_cid.h"
#include "teclado_cid.h"
#include "panel_contexto_texto.h"

// CID-04-04 : Inclusión de cabeceras del sistema y utilidades necesarias para temporización, vectores y texto.
#include <windows.h>
#include <vector>
#include <algorithm>
#include <string>

// CID-04-05 : Envía mensajes de depuración del detector de acordes al visor de salida de Windows.
static void Log(const std::wstring& s)
{
    OutputDebugStringW((s + L"\n").c_str());
}

// CID-04-06 : Estado global de sincronización para proteger el acceso concurrente al detector de acordes.
static CRITICAL_SECTION g_cs;
static bool g_cs_iniciado = false;

// CID-04-07 : Estado interno de teclas físicas presionadas y teclas acumuladas dentro de la ventana de acorde.
static bool g_presionada[256] = { false };
static bool g_enVentana[256] = { false };

// CID-04-08 : Duración configurada de la ventana temporal usada para capturar cada acorde.
static int g_ventana_ms = 60;

// CID-04-09 : Estado de actividad de la ventana de acorde y del bloqueo hasta liberar todas las teclas.
static bool g_ventana_activa = false;
static bool g_esperando_liberacion = false;

// CID-04-10 : Recursos de temporización usados para disparar el cierre de la ventana de acorde.
static HANDLE g_timerQueue = nullptr;
static HANDLE g_timer = nullptr;

// CID-04-11 : Referencias globales a la bitácora activa y al diccionario conectado del sistema CID.
static BitacoraCID* g_bitacora = nullptr;
static const DiccionarioCID* g_diccionario = nullptr;

// CID-04-12 : Estado del doble toque del pedal principal para borrar el último asentado con bitácora vacía.
static ULONGLONG g_ultimo_pedal_principal_up = 0;
static const ULONGLONG DOBLE_TOQUE_MS = 250;

// CID-04-13 : Comprueba si queda alguna tecla física pulsada dentro del estado interno actual del detector.
static bool HayAlgunaTeclaPresionada_NoLock()
{
    for (int i = 0; i < 256; ++i)
    {
        if (g_presionada[i])
            return true;
    }
    return false;
}

// CID-04-14 : Limpia por completo la ventana temporal donde se acumulan teclas candidatas a formar un acorde.
static void LimpiarVentana_NoLock()
{
    for (int i = 0; i < 256; ++i)
        g_enVentana[i] = false;
}

// CID-04-15 : Identifica si la tecla recibida corresponde al pedal principal físico de CID.
static bool EsPedalPrincipalCID(DWORD vk)
{
    return vk == VK_SPACE;
}

// CID-04-16 : Identifica si un scan code corresponde a un pedal auxiliar calibrado del sistema CID.
static bool EsPedalAuxiliarCID(DWORD scanCode)
{
    const wchar_t* nombre = NombreTeclaCID_PorScanCode(scanCode);
    return nombre != nullptr && EsPedalAuxiliar_PorNombre(nombre);
}

// CID-04-17 : Determina si una entrada física corresponde a cualquier pedal operativo del sistema CID.
static bool EsCualquierPedalCID(DWORD vk, DWORD scanCode)
{
    return EsPedalPrincipalCID(vk) || EsPedalAuxiliarCID(scanCode);
}

// CID-04-18 : Repesca el estado físico actual de las teclas CID calibradas para completar la ventana del acorde.
static void MarcarTeclasFisicamentePresionadas_NoLock()
{
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

// CID-04-19 : Construye la representación textual ordenada del acorde actual y devuelve sus teclas físicas válidas.
static std::wstring FormatearAcordeDesdeVentana_NoLock(std::vector<DWORD>& teclas_out)
{
    teclas_out.clear();
    teclas_out.reserve(8);

    // CID-04-20 : Recorre la ventana temporal y recoge solo teclas CID no pedales para formar el acorde normal.
    for (DWORD sc = 0; sc < 256; ++sc)
    {
        const wchar_t* nombre = NombreTeclaCID_PorScanCode(sc);
        if (!nombre) continue;

        if (EsPedalPrincipal_PorNombre(nombre) || EsPedalAuxiliar_PorNombre(nombre))
            continue;

        if (g_enVentana[sc])
            teclas_out.push_back(sc);
    }

    // CID-04-21 : Ordena las teclas del acorde según el orden lógico definido por el mapa CID.
    std::sort(teclas_out.begin(), teclas_out.end(),
        [](DWORD a, DWORD b)
        {
            const wchar_t* na = NombreTeclaCID_PorScanCode(a);
            const wchar_t* nb = NombreTeclaCID_PorScanCode(b);
            return OrdenTeclaCID_PorNombre(na) < OrdenTeclaCID_PorNombre(nb);
        });

    // CID-04-22 : Une los nombres de las teclas ordenadas para producir la clave textual de búsqueda del acorde.
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

// CID-04-23 : Refresca la superposición visual usando el estado actual expuesto por la bitácora conectada.
static void RefrescarSuperposicionVisual_NoLock()
{
    if (!g_bitacora) return;
    Superposicion_SetEstadoVisual(g_bitacora->ObtenerEstadoVisual());
}

// CID-04-24 : Notifica visualmente a la superposición que el acorde actual produjo un error.
static void NotificarErrorAcordeVisual_NoLock()
{
    Superposicion_NotificarErrorAcorde();
}

// CID-04-25 : Aplica el modificador D10 sobre la última pieza asentada cuando la bitácora lo permite.
static bool AplicarModificadorD10_NoLock()
{
    // CID-04-26 : Rechaza el modificador si no hay nada asentado todavía y muestra un estado visual neutro.
    if (!g_bitacora || g_bitacora->Tamano() == 0)
    {
        Superposicion_SetUltimoAsentado(L"(nada que modificar)");
        return false;
    }

    // CID-04-27 : Intenta aplicar el modificador D10 sobre la última pieza de la bitácora.
    std::wstring err;
    bool ok = g_bitacora->AplicarModificadorD10(&err);

    // CID-04-28 : Informa visualmente cuando D10 no produce ningún efecto sobre la pieza actual.
    if (!ok)
    {
        Superposicion_SetUltimoAsentado(L"(D10 sin efecto)");
        return false;
    }

    // CID-04-29 : Registra el modificador aplicado, refresca la superposición y notifica actividad CID.
    g_bitacora->AnotarTokenVisualMod();

    RefrescarSuperposicionVisual_NoLock();
    NotificarActividadCID();
    Superposicion_SetUltimoAsentado(L"(D10 aplicado)");
    return true;
}

// CID-04-30 : Conecta la bitácora activa al detector y sincroniza la superposición con su estado visual actual.
void ConectarBitacora(BitacoraCID* bitacora)
{
    // CID-04-31 : Ignora la conexión si la sincronización interna del detector aún no ha sido inicializada.
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_bitacora = bitacora;
    LeaveCriticalSection(&g_cs);

    if (bitacora)
        Superposicion_SetEstadoVisual(bitacora->ObtenerEstadoVisual());
}

// CID-04-32 : Conecta el diccionario activo que se usará para resolver acordes reconocidos.
void ConectarDiccionario(const DiccionarioCID* dic)
{
    // CID-04-33 : Ignora la conexión si la sincronización interna del detector aún no ha sido inicializada.
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_diccionario = dic;
    LeaveCriticalSection(&g_cs);
}

// CID-04-34 : Inicializa el detector de acordes, reinicia su estado interno y prepara la temporización base.
bool IniciarDetectorAcorde(int ventana_ms)
{
    // CID-04-35 : Inicializa la sección crítica interna la primera vez que se arranca el detector.
    if (!g_cs_iniciado)
    {
        InitializeCriticalSection(&g_cs);
        g_cs_iniciado = true;
    }

    EnterCriticalSection(&g_cs);

    // CID-04-36 : Ajusta la duración efectiva de la ventana de acorde y reinicia buffers y banderas internas.
    g_ventana_ms = (ventana_ms > 1) ? ventana_ms : 60;

    for (int i = 0; i < 256; ++i)
    {
        g_presionada[i] = false;
        g_enVentana[i] = false;
    }

    g_ventana_activa = false;
    g_esperando_liberacion = false;
    g_ultimo_pedal_principal_up = 0;

    // CID-04-37 : Crea la cola de temporizadores del detector si todavía no existe.
    if (!g_timerQueue)
        g_timerQueue = CreateTimerQueue();

    bool ok = (g_timerQueue != nullptr);

    LeaveCriticalSection(&g_cs);

    // CID-04-38 : Informa del fallo de inicialización si no pudo crearse la cola de temporizadores.
    if (!ok)
    {
        Log(L"ERROR: Detector de acorde no pudo crear TimerQueue.");
        return false;
    }

    // CID-04-39 : Registra el arranque correcto del detector y la ventana temporal configurada.
    Log(L"Detector de acorde iniciado (ventana " + std::to_wstring(g_ventana_ms) + L" ms).");
    return true;
}

// CID-04-40 : Detiene el detector liberando temporizadores, cola de temporización y sincronización interna.
void DetenerDetectorAcorde()
{
    // CID-04-41 : Elimina el temporizador activo si todavía existe dentro de la cola del detector.
    if (g_timer && g_timerQueue)
    {
        DeleteTimerQueueTimer(g_timerQueue, g_timer, INVALID_HANDLE_VALUE);
        g_timer = nullptr;
    }

    // CID-04-42 : Elimina la cola de temporizadores completa cuando el detector se apaga.
    if (g_timerQueue)
    {
        DeleteTimerQueueEx(g_timerQueue, INVALID_HANDLE_VALUE);
        g_timerQueue = nullptr;
    }

    // CID-04-43 : Libera la sección crítica del detector si había sido inicializada previamente.
    if (g_cs_iniciado)
    {
        DeleteCriticalSection(&g_cs);
        g_cs_iniciado = false;
    }
}

// CID-04-44 : Cierra la ventana temporal del acorde, resuelve su resultado y actualiza el estado del detector.
static void CALLBACK TimerCallback(PVOID, BOOLEAN)
{
    EnterCriticalSection(&g_cs);

    // CID-04-45 : Marca la ventana como cerrada y repesca las teclas físicas que sigan realmente pulsadas.
    g_ventana_activa = false;

    MarcarTeclasFisicamentePresionadas_NoLock();

    // CID-04-46 : Construye el acorde desde la ventana actual y limpia el buffer temporal de captura.
    std::vector<DWORD> teclas;
    std::wstring acorde = FormatearAcordeDesdeVentana_NoLock(teclas);

    LimpiarVentana_NoLock();

    // CID-04-47 : Procesa el acorde solo si la ventana llegó a contener teclas válidas.
    if (!teclas.empty())
    {
        // CID-04-48 : Rechaza acordes de más de tres teclas y muestra un error visual al usuario.
        if (teclas.size() > 3)
        {
            Log(L"ACORDE RECHAZADO (más de 3 teclas): " + acorde);
            Superposicion_SetUltimoAsentado(L"(acorde demasiado grande)");
            NotificarErrorAcordeVisual_NoLock();
        }
        else
        {
            // CID-04-49 : Trata una D10 solitaria como modificador sobre la última pieza asentada.
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

            // CID-04-50 : Informa error si el acorde llegó a resolverse sin un diccionario conectado.
            if (!g_diccionario)
            {
                Log(L"ERROR: Diccionario no conectado.");
                Superposicion_SetUltimoAsentado(L"(diccionario no conectado)");
            }
            else
            {
                // CID-04-51 : Busca el acorde en el diccionario y rechaza visualmente los no reconocidos.
                EntradaDiccionarioCID entry;
                if (!g_diccionario->Buscar(acorde, entry))
                {
                    Log(L"ACORDE DESCONOCIDO: " + acorde);
                    NotificarErrorAcordeVisual_NoLock();
                }
                else
                {
                    // CID-04-52 : Anota la pieza reconocida en la bitácora y refresca la superposición visual.
                    if (g_bitacora)
                    {
                        g_bitacora->Anotar(entry.resultado_crudo, entry.numero_tildal);
                        g_bitacora->AnotarTokenVisualPieza(entry.resultado_crudo);
                        RefrescarSuperposicionVisual_NoLock();
                    }

                    // CID-04-53 : Notifica actividad CID tras reconocer y aplicar correctamente un acorde válido.
                    NotificarActividadCID();
                }
            }
        }
    }

    // CID-04-54 : Activa el bloqueo hasta liberar teclas y marca el temporizador como ya consumido.
    g_esperando_liberacion = HayAlgunaTeclaPresionada_NoLock();
    g_timer = nullptr;

    LeaveCriticalSection(&g_cs);
}

// CID-04-55 : Recibe eventos filtrados del módulo de teclado y alimenta la lógica de captura de acordes.
void RecibirEventoTeclaCID(DWORD vk, DWORD scanCode, bool presionada)
{
    // CID-04-56 : Descarta eventos si el detector aún no está listo o si el scan code no es utilizable.
    if (!g_cs_iniciado) return;
    if (scanCode >= 256 && vk != VK_SPACE) return;

    // CID-04-57 : Ignora cualquier evento generado por la propia inyección de texto del sistema CID.
    if (InyeccionActiva())
        return;

    // CID-04-58 : Notifica actividad escribible al panel contextual al recibir una nueva pulsación física.
    if (presionada)
        NotificarActividadEscribiblePanelContextoTexto();

    // CID-04-59 : Procesa los pedales CID con tratamiento especial para espacio y doble toque de borrado.
    if (EsCualquierPedalCID(vk, scanCode))
    {
        // CID-04-60 : Gestiona el doble toque del pedal principal para borrar el último asentado con bitácora vacía.
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

        // CID-04-61 : Reenvía la pulsación o liberación del pedal al gestor correspondiente y termina la ruta.
        EventoTeclaCID_Key(presionada);
        return;
    }

    // CID-04-62 : Resuelve el nombre CID del scan code recibido y descarta teclas no calibradas.
    const wchar_t* nombreCid = NombreTeclaCID_PorScanCode(scanCode);
    if (!nombreCid)
        return;

    // CID-04-63 : Excluye del acorde normal cualquier tecla calibrada que realmente sea un pedal.
    if (EsPedalPrincipal_PorNombre(nombreCid) || EsPedalAuxiliar_PorNombre(nombreCid))
        return;

    EnterCriticalSection(&g_cs);

    // CID-04-64 : Actualiza el estado físico de la tecla recibida dentro del detector.
    g_presionada[scanCode] = presionada;

    // CID-04-65 : Mantiene el bloqueo hasta que todas las teclas hayan sido liberadas tras el acorde anterior.
    if (g_esperando_liberacion)
    {
        if (!HayAlgunaTeclaPresionada_NoLock())
            g_esperando_liberacion = false;

        LeaveCriticalSection(&g_cs);
        return;
    }

    // CID-04-66 : En una nueva pulsación abre la ventana de acorde o añade la tecla a la ya existente.
    if (presionada)
    {
        // CID-04-67 : Abre una nueva ventana de acorde con temporizador si todavía no había una activa.
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

                // CID-04-68 : Revierte la apertura de ventana si no pudo crearse el temporizador del acorde.
                if (!ok)
                {
                    g_ventana_activa = false;
                    g_timer = nullptr;
                    Log(L"ERROR: No se pudo crear el timer de ventana de acorde.");
                }
            }
            else
            {
                // CID-04-69 : Revierte la apertura de ventana si la cola de temporizadores no existe.
                g_ventana_activa = false;
                Log(L"ERROR: TimerQueue no existe.");
            }
        }
        else
        {
            // CID-04-70 : Añade la tecla recién pulsada a la ventana de acorde ya abierta.
            g_enVentana[scanCode] = true;
        }
    }

    LeaveCriticalSection(&g_cs);
}