// CID-22-01 : Inclusión de la implementación del layout visual del teclado CID.
#include "layout_teclado_visual.h"

// CID-22-02 : Inclusión de cabeceras del sistema y utilidades estándar para parsing y contenedores.
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <cwctype>
#include <algorithm>

// CID-22-03 : Espacio interno anónimo para encapsular el parser JSON mínimo y helpers privados del layout.
namespace
{
    // CID-22-04 : Representa un valor JSON mínimo con soporte para null, bool, número, string, array y objeto.
    struct JsonValue
    {
        enum Type
        {
            TNull,
            TBool,
            TNumber,
            TString,
            TArray,
            TObject
        } type = TNull;

        bool b = false;
        double n = 0.0;
        std::wstring s;
        std::vector<JsonValue> a;
        std::map<std::wstring, JsonValue> o;
    };

    // CID-22-05 : Parser JSON mínimo usado para leer el archivo KLE del teclado visual.
    struct JsonParser
    {
        const std::wstring* text = nullptr;
        size_t pos = 0;
        std::wstring error;

        // CID-22-06 : Devuelve el carácter actual sin avanzar la posición del parser.
        wchar_t Peek() const
        {
            if (!text || pos >= text->size()) return 0;
            return (*text)[pos];
        }

        // CID-22-07 : Devuelve el carácter actual y avanza la posición del parser.
        wchar_t Get()
        {
            if (!text || pos >= text->size()) return 0;
            return (*text)[pos++];
        }

        // CID-22-08 : Salta espacios en blanco JSON entre tokens.
        void SkipWS()
        {
            while (true)
            {
                wchar_t c = Peek();
                if (c == 0) return;
                if (c == L' ' || c == L'\t' || c == L'\r' || c == L'\n')
                    ++pos;
                else
                    return;
            }
        }

        // CID-22-09 : Intenta consumir un literal JSON exacto desde la posición actual.
        bool MatchLiteral(const wchar_t* lit)
        {
            size_t i = 0;
            while (lit[i])
            {
                if (Peek() != lit[i]) return false;
                ++pos;
                ++i;
            }
            return true;
        }

        // CID-22-10 : Parsea una cadena JSON con escapes básicos y unicode simple.
        bool ParseString(std::wstring& out)
        {
            out.clear();

            if (Get() != L'"')
            {
                error = L"Se esperaba comilla inicial de string JSON.";
                return false;
            }

            while (true)
            {
                wchar_t c = Get();
                if (c == 0)
                {
                    error = L"String JSON sin cerrar.";
                    return false;
                }

                if (c == L'"')
                    return true;

                if (c == L'\\')
                {
                    wchar_t esc = Get();
                    if (esc == 0)
                    {
                        error = L"Escape JSON truncado.";
                        return false;
                    }

                    switch (esc)
                    {
                    case L'"': out += L'"'; break;
                    case L'\\': out += L'\\'; break;
                    case L'/': out += L'/'; break;
                    case L'b': out += L'\b'; break;
                    case L'f': out += L'\f'; break;
                    case L'n': out += L'\n'; break;
                    case L'r': out += L'\r'; break;
                    case L't': out += L'\t'; break;
                    case L'u':
                    {
                        wchar_t hexbuf[5] = {};
                        for (int i = 0; i < 4; ++i)
                        {
                            wchar_t h = Get();
                            if (h == 0)
                            {
                                error = L"Escape unicode JSON truncado.";
                                return false;
                            }
                            hexbuf[i] = h;
                        }

                        unsigned int code = 0;
                        if (swscanf_s(hexbuf, L"%x", &code) != 1)
                        {
                            error = L"Escape unicode JSON inválido.";
                            return false;
                        }

                        out += (wchar_t)code;
                        break;
                    }
                    default:
                        error = L"Escape JSON no soportado.";
                        return false;
                    }
                }
                else
                {
                    out += c;
                }
            }
        }

        // CID-22-11 : Parsea un número JSON simple con soporte para signo, decimales y exponente.
        bool ParseNumber(double& out)
        {
            size_t start = pos;

            if (Peek() == L'-') ++pos;

            bool sawDigit = false;
            while (iswdigit(Peek()))
            {
                sawDigit = true;
                ++pos;
            }

            if (Peek() == L'.')
            {
                ++pos;
                while (iswdigit(Peek()))
                {
                    sawDigit = true;
                    ++pos;
                }
            }

            if (Peek() == L'e' || Peek() == L'E')
            {
                ++pos;
                if (Peek() == L'+' || Peek() == L'-') ++pos;
                while (iswdigit(Peek()))
                {
                    sawDigit = true;
                    ++pos;
                }
            }

            if (!sawDigit)
            {
                error = L"Número JSON inválido.";
                return false;
            }

            std::wstring token = text->substr(start, pos - start);
            out = _wtof(token.c_str());
            return true;
        }

        // CID-22-12 : Parsea cualquier valor JSON delegando al subtipo correspondiente.
        bool ParseValue(JsonValue& out)
        {
            SkipWS();

            wchar_t c = Peek();
            if (c == 0)
            {
                error = L"Fin inesperado del JSON.";
                return false;
            }

            if (c == L'"')
            {
                out.type = JsonValue::TString;
                return ParseString(out.s);
            }

            if (c == L'{')
                return ParseObject(out);

            if (c == L'[')
                return ParseArray(out);

            if (c == L't')
            {
                if (!MatchLiteral(L"true"))
                {
                    error = L"Literal JSON inválido.";
                    return false;
                }
                out.type = JsonValue::TBool;
                out.b = true;
                return true;
            }

            if (c == L'f')
            {
                if (!MatchLiteral(L"false"))
                {
                    error = L"Literal JSON inválido.";
                    return false;
                }
                out.type = JsonValue::TBool;
                out.b = false;
                return true;
            }

            if (c == L'n')
            {
                if (!MatchLiteral(L"null"))
                {
                    error = L"Literal JSON inválido.";
                    return false;
                }
                out.type = JsonValue::TNull;
                return true;
            }

            if (c == L'-' || iswdigit(c))
            {
                out.type = JsonValue::TNumber;
                return ParseNumber(out.n);
            }

            error = L"Valor JSON no reconocido.";
            return false;
        }

        // CID-22-13 : Parsea un array JSON y acumula sus elementos en orden.
        bool ParseArray(JsonValue& out)
        {
            if (Get() != L'[')
            {
                error = L"Se esperaba '['.";
                return false;
            }

            out.type = JsonValue::TArray;
            out.a.clear();

            SkipWS();
            if (Peek() == L']')
            {
                Get();
                return true;
            }

            while (true)
            {
                JsonValue elem;
                if (!ParseValue(elem))
                    return false;

                out.a.push_back(elem);

                SkipWS();
                wchar_t c = Get();
                if (c == L']')
                    return true;

                if (c != L',')
                {
                    error = L"Se esperaba ',' o ']' en array JSON.";
                    return false;
                }
            }
        }

        // CID-22-14 : Parsea un objeto JSON y almacena sus pares clave-valor.
        bool ParseObject(JsonValue& out)
        {
            if (Get() != L'{')
            {
                error = L"Se esperaba '{'.";
                return false;
            }

            out.type = JsonValue::TObject;
            out.o.clear();

            SkipWS();
            if (Peek() == L'}')
            {
                Get();
                return true;
            }

            while (true)
            {
                SkipWS();

                std::wstring key;
                if (!ParseString(key))
                    return false;

                SkipWS();
                if (Get() != L':')
                {
                    error = L"Se esperaba ':' en objeto JSON.";
                    return false;
                }

                JsonValue value;
                if (!ParseValue(value))
                    return false;

                out.o[key] = value;

                SkipWS();
                wchar_t c = Get();
                if (c == L'}')
                    return true;

                if (c != L',')
                {
                    error = L"Se esperaba ',' o '}' en objeto JSON.";
                    return false;
                }
            }
        }
    };

    // CID-22-15 : Envía mensajes de depuración del módulo de layout visual al visor de salida.
    static void Log(const std::wstring& s)
    {
        OutputDebugStringW((s + L"\n").c_str());
    }

    // CID-22-16 : Convierte una cadena UTF-8 a Unicode para cargar archivos JSON.
    static std::wstring NarrowToWideUtf8(const std::string& s)
    {
        if (s.empty()) return L"";

        int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
        if (len <= 0) return L"";

        std::wstring out;
        out.resize((size_t)len);
        MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &out[0], len);
        return out;
    }

    // CID-22-17 : Lee un archivo de texto UTF-8 y elimina BOM si existe.
    static bool LeerArchivoTextoUtf8(const std::wstring& ruta, std::wstring& outTexto, std::wstring* error)
    {
        std::ifstream f(ruta.c_str(), std::ios::binary);
        if (!f)
        {
            if (error) *error = L"No se pudo abrir el archivo: " + ruta;
            return false;
        }

        std::string bytes((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        f.close();

        if (bytes.size() >= 3 &&
            (unsigned char)bytes[0] == 0xEF &&
            (unsigned char)bytes[1] == 0xBB &&
            (unsigned char)bytes[2] == 0xBF)
        {
            bytes.erase(0, 3);
        }

        outTexto = NarrowToWideUtf8(bytes);
        return true;
    }

    // CID-22-18 : Obtiene un número desde una clave de un objeto JSON.
    static bool JsonGetNumber(const JsonValue& obj, const wchar_t* key, double& out)
    {
        if (obj.type != JsonValue::TObject) return false;
        std::map<std::wstring, JsonValue>::const_iterator it = obj.o.find(key);
        if (it == obj.o.end()) return false;
        if (it->second.type != JsonValue::TNumber) return false;
        out = it->second.n;
        return true;
    }

    // CID-22-19 : Obtiene una cadena desde una clave de un objeto JSON.
    static bool JsonGetString(const JsonValue& obj, const wchar_t* key, std::wstring& out)
    {
        if (obj.type != JsonValue::TObject) return false;
        std::map<std::wstring, JsonValue>::const_iterator it = obj.o.find(key);
        if (it == obj.o.end()) return false;
        if (it->second.type != JsonValue::TString) return false;
        out = it->second.s;
        return true;
    }

    // CID-22-20 : Convierte un color hexadecimal tipo #RRGGBB a COLORREF.
    static COLORREF ParseHexColor(const std::wstring& s, bool& ok)
    {
        ok = false;
        if (s.empty()) return RGB(200, 200, 200);

        std::wstring hex = s;
        if (!hex.empty() && hex[0] == L'#')
            hex.erase(hex.begin());

        if (hex.size() != 6)
            return RGB(200, 200, 200);

        unsigned int value = 0;
        if (swscanf_s(hex.c_str(), L"%x", &value) != 1)
            return RGB(200, 200, 200);

        ok = true;
        BYTE r = (BYTE)((value >> 16) & 0xFF);
        BYTE g = (BYTE)((value >> 8) & 0xFF);
        BYTE b = (BYTE)(value & 0xFF);
        return RGB(r, g, b);
    }

    // CID-22-21 : Determina si un color es aproximadamente gris para depuración y filtrado visual.
    static bool EsColorGrisAprox(COLORREF c)
    {
        int r = (int)GetRValue(c);
        int g = (int)GetGValue(c);
        int b = (int)GetBValue(c);

        int maxv = max(r, max(g, b));
        int minv = min(r, min(g, b));
        int delta = maxv - minv;

        if (delta <= 18 && r >= 90 && r <= 210 && g >= 90 && g <= 210 && b >= 90 && b <= 210)
            return true;

        return false;
    }

    // CID-22-22 : Recorta espacios en blanco al inicio y final de una cadena ancha.
    static std::wstring Trim(const std::wstring& s)
    {
        size_t a = 0;
        while (a < s.size() && iswspace(s[a])) ++a;

        size_t b = s.size();
        while (b > a && iswspace(s[b - 1])) --b;

        return s.substr(a, b - a);
    }

    // CID-22-23 : Divide un texto multilinea en líneas individuales.
    static std::vector<std::wstring> SplitLines(const std::wstring& s)
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

    // CID-22-24 : Comprueba si una cadena parece un identificador CID válido.
    static bool EsIdCidValido(const std::wstring& s)
    {
        if (s == L"AUX_CID") return true;
        if (s == L"CID_KEY") return true;
        if (s.size() >= 2 && (s[0] == L'I' || s[0] == L'C' || s[0] == L'D'))
            return true;
        return false;
    }

    // CID-22-25 : Convierte un texto a mayúsculas para detección robusta de IDs CID.
    static std::wstring NormalizarTextoMayus(const std::wstring& s)
    {
        std::wstring out = s;
        for (size_t i = 0; i < out.size(); ++i)
            out[i] = (wchar_t)towupper(out[i]);
        return out;
    }

    // CID-22-26 : Intenta detectar el id CID de una tecla a partir de su texto original multilínea.
    static std::wstring DetectarIdCidDesdeTexto(const std::wstring& raw)
    {
        std::vector<std::wstring> lines = SplitLines(raw);

        for (size_t i = 0; i < lines.size(); ++i)
        {
            std::wstring t = Trim(lines[i]);
            std::wstring u = NormalizarTextoMayus(t);

            if (u == L"CID KEY" || u == L"TECLA CID")
                return L"CID_KEY";

            if (u == L"AUX CID" || u == L"AUX_CID")
                return L"AUX_CID";

            if (EsIdCidValido(u))
                return u;
        }

        return L"";
    }

    // CID-22-27 : Escoge el texto visible principal de una tecla a partir del raw o su id CID detectado.
    static std::wstring EscogerTextoVisible(const std::wstring& raw, const std::wstring& idCid)
    {
        if (!idCid.empty())
        {
            if (idCid == L"CID_KEY") return L"CID KEY";
            if (idCid == L"AUX_CID") return L"AUX CID";
            return idCid;
        }

        std::vector<std::wstring> lines = SplitLines(raw);

        for (size_t i = 0; i < lines.size(); ++i)
        {
            std::wstring t = Trim(lines[i]);
            if (!t.empty())
                return t;
        }

        return L"";
    }

    // CID-22-28 : Decide si una tecla debe formar parte del layout renderizable final.
    static bool DebeRenderizarTecla(const TeclaVisualCID& t)
    {
        if (Trim(t.textoOriginal).empty() && Trim(t.textoVisible).empty() && t.idCid.empty())
            return false;

        if (!t.idCid.empty()) return true;
        if (!Trim(t.textoVisible).empty()) return true;

        if (t.esGris) return false;

        return false;
    }

    // CID-22-29 : Parsea el JSON KLE y construye el layout visual renderizable del teclado.
    static bool ParsearLayoutKLE(const JsonValue& root, LayoutTecladoVisual& outLayout, std::wstring* error)
    {
        if (root.type != JsonValue::TArray)
        {
            if (error) *error = L"El JSON del layout no es un array raíz válido.";
            return false;
        }

        outLayout.teclas.clear();
        outLayout.anchoTotal = 0.0;
        outLayout.altoTotal = 0.0;

        double y = 0.0;

        // CID-22-30 : Recorre cada fila KLE acumulando geometría y estado heredable de teclas.
        for (size_t rowIdx = 0; rowIdx < root.a.size(); ++rowIdx)
        {
            const JsonValue& row = root.a[rowIdx];
            if (row.type != JsonValue::TArray)
                continue;

            double x = 0.0;

            double nextW = 1.0;
            double nextH = 1.0;
            double pendingX = 0.0;
            double pendingY = 0.0;
            std::wstring colorHex = L"#cccccc";

            // CID-22-31 : Recorre objetos de estado y strings de teclas dentro de una fila KLE.
            for (size_t i = 0; i < row.a.size(); ++i)
            {
                const JsonValue& item = row.a[i];

                if (item.type == JsonValue::TObject)
                {
                    double v = 0.0;
                    std::wstring s;

                    if (JsonGetNumber(item, L"x", v)) pendingX = v;
                    if (JsonGetNumber(item, L"y", v)) pendingY = v;
                    if (JsonGetNumber(item, L"w", v)) nextW = v;
                    if (JsonGetNumber(item, L"h", v)) nextH = v;
                    if (JsonGetString(item, L"c", s)) colorHex = s;

                    continue;
                }

                // CID-22-32 : Convierte una entrada string KLE en una tecla visual concreta y renderizable.
                if (item.type == JsonValue::TString)
                {
                    x += pendingX;
                    y += pendingY;
                    pendingX = 0.0;
                    pendingY = 0.0;

                    TeclaVisualCID t;
                    t.textoOriginal = item.s;
                    t.x = x;
                    t.y = y;
                    t.w = nextW;
                    t.h = nextH;

                    bool okColor = false;
                    t.color = ParseHexColor(colorHex, okColor);
                    t.esGris = EsColorGrisAprox(t.color);

                    t.idCid = DetectarIdCidDesdeTexto(t.textoOriginal);
                    t.textoVisible = EscogerTextoVisible(t.textoOriginal, t.idCid);
                    t.renderizable = DebeRenderizarTecla(t);

                    if (t.renderizable)
                    {
                        outLayout.teclas.push_back(t);
                        outLayout.anchoTotal = max(outLayout.anchoTotal, t.x + t.w);
                        outLayout.altoTotal = max(outLayout.altoTotal, t.y + t.h);
                    }

                    x += nextW;

                    nextW = 1.0;
                    nextH = 1.0;
                    continue;
                }
            }

            y += 1.0;
            outLayout.altoTotal = max(outLayout.altoTotal, y);
        }

        // CID-22-33 : Falla si el layout no produce ninguna tecla utilizable para render.
        if (outLayout.teclas.empty())
        {
            if (error) *error = L"No se encontraron teclas renderizables en keyboard-layout.json.";
            return false;
        }

        return true;
    }
}

// CID-22-34 : Carga el archivo JSON del layout visual, lo parsea y construye el teclado renderizable.
bool CargarLayoutTecladoVisual(const std::wstring& rutaJson, LayoutTecladoVisual& outLayout, std::wstring* error)
{
    LimpiarLayoutTecladoVisual(outLayout);

    std::wstring texto;
    if (!LeerArchivoTextoUtf8(rutaJson, texto, error))
        return false;

    JsonParser p;
    p.text = &texto;
    p.pos = 0;

    JsonValue root;
    if (!p.ParseValue(root))
    {
        if (error) *error = p.error.empty() ? L"No se pudo parsear keyboard-layout.json." : p.error;
        return false;
    }

    if (!ParsearLayoutKLE(root, outLayout, error))
        return false;

    Log(L"Layout visual cargado. Teclas renderizables: " + std::to_wstring(outLayout.teclas.size()));
    return true;
}

// CID-22-35 : Limpia completamente el layout visual y reinicia sus métricas totales.
void LimpiarLayoutTecladoVisual(LayoutTecladoVisual& layout)
{
    layout.teclas.clear();
    layout.anchoTotal = 0.0;
    layout.altoTotal = 0.0;
}

// CID-22-36 : Convierte una tecla visual abstracta a su rectángulo en píxeles dentro de un lienzo dado.
RECT RectTeclaVisualAPixeles(
    const TeclaVisualCID& t,
    int origenX, int origenY,
    int unidadPxW, int unidadPxH)
{
    RECT r{};
    r.left = origenX + (int)(t.x * unidadPxW);
    r.top = origenY + (int)(t.y * unidadPxH);
    r.right = origenX + (int)((t.x + t.w) * unidadPxW);
    r.bottom = origenY + (int)((t.y + t.h) * unidadPxH);
    return r;
}

// CID-22-37 : Busca la tecla visual situada bajo un punto de pantalla ya transformado al canvas del layout.
int BuscarTeclaVisualEnPunto(
    const LayoutTecladoVisual& layout,
    int px, int py,
    int origenX, int origenY,
    int unidadPxW, int unidadPxH)
{
    for (size_t i = 0; i < layout.teclas.size(); ++i)
    {
        const TeclaVisualCID& t = layout.teclas[i];
        if (!t.renderizable) continue;

        RECT r = RectTeclaVisualAPixeles(t, origenX, origenY, unidadPxW, unidadPxH);
        if (px >= r.left && px < r.right && py >= r.top && py < r.bottom)
            return (int)i;
    }

    return -1;
}

// CID-22-38 : Busca una tecla visual por su identificador CID dentro del layout cargado.
int BuscarTeclaVisualPorIdCid(const LayoutTecladoVisual& layout, const std::wstring& idCid)
{
    for (size_t i = 0; i < layout.teclas.size(); ++i)
    {
        if (layout.teclas[i].idCid == idCid)
            return (int)i;
    }

    return -1;
}