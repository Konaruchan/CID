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
#include "engine_context.h"
#include "event_bus.h"
#include "platform.h"

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
static const ULONGLONG DOBLE_TOQUE_MS = 250;
// CID-04-07 : Comprueba si queda alguna tecla física pulsada dentro del estado interno actual del detector.
static bool HayAlgunaTeclaPresionada_NoLock()
{
    for (int i = 0; i < 256; ++i)
    {
        if (DCtx().presionada[i])
            return true;
    }
    return false;
}

// CID-04-08 : Limpia por completo la ventana temporal donde se acumulan teclas candidatas a formar un acorde.
static void LimpiarVentana_NoLock()
{
    for (int i = 0; i < 256; ++i)
        DCtx().en_ventana[i] = false;
}

// CID-04-09 : Identifica si la tecla recibida corresponde al pedal principal físico de CID.
static bool EsPedalPrincipalCID(DWORD vk)
{
    return vk == VK_SPACE;
}

// CID-04-10 : Identifica si un scan code corresponde a un pedal auxiliar calibrado del sistema CID.
static bool EsPedalAuxiliarCID(DWORD scanCode)
{
    const wchar_t* nombre = NombreTeclaCID_PorScanCode(scanCode);
    return nombre != nullptr && EsPedalAuxiliar_PorNombre(nombre);
}

// CID-04-11 : Determina si una entrada física corresponde a cualquier pedal operativo del sistema CID.
static bool EsCualquierPedalCID(DWORD vk, DWORD scanCode)
{
    return EsPedalPrincipalCID(vk) || EsPedalAuxiliarCID(scanCode);
}

// CID-04-12 : Repesca el estado físico actual de las teclas CID calibradas para completar la ventana del acorde.
static void MarcarTeclasFisicamentePresionadas_NoLock()
{
    std::vector<std::pair<std::wstring, DWORD> > asignaciones = ObtenerAsignacionesCalibradas();

    for (size_t i = 0; i < asignaciones.size(); ++i)
    {
        DWORD sc = asignaciones[i].second;
        if (sc >= 256)
            continue;

        SHORT state = PlataformaCIDActual()->AsyncKeyState((int)MapVirtualKeyW(sc, MAPVK_VSC_TO_VK));
        if (state & 0x8000)
            DCtx().en_ventana[sc] = true;
    }
}

// CID-04-13 : Construye la representación textual ordenada del acorde actual y devuelve sus teclas físicas válidas.
static std::wstring FormatearAcordeDesdeVentana_NoLock(std::vector<DWORD>& teclas_out)
{
    teclas_out.clear();
    teclas_out.reserve(8);

    // CID-04-14 : Recorre la ventana temporal y recoge solo teclas CID no pedales para formar el acorde normal.
    for (DWORD sc = 0; sc < 256; ++sc)
    {
        const wchar_t* nombre = NombreTeclaCID_PorScanCode(sc);
        if (!nombre) continue;

        if (EsPedalPrincipal_PorNombre(nombre) || EsPedalAuxiliar_PorNombre(nombre))
            continue;

        if (DCtx().en_ventana[sc])
            teclas_out.push_back(sc);
    }

    // CID-04-15 : Ordena las teclas del acorde según el orden lógico definido por el mapa CID.
    std::sort(teclas_out.begin(), teclas_out.end(),
        [](DWORD a, DWORD b)
        {
            const wchar_t* na = NombreTeclaCID_PorScanCode(a);
            const wchar_t* nb = NombreTeclaCID_PorScanCode(b);
            return OrdenTeclaCID_PorNombre(na) < OrdenTeclaCID_PorNombre(nb);
        });

    // CID-04-16 : Une los nombres de las teclas ordenadas para producir la clave textual de búsqueda del acorde.
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

// CID-04-17 : Refresca la superposición visual usando el estado actual expuesto por la bitácora conectada.
static void RefrescarSuperposicionVisual_NoLock()
{
    if (!DCtx().bitacora) return;
    Superposicion_SetEstadoVisual(DCtx().bitacora->ObtenerEstadoVisual());
}

// CID-04-18 : Notifica visualmente a la superposición que el acorde actual produjo un error.
static void NotificarErrorAcordeVisual_NoLock()
{
    Superposicion_NotificarErrorAcorde();
}

// CID-04-19 : Aplica el modificador D10 sobre la última pieza asentada cuando la bitácora lo permite.
static bool AplicarModificadorD10_NoLock()
{
    // CID-04-20 : Rechaza el modificador si no hay nada asentado todavía y muestra un estado visual neutro.
    if (!DCtx().bitacora || DCtx().bitacora->Tamano() == 0)
    {
        Superposicion_SetUltimoAsentado(L"(nada que modificar)");
        return false;
    }

    // CID-04-21 : Intenta aplicar el modificador D10 sobre la última pieza de la bitácora.
    std::wstring err;
    bool ok = DCtx().bitacora->AplicarModificadorD10(&err);

    // CID-04-22 : Informa visualmente cuando D10 no produce ningún efecto sobre la pieza actual.
    if (!ok)
    {
        Superposicion_SetUltimoAsentado(L"(D10 sin efecto)");
        return false;
    }

    // CID-04-23 : Registra el modificador aplicado, refresca la superposición y notifica actividad CID.
    DCtx().bitacora->AnotarTokenVisualMod();

    RefrescarSuperposicionVisual_NoLock();
    NotificarActividadCID();
    PublicarEventBusCID(EventBusCIDEvento{ EventBusCIDTipo::AcordeReconocido, PlataformaCIDActual()->NowMs(), L"D10" });
    Superposicion_SetUltimoAsentado(L"(D10 aplicado)");
    return true;
}

// CID-04-24 : Conecta la bitácora activa al detector y sincroniza la superposición con su estado visual actual.
void ConectarBitacora(BitacoraCID* bitacora)
{
    // CID-04-25 : Ignora la conexión si la sincronización interna del detector aún no ha sido inicializada.
    if (!DCtx().cs_iniciado) return;

    EnterCriticalSection(&DCtx().cs);
    DCtx().bitacora = bitacora;
    LeaveCriticalSection(&DCtx().cs);

    if (bitacora)
        Superposicion_SetEstadoVisual(bitacora->ObtenerEstadoVisual());
}

// CID-04-26 : Conecta el diccionario activo que se usará para resolver acordes reconocidos.
void ConectarDiccionario(const DiccionarioCID* dic)
{
    // CID-04-27 : Ignora la conexión si la sincronización interna del detector aún no ha sido inicializada.
    if (!DCtx().cs_iniciado) return;

    EnterCriticalSection(&DCtx().cs);
    DCtx().diccionario = dic;
    LeaveCriticalSection(&DCtx().cs);
}

// CID-04-28 : Inicializa el detector de acordes, reinicia su estado interno y prepara la temporización base.
bool IniciarDetectorAcorde(int ventana_ms)
{
    // CID-04-29 : Inicializa la sección crítica interna la primera vez que se arranca el detector.
    if (!DCtx().cs_iniciado)
    {
        InitializeCriticalSection(&DCtx().cs);
        DCtx().cs_iniciado = true;
    }

    EnterCriticalSection(&DCtx().cs);

    // CID-04-30 : Ajusta la duración efectiva de la ventana de acorde y reinicia buffers y banderas internas.
    DCtx().ventana_ms = (ventana_ms > 1) ? ventana_ms : 60;

    for (int i = 0; i < 256; ++i)
    {
        DCtx().presionada[i] = false;
        DCtx().en_ventana[i] = false;
    }

    DCtx().ventana_activa = false;
    DCtx().esperando_liberacion = false;
    DCtx().ultimo_pedal_principal_up = 0;

    // CID-04-31 : Crea la cola de temporizadores del detector si todavía no existe.
    if (!DCtx().timer_queue)
        DCtx().timer_queue = CreateTimerQueue();

    bool ok = (DCtx().timer_queue != nullptr);

    LeaveCriticalSection(&DCtx().cs);

    // CID-04-32 : Informa del fallo de inicialización si no pudo crearse la cola de temporizadores.
    if (!ok)
    {
        Log(L"ERROR: Detector de acorde no pudo crear TimerQueue.");
        return false;
    }

    // CID-04-33 : Registra el arranque correcto del detector y la ventana temporal configurada.
    Log(L"Detector de acorde iniciado (ventana " + std::to_wstring(DCtx().ventana_ms) + L" ms).");
    return true;
}

// CID-04-34 : Detiene el detector liberando temporizadores, cola de temporización y sincronización interna.
void DetenerDetectorAcorde()
{
    // CID-04-35 : Elimina el temporizador activo si todavía existe dentro de la cola del detector.
    if (DCtx().timer && DCtx().timer_queue)
    {
        DeleteTimerQueueTimer(DCtx().timer_queue, DCtx().timer, INVALID_HANDLE_VALUE);
        DCtx().timer = nullptr;
    }

    // CID-04-36 : Elimina la cola de temporizadores completa cuando el detector se apaga.
    if (DCtx().timer_queue)
    {
        DeleteTimerQueueEx(DCtx().timer_queue, INVALID_HANDLE_VALUE);
        DCtx().timer_queue = nullptr;
    }

    // CID-04-37 : Libera la sección crítica del detector si había sido inicializada previamente.
    if (DCtx().cs_iniciado)
    {
        DeleteCriticalSection(&DCtx().cs);
        DCtx().cs_iniciado = false;
    }
}

// CID-04-38 : Cierra la ventana temporal del acorde, resuelve su resultado y actualiza el estado del detector.
static void CALLBACK TimerCallback(PVOID, BOOLEAN)
{
    EnterCriticalSection(&DCtx().cs);

    // CID-04-39 : Marca la ventana como cerrada y repesca las teclas físicas que sigan realmente pulsadas.
    DCtx().ventana_activa = false;

    MarcarTeclasFisicamentePresionadas_NoLock();

    // CID-04-40 : Construye el acorde desde la ventana actual y limpia el buffer temporal de captura.
    std::vector<DWORD> teclas;
    std::wstring acorde = FormatearAcordeDesdeVentana_NoLock(teclas);

    LimpiarVentana_NoLock();

    // CID-04-41 : Procesa el acorde solo si la ventana llegó a contener teclas válidas.
    if (!teclas.empty())
    {
        // CID-04-42 : Rechaza acordes de más de tres teclas y muestra un error visual al usuario.
        if (teclas.size() > 3)
        {
            Log(L"ACORDE RECHAZADO (más de 3 teclas): " + acorde);
            Superposicion_SetUltimoAsentado(L"(acorde demasiado grande)");
            NotificarErrorAcordeVisual_NoLock();
            PublicarEventBusCID(EventBusCIDEvento{ EventBusCIDTipo::ErrorAcorde, PlataformaCIDActual()->NowMs(), acorde });
        }
        else
        {
            // CID-04-43 : Trata una D10 solitaria como modificador sobre la última pieza asentada.
            if (teclas.size() == 1)
            {
                const wchar_t* nombre = NombreTeclaCID_PorScanCode(teclas[0]);
                if (nombre && EsMarcadoraTilde_PorNombre(nombre))
                {
                    AplicarModificadorD10_NoLock();
                    DCtx().esperando_liberacion = HayAlgunaTeclaPresionada_NoLock();
                    DCtx().timer = nullptr;
                    LeaveCriticalSection(&DCtx().cs);
                    return;
                }
            }

            // CID-04-44 : Informa error si el acorde llegó a resolverse sin un diccionario conectado.
            if (!DCtx().diccionario)
            {
                Log(L"ERROR: Diccionario no conectado.");
                Superposicion_SetUltimoAsentado(L"(diccionario no conectado)");
            }
            else
            {
                // CID-04-45 : Busca el acorde en el diccionario y rechaza visualmente los no reconocidos.
                EntradaDiccionarioCID entry;
                if (!DCtx().diccionario->Buscar(acorde, entry))
                {
                    Log(L"ACORDE DESCONOCIDO: " + acorde);
                    NotificarErrorAcordeVisual_NoLock();
                    PublicarEventBusCID(EventBusCIDEvento{ EventBusCIDTipo::ErrorAcorde, PlataformaCIDActual()->NowMs(), acorde });
                }
                else
                {
                    // CID-04-46 : Anota la pieza reconocida en la bitácora y refresca la superposición visual.
                    if (DCtx().bitacora)
                    {
                        DCtx().bitacora->Anotar(entry.resultado_crudo, entry.numero_tildal);
                        DCtx().bitacora->AnotarTokenVisualPieza(entry.resultado_crudo);
                        RefrescarSuperposicionVisual_NoLock();
                    }

                    // CID-04-47 : Notifica actividad CID tras reconocer y aplicar correctamente un acorde válido.
                    NotificarActividadCID();
                    PublicarEventBusCID(EventBusCIDEvento{ EventBusCIDTipo::AcordeReconocido, PlataformaCIDActual()->NowMs(), acorde });
                }
            }
        }
    }

    // CID-04-48 : Activa el bloqueo hasta liberar teclas y marca el temporizador como ya consumido.
    DCtx().esperando_liberacion = HayAlgunaTeclaPresionada_NoLock();
    DCtx().timer = nullptr;

    LeaveCriticalSection(&DCtx().cs);
}

// CID-04-49 : Recibe eventos filtrados del módulo de teclado y alimenta la lógica de captura de acordes.
void RecibirEventoTeclaCID(DWORD vk, DWORD scanCode, bool presionada)
{
    // CID-04-50 : Descarta eventos si el detector aún no está listo o si el scan code no es utilizable.
    if (!DCtx().cs_iniciado) return;
    if (scanCode >= 256 && vk != VK_SPACE) return;

    // CID-04-51 : Ignora cualquier evento generado por la propia inyección de texto del sistema CID.
    if (InyeccionActiva())
        return;

    // CID-04-52 : Notifica actividad escribible al panel contextual al recibir una nueva pulsación física.
    if (presionada)
        PublicarEventBusCID(EventBusCIDEvento{ EventBusCIDTipo::ActividadEscribible, PlataformaCIDActual()->NowMs(), L"detector" });

    // CID-04-53 : Procesa los pedales CID con tratamiento especial para espacio y doble toque de borrado.
    if (EsCualquierPedalCID(vk, scanCode))
    {
        // CID-04-54 : Gestiona el doble toque del pedal principal para borrar el último asentado con bitácora vacía.
        if (EsPedalPrincipalCID(vk))
        {
            ULONGLONG ahora = PlataformaCIDActual()->NowMs();

            if (!presionada)
            {
                if (DCtx().bitacora && DCtx().bitacora->Tamano() == 0)
                {
                    if (DCtx().ultimo_pedal_principal_up != 0 &&
                        (ahora - DCtx().ultimo_pedal_principal_up) <= DOBLE_TOQUE_MS)
                    {
                        EventoTeclaCID_Key(false);
                        BorrarUltimoAsentado();
                        DCtx().ultimo_pedal_principal_up = 0;
                        return;
                    }
                }

                DCtx().ultimo_pedal_principal_up = ahora;
            }
        }

        // CID-04-55 : Reenvía la pulsación o liberación del pedal al gestor correspondiente y termina la ruta.
        EventoTeclaCID_Key(presionada);
        return;
    }

    // CID-04-56 : Resuelve el nombre CID del scan code recibido y descarta teclas no calibradas.
    const wchar_t* nombreCid = NombreTeclaCID_PorScanCode(scanCode);
    if (!nombreCid)
        return;

    // CID-04-57 : Excluye del acorde normal cualquier tecla calibrada que realmente sea un pedal.
    if (EsPedalPrincipal_PorNombre(nombreCid) || EsPedalAuxiliar_PorNombre(nombreCid))
        return;

    EnterCriticalSection(&DCtx().cs);

    // CID-04-58 : Actualiza el estado físico de la tecla recibida dentro del detector.
    DCtx().presionada[scanCode] = presionada;

    // CID-04-59 : Mantiene el bloqueo hasta que todas las teclas hayan sido liberadas tras el acorde anterior.
    if (DCtx().esperando_liberacion)
    {
        if (!HayAlgunaTeclaPresionada_NoLock())
            DCtx().esperando_liberacion = false;

        LeaveCriticalSection(&DCtx().cs);
        return;
    }

    // CID-04-60 : En una nueva pulsación abre la ventana de acorde o añade la tecla a la ya existente.
    if (presionada)
    {
        // CID-04-61 : Abre una nueva ventana de acorde con temporizador si todavía no había una activa.
        if (!DCtx().ventana_activa)
        {
            DCtx().ventana_activa = true;
            LimpiarVentana_NoLock();
            DCtx().en_ventana[scanCode] = true;

            if (DCtx().timer_queue)
            {
                BOOL ok = CreateTimerQueueTimer(
                    &DCtx().timer,
                    DCtx().timer_queue,
                    TimerCallback,
                    nullptr,
                    (DWORD)DCtx().ventana_ms,
                    0,
                    WT_EXECUTEDEFAULT
                );

                // CID-04-62 : Revierte la apertura de ventana si no pudo crearse el temporizador del acorde.
                if (!ok)
                {
                    DCtx().ventana_activa = false;
                    DCtx().timer = nullptr;
                    Log(L"ERROR: No se pudo crear el timer de ventana de acorde.");
                }
            }
            else
            {
                // CID-04-63 : Revierte la apertura de ventana si la cola de temporizadores no existe.
                DCtx().ventana_activa = false;
                Log(L"ERROR: TimerQueue no existe.");
            }
        }
        else
        {
            // CID-04-64 : Añade la tecla recién pulsada a la ventana de acorde ya abierta.
            DCtx().en_ventana[scanCode] = true;
        }
    }

    LeaveCriticalSection(&DCtx().cs);
}
