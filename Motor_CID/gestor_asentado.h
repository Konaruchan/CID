#pragma once
#include <windows.h>

class BitacoraCID;

// Arranca / detiene
bool IniciarGestorAsentado(int auto_ms, BitacoraCID* bitacora);
void DetenerGestorAsentado();

// Actividad (para auto-asentado inteligente)
void NotificarActividadCID();

// Pedal CID KEY (espacio)
void EventoTeclaCID_Key(bool presionada);

// Borrar el último asentado (doble toque CID KEY)
void BorrarUltimoAsentado();