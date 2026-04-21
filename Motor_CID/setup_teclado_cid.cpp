// CID-16-01 : Inclusión de la implementación del asistente de configuración del teclado CID.
#include "setup_teclado_cid.h"

// CID-16-02 : Inclusión de módulos de calibración, mapa CID y layout visual del teclado.
#include "calibracion_teclado.h"
#include "mapa_teclas_cid.h"
#include "layout_teclado_visual.h"

// CID-16-03 : Inclusión de cabeceras del sistema, utilidades de interfaz y contenedores estándar.
#include <windowsx.h>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cwctype>

// CID-16-04 : Espacio interno anónimo para encapsular estado y helpers privados del asistente de setup.
namespace
{
    // CID-16-05 : Nombre de la clase de ventana registrada por el asistente de configuración.
    static const wchar_t* kClaseVentanaSetup = L"CID_Setup_Teclado_V6";

    // CID-16-06 : Paleta base de colores usada por el asistente visual de configuración.
    static const COLORREF COLOR_BG = RGB(248, 248, 245);
    static const COLORREF COLOR_TEXT = RGB(28, 28, 28);
    static const COLORREF COLOR_TEXT_SOFT = RGB(90, 90, 90);
    static const COLORREF COLOR_STATUS_INFO = RGB(95, 105, 120);
    static const COLORREF COLOR_STATUS_ERR = RGB(170, 70, 70);
    static const COLORREF COLOR_CARD = RGB(255, 255, 255);
    static const COLORREF COLOR_CARD_BORDER = RGB(225, 225, 220);
    static const COLORREF COLOR_SHADOW = RGB(220, 220, 215);

    // CID-16-07 : Estado global del asistente con ventana, layout, pasos, captura y UI interactiva.
    struct SetupState
    {
        HINSTANCE hInstance = nullptr;
        HWND hwnd = nullptr;

        std::wstring rutaCalibrationJson;
        std::wstring rutaLayoutJson;
        std::wstring errorFinal;

        LayoutTecladoVisual layout;
        bool layoutCargado = false;

        std::vector<std::wstring> pasos;
        size_t indiceActual = 0;

        bool terminado = false;
        bool cancelado = false;
        bool guardadoOk = false;
        bool modoPruebaFinal = false;

        std::wstring mensajeEstado;

        DWORD ultimoScanCode = 0;
        std::vector<DWORD> scanCodesAbajo;

        std::wstring modoReasignacionIdCid;

        RECT botonReiniciar = { 0, 0, 0, 0 };
        bool hoverBotonReiniciar = false;
        bool trackingMouseLeave = false;
    };

    // CID-16-08 : Instancia global única del estado del asistente de setup.
    SetupState g_setup;

    // CID-16-09 : Envía mensajes de depuración del asistente al visor de salida de Windows.
    void Log(const std::wstring& s)
    {
        OutputDebugStringW((s + L"\n").c_str());
    }

    // CID-16-10 : Obtiene el directorio del ejecutable actual para resolver rutas auxiliares del setup.
    std::wstring DirectorioExe()
    {
        wchar_t exePath[MAX_PATH]{};
        GetModuleFileNameW(nullptr, exePath, MAX_PATH);

        std::wstring p = exePath;
        size_t pos = p.find_last_of(L"\\/");
        if (pos != std::wstring::npos) p = p.substr(0, pos);
        return p;
    }

    // CID-16-11 : Une dos segmentos de ruta garantizando un separador válido entre ambos.
    std::wstring Unir(const std::wstring& a, const std::wstring& b)
    {
        if (a.empty()) return b;
        if (a.back() == L'\\' || a.back() == L'/') return a + b;
        return a + L"\\" + b;
    }

    bool ExisteArchivo(const std::wstring& ruta)
    {
        DWORD attr = GetFileAttributesW(ruta.c_str());
        return (attr != INVALID_FILE_ATTRIBUTES) && !(attr & FILE_ATTRIBUTE_DIRECTORY);
    }

    std::wstring ResolverRutaLayoutJsonSetup()
    {
        const std::wstring exeDir = DirectorioExe();
        const std::wstring rutaRaiz = Unir(exeDir, L"keyboard-layout.json");
        if (ExisteArchivo(rutaRaiz))
            return rutaRaiz;

        const std::wstring rutaResources = Unir(exeDir, L"Resources\\keyboard-layout.json");
        if (ExisteArchivo(rutaResources))
            return rutaResources;

        return rutaRaiz;
    }

    // CID-16-12 : Recorta espacios en blanco al inicio y final de una cadena ancha.
    std::wstring Trim(const std::wstring& s)
    {
        size_t a = 0;
        while (a < s.size() && iswspace(s[a])) ++a;

        size_t b = s.size();
        while (b > a && iswspace(s[b - 1])) --b;

        return s.substr(a, b - a);
    }

    // CID-16-13 : Convierte una cadena completa a mayúsculas de forma simple para comparaciones visuales.
    std::wstring ToUpperSimple(const std::wstring& s)
    {
        std::wstring out = s;
        for (size_t i = 0; i < out.size(); ++i)
            out[i] = (wchar_t)towupper(out[i]);
        return out;
    }

    // CID-16-14 : Divide un texto multilinea en líneas individuales separadas por salto de línea.
    std::vector<std::wstring> SplitLines(const std::wstring& s)
    {
        std::vector<std::wstring> out;
        std::wstring cur;

        for (size_t i = 0; i < s.size(); ++i)
        {
            wchar_t c = s[i];
            if (c == L'\n')
            {
                out.push_back(cur);
                cur.clear();
            }
            else
            {
                cur += c;
            }
        }

        out.push_back(cur);
        return out;
    }

    // CID-16-15 : Extrae la pista secundaria visible de una tecla a partir de su texto original de layout.
    std::wstring HintTeclaDesdeTextoOriginal(const TeclaVisualCID& t)
    {
        std::vector<std::wstring> lines = SplitLines(t.textoOriginal);
        std::vector<std::wstring> utiles;

        for (size_t i = 0; i < lines.size(); ++i)
        {
            std::wstring q = Trim(lines[i]);
            if (!q.empty())
                utiles.push_back(q);
        }

        if (utiles.empty())
            return L"";

        for (size_t i = 0; i < utiles.size(); ++i)
        {
            std::wstring u = ToUpperSimple(utiles[i]);

            if (u == ToUpperSimple(t.idCid))
                continue;
            if (u == L"CID KEY" || u == L"TECLA CID" || u == L"AUX CID" || u == L"AUX_CID")
                continue;
            if (u == L"MOD." || u == L"MOD")
                continue;

            return utiles[i];
        }

        return L"";
    }

    // CID-16-16 : Obtiene el texto principal mostrado dentro de una tecla visual del asistente.
    std::wstring PrincipalTecla(const TeclaVisualCID& t)
    {
        if (!t.idCid.empty())
        {
            if (t.idCid == L"CID_KEY") return L"CID KEY";
            if (t.idCid == L"AUX_CID") return L"AUX CID";
            return t.idCid;
        }

        return t.textoVisible;
    }

    // CID-16-17 : Devuelve el nombre CID del paso actual de calibración si todavía existe.
    std::wstring NombrePasoActual()
    {
        if (g_setup.indiceActual >= g_setup.pasos.size())
            return L"";
        return g_setup.pasos[g_setup.indiceActual];
    }

    // CID-16-18 : Comprueba si un scanCode figura actualmente como pulsado dentro del asistente.
    bool EstaScanCodeAbajo(DWORD sc)
    {
        for (size_t i = 0; i < g_setup.scanCodesAbajo.size(); ++i)
        {
            if (g_setup.scanCodesAbajo[i] == sc)
                return true;
        }
        return false;
    }

    // CID-16-19 : Marca un scanCode como pulsado dentro del estado visual del asistente.
    void MarcarScanCodeAbajo(DWORD sc)
    {
        if (sc == 0 || sc >= 256) return;
        if (!EstaScanCodeAbajo(sc))
            g_setup.scanCodesAbajo.push_back(sc);
    }

    // CID-16-20 : Elimina un scanCode del conjunto de teclas actualmente pulsadas.
    void MarcarScanCodeArriba(DWORD sc)
    {
        for (size_t i = 0; i < g_setup.scanCodesAbajo.size(); ++i)
        {
            if (g_setup.scanCodesAbajo[i] == sc)
            {
                g_setup.scanCodesAbajo.erase(g_setup.scanCodesAbajo.begin() + (ptrdiff_t)i);
                return;
            }
        }
    }

    // CID-16-21 : Devuelve el título principal del asistente según su fase actual.
    std::wstring TextoTitulo()
    {
        if (g_setup.modoPruebaFinal)
            return L"Tu teclado CID ya está configurado";

        return L"Vamos a configurar tu teclado CID";
    }

    // CID-16-22 : Devuelve el texto principal explicativo según paso, reasignación o estado final.
    std::wstring TextoPrincipal()
    {
        if (g_setup.modoPruebaFinal)
        {
            if (!g_setup.modoReasignacionIdCid.empty())
                return L"Pulsa la nueva tecla para " + g_setup.modoReasignacionIdCid;

            return L"Pruébalo y corrige cualquier tecla si hace falta";
        }

        if (g_setup.terminado)
        {
            if (g_setup.guardadoOk)
                return L"Calibración completada";
            if (g_setup.cancelado)
                return L"Calibración cancelada";
            return L"Calibración terminada con error";
        }

        if (!g_setup.modoReasignacionIdCid.empty())
            return L"Pulsa la nueva tecla para " + g_setup.modoReasignacionIdCid;

        std::wstring nombre = NombrePasoActual();
        if (nombre.empty())
            return L"Sin pasos pendientes";

        return L"Pulsa la tecla que usarás como " + nombre;
    }

    // CID-16-23 : Devuelve el texto secundario de ayuda y controles rápidos del asistente.
    std::wstring TextoSecundario()
    {
        if (g_setup.modoPruebaFinal)
            return L"Pulsa teclas para comprobar el mapa · Haz clic en una tecla para reasignarla · Enter o Esc para cerrar";

        if (g_setup.terminado)
        {
            if (g_setup.guardadoOk)
                return L"Pulsa Enter o Esc para cerrar";
            return L"Pulsa Esc para cerrar";
        }

        std::wstring s;
        s += L"Paso ";
        s += std::to_wstring(g_setup.indiceActual + 1);
        s += L" de ";
        s += std::to_wstring(g_setup.pasos.size());
        s += L" · Haz clic en una tecla para reasignarla · Retroceso vuelve atrás · Esc cancela";
        return s;
    }

    // CID-16-24 : Devuelve el texto inferior de estado o error mostrado en la franja final de la ventana.
    std::wstring TextoEstadoInferior()
    {
        if (!g_setup.errorFinal.empty())
            return L"Error: " + g_setup.errorFinal;

        if (!g_setup.mensajeEstado.empty())
            return g_setup.mensajeEstado;

        if (g_setup.modoPruebaFinal)
            return L"Todo listo. Puedes probar y corregir antes de salir.";

        return L"";
    }

    // CID-16-25 : Invalida la ventana del asistente para forzar redibujado.
    void RefrescarVentana()
    {
        if (g_setup.hwnd)
            InvalidateRect(g_setup.hwnd, nullptr, TRUE);
    }

    // CID-16-26 : Comprueba si un scanCode ya estaba asignado a otra tecla CID distinta del objetivo actual.
    bool YaEstaScanCodeUsadoPorOtroPaso(DWORD scanCode, const std::wstring& nombreActual, std::wstring& nombreExistente)
    {
        std::vector<std::pair<std::wstring, DWORD> > asignaciones = ObtenerAsignacionesCalibradas();

        for (size_t i = 0; i < asignaciones.size(); ++i)
        {
            if (asignaciones[i].first != nombreActual && asignaciones[i].second == scanCode)
            {
                nombreExistente = asignaciones[i].first;
                return true;
            }
        }

        nombreExistente.clear();
        return false;
    }

    // CID-16-27 : Retrocede un paso o cancela una reasignación según el contexto actual del asistente.
    void RetrocederPaso()
    {
        if (g_setup.modoPruebaFinal)
        {
            g_setup.modoReasignacionIdCid.clear();
            g_setup.mensajeEstado = L"Reasignación cancelada.";
            RefrescarVentana();
            return;
        }

        if (g_setup.terminado)
            return;

        if (!g_setup.modoReasignacionIdCid.empty())
        {
            g_setup.modoReasignacionIdCid.clear();
            g_setup.mensajeEstado = L"Reasignación cancelada.";
            RefrescarVentana();
            return;
        }

        if (g_setup.indiceActual == 0)
        {
            g_setup.mensajeEstado = L"Ya estás en el primer paso.";
            RefrescarVentana();
            return;
        }

        if (g_setup.indiceActual < g_setup.pasos.size())
        {
            std::wstring pasoActual = g_setup.pasos[g_setup.indiceActual];
            QuitarAsignacionTeclaCID(pasoActual.c_str());
        }

        g_setup.indiceActual--;

        if (g_setup.indiceActual < g_setup.pasos.size())
        {
            std::wstring pasoPrevio = g_setup.pasos[g_setup.indiceActual];
            QuitarAsignacionTeclaCID(pasoPrevio.c_str());
        }

        g_setup.mensajeEstado = L"Has retrocedido al paso anterior.";
        RefrescarVentana();
    }

    // CID-16-28 : Guarda en disco la calibración actual y actualiza el estado final del asistente.
    bool GuardarCalibracionActual()
    {
        std::wstring err;
        if (!GuardarCalibracionTeclado(g_setup.rutaCalibrationJson, &err))
        {
            g_setup.guardadoOk = false;
            g_setup.errorFinal = err;
            g_setup.mensajeEstado = L"Error al guardar: " + err;
            RefrescarVentana();
            return false;
        }

        g_setup.guardadoOk = true;
        return true;
    }

    // CID-16-29 : Reinicia el asistente por completo borrando calibración, pasos y estado de prueba final.
    void ReiniciarCalibracionDesdeCero()
    {
        LimpiarCalibracionTeclado();

        g_setup.indiceActual = 0;
        g_setup.terminado = false;
        g_setup.cancelado = false;
        g_setup.guardadoOk = false;
        g_setup.modoPruebaFinal = false;

        g_setup.errorFinal.clear();
        g_setup.mensajeEstado = L"Calibración reiniciada. Empezamos otra vez.";
        g_setup.ultimoScanCode = 0;
        g_setup.scanCodesAbajo.clear();
        g_setup.modoReasignacionIdCid.clear();
        g_setup.hoverBotonReiniciar = false;

        RefrescarVentana();
    }

    // CID-16-30 : Entra en la fase final de prueba del teclado tras guardar correctamente la calibración.
    void EntrarModoPruebaFinal()
    {
        g_setup.modoPruebaFinal = true;
        g_setup.terminado = true;
        g_setup.modoReasignacionIdCid.clear();
        g_setup.mensajeEstado = L"Calibración guardada. Prueba el teclado o haz clic para reasignar.";
        RefrescarVentana();
    }

    // CID-16-31 : Cierra el flujo de pasos pendientes guardando la calibración y entrando en modo prueba.
    void FinalizarYGuardar()
    {
        if (GuardarCalibracionActual())
            EntrarModoPruebaFinal();
    }

    // CID-16-32 : Avanza automáticamente mientras los pasos secuenciales ya estén cubiertos por asignaciones válidas.
    void AvanzarSiPasoActualCompleto()
    {
        while (g_setup.indiceActual < g_setup.pasos.size())
        {
            DWORD dummy = 0;
            if (!ObtenerScanCodeDeNombreCID(g_setup.pasos[g_setup.indiceActual].c_str(), dummy))
                break;
            g_setup.indiceActual++;
        }

        if (g_setup.indiceActual >= g_setup.pasos.size())
            FinalizarYGuardar();
    }

    // CID-16-33 : Acepta un scanCode para una tecla objetivo concreta y actualiza progreso o reasignación.
    void AceptarScanCodeParaId(const std::wstring& nombreObjetivo, DWORD scanCode, bool avanzarEnSecuencia)
    {
        if (!g_setup.modoPruebaFinal && g_setup.terminado)
            return;

        if (scanCode == 0 || scanCode >= 256)
        {
            g_setup.mensajeEstado = L"ScanCode inválido.";
            RefrescarVentana();
            return;
        }

        g_setup.ultimoScanCode = scanCode;

        std::wstring nombreExistente;
        if (YaEstaScanCodeUsadoPorOtroPaso(scanCode, nombreObjetivo, nombreExistente))
        {
            g_setup.mensajeEstado =
                L"Esta tecla ya estaba asignada a " + nombreExistente +
                L". Se reasignará a " + nombreObjetivo + L".";
        }
        else
        {
            g_setup.mensajeEstado =
                L"Asignado " + nombreObjetivo + L" a scanCode " + std::to_wstring(scanCode) + L".";
        }

        if (!EstablecerAsignacionTeclaCID(nombreObjetivo.c_str(), scanCode))
        {
            g_setup.mensajeEstado = L"No se pudo asignar la tecla actual.";
            RefrescarVentana();
            return;
        }

        if (g_setup.modoPruebaFinal)
        {
            GuardarCalibracionActual();
        }
        else if (avanzarEnSecuencia)
        {
            AvanzarSiPasoActualCompleto();
        }

        g_setup.modoReasignacionIdCid.clear();
        RefrescarVentana();
    }

    // CID-16-34 : Acepta un scanCode detectado y lo enruta según paso normal, prueba final o reasignación manual.
    void AceptarScanCode(DWORD scanCode)
    {
        if (!g_setup.modoPruebaFinal && g_setup.terminado)
            return;

        if (!g_setup.modoReasignacionIdCid.empty())
        {
            AceptarScanCodeParaId(g_setup.modoReasignacionIdCid, scanCode, false);
            return;
        }

        if (g_setup.modoPruebaFinal)
        {
            g_setup.mensajeEstado = L"ScanCode detectado: " + std::to_wstring(scanCode) + L". Haz clic en una tecla para reasignarla.";
            g_setup.ultimoScanCode = scanCode;
            RefrescarVentana();
            return;
        }

        std::wstring nombrePaso = NombrePasoActual();
        if (nombrePaso.empty())
            return;

        AceptarScanCodeParaId(nombrePaso, scanCode, true);
    }

    // CID-16-35 : Calcula el rectángulo de la tarjeta de cabecera del asistente.
    RECT CalcularAreaCabecera(const RECT& rcCliente)
    {
        RECT r = rcCliente;
        r.left += 28;
        r.top += 22;
        r.right -= 28;
        r.bottom = 188;
        return r;
    }

    // CID-16-36 : Calcula el área disponible para dibujar el teclado visual dentro del asistente.
    RECT CalcularAreaTeclado(const RECT& rcCliente)
    {
        RECT r = rcCliente;
        r.left += 28;
        r.top = 212;
        r.right -= 28;
        r.bottom -= 74;
        return r;
    }

    // CID-16-37 : Calcula la franja inferior donde se dibuja el estado textual del asistente.
    RECT CalcularAreaEstadoInferior(const RECT& rcCliente)
    {
        RECT r = rcCliente;
        r.left += 28;
        r.right -= 28;
        r.bottom -= 18;
        r.top = r.bottom - 34;
        return r;
    }

    // CID-16-38 : Calcula el rectángulo del botón de reinicio disponible en modo prueba final.
    RECT CalcularRectBotonReiniciar(const RECT& rcCliente)
    {
        RECT r{};
        r.right = rcCliente.right - 28;
        r.left = r.right - 220;
        r.top = rcCliente.bottom - 58;
        r.bottom = r.top + 36;
        return r;
    }

    // CID-16-39 : Comprueba si un punto de ratón cae dentro de un rectángulo dado.
    bool PuntoEnRect(int x, int y, const RECT& r)
    {
        return x >= r.left && x < r.right && y >= r.top && y < r.bottom;
    }

    // CID-16-40 : Calcula la métrica real del teclado dibujado según el layout y el área disponible.
    void CalcularMetricaTeclado(const RECT& rcArea, int& origenX, int& origenY, int& unidadW, int& unidadH)
    {
        origenX = rcArea.left;
        origenY = rcArea.top;
        unidadW = 42;
        unidadH = 42;

        if (g_setup.layout.anchoTotal > 0.01 && g_setup.layout.altoTotal > 0.01)
        {
            int maxW = rcArea.right - rcArea.left;
            int maxH = rcArea.bottom - rcArea.top;

            int uw = (int)(maxW / g_setup.layout.anchoTotal);
            int uh = (int)(maxH / g_setup.layout.altoTotal);

            int unidad = max(18, min(uw, uh));
            unidad = (int)(unidad * 0.86);

            unidadW = unidad;
            unidadH = unidad;

            int keyboardW = (int)(g_setup.layout.anchoTotal * unidadW);
            int keyboardH = (int)(g_setup.layout.altoTotal * unidadH);

            origenX = rcArea.left + max(0, (maxW - keyboardW) / 2);
            origenY = rcArea.top + max(0, (maxH - keyboardH) / 2);
        }
    }

    // CID-16-41 : Aclara un color base sumando luminosidad a sus tres canales.
    COLORREF AclararColor(COLORREF c, int extra)
    {
        int r = min(255, (int)GetRValue(c) + extra);
        int g = min(255, (int)GetGValue(c) + extra);
        int b = min(255, (int)GetBValue(c) + extra);
        return RGB(r, g, b);
    }

    // CID-16-42 : Oscurece un color base restando intensidad a sus tres canales.
    COLORREF OscurecerColor(COLORREF c, int delta)
    {
        int r = max(0, (int)GetRValue(c) - delta);
        int g = max(0, (int)GetGValue(c) - delta);
        int b = max(0, (int)GetBValue(c) - delta);
        return RGB(r, g, b);
    }

    // CID-16-43 : Rellena un rectángulo redondeado con un color sólido.
    void RellenarRoundRect(HDC hdc, const RECT& r, COLORREF color, int radio)
    {
        HBRUSH b = CreateSolidBrush(color);
        HGDIOBJ oldBrush = SelectObject(hdc, b);
        HGDIOBJ oldPen = SelectObject(hdc, GetStockObject(NULL_PEN));
        RoundRect(hdc, r.left, r.top, r.right, r.bottom, radio, radio);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(b);
    }

    // CID-16-44 : Dibuja el borde de un rectángulo redondeado con grosor y color configurables.
    void BordeRoundRect(HDC hdc, const RECT& r, COLORREF color, int grosor, int radio)
    {
        HPEN pen = CreatePen(PS_SOLID, grosor, color);
        HGDIOBJ oldPen = SelectObject(hdc, pen);
        HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        RoundRect(hdc, r.left, r.top, r.right, r.bottom, radio, radio);
        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }

    // CID-16-45 : Dibuja la tarjeta visual de cabecera con sombra, fondo y borde suave.
    void PintarTarjetaCabecera(HDC hdc, const RECT& r)
    {
        RECT sombra = r;
        OffsetRect(&sombra, 0, 3);
        RellenarRoundRect(hdc, sombra, COLOR_SHADOW, 18);
        RellenarRoundRect(hdc, r, COLOR_CARD, 18);
        BordeRoundRect(hdc, r, COLOR_CARD_BORDER, 1, 18);
    }

    // CID-16-46 : Dibuja título, texto principal y texto secundario de la cabecera del asistente.
    void PintarTextoCabecera(HDC hdc, const RECT& rcCliente)
    {
        RECT card = CalcularAreaCabecera(rcCliente);
        PintarTarjetaCabecera(hdc, card);

        HFONT hFontTitulo = CreateFontW(
            33, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

        HFONT hFontMain = CreateFontW(
            20, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

        HFONT hFontBody = CreateFontW(
            15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

        HFONT oldFont = nullptr;

        RECT rcTitulo = card;
        rcTitulo.left += 24;
        rcTitulo.top += 18;
        rcTitulo.right -= 24;
        rcTitulo.bottom = rcTitulo.top + 40;

        oldFont = (HFONT)SelectObject(hdc, hFontTitulo);
        SetTextColor(hdc, COLOR_TEXT);
        SetBkMode(hdc, TRANSPARENT);
        std::wstring titulo = TextoTitulo();
        DrawTextW(hdc, titulo.c_str(), -1, &rcTitulo, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);

        RECT rcMain = card;
        rcMain.left += 24;
        rcMain.top = 86;
        rcMain.right -= 24;
        rcMain.bottom = rcMain.top + 30;

        SelectObject(hdc, hFontMain);
        SetTextColor(hdc, COLOR_TEXT);
        std::wstring principal = TextoPrincipal();
        DrawTextW(hdc, principal.c_str(), -1, &rcMain, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);

        RECT rcBody = card;
        rcBody.left += 24;
        rcBody.top = 126;
        rcBody.right -= 24;
        rcBody.bottom -= 18;

        SelectObject(hdc, hFontBody);
        SetTextColor(hdc, COLOR_TEXT_SOFT);
        std::wstring secundario = TextoSecundario();
        DrawTextW(hdc, secundario.c_str(), -1, &rcBody, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX);

        SelectObject(hdc, oldFont);
        DeleteObject(hFontTitulo);
        DeleteObject(hFontMain);
        DeleteObject(hFontBody);
    }

    // CID-16-47 : Dibuja una tecla individual del teclado visual con estados de objetivo, asignación y pulsación.
    void PintarTecla(HDC hdc, const TeclaVisualCID& t, const RECT& r)
    {
        std::wstring pasoActual = NombrePasoActual();

        bool esObjetivoActual =
            !g_setup.modoPruebaFinal &&
            !g_setup.terminado &&
            g_setup.modoReasignacionIdCid.empty() &&
            !pasoActual.empty() &&
            t.idCid == pasoActual;

        bool esObjetivoReasignacion =
            !g_setup.modoReasignacionIdCid.empty() &&
            t.idCid == g_setup.modoReasignacionIdCid;

        DWORD scanAsignado = 0;
        bool estaAsignada = !t.idCid.empty() && ObtenerScanCodeDeNombreCID(t.idCid.c_str(), scanAsignado);

        bool esUltimaPulsada = estaAsignada && scanAsignado == g_setup.ultimoScanCode;
        bool estaAbajo = estaAsignada && EstaScanCodeAbajo(scanAsignado);

        COLORREF base = t.color;
        if (t.esGris)
            base = RGB(190, 190, 190);

        base = AclararColor(base, 12);

        if (estaAsignada)
            base = AclararColor(base, 8);

        if (esObjetivoActual)
            base = RGB(255, 222, 140);

        if (esObjetivoReasignacion)
            base = RGB(255, 178, 132);

        if (esUltimaPulsada)
            base = RGB(181, 239, 188);

        RECT rSombra = r;
        OffsetRect(&rSombra, 0, 4);

        RECT rBase = r;
        RECT rTop = r;

        int lift = estaAbajo ? 0 : 4;
        OffsetRect(&rTop, 0, -lift);

        RECT rInner = rTop;
        InflateRect(&rInner, -2, -2);

        COLORREF baseOscura = OscurecerColor(base, estaAbajo ? 52 : 28);
        COLORREF bordeInterior = OscurecerColor(base, 60);

        RellenarRoundRect(hdc, rSombra, RGB(222, 222, 218), 14);
        RellenarRoundRect(hdc, rBase, baseOscura, 14);
        RellenarRoundRect(hdc, rTop, base, 14);
        BordeRoundRect(hdc, rInner, bordeInterior, 3, 12);

        std::wstring hint = HintTeclaDesdeTextoOriginal(t);
        std::wstring principal = PrincipalTecla(t);

        SetBkMode(hdc, TRANSPARENT);

        HFONT hFontHint = CreateFontW(
            11, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

        HFONT hFontMain = CreateFontW(
            19, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI Semibold");

        HFONT oldFont = (HFONT)SelectObject(hdc, hFontHint);

        // CID-16-48 : Dibuja la pista pequeña superior de la tecla cuando existe texto auxiliar útil.
        if (!hint.empty())
        {
            RECT rHint = rTop;
            rHint.left += 7;
            rHint.top += 5;
            rHint.right -= 7;
            rHint.bottom = rHint.top + 14;

            SetTextColor(hdc, RGB(90, 90, 90));
            DrawTextW(hdc, hint.c_str(), -1, &rHint, DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
        }

        // CID-16-49 : Dibuja la etiqueta principal grande de la tecla en el centro visual.
        RECT rMain = rTop;
        rMain.left += 5;
        rMain.top += 10;
        rMain.right -= 5;
        rMain.bottom -= 2;

        SelectObject(hdc, hFontMain);
        SetTextColor(hdc, RGB(30, 30, 30));
        DrawTextW(hdc, principal.c_str(), -1, &rMain, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);

        SelectObject(hdc, oldFont);
        DeleteObject(hFontHint);
        DeleteObject(hFontMain);
    }

    // CID-16-50 : Dibuja el teclado completo a partir del layout visual cargado.
    void PintarTeclado(HDC hdc, const RECT& rcCliente)
    {
        if (!g_setup.layoutCargado)
            return;

        RECT area = CalcularAreaTeclado(rcCliente);

        int origenX = 0, origenY = 0, unidadW = 42, unidadH = 42;
        CalcularMetricaTeclado(area, origenX, origenY, unidadW, unidadH);

        for (size_t i = 0; i < g_setup.layout.teclas.size(); ++i)
        {
            const TeclaVisualCID& t = g_setup.layout.teclas[i];
            if (!t.renderizable)
                continue;

            RECT r = RectTeclaVisualAPixeles(t, origenX, origenY, unidadW, unidadH);
            PintarTecla(hdc, t, r);
        }
    }

    // CID-16-51 : Dibuja la línea de estado inferior con color normal o de error según el contexto.
    void PintarEstadoInferior(HDC hdc, const RECT& rcCliente)
    {
        std::wstring estado = TextoEstadoInferior();
        if (estado.empty())
            return;

        RECT r = CalcularAreaEstadoInferior(rcCliente);

        HFONT hFont = CreateFontW(
            15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
        HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, g_setup.errorFinal.empty() ? COLOR_STATUS_INFO : COLOR_STATUS_ERR);
        DrawTextW(hdc, estado.c_str(), -1, &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS);

        SelectObject(hdc, oldFont);
        DeleteObject(hFont);
    }

    // CID-16-52 : Dibuja el botón de reinicio solo durante el modo final de prueba y corrección.
    void PintarBotonReiniciar(HDC hdc, const RECT& rcCliente)
    {
        if (!g_setup.modoPruebaFinal)
            return;

        RECT r = CalcularRectBotonReiniciar(rcCliente);
        g_setup.botonReiniciar = r;

        COLORREF fondo = g_setup.hoverBotonReiniciar ? RGB(235, 235, 232) : RGB(244, 244, 241);
        COLORREF borde = RGB(205, 205, 200);
        COLORREF texto = RGB(55, 55, 55);

        RECT sombra = r;
        OffsetRect(&sombra, 0, 2);
        RellenarRoundRect(hdc, sombra, RGB(225, 225, 220), 12);
        RellenarRoundRect(hdc, r, fondo, 12);
        BordeRoundRect(hdc, r, borde, 1, 12);

        HFONT hFont = CreateFontW(
            15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
        HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, texto);

        RECT rt = r;
        DrawTextW(hdc, L"Reiniciar calibración", -1, &rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);

        SelectObject(hdc, oldFont);
        DeleteObject(hFont);
    }

    // CID-16-53 : Activa el modo de reasignación manual al hacer clic sobre una tecla visual válida.
    void ActivarModoReasignacionPorClick(int mouseX, int mouseY, const RECT& rcCliente)
    {
        if ((!g_setup.modoPruebaFinal && g_setup.terminado) || !g_setup.layoutCargado)
            return;

        RECT area = CalcularAreaTeclado(rcCliente);

        int origenX = 0, origenY = 0, unidadW = 42, unidadH = 42;
        CalcularMetricaTeclado(area, origenX, origenY, unidadW, unidadH);

        int idx = BuscarTeclaVisualEnPunto(g_setup.layout, mouseX, mouseY, origenX, origenY, unidadW, unidadH);
        if (idx < 0)
            return;

        const TeclaVisualCID& t = g_setup.layout.teclas[(size_t)idx];
        if (t.idCid.empty() || t.idCid == L"CID_KEY")
            return;

        g_setup.modoReasignacionIdCid = t.idCid;
        g_setup.mensajeEstado = L"Reasignación manual: pulsa ahora la nueva tecla para " + t.idCid + L".";
        RefrescarVentana();
    }

    // CID-16-54 : Inicia el seguimiento de salida del ratón para gestionar el hover del botón inferior.
    void IniciarTrackMouseLeave(HWND hwnd)
    {
        if (g_setup.trackingMouseLeave)
            return;

        TRACKMOUSEEVENT tme{};
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;

        if (TrackMouseEvent(&tme))
            g_setup.trackingMouseLeave = true;
    }

    // CID-16-55 : Procedimiento de ventana del asistente que gestiona ratón, teclado, pintura y cierre.
    LRESULT CALLBACK SetupWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_CREATE:
            return 0;

            // CID-16-56 : Gestiona hover del botón de reinicio durante el modo de prueba final.
        case WM_MOUSEMOVE:
        {
            IniciarTrackMouseLeave(hwnd);

            if (g_setup.modoPruebaFinal)
            {
                int x = GET_X_LPARAM(lParam);
                int y = GET_Y_LPARAM(lParam);

                RECT rc;
                GetClientRect(hwnd, &rc);
                RECT rb = CalcularRectBotonReiniciar(rc);

                bool hover = PuntoEnRect(x, y, rb);
                if (hover != g_setup.hoverBotonReiniciar)
                {
                    g_setup.hoverBotonReiniciar = hover;
                    RefrescarVentana();
                }
            }
            return 0;
        }

        // CID-16-57 : Limpia el estado hover cuando el ratón abandona la ventana del asistente.
        case WM_MOUSELEAVE:
        {
            g_setup.trackingMouseLeave = false;
            if (g_setup.hoverBotonReiniciar)
            {
                g_setup.hoverBotonReiniciar = false;
                RefrescarVentana();
            }
            return 0;
        }

        // CID-16-58 : Gestiona clics sobre el botón de reinicio o sobre teclas para reasignación manual.
        case WM_LBUTTONDOWN:
        {
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);

            RECT rc;
            GetClientRect(hwnd, &rc);

            if (g_setup.modoPruebaFinal)
            {
                RECT rb = CalcularRectBotonReiniciar(rc);
                if (PuntoEnRect(x, y, rb))
                {
                    ReiniciarCalibracionDesdeCero();
                    return 0;
                }
            }

            ActivarModoReasignacionPorClick(x, y, rc);
            return 0;
        }

        // CID-16-59 : Procesa pulsaciones del asistente para captura de scanCodes, navegación y cierre.
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            DWORD scanCode = (DWORD)((lParam >> 16) & 0xFF);

            if (wParam != VK_SPACE)
            {
                MarcarScanCodeAbajo(scanCode);
                g_setup.ultimoScanCode = scanCode;
                RefrescarVentana();
            }

            // CID-16-60 : En modo prueba final captura teclas para comprobación o cierra con Enter y Esc.
            if (g_setup.modoPruebaFinal)
            {
                if (wParam == VK_RETURN || wParam == VK_ESCAPE)
                {
                    DestroyWindow(hwnd);
                    return 0;
                }

                if (wParam != VK_SPACE)
                {
                    AceptarScanCode(scanCode);
                    return 0;
                }

                return 0;
            }

            // CID-16-61 : Si el asistente ya terminó, solo permite cerrar con Enter o Esc.
            if (g_setup.terminado)
            {
                if (wParam == VK_RETURN || wParam == VK_ESCAPE)
                {
                    DestroyWindow(hwnd);
                    return 0;
                }
                return 0;
            }

            // CID-16-62 : Cancela el asistente actual cuando el usuario pulsa Escape durante la calibración.
            if (wParam == VK_ESCAPE)
            {
                g_setup.cancelado = true;
                g_setup.terminado = true;
                g_setup.mensajeEstado = L"Calibración cancelada por el usuario.";
                RefrescarVentana();
                return 0;
            }

            // CID-16-63 : Retrocede un paso cuando el usuario pulsa Retroceso durante la calibración.
            if (wParam == VK_BACK)
            {
                RetrocederPaso();
                return 0;
            }

            return 0;
        }

        // CID-16-64 : Actualiza el estado visual de teclas pulsadas al soltarlas.
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            DWORD scanCode = (DWORD)((lParam >> 16) & 0xFF);
            MarcarScanCodeArriba(scanCode);
            RefrescarVentana();
            return 0;
        }

        // CID-16-65 : Fuerza redibujado si cambia el layout de entrada del sistema.
        case WM_INPUTLANGCHANGE:
            RefrescarVentana();
            return 0;

            // CID-16-66 : Dibuja el fondo, cabecera, teclado, estado inferior y botón de reinicio.
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            RECT rc;
            GetClientRect(hwnd, &rc);

            HBRUSH bg = CreateSolidBrush(COLOR_BG);
            FillRect(hdc, &rc, bg);
            DeleteObject(bg);

            SetBkMode(hdc, TRANSPARENT);

            PintarTextoCabecera(hdc, rc);
            PintarTeclado(hdc, rc);
            PintarEstadoInferior(hdc, rc);
            PintarBotonReiniciar(hdc, rc);

            EndPaint(hwnd, &ps);
            return 0;
        }

        // CID-16-67 : Cierra el bucle del asistente al destruir la ventana principal.
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    // CID-16-68 : Registra la clase de ventana del asistente de configuración si todavía no existe.
    bool RegistrarClaseVentana(HINSTANCE hInstance, std::wstring* error)
    {
        WNDCLASSEXW wc{};
        wc.cbSize = sizeof(wc);
        wc.lpfnWndProc = SetupWndProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = kClaseVentanaSetup;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.style = CS_HREDRAW | CS_VREDRAW;

        if (!RegisterClassExW(&wc))
        {
            DWORD e = GetLastError();
            if (e != ERROR_CLASS_ALREADY_EXISTS)
            {
                if (error) *error = L"No se pudo registrar la clase de ventana del asistente.";
                return false;
            }
        }

        return true;
    }
}

// CID-16-69 : Ejecuta el asistente completo de calibración del teclado CID hasta guardado o cancelación.
bool EjecutarSetupTecladoCID(HINSTANCE hInstance, const std::wstring& rutaCalibrationJson, std::wstring* error)
{
    g_setup = SetupState{};
    g_setup.hInstance = hInstance;
    g_setup.rutaCalibrationJson = rutaCalibrationJson;
    g_setup.rutaLayoutJson = ResolverRutaLayoutJsonSetup();

    LimpiarCalibracionTeclado();

    // CID-16-70 : Construye la secuencia ordenada de pasos de calibración para todas las teclas CID físicas.
    g_setup.pasos.push_back(L"I1");
    g_setup.pasos.push_back(L"I2");
    g_setup.pasos.push_back(L"I3");
    g_setup.pasos.push_back(L"I4");
    g_setup.pasos.push_back(L"I5");
    g_setup.pasos.push_back(L"I6");
    g_setup.pasos.push_back(L"I7");
    g_setup.pasos.push_back(L"I8");
    g_setup.pasos.push_back(L"I9");
    g_setup.pasos.push_back(L"I10");

    g_setup.pasos.push_back(L"C1");
    g_setup.pasos.push_back(L"C2");
    g_setup.pasos.push_back(L"C3");
    g_setup.pasos.push_back(L"C4");
    g_setup.pasos.push_back(L"C5");
    g_setup.pasos.push_back(L"C6");

    g_setup.pasos.push_back(L"D1");
    g_setup.pasos.push_back(L"D2");
    g_setup.pasos.push_back(L"D3");
    g_setup.pasos.push_back(L"D4");
    g_setup.pasos.push_back(L"D5");
    g_setup.pasos.push_back(L"D6");
    g_setup.pasos.push_back(L"D7");
    g_setup.pasos.push_back(L"D8");
    g_setup.pasos.push_back(L"D9");
    g_setup.pasos.push_back(L"D10");

    g_setup.pasos.push_back(L"AUX_CID");

    // CID-16-71 : Carga el layout visual externo usado para mostrar el teclado del asistente.
    {
        std::wstring errLayout;
        if (!CargarLayoutTecladoVisual(g_setup.rutaLayoutJson, g_setup.layout, &errLayout))
        {
            if (error) *error = L"No se pudo cargar keyboard-layout.json: " + errLayout;
            return false;
        }
        g_setup.layoutCargado = true;
    }

    // CID-16-72 : Registra la clase del asistente antes de crear la ventana principal.
    if (!RegistrarClaseVentana(hInstance, error))
        return false;

    // CID-16-73 : Crea la ventana principal del asistente de calibración del teclado.
    HWND hwnd = CreateWindowExW(
        0,
        kClaseVentanaSetup,
        L"Vamos a configurar tu teclado CID",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1040, 790,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hwnd)
    {
        if (error) *error = L"No se pudo crear la ventana del asistente de teclado CID.";
        return false;
    }

    g_setup.hwnd = hwnd;
    g_setup.mensajeEstado = L"Empezando calibración...";

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    // CID-16-74 : Mantiene el bucle modal del asistente y captura scanCodes antes del despacho normal.
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0)
    {
        if ((msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN) && msg.hwnd == hwnd)
        {
            DWORD scanCode = (DWORD)((msg.lParam >> 16) & 0xFF);

            if (msg.wParam != VK_SPACE)
            {
                if (!g_setup.modoPruebaFinal)
                {
                    AceptarScanCode(scanCode);
                    continue;
                }
            }
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    // CID-16-75 : Traduce el resultado final del asistente a éxito real o mensaje de error para el llamador.
    if (!g_setup.guardadoOk)
    {
        if (error)
        {
            if (!g_setup.errorFinal.empty()) *error = g_setup.errorFinal;
            else if (g_setup.cancelado) *error = L"El usuario canceló la calibración.";
            else *error = L"No se completó la calibración.";
        }
        return false;
    }

    return true;
}
