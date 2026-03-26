// CID-19-01 : Previene inclusiones múltiples de la interfaz pública del panel de contexto de texto.
#pragma once

// CID-19-02 : Incluye los tipos base de Windows usados por la API del observador de contexto.
#include <windows.h>

// CID-19-03 : Declara el arranque y la detención del observador de contexto de texto editable.
bool IniciarPanelContextoTexto();
void DetenerPanelContextoTexto();

// CID-19-04 : Declara la actualización inmediata del contexto sin esperar al temporizador periódico.
void ActualizarPanelContextoTextoAhora();

// CID-19-05 : Declara la notificación de actividad escribible reciente para habilitar la aparición del panel.
void NotificarActividadEscribiblePanelContextoTexto();