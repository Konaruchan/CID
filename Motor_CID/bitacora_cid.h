#pragma once
#include <windows.h>
#include <string>
#include <vector>

enum class TipoTokenVisualCID
{
    Pieza,
    Modificador
};

struct TokenVisualCID
{
    TipoTokenVisualCID tipo = TipoTokenVisualCID::Pieza;
    std::wstring texto;
};

struct LineaVisualCID
{
    std::vector<TokenVisualCID> tokens;
};

struct EstadoVisualBitacoraCID
{
    std::vector<LineaVisualCID> lineas_cerradas;
    LineaVisualCID linea_actual;
};

class BitacoraCID
{
public:
    BitacoraCID();
    ~BitacoraCID();

    // -------------------- Configuración --------------------
    void ConfigurarMaximo(size_t max);
    void ConfigurarMaximoLineasVisuales(size_t max_lineas);

    // -------------------- Limpieza --------------------
    // Limpieza TOTAL: lógica + visual + snapshots de reapertura
    void Limpiar();

    // Limpia solo lo pendiente de la línea viva (lógica)
    void LimpiarPendientesLogicos();

    // Limpia solo el historial/estado visual
    void LimpiarVisual();

    // -------------------- Estado lógico --------------------
    size_t Tamano() const;
    bool HayPendientes() const;

    void Anotar(const std::wstring& texto, int numero_tildal);

    bool AplicarTildeUltimaEntrada(std::wstring* error = nullptr);
    bool AplicarModificadorD10(std::wstring* error = nullptr);

    // Borra la última PIEZA lógica pendiente.
    // Si había MOD. asociados a esa última pieza, también los descarta.
    bool BorrarUltimaEntrada(std::wstring* texto_borrado = nullptr);

    // Borra la última OPERACIÓN pendiente:
    // - si lo último fue una pieza, elimina esa pieza
    // - si lo último fue un modificador, revierte su efecto
    // También intenta mantener sincronizado el token visual de la línea actual.
    bool BorrarUltimaOperacionPendiente(std::wstring* texto_borrado = nullptr, bool* era_modificador = nullptr);

    bool ObtenerUltimaEntrada(std::wstring& out) const;
    bool ReemplazarUltimaEntradaSiCoincide(const std::wstring& esperado, const std::wstring& reemplazo);

    std::vector<std::wstring> ObtenerCopia() const;

    // -------------------- Estado visual --------------------
    void AnotarTokenVisualPieza(const std::wstring& texto);
    void AnotarTokenVisualMod();

    bool BorrarUltimoTokenVisual(TokenVisualCID* token_borrado = nullptr);

    // Cierra la línea actual como asentada:
    // - guarda snapshot para posible reapertura
    // - mueve la línea visual actual al historial cerrado
    // - limpia lo pendiente lógico
    // - abre línea visual nueva vacía
    void CerrarLineaPorAsentado();

    // Reabre la última línea asentada como línea actual, si no hay nada pendiente ahora.
    bool ReabrirUltimaLineaAsentada();

    EstadoVisualBitacoraCID ObtenerEstadoVisual() const;

private:
    struct Entrada
    {
        std::wstring texto;
        int numero_tildal = -1;
        bool tilde_aplicada = false;
    };

    struct OperacionPendiente
    {
        enum class Tipo
        {
            Pieza,
            Modificador
        };

        Tipo tipo = Tipo::Pieza;

        // Solo se usa para deshacer modificadores
        bool tiene_snapshot_previo = false;
        Entrada snapshot_previo;
    };

    static bool AplicarTildeSegunNumero(std::wstring& s, int numero_tildal, std::wstring* error);
    static bool LineasVisualesIguales(const LineaVisualCID& a, const LineaVisualCID& b);

    void LimitarLineasVisuales_NoLock();
    void AnotarOperacionModificadora_NoLock(const Entrada& previo);
    void RecortarOperacionYTokenVisualAsociadosALaUltimaEntrada_NoLock();

private:
    mutable CRITICAL_SECTION m_cs;
    bool m_cs_iniciado = false;

    // Lógica pendiente de la línea viva
    size_t m_max = 64;
    std::vector<Entrada> m_items;
    std::vector<OperacionPendiente> m_operaciones_pendientes;

    // Visual
    size_t m_max_lineas_visuales = 8;
    std::vector<LineaVisualCID> m_lineas_cerradas;
    LineaVisualCID m_linea_actual;

    // Snapshot de la última línea asentada para poder reabrirla
    bool m_hay_ultima_linea_asentada = false;
    LineaVisualCID m_ultima_linea_asentada_visual;
    std::vector<Entrada> m_ultima_linea_asentada_logica;
    std::vector<OperacionPendiente> m_ultima_linea_asentada_operaciones;
};