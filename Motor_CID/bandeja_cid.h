#pragma once
#include <shellapi.h>
#pragma comment(lib, "Shell32.lib")

// La bandeja pertenece al hilo principal y sigue disponible aunque fallen los atajos.
class BandejaCID
{
    HWND ventana = nullptr;
    NOTIFYICONDATAW icono{};
    inline static UINT reinicioExplorer = RegisterWindowMessageW(L"TaskbarCreated");
    static constexpr UINT Mensaje = WM_APP + 80;
    static LRESULT CALLBACK Procedimiento(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        auto self = reinterpret_cast<BandejaCID*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
        if (msg == WM_NCCREATE)
        {
            self = static_cast<BandejaCID*>(reinterpret_cast<CREATESTRUCTW*>(lp)->lpCreateParams);
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
        }
        if (!self) return DefWindowProcW(hwnd, msg, wp, lp);
        if (msg == reinicioExplorer)
        {
            Shell_NotifyIconW(NIM_ADD, &self->icono);
            return 0;
        }
        if (msg == Mensaje && (lp == WM_RBUTTONUP || lp == WM_LBUTTONUP || lp == WM_CONTEXTMENU))
        {
            HMENU menu = CreatePopupMenu();
            if (!menu) return 0;
            AppendMenuW(menu, MF_STRING, 1, EstaModoCID() ? L"Pausar CID (QWERTY)" : L"Activar CID");
            AppendMenuW(menu, MF_STRING, 2, L"Ayuda y atajos");
            AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
            AppendMenuW(menu, MF_STRING, 3, L"Salir de CID");
            ReiniciarDetectorAcorde();
            PausarGestorAsentado(true);
            POINT punto{};
            GetCursorPos(&punto);
            SetForegroundWindow(hwnd);
            const UINT comando = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON,
                punto.x, punto.y, 0, hwnd, nullptr);
            DestroyMenu(menu);
            PostMessageW(hwnd, WM_NULL, 0, 0);
            if (comando == 1)
            {
                AlternarModoCID();
                Superposicion_SetModoQwerty(!EstaModoCID());
                Superposicion_SetUltimoAsentado(EstaModoCID() ? L"MODO: CID" : L"MODO: QWERTY (pausado)");
                self->Actualizar();
            }
            if (comando == 2)
            {
                MessageBoxW(hwnd,
                    L"CID 0.2 beta\n\n"
                    L"Ctrl + Shift + F11: alternar CID / QWERTY.\n"
                    L"Ctrl + Shift + F9: cerrar el motor.\n\n"
                    L"Combina hasta tres teclas para formar un acorde.\n"
                    L"Mantén Espacio para evitar el asentado automático; suéltalo para asentar.\n"
                    L"D10 modifica la última pieza.\n\n"
                    L"Al pausar se conservan las piezas pendientes y no se inyecta texto.\n"
                    L"Antes de reactivar CID, vuelve al campo donde estabas escribiendo.\n\n"
                    L"Manual: github.com/Konaruchan/CID/wiki",
                    L"Ayuda de CID", MB_OK | MB_ICONINFORMATION);
            }
            if (comando == 3) PostQuitMessage(0);
            else PausarGestorAsentado(!EstaModoCID());
            return 0;
        }
        if (msg == WM_CLOSE) { PostQuitMessage(0); return 0; }
        return DefWindowProcW(hwnd, msg, wp, lp);
    }
public:
    bool Iniciar(HINSTANCE instancia)
    {
        WNDCLASSW wc{};
        wc.lpfnWndProc = Procedimiento;
        wc.hInstance = instancia;
        wc.lpszClassName = L"CID_Bandeja_02";
        if (!RegisterClassW(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) return false;
        ventana = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"CID 0.2 beta",
            WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, instancia, this);
        if (!ventana) return false;
        icono.cbSize = sizeof(icono);
        icono.hWnd = ventana;
        icono.uID = 1;
        icono.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
        icono.uCallbackMessage = Mensaje;
        icono.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
        wcscpy_s(icono.szTip, L"CID 0.2 beta — activo");
        return Shell_NotifyIconW(NIM_ADD, &icono) != FALSE;
    }
    void Actualizar()
    {
        wcscpy_s(icono.szTip, EstaModoCID() ? L"CID 0.2 beta — activo" : L"CID 0.2 beta — QWERTY (pausado)");
        Shell_NotifyIconW(NIM_MODIFY, &icono);
    }
    ~BandejaCID()
    {
        if (ventana)
        {
            Shell_NotifyIconW(NIM_DELETE, &icono);
            DestroyWindow(ventana);
        }
    }
};
