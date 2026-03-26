// CID-17-01 : Previene inclusiones múltiples de la interfaz pública del asistente de setup del teclado CID.
#pragma once

// CID-17-02 : Incluye los tipos base de Windows usados por la API del asistente.
#include <windows.h>

// CID-17-03 : Incluye el tipo de texto usado para rutas y mensajes de error del asistente.
#include <string>

// CID-17-04 : Declara la ejecución completa del asistente de calibración y guardado del teclado CID.
bool EjecutarSetupTecladoCID(HINSTANCE hInstance, const std::wstring& rutaCalibrationJson, std::wstring* error = nullptr);