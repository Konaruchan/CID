#include "mapa_teclas_cid.h"

#include <cwchar>

struct TeclaCIDLogica
{
    const wchar_t* nombre;
    int orden;
    bool esMarcadoraTilde;
    bool esPedalPrincipal;
    bool esPedalAuxiliar;
};

static const TeclaCIDLogica g_teclasCid[] =
{
    { L"I1",      10, false, false, false },
    { L"I2",      11, false, false, false },
    { L"I3",      12, false, false, false },
    { L"I4",      13, false, false, false },
    { L"I5",      14, false, false, false },
    { L"I6",      15, false, false, false },
    { L"I7",      16, false, false, false },
    { L"I8",      17, false, false, false },
    { L"I9",      18, false, false, false },
    { L"I10",     19, false, false, false },

    { L"C1",      30, false, false, false },
    { L"C2",      31, false, false, false },
    { L"C3",      32, false, false, false },
    { L"C4",      33, false, false, false },
    { L"C5",      34, false, false, false },
    { L"C6",      35, false, false, false },

    { L"D1",      50, false, false, false },
    { L"D2",      51, false, false, false },
    { L"D3",      52, false, false, false },
    { L"D4",      53, false, false, false },
    { L"D5",      54, false, false, false },
    { L"D6",      55, false, false, false },
    { L"D7",      56, false, false, false },
    { L"D8",      57, false, false, false },
    { L"D9",      58, false, false, false },
    { L"D10",     59, true,  false, false },

    { L"CID_KEY", 99, false, true,  false },
    { L"AUX_CID", 98, false, false, true  },
};

static const TeclaCIDLogica* BuscarTeclaCIDLogica(const wchar_t* nombreCid)
{
    if (!nombreCid || !nombreCid[0])
        return nullptr;

    for (const auto& t : g_teclasCid)
    {
        if (wcscmp(t.nombre, nombreCid) == 0)
            return &t;
    }

    return nullptr;
}

bool EsNombreTeclaCIDValido(const wchar_t* nombreCid)
{
    return BuscarTeclaCIDLogica(nombreCid) != nullptr;
}

int OrdenTeclaCID_PorNombre(const wchar_t* nombreCid)
{
    const TeclaCIDLogica* t = BuscarTeclaCIDLogica(nombreCid);
    return t ? t->orden : 1000;
}

bool EsMarcadoraTilde_PorNombre(const wchar_t* nombreCid)
{
    const TeclaCIDLogica* t = BuscarTeclaCIDLogica(nombreCid);
    return t ? t->esMarcadoraTilde : false;
}

bool EsPedalPrincipal_PorNombre(const wchar_t* nombreCid)
{
    const TeclaCIDLogica* t = BuscarTeclaCIDLogica(nombreCid);
    return t ? t->esPedalPrincipal : false;
}

bool EsPedalAuxiliar_PorNombre(const wchar_t* nombreCid)
{
    const TeclaCIDLogica* t = BuscarTeclaCIDLogica(nombreCid);
    return t ? t->esPedalAuxiliar : false;
}

// ----------------------------------------------------
// Compatibilidad temporal con el sistema viejo por VK
// ----------------------------------------------------

const wchar_t* NombreTeclaCID(DWORD vk)
{
    switch (vk)
    {
    case '6': return L"C1";
    case '7': return L"C2";
    case 'Y': return L"C3";
    case 'G': return L"C4";
    case 'H': return L"C5";
    case 'B': return L"C6";

    case '3': return L"I1";
    case '4': return L"I2";
    case '5': return L"I3";
    case 'E': return L"I4";
    case 'R': return L"I5";
    case 'T': return L"I6";
    case 'D': return L"I7";
    case 'F': return L"I8";
    case 'C': return L"I9";
    case 'V': return L"I10";

    case '8': return L"D1";
    case '9': return L"D2";
    case '0': return L"D3";
    case 'U': return L"D4";
    case 'I': return L"D5";
    case 'O': return L"D6";
    case 'J': return L"D7";
    case 'K': return L"D8";
    case 'N': return L"D9";
    case 'M': return L"D10";

    case VK_SPACE: return L"CID_KEY";
    default: return nullptr;
    }
}

int OrdenTeclaCID(DWORD vk)
{
    const wchar_t* nombre = NombreTeclaCID(vk);
    return OrdenTeclaCID_PorNombre(nombre);
}

bool EsTeclaCID(DWORD vk)
{
    return NombreTeclaCID(vk) != nullptr;
}

bool EsMarcadoraTilde(DWORD vk)
{
    const wchar_t* nombre = NombreTeclaCID(vk);
    return EsMarcadoraTilde_PorNombre(nombre);
}