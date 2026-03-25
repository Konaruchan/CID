#include "teclado_cid.h"

#include "calibracion_teclado.h"
#include "inyeccion_texto.h"
#include "panel_contexto_texto.h"

#include <windows.h>
#include <string>

static HHOOK g_hook = nullptr;
static CallbackTeclaCID g_callback = nullptr;
static bool g_modo_cid = true;

static bool g_vk_abajo[256] = {};
static bool g_sc_abajo[256] = {};

static void Log(const std::wstring& s)
{
    OutputDebugStringW((s + L"\n").c_str());
}

static bool EsVkEnRangoByte(DWORD vk)
{
    return vk < 256;
}

static bool EsScanCodeEnRangoByte(DWORD scanCode)
{
    return scanCode < 256;
}

static bool EstaCtrlActivo()
{
    return (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
}

static bool EstaAltActivo()
{
    return (GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
}

static bool EstaWinActivo()
{
    return (GetAsyncKeyState(VK_LWIN) & 0x8000) != 0 ||
        (GetAsyncKeyState(VK_RWIN) & 0x8000) != 0;
}

static bool EsPedalPrincipalCID(DWORD vk)
{
    return vk == VK_SPACE;
}

static bool EsTeclaCIDCalibrada(DWORD scanCode)
{
    if (!EsScanCodeEnRangoByte(scanCode))
        return false;

    const wchar_t* nombre = NombreTeclaCID_PorScanCode(scanCode);
    return nombre != nullptr;
}

static bool EsTeclaCIDFisica(DWORD vk, DWORD scanCode)
{
    if (EsPedalPrincipalCID(vk))
        return true;

    return EsTeclaCIDCalibrada(scanCode);
}

static bool EsTeclaFormatoPermitida(DWORD vk)
{
    switch (vk)
    {
    case VK_BACK:
    case VK_RETURN:
    case VK_TAB:
    case VK_SHIFT:
    case VK_LSHIFT:
    case VK_RSHIFT:
        return true;
    default:
        return false;
    }
}

static bool EsVkEscribibleQwerty(DWORD vk)
{
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9'))
        return true;

    switch (vk)
    {
    case VK_SPACE:
    case VK_BACK:
    case VK_RETURN:
    case VK_OEM_1:      // ;:
    case VK_OEM_2:      // /?
    case VK_OEM_3:      // `~
    case VK_OEM_4:      // [{
    case VK_OEM_5:      // \|
    case VK_OEM_6:      // ]}
    case VK_OEM_7:      // '"
    case VK_OEM_COMMA:  // ,<
    case VK_OEM_PERIOD: // .>
    case VK_OEM_MINUS:  // -_
    case VK_OEM_PLUS:   // =+
    case VK_DECIMAL:
    case VK_SUBTRACT:
    case VK_ADD:
    case VK_DIVIDE:
    case VK_MULTIPLY:
        return true;
    default:
        return false;
    }
}

static bool EsAutorepeatVk(DWORD vk, bool presionada)
{
    if (!EsVkEnRangoByte(vk))
        return false;

    if (!presionada)
    {
        g_vk_abajo[vk] = false;
        return false;
    }

    bool repetida = g_vk_abajo[vk];
    g_vk_abajo[vk] = true;
    return repetida;
}

static bool EsAutorepeatScanCode(DWORD scanCode, bool presionada)
{
    if (!EsScanCodeEnRangoByte(scanCode))
        return false;

    if (!presionada)
    {
        g_sc_abajo[scanCode] = false;
        return false;
    }

    bool repetida = g_sc_abajo[scanCode];
    g_sc_abajo[scanCode] = true;
    return repetida;
}

static void ReiniciarEstadosTeclas()
{
    for (int i = 0; i < 256; ++i)
    {
        g_vk_abajo[i] = false;
        g_sc_abajo[i] = false;
    }
}

static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0)
        return CallNextHookEx(g_hook, nCode, wParam, lParam);

    if (nCode != HC_ACTION)
        return CallNextHookEx(g_hook, nCode, wParam, lParam);

    const KBDLLHOOKSTRUCT* k = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lParam);
    if (!k)
        return CallNextHookEx(g_hook, nCode, wParam, lParam);

    const bool presionada = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);
    const bool liberada = (wParam == WM_KEYUP || wParam == WM_SYSKEYUP);

    if (!presionada && !liberada)
        return CallNextHookEx(g_hook, nCode, wParam, lParam);

    const DWORD vk = k->vkCode;
    const DWORD scanCode = k->scanCode;

    // Nunca interferir con la inyección propia.
    if (InyeccionActiva())
        return CallNextHookEx(g_hook, nCode, wParam, lParam);

    const bool ctrl_activo = EstaCtrlActivo();
    const bool alt_activo = EstaAltActivo();
    const bool win_activo = EstaWinActivo();
    const bool hay_modificador_sistema = ctrl_activo || alt_activo || win_activo;

    // ------------------------------------------------------------
    // MODO QWERTY
    // ------------------------------------------------------------
    if (!g_modo_cid)
    {
        // Solo despierta el mini aviso al pulsar algo realmente escribible.
        if (presionada &&
            !hay_modificador_sistema &&
            EsVkEscribibleQwerty(vk))
        {
            bool repetida = EsAutorepeatVk(vk, true);
            if (!repetida)
                NotificarActividadEscribiblePanelContextoTexto();
        }
        else if (liberada && EsVkEnRangoByte(vk))
        {
            g_vk_abajo[vk] = false;
        }

        return CallNextHookEx(g_hook, nCode, wParam, lParam);
    }

    // ------------------------------------------------------------
    // MODO CID
    // ------------------------------------------------------------

    // Dejar pasar atajos del sistema / app
    if (hay_modificador_sistema)
    {
        if (liberada && EsVkEnRangoByte(vk))
            g_vk_abajo[vk] = false;
        if (liberada && EsScanCodeEnRangoByte(scanCode))
            g_sc_abajo[scanCode] = false;

        return CallNextHookEx(g_hook, nCode, wParam, lParam);
    }

    // Dejar pasar algunas teclas de formato
    if (EsTeclaFormatoPermitida(vk))
    {
        if (liberada && EsVkEnRangoByte(vk))
            g_vk_abajo[vk] = false;

        return CallNextHookEx(g_hook, nCode, wParam, lParam);
    }

    // Teclas CID físicas: se capturan y se envían al detector
    if (EsTeclaCIDFisica(vk, scanCode))
    {
        bool repetida = false;

        if (EsPedalPrincipalCID(vk))
            repetida = EsAutorepeatVk(vk, presionada);
        else
            repetida = EsAutorepeatScanCode(scanCode, presionada);

        if (presionada && !repetida)
            NotificarActividadEscribiblePanelContextoTexto();

        if (g_callback)
        {
            if (!presionada || !repetida)
                g_callback(vk, scanCode, presionada);
        }

        return 1; // interceptar
    }

    // Si es una tecla escribible normal y estamos en CID, bloquearla
    // para que no entre texto QWERTY accidental.
    if (EsVkEscribibleQwerty(vk))
    {
        if (liberada && EsVkEnRangoByte(vk))
            g_vk_abajo[vk] = false;
        return 1;
    }

    // Resto: dejar pasar
    if (liberada && EsVkEnRangoByte(vk))
        g_vk_abajo[vk] = false;
    if (liberada && EsScanCodeEnRangoByte(scanCode))
        g_sc_abajo[scanCode] = false;

    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

bool IniciarTecladoCID()
{
    if (g_hook)
        return true;

    ReiniciarEstadosTeclas();

    g_hook = SetWindowsHookExW(
        WH_KEYBOARD_LL,
        HookProc,
        GetModuleHandleW(nullptr),
        0
    );

    if (!g_hook)
    {
        Log(L"ERROR: no se pudo instalar el hook de teclado CID.");
        return false;
    }

    Log(L"Hook global de teclado CID iniciado.");
    return true;
}

void DetenerTecladoCID()
{
    if (g_hook)
    {
        UnhookWindowsHookEx(g_hook);
        g_hook = nullptr;
    }

    ReiniciarEstadosTeclas();
    Log(L"Hook global de teclado CID detenido.");
}

void RegistrarCallbackTecladoCID(CallbackTeclaCID cb)
{
    g_callback = cb;
}

bool EstaModoCID()
{
    return g_modo_cid;
}

void AlternarModoCID()
{
    g_modo_cid = !g_modo_cid;
    ReiniciarEstadosTeclas();

    Log(g_modo_cid ? L"MODO CID: ON" : L"MODO CID: OFF (QWERTY)");
}

void EstablecerModoCID(bool activo)
{
    g_modo_cid = activo;
    ReiniciarEstadosTeclas();

    Log(g_modo_cid ? L"MODO CID: ON" : L"MODO CID: OFF (QWERTY)");
}