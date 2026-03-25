#pragma once
#include <windows.h>

typedef void (*CallbackTeclaCID)(DWORD vk, DWORD scanCode, bool presionada);

// Arranca / detiene hook global
bool IniciarTecladoCID();
void DetenerTecladoCID();

// Callback del detector
void RegistrarCallbackTecladoCID(CallbackTeclaCID cb);

// Estado del modo
bool EstaModoCID();
void AlternarModoCID();
void EstablecerModoCID(bool activo);