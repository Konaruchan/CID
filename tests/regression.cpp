#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "diccionario_cid.h"
#include "bitacora_cid.h"
#include "gestor_asentado.h"
#include "detector_acorde.h"
#include "engine_context.h"
#include "platform.h"
#include "calibracion_teclado.h"

static int comprobaciones = 0;
void Verificar(bool ok, const char* mensaje)
{
    ++comprobaciones;
    if (!ok) throw std::runtime_error(mensaje);
}
struct PlataformaPrueba : IPlatformCID
{
    bool permitir = true;
    int intentos = 0;
    std::wstring recibido;
    ULONGLONG NowMs() const override { return GetTickCount64(); }
    SHORT AsyncKeyState(int) const override { return 0; }
    UINT SendInputEvents(UINT count, INPUT*) const override { return count; }
    bool SendUnicodeText(const std::wstring& texto) const override
    {
        auto self = const_cast<PlataformaPrueba*>(this);
        ++self->intentos;
        if (permitir) self->recibido += texto;
        return permitir;
    }
};
void Bombear(DWORD duracion)
{
    const auto inicio = GetTickCount64();
    while (GetTickCount64() - inicio < duracion)
    {
        MSG msg{};
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
        Sleep(1);
    }
}
int wmain(int argc, wchar_t** argv)
{
    const auto temp = std::filesystem::temp_directory_path() / (L"cid-tests-" + std::to_wstring(GetCurrentProcessId()));
    std::filesystem::create_directories(temp);
    try
    {
        DiccionarioCID dic;
        std::wstring error;
        auto cargar = [&](const std::string& bytes) {
            std::ofstream f(temp / L"entrada.cid", std::ios::binary);
            f << bytes;
            f.close();
            return dic.CargarDesdeArchivo((temp / L"entrada.cid").wstring(), &error);
        };
        Verificar(cargar("\xEF\xBB\xBF# comentario\nI1|a|1\n"), "BOM antes de comentario");
        EntradaDiccionarioCID entrada;
        for (const auto& invalido : {"I1|a|1x\n", "I1|a|-2\n", "I1||1\n", "I1+|a|1\n", "+I1|a|1\n", "I1++I2|a|1\n", "I1|a|1|extra\n", "I99999999999999999|a|1\n", "I1|a|1\nI1|b|0\n", "# vacio\n"})
        {
            Verificar(!cargar(invalido), "diccionario invalido aceptado");
            Verificar(dic.Buscar(L"I1", entrada) && entrada.resultado_crudo == L"a", "recarga destruye diccionario valido");
            Verificar(!error.empty(), "falta diagnostico");
        }
        Verificar(cargar("I1|caf\xE9|0\n"), "compatibilidad CP1252");
        Verificar(dic.Buscar(L"I1", entrada) && entrada.resultado_crudo == L"café", "decodificacion CP1252");
        Verificar(cargar("I2+I1|á|0\n"), "UTF-8 y acorde sin orden");
        Verificar(dic.Buscar(L"I1+I2", entrada) && entrada.resultado_crudo == L"á", "normalizacion del acorde");
        Verificar(argc > 1 && dic.CargarDesdeArchivo(argv[1], &error), "diccionario distribuido no carga");

        BitacoraCID bitacora;
        bitacora.Anotar(L"cafe", 2);
        bitacora.AnotarTokenVisualPieza(L"cafe");
        Verificar(bitacora.AplicarTildeUltimaEntrada(&error), "aplicar tilde");
        Verificar(bitacora.ObtenerCopia().back() == L"café", "tilde incorrecta");
        bitacora.Limpiar();

        PlataformaPrueba plataforma;
        EstablecerPlataformaCID(&plataforma);
        Verificar(IniciarGestorAsentado(400, &bitacora), "iniciar gestor");
        bitacora.Anotar(L"hola", -1);
        plataforma.permitir = false;
        EventoTeclaCID_Key(true);
        EventoTeclaCID_Key(false);
        Verificar(bitacora.Tamano() == 1 && GCtx().ultimo_inyectado.empty(), "fallo pierde pendientes");
        const int intentos = plataforma.intentos;
        Bombear(650);
        Verificar(plataforma.intentos == intentos, "reintento automatico tras fallo");
        plataforma.permitir = true;
        EventoTeclaCID_Key(true);
        EventoTeclaCID_Key(false);
        Verificar(bitacora.Tamano() == 0 && plataforma.recibido == L"Hola ", "asentado manual");
        bitacora.Anotar(L"mundo", -1);
        EstablecerModoCID(false);
        Bombear(650);
        Verificar(bitacora.Tamano() == 1 && plataforma.recibido == L"Hola ", "QWERTY inyecta pendientes");
        EstablecerModoCID(true);
        Bombear(650);
        Verificar(bitacora.Tamano() == 0 && plataforma.recibido == L"Hola mundo ", "reanudar asentado");
        DetenerGestorAsentado();
        DetenerGestorAsentado();
        RestablecerPlataformaCIDPredeterminada();

        Verificar(EstablecerAsignacionTeclaCID(L"I1", 4), "asignar tecla de prueba");
        Verificar(IniciarDetectorAcorde(30), "iniciar detector");
        ConectarBitacora(&bitacora);
        ConectarDiccionario(&dic);
        for (int i = 0; i < 30; ++i)
        {
            RecibirEventoTeclaCID('3', 4, true);
            RecibirEventoTeclaCID('3', 4, false);
            Bombear(60);
            Verificar(DCtx().timer == 0 && !DCtx().ventana_activa, "temporizador no liberado");
        }
        RecibirEventoTeclaCID('3', 4, true);
        EstablecerModoCID(false);
        auto pendientes = bitacora.Tamano();
        Bombear(80);
        Verificar(bitacora.Tamano() == pendientes && DCtx().timer == 0, "acorde diferido tras pausa");
        DetenerDetectorAcorde();
        DetenerDetectorAcorde();
        Verificar(GuardarCalibracionTeclado((temp / L"calibracion.json").wstring(), &error), "guardar calibracion");
        Verificar(CargarCalibracionTeclado((temp / L"calibracion.json").wstring(), &error), "leer calibracion guardada");
        Verificar(!GuardarCalibracionTeclado((temp / L"no-existe" / L"calibracion.json").wstring(), &error), "guardado fallido informa exito");
        std::filesystem::remove_all(temp);
        std::cout << comprobaciones << " comprobaciones correctas\n";
        return 0;
    }
    catch (const std::exception& e)
    {
        DetenerDetectorAcorde();
        DetenerGestorAsentado();
        RestablecerPlataformaCIDPredeterminada();
        std::cerr << "FALLO: " << e.what() << '\n';
        std::filesystem::remove_all(temp);
        return 1;
    }
}
