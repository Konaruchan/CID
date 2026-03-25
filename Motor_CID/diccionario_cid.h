#pragma once
#include <string>
#include <unordered_map>

struct EntradaDiccionarioCID
{
    std::wstring resultado_crudo;
    int numero_tildal = -1;
};

class DiccionarioCID
{
public:
    bool CargarDesdeArchivo(const std::wstring& ruta, std::wstring* error = nullptr);
    bool Buscar(const std::wstring& acorde_normalizado, EntradaDiccionarioCID& out) const;

private:
    std::unordered_map<std::wstring, EntradaDiccionarioCID> m_map;
};
