#pragma once
#include <string>
#include <windows.h>
#include "bitacora_cid.h"

bool IniciarSuperposicionCID(HINSTANCE hInst);
void DetenerSuperposicionCID();

// Compatibilidad temporal con flujo antiguo
void Superposicion_SetBitacora(const std::wstring& texto);
void Superposicion_SetUltimoAsentado(const std::wstring& texto);

// API buena del panel visual
void Superposicion_SetEstadoVisual(const EstadoVisualBitacoraCID& estado);
void Superposicion_NotificarErrorAcorde();

// API de posicionamiento / visibilidad
void Superposicion_SetVisible(bool visible);
void Superposicion_SetRectAnclaje(const RECT& rc);

// Sustituye el panel grande por aviso mínimo
void Superposicion_SetModoQwerty(bool activo);