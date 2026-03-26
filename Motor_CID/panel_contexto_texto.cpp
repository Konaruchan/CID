// CID-18-01 : Inclusión de la implementación del panel de contexto de texto del sistema CID.
#include "panel_contexto_texto.h"

// CID-18-02 : Inclusión de la superposición visual controlada por el detector de contexto editable.
#include "superposicion_cid.h"

// CID-18-03 : Inclusión de cabeceras del sistema, UI Automation y utilidades de texto.
#include <windows.h>
#include <UIAutomation.h>
#include <string>

// CID-18-04 : Vinculación explícita de bibliotecas necesarias para UI Automation y COM.
#pragma comment(lib, "Uiautomationcore.lib")
#pragma comment(lib, "Ole32.lib")

// CID-18-05 : Estado global de sincronización y ciclo de vida del panel de contexto.
static CRITICAL_SECTION g_cs;
static bool g_cs_iniciado = false;

static HANDLE g_timerQueue = nullptr;
static HANDLE g_timer = nullptr;
static bool g_iniciado = false;

// CID-18-06 : Parámetros temporales de chequeo, debounce de aparición y ventana de activación por input.
static const DWORD CHEQUEO_MS = 40;
static const ULONGLONG DEBOUNCE_MOSTRAR_MS = 80;
static const ULONGLONG VENTANA_ACTIVACION_MS = 900;

// CID-18-07 : Último estado visible aplicado y últimos datos de foco, rectángulo y logging.
static bool g_ultimo_visible = false;
static RECT g_ultimo_rect{ 0,0,0,0 };
static HWND g_ultimo_hwnd_foreground = nullptr;
static HWND g_ultimo_hwnd_focus = nullptr;
static std::wstring g_ultima_clase_log;
static std::wstring g_ultimo_origen_log;

// CID-18-08 : Marca temporal del último input realmente escribible detectado.
static ULONGLONG g_ultimo_input_escribible_tick = 0;

// CID-18-09 : Estructura del contexto de texto detectado en un momento dado.
struct ContextoTextoDetectado
{
    bool visible = false;
    RECT rc_anclaje{ 0,0,0,0 };
    HWND hwnd_foreground = nullptr;
    HWND hwnd_focus = nullptr;
    std::wstring clase_focus;
    std::wstring origen;
};

// CID-18-10 : Estado del candidato pendiente antes de mostrar el panel tras debounce.
static bool g_tenemos_candidato = false;
static ContextoTextoDetectado g_candidato;
static ULONGLONG g_candidato_tick = 0;

// CID-18-11 : Envía mensajes de depuración del panel de contexto al visor de salida de Windows.
static void Log(const std::wstring& s)
{
    OutputDebugStringW((s + L"\n").c_str());
}

// CID-18-12 : Libera de forma segura una interfaz COM y la pone a null.
template<typename T>
static void SafeRelease(T*& p)
{
    if (p)
    {
        p->Release();
        p = nullptr;
    }
}

// CID-18-13 : Devuelve el valor absoluto entero usado en comparaciones geométricas.
static int AbsInt(int x)
{
    return (x < 0) ? -x : x;
}

// CID-18-14 : Comprueba si dos rectángulos son exactamente iguales.
static bool RectIguales(const RECT& a, const RECT& b)
{
    return a.left == b.left &&
        a.top == b.top &&
        a.right == b.right &&
        a.bottom == b.bottom;
}

// CID-18-15 : Comprueba si dos rectángulos son suficientemente parecidos dentro de una tolerancia dada.
static bool RectParecidos(const RECT& a, const RECT& b, int tol)
{
    return
        AbsInt(a.left - b.left) <= tol &&
        AbsInt(a.top - b.top) <= tol &&
        AbsInt(a.right - b.right) <= tol &&
        AbsInt(a.bottom - b.bottom) <= tol;
}

// CID-18-16 : Comprueba si un rectángulo tiene dimensiones positivas utilizables.
static bool RectValido(const RECT& rc)
{
    return (rc.right > rc.left) && (rc.bottom > rc.top);
}

// CID-18-17 : Normaliza el rectángulo de caret para asegurar ancho y alto mínimos visibles.
static void NormalizarRectCaret(RECT& rc)
{
    if (rc.right <= rc.left)
        rc.right = rc.left + 2;

    if (rc.bottom <= rc.top)
        rc.bottom = rc.top + 20;

    if ((rc.bottom - rc.top) < 14)
        rc.bottom = rc.top + 18;
}

// CID-18-18 : Devuelve el nombre de clase Win32 asociado a una ventana dada.
static std::wstring ObtenerClase(HWND hwnd)
{
    wchar_t clase[256] = {};
    if (!hwnd) return L"";
    GetClassNameW(hwnd, clase, (int)(sizeof(clase) / sizeof(clase[0])));
    return std::wstring(clase);
}

// CID-18-19 : Comprueba si una cadena contiene otra subcadena.
static bool Contiene(const std::wstring& s, const std::wstring& trozo)
{
    return s.find(trozo) != std::wstring::npos;
}

// CID-18-20 : Comprueba si una ventana pertenece exactamente a una clase Win32 dada.
static bool EsClase(HWND hwnd, const wchar_t* nombre)
{
    std::wstring clase = ObtenerClase(hwnd);
    return _wcsicmp(clase.c_str(), nombre) == 0;
}

// CID-18-21 : Identifica controles Win32 que son claramente editables sin recurrir a UI Automation.
static bool EsClaseEditableClara(HWND hwnd)
{
    if (!hwnd) return false;

    return
        EsClase(hwnd, L"Edit") ||
        EsClase(hwnd, L"RichEdit20A") ||
        EsClase(hwnd, L"RichEdit20W") ||
        EsClase(hwnd, L"RichEdit50W") ||
        EsClase(hwnd, L"RICHEDIT50W") ||
        EsClase(hwnd, L"RichEditD2DPT") ||
        EsClase(hwnd, L"Scintilla");
}

// CID-18-22 : Identifica clases modernas o wrappers donde suele ser necesario usar UI Automation.
static bool EsClaseWrapperModerna(const std::wstring& c)
{
    return
        _wcsicmp(c.c_str(), L"MozillaWindowClass") == 0 ||
        _wcsicmp(c.c_str(), L"Windows.UI.Input.InputSite.WindowClass") == 0 ||
        _wcsicmp(c.c_str(), L"Chrome_WidgetWin_0") == 0 ||
        _wcsicmp(c.c_str(), L"Chrome_WidgetWin_1") == 0 ||
        _wcsicmp(c.c_str(), L"Chrome_RenderWidgetHostHWND") == 0 ||
        _wcsicmp(c.c_str(), L"Internet Explorer_Server") == 0 ||
        Contiene(c, L"HwndWrapper[");
}

// CID-18-23 : Identifica clases Win32 claramente no editables para evitar falsos positivos.
static bool EsClaseClaramenteNoEditable(HWND hwnd)
{
    if (!hwnd) return true;

    const std::wstring c = ObtenerClase(hwnd);

    return
        _wcsicmp(c.c_str(), L"Button") == 0 ||
        _wcsicmp(c.c_str(), L"Static") == 0 ||
        _wcsicmp(c.c_str(), L"ComboBox") == 0 ||
        _wcsicmp(c.c_str(), L"ComboLBox") == 0 ||
        _wcsicmp(c.c_str(), L"ListBox") == 0 ||
        _wcsicmp(c.c_str(), L"SysListView32") == 0 ||
        _wcsicmp(c.c_str(), L"SysTreeView32") == 0 ||
        _wcsicmp(c.c_str(), L"ToolbarWindow32") == 0 ||
        _wcsicmp(c.c_str(), L"ReBarWindow32") == 0 ||
        _wcsicmp(c.c_str(), L"msctls_statusbar32") == 0 ||
        _wcsicmp(c.c_str(), L"Shell_TrayWnd") == 0 ||
        _wcsicmp(c.c_str(), L"Shell_SecondaryTrayWnd") == 0;
}

// CID-18-24 : En controles Edit puros comprueba además que no estén en modo solo lectura.
static bool EsEditNoReadonly(HWND hwnd)
{
    if (!hwnd) return false;

    if (!EsClase(hwnd, L"Edit"))
        return true;

    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    return (style & ES_READONLY) == 0;
}

// CID-18-25 : Obtiene el rectángulo en pantalla de una ventana válida.
static bool ObtenerRectPantalla(HWND hwnd, RECT& out)
{
    if (!hwnd || !IsWindow(hwnd))
        return false;

    RECT rc{};
    if (!GetWindowRect(hwnd, &rc))
        return false;

    if (!RectValido(rc))
        return false;

    out = rc;
    return true;
}

// CID-18-26 : Obtiene y normaliza el rectángulo real del caret en coordenadas de pantalla.
static bool ObtenerRectCaretEnPantalla(const GUITHREADINFO& gti, RECT& out)
{
    if (!gti.hwndCaret || !IsWindow(gti.hwndCaret))
        return false;

    RECT rc = gti.rcCaret;

    if (rc.bottom <= rc.top)
        return false;

    MapWindowPoints(gti.hwndCaret, HWND_DESKTOP, reinterpret_cast<LPPOINT>(&rc), 2);
    NormalizarRectCaret(rc);

    out = rc;
    return true;
}

// CID-18-27 : Intenta obtener el foco real del hilo foreground mediante AttachThreadInput.
static HWND ObtenerFocusAlternativo(HWND hwndForeground)
{
    if (!hwndForeground)
        return nullptr;

    DWORD tidForeground = GetWindowThreadProcessId(hwndForeground, nullptr);
    DWORD tidActual = GetCurrentThreadId();

    if (!tidForeground)
        return nullptr;

    HWND out = nullptr;

    if (AttachThreadInput(tidActual, tidForeground, TRUE))
    {
        out = GetFocus();
        AttachThreadInput(tidActual, tidForeground, FALSE);
    }

    return out;
}

// CID-18-28 : Comprueba si un rectángulo UIA es sospechosamente grande respecto a la ventana foreground.
static bool RectGiganteRespectoAVentana(const RECT& rc, HWND hwndForeground)
{
    RECT rcWin{};
    if (!ObtenerRectPantalla(hwndForeground, rcWin))
        return false;

    const int w1 = rc.right - rc.left;
    const int h1 = rc.bottom - rc.top;
    const int w2 = rcWin.right - rcWin.left;
    const int h2 = rcWin.bottom - rcWin.top;

    if (w1 <= 0 || h1 <= 0 || w2 <= 0 || h2 <= 0)
        return false;

    const double area1 = (double)w1 * (double)h1;
    const double area2 = (double)w2 * (double)h2;
    const double ratio = area1 / area2;

    return ratio > 0.65;
}

// CID-18-29 : Identifica HRESULTs de desconexión o elementos UIA no disponibles.
static bool EsHRESULTDesconexion(HRESULT hr)
{
    return
        hr == RPC_E_DISCONNECTED ||
        hr == RPC_E_CALL_REJECTED ||
        hr == CO_E_OBJNOTCONNECTED ||
        hr == UIA_E_ELEMENTNOTAVAILABLE;
}

// CID-18-30 : Decide si conviene activar el fallback de UI Automation según clases modernas detectadas.
static bool NecesitaUIAFallback(HWND hwndFocus, HWND hwndForeground)
{
    std::wstring claseFocus = ObtenerClase(hwndFocus);
    std::wstring claseForeground = ObtenerClase(hwndForeground);

    if (EsClaseWrapperModerna(claseFocus))
        return true;

    if (EsClaseWrapperModerna(claseForeground))
        return true;

    return false;
}

// CID-18-31 : Intenta localizar un elemento enfocado editable mediante UI Automation y obtener su rectángulo.
static bool UiAutomation_IntentarRectElementoEnfocado(HWND hwndForeground, RECT& outRect, std::wstring& outInfo)
{
    outInfo.clear();

    HRESULT hrCo = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    bool needUninit = (hrCo == S_OK || hrCo == S_FALSE);

    if (FAILED(hrCo) && hrCo != RPC_E_CHANGED_MODE)
        return false;

    IUIAutomation* automation = nullptr;
    IUIAutomationElement* focused = nullptr;
    IUIAutomationValuePattern* valuePattern = nullptr;
    IUIAutomationTextPattern* textPattern = nullptr;

    bool ok = false;

    do
    {
        HRESULT hr = CoCreateInstance(
            CLSID_CUIAutomation,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&automation)
        );
        if (FAILED(hr) || !automation)
            break;

        hr = automation->GetFocusedElement(&focused);
        if (FAILED(hr) || !focused)
            break;

        CONTROLTYPEID controlType = 0;
        BOOL isKeyboardFocusable = FALSE;
        RECT rc{ 0,0,0,0 };
        BSTR className = nullptr;
        BSTR name = nullptr;

        hr = focused->get_CurrentControlType(&controlType);
        if (FAILED(hr)) break;

        hr = focused->get_CurrentIsKeyboardFocusable(&isKeyboardFocusable);
        if (FAILED(hr)) break;

        hr = focused->get_CurrentBoundingRectangle(&rc);
        if (FAILED(hr)) break;

        hr = focused->get_CurrentClassName(&className);
        if (FAILED(hr) && !EsHRESULTDesconexion(hr)) break;

        hr = focused->get_CurrentName(&name);
        if (FAILED(hr) && !EsHRESULTDesconexion(hr)) break;

        HRESULT hrValue = focused->GetCurrentPatternAs(UIA_ValuePatternId, IID_PPV_ARGS(&valuePattern));
        if (FAILED(hrValue) && !EsHRESULTDesconexion(hrValue))
        {
            if (className) SysFreeString(className);
            if (name) SysFreeString(name);
            break;
        }

        HRESULT hrText = focused->GetCurrentPatternAs(UIA_TextPatternId, IID_PPV_ARGS(&textPattern));
        if (FAILED(hrText) && !EsHRESULTDesconexion(hrText))
        {
            if (className) SysFreeString(className);
            if (name) SysFreeString(name);
            break;
        }

        bool rectOk = RectValido(rc);
        bool tipoEdit = (controlType == UIA_EditControlTypeId);
        bool tipoDocumento = (controlType == UIA_DocumentControlTypeId);
        bool soportaTexto = (valuePattern != nullptr) || (textPattern != nullptr);

        std::wstring clase = className ? std::wstring(className) : std::wstring(L"");
        std::wstring nombre = name ? std::wstring(name) : std::wstring(L"");

        outInfo =
            L"UIA type=" + std::to_wstring(controlType) +
            L" class=" + (clase.empty() ? std::wstring(L"(null)") : clase) +
            L" name=" + (nombre.empty() ? std::wstring(L"(null)") : nombre);

        if (rectOk && isKeyboardFocusable && soportaTexto)
        {
            if (tipoEdit)
            {
                ok = true;
            }
            else if (tipoDocumento && !RectGiganteRespectoAVentana(rc, hwndForeground))
            {
                ok = true;
            }
        }

        if (ok)
            outRect = rc;

        if (className) SysFreeString(className);
        if (name) SysFreeString(name);
    } while (false);

    SafeRelease(textPattern);
    SafeRelease(valuePattern);
    SafeRelease(focused);
    SafeRelease(automation);

    if (needUninit)
        CoUninitialize();

    return ok;
}

// CID-18-32 : Resuelve el mejor contexto de texto editable disponible usando caret, Win32 claro o UIA.
static ContextoTextoDetectado ResolverContextoTexto()
{
    ContextoTextoDetectado ctx{};

    HWND hwndForeground = GetForegroundWindow();
    if (!hwndForeground || !IsWindow(hwndForeground) || IsIconic(hwndForeground))
        return ctx;

    DWORD tid = GetWindowThreadProcessId(hwndForeground, nullptr);
    if (!tid)
        return ctx;

    GUITHREADINFO gti{};
    gti.cbSize = sizeof(gti);
    if (!GetGUIThreadInfo(tid, &gti))
        return ctx;

    HWND hwndFocus = gti.hwndFocus;
    if (!hwndFocus)
        hwndFocus = ObtenerFocusAlternativo(hwndForeground);
    if (!hwndFocus && gti.hwndCaret)
        hwndFocus = gti.hwndCaret;

    ctx.hwnd_foreground = hwndForeground;
    ctx.hwnd_focus = hwndFocus;
    ctx.clase_focus = ObtenerClase(hwndFocus);

    // CID-18-33 : Caso preferente basado en caret Win32 real.
    RECT rcCaret{};
    if (ObtenerRectCaretEnPantalla(gti, rcCaret))
    {
        ctx.visible = true;
        ctx.rc_anclaje = rcCaret;
        ctx.origen = L"caret-win32";
        return ctx;
    }

    // CID-18-34 : Fallback sobre controles editables Win32 claramente reconocibles.
    if (hwndFocus &&
        EsClaseEditableClara(hwndFocus) &&
        EsEditNoReadonly(hwndFocus) &&
        !EsClaseClaramenteNoEditable(hwndFocus))
    {
        RECT rcFocus{};
        if (ObtenerRectPantalla(hwndFocus, rcFocus))
        {
            ctx.visible = true;
            ctx.rc_anclaje = rcFocus;
            ctx.origen = L"control-win32";
            return ctx;
        }
    }

    // CID-18-35 : Fallback estricto por UI Automation solo para wrappers modernos compatibles.
    if (hwndFocus &&
        !EsClaseClaramenteNoEditable(hwndFocus) &&
        NecesitaUIAFallback(hwndFocus, hwndForeground))
    {
        RECT rcUIA{};
        std::wstring infoUIA;
        if (UiAutomation_IntentarRectElementoEnfocado(hwndForeground, rcUIA, infoUIA))
        {
            ctx.visible = true;
            ctx.rc_anclaje = rcUIA;
            ctx.origen = infoUIA;
            return ctx;
        }
    }

    return ctx;
}

// CID-18-36 : Aplica el contexto detectado si cambia, con debounce de aparición y control de foco activo.
static void AplicarContextoSiCambia_NoLock(const ContextoTextoDetectado& ctx)
{
    if (ctx.clase_focus != g_ultima_clase_log)
    {
        g_ultima_clase_log = ctx.clase_focus;
        Log(L"[CTX] focus class = " + (ctx.clase_focus.empty() ? std::wstring(L"(null)") : ctx.clase_focus));
    }

    ULONGLONG ahora = GetTickCount64();
    bool actividadReciente =
        (g_ultimo_input_escribible_tick != 0) &&
        ((ahora - g_ultimo_input_escribible_tick) <= VENTANA_ACTIVACION_MS);

    // CID-18-37 : Oculta el panel y limpia candidato si ya no hay contexto editable visible.
    if (!ctx.visible)
    {
        g_tenemos_candidato = false;
        g_candidato_tick = 0;

        if (g_ultimo_visible)
        {
            g_ultimo_visible = false;
            g_ultimo_rect = RECT{ 0,0,0,0 };
            g_ultimo_hwnd_foreground = ctx.hwnd_foreground;
            g_ultimo_hwnd_focus = ctx.hwnd_focus;
            Log(L"[CTX] panel hidden");
            Superposicion_SetVisible(false);
        }
        return;
    }

    // CID-18-38 : Mientras el panel aún no está visible exige actividad escribible reciente para mostrarlo.
    if (!g_ultimo_visible && !actividadReciente)
    {
        g_tenemos_candidato = false;
        g_candidato_tick = 0;
        return;
    }

    // CID-18-39 : Gestiona el debounce inicial antes de hacer visible el panel por primera vez.
    if (!g_ultimo_visible)
    {
        bool mismoCandidato =
            g_tenemos_candidato &&
            g_candidato.hwnd_foreground == ctx.hwnd_foreground &&
            g_candidato.hwnd_focus == ctx.hwnd_focus &&
            RectParecidos(g_candidato.rc_anclaje, ctx.rc_anclaje, 20);

        if (!mismoCandidato)
        {
            g_tenemos_candidato = true;
            g_candidato = ctx;
            g_candidato_tick = ahora;
            return;
        }

        if ((ahora - g_candidato_tick) < DEBOUNCE_MOSTRAR_MS)
            return;

        g_ultimo_visible = true;
        g_ultimo_rect = ctx.rc_anclaje;
        g_ultimo_hwnd_foreground = ctx.hwnd_foreground;
        g_ultimo_hwnd_focus = ctx.hwnd_focus;

        if (ctx.origen != g_ultimo_origen_log && !ctx.origen.empty())
        {
            g_ultimo_origen_log = ctx.origen;
            Log(L"[CTX] source = " + ctx.origen);
        }

        Log(L"[CTX] panel visible at rect: " +
            std::to_wstring(ctx.rc_anclaje.left) + L"," +
            std::to_wstring(ctx.rc_anclaje.top) + L"," +
            std::to_wstring(ctx.rc_anclaje.right) + L"," +
            std::to_wstring(ctx.rc_anclaje.bottom));

        Superposicion_SetRectAnclaje(ctx.rc_anclaje);
        Superposicion_SetVisible(true);
        return;
    }

    // CID-18-40 : Si cambia la ventana o el foco real, esconde el panel y reinicia el ciclo de candidato.
    bool cambiaDeFoco =
        ctx.hwnd_foreground != g_ultimo_hwnd_foreground ||
        ctx.hwnd_focus != g_ultimo_hwnd_focus;

    if (cambiaDeFoco)
    {
        g_ultimo_visible = false;
        g_tenemos_candidato = false;
        Superposicion_SetVisible(false);
        return;
    }

    // CID-18-41 : Si cambia de forma apreciable el rectángulo de anclaje, reposiciona la superposición.
    if (!RectParecidos(ctx.rc_anclaje, g_ultimo_rect, 12))
    {
        g_ultimo_rect = ctx.rc_anclaje;

        if (ctx.origen != g_ultimo_origen_log && !ctx.origen.empty())
        {
            g_ultimo_origen_log = ctx.origen;
            Log(L"[CTX] source = " + ctx.origen);
        }

        Log(L"[CTX] panel visible at rect: " +
            std::to_wstring(ctx.rc_anclaje.left) + L"," +
            std::to_wstring(ctx.rc_anclaje.top) + L"," +
            std::to_wstring(ctx.rc_anclaje.right) + L"," +
            std::to_wstring(ctx.rc_anclaje.bottom));

        Superposicion_SetRectAnclaje(ctx.rc_anclaje);
    }
}

// CID-18-42 : Resuelve el contexto actual y aplica los cambios necesarios sobre el panel.
static void ActualizarContexto_NoLock()
{
    ContextoTextoDetectado ctx = ResolverContextoTexto();
    AplicarContextoSiCambia_NoLock(ctx);
}

// CID-18-43 : Callback periódico del temporizador que refresca el contexto editable actual.
static void CALLBACK TimerCallback(PVOID, BOOLEAN)
{
    if (!g_cs_iniciado)
        return;

    EnterCriticalSection(&g_cs);
    ActualizarContexto_NoLock();
    LeaveCriticalSection(&g_cs);
}

// CID-18-44 : Inicializa el panel de contexto, su temporizador y su estado base de detección.
bool IniciarPanelContextoTexto()
{
    if (!g_cs_iniciado)
    {
        InitializeCriticalSection(&g_cs);
        g_cs_iniciado = true;
    }

    EnterCriticalSection(&g_cs);

    g_ultimo_visible = false;
    g_ultimo_rect = RECT{ 0,0,0,0 };
    g_ultimo_hwnd_foreground = nullptr;
    g_ultimo_hwnd_focus = nullptr;
    g_ultima_clase_log.clear();
    g_ultimo_origen_log.clear();
    g_ultimo_input_escribible_tick = 0;
    g_tenemos_candidato = false;
    g_candidato = ContextoTextoDetectado{};
    g_candidato_tick = 0;

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

    if (ok)
    {
        g_iniciado = true;
        ActualizarContexto_NoLock();
    }

    LeaveCriticalSection(&g_cs);

    return ok;
}

// CID-18-45 : Detiene el panel de contexto liberando temporizador, estado interno y visibilidad.
void DetenerPanelContextoTexto()
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
        EnterCriticalSection(&g_cs);

        g_iniciado = false;
        g_ultimo_visible = false;
        g_ultimo_rect = RECT{ 0,0,0,0 };
        g_ultimo_hwnd_foreground = nullptr;
        g_ultimo_hwnd_focus = nullptr;
        g_ultima_clase_log.clear();
        g_ultimo_origen_log.clear();
        g_ultimo_input_escribible_tick = 0;
        g_tenemos_candidato = false;
        g_candidato = ContextoTextoDetectado{};
        g_candidato_tick = 0;

        LeaveCriticalSection(&g_cs);

        DeleteCriticalSection(&g_cs);
        g_cs_iniciado = false;
    }

    Superposicion_SetVisible(false);
}

// CID-18-46 : Fuerza una actualización inmediata del contexto sin esperar al siguiente tick periódico.
void ActualizarPanelContextoTextoAhora()
{
    if (!g_cs_iniciado || !g_iniciado)
        return;

    EnterCriticalSection(&g_cs);
    ActualizarContexto_NoLock();
    LeaveCriticalSection(&g_cs);
}

// CID-18-47 : Registra actividad escribible reciente para permitir la aparición del panel contextual.
void NotificarActividadEscribiblePanelContextoTexto()
{
    if (!g_cs_iniciado || !g_iniciado)
        return;

    EnterCriticalSection(&g_cs);
    g_ultimo_input_escribible_tick = GetTickCount64();
    LeaveCriticalSection(&g_cs);
}