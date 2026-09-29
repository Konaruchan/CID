# CID 0.3 beta + MECACID — guía rápida

1. Extrae todo el ZIP en una carpeta en la que puedas guardar archivos. No ejecutes el programa dentro del ZIP.
2. Abre `Motor_CID.exe`. El primer arranque muestra el asistente de calibración.
3. Abre **MECACID** desde el icono junto al reloj para practicar en el taller. El motor externo queda pausado. Consulta [MECACID.md](MECACID.md).
4. Para escribir fuera del taller, activa CID desde el icono y abre el Bloc de notas.
5. Pulsa hasta tres teclas del mapa CID para formar un acorde. Las piezas aparecen en la bitácora antes de asentarse.
6. Mantén Espacio para impedir el asentado automático; suéltalo para asentar. D10 modifica la última pieza.

Haz clic en el icono de CID junto al reloj para **pausar**, **activar**, consultar **ayuda** o **salir**. Puede estar dentro de los iconos ocultos de Windows.

- `Ctrl + Shift + F11`: alternar CID y QWERTY.
- `Ctrl + Shift + F9`: cerrar CID.

Al pausar, las piezas pendientes se conservan y el motor deja de asentarlas automáticamente. Antes de reactivar, vuelve al campo en el que estabas escribiendo. La pausa invalida el borrado del último asentado, porque podrías haber editado el texto con QWERTY.

## Si algo falla

- **Destino cambiado:** vuelve al campo original y pulsa/suelta Espacio. CID conserva los fragmentos para evitar enviarlos a otra ventana. Esta protección no distingue todos los campos virtuales de una misma ventana ni los cambios de posición del cursor.
- **Faltan archivos:** vuelve a extraer el ZIP completo. Necesitas `keyboard-layout.json` y `Diccionarios/cid0.cid` junto al ejecutable.
- **No se guarda la calibración:** usa una carpeta con permisos de escritura y comprueba el espacio libre. Un guardado fallido conserva el archivo anterior.
- **No se completa la escritura:** CID conserva las piezas y detiene los reintentos automáticos. Revisa el campo de destino (podría haber llegado parte del texto), corrígelo si procede y pulsa/suelta Espacio para reintentar. Windows puede bloquear la entrada a una aplicación con permisos superiores.
- **Un atajo está ocupado:** utiliza el menú del icono junto al reloj.

Manual del sistema y mapa de teclas: https://github.com/Konaruchan/CID/wiki
