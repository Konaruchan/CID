// CID-13-01 : Previene inclusiones múltiples de la interfaz pública de la superposición CID.
#pragma once

// CID-13-02 : Incluye los tipos de texto usados por la interfaz pública del panel.
#include <string>

// CID-13-03 : Incluye los tipos base de Windows usados para ventana, instancia y rectángulos.
#include <windows.h>

// CID-13-04 : Incluye la definición del estado visual de bitácora consumido por la superposición.
#include "bitacora_cid.h"

// CID-13-05 : Declara el arranque y la detención de la superposición visual principal del sistema CID.
bool IniciarSuperposicionCID(HINSTANCE hInst);
void DetenerSuperposicionCID();

// CID-13-06 : Declara la compatibilidad temporal con el flujo heredado basado en texto simple.
void Superposicion_SetBitacora(const std::wstring& texto);
void Superposicion_SetUltimoAsentado(const std::wstring& texto);

// CID-13-07 : Declara la API visual moderna basada en estado autoritativo y notificación de error.
void Superposicion_SetEstadoVisual(const EstadoVisualBitacoraCID& estado);
void Superposicion_NotificarErrorAcorde();

// CID-13-08 : Declara la API de visibilidad y posicionamiento del panel respecto al contexto activo.
void Superposicion_SetVisible(bool visible);
void Superposicion_SetRectAnclaje(const RECT& rc);

// CID-13-09 : Declara el cambio al modo visual compacto que sustituye el panel grande por aviso mínimo.
void Superposicion_SetModoQwerty(bool activo);