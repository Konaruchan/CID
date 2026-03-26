// CID-10-01 : Inclusión de la implementación del diccionario CID y su interfaz pública.
#include "diccionario_cid.h"

// CID-10-02 : Inclusión del mapa oficial de teclas usado para normalizar acordes y validar nombres.
#include "mapa_teclas_cid.h"

// CID-10-03 : Inclusión de utilidades de archivo, parsing, contenedores, ordenación y Windows.
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>

// CID-10-04 : Recorta espacios ASCII al inicio y final de una cadena estrecha modificándola en sitio.
static void TrimInPlace(std::string& s)
{
    auto isspace_ = [](unsigned char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; };
    while (!s.empty() && isspace_((unsigned char)s.front())) s.erase(s.begin());
    while (!s.empty() && isspace_((unsigned char)s.back())) s.pop_back();
}

// CID-10-05 : Recorta espacios Unicode típicos, BOM y NBSP al inicio y final de una cadena ancha.
static void TrimWideInPlace(std::wstring& s)
{
    auto isws = [](wchar_t c) {
        return c == L' ' || c == L'\t' || c == L'\r' || c == L'\n'
            || c == 0xFEFF
            || c == 0x00A0;
        };

    while (!s.empty() && isws(s.front())) s.erase(s.begin());
    while (!s.empty() && isws(s.back()))  s.pop_back();
}

// CID-10-06 : Convierte una cadena multibyte a Unicode usando la code page indicada.
static std::wstring ConvertirAUnicode(const std::string& s, UINT cp)
{
    if (s.empty()) return L"";
    int need = MultiByteToWideChar(cp, 0, s.c_str(), (int)s.size(), nullptr, 0);
    if (need <= 0) return L"";
    std::wstring out;
    out.resize(need);
    MultiByteToWideChar(cp, 0, s.c_str(), (int)s.size(), out.data(), need);
    return out;
}

// CID-10-07 : Separa una línea del diccionario en acorde, resultado y número tildal.
static bool SepararCampos(const std::string& linea, std::string& a, std::string& b, std::string& c)
{
    size_t p1 = linea.find('|');
    if (p1 == std::string::npos) return false;
    size_t p2 = linea.find('|', p1 + 1);
    if (p2 == std::string::npos) return false;

    a = linea.substr(0, p1);
    b = linea.substr(p1 + 1, p2 - (p1 + 1));
    c = linea.substr(p2 + 1);

    TrimInPlace(a);
    TrimInPlace(b);
    TrimInPlace(c);
    return true;
}

// CID-10-08 : Divide una cadena de nombres de teclas separadas por más y devuelve las partes limpias.
static void SplitPlus(const std::wstring& s, std::vector<std::wstring>& out)
{
    out.clear();
    size_t i = 0;
    while (i < s.size())
    {
        size_t j = s.find(L'+', i);
        std::wstring part = (j == std::wstring::npos) ? s.substr(i) : s.substr(i, j - i);

        TrimWideInPlace(part);

        if (!part.empty()) out.push_back(part);

        if (j == std::wstring::npos) break;
        i = j + 1;
    }
}

// CID-10-09 : Comprueba si un carácter ancho es un dígito decimal ASCII.
static bool EsDigito(wchar_t c) { return c >= L'0' && c <= L'9'; }

// CID-10-10 : Convierte un token CID textual como I3 o D10 en su virtual key oficial del mapa fijo.
static bool ParsearTokenTeclaCID(const std::wstring& token_in, DWORD* out_vk, std::wstring& err)
{
    std::wstring token = token_in;
    TrimWideInPlace(token);

    // CID-10-11 : Rechaza tokens vacíos después de la limpieza inicial.
    if (token.empty())
    {
        err = L"Token de tecla vacío.";
        return false;
    }

    // CID-10-12 : Normaliza y valida el prefijo de familia I, C o D.
    wchar_t pref = token[0];
    if (pref >= L'a' && pref <= L'z') pref = (wchar_t)(pref - (L'a' - L'A'));

    if (pref != L'I' && pref != L'C' && pref != L'D')
    {
        err = L"Prefijo inválido (esperado I/C/D) en: [" + token + L"]";
        return false;
    }

    // CID-10-13 : Rechaza tokens sin parte numérica tras el prefijo.
    if (token.size() < 2)
    {
        err = L"Falta número en: [" + token + L"]";
        return false;
    }

    // CID-10-14 : Parsea y valida el número de tecla dentro del token textual.
    int num = 0;
    for (size_t k = 1; k < token.size(); ++k)
    {
        if (!EsDigito(token[k]))
        {
            err = L"Número inválido en: [" + token + L"]";
            return false;
        }
        num = num * 10 + (token[k] - L'0');
    }

    // CID-10-15 : Define las tablas fijas que convierten nombres CID a virtual keys oficiales.
    static const DWORD VK_I[10] = { '3','4','5','E','R','T','D','F','C','V' };
    static const DWORD VK_C[6] = { '6','7','Y','G','H','B' };
    static const DWORD VK_D[10] = { '8','9','0','U','I','O','J','K','N','M' };

    DWORD vk = 0;

    // CID-10-16 : Resuelve y valida tokens de la familia I dentro del rango permitido.
    if (pref == L'I')
    {
        if (num < 1 || num > 10) { err = L"I fuera de rango (1..10) en: [" + token + L"]"; return false; }
        vk = VK_I[num - 1];
    }
    // CID-10-17 : Resuelve y valida tokens de la familia C dentro del rango permitido.
    else if (pref == L'C')
    {
        if (num < 1 || num > 6) { err = L"C fuera de rango (1..6) en: [" + token + L"]"; return false; }
        vk = VK_C[num - 1];
    }
    // CID-10-18 : Resuelve y valida tokens de la familia D dentro del rango permitido.
    else
    {
        if (num < 1 || num > 10) { err = L"D fuera de rango (1..10) en: [" + token + L"]"; return false; }
        vk = VK_D[num - 1];
    }

    *out_vk = vk;
    return true;
}

// CID-10-19 : Normaliza un acorde textual a su forma canónica oficial basada en nombres del mapa CID.
static bool NormalizarAcordeDesdeNombres(const std::wstring& acorde_in, std::wstring& acorde_out, std::wstring& err)
{
    std::vector<std::wstring> partes;
    SplitPlus(acorde_in, partes);
    if (partes.empty())
    {
        err = L"Acorde vacío.";
        return false;
    }

    std::vector<DWORD> vks;
    vks.reserve(partes.size());

    // CID-10-20 : Convierte cada nombre de tecla del acorde en su virtual key oficial.
    for (const auto& nombre : partes)
    {
        DWORD vk = 0;
        std::wstring e;
        if (!ParsearTokenTeclaCID(nombre, &vk, e))
        {
            err = L"Tecla CID desconocida: [" + nombre + L"]";
            return false;
        }
        vks.push_back(vk);
    }

    // CID-10-21 : Rechaza acordes con teclas duplicadas dentro de la misma combinación.
    std::sort(vks.begin(), vks.end());
    for (size_t i = 1; i < vks.size(); ++i)
    {
        if (vks[i] == vks[i - 1])
        {
            err = L"Acorde con tecla repetida.";
            return false;
        }
    }

    // CID-10-22 : Ordena las teclas del acorde según el orden canónico oficial del mapa CID.
    std::sort(vks.begin(), vks.end(), [](DWORD a, DWORD b) {
        return OrdenTeclaCID(a) < OrdenTeclaCID(b);
        });

    // CID-10-23 : Reconstruye la clave canónica final usando los nombres oficiales del mapa.
    acorde_out.clear();
    for (size_t i = 0; i < vks.size(); ++i)
    {
        const wchar_t* n = NombreTeclaCID(vks[i]);
        if (!n)
        {
            err = L"Mapa CID inconsistente (vk sin nombre).";
            return false;
        }
        if (!acorde_out.empty()) acorde_out += L"+";
        acorde_out += n;
    }
    return true;
}

// CID-10-24 : Carga el diccionario CID desde archivo validando formato, codificación y unicidad de acordes.
bool DiccionarioCID::CargarDesdeArchivo(const std::wstring& ruta, std::wstring* error)
{
    m_map.clear();

    std::ifstream f(ruta, std::ios::binary);
    if (!f)
    {
        if (error) *error = L"No se pudo abrir: " + ruta;
        return false;
    }

    std::string linea;
    int numLinea = 0;

    // CID-10-25 : Recorre el archivo línea a línea y procesa solo entradas útiles del diccionario.
    while (std::getline(f, linea))
    {
        numLinea++;

        // CID-10-26 : Limpia el retorno de carro final conservado por lecturas CRLF.
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();

        // CID-10-27 : Ignora líneas vacías tras la limpieza superficial.
        std::string t = linea;
        TrimInPlace(t);
        if (t.empty()) continue;

        // CID-10-28 : Ignora comentarios de línea con prefijo almohadilla o doble barra.
        if (!t.empty() && t[0] == '#') continue;
        if (t.size() >= 2 && t[0] == '/' && t[1] == '/') continue;

        // CID-10-29 : Separa los tres campos esperados de la línea actual del diccionario.
        std::string sAcorde, sRes, sNum;
        if (!SepararCampos(linea, sAcorde, sRes, sNum))
        {
            if (error) *error = L"Formato inválido en línea " + std::to_wstring(numLinea) + L". Esperado: A|B|C";
            return false;
        }

        // CID-10-30 : Convierte acorde, resultado y número a Unicode con UTF-8 y fallback CP1252.
        std::wstring wAcorde = ConvertirAUnicode(sAcorde, CP_UTF8);
        std::wstring wRes = ConvertirAUnicode(sRes, CP_UTF8);
        std::wstring wNum = ConvertirAUnicode(sNum, CP_UTF8);

        if (wAcorde.empty() && !sAcorde.empty()) wAcorde = ConvertirAUnicode(sAcorde, 1252);
        if (wRes.empty() && !sRes.empty())       wRes = ConvertirAUnicode(sRes, 1252);
        if (wNum.empty() && !sNum.empty())       wNum = ConvertirAUnicode(sNum, 1252);

        // CID-10-31 : Limpia BOM y espacios raros de los tres campos ya convertidos a Unicode.
        TrimWideInPlace(wAcorde);
        TrimWideInPlace(wRes);
        TrimWideInPlace(wNum);

        // CID-10-32 : Parsea el número tildal y falla si el campo no es un entero válido.
        int numero = -1;
        try {
            numero = std::stoi(wNum);
        }
        catch (...) {
            if (error) *error = L"Número tildal inválido en línea " + std::to_wstring(numLinea);
            return false;
        }

        // CID-10-33 : Normaliza el acorde textual a su clave canónica oficial para almacenarlo en el mapa.
        std::wstring acordeKey, err;
        if (!NormalizarAcordeDesdeNombres(wAcorde, acordeKey, err))
        {
            if (error) *error = L"Error en línea " + std::to_wstring(numLinea) + L": " + err;
            return false;
        }

        // CID-10-34 : Rechaza acordes duplicados ya presentes en el diccionario cargado.
        if (m_map.find(acordeKey) != m_map.end())
        {
            if (error) *error = L"Acorde duplicado en diccionario: [" + acordeKey + L"] (línea " + std::to_wstring(numLinea) + L")";
            return false;
        }

        // CID-10-35 : Construye la entrada final del diccionario y la inserta en el mapa por acorde canónico.
        EntradaDiccionarioCID e;
        e.resultado_crudo = wRes;
        e.numero_tildal = numero;

        m_map.emplace(acordeKey, e);
    }

    return true;
}

// CID-10-36 : Busca una entrada del diccionario por acorde ya normalizado y devuelve su contenido si existe.
bool DiccionarioCID::Buscar(const std::wstring& acorde_normalizado, EntradaDiccionarioCID& out) const
{
    auto it = m_map.find(acorde_normalizado);
    if (it == m_map.end()) return false;
    out = it->second;
    return true;
}