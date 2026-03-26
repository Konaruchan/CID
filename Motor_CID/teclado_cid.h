// CID-03-01 : Previene inclusiones múltiples de la interfaz pública del módulo de teclado CID.
#pragma once

// CID-03-02 : Incluye los tipos base de Windows usados por la interfaz del módulo.
#include <windows.h>

// CID-03-03 : Define el tipo de callback que recibe eventos filtrados de teclas CID.
typedef void (*CallbackTeclaCID)(DWORD vk, DWORD scanCode, bool presionada);

// CID-03-04 : Declara el arranque y la detención del hook global de teclado del sistema CID.
bool IniciarTecladoCID();
void DetenerTecladoCID();

// CID-03-05 : Declara el registro del callback que recibirá eventos del teclado CID.
void RegistrarCallbackTecladoCID(CallbackTeclaCID cb);

// CID-03-06 : Declara la consulta y modificación del modo operativo entre CID y QWERTY.
bool EstaModoCID();
void AlternarModoCID();
void EstablecerModoCID(bool activo);