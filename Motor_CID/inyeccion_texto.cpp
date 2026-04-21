// CID-20-01 : Inclusión de la implementación del módulo de inyección de texto Unicode.
#include "inyeccion_texto.h"

// CID-20-02 : Inclusión de cabeceras del sistema y contenedores usados por la inyección.
#include <windows.h>
#include "platform.h"

// CID-20-03 : Estado global atómico que marca si el sistema CID está inyectando entrada propia.
static volatile LONG g_inyectando = 0;

// CID-20-04 : Activa o desactiva la marca global de inyección propia del sistema CID.
void MarcarInyeccionActiva(bool activa)
{
    InterlockedExchange(&g_inyectando, activa ? 1 : 0);
}

// CID-20-05 : Devuelve si el sistema se encuentra actualmente en medio de una inyección propia.
bool InyeccionActiva()
{
    return InterlockedCompareExchange(&g_inyectando, 0, 0) != 0;
}

// CID-20-06 : Inyecta una cadena Unicode completa simulando pulsación y liberación de cada carácter.
bool InyectarTextoUnicode(const std::wstring& texto)
{
    IPlatformCID* plataforma = PlataformaCIDActual();
    return plataforma ? plataforma->SendUnicodeText(texto) : false;
}
