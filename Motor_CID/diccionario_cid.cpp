#include "diccionario_cid.h"
#include "mapa_teclas_cid.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <windows.h>

static void TrimInPlace(std::string& s)
{
    auto isspace_ = [](unsigned char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; };
    while (!s.empty() && isspace_((unsigned char)s.front())) s.erase(s.begin());
    while (!s.empty() && isspace_((unsigned char)s.back())) s.pop_back();
}

static void TrimWideInPlace(std::wstring& s)
{
    auto isws = [](wchar_t c) {
        // Espacios típicos + BOM + NBSP
        return c == L' ' || c == L'\t' || c == L'\r' || c == L'\n'
            || c == 0xFEFF /* BOM */
            || c == 0x00A0 /* NBSP */;
        };

    while (!s.empty() && isws(s.front())) s.erase(s.begin());
    while (!s.empty() && isws(s.back()))  s.pop_back();
}

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

static bool SepararCampos(const std::string& linea, std::string& a, std::string& b, std::string& c)
{
    // Formato: Acorde | resultado | numero
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

static bool EsDigito(wchar_t c) { return c >= L'0' && c <= L'9'; }

static bool ParsearTokenTeclaCID(const std::wstring& token_in, DWORD* out_vk, std::wstring& err)
{
    std::wstring token = token_in;
    TrimWideInPlace(token);

    if (token.empty())
    {
        err = L"Token de tecla vacío.";
        return false;
    }

    // Normaliza mayúscula en el prefijo
    wchar_t pref = token[0];
    if (pref >= L'a' && pref <= L'z') pref = (wchar_t)(pref - (L'a' - L'A'));

    if (pref != L'I' && pref != L'C' && pref != L'D')
    {
        err = L"Prefijo inválido (esperado I/C/D) en: [" + token + L"]";
        return false;
    }

    if (token.size() < 2)
    {
        err = L"Falta número en: [" + token + L"]";
        return false;
    }

    // Extraer número (I10, D10, etc.)
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

    // Tablas de mapeo a VK (tu mapa fijo)
    // I1..I10: 3 4 5 E R T D F C V
    static const DWORD VK_I[10] = { '3','4','5','E','R','T','D','F','C','V' };

    // C1..C6 : 6 7 Y G H B
    static const DWORD VK_C[6] = { '6','7','Y','G','H','B' };

    // D1..D10: 8 9 0 U I O J K N M
    static const DWORD VK_D[10] = { '8','9','0','U','I','O','J','K','N','M' };

    DWORD vk = 0;

    if (pref == L'I')
    {
        if (num < 1 || num > 10) { err = L"I fuera de rango (1..10) en: [" + token + L"]"; return false; }
        vk = VK_I[num - 1];
    }
    else if (pref == L'C')
    {
        if (num < 1 || num > 6) { err = L"C fuera de rango (1..6) en: [" + token + L"]"; return false; }
        vk = VK_C[num - 1];
    }
    else // D
    {
        if (num < 1 || num > 10) { err = L"D fuera de rango (1..10) en: [" + token + L"]"; return false; }
        vk = VK_D[num - 1];
    }

    *out_vk = vk;
    return true;
}

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

    for (const auto& nombre : partes)
    {
        DWORD vk = 0;
        std::wstring e;
        if (!ParsearTokenTeclaCID(nombre, &vk, e))
        {
            err = L"Tecla CID desconocida: [" + nombre + L"]";
            // Si quieres el motivo exacto, cambia a: err = e;
            return false;
        }
        vks.push_back(vk);
    }

    // Duplicados dentro del mismo acorde
    std::sort(vks.begin(), vks.end());
    for (size_t i = 1; i < vks.size(); ++i)
    {
        if (vks[i] == vks[i - 1])
        {
            err = L"Acorde con tecla repetida.";
            return false;
        }
    }

    // Orden canónico usando el orden oficial del mapa
    std::sort(vks.begin(), vks.end(), [](DWORD a, DWORD b) {
        return OrdenTeclaCID(a) < OrdenTeclaCID(b);
        });

    // Construir clave canónica con NOMBRE oficial (no el literal del archivo)
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

    while (std::getline(f, linea))
    {
        numLinea++;

        // Limpia \r
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();

        // Permite líneas vacías
        std::string t = linea;
        TrimInPlace(t);
        if (t.empty()) continue;

        // (Opcional) Ignorar comentarios tipo # o //
        if (!t.empty() && t[0] == '#') continue;
        if (t.size() >= 2 && t[0] == '/' && t[1] == '/') continue;

        // Campos
        std::string sAcorde, sRes, sNum;
        if (!SepararCampos(linea, sAcorde, sRes, sNum))
        {
            if (error) *error = L"Formato inválido en línea " + std::to_wstring(numLinea) + L". Esperado: A|B|C";
            return false;
        }

        // Convertimos (intentamos UTF-8, si sale vacío, fallback CP1252)
        std::wstring wAcorde = ConvertirAUnicode(sAcorde, CP_UTF8);
        std::wstring wRes = ConvertirAUnicode(sRes, CP_UTF8);
        std::wstring wNum = ConvertirAUnicode(sNum, CP_UTF8);

        if (wAcorde.empty() && !sAcorde.empty()) wAcorde = ConvertirAUnicode(sAcorde, 1252);
        if (wRes.empty() && !sRes.empty())       wRes = ConvertirAUnicode(sRes, 1252);
        if (wNum.empty() && !sNum.empty())       wNum = ConvertirAUnicode(sNum, 1252);

        // Limpia BOM / espacios raros (clave para la primera línea si hay UTF-8 BOM)
        TrimWideInPlace(wAcorde);
        TrimWideInPlace(wRes);
        TrimWideInPlace(wNum);

        int numero = -1;
        try {
            numero = std::stoi(wNum);
        }
        catch (...) {
            if (error) *error = L"Número tildal inválido en línea " + std::to_wstring(numLinea);
            return false;
        }

        // Normaliza acorde
        std::wstring acordeKey, err;
        if (!NormalizarAcordeDesdeNombres(wAcorde, acordeKey, err))
        {
            if (error) *error = L"Error en línea " + std::to_wstring(numLinea) + L": " + err;
            return false;
        }

        // Duplicado
        if (m_map.find(acordeKey) != m_map.end())
        {
            if (error) *error = L"Acorde duplicado en diccionario: [" + acordeKey + L"] (línea " + std::to_wstring(numLinea) + L")";
            return false;
        }

        EntradaDiccionarioCID e;
        e.resultado_crudo = wRes;
        e.numero_tildal = numero;

        m_map.emplace(acordeKey, e);
    }

    return true;
}

bool DiccionarioCID::Buscar(const std::wstring& acorde_normalizado, EntradaDiccionarioCID& out) const
{
    auto it = m_map.find(acorde_normalizado);
    if (it == m_map.end()) return false;
    out = it->second;
    return true;
}
