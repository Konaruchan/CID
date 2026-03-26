// CID-15-01 : Previene inclusiones múltiples de la interfaz pública de calibración del teclado CID.
#pragma once

// CID-15-02 : Incluye los tipos base de Windows usados por la API pública de calibración.
#include <windows.h>

// CID-15-03 : Incluye tipos de texto y contenedores usados por la interfaz de calibración.
#include <string>
#include <vector>

// CID-15-04 : Declara la carga y guardado del archivo JSON de calibración del teclado.
bool CargarCalibracionTeclado(const std::wstring& rutaJson, std::wstring* error = nullptr);
bool GuardarCalibracionTeclado(const std::wstring& rutaJson, std::wstring* error = nullptr);

// CID-15-05 : Declara la limpieza y consulta del estado global de calibración cargado en memoria.
void LimpiarCalibracionTeclado();
bool HayCalibracionTecladoCargada();

// CID-15-06 : Declara la creación, sustitución y eliminación de asignaciones nombre CID a scanCode.
bool EstablecerAsignacionTeclaCID(const wchar_t* nombreCid, DWORD scanCode);
bool QuitarAsignacionTeclaCID(const wchar_t* nombreCid);

// CID-15-07 : Declara las consultas de existencia y resolución entre scanCode y nombre CID.
bool ExisteTeclaCIDParaScanCode(DWORD scanCode);
const wchar_t* NombreTeclaCID_PorScanCode(DWORD scanCode);
bool ObtenerScanCodeDeNombreCID(const wchar_t* nombreCid, DWORD& outScanCode);

// CID-15-08 : Declara la obtención ordenada de todas las asignaciones calibradas para UI o depuración.
std::vector<std::pair<std::wstring, DWORD>> ObtenerAsignacionesCalibradas();