#include <windows.h>
#include <string>
#include <vector>

#include "teclado_cid.h"
#include "detector_acorde.h"
#include "bitacora_cid.h"
#include "gestor_asentado.h"
#include "diccionario_cid.h"
#include "superposicion_cid.h"
#include "calibracion_teclado.h"
#include "setup_teclado_cid.h"
#include "panel_contexto_texto.h"

static const int HOTKEY_SALIR_ID = 1;
static const int HOTKEY_TOGGLE_CID_ID = 2;

static void Log(const wchar_t* s)
{
    OutputDebugStringW(s);
    OutputDebugStringW(L"\n");
}

static bool ExisteArchivo(const std::wstring& ruta)
{
    DWORD attr = GetFileAttributesW(ruta.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES) && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

static std::wstring DirectorioExe()
{
    wchar_t exePath[MAX_PATH]{};
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);

    std::wstring p = exePath;
    size_t pos = p.find_last_of(L"\\/");
    if (pos != std::wstring::npos) p = p.substr(0, pos);
    return p;
}

static std::wstring Unir(const std::wstring& a, const std::wstring& b)
{
    if (a.empty()) return b;
    if (a.back() == L'\\' || a.back() == L'/') return a + b;
    return a + L"\\" + b;
}

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

static std::wstring ResolverRutaKeyboardLayoutJson()
{
    return Unir(DirectorioExe(), L"keyboard-layout.json");
}

static std::wstring ResolverRutaKeyboardCalibrationJson()
{
    return Unir(DirectorioExe(), L"keyboard-calibration.json");
}

static void LimpiezaFatal(bool hotkey_salir_ok, bool hotkey_toggle_ok)
{
    DetenerTecladoCID();
    DetenerDetectorAcorde();
    DetenerGestorAsentado();
    DetenerPanelContextoTexto();
    DetenerSuperposicionCID();

    if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
    if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
    Log(L"Motor CID iniciado (diccionario + bitácora + asentado).");
    Log(L"Hotkey salir: Ctrl + Shift + F9");
    Log(L"Hotkey modo CID: Ctrl + Shift + F11");
    Log(L"Ver logs: Depurar -> Ventanas -> Salida");

    bool hotkey_salir_ok =
        RegisterHotKey(nullptr, HOTKEY_SALIR_ID, MOD_CONTROL | MOD_SHIFT, VK_F9) != 0;
    if (!hotkey_salir_ok)
        Log(L"ADVERTENCIA: no se pudo registrar Ctrl+Shift+F9. Se continuará sin hotkey de salida.");

    bool hotkey_toggle_ok =
        RegisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID, MOD_CONTROL | MOD_SHIFT, VK_F11) != 0;
    if (!hotkey_toggle_ok)
        Log(L"ADVERTENCIA: no se pudo registrar Ctrl+Shift+F11. Se continuará sin hotkey de cambio de modo.");

    if (!IniciarSuperposicionCID(hInstance))
    {
        MessageBoxW(nullptr, L"No se pudo iniciar la superposición CID.", L"Motor CID", MB_OK | MB_ICONERROR);
        if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
        if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);
        return 1;
    }

    if (!IniciarPanelContextoTexto())
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el panel contextual de texto.", L"Motor CID", MB_OK | MB_ICONERROR);
        DetenerSuperposicionCID();
        if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
        if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);
        return 1;
    }

    Superposicion_SetBitacora(L"[]");
    Superposicion_SetUltimoAsentado(EstaModoCID() ? L"MODO: CID" : L"MODO: QWERTY");
    Superposicion_SetModoQwerty(!EstaModoCID());

    // ------------------------------------------------------------
    // Comprobar archivos base del nuevo sistema
    // ------------------------------------------------------------
    const std::wstring rutaLayoutJson = ResolverRutaKeyboardLayoutJson();
    const std::wstring rutaCalibrationJson = ResolverRutaKeyboardCalibrationJson();

    if (!ExisteArchivo(rutaLayoutJson))
    {
        std::wstring msg =
            L"No se encontró keyboard-layout.json junto al ejecutable.\n\nRuta esperada:\n" +
            rutaLayoutJson +
            L"\n\nEste archivo es necesario para el setup/calibrador de teclado CID.";

        MessageBoxW(nullptr, msg.c_str(), L"Motor CID - keyboard-layout.json no encontrado", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
        return 1;
    }

    Log((L"Layout visual encontrado en: " + rutaLayoutJson).c_str());

    // ------------------------------------------------------------
    // Calibración de teclado
    // Si no existe, lanzar setup y generar keyboard-calibration.json
    // ------------------------------------------------------------
    if (!ExisteArchivo(rutaCalibrationJson))
    {
        std::wstring errSetup;
        if (!EjecutarSetupTecladoCID(hInstance, rutaCalibrationJson, &errSetup))
        {
            std::wstring msg =
                L"No se pudo completar el setup de calibración del teclado.\n\nError:\n" + errSetup;

            MessageBoxW(nullptr, msg.c_str(), L"Motor CID - Error en setup de teclado", MB_OK | MB_ICONERROR);
            LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
            return 1;
        }
    }

    {
        std::wstring errCal;
        if (!CargarCalibracionTeclado(rutaCalibrationJson, &errCal))
        {
            std::wstring msg =
                L"No se pudo cargar keyboard-calibration.json.\n\nRuta:\n" + rutaCalibrationJson +
                L"\n\nError:\n" + errCal;

            MessageBoxW(nullptr, msg.c_str(), L"Motor CID - Error leyendo keyboard-calibration.json", MB_OK | MB_ICONERROR);
            LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
            return 1;
        }
    }

    Log((L"Calibración cargada desde: " + rutaCalibrationJson).c_str());

    BitacoraCID bitacora;
    bitacora.ConfigurarMaximo(64);
    bitacora.ConfigurarMaximoLineasVisuales(24);

    // Estado visual inicial limpio
    Superposicion_SetEstadoVisual(bitacora.ObtenerEstadoVisual());

    std::wstring trazado;
    std::wstring ruta = ResolverRutaCid0(&trazado);

    if (ruta.empty())
    {
        std::wstring msg =
            L"No se pudo encontrar cid0.cid.\n\n"
            L"Directorio del EXE:\n" + DirectorioExe() + L"\n\n"
            L"Ruta probada:\n" + trazado;

        MessageBoxW(nullptr, msg.c_str(), L"Motor CID - cid0.cid no encontrado", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
        return 1;
    }

    Log((L"Diccionario base encontrado en: " + ruta).c_str());

    DiccionarioCID dic;
    std::wstring err;
    if (!dic.CargarDesdeArchivo(ruta, &err))
    {
        std::wstring msg =
            L"No se pudo cargar el diccionario base.\n\nRuta:\n" + ruta +
            L"\n\nError:\n" + err;

        MessageBoxW(nullptr, msg.c_str(), L"Motor CID - Error leyendo cid0.cid", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
        return 1;
    }

    if (!IniciarGestorAsentado(400, &bitacora))
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el gestor de asentado.", L"Motor CID", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
        return 1;
    }

    if (!IniciarDetectorAcorde(60))
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el detector de acordes.", L"Motor CID", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
        return 1;
    }

    ConectarBitacora(&bitacora);
    ConectarDiccionario(&dic);
    RegistrarCallbackTecladoCID(RecibirEventoTeclaCID);

    if (!IniciarTecladoCID())
    {
        MessageBoxW(nullptr, L"No se pudo iniciar el módulo de teclado CID.", L"Motor CID", MB_OK | MB_ICONERROR);
        LimpiezaFatal(hotkey_salir_ok, hotkey_toggle_ok);
        return 1;
    }

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0)
    {
        if (msg.message == WM_HOTKEY)
        {
            if (hotkey_salir_ok && msg.wParam == HOTKEY_SALIR_ID)
            {
                Log(L"Motor CID: salida por hotkey.");
                break;
            }

            if (hotkey_toggle_ok && msg.wParam == HOTKEY_TOGGLE_CID_ID)
            {
                AlternarModoCID();
                Superposicion_SetUltimoAsentado(EstaModoCID() ? L"MODO: CID" : L"MODO: QWERTY");
                Superposicion_SetModoQwerty(!EstaModoCID());
                continue;
            }
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    DetenerTecladoCID();
    DetenerDetectorAcorde();
    DetenerGestorAsentado();
    DetenerPanelContextoTexto();
    DetenerSuperposicionCID();

    if (hotkey_salir_ok)  UnregisterHotKey(nullptr, HOTKEY_SALIR_ID);
    if (hotkey_toggle_ok) UnregisterHotKey(nullptr, HOTKEY_TOGGLE_CID_ID);

    Log(L"Motor CID terminado.");
    return 0;
}