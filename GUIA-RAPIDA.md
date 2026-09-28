# CID 0.2 beta — guía rápida

1. Extrae todo el ZIP en una carpeta en la que puedas guardar archivos. No ejecutes el programa dentro del ZIP.
2. Abre `Motor_CID.exe`. El primer arranque muestra el asistente de calibración.
3. Abre el Bloc de notas para practicar. CID empieza activo y cambia la escritura del teclado.
4. Pulsa hasta tres teclas del mapa CID para formar un acorde. Las piezas aparecen en la bitácora antes de asentarse.
5. Mantén Espacio para impedir el asentado automático; suéltalo para asentar. D10 modifica la última pieza.

Haz clic en el icono de CID junto al reloj para **pausar**, **activar**, consultar **ayuda** o **salir**. Puede estar dentro de los iconos ocultos de Windows.

- `Ctrl + Shift + F11`: alternar CID y QWERTY.
- `Ctrl + Shift + F9`: cerrar CID.

Al pausar, las piezas pendientes se conservan y el motor deja de asentarlas automáticamente. Antes de reactivar, vuelve al campo en el que estabas escribiendo. La pausa invalida el borrado del último asentado, porque podrías haber editado el texto con QWERTY.

## Si algo falla

- **Faltan archivos:** vuelve a extraer el ZIP completo. Necesitas `keyboard-layout.json` y `Diccionarios/cid0.cid` junto al ejecutable.
- **No se guarda la calibración:** usa una carpeta con permisos de escritura y comprueba el espacio libre. Un guardado fallido conserva el archivo anterior.
- **No se completa la escritura:** CID conserva las piezas y detiene los reintentos automáticos. Revisa el campo de destino (podría haber llegado parte del texto), corrígelo si procede y pulsa/suelta Espacio para reintentar. Windows puede bloquear la entrada a una aplicación con permisos superiores.
- **Un atajo está ocupado:** utiliza el menú del icono junto al reloj.

Manual del sistema y mapa de teclas: https://github.com/Konaruchan/CID/wiki
