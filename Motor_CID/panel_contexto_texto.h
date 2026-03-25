#pragma once
#include <windows.h>

// Inicia / detiene el observador de contexto de texto.
bool IniciarPanelContextoTexto();
void DetenerPanelContextoTexto();

// Fuerza una actualización inmediata del contexto.
void ActualizarPanelContextoTextoAhora();

// Se llama cuando el usuario pulsa algo potencialmente escribible.
// El panel no debe aparecer solo por foco/cursor: necesita actividad reciente.
void NotificarActividadEscribiblePanelContextoTexto();