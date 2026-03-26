// CID-09-01 : Previene inclusiones múltiples de la interfaz pública del gestor de asentado CID.
#pragma once

// CID-09-02 : Incluye los tipos base de Windows usados por la interfaz del gestor.
#include <windows.h>

// CID-09-03 : Declara en adelantado la bitácora conectable usada por el gestor de asentado.
class BitacoraCID;

// CID-09-04 : Declara el arranque y la detención del gestor de asentado con auto-asentado configurable.
bool IniciarGestorAsentado(int auto_ms, BitacoraCID* bitacora);
void DetenerGestorAsentado();

// CID-09-05 : Declara la notificación de actividad CID usada para entrenar el auto-asentado inteligente.
void NotificarActividadCID();

// CID-09-06 : Declara el procesamiento del pedal CID KEY para pulsación y liberación.
void EventoTeclaCID_Key(bool presionada);

// CID-09-07 : Declara el borrado del último asentado recientemente inyectado por el sistema CID.
void BorrarUltimoAsentado();