#pragma once
#include "diccionario_cid.h"
#include <map>
#include <string>
#include <vector>

enum class MecaTipo { Acorde, Modificador, Asentar, Qwerty };
struct MecaPaso
{
    MecaTipo tipo = MecaTipo::Acorde;
    std::wstring acorde, fragmento, acumulado, explicacion;
};
struct MecaPlan
{
    std::wstring original, normalizado, aviso;
    std::vector<MecaPaso> pasos;
    size_t palabras = 0, alternativasQwerty = 0;
};
struct MecaMarca { unsigned aciertos = 0, errores = 0; };
class MecaModelo
{
public:
    explicit MecaModelo(const DiccionarioCID& diccionario);
    MecaPlan Traducir(const std::wstring& texto) const;
    std::vector<std::wstring> Ejercicios(int nivel) const;
    std::wstring Siguiente(int nivel, const std::map<std::wstring, MecaMarca>& marcas, size_t turno) const;
    size_t NumeroEntradas() const { return entradas.size(); }
private:
    struct Forma { std::wstring texto, base, acorde; bool modificar = false; int teclas = 1; };
    std::vector<std::pair<std::wstring, EntradaDiccionarioCID>> entradas;
    std::vector<Forma> formas;
};
std::wstring MecaMinusculas(std::wstring texto);
