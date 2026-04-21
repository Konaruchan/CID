// CID-28-01 : Implementación thread-safe del bus interno de eventos del motor CID.
#include "event_bus.h"

#include <vector>

struct SuscriptorCID
{
    EventBusCIDSubId id = 0;
    EventBusCIDTipo tipo = EventBusCIDTipo::ActividadEscribible;
    EventBusCIDCallback callback = nullptr;
    void* usuario = nullptr;
};

static CRITICAL_SECTION g_cs;
static bool g_iniciado = false;
static EventBusCIDSubId g_siguiente_id = 1;
static std::vector<SuscriptorCID> g_suscriptores;

bool IniciarEventBusCID()
{
    if (g_iniciado)
        return true;

    InitializeCriticalSection(&g_cs);
    g_iniciado = true;
    g_siguiente_id = 1;
    g_suscriptores.clear();
    return true;
}

void DetenerEventBusCID()
{
    if (!g_iniciado)
        return;

    EnterCriticalSection(&g_cs);
    g_suscriptores.clear();
    LeaveCriticalSection(&g_cs);

    DeleteCriticalSection(&g_cs);
    g_iniciado = false;
}

EventBusCIDSubId SuscribirEventBusCID(EventBusCIDTipo tipo, EventBusCIDCallback cb, void* usuario)
{
    if (!g_iniciado || !cb)
        return 0;

    EnterCriticalSection(&g_cs);
    const EventBusCIDSubId id = g_siguiente_id++;
    g_suscriptores.push_back(SuscriptorCID{ id, tipo, cb, usuario });
    LeaveCriticalSection(&g_cs);
    return id;
}

void DesuscribirEventBusCID(EventBusCIDSubId sub_id)
{
    if (!g_iniciado || sub_id == 0)
        return;

    EnterCriticalSection(&g_cs);
    for (size_t i = 0; i < g_suscriptores.size(); ++i)
    {
        if (g_suscriptores[i].id == sub_id)
        {
            g_suscriptores.erase(g_suscriptores.begin() + (ptrdiff_t)i);
            break;
        }
    }
    LeaveCriticalSection(&g_cs);
}

void PublicarEventBusCID(const EventBusCIDEvento& evento)
{
    if (!g_iniciado)
        return;

    std::vector<SuscriptorCID> snapshot;

    EnterCriticalSection(&g_cs);
    snapshot = g_suscriptores;
    LeaveCriticalSection(&g_cs);

    for (size_t i = 0; i < snapshot.size(); ++i)
    {
        const SuscriptorCID& s = snapshot[i];
        if (s.tipo == evento.tipo && s.callback)
            s.callback(evento, s.usuario);
    }
}
