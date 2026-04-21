// CID-27-01 : Previene inclusiones múltiples del contexto unificado del motor CID.
#pragma once

#include <windows.h>
#include <string>

#include "teclado_cid.h"

class BitacoraCID;
class DiccionarioCID;
class IPlatformCID;

struct TecladoContextCID
{
    HHOOK hook = nullptr;
    CallbackTeclaCID callback = nullptr;
    bool modo_cid = true;
    bool vk_abajo[256] = {};
    bool sc_abajo[256] = {};
};

struct DetectorContextCID
{
    CRITICAL_SECTION cs{};
    bool cs_iniciado = false;
    bool presionada[256] = {};
    bool en_ventana[256] = {};
    int ventana_ms = 60;
    bool ventana_activa = false;
    bool esperando_liberacion = false;
    HANDLE timer_queue = nullptr;
    HANDLE timer = nullptr;
    BitacoraCID* bitacora = nullptr;
    const DiccionarioCID* diccionario = nullptr;
    ULONGLONG ultimo_pedal_principal_up = 0;
};

struct GestorAsentadoContextCID
{
    CRITICAL_SECTION cs{};
    bool cs_iniciado = false;
    BitacoraCID* bitacora = nullptr;
    bool pedal_abajo = false;
    int auto_ms = 400;
    HANDLE timer_queue = nullptr;
    HANDLE timer = nullptr;
    ULONGLONG ultimo_tick = 0;
    std::wstring ultimo_inyectado;
    bool debe_mayuscula = true;
    double promedio_ms = 220.0;
    ULONGLONG tick_anterior_ritmo = 0;
};

struct EngineContext
{
    TecladoContextCID teclado;
    DetectorContextCID detector;
    GestorAsentadoContextCID asentado;
    IPlatformCID* plataforma = nullptr;
};

EngineContext& ContextoMotorCID();
TecladoContextCID& TCtx();
DetectorContextCID& DCtx();
GestorAsentadoContextCID& GCtx();
