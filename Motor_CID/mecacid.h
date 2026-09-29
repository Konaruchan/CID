#pragma once
#include <windows.h>
#include <string>
class DiccionarioCID;
void MECACID_Inicializar(HINSTANCE instancia, const DiccionarioCID& diccionario);
void MECACID_Abrir();
void MECACID_Cerrar();
bool MECACID_TieneFoco();
bool MECACID_ProcesarTecla(DWORD vk, DWORD scanCode, bool presionada, DWORD flags);
bool MECACID_ProcesarMensaje(MSG* mensaje);
int MECACID_PruebaVisual(HINSTANCE instancia, const DiccionarioCID& diccionario, const std::wstring& directorio);
