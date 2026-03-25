#pragma once
#include <windows.h>
#include <string>
#include <vector>

struct TeclaVisualCID
{
    // Etiqueta lógica CID si existe:
    // I1..I10, C1..C6, D1..D10, AUX_CID, CID_KEY
    std::wstring idCid;

    // Texto visible resumido para pintar en pantalla
    std::wstring textoVisible;

    // Texto bruto original del JSON/KLE
    std::wstring textoOriginal;

    // Geometría en unidades KLE
    double x = 0.0;
    double y = 0.0;
    double w = 1.0;
    double h = 1.0;

    // Color base original si existe
    COLORREF color = RGB(200, 200, 200);

    // Flags útiles
    bool esGris = false;
    bool renderizable = false;
};

struct LayoutTecladoVisual
{
    std::vector<TeclaVisualCID> teclas;

    double anchoTotal = 0.0;
    double altoTotal = 0.0;
};

bool CargarLayoutTecladoVisual(const std::wstring& rutaJson, LayoutTecladoVisual& outLayout, std::wstring* error = nullptr);

void LimpiarLayoutTecladoVisual(LayoutTecladoVisual& layout);

// Hit-test en coordenadas de pantalla del dibujo.
// Devuelve índice o -1 si no hay tecla.
int BuscarTeclaVisualEnPunto(
    const LayoutTecladoVisual& layout,
    int px, int py,
    int origenX, int origenY,
    int unidadPxW, int unidadPxH);

// Utilidad por ID lógico
int BuscarTeclaVisualPorIdCid(const LayoutTecladoVisual& layout, const std::wstring& idCid);

// Helpers para render
RECT RectTeclaVisualAPixeles(
    const TeclaVisualCID& t,
    int origenX, int origenY,
    int unidadPxW, int unidadPxH);