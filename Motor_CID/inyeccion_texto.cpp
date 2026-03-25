#include "inyeccion_texto.h"
#include <windows.h>
#include <vector>

static volatile LONG g_inyectando = 0;

void MarcarInyeccionActiva(bool activa)
{
    InterlockedExchange(&g_inyectando, activa ? 1 : 0);
}

bool InyeccionActiva()
{
    return InterlockedCompareExchange(&g_inyectando, 0, 0) != 0;
}

bool InyectarTextoUnicode(const std::wstring& texto)
{
    if (texto.empty()) return true;

    std::vector<INPUT> inputs;
    inputs.reserve(texto.size() * 2);

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

    UINT enviados = SendInput((UINT)inputs.size(), inputs.data(), sizeof(INPUT));
    return enviados == inputs.size();
}
