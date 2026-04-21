// CID-26-01 : Implementación del contexto global unificado del motor CID.
#include "engine_context.h"

#include "platform.h"

EngineContext& ContextoMotorCID()
{
    static EngineContext ctx;
    if (!ctx.plataforma)
        ctx.plataforma = PlataformaCIDActual();
    return ctx;
}

TecladoContextCID& TCtx()
{
    return ContextoMotorCID().teclado;
}

DetectorContextCID& DCtx()
{
    return ContextoMotorCID().detector;
}

GestorAsentadoContextCID& GCtx()
{
    return ContextoMotorCID().asentado;
}
