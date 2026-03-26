// CID-23-01 : Previene inclusiones múltiples de la interfaz pública del layout visual del teclado CID.
#pragma once

// CID-23-02 : Incluye los tipos base de Windows usados por geometría y color del layout.
#include <windows.h>

// CID-23-03 : Incluye tipos de texto y contenedores usados por la interfaz del layout visual.
#include <string>
#include <vector>

// CID-23-04 : Define una tecla visual del layout con identidad CID, texto, geometría y flags de render.
struct TeclaVisualCID
{
    std::wstring idCid;
    std::wstring textoVisible;
    std::wstring textoOriginal;

    double x = 0.0;
    double y = 0.0;
    double w = 1.0;
    double h = 1.0;

    COLORREF color = RGB(200, 200, 200);

    bool esGris = false;
    bool renderizable = false;
};

// CID-23-05 : Define el layout visual completo del teclado con sus teclas y tamaño total abstracto.
struct LayoutTecladoVisual
{
    std::vector<TeclaVisualCID> teclas;

    double anchoTotal = 0.0;
    double altoTotal = 0.0;
};

// CID-23-06 : Declara la carga y limpieza del layout visual desde su archivo JSON/KLE.
bool CargarLayoutTecladoVisual(const std::wstring& rutaJson, LayoutTecladoVisual& outLayout, std::wstring* error = nullptr);
void LimpiarLayoutTecladoVisual(LayoutTecladoVisual& layout);

// CID-23-07 : Declara el hit-test sobre el dibujo del teclado para localizar teclas por coordenadas.
int BuscarTeclaVisualEnPunto(
    const LayoutTecladoVisual& layout,
    int px, int py,
    int origenX, int origenY,
    int unidadPxW, int unidadPxH);

// CID-23-08 : Declara la búsqueda de una tecla visual por su identificador CID lógico.
int BuscarTeclaVisualPorIdCid(const LayoutTecladoVisual& layout, const std::wstring& idCid);

// CID-23-09 : Declara la conversión de una tecla visual abstracta a su rectángulo de píxeles en pantalla.
RECT RectTeclaVisualAPixeles(
    const TeclaVisualCID& t,
    int origenX, int origenY,
    int unidadPxW, int unidadPxH);