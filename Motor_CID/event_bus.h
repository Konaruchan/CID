// CID-29-01 : Previene inclusiones múltiples del bus interno de eventos del motor CID.
#pragma once

#include <windows.h>
#include <string>

// CID-29-02 : Define los tipos de evento internos publicados por los módulos desacoplados.
enum class EventBusCIDTipo
{
    ActividadEscribible,
    AcordeReconocido,
    ErrorAcorde
};

// CID-29-03 : Describe la carga útil estándar para eventos internos del bus CID.
struct EventBusCIDEvento
{
    EventBusCIDTipo tipo = EventBusCIDTipo::ActividadEscribible;
    ULONGLONG timestamp_ms = 0;
    std::wstring texto;
};

using EventBusCIDCallback = void(*)(const EventBusCIDEvento& evento, void* usuario);
using EventBusCIDSubId = unsigned int;

// CID-29-04 : Expone el ciclo de vida y API de suscripción/publicación del bus interno.
bool IniciarEventBusCID();
void DetenerEventBusCID();
EventBusCIDSubId SuscribirEventBusCID(EventBusCIDTipo tipo, EventBusCIDCallback cb, void* usuario);
void DesuscribirEventBusCID(EventBusCIDSubId sub_id);
void PublicarEventBusCID(const EventBusCIDEvento& evento);
