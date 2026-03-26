// CID-25-01 : Previene inclusiones múltiples de la interfaz pública del mapa lógico de teclas CID.
#pragma once

// CID-25-02 : Incluye los tipos base de Windows usados por la compatibilidad heredada por virtual key.
#include <windows.h>

// CID-25-03 : Declara la validación y propiedades lógicas de teclas CID identificadas por nombre.
bool EsNombreTeclaCIDValido(const wchar_t* nombreCid);
int OrdenTeclaCID_PorNombre(const wchar_t* nombreCid);
bool EsMarcadoraTilde_PorNombre(const wchar_t* nombreCid);
bool EsPedalPrincipal_PorNombre(const wchar_t* nombreCid);
bool EsPedalAuxiliar_PorNombre(const wchar_t* nombreCid);

// CID-25-04 : Declara la capa temporal de compatibilidad del sistema antiguo basado en virtual keys.
const wchar_t* NombreTeclaCID(DWORD vk);
int OrdenTeclaCID(DWORD vk);
bool EsTeclaCID(DWORD vk);
bool EsMarcadoraTilde(DWORD vk);