// CID-21-01 : Previene inclusiones múltiples de la interfaz pública del módulo de inyección de texto.
#pragma once

// CID-21-02 : Incluye el tipo de texto Unicode usado por la API de inyección.
#include <string>

// CID-21-03 : Declara el control del estado global de inyección propia del sistema CID.
void MarcarInyeccionActiva(bool activa);
bool InyeccionActiva();

// CID-21-04 : Declara la inyección de una cadena Unicode completa en el sistema activo.
bool InyectarTextoUnicode(const std::wstring& texto);