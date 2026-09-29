#include <windows.h>
#include <filesystem>
#include <algorithm>
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
#include "mecacid_model.h"

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
    mutable int borrados = 0;
    DestinoEntradaCID destino{ reinterpret_cast<HWND>(1), reinterpret_cast<HWND>(2) };
    DestinoEntradaCID DestinoActual() const override { return destino; }
    std::wstring recibido;
    ULONGLONG NowMs() const override { return GetTickCount64(); }
    SHORT AsyncKeyState(int) const override { return 0; }
    UINT SendInputEvents(UINT count, INPUT*) const override { ++borrados; return count; }
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

        Verificar(dic.Buscar(L"I6+D9", entrada) && entrada.resultado_crudo == L"r", "se empaqueta diccionario antiguo");

        MecaModelo tutor(dic);
        Verificar(tutor.NumeroEntradas() > 500, "MECACID no usa el diccionario completo");
        Verificar(tutor.Traducir(L"  \t\n").pasos.empty(), "texto vacio crea pasos");
        Verificar(tutor.Traducir(std::wstring(513, L'a')).pasos.empty(), "limite de traduccion");
        auto normal = tutor.Traducir(L"  HOLA  MUNDO\nCAFÉ ");
        Verificar(normal.normalizado == L"hola mundo café ", "normalizacion espanola");
        auto fuera = tutor.Traducir(L"hola ☃ mundo");
        Verificar(fuera.alternativasQwerty == 1 && fuera.palabras == 3, "fallback QWERTY explicito");
        auto reproducir = [&](const MecaPlan& plan) {
            BitacoraCID simulacion;
            std::wstring terminado;
            for (const auto& paso : plan.pasos) {
                if (paso.tipo == MecaTipo::Acorde) {
                    EntradaDiccionarioCID e;
                    Verificar(dic.Buscar(paso.acorde, e), "acorde inventado por traductor");
                    Verificar(paso.acorde != L"D10" && std::count(paso.acorde.begin(), paso.acorde.end(), L'+') < 3, "acorde no ejecutable");
                    simulacion.Anotar(e.resultado_crudo, e.numero_tildal);
                } else if (paso.tipo == MecaTipo::Modificador) {
                    Verificar(simulacion.AplicarModificadorD10(), "D10 no aplicable");
                } else if (paso.tipo == MecaTipo::Qwerty) {
                    terminado += paso.fragmento;
                    continue;
                }
                std::wstring palabra;
                for (const auto& parte : simulacion.ObtenerCopia()) palabra += parte;
                Verificar(MecaMinusculas(palabra) == paso.acumulado, "traduccion difiere del motor real");
                if (paso.tipo == MecaTipo::Asentar) { terminado += MecaMinusculas(palabra) + L" "; simulacion.Limpiar(); }
            }
            Verificar(terminado == plan.normalizado, "traduccion incompleta");
        };
        reproducir(normal); reproducir(fuera);
        reproducir(tutor.Traducir(L"¿cómo estás? ¡hola! café música mañana"));
        for (const auto& [acorde, e] : dic.EnumerarEntradas()) reproducir(tutor.Traducir(e.resultado_crudo));
        for (int nivel = 0; nivel < 5; ++nivel) {
            auto ejercicios = tutor.Ejercicios(nivel);
            Verificar(!ejercicios.empty(), "nivel sin ejercicios");
            for (const auto& ejercicio : ejercicios) {
                auto plan = tutor.Traducir(ejercicio);
                Verificar(plan.alternativasQwerty == 0, "ejercicio CID necesita QWERTY");
                reproducir(plan);
            }
        }
        Verificar(cargar("I1|a|1\nI2|ab|1\nI3|bc|1\nI4|c|1\n"), "diccionario de optimizacion");
        MecaModelo minimo(dic);
        auto optimo = minimo.Traducir(L"abc");
        Verificar(optimo.pasos.size() == 3, "traductor no minimiza acciones");
        Verificar(minimo.Traducir(L"abc").pasos.front().acorde == optimo.pasos.front().acorde, "traduccion no determinista");
        Verificar(dic.CargarDesdeArchivo(argv[1], &error), "restaurar diccionario distribuido");

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
        bitacora.Anotar(L"seguro", -1);
        Verificar(PrepararDestinoCID(plataforma.destino), "capturar destino");
        const auto original = plataforma.destino;
        plataforma.destino.foco = reinterpret_cast<HWND>(3);
        const int antes = plataforma.intentos;
        Bombear(650);
        EventoTeclaCID_Key(false);
        Verificar(plataforma.intentos == antes && bitacora.Tamano() == 1, "escritura en otro campo");
        Verificar(!PrepararDestinoCID(plataforma.destino), "mezcla fragmentos de otro destino");
        plataforma.destino = original;
        EventoTeclaCID_Key(false);
        Verificar(bitacora.Tamano() == 0, "no recupera pendientes al volver al destino");
        plataforma.destino.ventana = reinterpret_cast<HWND>(4);
        BorrarUltimoAsentado();
        Verificar(plataforma.borrados == 0, "borrado en otra ventana");
        plataforma.destino = original;
        DetenerGestorAsentado();
        DetenerGestorAsentado();

        Verificar(EstablecerAsignacionTeclaCID(L"I1", 4), "asignar tecla de prueba");
        Verificar(IniciarDetectorAcorde(30), "iniciar detector");
        ConectarBitacora(&bitacora);
        ConectarDiccionario(&dic);
        for (int i = 0; i < 30; ++i)
        {
            RecibirEventoTeclaCID('3', 4, true);
            RecibirEventoTeclaCID('3', 4, false);
            // Windows no garantiza el despacho de WM_TIMER en 60 ms bajo carga.
            const auto limite = GetTickCount64() + 2000;
            while (DCtx().timer != 0 && GetTickCount64() < limite) Bombear(10);
            Verificar(DCtx().timer == 0 && !DCtx().ventana_activa, "temporizador no liberado");
        }
        const auto tamanoAntes = bitacora.Tamano();
        RecibirEventoTeclaCID('3', 4, true);
        plataforma.destino.foco = reinterpret_cast<HWND>(5);
        Bombear(150);
        Verificar(bitacora.Tamano() == tamanoAntes, "acorde resuelto en otro destino");
        plataforma.destino = original;
        RecibirEventoTeclaCID('3', 4, false);
        RecibirEventoTeclaCID('3', 4, true);
        EstablecerModoCID(false);
        auto pendientes = bitacora.Tamano();
        Bombear(80);
        Verificar(bitacora.Tamano() == pendientes && DCtx().timer == 0, "acorde diferido tras pausa");
        DetenerDetectorAcorde();
        DetenerDetectorAcorde();
        Bombear(80);
        Verificar(GuardarCalibracionTeclado((temp / L"calibracion.json").wstring(), &error), "guardar calibracion");
        Verificar(CargarCalibracionTeclado((temp / L"calibracion.json").wstring(), &error), "leer calibracion guardada");
        Verificar(!GuardarCalibracionTeclado((temp / L"no-existe" / L"calibracion.json").wstring(), &error), "guardado fallido informa exito");
        RestablecerPlataformaCIDPredeterminada();
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
