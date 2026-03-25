#include "bitacora_cid.h"
#include <cwctype>

BitacoraCID::BitacoraCID()
{
    InitializeCriticalSection(&m_cs);
    m_cs_iniciado = true;
}

BitacoraCID::~BitacoraCID()
{
    if (m_cs_iniciado)
    {
        DeleteCriticalSection(&m_cs);
        m_cs_iniciado = false;
    }
}

// -------------------- Helpers internos --------------------

static bool EsVocal(wchar_t c)
{
    c = (wchar_t)towlower(c);
    return c == L'a' || c == L'e' || c == L'i' || c == L'o' || c == L'u';
}

static wchar_t VocalConTilde(wchar_t c)
{
    bool may = (c == towupper(c));
    wchar_t base = (wchar_t)towlower(c);
    wchar_t out = c;

    switch (base)
    {
    case L'a': out = L'á'; break;
    case L'e': out = L'é'; break;
    case L'i': out = L'í'; break;
    case L'o': out = L'ó'; break;
    case L'u': out = L'ú'; break;
    default: return c;
    }

    if (may) out = (wchar_t)towupper(out);
    return out;
}

bool BitacoraCID::AplicarTildeSegunNumero(std::wstring& s, int numero_tildal, std::wstring* error)
{
    if (numero_tildal <= 0)
    {
        if (error) *error = L"La entrada no admite tilde por número.";
        return false;
    }

    int contador = 0;
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (EsVocal(s[i]))
        {
            contador++;
            if (contador == numero_tildal)
            {
                s[i] = VocalConTilde(s[i]);
                return true;
            }
        }
    }

    if (error) *error = L"No se encontró la vocal #" + std::to_wstring(numero_tildal) + L" para tildar.";
    return false;
}

bool BitacoraCID::LineasVisualesIguales(const LineaVisualCID& a, const LineaVisualCID& b)
{
    if (a.tokens.size() != b.tokens.size())
        return false;

    for (size_t i = 0; i < a.tokens.size(); ++i)
    {
        if (a.tokens[i].tipo != b.tokens[i].tipo)
            return false;
        if (a.tokens[i].texto != b.tokens[i].texto)
            return false;
    }

    return true;
}

void BitacoraCID::LimitarLineasVisuales_NoLock()
{
    if (m_max_lineas_visuales < 1)
        m_max_lineas_visuales = 1;

    if (m_lineas_cerradas.size() > m_max_lineas_visuales)
    {
        size_t exceso = m_lineas_cerradas.size() - m_max_lineas_visuales;
        m_lineas_cerradas.erase(m_lineas_cerradas.begin(), m_lineas_cerradas.begin() + exceso);
    }
}

void BitacoraCID::AnotarOperacionModificadora_NoLock(const Entrada& previo)
{
    OperacionPendiente op;
    op.tipo = OperacionPendiente::Tipo::Modificador;
    op.tiene_snapshot_previo = true;
    op.snapshot_previo = previo;
    m_operaciones_pendientes.push_back(op);
}

void BitacoraCID::RecortarOperacionYTokenVisualAsociadosALaUltimaEntrada_NoLock()
{
    // Primero quitamos MOD. finales asociados a la última pieza
    while (!m_operaciones_pendientes.empty() &&
        m_operaciones_pendientes.back().tipo == OperacionPendiente::Tipo::Modificador)
    {
        m_operaciones_pendientes.pop_back();

        if (!m_linea_actual.tokens.empty() &&
            m_linea_actual.tokens.back().tipo == TipoTokenVisualCID::Modificador)
        {
            m_linea_actual.tokens.pop_back();
        }
    }

    // Luego quitamos la pieza final
    if (!m_operaciones_pendientes.empty() &&
        m_operaciones_pendientes.back().tipo == OperacionPendiente::Tipo::Pieza)
    {
        m_operaciones_pendientes.pop_back();

        if (!m_linea_actual.tokens.empty() &&
            m_linea_actual.tokens.back().tipo == TipoTokenVisualCID::Pieza)
        {
            m_linea_actual.tokens.pop_back();
        }
    }
}

// -------------------- Configuración --------------------

void BitacoraCID::ConfigurarMaximo(size_t max)
{
    EnterCriticalSection(&m_cs);

    m_max = (max < 1) ? 1 : max;

    if (m_items.size() > m_max)
        m_items.erase(m_items.begin(), m_items.begin() + (m_items.size() - m_max));

    LeaveCriticalSection(&m_cs);
}

void BitacoraCID::ConfigurarMaximoLineasVisuales(size_t max_lineas)
{
    EnterCriticalSection(&m_cs);

    m_max_lineas_visuales = (max_lineas < 1) ? 1 : max_lineas;
    LimitarLineasVisuales_NoLock();

    LeaveCriticalSection(&m_cs);
}

// -------------------- Limpieza --------------------

void BitacoraCID::Limpiar()
{
    EnterCriticalSection(&m_cs);

    m_items.clear();
    m_operaciones_pendientes.clear();

    m_lineas_cerradas.clear();
    m_linea_actual.tokens.clear();

    m_hay_ultima_linea_asentada = false;
    m_ultima_linea_asentada_visual.tokens.clear();
    m_ultima_linea_asentada_logica.clear();
    m_ultima_linea_asentada_operaciones.clear();

    LeaveCriticalSection(&m_cs);
}

void BitacoraCID::LimpiarPendientesLogicos()
{
    EnterCriticalSection(&m_cs);

    m_items.clear();
    m_operaciones_pendientes.clear();

    LeaveCriticalSection(&m_cs);
}

void BitacoraCID::LimpiarVisual()
{
    EnterCriticalSection(&m_cs);

    m_lineas_cerradas.clear();
    m_linea_actual.tokens.clear();

    m_hay_ultima_linea_asentada = false;
    m_ultima_linea_asentada_visual.tokens.clear();

    LeaveCriticalSection(&m_cs);
}

// -------------------- Estado lógico --------------------

size_t BitacoraCID::Tamano() const
{
    EnterCriticalSection(&m_cs);
    size_t n = m_items.size();
    LeaveCriticalSection(&m_cs);
    return n;
}

bool BitacoraCID::HayPendientes() const
{
    return Tamano() > 0;
}

void BitacoraCID::Anotar(const std::wstring& texto, int numero_tildal)
{
    EnterCriticalSection(&m_cs);

    if (m_items.size() >= m_max)
        m_items.erase(m_items.begin());

    Entrada e;
    e.texto = texto;
    e.numero_tildal = numero_tildal;
    e.tilde_aplicada = false;

    m_items.push_back(e);

    OperacionPendiente op;
    op.tipo = OperacionPendiente::Tipo::Pieza;
    op.tiene_snapshot_previo = false;
    m_operaciones_pendientes.push_back(op);

    LeaveCriticalSection(&m_cs);
}

std::vector<std::wstring> BitacoraCID::ObtenerCopia() const
{
    EnterCriticalSection(&m_cs);

    std::vector<std::wstring> out;
    out.reserve(m_items.size());

    for (const auto& e : m_items)
        out.push_back(e.texto);

    LeaveCriticalSection(&m_cs);
    return out;
}

bool BitacoraCID::ObtenerUltimaEntrada(std::wstring& out) const
{
    EnterCriticalSection(&m_cs);

    if (m_items.empty())
    {
        LeaveCriticalSection(&m_cs);
        out.clear();
        return false;
    }

    out = m_items.back().texto;

    LeaveCriticalSection(&m_cs);
    return true;
}

bool BitacoraCID::BorrarUltimaEntrada(std::wstring* texto_borrado)
{
    EnterCriticalSection(&m_cs);

    if (m_items.empty())
    {
        LeaveCriticalSection(&m_cs);
        if (texto_borrado) texto_borrado->clear();
        return false;
    }

    if (texto_borrado)
        *texto_borrado = m_items.back().texto;

    m_items.pop_back();
    RecortarOperacionYTokenVisualAsociadosALaUltimaEntrada_NoLock();

    LeaveCriticalSection(&m_cs);
    return true;
}

bool BitacoraCID::BorrarUltimaOperacionPendiente(std::wstring* texto_borrado, bool* era_modificador)
{
    EnterCriticalSection(&m_cs);

    if (m_operaciones_pendientes.empty())
    {
        LeaveCriticalSection(&m_cs);

        if (texto_borrado) texto_borrado->clear();
        if (era_modificador) *era_modificador = false;
        return false;
    }

    const OperacionPendiente op = m_operaciones_pendientes.back();

    if (op.tipo == OperacionPendiente::Tipo::Modificador)
    {
        if (m_items.empty() || !op.tiene_snapshot_previo)
        {
            LeaveCriticalSection(&m_cs);

            if (texto_borrado) texto_borrado->clear();
            if (era_modificador) *era_modificador = true;
            return false;
        }

        if (texto_borrado) *texto_borrado = L"MOD.";
        if (era_modificador) *era_modificador = true;

        m_items.back() = op.snapshot_previo;
        m_operaciones_pendientes.pop_back();

        if (!m_linea_actual.tokens.empty() &&
            m_linea_actual.tokens.back().tipo == TipoTokenVisualCID::Modificador)
        {
            m_linea_actual.tokens.pop_back();
        }

        LeaveCriticalSection(&m_cs);
        return true;
    }

    // Última operación = pieza
    if (m_items.empty())
    {
        LeaveCriticalSection(&m_cs);

        if (texto_borrado) texto_borrado->clear();
        if (era_modificador) *era_modificador = false;
        return false;
    }

    if (texto_borrado) *texto_borrado = m_items.back().texto;
    if (era_modificador) *era_modificador = false;

    m_items.pop_back();
    m_operaciones_pendientes.pop_back();

    if (!m_linea_actual.tokens.empty() &&
        m_linea_actual.tokens.back().tipo == TipoTokenVisualCID::Pieza)
    {
        m_linea_actual.tokens.pop_back();
    }

    LeaveCriticalSection(&m_cs);
    return true;
}

bool BitacoraCID::ReemplazarUltimaEntradaSiCoincide(const std::wstring& esperado, const std::wstring& reemplazo)
{
    EnterCriticalSection(&m_cs);

    if (m_items.empty())
    {
        LeaveCriticalSection(&m_cs);
        return false;
    }

    Entrada& e = m_items.back();
    if (e.texto != esperado)
    {
        LeaveCriticalSection(&m_cs);
        return false;
    }

    Entrada previo = e;

    e.texto = reemplazo;
    e.numero_tildal = -1;
    e.tilde_aplicada = false;

    AnotarOperacionModificadora_NoLock(previo);

    LeaveCriticalSection(&m_cs);
    return true;
}

bool BitacoraCID::AplicarTildeUltimaEntrada(std::wstring* error)
{
    EnterCriticalSection(&m_cs);

    if (m_items.empty())
    {
        if (error) *error = L"La bitácora está vacía.";
        LeaveCriticalSection(&m_cs);
        return false;
    }

    Entrada& e = m_items.back();

    if (e.numero_tildal == -1)
    {
        if (error) *error = L"Esta entrada no admite variante con tilde.";
        LeaveCriticalSection(&m_cs);
        return false;
    }

    if (e.numero_tildal == 0)
    {
        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    if (e.tilde_aplicada)
    {
        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    Entrada previo = e;

    std::wstring err;
    bool ok = AplicarTildeSegunNumero(e.texto, e.numero_tildal, &err);
    if (!ok)
    {
        if (error) *error = err;
        LeaveCriticalSection(&m_cs);
        return false;
    }

    e.tilde_aplicada = true;
    AnotarOperacionModificadora_NoLock(previo);

    if (error) error->clear();
    LeaveCriticalSection(&m_cs);
    return true;
}

bool BitacoraCID::AplicarModificadorD10(std::wstring* error)
{
    // Orden oficial:
    // 1) tilde si realmente cambia algo
    // 2) ? -> ¿
    // 3) ! -> ¡
    // 4) - -> —
    // 5) / -> \

    EnterCriticalSection(&m_cs);

    if (m_items.empty())
    {
        if (error) *error = L"La bitácora está vacía.";
        LeaveCriticalSection(&m_cs);
        return false;
    }

    Entrada& e = m_items.back();
    Entrada previo = e;

    // 1) tilde si realmente cambia algo
    if (e.numero_tildal > 0 && !e.tilde_aplicada)
    {
        std::wstring err;
        if (AplicarTildeSegunNumero(e.texto, e.numero_tildal, &err))
        {
            if (e.texto != previo.texto)
            {
                e.tilde_aplicada = true;
                AnotarOperacionModificadora_NoLock(previo);

                if (error) error->clear();
                LeaveCriticalSection(&m_cs);
                return true;
            }
        }
    }

    // 2) ? -> ¿
    if (e.texto == L"?")
    {
        e.texto = L"¿";
        e.numero_tildal = -1;
        e.tilde_aplicada = false;
        AnotarOperacionModificadora_NoLock(previo);

        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    // 3) ! -> ¡
    if (e.texto == L"!")
    {
        e.texto = L"¡";
        e.numero_tildal = -1;
        e.tilde_aplicada = false;
        AnotarOperacionModificadora_NoLock(previo);

        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    // 4) - -> —
    if (e.texto == L"-")
    {
        e.texto = L"—";
        e.numero_tildal = -1;
        e.tilde_aplicada = false;
        AnotarOperacionModificadora_NoLock(previo);

        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    // 5) / -> \
    if (e.texto == L"/")
    {
        e.texto = L"\\";
        e.numero_tildal = -1;
        e.tilde_aplicada = false;
        AnotarOperacionModificadora_NoLock(previo);

        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    if (error) *error = L"D10 no tuvo efecto sobre la última entrada.";
    LeaveCriticalSection(&m_cs);
    return false;
}

// -------------------- Estado visual --------------------

void BitacoraCID::AnotarTokenVisualPieza(const std::wstring& texto)
{
    EnterCriticalSection(&m_cs);

    TokenVisualCID t;
    t.tipo = TipoTokenVisualCID::Pieza;
    t.texto = texto;

    m_linea_actual.tokens.push_back(t);

    LeaveCriticalSection(&m_cs);
}

void BitacoraCID::AnotarTokenVisualMod()
{
    EnterCriticalSection(&m_cs);

    TokenVisualCID t;
    t.tipo = TipoTokenVisualCID::Modificador;
    t.texto = L"MOD.";

    m_linea_actual.tokens.push_back(t);

    LeaveCriticalSection(&m_cs);
}

bool BitacoraCID::BorrarUltimoTokenVisual(TokenVisualCID* token_borrado)
{
    EnterCriticalSection(&m_cs);

    if (m_linea_actual.tokens.empty())
    {
        LeaveCriticalSection(&m_cs);

        if (token_borrado)
            token_borrado->texto.clear();

        return false;
    }

    if (token_borrado)
        *token_borrado = m_linea_actual.tokens.back();

    m_linea_actual.tokens.pop_back();

    LeaveCriticalSection(&m_cs);
    return true;
}

void BitacoraCID::CerrarLineaPorAsentado()
{
    EnterCriticalSection(&m_cs);

    // Snapshot para posible reapertura del último asentado
    m_ultima_linea_asentada_visual = m_linea_actual;
    m_ultima_linea_asentada_logica = m_items;
    m_ultima_linea_asentada_operaciones = m_operaciones_pendientes;
    m_hay_ultima_linea_asentada = (!m_items.empty() || !m_linea_actual.tokens.empty());

    // Mover línea visual actual al historial cerrado
    if (!m_linea_actual.tokens.empty())
    {
        m_lineas_cerradas.push_back(m_linea_actual);
        LimitarLineasVisuales_NoLock();
    }

    // Limpiar lo pendiente lógico y abrir línea nueva vacía
    m_items.clear();
    m_operaciones_pendientes.clear();
    m_linea_actual.tokens.clear();

    LeaveCriticalSection(&m_cs);
}

bool BitacoraCID::ReabrirUltimaLineaAsentada()
{
    EnterCriticalSection(&m_cs);

    if (!m_hay_ultima_linea_asentada)
    {
        LeaveCriticalSection(&m_cs);
        return false;
    }

    // No reabrir si ya hay algo vivo
    if (!m_items.empty() || !m_linea_actual.tokens.empty())
    {
        LeaveCriticalSection(&m_cs);
        return false;
    }

    m_items = m_ultima_linea_asentada_logica;
    m_operaciones_pendientes = m_ultima_linea_asentada_operaciones;
    m_linea_actual = m_ultima_linea_asentada_visual;

    if (!m_lineas_cerradas.empty() &&
        LineasVisualesIguales(m_lineas_cerradas.back(), m_ultima_linea_asentada_visual))
    {
        m_lineas_cerradas.pop_back();
    }

    m_hay_ultima_linea_asentada = false;
    m_ultima_linea_asentada_visual.tokens.clear();
    m_ultima_linea_asentada_logica.clear();
    m_ultima_linea_asentada_operaciones.clear();

    LeaveCriticalSection(&m_cs);
    return true;
}

EstadoVisualBitacoraCID BitacoraCID::ObtenerEstadoVisual() const
{
    EnterCriticalSection(&m_cs);

    EstadoVisualBitacoraCID estado;
    estado.lineas_cerradas = m_lineas_cerradas;
    estado.linea_actual = m_linea_actual;

    LeaveCriticalSection(&m_cs);
    return estado;
}