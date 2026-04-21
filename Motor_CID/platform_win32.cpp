// CID-31-01 : Implementación Win32 de la abstracción de plataforma del motor CID.
#include "platform.h"

#include <vector>

class PlatformCIDWin32 final : public IPlatformCID
{
public:
    ULONGLONG NowMs() const override
    {
        return GetTickCount64();
    }

    SHORT AsyncKeyState(int vk) const override
    {
        return GetAsyncKeyState(vk);
    }

    UINT SendInputEvents(UINT count, INPUT* events) const override
    {
        return SendInput(count, events, sizeof(INPUT));
    }

    bool SendUnicodeText(const std::wstring& texto) const override
    {
        if (texto.empty())
            return true;

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

        const UINT enviados = SendInputEvents((UINT)inputs.size(), inputs.data());
        return enviados == inputs.size();
    }
};

static PlatformCIDWin32 g_plataforma_win32;
static IPlatformCID* g_plataforma_actual = &g_plataforma_win32;

IPlatformCID* PlataformaCIDActual()
{
    return g_plataforma_actual;
}

void EstablecerPlataformaCID(IPlatformCID* plataforma)
{
    g_plataforma_actual = plataforma ? plataforma : &g_plataforma_win32;
}

void RestablecerPlataformaCIDPredeterminada()
{
    g_plataforma_actual = &g_plataforma_win32;
}
