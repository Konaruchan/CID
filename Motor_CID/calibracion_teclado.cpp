#include "calibracion_teclado.h"
#include "mapa_teclas_cid.h"

#include <algorithm>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>

namespace
{
    struct CalibracionTecladoState
    {
        CRITICAL_SECTION cs{};
        bool csIniciado = false;
        bool cargada = false;

        // nombre CID -> scanCode
        std::map<std::wstring, DWORD> nombreAScan;

        // scanCode -> nombre CID
        std::map<DWORD, std::wstring> scanANombre;
    };

    CalibracionTecladoState g_state;

    void AsegurarCS()
    {
        if (!g_state.csIniciado)
        {
            InitializeCriticalSection(&g_state.cs);
            g_state.csIniciado = true;
        }
    }

    void Log(const std::wstring& s)
    {
        OutputDebugStringW((s + L"\n").c_str());
    }

    std::wstring NarrowToWideUtf8(const std::string& s)
    {
        if (s.empty()) return L"";

        int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
        if (len <= 0) return L"";

        std::wstring out;
        out.resize((size_t)len);
        MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &out[0], len);
        return out;
    }

    std::string WideToUtf8(const std::wstring& s)
    {
        if (s.empty()) return "";

        int len = WideCharToMultiByte(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0, nullptr, nullptr);
        if (len <= 0) return "";

        std::string out;
        out.resize((size_t)len);
        WideCharToMultiByte(CP_UTF8, 0, s.data(), (int)s.size(), &out[0], len, nullptr, nullptr);
        return out;
    }

    bool LeerArchivoTextoUtf8(const std::wstring& ruta, std::wstring& outTexto, std::wstring* error)
    {
        std::ifstream f(ruta, std::ios::binary);
        if (!f)
        {
            if (error) *error = L"No se pudo abrir el archivo: " + ruta;
            return false;
        }

        std::string bytes((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
        f.close();

        // Quitar BOM UTF-8 si existe
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

    bool EscribirArchivoTextoUtf8(const std::wstring& ruta, const std::wstring& texto, std::wstring* error)
    {
        std::ofstream f(ruta, std::ios::binary | std::ios::trunc);
        if (!f)
        {
            if (error) *error = L"No se pudo escribir el archivo: " + ruta;
            return false;
        }

        const std::string utf8 = WideToUtf8(texto);
        const unsigned char bom[3] = { 0xEF, 0xBB, 0xBF };
        f.write((const char*)bom, 3);
        f.write(utf8.data(), (std::streamsize)utf8.size());
        f.close();

        return true;
    }

    bool EsNombreCIDCalibrable(const wchar_t* nombreCid)
    {
        if (!nombreCid || !nombreCid[0]) return false;

        // En calibración guardamos teclas CID físicas + AUX_CID.
        // CID_KEY no hace falta si espacio sigue por VK_SPACE.
        if (wcscmp(nombreCid, L"CID_KEY") == 0) return false;
        return EsNombreTeclaCIDValido(nombreCid);
    }

    std::vector<std::wstring> ObtenerNombresCIDCalibrablesOrdenados()
    {
        std::vector<std::wstring> nombres =
        {
            L"I1",L"I2",L"I3",L"I4",L"I5",L"I6",L"I7",L"I8",L"I9",L"I10",
            L"C1",L"C2",L"C3",L"C4",L"C5",L"C6",
            L"D1",L"D2",L"D3",L"D4",L"D5",L"D6",L"D7",L"D8",L"D9",L"D10",
            L"AUX_CID"
        };

        return nombres;
    }

    void LimpiarNoLock()
    {
        g_state.nombreAScan.clear();
        g_state.scanANombre.clear();
        g_state.cargada = false;
    }

    bool EstablecerAsignacionNoLock(const std::wstring& nombreCid, DWORD scanCode)
    {
        if (!EsNombreCIDCalibrable(nombreCid.c_str()))
            return false;

        if (scanCode == 0 || scanCode >= 256)
            return false;

        // Si este nombre ya existía, eliminar reverse anterior
        std::map<std::wstring, DWORD>::iterator itNombre = g_state.nombreAScan.find(nombreCid);
        if (itNombre != g_state.nombreAScan.end())
        {
            DWORD scanViejo = itNombre->second;
            g_state.scanANombre.erase(scanViejo);
            g_state.nombreAScan.erase(itNombre);
        }

        // Si este scanCode ya estaba asignado a otro nombre, eliminar esa asignación
        std::map<DWORD, std::wstring>::iterator itScan = g_state.scanANombre.find(scanCode);
        if (itScan != g_state.scanANombre.end())
        {
            std::wstring nombreViejo = itScan->second;
            g_state.nombreAScan.erase(nombreViejo);
            g_state.scanANombre.erase(itScan);
        }

        g_state.nombreAScan[nombreCid] = scanCode;
        g_state.scanANombre[scanCode] = nombreCid;
        g_state.cargada = true;
        return true;
    }

    std::wstring EscaparJson(const std::wstring& s)
    {
        std::wstring out;
        out.reserve(s.size() + 8);

        for (size_t i = 0; i < s.size(); ++i)
        {
            wchar_t ch = s[i];
            switch (ch)
            {
            case L'\\': out += L"\\\\"; break;
            case L'"':  out += L"\\\""; break;
            case L'\r': out += L"\\r";  break;
            case L'\n': out += L"\\n";  break;
            case L'\t': out += L"\\t";  break;
            default:    out += ch;      break;
            }
        }

        return out;
    }

    // Parser simple para el formato:
    // {
    //   "version": 1,
    //   "keys": {
    //      "I1": 4,
    //      ...
    //      "AUX_CID": 41
    //   }
    // }
    bool ParsearCalibracionJson(const std::wstring& texto, std::wstring* error)
    {
        std::wregex reKeysBlock(L"\"keys\"\\s*:\\s*\\{([\\s\\S]*?)\\}", std::regex::ECMAScript);
        std::wsmatch mKeys;

        if (!std::regex_search(texto, mKeys, reKeysBlock))
        {
            if (error) *error = L"No se encontró el bloque \"keys\" en keyboard-calibration.json.";
            return false;
        }

        const std::wstring bloqueKeys = mKeys[1].str();

        std::wregex rePar(L"\"([A-Za-z0-9_]+)\"\\s*:\\s*([0-9]+)", std::regex::ECMAScript);
        std::wsregex_iterator it(bloqueKeys.begin(), bloqueKeys.end(), rePar);
        std::wsregex_iterator end;

        std::map<std::wstring, DWORD> temporales;

        for (; it != end; ++it)
        {
            std::wstring nombre = (*it)[1].str();
            DWORD scanCode = (DWORD)_wtoi((*it)[2].str().c_str());

            if (!EsNombreCIDCalibrable(nombre.c_str()))
            {
                // Ignoramos claves raras por si luego ampliáis JSON
                continue;
            }

            if (scanCode == 0 || scanCode >= 256)
            {
                if (error) *error = L"ScanCode inválido para " + nombre + L".";
                return false;
            }

            temporales[nombre] = scanCode;
        }

        if (temporales.empty())
        {
            if (error) *error = L"No se encontró ninguna asignación válida dentro de \"keys\".";
            return false;
        }

        // Validar duplicados de scanCode
        std::map<DWORD, std::wstring> vistos;
        std::map<std::wstring, DWORD>::const_iterator kv;
        for (kv = temporales.begin(); kv != temporales.end(); ++kv)
        {
            std::map<DWORD, std::wstring>::iterator itV = vistos.find(kv->second);
            if (itV != vistos.end())
            {
                if (error)
                {
                    *error = L"El scanCode " + std::to_wstring(kv->second) +
                        L" está duplicado entre " + itV->second + L" y " + kv->first + L".";
                }
                return false;
            }
            vistos[kv->second] = kv->first;
        }

        // Aplicar al estado global
        LimpiarNoLock();
        for (kv = temporales.begin(); kv != temporales.end(); ++kv)
            EstablecerAsignacionNoLock(kv->first, kv->second);

        g_state.cargada = true;
        return true;
    }

    std::wstring ConstruirJsonCalibracion()
    {
        std::wstringstream ss;
        ss << L"{\n";
        ss << L"  \"version\": 1,\n";
        ss << L"  \"keys\": {\n";

        std::vector<std::wstring> nombres = ObtenerNombresCIDCalibrablesOrdenados();
        bool primero = true;

        for (size_t i = 0; i < nombres.size(); ++i)
        {
            std::map<std::wstring, DWORD>::iterator it = g_state.nombreAScan.find(nombres[i]);
            if (it == g_state.nombreAScan.end())
                continue;

            if (!primero)
                ss << L",\n";

            ss << L"    \"" << EscaparJson(nombres[i]) << L"\": " << it->second;
            primero = false;
        }

        ss << L"\n";
        ss << L"  }\n";
        ss << L"}\n";

        return ss.str();
    }
}

bool CargarCalibracionTeclado(const std::wstring& rutaJson, std::wstring* error)
{
    AsegurarCS();

    std::wstring texto;
    std::wstring errLocal;

    if (!LeerArchivoTextoUtf8(rutaJson, texto, &errLocal))
    {
        if (error) *error = errLocal;
        return false;
    }

    EnterCriticalSection(&g_state.cs);
    bool ok = ParsearCalibracionJson(texto, &errLocal);
    LeaveCriticalSection(&g_state.cs);

    if (!ok)
    {
        if (error) *error = errLocal;
        return false;
    }

    Log(L"Calibración de teclado cargada: " + rutaJson);
    return true;
}

bool GuardarCalibracionTeclado(const std::wstring& rutaJson, std::wstring* error)
{
    AsegurarCS();
    EnterCriticalSection(&g_state.cs);

    if (g_state.nombreAScan.empty())
    {
        LeaveCriticalSection(&g_state.cs);
        if (error) *error = L"No hay asignaciones de calibración para guardar.";
        return false;
    }

    const std::wstring json = ConstruirJsonCalibracion();

    LeaveCriticalSection(&g_state.cs);

    if (!EscribirArchivoTextoUtf8(rutaJson, json, error))
        return false;

    Log(L"Calibración de teclado guardada: " + rutaJson);
    return true;
}

void LimpiarCalibracionTeclado()
{
    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    LimpiarNoLock();
    LeaveCriticalSection(&g_state.cs);
}

bool HayCalibracionTecladoCargada()
{
    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    bool ok = g_state.cargada && !g_state.nombreAScan.empty();
    LeaveCriticalSection(&g_state.cs);
    return ok;
}

bool EstablecerAsignacionTeclaCID(const wchar_t* nombreCid, DWORD scanCode)
{
    if (!nombreCid) return false;

    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    bool ok = EstablecerAsignacionNoLock(nombreCid, scanCode);
    LeaveCriticalSection(&g_state.cs);
    return ok;
}

bool QuitarAsignacionTeclaCID(const wchar_t* nombreCid)
{
    if (!nombreCid || !nombreCid[0])
        return false;

    AsegurarCS();
    EnterCriticalSection(&g_state.cs);

    std::map<std::wstring, DWORD>::iterator it = g_state.nombreAScan.find(nombreCid);
    if (it == g_state.nombreAScan.end())
    {
        LeaveCriticalSection(&g_state.cs);
        return false;
    }

    DWORD scan = it->second;
    g_state.nombreAScan.erase(it);
    g_state.scanANombre.erase(scan);

    g_state.cargada = !g_state.nombreAScan.empty();

    LeaveCriticalSection(&g_state.cs);
    return true;
}

bool ExisteTeclaCIDParaScanCode(DWORD scanCode)
{
    if (scanCode >= 256) return false;

    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    bool existe = g_state.scanANombre.find(scanCode) != g_state.scanANombre.end();
    LeaveCriticalSection(&g_state.cs);
    return existe;
}

const wchar_t* NombreTeclaCID_PorScanCode(DWORD scanCode)
{
    if (scanCode >= 256) return nullptr;

    AsegurarCS();
    EnterCriticalSection(&g_state.cs);

    std::map<DWORD, std::wstring>::iterator it = g_state.scanANombre.find(scanCode);
    if (it == g_state.scanANombre.end())
    {
        LeaveCriticalSection(&g_state.cs);
        return nullptr;
    }

    // OJO: puntero válido mientras no cambie el mapa.
    const wchar_t* out = it->second.c_str();

    LeaveCriticalSection(&g_state.cs);
    return out;
}

bool ObtenerScanCodeDeNombreCID(const wchar_t* nombreCid, DWORD& outScanCode)
{
    outScanCode = 0;
    if (!nombreCid || !nombreCid[0]) return false;

    AsegurarCS();
    EnterCriticalSection(&g_state.cs);

    std::map<std::wstring, DWORD>::iterator it = g_state.nombreAScan.find(nombreCid);
    if (it == g_state.nombreAScan.end())
    {
        LeaveCriticalSection(&g_state.cs);
        return false;
    }

    outScanCode = it->second;

    LeaveCriticalSection(&g_state.cs);
    return true;
}

std::vector<std::pair<std::wstring, DWORD>> ObtenerAsignacionesCalibradas()
{
    AsegurarCS();
    EnterCriticalSection(&g_state.cs);

    std::vector<std::pair<std::wstring, DWORD>> out;
    out.reserve(g_state.nombreAScan.size());

    std::map<std::wstring, DWORD>::iterator it;
    for (it = g_state.nombreAScan.begin(); it != g_state.nombreAScan.end(); ++it)
        out.push_back(*it);

    LeaveCriticalSection(&g_state.cs);

    std::sort(out.begin(), out.end(),
        [](const std::pair<std::wstring, DWORD>& a, const std::pair<std::wstring, DWORD>& b)
        {
            return OrdenTeclaCID_PorNombre(a.first.c_str()) < OrdenTeclaCID_PorNombre(b.first.c_str());
        });

    return out;
}