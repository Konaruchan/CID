// CID-11-01 : Previene inclusiones múltiples de la interfaz pública del diccionario CID.
#pragma once

// CID-11-02 : Incluye los tipos de texto y mapa hash usados por la interfaz del diccionario.
#include <string>
#include <unordered_map>

// CID-11-03 : Define la entrada pública del diccionario con resultado crudo y número tildal asociado.
struct EntradaDiccionarioCID
{
    std::wstring resultado_crudo;
    int numero_tildal = -1;
};

// CID-11-04 : Declara la clase que carga y consulta el diccionario normalizado de acordes CID.
class DiccionarioCID
{
public:
    // CID-11-05 : Declara la carga desde archivo y la búsqueda por acorde ya normalizado.
    bool CargarDesdeArchivo(const std::wstring& ruta, std::wstring* error = nullptr);
    bool Buscar(const std::wstring& acorde_normalizado, EntradaDiccionarioCID& out) const;

private:
    // CID-11-06 : Almacena el mapa interno de acordes canónicos hacia sus entradas de diccionario.
    std::unordered_map<std::wstring, EntradaDiccionarioCID> m_map;
};