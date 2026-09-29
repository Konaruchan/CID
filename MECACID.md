# MECACID — aprende a escribir en CID

MECACID es el taller de mecanografía integrado en CID 0.3 beta. Usa el mismo diccionario cargado por el motor y tu calibración del teclado. No requiere conexión ni instala componentes adicionales.

## Abrir y empezar

1. Extrae el ZIP completo y ejecuta `Motor_CID.exe`. Completa la calibración si es el primer arranque.
2. En el icono de CID junto al reloj, elige **MECACID — aprender a escribir**.
3. Elige **Teclas**, **Acordes**, **Palabras** o **Frases** y pulsa **Empezar**.
4. Pulsa juntas las teclas resaltadas y suéltalas antes del siguiente acorde. La captura agrupa pulsaciones durante 60 ms, como el motor.
5. Cuando aparezca **Asentar**, pulsa y suelta Espacio. D10 se practica como un paso separado para modificar la última pieza.
6. Prueba sin pistas y usa **Repaso** para volver a los acordes en los que acumulas errores.

El teclado visual muestra la posición lógica CID arriba y la tecla física de tu calibración abajo. No presupone un mapa QWERTY universal. Esc pausa; cambiar de ventana o pasar a otro control también pausa. Los botones se pueden recorrer con Tab cuando la práctica está detenida.

CID se pausa al abrir MECACID. El taller evalúa las teclas localmente y no inyecta texto en otras aplicaciones. Al cerrar permanece pausado: reactívalo desde el icono cuando vuelvas al campo de escritura. Los fragmentos pendientes que tenías antes de abrir el taller se conservan.

## Traductor QWERTY → CID

Pega hasta 512 caracteres en **Traductor** y pulsa **Descomponer**. El camino muestra los acordes, las piezas que producen y cuándo aplicar D10 o asentar. **Anterior / Siguiente** permite estudiar cada paso; **Empezar** practica toda la frase desde el principio después de explorarla.

El traductor busca una composición con el menor número de acciones y, en caso de empate, menos teclas. Las variantes D10 se derivan del propio motor: tildes, signos de apertura y otras transformaciones existentes. No hay un diccionario didáctico paralelo.

La guía normaliza el texto a minúsculas y espacios simples, incluido un espacio después de cada palabra. No reproduce exactamente las mayúsculas y el formato del texto pegado: el motor real aplica sus propias reglas de mayúscula inicial y asentado. Si una palabra no tiene composición completa, aparece un paso **QWERTY** explícito. Durante la práctica escribe literalmente esa palabra y su espacio final. En el motor externo cambia al modo QWERTY con Ctrl+Shift+F11 para escribirla.

## Progreso

Precisión, racha y acordes por minuto describen la sesión actual, excluyendo el tiempo en pausa. Se conservan los ejercicios completados y los aciertos/errores por acorde entre arranques. Un acorde se considera afianzado con al menos cinco aciertos y un 80 % de precisión. El repaso prioriza errores respecto a aciertos.

Los contadores se guardan en `%LOCALAPPDATA%\MECACID\progreso-v1.txt`, mediante reemplazo atómico. No se guarda el texto introducido. Si falla el guardado, el panel de progreso lo indica.

## Diccionario y desarrollo

El archivo distribuido es `Diccionarios/cid0.cid`, copiado del canónico `Motor_CID/cid0.cid`. Para usar cambios del diccionario, reinicia CID. MECACID toma una instantánea del diccionario válido cargado al arrancar.

- `mecacid_model.*`: composición inversa y selección de ejercicios.
- `mecacid.*`: interfaz Win32, práctica local y progreso.
- `tests/regression.cpp`: reproducción de las traducciones con la bitácora real, ejercicios, caracteres sin cobertura y límites.
- `scripts/build.ps1`: compila x64 o Win32, ejecuta regresión y una sesión simulada de MECACID, renderiza las tres vistas y crea el ZIP.

La prueba `Motor_CID.exe --mecacid-smoke` usa una calibración temporal en memoria y no modifica el progreso personal. La simulación no sustituye las pruebas físicas de ergonomía, rollover del teclado, lectores de pantalla o escalados especiales de Windows.

Referencias del sistema: [wiki oficial de CID](https://github.com/Konaruchan/CID/wiki).
