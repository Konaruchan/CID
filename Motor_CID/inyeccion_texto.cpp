// CID-20-01 : Inclusión de la implementación del módulo de inyección de texto Unicode.
#include "inyeccion_texto.h"

// CID-20-02 : Inclusión de cabeceras del sistema y contenedores usados por la inyección.
#include <windows.h>
#include <vector>

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
    if (texto.empty()) return true;

    std::vector<INPUT> inputs;
    inputs.reserve(texto.size() * 2);

    // CID-20-07 : Construye la secuencia de eventos KEYEVENTF_UNICODE para cada carácter del texto.
    for (wchar_t ch : texto)
    {
        INPUT down{};
        down.type = INPUT_KEYBOARD;
        down.ki.wScan = ch;
        down.ki.dwFlags = KEYEVENTF_UNICODE;
        inputs.push_back(down);

        INPUT up{};
        up.type = INPUT_KEYBOARD;
        up.ki.wScan = ch;
        up.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
        inputs.push_back(up);
    }

    // CID-20-08 : Envía todos los eventos acumulados y devuelve si la inyección fue completa.
    UINT enviados = SendInput((UINT)inputs.size(), inputs.data(), sizeof(INPUT));
    return enviados == inputs.size();
}