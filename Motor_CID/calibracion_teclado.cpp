// CID-14-01 : Inclusión de la implementación del sistema de calibración persistente del teclado CID.
#include "calibracion_teclado.h"

// CID-14-02 : Inclusión del mapa oficial de teclas CID usado para validar y ordenar asignaciones.
#include "mapa_teclas_cid.h"

// CID-14-03 : Inclusión de utilidades estándar para ordenación, archivo, mapas, regex y streams.
#include <algorithm>
#include <fstream>
#include <map>
#include <regex>
#include <sstream>

// CID-14-04 : Espacio interno anónimo para encapsular el estado y helpers privados de calibración.
namespace
{
    // CID-14-05 : Estado global de calibración con sincronización y mapas bidireccionales nombre-scanCode.
    struct CalibracionTecladoState
    {
        CRITICAL_SECTION cs{};
        bool csIniciado = false;
        bool cargada = false;

        std::map<std::wstring, DWORD> nombreAScan;
        std::map<DWORD, std::wstring> scanANombre;
    };

    // CID-14-06 : Instancia global única del estado de calibración del teclado.
    CalibracionTecladoState g_state;

    // CID-14-07 : Inicializa la sección crítica interna la primera vez que se necesita.
    void AsegurarCS()
    {
        if (!g_state.csIniciado)
        {
            InitializeCriticalSection(&g_state.cs);
            g_state.csIniciado = true;
        }
    }

    // CID-14-08 : Envía mensajes de depuración del módulo de calibración al visor de salida de Windows.
    void Log(const std::wstring& s)
    {
        OutputDebugStringW((s + L"\n").c_str());
    }

    // CID-14-09 : Convierte una cadena estrecha UTF-8 a Unicode.
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

    // CID-14-10 : Convierte una cadena Unicode a UTF-8 para persistencia en archivo.
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

    // CID-14-11 : Lee un archivo de texto UTF-8, elimina BOM si existe y devuelve su contenido Unicode.
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

    // CID-14-12 : Escribe un archivo de texto UTF-8 con BOM a partir de una cadena Unicode.
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

    // CID-14-13 : Decide si un nombre CID puede participar en calibración persistente.
    bool EsNombreCIDCalibrable(const wchar_t* nombreCid)
    {
        if (!nombreCid || !nombreCid[0]) return false;

        if (wcscmp(nombreCid, L"CID_KEY") == 0) return false;
        return EsNombreTeclaCIDValido(nombreCid);
    }

    // CID-14-14 : Devuelve la lista ordenada oficial de nombres CID que deben guardarse en calibración.
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

    // CID-14-15 : Limpia completamente el estado interno de calibración y marca el sistema como no cargado.
    void LimpiarNoLock()
    {
        g_state.nombreAScan.clear();
        g_state.scanANombre.clear();
        g_state.cargada = false;
    }

    // CID-14-16 : Establece una asignación nombre-scanCode manteniendo coherencia bidireccional sin duplicados.
    bool EstablecerAsignacionNoLock(const std::wstring& nombreCid, DWORD scanCode)
    {
        if (!EsNombreCIDCalibrable(nombreCid.c_str()))
            return false;

        if (scanCode == 0 || scanCode >= 256)
            return false;

        // CID-14-17 : Si el nombre ya existía, elimina antes su asociación inversa anterior.
        std::map<std::wstring, DWORD>::iterator itNombre = g_state.nombreAScan.find(nombreCid);
        if (itNombre != g_state.nombreAScan.end())
        {
            DWORD scanViejo = itNombre->second;
            g_state.scanANombre.erase(scanViejo);
            g_state.nombreAScan.erase(itNombre);
        }

        // CID-14-18 : Si el scanCode ya estaba asignado, elimina la asociación previa del nombre antiguo.
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

    // CID-14-19 : Escapa una cadena Unicode para poder escribirla con seguridad dentro de JSON.
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

    // CID-14-20 : Parsea el JSON de calibración, valida asignaciones y las aplica al estado global.
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

        // CID-14-21 : Extrae pares nombre-scanCode válidos desde el bloque JSON keys.
        for (; it != end; ++it)
        {
            std::wstring nombre = (*it)[1].str();
            DWORD scanCode = (DWORD)_wtoi((*it)[2].str().c_str());

            if (!EsNombreCIDCalibrable(nombre.c_str()))
            {
                continue;
            }

            if (scanCode == 0 || scanCode >= 256)
            {
                if (error) *error = L"ScanCode inválido para " + nombre + L".";
                return false;
            }

            temporales[nombre] = scanCode;
        }

        // CID-14-22 : Falla si el JSON no aporta ninguna asignación calibrable válida.
        if (temporales.empty())
        {
            if (error) *error = L"No se encontró ninguna asignación válida dentro de \"keys\".";
            return false;
        }

        // CID-14-23 : Detecta scanCodes duplicados entre distintas teclas CID antes de aplicar el estado.
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

        // CID-14-24 : Sustituye el estado global por las asignaciones temporales ya validadas.
        LimpiarNoLock();
        for (kv = temporales.begin(); kv != temporales.end(); ++kv)
            EstablecerAsignacionNoLock(kv->first, kv->second);

        g_state.cargada = true;
        return true;
    }

    // CID-14-25 : Construye el JSON completo de calibración a partir del estado interno actual.
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

// CID-14-26 : Carga la calibración desde JSON, la valida y la publica en el estado global del sistema.
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

// CID-14-27 : Guarda la calibración actual en disco serializándola como JSON UTF-8 con BOM.
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

// CID-14-28 : Limpia completamente la calibración cargada actualmente en memoria.
void LimpiarCalibracionTeclado()
{
    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    LimpiarNoLock();
    LeaveCriticalSection(&g_state.cs);
}

// CID-14-29 : Informa si existe una calibración cargada y con asignaciones reales en memoria.
bool HayCalibracionTecladoCargada()
{
    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    bool ok = g_state.cargada && !g_state.nombreAScan.empty();
    LeaveCriticalSection(&g_state.cs);
    return ok;
}

// CID-14-30 : Establece o sustituye la asignación de una tecla CID hacia un scanCode concreto.
bool EstablecerAsignacionTeclaCID(const wchar_t* nombreCid, DWORD scanCode)
{
    if (!nombreCid) return false;

    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    bool ok = EstablecerAsignacionNoLock(nombreCid, scanCode);
    LeaveCriticalSection(&g_state.cs);
    return ok;
}

// CID-14-31 : Elimina la asignación existente de una tecla CID por su nombre.
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

// CID-14-32 : Comprueba si un scanCode ya está asociado a alguna tecla CID calibrada.
bool ExisteTeclaCIDParaScanCode(DWORD scanCode)
{
    if (scanCode >= 256) return false;

    AsegurarCS();
    EnterCriticalSection(&g_state.cs);
    bool existe = g_state.scanANombre.find(scanCode) != g_state.scanANombre.end();
    LeaveCriticalSection(&g_state.cs);
    return existe;
}

// CID-14-33 : Devuelve el nombre CID asociado a un scanCode calibrado si existe actualmente.
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

    const wchar_t* out = it->second.c_str();

    LeaveCriticalSection(&g_state.cs);
    return out;
}

// CID-14-34 : Obtiene el scanCode asociado a un nombre CID calibrado concreto.
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

// CID-14-35 : Devuelve todas las asignaciones calibradas ordenadas según el orden oficial del mapa CID.
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