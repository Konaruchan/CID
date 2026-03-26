// CID-06-01 : Inclusión de la implementación de la bitácora lógica y visual del sistema CID.
#include "bitacora_cid.h"

// CID-06-02 : Inclusión de utilidades de clasificación de caracteres para vocales y tildes.
#include <cwctype>

// CID-06-03 : Inicializa la bitácora creando su sección crítica para acceso concurrente seguro.
BitacoraCID::BitacoraCID()
{
    InitializeCriticalSection(&m_cs);
    m_cs_iniciado = true;
}

// CID-06-04 : Destruye la bitácora liberando su sección crítica si fue iniciada correctamente.
BitacoraCID::~BitacoraCID()
{
    if (m_cs_iniciado)
    {
        DeleteCriticalSection(&m_cs);
        m_cs_iniciado = false;
    }
}

// CID-06-05 : Comprueba si un carácter es una vocal latina sin importar mayúsculas o minúsculas.
static bool EsVocal(wchar_t c)
{
    c = (wchar_t)towlower(c);
    return c == L'a' || c == L'e' || c == L'i' || c == L'o' || c == L'u';
}

// CID-06-06 : Devuelve la versión acentuada de una vocal respetando la capitalización original.
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

// CID-06-07 : Aplica una tilde a la vocal indicada por número ordinal dentro de una cadena.
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

// CID-06-08 : Compara dos líneas visuales completas para saber si sus tokens son exactamente iguales.
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

// CID-06-09 : Recorta el historial de líneas visuales cerradas para respetar el máximo configurado.
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

// CID-06-10 : Registra una operación modificadora pendiente guardando el snapshot previo de la última entrada.
void BitacoraCID::AnotarOperacionModificadora_NoLock(const Entrada& previo)
{
    OperacionPendiente op;
    op.tipo = OperacionPendiente::Tipo::Modificador;
    op.tiene_snapshot_previo = true;
    op.snapshot_previo = previo;
    m_operaciones_pendientes.push_back(op);
}

// CID-06-11 : Recorta la última pieza lógica junto a sus modificadores y tokens visuales asociados.
void BitacoraCID::RecortarOperacionYTokenVisualAsociadosALaUltimaEntrada_NoLock()
{
    // CID-06-12 : Elimina primero los modificadores finales asociados a la última pieza visual y lógica.
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

    // CID-06-13 : Elimina después la última pieza principal de la línea visual y del historial lógico.
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

// CID-06-14 : Configura el tamaño máximo del buffer lógico de entradas pendientes.
void BitacoraCID::ConfigurarMaximo(size_t max)
{
    EnterCriticalSection(&m_cs);

    m_max = (max < 1) ? 1 : max;

    if (m_items.size() > m_max)
        m_items.erase(m_items.begin(), m_items.begin() + (m_items.size() - m_max));

    LeaveCriticalSection(&m_cs);
}

// CID-06-15 : Configura el máximo de líneas visuales cerradas conservadas por la bitácora.
void BitacoraCID::ConfigurarMaximoLineasVisuales(size_t max_lineas)
{
    EnterCriticalSection(&m_cs);

    m_max_lineas_visuales = (max_lineas < 1) ? 1 : max_lineas;
    LimitarLineasVisuales_NoLock();

    LeaveCriticalSection(&m_cs);
}

// CID-06-16 : Limpia por completo el estado lógico, visual y de reapertura de la bitácora.
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

// CID-06-17 : Limpia solo las entradas y operaciones lógicas pendientes sin tocar el historial visual.
void BitacoraCID::LimpiarPendientesLogicos()
{
    EnterCriticalSection(&m_cs);

    m_items.clear();
    m_operaciones_pendientes.clear();

    LeaveCriticalSection(&m_cs);
}

// CID-06-18 : Limpia solo el estado visual activo y el snapshot de la última línea asentada.
void BitacoraCID::LimpiarVisual()
{
    EnterCriticalSection(&m_cs);

    m_lineas_cerradas.clear();
    m_linea_actual.tokens.clear();

    m_hay_ultima_linea_asentada = false;
    m_ultima_linea_asentada_visual.tokens.clear();

    LeaveCriticalSection(&m_cs);
}

// CID-06-19 : Devuelve el número de entradas lógicas pendientes actualmente almacenadas.
size_t BitacoraCID::Tamano() const
{
    EnterCriticalSection(&m_cs);
    size_t n = m_items.size();
    LeaveCriticalSection(&m_cs);
    return n;
}

// CID-06-20 : Indica si existen entradas pendientes comprobando el tamaño lógico actual.
bool BitacoraCID::HayPendientes() const
{
    return Tamano() > 0;
}

// CID-06-21 : Añade una nueva pieza lógica a la bitácora y registra su operación pendiente asociada.
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

// CID-06-22 : Devuelve una copia simple del contenido lógico pendiente en forma de textos planos.
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

// CID-06-23 : Obtiene el texto de la última entrada lógica pendiente si existe.
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

// CID-06-24 : Borra la última entrada lógica y recorta también sus tokens visuales y modificadores asociados.
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

// CID-06-25 : Borra la última operación pendiente restaurando una modificación o eliminando la última pieza.
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

    // CID-06-26 : Revierte la última operación si era un modificador con snapshot previo válido.
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

    // CID-06-27 : Borra la última pieza lógica y su token visual cuando la última operación era una pieza.
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

// CID-06-28 : Reemplaza la última entrada solo si coincide con el valor esperado y registra la modificación.
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

// CID-06-29 : Aplica la tilde pendiente sobre la última entrada cuando su configuración lo permite.
bool BitacoraCID::AplicarTildeUltimaEntrada(std::wstring* error)
{
    EnterCriticalSection(&m_cs);

    // CID-06-30 : Rechaza la operación si no existe ninguna entrada lógica pendiente.
    if (m_items.empty())
    {
        if (error) *error = L"La bitácora está vacía.";
        LeaveCriticalSection(&m_cs);
        return false;
    }

    Entrada& e = m_items.back();

    // CID-06-31 : Rechaza la operación si la entrada actual no admite variante acentuada.
    if (e.numero_tildal == -1)
    {
        if (error) *error = L"Esta entrada no admite variante con tilde.";
        LeaveCriticalSection(&m_cs);
        return false;
    }

    // CID-06-32 : Considera resuelta la operación cuando la entrada no requiere tilde real.
    if (e.numero_tildal == 0)
    {
        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    // CID-06-33 : Considera resuelta la operación si la tilde ya había sido aplicada anteriormente.
    if (e.tilde_aplicada)
    {
        if (error) error->clear();
        LeaveCriticalSection(&m_cs);
        return true;
    }

    // CID-06-34 : Intenta aplicar la tilde real y registra un snapshot para posible deshacer.
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

// CID-06-35 : Aplica el modificador D10 sobre la última entrada siguiendo el orden oficial de transformaciones.
bool BitacoraCID::AplicarModificadorD10(std::wstring* error)
{
    EnterCriticalSection(&m_cs);

    // CID-06-36 : Rechaza D10 si la bitácora no contiene ninguna entrada sobre la que actuar.
    if (m_items.empty())
    {
        if (error) *error = L"La bitácora está vacía.";
        LeaveCriticalSection(&m_cs);
        return false;
    }

    Entrada& e = m_items.back();
    Entrada previo = e;

    // CID-06-37 : Intenta aplicar primero la tilde si todavía no fue aplicada y realmente cambia el texto.
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

    // CID-06-38 : Convierte un cierre de interrogación en apertura cuando D10 actúa sobre un signo de pregunta.
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

    // CID-06-39 : Convierte un cierre de exclamación en apertura cuando D10 actúa sobre un signo de admiración.
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

    // CID-06-40 : Convierte un guion simple en raya larga cuando D10 actúa sobre el símbolo correspondiente.
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

    // CID-06-41 : Convierte una barra inclinada en barra invertida cuando D10 actúa sobre esa entrada.
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

    // CID-06-42 : Informa que D10 no produjo ningún efecto sobre la última entrada disponible.
    if (error) *error = L"D10 no tuvo efecto sobre la última entrada.";
    LeaveCriticalSection(&m_cs);
    return false;
}

// CID-06-43 : Añade un token visual de pieza a la línea visual actualmente abierta.
void BitacoraCID::AnotarTokenVisualPieza(const std::wstring& texto)
{
    EnterCriticalSection(&m_cs);

    TokenVisualCID t;
    t.tipo = TipoTokenVisualCID::Pieza;
    t.texto = texto;

    m_linea_actual.tokens.push_back(t);

    LeaveCriticalSection(&m_cs);
}

// CID-06-44 : Añade un token visual de modificador a la línea visual actualmente abierta.
void BitacoraCID::AnotarTokenVisualMod()
{
    EnterCriticalSection(&m_cs);

    TokenVisualCID t;
    t.tipo = TipoTokenVisualCID::Modificador;
    t.texto = L"MOD.";

    m_linea_actual.tokens.push_back(t);

    LeaveCriticalSection(&m_cs);
}

// CID-06-45 : Borra el último token visual de la línea abierta y devuelve cuál fue eliminado.
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

// CID-06-46 : Cierra la línea actual por asentado y guarda un snapshot para posible reapertura posterior.
void BitacoraCID::CerrarLineaPorAsentado()
{
    EnterCriticalSection(&m_cs);

    // CID-06-47 : Guarda el snapshot completo de la línea asentada para permitir su reapertura posterior.
    m_ultima_linea_asentada_visual = m_linea_actual;
    m_ultima_linea_asentada_logica = m_items;
    m_ultima_linea_asentada_operaciones = m_operaciones_pendientes;
    m_hay_ultima_linea_asentada = (!m_items.empty() || !m_linea_actual.tokens.empty());

    // CID-06-48 : Mueve la línea visual activa al historial de líneas cerradas respetando el máximo configurado.
    if (!m_linea_actual.tokens.empty())
    {
        m_lineas_cerradas.push_back(m_linea_actual);
        LimitarLineasVisuales_NoLock();
    }

    // CID-06-49 : Limpia el estado pendiente y deja abierta una nueva línea vacía tras el asentado.
    m_items.clear();
    m_operaciones_pendientes.clear();
    m_linea_actual.tokens.clear();

    LeaveCriticalSection(&m_cs);
}

// CID-06-50 : Reabre la última línea asentada si no hay nada vivo actualmente en la bitácora.
bool BitacoraCID::ReabrirUltimaLineaAsentada()
{
    EnterCriticalSection(&m_cs);

    // CID-06-51 : Rechaza la reapertura cuando no existe un snapshot válido de la última línea asentada.
    if (!m_hay_ultima_linea_asentada)
    {
        LeaveCriticalSection(&m_cs);
        return false;
    }

    // CID-06-52 : Rechaza la reapertura si ya hay contenido lógico o visual activo en la línea actual.
    if (!m_items.empty() || !m_linea_actual.tokens.empty())
    {
        LeaveCriticalSection(&m_cs);
        return false;
    }

    // CID-06-53 : Restaura el snapshot lógico y visual previamente asentado como línea activa otra vez.
    m_items = m_ultima_linea_asentada_logica;
    m_operaciones_pendientes = m_ultima_linea_asentada_operaciones;
    m_linea_actual = m_ultima_linea_asentada_visual;

    // CID-06-54 : Retira del historial cerrado la línea restaurada si coincide con el último cierre visible.
    if (!m_lineas_cerradas.empty() &&
        LineasVisualesIguales(m_lineas_cerradas.back(), m_ultima_linea_asentada_visual))
    {
        m_lineas_cerradas.pop_back();
    }

    // CID-06-55 : Limpia el snapshot de reapertura para evitar restauraciones repetidas de la misma línea.
    m_hay_ultima_linea_asentada = false;
    m_ultima_linea_asentada_visual.tokens.clear();
    m_ultima_linea_asentada_logica.clear();
    m_ultima_linea_asentada_operaciones.clear();

    LeaveCriticalSection(&m_cs);
    return true;
}

// CID-06-56 : Devuelve una copia del estado visual completo compuesto por líneas cerradas y línea actual.
EstadoVisualBitacoraCID BitacoraCID::ObtenerEstadoVisual() const
{
    EnterCriticalSection(&m_cs);

    EstadoVisualBitacoraCID estado;
    estado.lineas_cerradas = m_lineas_cerradas;
    estado.linea_actual = m_linea_actual;

    LeaveCriticalSection(&m_cs);
    return estado;
}