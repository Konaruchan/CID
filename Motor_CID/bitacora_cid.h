// CID-07-01 : Previene inclusiones múltiples de la interfaz pública de la bitácora CID.
#pragma once

// CID-07-02 : Incluye los tipos base del sistema usados por la sincronización interna de la bitácora.
#include <windows.h>

// CID-07-03 : Incluye los tipos de texto y contenedores usados por la interfaz lógica y visual de la bitácora.
#include <string>
#include <vector>

// CID-07-04 : Define los tipos de tokens visuales que pueden aparecer en la representación de la bitácora.
enum class TipoTokenVisualCID
{
    Pieza,
    Modificador
};

// CID-07-05 : Define un token visual individual compuesto por tipo y texto mostrado en pantalla.
struct TokenVisualCID
{
    TipoTokenVisualCID tipo = TipoTokenVisualCID::Pieza;
    std::wstring texto;
};

// CID-07-06 : Define una línea visual como secuencia ordenada de tokens mostrables.
struct LineaVisualCID
{
    std::vector<TokenVisualCID> tokens;
};

// CID-07-07 : Define el estado visual completo de la bitácora con historial cerrado y línea actual abierta.
struct EstadoVisualBitacoraCID
{
    std::vector<LineaVisualCID> lineas_cerradas;
    LineaVisualCID linea_actual;
};

// CID-07-08 : Declara la clase que gestiona el estado lógico, visual y reaperturas de la bitácora CID.
class BitacoraCID
{
public:
    // CID-07-09 : Declara la construcción y destrucción segura de la bitácora con sincronización interna.
    BitacoraCID();
    ~BitacoraCID();

    // CID-07-10 : Declara la configuración de límites para entradas lógicas y líneas visuales.
    void ConfigurarMaximo(size_t max);
    void ConfigurarMaximoLineasVisuales(size_t max_lineas);

    // CID-07-11 : Declara la limpieza total o parcial del estado lógico y visual de la bitácora.
    void Limpiar();
    void LimpiarPendientesLogicos();
    void LimpiarVisual();

    // CID-07-12 : Declara las operaciones de consulta y anotación del estado lógico pendiente.
    size_t Tamano() const;
    bool HayPendientes() const;
    void Anotar(const std::wstring& texto, int numero_tildal);

    // CID-07-13 : Declara la aplicación de tilde y del modificador D10 sobre la última entrada lógica.
    bool AplicarTildeUltimaEntrada(std::wstring* error = nullptr);
    bool AplicarModificadorD10(std::wstring* error = nullptr);

    // CID-07-14 : Declara el borrado de la última entrada completa junto a modificadores asociados.
    bool BorrarUltimaEntrada(std::wstring* texto_borrado = nullptr);

    // CID-07-15 : Declara el borrado o reversión de la última operación pendiente manteniendo la sincronía visual.
    bool BorrarUltimaOperacionPendiente(std::wstring* texto_borrado = nullptr, bool* era_modificador = nullptr);

    // CID-07-16 : Declara la consulta, reemplazo y copia del contenido lógico pendiente de la bitácora.
    bool ObtenerUltimaEntrada(std::wstring& out) const;
    bool ReemplazarUltimaEntradaSiCoincide(const std::wstring& esperado, const std::wstring& reemplazo);
    std::vector<std::wstring> ObtenerCopia() const;

    // CID-07-17 : Declara la anotación y borrado de tokens del estado visual de la línea actual.
    void AnotarTokenVisualPieza(const std::wstring& texto);
    void AnotarTokenVisualMod();
    bool BorrarUltimoTokenVisual(TokenVisualCID* token_borrado = nullptr);

    // CID-07-18 : Declara el cierre por asentado y la posible reapertura de la última línea asentada.
    void CerrarLineaPorAsentado();
    bool ReabrirUltimaLineaAsentada();

    // CID-07-19 : Declara la obtención del estado visual completo expuesto hacia la superposición.
    EstadoVisualBitacoraCID ObtenerEstadoVisual() const;

private:
    // CID-07-20 : Define la estructura interna de una entrada lógica con texto, número tildal y estado de tilde.
    struct Entrada
    {
        std::wstring texto;
        int numero_tildal = -1;
        bool tilde_aplicada = false;
    };

    // CID-07-21 : Define la estructura interna de una operación pendiente para piezas y modificadores reversibles.
    struct OperacionPendiente
    {
        // CID-07-22 : Define los tipos internos de operación pendiente manejados por la bitácora.
        enum class Tipo
        {
            Pieza,
            Modificador
        };

        Tipo tipo = Tipo::Pieza;

        // CID-07-23 : Conserva el snapshot previo usado para deshacer operaciones modificadoras.
        bool tiene_snapshot_previo = false;
        Entrada snapshot_previo;
    };

    // CID-07-24 : Declara helpers internos para tildado y comparación completa de líneas visuales.
    static bool AplicarTildeSegunNumero(std::wstring& s, int numero_tildal, std::wstring* error);
    static bool LineasVisualesIguales(const LineaVisualCID& a, const LineaVisualCID& b);

    // CID-07-25 : Declara helpers internos sin lock para recorte visual y registro de operaciones modificadoras.
    void LimitarLineasVisuales_NoLock();
    void AnotarOperacionModificadora_NoLock(const Entrada& previo);
    void RecortarOperacionYTokenVisualAsociadosALaUltimaEntrada_NoLock();

private:
    // CID-07-26 : Estado interno de sincronización de acceso concurrente a la bitácora.
    mutable CRITICAL_SECTION m_cs;
    bool m_cs_iniciado = false;

    // CID-07-27 : Estado lógico pendiente de la línea viva con límite máximo y operaciones deshacibles.
    size_t m_max = 64;
    std::vector<Entrada> m_items;
    std::vector<OperacionPendiente> m_operaciones_pendientes;

    // CID-07-28 : Estado visual con historial de líneas cerradas y línea actual abierta.
    size_t m_max_lineas_visuales = 8;
    std::vector<LineaVisualCID> m_lineas_cerradas;
    LineaVisualCID m_linea_actual;

    // CID-07-29 : Snapshot de la última línea asentada para permitir su reapertura posterior.
    bool m_hay_ultima_linea_asentada = false;
    LineaVisualCID m_ultima_linea_asentada_visual;
    std::vector<Entrada> m_ultima_linea_asentada_logica;
    std::vector<OperacionPendiente> m_ultima_linea_asentada_operaciones;
};