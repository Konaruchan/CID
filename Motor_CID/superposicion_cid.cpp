// CID-12-01 : Inclusión de la implementación de la superposición visual del sistema CID.
#include "superposicion_cid.h"

// CID-12-02 : Inclusión de cabeceras del sistema y utilidades de texto, contenedores y caracteres.
#include <windows.h>
#include <string>
#include <vector>
#include <cwctype>

// CID-12-03 : Estado global de la ventana principal de la superposición CID.
static HWND g_hwnd = nullptr;

// CID-12-04 : Estado global de sincronización para proteger acceso concurrente a la superposición.
static CRITICAL_SECTION g_cs;
static bool g_cs_iniciado = false;

// CID-12-05 : Estado textual legado de bitácora y última línea asentada mostrada en el pie del panel.
static std::wstring g_linea_bitacora;
static std::wstring g_linea_asentado;

// CID-12-06 : Estado visual autoritativo de la bitácora y bandera de modo visual moderno.
static EstadoVisualBitacoraCID g_estado_visual;
static bool g_modo_visual_autoritativo = false;

// CID-12-07 : Estado temporal del efecto visual de error de acorde y su duración configurada.
static ULONGLONG g_error_hasta_tick = 0;
static const ULONGLONG ERROR_MS = 160;

// CID-12-08 : Recursos tipográficos usados por el panel principal y la línea de información.
static HFONT g_font_tokens = nullptr;
static HFONT g_font_info = nullptr;

// CID-12-09 : Identidad de clase de ventana y temporizador interno de animación visual.
static const wchar_t* CLASE = L"SUPERPOSICION_CID_PANEL";
static const UINT ID_TIMER_ANIM = 1;

// CID-12-10 : Mensajes internos que fuerzan layout e invalidación siempre en el hilo de la ventana.
static const UINT WM_CID_APLICAR_LAYOUT = WM_APP + 101;
static const UINT WM_CID_INVALIDAR = WM_APP + 102;

// CID-12-11 : Dimensiones y posición base del panel grande de modo CID.
static const int PANEL_DEFAULT_X = 24;
static const int PANEL_DEFAULT_Y = 24;
static const int PANEL_W = 392;
static const int PANEL_H = 214;

// CID-12-12 : Dimensiones del panel reducido usado en modo QWERTY.
static const int PANEL_QWERTY_W = 132;
static const int PANEL_QWERTY_H = 28;

// CID-12-13 : Márgenes de pantalla y separación visual respecto al rectángulo de anclaje.
static const int PANEL_MARGEN_PANTALLA = 8;
static const int PANEL_SEPARACION_ANCLAJE = 8;

// CID-12-14 : Límites de historial visual y número de líneas visibles simultáneamente en pantalla.
static const int MAX_LINEAS_CERRADAS_UI = 24;
static const int LINEAS_VISIBLES = 5;

// CID-12-15 : Estado deseado de visibilidad, anclaje y modo QWERTY de la superposición.
static bool g_visible_deseado = false;
static bool g_tiene_rect_anclaje = false;
static RECT g_rect_anclaje{ 0,0,0,0 };

static bool g_modo_qwerty = false;

// CID-12-16 : Interpola linealmente un byte entre dos extremos para construir colores intermedios.
static BYTE LerpByte(BYTE a, BYTE b, int t, int den)
{
    return (BYTE)(a + (((int)b - (int)a) * t) / den);
}

// CID-12-17 : Interpola linealmente un color RGB completo a partir de dos colores base.
static COLORREF LerpColor(COLORREF a, COLORREF b, int t, int den)
{
    return RGB(
        LerpByte(GetRValue(a), GetRValue(b), t, den),
        LerpByte(GetGValue(a), GetGValue(b), t, den),
        LerpByte(GetBValue(a), GetBValue(b), t, den)
    );
}

// CID-12-18 : Convierte una cadena completa a mayúsculas para su representación visual en el panel.
static std::wstring A_Mayusculas(const std::wstring& s)
{
    std::wstring out = s;
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = (wchar_t)towupper(out[i]);
    return out;
}

// CID-12-19 : Indica si el efecto visual de error sigue activo en este instante.
static bool ErrorVisualActivo_NoLock()
{
    return GetTickCount64() < g_error_hasta_tick;
}

// CID-12-20 : Comprueba si un rectángulo tiene dimensiones positivas utilizables.
static bool RectValido(const RECT& rc)
{
    return (rc.right > rc.left) && (rc.bottom > rc.top);
}

// CID-12-21 : Heurística para detectar si un rectángulo de anclaje parece representar un caret de texto.
static bool PareceCaret(const RECT& rc)
{
    return RectValido(rc) && ((rc.right - rc.left) <= 10);
}

// CID-12-22 : Solicita repintado asíncrono de la ventana de superposición en su propio hilo.
static void SolicitarInvalidar()
{
    if (g_hwnd)
        PostMessageW(g_hwnd, WM_CID_INVALIDAR, 0, 0);
}

// CID-12-23 : Solicita recálculo asíncrono de layout y posición de la superposición en su propio hilo.
static void SolicitarAplicarLayout()
{
    if (g_hwnd)
        PostMessageW(g_hwnd, WM_CID_APLICAR_LAYOUT, 0, 0);
}

// CID-12-24 : Recorta el historial visual cerrado a un máximo seguro para la interfaz.
static void LimitarLineasCerradasUI_NoLock()
{
    if (g_estado_visual.lineas_cerradas.size() > MAX_LINEAS_CERRADAS_UI)
    {
        size_t exceso = g_estado_visual.lineas_cerradas.size() - MAX_LINEAS_CERRADAS_UI;
        g_estado_visual.lineas_cerradas.erase(
            g_estado_visual.lineas_cerradas.begin(),
            g_estado_visual.lineas_cerradas.begin() + exceso
        );
    }
}

// CID-12-25 : Convierte la bitácora textual antigua entre corchetes en tokens visuales básicos de piezas.
static std::vector<TokenVisualCID> ParsearTokensLegacy(const std::wstring& texto)
{
    std::vector<TokenVisualCID> out;

    if (texto.size() < 2)
        return out;

    std::wstring s = texto;

    if (!s.empty() && s.front() == L'[')
        s.erase(s.begin());
    if (!s.empty() && s.back() == L']')
        s.pop_back();

    size_t i = 0;
    while (i < s.size())
    {
        while (i < s.size() && (s[i] == L' ' || s[i] == L'\t'))
            ++i;

        if (i >= s.size())
            break;

        size_t j = i;
        while (j < s.size() && s[j] != L' ' && s[j] != L'\t')
            ++j;

        std::wstring token = s.substr(i, j - i);
        if (!token.empty())
        {
            TokenVisualCID tv;
            tv.tipo = TipoTokenVisualCID::Pieza;
            tv.texto = token;
            out.push_back(tv);
        }

        i = j;
    }

    return out;
}

// CID-12-26 : Traduce la bitácora textual heredada al estado visual interno mientras no exista modo autoritativo.
static void AplicarBitacoraLegacyAlEstadoVisual_NoLock(const std::wstring& texto)
{
    if (g_modo_visual_autoritativo)
        return;

    std::vector<TokenVisualCID> tokens = ParsearTokensLegacy(texto);

    if (tokens.empty())
    {
        if (!g_estado_visual.linea_actual.tokens.empty())
        {
            g_estado_visual.lineas_cerradas.push_back(g_estado_visual.linea_actual);
            LimitarLineasCerradasUI_NoLock();
        }
        g_estado_visual.linea_actual.tokens.clear();
        return;
    }

    g_estado_visual.linea_actual.tokens = tokens;
}

// CID-12-27 : Construye las filas visibles finales combinando líneas cerradas recientes y línea actual.
static void ConstruirFilasVisibles(
    const EstadoVisualBitacoraCID& estado,
    std::vector<LineaVisualCID>& filas_out,
    int& indice_activa_out)
{
    filas_out.clear();

    int cerradas = (int)estado.lineas_cerradas.size();
    int desde = cerradas - (LINEAS_VISIBLES - 1);
    if (desde < 0) desde = 0;

    for (int i = desde; i < cerradas; ++i)
        filas_out.push_back(estado.lineas_cerradas[(size_t)i]);

    filas_out.push_back(estado.linea_actual);

    while ((int)filas_out.size() < LINEAS_VISIBLES)
        filas_out.insert(filas_out.begin(), LineaVisualCID{});

    if ((int)filas_out.size() > LINEAS_VISIBLES)
        filas_out.erase(filas_out.begin(), filas_out.begin() + ((int)filas_out.size() - LINEAS_VISIBLES));

    indice_activa_out = (int)filas_out.size() - 1;
}

// CID-12-28 : Aplica visibilidad, tamaño y posición de la ventana según modo, anclaje y monitor activo.
static void AplicarVisibilidadYPosicion_NoLock()
{
    if (!g_hwnd)
        return;

    if (!g_visible_deseado)
    {
        ShowWindow(g_hwnd, SW_HIDE);
        return;
    }

    const int panelW = g_modo_qwerty ? PANEL_QWERTY_W : PANEL_W;
    const int panelH = g_modo_qwerty ? PANEL_QWERTY_H : PANEL_H;

    int x = PANEL_DEFAULT_X;
    int y = PANEL_DEFAULT_Y;

    RECT rcTrabajo{};
    bool tieneMonitor = false;

    // CID-12-29 : Si existe rectángulo de anclaje válido, calcula la mejor posición relativa al caret o control.
    if (g_tiene_rect_anclaje && RectValido(g_rect_anclaje))
    {
        HMONITOR mon = MonitorFromRect(&g_rect_anclaje, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mi{};
        mi.cbSize = sizeof(mi);
        if (GetMonitorInfoW(mon, &mi))
        {
            rcTrabajo = mi.rcWork;
            tieneMonitor = true;
        }

        if (PareceCaret(g_rect_anclaje))
        {
            int caretCentro = (g_rect_anclaje.left + g_rect_anclaje.right) / 2;
            x = caretCentro - (panelW / 2);
        }
        else
        {
            x = g_rect_anclaje.left + 8;
        }

        int espacioAbajo = rcTrabajo.bottom - g_rect_anclaje.bottom - PANEL_SEPARACION_ANCLAJE;
        int espacioArriba = g_rect_anclaje.top - rcTrabajo.top - PANEL_SEPARACION_ANCLAJE;

        if (!tieneMonitor)
        {
            y = g_rect_anclaje.bottom + PANEL_SEPARACION_ANCLAJE;
        }
        else
        {
            if (espacioAbajo >= panelH || espacioAbajo >= espacioArriba)
                y = g_rect_anclaje.bottom + PANEL_SEPARACION_ANCLAJE;
            else
                y = g_rect_anclaje.top - panelH - PANEL_SEPARACION_ANCLAJE;

            if (x < rcTrabajo.left + PANEL_MARGEN_PANTALLA)
                x = rcTrabajo.left + PANEL_MARGEN_PANTALLA;
            if (x > rcTrabajo.right - panelW - PANEL_MARGEN_PANTALLA)
                x = rcTrabajo.right - panelW - PANEL_MARGEN_PANTALLA;

            if (y < rcTrabajo.top + PANEL_MARGEN_PANTALLA)
                y = rcTrabajo.top + PANEL_MARGEN_PANTALLA;
            if (y > rcTrabajo.bottom - panelH - PANEL_MARGEN_PANTALLA)
                y = rcTrabajo.bottom - panelH - PANEL_MARGEN_PANTALLA;
        }
    }

    SetWindowPos(
        g_hwnd,
        HWND_TOPMOST,
        x, y, panelW, panelH,
        SWP_NOACTIVATE | SWP_SHOWWINDOW
    );
}

// CID-12-30 : Rellena un rectángulo completo con un color sólido.
static void RellenarRect(HDC hdc, const RECT& rc, COLORREF color)
{
    HBRUSH br = CreateSolidBrush(color);
    FillRect(hdc, &rc, br);
    DeleteObject(br);
}

// CID-12-31 : Dibuja el borde de un rectángulo usando un color de línea simple.
static void DibujarRectBorde(HDC hdc, const RECT& rc, COLORREF borde)
{
    HPEN pen = CreatePen(PS_SOLID, 1, borde);
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

// CID-12-32 : Dibuja un degradado vertical por líneas interpolando entre tres colores.
static void DibujarDegradadoVertical(HDC hdc, const RECT& rc, COLORREF top, COLORREF mid, COLORREF bottom)
{
    int h = rc.bottom - rc.top;
    if (h <= 0) return;

    int mitad = h / 2;
    if (mitad <= 0) mitad = 1;

    for (int y = 0; y < h; ++y)
    {
        COLORREF c;
        if (y <= mitad)
            c = LerpColor(top, mid, y, mitad);
        else
            c = LerpColor(mid, bottom, y - mitad, h - mitad);

        HPEN pen = CreatePen(PS_SOLID, 1, c);
        HGDIOBJ oldPen = SelectObject(hdc, pen);

        MoveToEx(hdc, rc.left, rc.top + y, nullptr);
        LineTo(hdc, rc.right, rc.top + y);

        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }
}

// CID-12-33 : Dibuja una fila del panel con estilo distinto según esté activa o alternada.
static void DibujarFila(HDC hdc, const RECT& rc, bool activa, bool alterna)
{
    COLORREF top, mid, bottom, borde;

    if (activa)
    {
        top = RGB(216, 230, 249);
        mid = RGB(238, 244, 253);
        bottom = RGB(216, 230, 249);
        borde = RGB(180, 202, 232);
    }
    else if (alterna)
    {
        top = RGB(234, 239, 244);
        mid = RGB(246, 248, 250);
        bottom = RGB(234, 239, 244);
        borde = RGB(213, 220, 227);
    }
    else
    {
        top = RGB(246, 248, 250);
        mid = RGB(253, 254, 255);
        bottom = RGB(246, 248, 250);
        borde = RGB(223, 228, 233);
    }

    DibujarDegradadoVertical(hdc, rc, top, mid, bottom);

    HPEN pen = CreatePen(PS_SOLID, 1, borde);
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    MoveToEx(hdc, rc.left, rc.bottom - 1, nullptr);
    LineTo(hdc, rc.right, rc.bottom - 1);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

// CID-12-34 : Devuelve el ancho aproximado de un carácter monoespaciado para cálculos de wrapping.
static int AnchoCaracterMono(HDC hdc)
{
    SIZE sz{};
    GetTextExtentPoint32W(hdc, L"M", 1, &sz);
    return (sz.cx > 0) ? sz.cx : 8;
}

// CID-12-35 : Parte un token largo en varias líneas cuando no contiene espacios y supera el ancho útil.
static std::wstring PartirTokenLargo(const std::wstring& texto, int maxCharsPorLinea)
{
    if (maxCharsPorLinea < 4)
        maxCharsPorLinea = 4;

    bool tieneEspacios = false;
    for (wchar_t c : texto)
    {
        if (c == L' ' || c == L'\t')
        {
            tieneEspacios = true;
            break;
        }
    }

    if (tieneEspacios || (int)texto.size() <= maxCharsPorLinea)
        return texto;

    std::wstring out;
    for (size_t i = 0; i < texto.size(); ++i)
    {
        if (i > 0 && (i % (size_t)maxCharsPorLinea) == 0)
            out += L'\n';
        out += texto[i];
    }
    return out;
}

// CID-12-36 : Dibuja texto centrado y con wrapping dentro de una caja calculando su altura visual real.
static void DibujarTextoCajaCentradoWrap(HDC hdc, RECT rcCaja, const std::wstring& texto)
{
    int anchoChar = AnchoCaracterMono(hdc);
    int anchoCaja = rcCaja.right - rcCaja.left - 4;
    int maxCharsPorLinea = (anchoChar > 0) ? (anchoCaja / anchoChar) : 8;

    std::wstring t = PartirTokenLargo(A_Mayusculas(texto), maxCharsPorLinea);

    RECT rcCalc = rcCaja;
    DrawTextW(
        hdc,
        t.c_str(),
        (int)t.size(),
        &rcCalc,
        DT_CENTER | DT_WORDBREAK | DT_NOPREFIX | DT_EDITCONTROL | DT_CALCRECT
    );

    int altoTexto = rcCalc.bottom - rcCalc.top;
    int altoCaja = rcCaja.bottom - rcCaja.top;
    int dy = 0;
    if (altoTexto < altoCaja)
        dy = (altoCaja - altoTexto) / 2;

    RECT rcDraw = rcCaja;
    rcDraw.top += dy;

    DrawTextW(
        hdc,
        t.c_str(),
        (int)t.size(),
        &rcDraw,
        DT_CENTER | DT_WORDBREAK | DT_NOPREFIX | DT_EDITCONTROL
    );
}

// CID-12-37 : Dibuja los tokens de una línea distribuyéndolos de forma equilibrada dentro de su fila.
static void DibujarTokensLinea(HDC hdc, const RECT& rc, const LineaVisualCID& linea)
{
    const int n = (int)linea.tokens.size();
    if (n <= 0) return;

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(36, 44, 54));

    int left = rc.left + 14;
    int right = rc.right - 14;
    int top = rc.top + 2;
    int bottom = rc.bottom - 2;

    // CID-12-38 : Caso especial para una sola pieza ocupando visualmente todo el ancho útil de la fila.
    if (n == 1)
    {
        RECT rcSolo{ left, top, right, bottom };
        DibujarTextoCajaCentradoWrap(hdc, rcSolo, linea.tokens[0].texto);
        return;
    }

    const int gap = 6;
    int totalGap = gap * (n - 1);
    int anchoTotal = right - left;
    if (anchoTotal <= totalGap)
        totalGap = 0;

    int cellW = (anchoTotal - totalGap) / n;
    if (cellW < 24) cellW = 24;

    int usado = cellW * n + gap * (n - 1);
    int x = left + ((anchoTotal - usado) / 2);

    // CID-12-39 : Dibuja cada token en su celda horizontal correspondiente.
    for (int i = 0; i < n; ++i)
    {
        RECT rcCell{
            x,
            top,
            x + cellW,
            bottom
        };

        DibujarTextoCajaCentradoWrap(hdc, rcCell, linea.tokens[(size_t)i].texto);
        x += cellW + gap;
    }
}

// CID-12-40 : Dibuja las marcas diagonales rojas en las esquinas cuando hay error visual activo.
static void DibujarEsquinasError(HDC hdc, const RECT& rc)
{
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(196, 56, 56));
    HGDIOBJ oldPen = SelectObject(hdc, pen);

    const int paso = 5;

    for (int i = 0; i < 4; ++i)
    {
        MoveToEx(hdc, rc.left + 6 + i * paso, rc.top + 2, nullptr);
        LineTo(hdc, rc.left + 2, rc.top + 6 + i * paso);
    }

    for (int i = 0; i < 4; ++i)
    {
        MoveToEx(hdc, rc.right - 6 - i * paso, rc.top + 2, nullptr);
        LineTo(hdc, rc.right - 2, rc.top + 6 + i * paso);
    }

    for (int i = 0; i < 4; ++i)
    {
        MoveToEx(hdc, rc.left + 6 + i * paso, rc.bottom - 2, nullptr);
        LineTo(hdc, rc.left + 2, rc.bottom - 6 - i * paso);
    }

    for (int i = 0; i < 4; ++i)
    {
        MoveToEx(hdc, rc.right - 6 - i * paso, rc.bottom - 2, nullptr);
        LineTo(hdc, rc.right - 2, rc.bottom - 6 - i * paso);
    }

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

// CID-12-41 : Procedimiento de ventana principal que procesa entrada, temporización, layout y repintado.
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_MOUSEACTIVATE:
        return MA_NOACTIVATE;

    case WM_ERASEBKGND:
        return 1;

        // CID-12-42 : Aplica layout y posición solicitados de forma segura en el hilo de la ventana.
    case WM_CID_APLICAR_LAYOUT:
    {
        if (g_cs_iniciado)
        {
            EnterCriticalSection(&g_cs);
            AplicarVisibilidadYPosicion_NoLock();
            LeaveCriticalSection(&g_cs);
        }
        return 0;
    }

    // CID-12-43 : Invalida completamente la ventana para solicitar un nuevo repintado.
    case WM_CID_INVALIDAR:
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;

        // CID-12-44 : Anima repintados periódicos solo mientras siga vivo el efecto visual de error.
    case WM_TIMER:
        if (wParam == ID_TIMER_ANIM)
        {
            bool inval = false;

            if (g_cs_iniciado)
            {
                EnterCriticalSection(&g_cs);
                inval = ErrorVisualActivo_NoLock();
                LeaveCriticalSection(&g_cs);
            }

            if (inval)
                InvalidateRect(hwnd, nullptr, TRUE);
        }
        return 0;

        // CID-12-45 : Dibuja el panel completo en backbuffer y lo copia luego a pantalla para evitar parpadeos.
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdcPantalla = BeginPaint(hwnd, &ps);

        RECT rcClient;
        GetClientRect(hwnd, &rcClient);

        int ancho = rcClient.right - rcClient.left;
        int alto = rcClient.bottom - rcClient.top;

        HDC hdc = CreateCompatibleDC(hdcPantalla);
        HBITMAP bmp = CreateCompatibleBitmap(hdcPantalla, ancho, alto);
        HGDIOBJ oldBmp = SelectObject(hdc, bmp);

        EstadoVisualBitacoraCID estado;
        std::wstring asentado;
        bool errorActivo = false;
        bool modoQwerty = false;

        // CID-12-46 : Captura una instantánea local del estado protegido antes de dibujar.
        EnterCriticalSection(&g_cs);
        estado = g_estado_visual;
        asentado = g_linea_asentado;
        errorActivo = ErrorVisualActivo_NoLock();
        modoQwerty = g_modo_qwerty;
        LeaveCriticalSection(&g_cs);

        RellenarRect(hdc, rcClient, RGB(229, 234, 239));

        int shakeX = 0;
        if (errorActivo)
        {
            ULONGLONG ahora = GetTickCount64();
            int fase = (int)((ahora / 18) % 4);
            int amp = 3;
            shakeX = (fase == 0 || fase == 2) ? -amp : amp;
        }

        RECT rcPanel{
            6 + shakeX,
            6,
            rcClient.right - 6 + shakeX,
            rcClient.bottom - 6
        };

        // CID-12-47 : Dibuja el panel compacto de modo QWERTY cuando ese modo está activo.
        if (modoQwerty)
        {
            RECT rcSombra = rcPanel;
            OffsetRect(&rcSombra, 2, 2);
            RellenarRect(hdc, rcSombra, RGB(206, 213, 221));

            DibujarDegradadoVertical(
                hdc,
                rcPanel,
                RGB(244, 245, 247),
                RGB(252, 252, 253),
                RGB(244, 245, 247)
            );
            DibujarRectBorde(hdc, rcPanel, RGB(170, 180, 192));

            HGDIOBJ oldFont = SelectObject(hdc, g_font_info);
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(80, 88, 98));

            RECT rcText = rcPanel;
            rcText.left += 8;
            rcText.right -= 8;

            DrawTextW(
                hdc,
                L"MODO QWERTY",
                -1,
                &rcText,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE
            );

            SelectObject(hdc, oldFont);

            BitBlt(hdcPantalla, 0, 0, ancho, alto, hdc, 0, 0, SRCCOPY);

            SelectObject(hdc, oldBmp);
            DeleteObject(bmp);
            DeleteDC(hdc);

            EndPaint(hwnd, &ps);
            return 0;
        }

        // CID-12-48 : Dibuja la caja general del panel grande del modo CID con sombra y borde.
        RECT rcSombra = rcPanel;
        OffsetRect(&rcSombra, 2, 2);
        RellenarRect(hdc, rcSombra, RGB(206, 213, 221));

        RellenarRect(hdc, rcPanel, RGB(245, 247, 250));
        DibujarRectBorde(hdc, rcPanel, RGB(169, 179, 191));

        RECT rcLineas = rcPanel;
        rcLineas.left += 8;
        rcLineas.right -= 8;
        rcLineas.top += 8;
        rcLineas.bottom -= 26;

        RECT rcFooter = rcPanel;
        rcFooter.left += 8;
        rcFooter.right -= 8;
        rcFooter.top = rcLineas.bottom + 2;
        rcFooter.bottom = rcPanel.bottom - 5;

        std::vector<LineaVisualCID> filas;
        int indiceActiva = 0;
        ConstruirFilasVisibles(estado, filas, indiceActiva);

        int totalH = rcLineas.bottom - rcLineas.top;
        int filaH = totalH / LINEAS_VISIBLES;
        if (filaH < 24) filaH = 24;

        HGDIOBJ oldFont = SelectObject(hdc, g_font_tokens);

        // CID-12-49 : Dibuja cada fila visible del historial y la línea activa con sus tokens.
        for (int i = 0; i < LINEAS_VISIBLES; ++i)
        {
            RECT rcFila{
                rcLineas.left,
                rcLineas.top + i * filaH,
                rcLineas.right,
                (i == LINEAS_VISIBLES - 1) ? rcLineas.bottom : (rcLineas.top + (i + 1) * filaH)
            };

            bool activa = (i == indiceActiva);
            bool alterna = ((i % 2) != 0);

            DibujarFila(hdc, rcFila, activa, alterna);

            if (i >= 0 && i < (int)filas.size())
                DibujarTokensLinea(hdc, rcFila, filas[(size_t)i]);
        }

        SelectObject(hdc, oldFont);

        // CID-12-50 : Dibuja la línea divisoria y el texto informativo del último asentado en el pie.
        HPEN penFooter = CreatePen(PS_SOLID, 1, RGB(208, 214, 221));
        HGDIOBJ oldPen = SelectObject(hdc, penFooter);
        MoveToEx(hdc, rcFooter.left, rcFooter.top, nullptr);
        LineTo(hdc, rcFooter.right, rcFooter.top);
        SelectObject(hdc, oldPen);
        DeleteObject(penFooter);

        oldFont = SelectObject(hdc, g_font_info);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(86, 96, 108));

        std::wstring textoInfo;
        if (!asentado.empty())
            textoInfo = L"ASENTADO: " + asentado;

        RECT rcTextoInfo = rcFooter;
        rcTextoInfo.top += 2;
        DrawTextW(
            hdc,
            textoInfo.c_str(),
            (int)textoInfo.size(),
            &rcTextoInfo,
            DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS
        );

        SelectObject(hdc, oldFont);

        // CID-12-51 : Dibuja el adorno de error visual sobre el panel cuando el estado de error está activo.
        if (errorActivo)
            DibujarEsquinasError(hdc, rcPanel);

        BitBlt(hdcPantalla, 0, 0, ancho, alto, hdc, 0, 0, SRCCOPY);

        SelectObject(hdc, oldBmp);
        DeleteObject(bmp);
        DeleteDC(hdc);

        EndPaint(hwnd, &ps);
        return 0;
    }

    // CID-12-52 : Limpia temporizador y referencia global cuando la ventana es destruida.
    case WM_DESTROY:
        KillTimer(hwnd, ID_TIMER_ANIM);
        g_hwnd = nullptr;
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

// CID-12-53 : Inicializa la clase de ventana, recursos gráficos y estado base de la superposición CID.
bool IniciarSuperposicionCID(HINSTANCE hInst)
{
    if (!g_cs_iniciado)
    {
        InitializeCriticalSection(&g_cs);
        g_cs_iniciado = true;
    }

    // CID-12-54 : Construye las dos fuentes usadas por el panel para tokens e información secundaria.
    LOGFONTW lfTokens{};
    lfTokens.lfHeight = -15;
    lfTokens.lfWeight = FW_NORMAL;
    lfTokens.lfQuality = CLEARTYPE_QUALITY;
    lstrcpyW(lfTokens.lfFaceName, L"Consolas");

    LOGFONTW lfInfo{};
    lfInfo.lfHeight = -11;
    lfInfo.lfWeight = FW_NORMAL;
    lfInfo.lfQuality = CLEARTYPE_QUALITY;
    lstrcpyW(lfInfo.lfFaceName, L"Segoe UI");

    g_font_tokens = CreateFontIndirectW(&lfTokens);
    g_font_info = CreateFontIndirectW(&lfInfo);

    // CID-12-55 : Registra la clase de ventana y crea la ventana popup transparente de la superposición.
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.hInstance = hInst;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = CLASE;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr;

    RegisterClassExW(&wc);

    g_hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE,
        CLASE,
        L"Superposición CID",
        WS_POPUP,
        PANEL_DEFAULT_X, PANEL_DEFAULT_Y, PANEL_W, PANEL_H,
        nullptr, nullptr, hInst, nullptr
    );

    if (!g_hwnd)
        return false;

    SetLayeredWindowAttributes(g_hwnd, 0, (BYTE)246, LWA_ALPHA);
    SetTimer(g_hwnd, ID_TIMER_ANIM, 16, nullptr);

    // CID-12-56 : Inicializa el estado interno base de la superposición tras crear la ventana.
    EnterCriticalSection(&g_cs);
    g_linea_bitacora = L"[]";
    g_linea_asentado.clear();
    g_estado_visual.lineas_cerradas.clear();
    g_estado_visual.linea_actual.tokens.clear();
    g_modo_visual_autoritativo = false;
    g_error_hasta_tick = 0;
    g_visible_deseado = false;
    g_tiene_rect_anclaje = false;
    g_rect_anclaje = RECT{ 0,0,0,0 };
    g_modo_qwerty = false;
    LeaveCriticalSection(&g_cs);

    ShowWindow(g_hwnd, SW_HIDE);
    SolicitarAplicarLayout();
    SolicitarInvalidar();

    return true;
}

// CID-12-57 : Detiene la superposición liberando ventana, fuentes y sincronización interna.
void DetenerSuperposicionCID()
{
    if (g_hwnd)
    {
        DestroyWindow(g_hwnd);
        g_hwnd = nullptr;
    }

    if (g_font_tokens)
    {
        DeleteObject(g_font_tokens);
        g_font_tokens = nullptr;
    }

    if (g_font_info)
    {
        DeleteObject(g_font_info);
        g_font_info = nullptr;
    }

    if (g_cs_iniciado)
    {
        DeleteCriticalSection(&g_cs);
        g_cs_iniciado = false;
    }
}

// CID-12-58 : Actualiza la bitácora textual heredada y la proyecta al estado visual cuando procede.
void Superposicion_SetBitacora(const std::wstring& texto)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_linea_bitacora = texto;
    AplicarBitacoraLegacyAlEstadoVisual_NoLock(texto);
    LeaveCriticalSection(&g_cs);

    SolicitarAplicarLayout();
    SolicitarInvalidar();
}

// CID-12-59 : Actualiza el texto mostrado como último asentado en el pie del panel.
void Superposicion_SetUltimoAsentado(const std::wstring& texto)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_linea_asentado = texto;
    LeaveCriticalSection(&g_cs);

    SolicitarInvalidar();
}

// CID-12-60 : Sustituye el estado visual completo por uno autoritativo proveniente de la bitácora moderna.
void Superposicion_SetEstadoVisual(const EstadoVisualBitacoraCID& estado)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_estado_visual = estado;
    g_modo_visual_autoritativo = true;
    LimitarLineasCerradasUI_NoLock();
    LeaveCriticalSection(&g_cs);

    SolicitarAplicarLayout();
    SolicitarInvalidar();
}

// CID-12-61 : Activa temporalmente el efecto visual de error de acorde.
void Superposicion_NotificarErrorAcorde()
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_error_hasta_tick = GetTickCount64() + ERROR_MS;
    LeaveCriticalSection(&g_cs);

    SolicitarInvalidar();
}

// CID-12-62 : Establece la visibilidad deseada del panel y solicita recalcular layout.
void Superposicion_SetVisible(bool visible)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_visible_deseado = visible;
    LeaveCriticalSection(&g_cs);

    SolicitarAplicarLayout();
    SolicitarInvalidar();
}

// CID-12-63 : Actualiza el rectángulo de anclaje usado para posicionar el panel cerca del caret o control activo.
void Superposicion_SetRectAnclaje(const RECT& rc)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);

    if (RectValido(rc))
    {
        g_tiene_rect_anclaje = true;
        g_rect_anclaje = rc;
    }
    else
    {
        g_tiene_rect_anclaje = false;
        g_rect_anclaje = RECT{ 0,0,0,0 };
    }

    LeaveCriticalSection(&g_cs);

    SolicitarAplicarLayout();
    SolicitarInvalidar();
}

// CID-12-64 : Activa o desactiva el modo visual compacto QWERTY de la superposición.
void Superposicion_SetModoQwerty(bool activo)
{
    if (!g_cs_iniciado) return;

    EnterCriticalSection(&g_cs);
    g_modo_qwerty = activo;
    LeaveCriticalSection(&g_cs);

    SolicitarAplicarLayout();
    SolicitarInvalidar();
}