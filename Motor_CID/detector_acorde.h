#pragma once
#include <windows.h>

class BitacoraCID;
class DiccionarioCID;

// Inicia detector de acordes por ventana temporal (ms)
bool IniciarDetectorAcorde(int ventana_ms);
void DetenerDetectorAcorde();

// Conexiones
void ConectarBitacora(BitacoraCID* bitacora);
void ConectarDiccionario(const DiccionarioCID* dic);

// Callback desde teclado_cid
void RecibirEventoTeclaCID(DWORD vk, DWORD scanCode, bool presionada);