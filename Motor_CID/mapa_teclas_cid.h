#pragma once
#include <windows.h>

// ---------------------------------
// Identidad lógica CID (por nombre)
// ---------------------------------

// Devuelve true si el nombre CID es válido.
// Ejemplos válidos: I1..I10, C1..C6, D1..D10, CID_KEY, AUX_CID
bool EsNombreTeclaCIDValido(const wchar_t* nombreCid);

// Orden fijo para imprimir acordes consistentes.
// Primero I..., luego C..., luego D...
// CID_KEY y AUX_CID quedan fuera del acorde normal.
int OrdenTeclaCID_PorNombre(const wchar_t* nombreCid);

// Helpers lógicos
bool EsMarcadoraTilde_PorNombre(const wchar_t* nombreCid); // D10 sola
bool EsPedalPrincipal_PorNombre(const wchar_t* nombreCid); // CID_KEY
bool EsPedalAuxiliar_PorNombre(const wchar_t* nombreCid);  // AUX_CID

// ---------------------------------
// Compatibilidad temporal antigua
// ---------------------------------
// Estas funciones antiguas pueden mantenerse mientras migramos,
// pero ya no deben ser la base del sistema.

const wchar_t* NombreTeclaCID(DWORD vk);
int OrdenTeclaCID(DWORD vk);
bool EsTeclaCID(DWORD vk);
bool EsMarcadoraTilde(DWORD vk);