// CID-05-01 : Previene inclusiones múltiples de la interfaz pública del detector de acordes CID.
#pragma once

// CID-05-02 : Incluye los tipos base de Windows usados por la interfaz del detector.
#include <windows.h>

// CID-05-03 : Declara en adelantado los tipos conectables de bitácora y diccionario usados por el detector.
class BitacoraCID;
class DiccionarioCID;

// CID-05-04 : Declara el arranque y la detención del detector de acordes basado en ventana temporal.
bool IniciarDetectorAcorde(int ventana_ms);
void DetenerDetectorAcorde();

// CID-05-05 : Declara la conexión de bitácora y diccionario al flujo interno del detector.
void ConectarBitacora(BitacoraCID* bitacora);
void ConectarDiccionario(const DiccionarioCID* dic);

// CID-05-06 : Declara la recepción de eventos de teclado ya filtrados desde el módulo teclado_cid.
void RecibirEventoTeclaCID(DWORD vk, DWORD scanCode, bool presionada);