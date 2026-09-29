// CID-30-01 : Previene inclusiones múltiples de la abstracción de plataforma del motor CID.
#pragma once

#include <windows.h>
#include <string>

// Identidad Win32 del destino; no identifica campos virtuales que comparten HWND.
struct DestinoEntradaCID
{
    HWND ventana = nullptr;
    HWND foco = nullptr;
    bool operator==(const DestinoEntradaCID&) const = default;
};

// CID-30-02 : Define la interfaz de plataforma para tiempo, teclado e inyección.
class IPlatformCID
{
public:
    virtual ~IPlatformCID() = default;
    virtual DestinoEntradaCID DestinoActual() const = 0;
    virtual ULONGLONG NowMs() const = 0;
    virtual SHORT AsyncKeyState(int vk) const = 0;
    virtual UINT SendInputEvents(UINT count, INPUT* events) const = 0;
    virtual bool SendUnicodeText(const std::wstring& texto) const = 0;
};

// CID-30-03 : Expone la plataforma activa y el restablecimiento al backend Win32 por defecto.
IPlatformCID* PlataformaCIDActual();
void EstablecerPlataformaCID(IPlatformCID* plataforma);
void RestablecerPlataformaCIDPredeterminada();
