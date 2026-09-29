# CID 0.3 beta — MECACID

- Taller Win32 integrado con teclado visual calibrado, cinco niveles y práctica local.
- Traductor QWERTY a secuencias CID mínimas, con D10 del motor y alternativas QWERTY explícitas.
- Precisión, racha, ritmo, progreso persistente y repaso de errores.
- Pausa al perder el foco; el entrenamiento no inyecta texto.
- Regresión del traductor sobre el diccionario real y sesiones simuladas con vistas renderizadas en CI.
- Incluye las correcciones de estabilidad de CID 0.2.

# CID 0.2 beta

Esta build conserva el sistema de acordes, la bitácora, D10 y los pedales descritos en la wiki. No inventa ni reasigna acordes: empaqueta `Motor_CID/cid0.cid`, que contiene las últimas correcciones del autor. La copia histórica de `Motor_CID/Diccionarios/cid0.cid` ya no se usa al compilar.

## Correcciones

- El hook comunica la actividad al panel mediante una marca temporal atómica, sin esperar al bloqueo de una consulta de UI Automation a otra aplicación.

- El empaquetado usa el diccionario más reciente; una prueba protege la corrección de `I6+D9 → r` frente a la copia antigua.
- Las piezas pendientes quedan ligadas a la ventana y al control Win32 de origen. Si cambia el destino antes de resolver el acorde o de asentar, se conserva lo pendiente y se pide volver al campo original. El borrado también comprueba el destino.

- Los temporizadores del detector y del asentado se ejecutan en el hilo de mensajes de Windows. Se elimina la acumulación de temporizadores de un solo uso y la ejecución simultánea de operaciones compuestas sobre la bitácora.
- Al pasar a QWERTY se cancela el acorde en curso, se restablecen las teclas/pedal y se pausa el autoasentado conservando las piezas pendientes.
- La liberación de una tecla consumida por CID llega al detector aunque se haya pulsado Ctrl, Alt o Windows mientras estaba abajo.
- Los eventos propios de SendInput llevan una marca individual; no se confunden con pulsaciones físicas concurrentes.
- Una inyección de texto fallida conserva las piezas, no registra un asentado falso y detiene los reintentos automáticos. No se puede deshacer automáticamente una entrega parcial: se pide revisar el destino antes de reintentar.
- El diccionario se carga de forma transaccional. Se rechazan números incompletos, campos extra, tokens vacíos, entradas sin resultado y archivos vacíos; una recarga inválida conserva el contenido anterior.
- La conversión UTF-8 valida los bytes antes de recurrir a CP1252; se admite BOM antes de comentarios.
- La calibración se guarda en un archivo temporal y se reemplaza al completar la escritura, comprobando errores.
- Fuentes C++ normalizadas a UTF-8 y compilación explícita en UTF-8 para conservar acentos.
- Todas las configuraciones copian el diccionario y el layout al lugar que espera el programa. Debug Win32 usa el punto de entrada gráfico correcto.

## Uso y distribución

- Menú en la bandeja para pausar/activar CID, consultar ayuda y salir; se restaura al reiniciar Explorer.
- Aviso visible si no se pueden reservar los atajos y protección contra su repetición automática.
- Guía rápida dentro del ZIP. Compilación de Release con runtime estático.
- Script PowerShell y CI Windows x64/x86: compilar, ejecutar regresiones y generar ZIP más SHA-256.

## Validación

`./scripts/build.ps1 -Platform x64` (o `Win32`) compila y ejecuta las pruebas de diccionario, bitácora, inyección fallida, pausa/reanudación, cancelación/liberación de temporizadores y guardado de calibración. Requiere Visual Studio 2022 con C++ y Windows SDK.

La batería automatizada usa una plataforma simulada para no escribir en otras aplicaciones. La captura física, el asistente de calibración, el comportamiento de UI Automation y la presentación visual requieren una prueba manual en Windows con el teclado del usuario.

La comprobación del destino distingue ventanas y controles Win32. No identifica por sí sola cambios de documento, cursor o campos virtuales dentro de un mismo HWND (por ejemplo, ciertos editores web).
