// CID-01-01 : Inclusión de cabeceras estándar y del sistema necesarias para el arranque del motor.
#include <windows.h>
#include <string>
#include <vector>

// CID-01-02 : Inclusión de módulos principales enlazados desde el punto de entrada del motor CID.
#include "teclado_cid.h"
#include "detector_acorde.h"
#include "bitacora_cid.h"
#include "gestor_asentado.h"
#include "diccionario_cid.h"
#include "superposicion_cid.h"
#include "calibracion_teclado.h"
#include "setup_teclado_cid.h"
#include "panel_contexto_texto.h"
#include "event_bus.h"
#include "platform.h"

// CID-01-03 : Identificadores de hotkeys globales para salir del motor y alternar el modo CID.
static const int HOTKEY_SALIR_ID = 1;
static const int HOTKEY_TOGGLE_CID_ID = 2;

// CID-01-04 : Nombre global del mutex que impide ejecutar varias instancias simultáneas del motor.
static const wchar_t* MUTEX_INSTANCIA_UNICA = L"Local\\MotorCID_UnicaInstancia";

// CID-01-05 : Envía una línea de texto al depurador de Windows para registrar actividad interna.
static void Log(const wchar_t* s)
{
    OutputDebugStringW(s);
    OutputDebugStringW(L"\n");
}

// CID-01-06 : Comprueba si una ruta apunta a un archivo existente y descarta directorios.
static bool ExisteArchivo(const std::wstring& ruta)
{
    DWORD attr = GetFileAttributesW(ruta.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES) && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

// CID-01-07 : Obtiene el directorio donde se encuentra el ejecutable actual del motor.
static std::wstring DirectorioExe()
{
    wchar_t exePath[MAX_PATH]{};
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);

    std::wstring p = exePath;
    size_t pos = p.find_last_of(L"\\/");
    if (pos != std::wstring::npos) p = p.substr(0, pos);
    return p;
}

// CID-01-08 : Une dos fragmentos de ruta garantizando un separador válido entre ambos.
static std::wstring Unir(const std::wstring& a, const std::wstring& b)
{
    if (a.empty()) return b;
    if (a.back() == L'\\' || a.back() == L'/') return a + b;
    return a + L"\\" + b;
}

// CID-01-09 : Resuelve la ruta del diccionario base cid0.cid y devuelve también el trazado probado.
static std::wstring ResolverRutaCid0(std::wstring* trazado)
{
    const std::wstring exeDir = DirectorioExe();
    const std::wstring ruta = Unir(exeDir, L"Diccionarios\\cid0.cid");

    if (trazado)
        *trazado = ruta + L"\n";

    if (ExisteArchivo(ruta))
        return ruta;

    return L"";
}

// CID-01-10 : Resuelve la ruta del archivo de layout visual del teclado CID.
static std::wstring ResolverRutaKeyboardLayoutJson()
{
    const std::wstring exeDir = DirectorioExe();
    const std::wstring rutaLocal = Unir(exeDir, L"keyboard-layout.json");
    if (ExisteArchivo(rutaLocal))
        return rutaLocal;

    const std::wstring rutaResource = Unir(exeDir, L"Resources\\keyboard-layout.json");
    if (ExisteArchivo(rutaResource))
        return rutaResource;

    return rutaLocal;
}

// CID-01-11 : Resuelve la ruta del archivo de calibración persistente del teclado CID.
static std::wstring ResolverRutaKeyboardCalibrationJson()
{
    return Unir(DirectorioExe(), L"keyboard-calibration.json");
}

// CID-01-12 : Ejecuta la limpieza de emergencia deteniendo módulos activos, liberando hotkeys y soltando el mutex.
static void LimpiezaFatal(bool hotkey_salir_ok, bool hotkey_toggle_ok, HANDLE mutex_instancia)
{
    DetenerTecladoCID();
    DetenerDetectorAcorde();
    DetenerGestorAsentado();
    DetenerPanelContextoTexto();
    DetenerSuperposicionCID();
    DetenerEventBusCID();

    if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
    if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);

    if (mutex_instancia)
        CloseHandle(mutex_instancia);
}

// CID-01-13 : Inicia el motor CID, valida recursos base, arranca módulos y mantiene el bucle principal.
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
    // CID-01-14 : Registra en depuración el arranque del motor y sus hotkeys principales.
    Log(L"Motor CID iniciado (diccionario + bitácora + asentado).");
    Log(L"Hotkey salir: Ctrl + Shift + F9");
    Log(L"Hotkey modo CID: Ctrl + Shift + F11");
    Log(L"Ver logs: Depurar -> Ventanas -> Salida");

    // CID-01-15 : Crea el mutex de instancia única y aborta si ya existe otro Motor CID activo.
    HANDLE mutex_instancia = CreateMutexW(nullptr, FALSE, MUTEX_INSTANCIA_UNICA);
    if (!mutex_instancia)
    {
        MessageBoxW(
            nullptr,
            L"No se pudo crear el control de instancia única del Motor CID.",
            L"Motor CID",
            MB_OK | MB_ICONERROR);
        return 1;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        MessageBoxW(
            nullptr,
            L"Motor CID ya se está ejecutando.",
            L"Motor CID",
            MB_OK | MB_ICONINFORMATION);
        CloseHandle(mutex_instancia);
        return 0;
    }

    RestablecerPlataformaCIDPredeterminada();

    if (!IniciarEventBusCID())
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el bus interno de eventos.", L"Motor CID", MB_OK | MB_ICONERROR);
        CloseHandle(mutex_instancia);
        return 1;
    }

    // CID-01-16 : Registra la hotkey global de salida y avisa si no se puede reservar.
    bool hotkey_salir_ok =
        RegisterHotKey(nullptr, HOTKEY_SALIR_ID, MOD_CONTROL | MOD_SHIFT, VK_F9) != 0;
    if (!hotkey_salir_ok)
        Log(L"ADVERTENCIA: no se pudo registrar Ctrl+Shift+F9. Se continuará sin hotkey de salida.");

    // CID-01-17 : Registra la hotkey global de cambio de modo y avisa si no se puede reservar.
    bool hotkey_toggle_ok =
        RegisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID, MOD_CONTROL | MOD_SHIFT, VK_F11) != 0;
    if (!hotkey_toggle_ok)
        Log(L"ADVERTENCIA: no se pudo registrar Ctrl+Shift+F11. Se continuará sin hotkey de cambio de modo.");

    // CID-01-18 : Inicia la superposición visual principal y aborta si no puede arrancar.
    if (!IniciarSuperposicionCID(hInstance))
    {
        MessageBoxW(nullptr, L"No se pudo iniciar la superposición CID.", L"Motor CID", MB_OK | MB_ICONERROR);
        if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
        if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);
        DetenerEventBusCID();
        CloseHandle(mutex_instancia);
        return 1;
    }

    // CID-01-19 : Inicia el panel contextual de texto y revierte la superposición si falla.
    if (!IniciarPanelContextoTexto())
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el panel contextual de texto.", L"Motor CID", MB_OK | MB_ICONERROR);
        DetenerSuperposicionCID();
        DetenerEventBusCID();
        if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
        if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);
        CloseHandle(mutex_instancia);
        return 1;
    }

    // CID-01-20 : Inicializa el estado visual base de la superposición según el modo activo actual.
    Superposicion_SetBitacora(L"[]");
    Superposicion_SetUltimoAsentado(EstaModoCID() ? L"MODO: CID" : L"MODO: QWERTY");
    Superposicion_SetModoQwerty(!EstaModoCID());

    // CID-01-21 : Resuelve las rutas de layout visual y calibración necesarias para el sistema de teclado.
    const std::wstring rutaLayoutJson = ResolverRutaKeyboardLayoutJson();
    const std::wstring rutaCalibrationJson = ResolverRutaKeyboardCalibrationJson();

    // CID-01-22 : Verifica que exista el layout visual del teclado antes de continuar con setup o calibración.
    if (!ExisteArchivo(rutaLayoutJson))
    {
        std::wstring msg =
            L"No se encontró keyboard-layout.json junto al ejecutable.\n\nRuta esperada:\n" +
            rutaLayoutJson +
            L"\n\nEste archivo es necesario para el setup/calibrador de teclado CID.";

        MessageBoxW(nullptr, msg.c_str(), L"Motor CID - keyboard-layout.json no encontrado", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
        return 1;
    }

    // CID-01-23 : Registra la ruta detectada del layout visual del teclado.
    Log((L"Layout visual encontrado en: " + rutaLayoutJson).c_str());

    // CID-01-24 : Ejecuta el setup de teclado si aún no existe un archivo de calibración persistido.
    if (!ExisteArchivo(rutaCalibrationJson))
    {
        std::wstring errSetup;
        if (!EjecutarSetupTecladoCID(hInstance, rutaCalibrationJson, &errSetup))
        {
            std::wstring msg =
                L"No se pudo completar el setup de calibración del teclado.\n\nError:\n" + errSetup;

            MessageBoxW(nullptr, msg.c_str(), L"Motor CID - Error en setup de teclado", MB_OK | MB_ICONERROR);
            LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
            return 1;
        }
    }

    // CID-01-25 : Carga la calibración de teclado desde disco y aborta si el archivo es inválido o inaccesible.
    {
        std::wstring errCal;
        if (!CargarCalibracionTeclado(rutaCalibrationJson, &errCal))
        {
            std::wstring msg =
                L"No se pudo cargar keyboard-calibration.json.\n\nRuta:\n" + rutaCalibrationJson +
                L"\n\nError:\n" + errCal;

            MessageBoxW(nullptr, msg.c_str(), L"Motor CID - Error leyendo keyboard-calibration.json", MB_OK | MB_ICONERROR);
            LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
            return 1;
        }
    }

    // CID-01-26 : Registra la ruta desde la que se cargó correctamente la calibración del teclado.
    Log((L"Calibración cargada desde: " + rutaCalibrationJson).c_str());

    // CID-01-27 : Construye la bitácora principal y ajusta sus límites de historial y líneas visibles.
    BitacoraCID bitacora;
    bitacora.ConfigurarMaximo(64);
    bitacora.ConfigurarMaximoLineasVisuales(24);

    // CID-01-28 : Sincroniza la superposición con el estado visual inicial vacío de la bitácora.
    Superposicion_SetEstadoVisual(bitacora.ObtenerEstadoVisual());

    // CID-01-29 : Resuelve la ruta del diccionario base cid0.cid y guarda el trazado probado.
    std::wstring trazado;
    std::wstring ruta = ResolverRutaCid0(&trazado);

    // CID-01-30 : Aborta el arranque si no se localiza el diccionario base requerido por el motor.
    if (ruta.empty())
    {
        std::wstring msg =
            L"No se pudo encontrar cid0.cid.\n\n"
            L"Directorio del EXE:\n" + DirectorioExe() + L"\n\n"
            L"Ruta probada:\n" + trazado;

        MessageBoxW(nullptr, msg.c_str(), L"Motor CID - cid0.cid no encontrado", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
        return 1;
    }

    // CID-01-31 : Registra la ruta válida encontrada para el diccionario base del sistema.
    Log((L"Diccionario base encontrado en: " + ruta).c_str());

    // CID-01-32 : Instancia el diccionario CID y prepara el buffer de error de carga.
    DiccionarioCID dic;
    std::wstring err;

    // CID-01-33 : Carga el diccionario base desde archivo y aborta si el contenido no es válido.
    if (!dic.CargarDesdeArchivo(ruta, &err))
    {
        std::wstring msg =
            L"No se pudo cargar el diccionario base.\n\nRuta:\n" + ruta +
            L"\n\nError:\n" + err;

        MessageBoxW(nullptr, msg.c_str(), L"Motor CID - Error leyendo cid0.cid", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
        return 1;
    }

    // CID-01-34 : Inicia el gestor de asentado con retardo base y acceso a la bitácora principal.
    if (!IniciarGestorAsentado(400, &bitacora))
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el gestor de asentado.", L"Motor CID", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
        return 1;
    }

    // CID-01-35 : Inicia el detector de acordes con su ventana temporal de reconocimiento.
    if (!IniciarDetectorAcorde(60))
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el detector de acordes.", L"Motor CID", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
        return 1;
    }

    // CID-01-36 : Conecta la bitácora, el diccionario y el callback de teclado al flujo del motor.
    ConectarBitacora(&bitacora);
    ConectarDiccionario(&dic);
    RegistrarCallbackTecladoCID(RecibirEventoTeclaCID);

    // CID-01-37 : Inicia el módulo de teclado CID y aborta si no puede enganchar la captura de entrada.
    if (!IniciarTecladoCID())
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el módulo de teclado CID.", L"Motor CID", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok, mutex_instancia);
        return 1;
    }

    // CID-01-38 : Declara la estructura de mensajes usada por el bucle principal de Windows.
    MSG msg;

    // CID-01-39 : Mantiene el bucle de mensajes del proceso mientras el sistema siga activo.
    while (GetMessageW(&msg, nullptr, 0, 0) > 0)
    {
        // CID-01-40 : Filtra y procesa las hotkeys globales registradas por el motor.
        if (msg.message == WM_HOTKEY)
        {
            // CID-01-41 : Finaliza el bucle principal cuando se activa la hotkey global de salida.
            if (hotkey_salir_ok && msg.wParam == HOTKEY_SALIR_ID)
            {
                Log(L"Motor CID: salida por hotkey.");
                break;
            }

            // CID-01-42 : Alterna entre modo CID y QWERTY y actualiza la superposición visual.
            if (hotkey_toggle_ok && msg.wParam == HOTKEY_TOGGLE_CID_ID)
            {
                AlternarModoCID();
                Superposicion_SetUltimoAsentado(EstaModoCID() ? L"MODO: CID" : L"MODO: QWERTY");
                Superposicion_SetModoQwerty(!EstaModoCID());
                continue;
            }
        }

        // CID-01-43 : Reenvía al sistema los mensajes que no fueron consumidos por las hotkeys del motor.
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    // CID-01-44 : Detiene de forma ordenada todos los módulos activos al salir del bucle principal.
    DetenerTecladoCID();
    DetenerDetectorAcorde();
    DetenerGestorAsentado();
    DetenerPanelContextoTexto();
    DetenerSuperposicionCID();
    DetenerEventBusCID();

    // CID-01-45 : Libera las hotkeys globales que hubieran sido registradas con éxito.
    if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
    if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);

    // CID-01-46 : Libera el mutex de instancia única al cerrar normalmente el motor.
    if (mutex_instancia)
        CloseHandle(mutex_instancia);

    // CID-01-47 : Registra el cierre normal del motor y devuelve código de salida correcto.
    Log(L"Motor CID terminado.");
    return 0;
}
