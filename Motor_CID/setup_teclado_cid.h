#pragma once
#include <windows.h>
#include <string>

// Ejecuta el asistente de calibración del teclado CID.
// Devuelve true si se guardó correctamente keyboard-calibration.json.
bool EjecutarSetupTecladoCID(HINSTANCE hInstance, const std::wstring& rutaCalibrationJson, std::wstring* error = nullptr);
