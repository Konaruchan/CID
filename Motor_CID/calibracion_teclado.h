#pragma once
#include <windows.h>
#include <string>
#include <vector>

// Carga / guarda el archivo de calibración del teclado.
// Devuelven true si todo salió bien.
bool CargarCalibracionTeclado(const std::wstring& rutaJson, std::wstring* error = nullptr);
bool GuardarCalibracionTeclado(const std::wstring& rutaJson, std::wstring* error = nullptr);

// Estado global en memoria
void LimpiarCalibracionTeclado();
bool HayCalibracionTecladoCargada();

// Asignaciones
bool EstablecerAsignacionTeclaCID(const wchar_t* nombreCid, DWORD scanCode);
bool QuitarAsignacionTeclaCID(const wchar_t* nombreCid);

// Consultas
bool ExisteTeclaCIDParaScanCode(DWORD scanCode);
const wchar_t* NombreTeclaCID_PorScanCode(DWORD scanCode);
bool ObtenerScanCodeDeNombreCID(const wchar_t* nombreCid, DWORD& outScanCode);

// Utilidad para UI / debug
std::vector<std::pair<std::wstring, DWORD>> ObtenerAsignacionesCalibradas();