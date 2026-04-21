// CID-02-01 : Inclusión de la interfaz pública del módulo de captura de teclado CID.
#include "teclado_cid.h"

// CID-02-02 : Inclusión de módulos auxiliares para calibración, texto inyectado y panel contextual.
#include "calibracion_teclado.h"
#include "inyeccion_texto.h"
#include "panel_contexto_texto.h"
#include "engine_context.h"
#include "event_bus.h"
#include "platform.h"

// CID-02-03 : Inclusión de cabeceras del sistema y utilidades de texto necesarias para el hook global.
#include <windows.h>
#include <string>

// CID-02-04 : Envía mensajes de depuración del módulo de teclado al visor de salida de Windows.
static void Log(const std::wstring& s)
{
    OutputDebugStringW((s + L"\n").c_str());
}

// CID-02-05 : Comprueba si una virtual key cabe dentro del rango indexable de los buffers internos.
static bool EsVkEnRangoByte(DWORD vk)
{
    return vk < 256;
}

// CID-02-06 : Comprueba si un scan code cabe dentro del rango indexable de los buffers internos.
static bool EsScanCodeEnRangoByte(DWORD scanCode)
{
    return scanCode < 256;
}

// CID-02-07 : Detecta si la tecla Control está activa en este instante.
static bool EstaCtrlActivo()
{
    return (PlataformaCIDActual()->AsyncKeyState(VK_CONTROL) & 0x8000) != 0;
}

// CID-02-08 : Detecta si la tecla Alt está activa en este instante.
static bool EstaAltActivo()
{
    return (PlataformaCIDActual()->AsyncKeyState(VK_MENU) & 0x8000) != 0;
}

// CID-02-09 : Detecta si alguna tecla Windows está activa en este instante.
static bool EstaWinActivo()
{
    return (PlataformaCIDActual()->AsyncKeyState(VK_LWIN) & 0x8000) != 0 ||
        (PlataformaCIDActual()->AsyncKeyState(VK_RWIN) & 0x8000) != 0;
}

// CID-02-10 : Identifica si la tecla recibida corresponde al pedal principal físico de CID.
static bool EsPedalPrincipalCID(DWORD vk)
{
    return vk == VK_SPACE;
}

// CID-02-11 : Comprueba si un scan code pertenece a una tecla CID reconocida por la calibración cargada.
static bool EsTeclaCIDCalibrada(DWORD scanCode)
{
    if (!EsScanCodeEnRangoByte(scanCode))
        return false;

    const wchar_t* nombre = NombreTeclaCID_PorScanCode(scanCode);
    return nombre != nullptr;
}

// CID-02-12 : Determina si una tecla física forma parte del conjunto operativo de entrada CID.
static bool EsTeclaCIDFisica(DWORD vk, DWORD scanCode)
{
    if (EsPedalPrincipalCID(vk))
        return true;

    return EsTeclaCIDCalibrada(scanCode);
}

// CID-02-13 : Permite pasar ciertas teclas de formato que no deben bloquearse en modo CID.
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

// CID-02-14 : Determina si una tecla pertenece al conjunto de entrada escribible normal de QWERTY.
static bool EsVkEscribibleQwerty(DWORD vk)
{
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9'))
        return true;

    switch (vk)
    {
    case VK_SPACE:
    case VK_BACK:
    case VK_RETURN:
    case VK_OEM_1:
    case VK_OEM_2:
    case VK_OEM_3:
    case VK_OEM_4:
    case VK_OEM_5:
    case VK_OEM_6:
    case VK_OEM_7:
    case VK_OEM_COMMA:
    case VK_OEM_PERIOD:
    case VK_OEM_MINUS:
    case VK_OEM_PLUS:
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

// CID-02-15 : Detecta autorepetición por virtual key y actualiza su estado de pulsación.
static bool EsAutorepeatVk(DWORD vk, bool presionada)
{
    if (!EsVkEnRangoByte(vk))
        return false;

    if (!presionada)
    {
        TCtx().vk_abajo[vk] = false;
        return false;
    }

    bool repetida = TCtx().vk_abajo[vk];
    TCtx().vk_abajo[vk] = true;
    return repetida;
}

// CID-02-16 : Detecta autorepetición por scan code y actualiza su estado de pulsación.
static bool EsAutorepeatScanCode(DWORD scanCode, bool presionada)
{
    if (!EsScanCodeEnRangoByte(scanCode))
        return false;

    if (!presionada)
    {
        TCtx().sc_abajo[scanCode] = false;
        return false;
    }

    bool repetida = TCtx().sc_abajo[scanCode];
    TCtx().sc_abajo[scanCode] = true;
    return repetida;
}

// CID-02-17 : Reinicia por completo el estado interno de teclas pulsadas del módulo de captura.
static void ReiniciarEstadosTeclas()
{
    for (int i = 0; i < 256; ++i)
    {
        TCtx().vk_abajo[i] = false;
        TCtx().sc_abajo[i] = false;
    }
}

// CID-02-18 : Procesa cada evento del hook global y decide si dejar pasar, notificar o interceptar la tecla.
static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    // CID-02-19 : Reenvía inmediatamente eventos inválidos o no accionables al siguiente hook del sistema.
    if (nCode < 0)
        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);

    if (nCode != HC_ACTION)
        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);

    const KBDLLHOOKSTRUCT* k = reinterpret_cast<const KBDLLHOOKSTRUCT*>(lParam);
    if (!k)
        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);

    // CID-02-20 : Clasifica el evento como pulsación o liberación y descarta cualquier otro tipo.
    const bool presionada = (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);
    const bool liberada = (wParam == WM_KEYUP || wParam == WM_SYSKEYUP);

    if (!presionada && !liberada)
        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);

    // CID-02-21 : Extrae la virtual key y el scan code de la tecla recibida por el hook.
    const DWORD vk = k->vkCode;
    const DWORD scanCode = k->scanCode;

    // CID-02-22 : Nunca intercepta eventos generados por la propia inyección de texto del sistema CID.
    if (InyeccionActiva())
        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);

    // CID-02-23 : Calcula el estado actual de modificadores del sistema para evitar interferir con atajos globales.
    const bool ctrl_activo = EstaCtrlActivo();
    const bool alt_activo = EstaAltActivo();
    const bool win_activo = EstaWinActivo();
    const bool hay_modificador_sistema = ctrl_activo || alt_activo || win_activo;

    // CID-02-24 : En modo QWERTY solo despierta el panel contextual con pulsaciones escribibles reales y deja pasar todo.
    if (!TCtx().modo_cid)
    {
        // CID-02-25 : Notifica actividad escribible al panel solo en pulsaciones nuevas y sin modificadores de sistema.
        if (presionada &&
            !hay_modificador_sistema &&
            EsVkEscribibleQwerty(vk))
        {
            bool repetida = EsAutorepeatVk(vk, true);
            if (!repetida)
                PublicarEventBusCID(EventBusCIDEvento{ EventBusCIDTipo::ActividadEscribible, PlataformaCIDActual()->NowMs(), L"teclado" });
        }
        // CID-02-26 : Limpia el estado de la tecla al liberarse para mantener consistente el control de autorepetición.
        else if (liberada && EsVkEnRangoByte(vk))
        {
            TCtx().vk_abajo[vk] = false;
        }

        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);
    }

    // CID-02-27 : En modo CID deja pasar combinaciones con modificadores del sistema para no romper atajos ni accesos externos.
    if (hay_modificador_sistema)
    {
        if (liberada && EsVkEnRangoByte(vk))
            TCtx().vk_abajo[vk] = false;
        if (liberada && EsScanCodeEnRangoByte(scanCode))
            TCtx().sc_abajo[scanCode] = false;

        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);
    }

    // CID-02-28 : En modo CID deja pasar teclas de formato permitidas y solo limpia su estado al liberarse.
    if (EsTeclaFormatoPermitida(vk))
    {
        if (liberada && EsVkEnRangoByte(vk))
            TCtx().vk_abajo[vk] = false;

        return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);
    }

    // CID-02-29 : Captura las teclas físicas de CID, detecta autorepetición y las reenvía al detector de acordes.
    if (EsTeclaCIDFisica(vk, scanCode))
    {
        bool repetida = false;

        if (EsPedalPrincipalCID(vk))
            repetida = EsAutorepeatVk(vk, presionada);
        else
            repetida = EsAutorepeatScanCode(scanCode, presionada);

        // CID-02-30 : Notifica actividad escribible al panel contextual solo en pulsaciones nuevas de teclas CID.
        if (presionada && !repetida)
            PublicarEventBusCID(EventBusCIDEvento{ EventBusCIDTipo::ActividadEscribible, PlataformaCIDActual()->NowMs(), L"teclado" });

        // CID-02-31 : Llama al callback registrado evitando reenviar pulsaciones autorepetidas innecesarias.
        if (TCtx().callback)
        {
            if (!presionada || !repetida)
                TCtx().callback(vk, scanCode, presionada);
        }

        return 1;
    }

    // CID-02-32 : Bloquea teclas escribibles QWERTY normales para evitar texto accidental mientras CID está activo.
    if (EsVkEscribibleQwerty(vk))
    {
        if (liberada && EsVkEnRangoByte(vk))
            TCtx().vk_abajo[vk] = false;
        return 1;
    }

    // CID-02-33 : Deja pasar el resto de teclas no escribibles y limpia sus estados internos al liberarse.
    if (liberada && EsVkEnRangoByte(vk))
        TCtx().vk_abajo[vk] = false;
    if (liberada && EsScanCodeEnRangoByte(scanCode))
        TCtx().sc_abajo[scanCode] = false;

    return CallNextHookEx(TCtx().hook, nCode, wParam, lParam);
}

// CID-02-34 : Instala el hook global de teclado CID si todavía no está activo.
bool IniciarTecladoCID()
{
    // CID-02-35 : Evita reinstalar el hook si el módulo ya está iniciado.
    if (TCtx().hook)
        return true;

    // CID-02-36 : Reinicia el estado interno de teclas antes de enganchar la captura global.
    ReiniciarEstadosTeclas();

    // CID-02-37 : Instala el hook de bajo nivel para interceptar eventos de teclado en todo el sistema.
    TCtx().hook = SetWindowsHookExW(
        WH_KEYBOARD_LL,
        HookProc,
        GetModuleHandleW(nullptr),
        0
    );

    // CID-02-38 : Registra error y falla el arranque si no se pudo instalar el hook global.
    if (!TCtx().hook)
    {
        Log(L"ERROR: no se pudo instalar el hook de teclado CID.");
        return false;
    }

    // CID-02-39 : Registra el arranque correcto del hook global de teclado.
    Log(L"Hook global de teclado CID iniciado.");
    return true;
}

// CID-02-40 : Desinstala el hook global de teclado y limpia el estado interno del módulo.
void DetenerTecladoCID()
{
    // CID-02-41 : Desengancha el hook solo si actualmente estaba activo.
    if (TCtx().hook)
    {
        UnhookWindowsHookEx(TCtx().hook);
        TCtx().hook = nullptr;
    }

    // CID-02-42 : Reinicia estados residuales y registra el cierre del módulo de teclado.
    ReiniciarEstadosTeclas();
    Log(L"Hook global de teclado CID detenido.");
}

// CID-02-43 : Registra el callback que recibirá los eventos de teclas CID ya filtrados por el hook.
void RegistrarCallbackTecladoCID(CallbackTeclaCID cb)
{
    TCtx().callback = cb;
}

// CID-02-44 : Devuelve si el módulo se encuentra actualmente operando en modo CID.
bool EstaModoCID()
{
    return TCtx().modo_cid;
}

// CID-02-45 : Alterna entre modo CID y modo QWERTY y reinicia el estado interno del teclado.
void AlternarModoCID()
{
    TCtx().modo_cid = !TCtx().modo_cid;
    ReiniciarEstadosTeclas();

    Log(TCtx().modo_cid ? L"MODO CID: ON" : L"MODO CID: OFF (QWERTY)");
}

// CID-02-46 : Establece explícitamente el modo de funcionamiento del teclado y reinicia sus estados internos.
void EstablecerModoCID(bool activo)
{
    TCtx().modo_cid = activo;
    ReiniciarEstadosTeclas();

    Log(TCtx().modo_cid ? L"MODO CID: ON" : L"MODO CID: OFF (QWERTY)");
}
