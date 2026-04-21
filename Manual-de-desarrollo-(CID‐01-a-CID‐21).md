# Introducción

El manual de desarrollo reúne la documentación técnica de CID. Aquí se documenta el entorno base del proyecto, la estructura real del repositorio, la forma de cargarlo localmente en Visual Studio, el sistema de referencias `CID-XX-YY` y la organización de la documentación por scripts y por bloques internos.

CID está desarrollado en C++ como un proyecto nativo para Windows dentro de Visual Studio. La solución principal del repositorio es `Motor_CID.slnx`, y el contenido real del proyecto se encuentra dentro de la carpeta `Motor_CID`, donde se agrupan los archivos fuente, las cabeceras y los recursos propios del sistema, incluyendo también los diccionarios `.cid`. El repositorio refleja de forma bastante directa la estructura de trabajo real del proyecto y no añade una jerarquía artificial ajena al propio entorno de Visual Studio.

## Entorno base

CID está pensado para desarrollarse en Windows, usando Visual Studio como entorno principal y C++ como lenguaje de implementación. La referencia principal de trabajo es la solución `Motor_CID.slnx`, abierta directamente desde Visual Studio. El proyecto se mantiene como una aplicación nativa de escritorio y su flujo de desarrollo es el habitual de un proyecto de C++ para Windows.

## Requisitos generales

Para trabajar con el proyecto en local se parte de un entorno estándar de desarrollo en Windows. El supuesto general es disponer de Visual Studio correctamente instalado con soporte para desarrollo en C++, junto con las herramientas normales de compilación para escritorio. CID, en su estado actual, no depende de una cadena de preparación especialmente compleja ni de un sistema de paquetes externo que obligue a reconstruir el proyecto antes de abrirlo.

## Estructura del repositorio

La estructura base actual del repositorio es la siguiente:

```text
Motor_CID.slnx
Motor_CID/
.gitignore
.gitattributes
LICENSE
```

La carpeta `Motor_CID` contiene los archivos reales del proyecto. Ahí se encuentran los `.cpp`, los `.h`, los diccionarios `.cid` y el resto de recursos directamente ligados al funcionamiento del sistema. Los archivos `.gitignore`, `.gitattributes` y `LICENSE` forman parte del repositorio, pero no de la lógica interna de CID.

## Cargar el proyecto localmente

Para trabajar con CID en local, el flujo es el habitual de un proyecto de Visual Studio. Basta con clonar o descargar el repositorio, abrir `Motor_CID.slnx` en Visual Studio y trabajar directamente sobre el contenido de la carpeta `Motor_CID`. No existe una fase adicional de preparación compleja ni una estructura paralela que deba reconstruirse antes de compilar. El trabajo diario se realiza directamente sobre la solución y sobre los archivos reales del proyecto.

## Explicación del sistema CID-XX-YY

La documentación técnica de CID utiliza un sistema interno de referencias con formato `CID-XX-YY`. Este sistema sirve para localizar partes concretas del código de forma rápida, precisa y estable, sin depender de búsquedas ambiguas ni de números de línea frágiles.

La parte `XX` identifica un archivo del proyecto dentro del mapa general de equivalencias. La parte `YY` identifica un bloque lógico concreto dentro de ese archivo, siguiendo el orden vertical de aparición de arriba abajo. De este modo, una referencia como `CID-12-49` no señala una línea exacta, sino un bloque reconocible y documentado dentro de la sección <a href="#cid-12">CID-12</a>, correspondiente al archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.cpp"><code>superposicion_cid.cpp</code></a>.

Este sistema se usa tanto en la wiki como en el desarrollo diario del proyecto. Las referencias `CID-XX` y `CID-XX-YY` pueden aparecer en documentación, issues, notas técnicas, revisiones o discusiones internas. Su función es permitir que cualquier parte importante del código pueda señalarse de forma uniforme y estable.

## Equivalencias

La siguiente relación fija la equivalencia oficial entre los archivos principales del proyecto y su identificador `CID-XX`. Esta nomenclatura debe usarse de forma consistente en la wiki, en las issues y en cualquier contexto de desarrollo de CID.

* <a href="#cid-01">CID-01</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/main.cpp"><code>main.cpp</code></a>
* <a href="#cid-02">CID-02</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/teclado_cid.cpp"><code>teclado_cid.cpp</code></a>
* <a href="#cid-03">CID-03</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/teclado_cid.h"><code>teclado_cid.h</code></a>
* <a href="#cid-04">CID-04</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/detector_acorde.cpp"><code>detector_acorde.cpp</code></a>
* <a href="#cid-05">CID-05</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/detector_acorde.h"><code>detector_acorde.h</code></a>
* <a href="#cid-06">CID-06</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/bitacora_cid.cpp"><code>bitacora_cid.cpp</code></a>
* <a href="#cid-07">CID-07</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/bitacora_cid.h"><code>bitacora_cid.h</code></a>
* <a href="#cid-08">CID-08</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/gestor_asentado.cpp"><code>gestor_asentado.cpp</code></a>
* <a href="#cid-09">CID-09</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/gestor_asentado.h"><code>gestor_asentado.h</code></a>
* <a href="#cid-10">CID-10</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/diccionario_cid.cpp"><code>diccionario_cid.cpp</code></a>
* <a href="#cid-11">CID-11</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/diccionario_cid.h"><code>diccionario_cid.h</code></a>
* <a href="#cid-12">CID-12</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.cpp"><code>superposicion_cid.cpp</code></a>
* <a href="#cid-13">CID-13</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.h"><code>superposicion_cid.h</code></a>
* <a href="#cid-14">CID-14</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.cpp"><code>calibracion_teclado.cpp</code></a>
* <a href="#cid-15">CID-15</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a>
* <a href="#cid-16">CID-16</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/setup_teclado_cid.cpp"><code>setup_teclado_cid.cpp</code></a>
* <a href="#cid-17">CID-17</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/setup_teclado_cid.h"><code>setup_teclado_cid.h</code></a>
* <a href="#cid-18">CID-18</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/panel_contexto_texto.cpp"><code>panel_contexto_texto.cpp</code></a>
* <a href="#cid-19">CID-19</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/panel_contexto_texto.h"><code>panel_contexto_texto.h</code></a>
* <a href="#cid-20">CID-20</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/inyeccion_texto.cpp"><code>inyeccion_texto.cpp</code></a>
* <a href="#cid-21">CID-21</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/inyeccion_texto.h"><code>inyeccion_texto.h</code></a>
* <a href="#cid-22">CID-22</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/layout_teclado_visual.cpp"><code>layout_teclado_visual.cpp</code></a>
* <a href="#cid-23">CID-23</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/layout_teclado_visual.h"><code>layout_teclado_visual.h</code></a>
* <a href="#cid-24">CID-24</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/mapa_teclas_cid.cpp"><code>mapa_teclas_cid.cpp</code></a>
* <a href="#cid-25">CID-25</a> — <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/mapa_teclas_cid.h"><code>mapa_teclas_cid.h</code></a>


# Archivos

A continuación se reúnen las secciones individuales de cada archivo principal del proyecto. Cada entrada `CID-XX` corresponde a un archivo concreto de CID y actúa como punto de acceso a su documentación técnica dentro de esta misma página.

En cada caso, la referencia `CID-XX` funciona como identificador documental interno, mientras que el nombre del archivo mantiene su enlace directo al repositorio. Dentro de cada sección de archivo se documentarán después sus bloques internos `CID-XX-YY`, siguiendo la misma lógica de navegación técnica usada en el resto del manual.

## Como leer cada documento

Cada bloque `CID-XX-YY` de la documentación sigue una plantilla fija. La idea de esa plantilla no es adornar el texto ni repetir el código con otras palabras, sino convertir cada bloque del proyecto en una unidad técnica fácil de leer, entender y localizar.

La cabecera del bloque empieza siempre con su identificador completo y una descripción breve. Esa primera línea sirve para fijar exactamente qué parte del archivo se está documentando. Por ejemplo, una entrada como `CID-12-07 — Inicialización del buffer de superposición` indica de forma inmediata dos cosas: primero, que se está hablando del séptimo bloque documentado dentro de <a href="#cid-12">CID-12</a>; y segundo, cuál es la función concreta de ese bloque dentro del archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.cpp"><code>superposicion_cid.cpp</code></a>.

Después de esa cabecera, la plantilla se organiza en cuatro apartados. El apartado “Qué hace” resume la responsabilidad del bloque. No explica todavía cada detalle interno, sino que deja claro para qué existe ese fragmento de código dentro del conjunto. El apartado “Cómo funciona” describe el comportamiento interno del bloque de forma un poco más desarrollada, explicando el orden general de sus pasos, validaciones, decisiones o efectos. El apartado “Pseudocódigo” traduce esa lógica a una secuencia corta y legible en español, para que el lector pueda captar la mecánica del bloque sin tener que leer inmediatamente la implementación real. Por último, el apartado “Relaciones” conecta ese bloque con otras partes documentadas del proyecto, indicando qué otros `CID-XX-YY` usa, de cuáles depende o desde cuáles suele ser llamado.

## CID-01

La referencia <a href="#cid-01">CID-01</a> corresponde al archivo <code>main.cpp</code>. Este archivo actúa como punto de entrada del motor CID. Su responsabilidad principal es preparar el entorno de arranque, validar los recursos base necesarios, iniciar los módulos principales del sistema y mantener el bucle principal de mensajes de Windows hasta el cierre del proceso.

Dentro de <a href="#cid-01">CID-01</a> también se centraliza la secuencia de apagado ordenado del motor. Por eso aquí se concentran tanto la resolución de rutas críticas como el arranque de la superposición, el panel contextual, el teclado, el detector de acordes, el gestor de asentado y el diccionario base. En esta versión, además, <a href="#cid-01">CID-01</a> incorpora el control de instancia única del proceso para impedir que varias copias del motor se ejecuten a la vez y provoquen comportamientos erráticos en la captura e inyección de entrada.

### Índice interno de bloques

* <a href="#cid-01-01">CID-01-01</a>
* <a href="#cid-01-02">CID-01-02</a>
* <a href="#cid-01-03">CID-01-03</a>
* <a href="#cid-01-04">CID-01-04</a>
* <a href="#cid-01-05">CID-01-05</a>
* <a href="#cid-01-06">CID-01-06</a>
* <a href="#cid-01-07">CID-01-07</a>
* <a href="#cid-01-08">CID-01-08</a>
* <a href="#cid-01-09">CID-01-09</a>
* <a href="#cid-01-10">CID-01-10</a>
* <a href="#cid-01-11">CID-01-11</a>
* <a href="#cid-01-12">CID-01-12</a>
* <a href="#cid-01-13">CID-01-13</a>
* <a href="#cid-01-14">CID-01-14</a>
* <a href="#cid-01-15">CID-01-15</a>
* <a href="#cid-01-16">CID-01-16</a>
* <a href="#cid-01-17">CID-01-17</a>
* <a href="#cid-01-18">CID-01-18</a>
* <a href="#cid-01-19">CID-01-19</a>
* <a href="#cid-01-20">CID-01-20</a>
* <a href="#cid-01-21">CID-01-21</a>
* <a href="#cid-01-22">CID-01-22</a>
* <a href="#cid-01-23">CID-01-23</a>
* <a href="#cid-01-24">CID-01-24</a>
* <a href="#cid-01-25">CID-01-25</a>
* <a href="#cid-01-26">CID-01-26</a>
* <a href="#cid-01-27">CID-01-27</a>
* <a href="#cid-01-28">CID-01-28</a>
* <a href="#cid-01-29">CID-01-29</a>
* <a href="#cid-01-30">CID-01-30</a>
* <a href="#cid-01-31">CID-01-31</a>
* <a href="#cid-01-32">CID-01-32</a>
* <a href="#cid-01-33">CID-01-33</a>
* <a href="#cid-01-34">CID-01-34</a>
* <a href="#cid-01-35">CID-01-35</a>
* <a href="#cid-01-36">CID-01-36</a>
* <a href="#cid-01-37">CID-01-37</a>
* <a href="#cid-01-38">CID-01-38</a>
* <a href="#cid-01-39">CID-01-39</a>
* <a href="#cid-01-40">CID-01-40</a>
* <a href="#cid-01-41">CID-01-41</a>
* <a href="#cid-01-42">CID-01-42</a>
* <a href="#cid-01-43">CID-01-43</a>
* <a href="#cid-01-44">CID-01-44</a>
* <a href="#cid-01-45">CID-01-45</a>
* <a href="#cid-01-46">CID-01-46</a>
* <a href="#cid-01-47">CID-01-47</a>

---

### <a id="cid-01-01"></a>CID-01-01

**Qué hace:**
Incluye las cabeceras base del sistema y de la biblioteca estándar que necesita el punto de entrada del motor para trabajar con Windows, cadenas y contenedores simples.

**Cómo funciona:**
Este bloque habilita el acceso a la API Win32 y a tipos estándar usados en el resto del archivo, como `std::wstring`. No contiene lógica ejecutable, pero define dependencias mínimas necesarias para compilar el arranque del motor.

**Pseudocódigo:**

```text id="cid0101"
incluir API de Windows
incluir soporte de cadenas
incluir soporte de vectores
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-01">CID-01</a>.
* Da soporte indirecto a <a href="#cid-01-05">CID-01-05</a>, <a href="#cid-01-06">CID-01-06</a>, <a href="#cid-01-07">CID-01-07</a> y al resto de bloques con lógica Win32.

---

### <a id="cid-01-02"></a>CID-01-02

**Qué hace:**
Incluye los módulos internos del proyecto que el punto de entrada necesita para ensamblar el motor completo.

**Cómo funciona:**
Este bloque conecta `main.cpp` con los subsistemas principales: teclado, detector de acordes, bitácora, gestor de asentado, diccionario, superposición, calibración, setup y panel contextual. A partir de estas inclusiones, el punto de entrada puede iniciar, detener y conectar dichos componentes.

**Pseudocódigo:**

```text id="cid0102"
incluir módulos internos del motor
habilitar acceso a arranque, parada y conexión entre subsistemas
```

**Relaciones:**

* Da acceso a <a href="#cid-01-12">CID-01-12</a>, <a href="#cid-01-18">CID-01-18</a>, <a href="#cid-01-19">CID-01-19</a>, <a href="#cid-01-24">CID-01-24</a>, <a href="#cid-01-25">CID-01-25</a>, <a href="#cid-01-34">CID-01-34</a>, <a href="#cid-01-35">CID-01-35</a>, <a href="#cid-01-36">CID-01-36</a> y <a href="#cid-01-37">CID-01-37</a>.

---

### <a id="cid-01-03"></a>CID-01-03

**Qué hace:**
Define los identificadores internos usados para registrar y diferenciar las dos hotkeys globales principales del motor.

**Cómo funciona:**
Se asignan dos constantes enteras estables que luego se usan al registrar las hotkeys y al interpretar los mensajes `WM_HOTKEY` en el bucle principal. De este modo, cada combinación de teclado puede mapearse a una acción distinta sin ambigüedad.

**Pseudocódigo:**

```text id="cid0103"
definir ID de hotkey de salida
definir ID de hotkey de cambio de modo
```

**Relaciones:**

* Usado por <a href="#cid-01-12">CID-01-12</a>, <a href="#cid-01-16">CID-01-16</a>, <a href="#cid-01-17">CID-01-17</a>, <a href="#cid-01-41">CID-01-41</a>, <a href="#cid-01-42">CID-01-42</a> y <a href="#cid-01-45">CID-01-45</a>.

---

### <a id="cid-01-04"></a>CID-01-04

**Qué hace:**
Define el nombre global del mutex que impide ejecutar varias instancias simultáneas del motor.

**Cómo funciona:**
Declara una cadena constante usada al crear el mutex de instancia única. Ese nombre actúa como identidad compartida del proceso en el sistema local, permitiendo detectar si ya existe otra instancia activa del motor.

**Pseudocódigo:**

```text id="cid0104"
definir nombre global del mutex de instancia única
```

**Relaciones:**

* Es usado por <a href="#cid-01-15">CID-01-15</a>.
* Introduce la política de instancia única dentro de <a href="#cid-01">CID-01</a>.

---

### <a id="cid-01-05"></a>CID-01-05

**Qué hace:**
Envía una línea de texto al depurador de Windows para registrar actividad interna.

**Cómo funciona:**
Recibe una cadena ancha, la envía mediante `OutputDebugStringW` y añade un salto de línea como segunda escritura. Con esto unifica el registro básico del archivo sin repetir código de depuración cada vez.

**Pseudocódigo:**

```text id="cid0105"
enviar texto al depurador
enviar salto de línea
```

**Relaciones:**

* Usado por <a href="#cid-01-14">CID-01-14</a>, <a href="#cid-01-23">CID-01-23</a>, <a href="#cid-01-26">CID-01-26</a>, <a href="#cid-01-31">CID-01-31</a>, <a href="#cid-01-41">CID-01-41</a> y <a href="#cid-01-47">CID-01-47</a>.

---

### <a id="cid-01-06"></a>CID-01-06

**Qué hace:**
Comprueba si una ruta apunta a un archivo existente y descarta directorios.

**Cómo funciona:**
Consulta los atributos del sistema de archivos con `GetFileAttributesW`. Si la consulta falla, la ruta no existe. Si la consulta tiene éxito pero el atributo indica directorio, la ruta tampoco se acepta como archivo válido.

**Pseudocódigo:**

```text id="cid0106"
leer atributos de la ruta
si la ruta no existe:
    devolver falso
si la ruta es un directorio:
    devolver falso
devolver verdadero
```

**Relaciones:**

* Usado por <a href="#cid-01-09">CID-01-09</a>, <a href="#cid-01-22">CID-01-22</a> y <a href="#cid-01-24">CID-01-24</a>.

---

### <a id="cid-01-07"></a>CID-01-07

**Qué hace:**
Obtiene el directorio donde se encuentra el ejecutable actual del motor.

**Cómo funciona:**
Obtiene la ruta completa del ejecutable actual con `GetModuleFileNameW`, la convierte en `std::wstring` y elimina el nombre del archivo para quedarse solo con el directorio contenedor. Esa carpeta sirve como base para construir rutas relativas a recursos críticos.

**Pseudocódigo:**

```text id="cid0107"
obtener ruta completa del ejecutable
quedarse con el directorio padre
devolver directorio
```

**Relaciones:**

* Usado por <a href="#cid-01-09">CID-01-09</a>, <a href="#cid-01-10">CID-01-10</a>, <a href="#cid-01-11">CID-01-11</a> y <a href="#cid-01-30">CID-01-30</a>.

---

### <a id="cid-01-08"></a>CID-01-08

**Qué hace:**
Une dos fragmentos de ruta garantizando un separador válido entre ambos.

**Cómo funciona:**
Si la primera parte está vacía devuelve directamente la segunda. Si la primera ya termina en barra o contrabarra, concatena sin añadir nada. En caso contrario inserta una contrabarra intermedia.

**Pseudocódigo:**

```text id="cid0108"
si la primera parte está vacía:
    devolver la segunda
si la primera parte ya termina en separador:
    devolver concatenación directa
devolver primera parte + separador + segunda parte
```

**Relaciones:**

* Usado por <a href="#cid-01-09">CID-01-09</a>, <a href="#cid-01-10">CID-01-10</a> y <a href="#cid-01-11">CID-01-11</a>.

---

### <a id="cid-01-09"></a>CID-01-09

**Qué hace:**
Resuelve la ruta del diccionario base `cid0.cid` y devuelve también el trazado probado.

**Cómo funciona:**
Parte del directorio del ejecutable, construye la ruta `Diccionarios\cid0.cid` y la escribe en el buffer de trazado si este existe. Después comprueba si el archivo está presente. Si lo está, devuelve la ruta válida; si no, devuelve una cadena vacía.

**Pseudocódigo:**

```text id="cid0109"
obtener directorio del ejecutable
construir ruta a Diccionarios/cid0.cid
si hay buffer de trazado:
    guardar ruta probada
si el archivo existe:
    devolver ruta
devolver vacío
```

**Relaciones:**

* Usa <a href="#cid-01-06">CID-01-06</a>, <a href="#cid-01-07">CID-01-07</a> y <a href="#cid-01-08">CID-01-08</a>.
* Es llamado desde <a href="#cid-01-29">CID-01-29</a>.

---

### <a id="cid-01-10"></a>CID-01-10

**Qué hace:**
Resuelve la ruta del archivo de layout visual del teclado CID.

**Cómo funciona:**
Toma como base el directorio del ejecutable y concatena el nombre del archivo de layout. No valida su existencia; solo resuelve la ubicación esperada.

**Pseudocódigo:**

```text id="cid0110"
obtener directorio del ejecutable
unir con keyboard-layout.json
devolver ruta
```

**Relaciones:**

* Usa <a href="#cid-01-07">CID-01-07</a> y <a href="#cid-01-08">CID-01-08</a>.
* Es llamado desde <a href="#cid-01-21">CID-01-21</a>.

---

### <a id="cid-01-11"></a>CID-01-11

**Qué hace:**
Resuelve la ruta del archivo de calibración persistente del teclado CID.

**Cómo funciona:**
Usa el directorio del ejecutable como base y concatena el nombre del archivo de calibración persistente. Su cometido es centralizar la ruta para evitar duplicación dentro del arranque.

**Pseudocódigo:**

```text id="cid0111"
obtener directorio del ejecutable
unir con keyboard-calibration.json
devolver ruta
```

**Relaciones:**

* Usa <a href="#cid-01-07">CID-01-07</a> y <a href="#cid-01-08">CID-01-08</a>.
* Es llamado desde <a href="#cid-01-21">CID-01-21</a>.

---

### <a id="cid-01-12"></a>CID-01-12

**Qué hace:**
Ejecuta la limpieza de emergencia deteniendo módulos activos, liberando hotkeys y soltando el mutex.

**Cómo funciona:**
Detiene explícitamente los subsistemas que pueden haber quedado activos, libera las hotkeys si llegaron a registrarse y cierra el handle del mutex de instancia única si existe. Así evita dejar recursos vivos cuando el arranque falla a mitad de camino.

**Pseudocódigo:**

```text id="cid0112"
detener teclado
detener detector
detener gestor de asentado
detener panel contextual
detener superposición
si la hotkey de salida existe:
    liberarla
si la hotkey de cambio de modo existe:
    liberarla
si existe mutex de instancia:
    cerrarlo
```

**Relaciones:**

* Es usado por <a href="#cid-01-22">CID-01-22</a>, <a href="#cid-01-24">CID-01-24</a>, <a href="#cid-01-25">CID-01-25</a>, <a href="#cid-01-30">CID-01-30</a>, <a href="#cid-01-33">CID-01-33</a>, <a href="#cid-01-34">CID-01-34</a>, <a href="#cid-01-35">CID-01-35</a> y <a href="#cid-01-37">CID-01-37</a>.
* Amplía la limpieza fatal anterior incorporando el recurso de instancia única.

---

### <a id="cid-01-13"></a>CID-01-13

**Qué hace:**
Define el punto de entrada real del proceso y concentra toda la secuencia de arranque, operación y cierre del motor CID.

**Cómo funciona:**
La función `wWinMain` ejecuta el flujo completo del proceso: registra trazas iniciales, asegura instancia única, intenta reservar hotkeys, inicia la UI de soporte, comprueba recursos obligatorios, ejecuta setup si hace falta, carga calibración y diccionario, arranca los subsistemas principales, entra en el bucle de mensajes y, al salir, detiene y libera todo de forma ordenada.

**Pseudocódigo:**

```text id="cid0113"
registrar estado inicial
asegurar instancia única
registrar hotkeys
iniciar superposición y panel
validar layout y calibración
cargar bitácora y diccionario
iniciar gestor, detector y teclado
entrar en bucle de mensajes
al salir:
    detener módulos
    liberar hotkeys
    cerrar mutex
    terminar
```

**Relaciones:**

* Contiene internamente <a href="#cid-01-14">CID-01-14</a> a <a href="#cid-01-47">CID-01-47</a>.
* Usa como helpers previos <a href="#cid-01-05">CID-01-05</a> a <a href="#cid-01-12">CID-01-12</a>.

---

### <a id="cid-01-14"></a>CID-01-14

**Qué hace:**
Emite las primeras trazas de depuración del proceso para dejar constancia del arranque y de los atajos principales disponibles.

**Cómo funciona:**
Llama varias veces al helper de log con mensajes fijos que describen el inicio del motor, la hotkey de salida, la hotkey de cambio de modo y la ruta usual para ver la salida de depuración.

**Pseudocódigo:**

```text id="cid0114"
escribir mensaje de arranque
escribir hotkey de salida
escribir hotkey de cambio de modo
escribir dónde ver logs
```

**Relaciones:**

* Usa <a href="#cid-01-05">CID-01-05</a>.
* Está dentro de <a href="#cid-01-13">CID-01-13</a>.

---

### <a id="cid-01-15"></a>CID-01-15

**Qué hace:**
Crea el mutex de instancia única y aborta si ya existe otro Motor CID activo.

**Cómo funciona:**
Llama a `CreateMutexW` con el nombre global del motor. Si ni siquiera puede crear el mutex, muestra un error y termina. Si el mutex existe pero `GetLastError()` informa `ERROR_ALREADY_EXISTS`, concluye que ya hay otra instancia abierta, informa al usuario y sale sin arrancar una copia nueva.

**Pseudocódigo:**

```text id="cid0115"
crear mutex de instancia única
si no se pudo crear:
    mostrar error
    salir con error
si el mutex ya existía:
    informar que el motor ya está abierto
    cerrar mutex
    salir normalmente
```

**Relaciones:**

* Usa <a href="#cid-01-04">CID-01-04</a>.
* Precede a <a href="#cid-01-16">CID-01-16</a>.
* Es el bloque nuevo que evita las múltiples instancias simultáneas del motor.

---

### <a id="cid-01-16"></a>CID-01-16

**Qué hace:**
Registra la hotkey global de salida y avisa si no se puede reservar.

**Cómo funciona:**
Llama a `RegisterHotKey` con el identificador de salida y la combinación `Ctrl + Shift + F9`. Guarda el resultado en una bandera booleana y, si falla, registra una advertencia pero no aborta el arranque.

**Pseudocódigo:**

```text id="cid0116"
intentar registrar hotkey de salida
si falla:
    escribir advertencia
```

**Relaciones:**

* Usa <a href="#cid-01-03">CID-01-03</a> y <a href="#cid-01-05">CID-01-05</a>.
* Su resultado se usa en <a href="#cid-01-12">CID-01-12</a>, <a href="#cid-01-18">CID-01-18</a>, <a href="#cid-01-19">CID-01-19</a>, <a href="#cid-01-41">CID-01-41</a> y <a href="#cid-01-45">CID-01-45</a>.

---

### <a id="cid-01-17"></a>CID-01-17

**Qué hace:**
Registra la hotkey global de cambio de modo y avisa si no se puede reservar.

**Cómo funciona:**
Registra la hotkey `Ctrl + Shift + F11`, almacena el resultado y, si no puede reservarla, emite una advertencia pero permite que el motor siga arrancando.

**Pseudocódigo:**

```text id="cid0117"
intentar registrar hotkey de cambio de modo
si falla:
    escribir advertencia
```

**Relaciones:**

* Usa <a href="#cid-01-03">CID-01-03</a> y <a href="#cid-01-05">CID-01-05</a>.
* Su resultado se usa en <a href="#cid-01-12">CID-01-12</a>, <a href="#cid-01-18">CID-01-18</a>, <a href="#cid-01-19">CID-01-19</a>, <a href="#cid-01-42">CID-01-42</a> y <a href="#cid-01-45">CID-01-45</a>.

---

### <a id="cid-01-18"></a>CID-01-18

**Qué hace:**
Inicia la superposición visual principal y aborta si no puede arrancar.

**Cómo funciona:**
Invoca `IniciarSuperposicionCID` con la instancia del proceso. Si el arranque falla, muestra un mensaje de error, libera las hotkeys que se hubieran reservado, cierra el mutex y termina el proceso con código de error.

**Pseudocódigo:**

```text id="cid0118"
si no se puede iniciar la superposición:
    mostrar error
    liberar hotkeys si existen
    cerrar mutex
    salir con error
```

**Relaciones:**

* Usa resultados de <a href="#cid-01-16">CID-01-16</a> y <a href="#cid-01-17">CID-01-17</a>.
* Depende de que <a href="#cid-01-15">CID-01-15</a> haya permitido continuar.

---

### <a id="cid-01-19"></a>CID-01-19

**Qué hace:**
Inicia el panel contextual de texto y revierte la superposición si falla.

**Cómo funciona:**
Llama a `IniciarPanelContextoTexto`. Si falla, muestra un mensaje de error, detiene la superposición ya iniciada, libera hotkeys, cierra el mutex y termina el proceso con error.

**Pseudocódigo:**

```text id="cid0119"
si no se puede iniciar el panel contextual:
    mostrar error
    detener superposición
    liberar hotkeys si existen
    cerrar mutex
    salir con error
```

**Relaciones:**

* Depende de que <a href="#cid-01-18">CID-01-18</a> haya tenido éxito.
* Usa el mismo patrón de liberación temprana que el resto del arranque.

---

### <a id="cid-01-20"></a>CID-01-20

**Qué hace:**
Inicializa el estado visual base de la superposición según el modo activo actual.

**Cómo funciona:**
Inicializa la bitácora visual como vacía, actualiza el texto del último asentado con el modo actual y sincroniza la bandera visual de modo QWERTY según el estado interno del sistema.

**Pseudocódigo:**

```text id="cid0120"
mostrar bitácora vacía
mostrar modo actual
actualizar bandera visual de modo QWERTY
```

**Relaciones:**

* Usa funciones de la superposición.
* Prepara el estado antes de <a href="#cid-01-21">CID-01-21</a>.

---

### <a id="cid-01-21"></a>CID-01-21

**Qué hace:**
Resuelve las rutas de layout visual y calibración necesarias para el sistema de teclado.

**Cómo funciona:**
Llama a los helpers de resolución de rutas y guarda los resultados en constantes locales que se reutilizan en los bloques posteriores de validación, setup y carga de calibración.

**Pseudocódigo:**

```text id="cid0121"
resolver ruta del layout
resolver ruta de la calibración
guardar ambas rutas
```

**Relaciones:**

* Usa <a href="#cid-01-10">CID-01-10</a> y <a href="#cid-01-11">CID-01-11</a>.
* Alimenta a <a href="#cid-01-22">CID-01-22</a> a <a href="#cid-01-26">CID-01-26</a>.

---

### <a id="cid-01-22"></a>CID-01-22

**Qué hace:**
Verifica que exista el layout visual del teclado antes de continuar con setup o calibración.

**Cómo funciona:**
Valida la ruta resuelta del layout. Si el archivo falta, construye un mensaje detallado con la ruta esperada, informa al usuario y ejecuta una limpieza fatal antes de abortar el arranque.

**Pseudocódigo:**

```text id="cid0122"
si no existe el layout:
    construir mensaje con ruta esperada
    mostrar error
    ejecutar limpieza fatal
    salir con error
```

**Relaciones:**

* Usa <a href="#cid-01-06">CID-01-06</a>, <a href="#cid-01-12">CID-01-12</a> y datos de <a href="#cid-01-21">CID-01-21</a>.
* Precede a <a href="#cid-01-23">CID-01-23</a>.

---

### <a id="cid-01-23"></a>CID-01-23

**Qué hace:**
Registra la ruta detectada del layout visual del teclado.

**Cómo funciona:**
Compone un mensaje con la ruta ya validada y lo envía al helper de log. Sirve como traza útil para inspección y diagnóstico del arranque.

**Pseudocódigo:**

```text id="cid0123"
construir mensaje con ruta de layout
escribir log
```

**Relaciones:**

* Usa <a href="#cid-01-05">CID-01-05</a>.
* Se apoya en la ruta validada por <a href="#cid-01-22">CID-01-22</a>.

---

### <a id="cid-01-24"></a>CID-01-24

**Qué hace:**
Ejecuta el setup de teclado si aún no existe un archivo de calibración persistido.

**Cómo funciona:**
Comprueba si `keyboard-calibration.json` existe. Si no existe, llama al módulo de setup con la ruta objetivo de calibración y un buffer de error. Si el setup falla, informa al usuario, ejecuta limpieza fatal y aborta.

**Pseudocódigo:**

```text id="cid0124"
si no existe archivo de calibración:
    ejecutar setup de teclado
    si falla:
        mostrar error
        ejecutar limpieza fatal
        salir con error
```

**Relaciones:**

* Usa <a href="#cid-01-06">CID-01-06</a>, <a href="#cid-01-12">CID-01-12</a> y datos de <a href="#cid-01-21">CID-01-21</a>.
* Precede a <a href="#cid-01-25">CID-01-25</a>.

---

### <a id="cid-01-25"></a>CID-01-25

**Qué hace:**
Carga la calibración de teclado desde disco y aborta si el archivo es inválido o inaccesible.

**Cómo funciona:**
Llama a `CargarCalibracionTeclado` con la ruta de calibración y un buffer de error. Si la operación falla, construye un mensaje completo con ruta y motivo, lo muestra y ejecuta la limpieza fatal.

**Pseudocódigo:**

```text id="cid0125"
intentar cargar calibración
si falla:
    construir mensaje con ruta y error
    mostrar error
    ejecutar limpieza fatal
    salir con error
```

**Relaciones:**

* Usa <a href="#cid-01-12">CID-01-12</a> y datos de <a href="#cid-01-21">CID-01-21</a>.
* Precede a <a href="#cid-01-26">CID-01-26</a>.

---

### <a id="cid-01-26"></a>CID-01-26

**Qué hace:**
Registra la ruta desde la que se cargó correctamente la calibración del teclado.

**Cómo funciona:**
Compone un mensaje con la ruta de calibración y lo envía al helper de log. Da visibilidad al origen efectivo de la configuración cargada.

**Pseudocódigo:**

```text id="cid0126"
construir mensaje con ruta de calibración
escribir log
```

**Relaciones:**

* Usa <a href="#cid-01-05">CID-01-05</a>.
* Se apoya en el éxito de <a href="#cid-01-25">CID-01-25</a>.

---

### <a id="cid-01-27"></a>CID-01-27

**Qué hace:**
Construye la bitácora principal y ajusta sus límites de historial y líneas visibles.

**Cómo funciona:**
Instancia un objeto `BitacoraCID`, ajusta el máximo de entradas almacenadas y el número máximo de líneas visibles para la representación en pantalla.

**Pseudocódigo:**

```text id="cid0127"
crear bitácora
configurar máximo de historial
configurar máximo de líneas visuales
```

**Relaciones:**

* Su objeto se usa en <a href="#cid-01-28">CID-01-28</a>, <a href="#cid-01-34">CID-01-34</a> y <a href="#cid-01-36">CID-01-36</a>.

---

### <a id="cid-01-28"></a>CID-01-28

**Qué hace:**
Sincroniza la superposición con el estado visual inicial vacío de la bitácora.

**Cómo funciona:**
Consulta el estado visual actual de la bitácora y lo envía a la superposición para que ambos sistemas arranquen sincronizados desde el principio.

**Pseudocódigo:**

```text id="cid0128"
obtener estado visual de la bitácora
enviarlo a la superposición
```

**Relaciones:**

* Depende de <a href="#cid-01-27">CID-01-27</a>.
* Prepara la UI antes de la carga del diccionario.

---

### <a id="cid-01-29"></a>CID-01-29

**Qué hace:**
Resuelve la ruta del diccionario base `cid0.cid` y guarda el trazado probado.

**Cómo funciona:**
Declara buffers locales de trazado y ruta, y delega la resolución al helper específico del diccionario base.

**Pseudocódigo:**

```text id="cid0129"
crear buffer de trazado
resolver ruta de cid0
guardar ruta y trazado
```

**Relaciones:**

* Usa <a href="#cid-01-09">CID-01-09</a>.
* Sus resultados se usan en <a href="#cid-01-30">CID-01-30</a>, <a href="#cid-01-31">CID-01-31</a> y <a href="#cid-01-33">CID-01-33</a>.

---

### <a id="cid-01-30"></a>CID-01-30

**Qué hace:**
Aborta el arranque si no se localiza el diccionario base requerido por el motor.

**Cómo funciona:**
Comprueba si la ruta resuelta del diccionario está vacía. Si lo está, construye un mensaje detallado con el directorio del ejecutable y el trazado intentado, lo muestra y ejecuta limpieza fatal.

**Pseudocódigo:**

```text id="cid0130"
si la ruta del diccionario está vacía:
    construir mensaje con directorio y trazado
    mostrar error
    ejecutar limpieza fatal
    salir con error
```

**Relaciones:**

* Usa datos de <a href="#cid-01-29">CID-01-29</a>, <a href="#cid-01-07">CID-01-07</a> y <a href="#cid-01-12">CID-01-12</a>.
* Precede a <a href="#cid-01-31">CID-01-31</a> y <a href="#cid-01-33">CID-01-33</a>.

---

### <a id="cid-01-31"></a>CID-01-31

**Qué hace:**
Registra la ruta válida encontrada para el diccionario base del sistema.

**Cómo funciona:**
Compone un mensaje informativo a partir de la ruta válida y lo envía al sistema de log.

**Pseudocódigo:**

```text id="cid0131"
construir mensaje con ruta del diccionario
escribir log
```

**Relaciones:**

* Usa <a href="#cid-01-05">CID-01-05</a>.
* Se apoya en el éxito de <a href="#cid-01-30">CID-01-30</a>.

---

### <a id="cid-01-32"></a>CID-01-32

**Qué hace:**
Instancia el diccionario CID y prepara el buffer de error de carga.

**Cómo funciona:**
Instancia `DiccionarioCID` y declara una cadena ancha para recibir mensajes de error procedentes del proceso de carga desde archivo.

**Pseudocódigo:**

```text id="cid0132"
crear objeto diccionario
crear buffer de error
```

**Relaciones:**

* Precede a <a href="#cid-01-33">CID-01-33</a> y <a href="#cid-01-36">CID-01-36</a>.

---

### <a id="cid-01-33"></a>CID-01-33

**Qué hace:**
Carga el diccionario base desde archivo y aborta si el contenido no es válido.

**Cómo funciona:**
Invoca `CargarDesdeArchivo` sobre el objeto diccionario. Si la operación falla, muestra un mensaje con la ruta y el error recibido, ejecuta limpieza fatal y termina el proceso.

**Pseudocódigo:**

```text id="cid0133"
intentar cargar diccionario desde archivo
si falla:
    construir mensaje con ruta y error
    mostrar error
    ejecutar limpieza fatal
    salir con error
```

**Relaciones:**

* Depende de <a href="#cid-01-29">CID-01-29</a> y <a href="#cid-01-32">CID-01-32</a>.
* Usa <a href="#cid-01-12">CID-01-12</a>.

---

### <a id="cid-01-34"></a>CID-01-34

**Qué hace:**
Inicia el gestor de asentado con retardo base y acceso a la bitácora principal.

**Cómo funciona:**
Llama a `IniciarGestorAsentado` con un retardo base de 400 ms y la referencia a la bitácora. Si el módulo no puede iniciarse, muestra un error, ejecuta limpieza fatal y aborta.

**Pseudocódigo:**

```text id="cid0134"
iniciar gestor de asentado con retardo y bitácora
si falla:
    mostrar error
    ejecutar limpieza fatal
    salir con error
```

**Relaciones:**

* Usa la bitácora creada en <a href="#cid-01-27">CID-01-27</a>.
* Precede a <a href="#cid-01-35">CID-01-35</a>.

---

### <a id="cid-01-35"></a>CID-01-35

**Qué hace:**
Inicia el detector de acordes con su ventana temporal de reconocimiento.

**Cómo funciona:**
Llama a `IniciarDetectorAcorde` con un valor de 60 ms. Si falla, informa al usuario, ejecuta limpieza fatal y detiene el arranque.

**Pseudocódigo:**

```text id="cid0135"
iniciar detector de acordes con ventana temporal
si falla:
    mostrar error
    ejecutar limpieza fatal
    salir con error
```

**Relaciones:**

* Usa <a href="#cid-01-12">CID-01-12</a>.
* Precede a <a href="#cid-01-36">CID-01-36</a>.

---

### <a id="cid-01-36"></a>CID-01-36

**Qué hace:**
Conecta la bitácora, el diccionario y el callback de teclado al flujo del motor.

**Cómo funciona:**
Entrega al sistema el puntero a la bitácora, el puntero al diccionario cargado y el callback que debe recibir los eventos de teclado CID. Este bloque no arranca módulos nuevos, pero establece las conexiones lógicas entre los ya preparados.

**Pseudocódigo:**

```text id="cid0136"
conectar bitácora al sistema
conectar diccionario al sistema
registrar callback de teclado
```

**Relaciones:**

* Usa la bitácora de <a href="#cid-01-27">CID-01-27</a> y el diccionario de <a href="#cid-01-32">CID-01-32</a>.
* Precede a <a href="#cid-01-37">CID-01-37</a>.

---

### <a id="cid-01-37"></a>CID-01-37

**Qué hace:**
Inicia el módulo de teclado CID y aborta si no puede enganchar la captura de entrada.

**Cómo funciona:**
Invoca `IniciarTecladoCID`. Si el módulo no puede iniciar la captura de entrada, informa al usuario, ejecuta limpieza fatal y aborta.

**Pseudocódigo:**

```text id="cid0137"
iniciar módulo de teclado CID
si falla:
    mostrar error
    ejecutar limpieza fatal
    salir con error
```

**Relaciones:**

* Depende de la conexión previa realizada en <a href="#cid-01-36">CID-01-36</a>.
* Precede a <a href="#cid-01-38">CID-01-38</a>.

---

### <a id="cid-01-38"></a>CID-01-38

**Qué hace:**
Declara la estructura de mensajes usada por el bucle principal de Windows.

**Cómo funciona:**
Declara una variable local `MSG msg;` que actuará como contenedor de cada mensaje recuperado por `GetMessageW`.

**Pseudocódigo:**

```text id="cid0138"
declarar estructura de mensaje de Windows
```

**Relaciones:**

* Prepara <a href="#cid-01-39">CID-01-39</a>.

---

### <a id="cid-01-39"></a>CID-01-39

**Qué hace:**
Mantiene el bucle de mensajes del proceso mientras el sistema siga activo.

**Cómo funciona:**
Llama repetidamente a `GetMessageW`. Mientras esta función devuelva un valor positivo, el motor procesa el mensaje, primero verificando si es una hotkey propia y, en caso contrario, reenviándolo al sistema.

**Pseudocódigo:**

```text id="cid0139"
mientras haya mensajes válidos:
    revisar si es hotkey del motor
    si no lo es:
        traducir y despachar mensaje
```

**Relaciones:**

* Contiene internamente <a href="#cid-01-40">CID-01-40</a> a <a href="#cid-01-43">CID-01-43</a>.
* Precede al cierre ordenado de <a href="#cid-01-44">CID-01-44</a>.

---

### <a id="cid-01-40"></a>CID-01-40

**Qué hace:**
Filtra y procesa las hotkeys globales registradas por el motor.

**Cómo funciona:**
Comprueba si el tipo de mensaje es `WM_HOTKEY`. Si lo es, entra en la rama de gestión propia del motor, donde se evaluará si la hotkey corresponde a salida o a cambio de modo.

**Pseudocódigo:**

```text id="cid0140"
si el mensaje es una hotkey:
    procesar ramas internas del motor
```

**Relaciones:**

* Forma parte de <a href="#cid-01-39">CID-01-39</a>.
* Da paso a <a href="#cid-01-41">CID-01-41</a> y <a href="#cid-01-42">CID-01-42</a>.

---

### <a id="cid-01-41"></a>CID-01-41

**Qué hace:**
Finaliza el bucle principal cuando se activa la hotkey global de salida.

**Cómo funciona:**
Comprueba que la hotkey de salida se haya registrado correctamente y que el identificador del mensaje coincida con el de salida. Si ambas condiciones se cumplen, registra una traza y rompe el bucle principal.

**Pseudocódigo:**

```text id="cid0141"
si existe hotkey de salida y el mensaje es esa hotkey:
    escribir log
    salir del bucle
```

**Relaciones:**

* Usa <a href="#cid-01-03">CID-01-03</a>, <a href="#cid-01-05">CID-01-05</a> y el resultado de <a href="#cid-01-16">CID-01-16</a>.
* Está dentro de <a href="#cid-01-40">CID-01-40</a>.

---

### <a id="cid-01-42"></a>CID-01-42

**Qué hace:**
Alterna entre modo CID y QWERTY y actualiza la superposición visual.

**Cómo funciona:**
Comprueba que la hotkey de cambio de modo exista y que el mensaje actual corresponda a ella. Si es así, alterna el modo interno, actualiza el texto de estado mostrado por la superposición y refresca la bandera visual de modo QWERTY. Finalmente consume el mensaje con `continue`.

**Pseudocódigo:**

```text id="cid0142"
si existe hotkey de cambio de modo y el mensaje es esa hotkey:
    alternar modo interno
    actualizar texto visual del modo
    actualizar bandera visual QWERTY
    continuar bucle
```

**Relaciones:**

* Usa <a href="#cid-01-03">CID-01-03</a> y el resultado de <a href="#cid-01-17">CID-01-17</a>.
* Está dentro de <a href="#cid-01-40">CID-01-40</a>.

---

### <a id="cid-01-43"></a>CID-01-43

**Qué hace:**
Reenvía al sistema los mensajes que no fueron consumidos por las hotkeys del motor.

**Cómo funciona:**
Llama a `TranslateMessage` y `DispatchMessageW` con el mensaje actual. Así mantiene el comportamiento normal del bucle de mensajes para todo lo que no sea lógica específica del motor.

**Pseudocódigo:**

```text id="cid0143"
traducir mensaje
despachar mensaje
```

**Relaciones:**

* Forma parte de <a href="#cid-01-39">CID-01-39</a>.
* Se ejecuta cuando <a href="#cid-01-40">CID-01-40</a> no consume el mensaje.

---

### <a id="cid-01-44"></a>CID-01-44

**Qué hace:**
Detiene de forma ordenada todos los módulos activos al salir del bucle principal.

**Cómo funciona:**
Detiene explícitamente el teclado, el detector, el gestor de asentado, el panel contextual y la superposición. A diferencia de la limpieza fatal, aquí se trata del camino normal de cierre del proceso.

**Pseudocódigo:**

```text id="cid0144"
detener teclado
detener detector
detener gestor de asentado
detener panel contextual
detener superposición
```

**Relaciones:**

* Usa los mismos subsistemas que <a href="#cid-01-12">CID-01-12</a>, pero en el cierre normal.
* Precede a <a href="#cid-01-45">CID-01-45</a>.

---

### <a id="cid-01-45"></a>CID-01-45

**Qué hace:**
Libera las hotkeys globales que hubieran sido registradas con éxito.

**Cómo funciona:**
Comprueba las banderas de registro de cada hotkey y llama a `UnregisterHotKey` solo cuando la reserva correspondiente se realizó con éxito.

**Pseudocódigo:**

```text id="cid0145"
si la hotkey de salida existe:
    liberarla
si la hotkey de cambio de modo existe:
    liberarla
```

**Relaciones:**

* Usa resultados de <a href="#cid-01-16">CID-01-16</a> y <a href="#cid-01-17">CID-01-17</a>.
* Precede a <a href="#cid-01-46">CID-01-46</a>.

---

### <a id="cid-01-46"></a>CID-01-46

**Qué hace:**
Libera el mutex de instancia única al cerrar normalmente el motor.

**Cómo funciona:**
Comprueba si el handle del mutex existe y, si existe, lo cierra con `CloseHandle`. Esto completa la liberación del recurso de instancia única en la salida normal del proceso.

**Pseudocódigo:**

```text id="cid0146"
si existe mutex de instancia:
    cerrarlo
```

**Relaciones:**

* Usa el recurso creado en <a href="#cid-01-15">CID-01-15</a>.
* Complementa la variante de limpieza de emergencia descrita en <a href="#cid-01-12">CID-01-12</a>.
* Precede a <a href="#cid-01-47">CID-01-47</a>.

---

### <a id="cid-01-47"></a>CID-01-47

**Qué hace:**
Registra el cierre normal del motor y devuelve código de salida correcto.

**Cómo funciona:**
Escribe un último mensaje de depuración indicando que el motor ha terminado y devuelve `0` como señal de finalización correcta del proceso.

**Pseudocódigo:**

```text id="cid0147"
escribir log de cierre
devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-01-05">CID-01-05</a>.
* Es el cierre final de <a href="#cid-01-13">CID-01-13</a>.

## CID-02

La referencia <a href="#cid-02">CID-02</a> corresponde al archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/teclado_cid.cpp"><code>teclado_cid.cpp</code></a>. Este archivo implementa el módulo de captura global de teclado de CID. Su responsabilidad principal es instalar el hook de bajo nivel, filtrar los eventos recibidos, decidir qué teclas deben dejarse pasar y cuáles deben interceptarse, y reenviar al resto del sistema únicamente los eventos relevantes para el flujo de entrada CID.

Dentro de <a href="#cid-02">CID-02</a> también se mantiene el estado interno necesario para distinguir entre modo CID y modo QWERTY, controlar autorepeticiones, evitar interferencias con texto inyectado por el propio sistema y notificar actividad escribible al panel contextual. En términos prácticos, <a href="#cid-02">CID-02</a> es la capa que se sienta entre el teclado físico y el resto del motor, decidiendo en tiempo real cómo debe tratarse cada pulsación.

### Índice interno de bloques

* <a href="#cid-02-01">CID-02-01</a>
* <a href="#cid-02-02">CID-02-02</a>
* <a href="#cid-02-03">CID-02-03</a>
* <a href="#cid-02-04">CID-02-04</a>
* <a href="#cid-02-05">CID-02-05</a>
* <a href="#cid-02-06">CID-02-06</a>
* <a href="#cid-02-07">CID-02-07</a>
* <a href="#cid-02-08">CID-02-08</a>
* <a href="#cid-02-09">CID-02-09</a>
* <a href="#cid-02-10">CID-02-10</a>
* <a href="#cid-02-11">CID-02-11</a>
* <a href="#cid-02-12">CID-02-12</a>
* <a href="#cid-02-13">CID-02-13</a>
* <a href="#cid-02-14">CID-02-14</a>
* <a href="#cid-02-15">CID-02-15</a>
* <a href="#cid-02-16">CID-02-16</a>
* <a href="#cid-02-17">CID-02-17</a>
* <a href="#cid-02-18">CID-02-18</a>
* <a href="#cid-02-19">CID-02-19</a>
* <a href="#cid-02-20">CID-02-20</a>
* <a href="#cid-02-21">CID-02-21</a>
* <a href="#cid-02-22">CID-02-22</a>
* <a href="#cid-02-23">CID-02-23</a>
* <a href="#cid-02-24">CID-02-24</a>
* <a href="#cid-02-25">CID-02-25</a>
* <a href="#cid-02-26">CID-02-26</a>
* <a href="#cid-02-27">CID-02-27</a>
* <a href="#cid-02-28">CID-02-28</a>
* <a href="#cid-02-29">CID-02-29</a>
* <a href="#cid-02-30">CID-02-30</a>
* <a href="#cid-02-31">CID-02-31</a>
* <a href="#cid-02-32">CID-02-32</a>
* <a href="#cid-02-33">CID-02-33</a>
* <a href="#cid-02-34">CID-02-34</a>
* <a href="#cid-02-35">CID-02-35</a>
* <a href="#cid-02-36">CID-02-36</a>
* <a href="#cid-02-37">CID-02-37</a>
* <a href="#cid-02-38">CID-02-38</a>
* <a href="#cid-02-39">CID-02-39</a>
* <a href="#cid-02-40">CID-02-40</a>
* <a href="#cid-02-41">CID-02-41</a>
* <a href="#cid-02-42">CID-02-42</a>
* <a href="#cid-02-43">CID-02-43</a>
* <a href="#cid-02-44">CID-02-44</a>
* <a href="#cid-02-45">CID-02-45</a>
* <a href="#cid-02-46">CID-02-46</a>
* <a href="#cid-02-47">CID-02-47</a>
* <a href="#cid-02-48">CID-02-48</a>

---

### <a id="cid-02-01"></a>CID-02-01

**Qué hace:**  
Incluye la interfaz pública del propio módulo de teclado CID.

**Cómo funciona:**  
Este bloque importa la cabecera que declara las funciones públicas del módulo, permitiendo que la implementación de <a href="#cid-02">CID-02</a> coincida con la interfaz expuesta al resto del proyecto.

**Pseudocódigo:**  
```text
incluir interfaz pública del teclado CID
````

**Relaciones:**

* Prepara la implementación de todo <a href="#cid-02">CID-02</a>.
* Se corresponde con <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/teclado_cid.h"><code>teclado_cid.h</code></a>.

---

### <a id="cid-02-02"></a>CID-02-02

**Qué hace:**
Incluye módulos auxiliares necesarios para el filtrado de entrada y la interacción con otros subsistemas.

**Cómo funciona:**
Este bloque enlaza la captura de teclado con la calibración cargada, la detección de texto inyectado y la activación del panel contextual. Gracias a estas inclusiones, el hook puede tomar decisiones apoyándose en el resto del motor.

**Pseudocódigo:**

```text
incluir calibración del teclado
incluir control de inyección de texto
incluir panel contextual
```

**Relaciones:**

* Da soporte a <a href="#cid-02-13">CID-02-13</a>, <a href="#cid-02-24">CID-02-24</a>, <a href="#cid-02-27">CID-02-27</a> y <a href="#cid-02-32">CID-02-32</a>.
* Enlaza con <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a>, <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/inyeccion_texto.h"><code>inyeccion_texto.h</code></a> y <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/panel_contexto_texto.h"><code>panel_contexto_texto.h</code></a>.

---

### <a id="cid-02-03"></a>CID-02-03

**Qué hace:**
Incluye las cabeceras del sistema y de texto necesarias para el hook global.

**Cómo funciona:**
Aporta acceso a la API Win32 y a `std::wstring`, que se usan para instalar el hook y para generar mensajes de depuración del módulo.

**Pseudocódigo:**

```text
incluir API de Windows
incluir soporte de cadenas
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-02-06">CID-02-06</a>, <a href="#cid-02-20">CID-02-20</a> y <a href="#cid-02-39">CID-02-39</a>.

---

### <a id="cid-02-04"></a>CID-02-04

**Qué hace:**
Define el estado global principal del módulo: hook instalado, callback registrado y modo activo.

**Cómo funciona:**
Mantiene tres variables estáticas persistentes. `g_hook` guarda el identificador del hook global, `g_callback` almacena la función que recibirá los eventos CID ya filtrados y `g_modo_cid` conserva si el sistema está en modo CID o en modo QWERTY.

**Pseudocódigo:**

```text
guardar referencia al hook global
guardar callback de eventos
guardar modo activo del teclado
```

**Relaciones:**

* Usado por <a href="#cid-02-20">CID-02-20</a>, <a href="#cid-02-36">CID-02-36</a>, <a href="#cid-02-42">CID-02-42</a>, <a href="#cid-02-45">CID-02-45</a>, <a href="#cid-02-46">CID-02-46</a>, <a href="#cid-02-47">CID-02-47</a> y <a href="#cid-02-48">CID-02-48</a>.

---

### <a id="cid-02-05"></a>CID-02-05

**Qué hace:**
Mantiene el estado de teclas pulsadas para detectar autorepeticiones por virtual key y por scan code.

**Cómo funciona:**
Define dos buffers booleanos de 256 posiciones. Uno indexa por virtual key y otro por scan code. Estos estados permiten distinguir entre una pulsación nueva y una repetición automática generada por mantener una tecla presionada.

**Pseudocódigo:**

```text
crear buffer de estado por virtual key
crear buffer de estado por scan code
```

**Relaciones:**

* Usado por <a href="#cid-02-17">CID-02-17</a>, <a href="#cid-02-18">CID-02-18</a>, <a href="#cid-02-19">CID-02-19</a>, <a href="#cid-02-28">CID-02-28</a>, <a href="#cid-02-29">CID-02-29</a>, <a href="#cid-02-30">CID-02-30</a>, <a href="#cid-02-34">CID-02-34</a> y <a href="#cid-02-35">CID-02-35</a>.

---

### <a id="cid-02-06"></a>CID-02-06

**Qué hace:**
Envía mensajes de depuración del módulo de teclado al visor de salida de Windows.

**Cómo funciona:**
Recibe una cadena `std::wstring`, le añade un salto de línea y la envía a `OutputDebugStringW`. Sirve como helper interno para registrar arranques, cierres y errores del módulo.

**Pseudocódigo:**

```text
añadir salto de línea al mensaje
enviar mensaje al depurador
```

**Relaciones:**

* Usado por <a href="#cid-02-40">CID-02-40</a>, <a href="#cid-02-41">CID-02-41</a>, <a href="#cid-02-44">CID-02-44</a>, <a href="#cid-02-47">CID-02-47</a> y <a href="#cid-02-48">CID-02-48</a>.

---

### <a id="cid-02-07"></a>CID-02-07

**Qué hace:**
Comprueba si una virtual key cabe dentro del rango de indexación de los buffers internos.

**Cómo funciona:**
Verifica que el valor de la virtual key sea menor que 256. Esto permite usarla con seguridad como índice sobre el buffer `g_vk_abajo`.

**Pseudocódigo:**

```text
si la virtual key es menor que 256:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usado por <a href="#cid-02-17">CID-02-17</a>, <a href="#cid-02-28">CID-02-28</a>, <a href="#cid-02-29">CID-02-29</a>, <a href="#cid-02-30">CID-02-30</a>, <a href="#cid-02-34">CID-02-34</a> y <a href="#cid-02-35">CID-02-35</a>.

---

### <a id="cid-02-08"></a>CID-02-08

**Qué hace:**
Comprueba si un scan code cabe dentro del rango de indexación de los buffers internos.

**Cómo funciona:**
Valida que el scan code sea menor que 256 para poder usarlo con seguridad como índice sobre `g_sc_abajo`.

**Pseudocódigo:**

```text
si el scan code es menor que 256:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usado por <a href="#cid-02-13">CID-02-13</a>, <a href="#cid-02-18">CID-02-18</a>, <a href="#cid-02-29">CID-02-29</a> y <a href="#cid-02-35">CID-02-35</a>.

---

### <a id="cid-02-09"></a>CID-02-09

**Qué hace:**
Detecta si la tecla Control está activa en el instante actual.

**Cómo funciona:**
Consulta `GetAsyncKeyState` sobre `VK_CONTROL` y comprueba el bit alto para saber si Control está presionado en tiempo real.

**Pseudocódigo:**

```text
consultar estado asíncrono de Control
devolver si está activo
```

**Relaciones:**

* Usado por <a href="#cid-02-25">CID-02-25</a>.

---

### <a id="cid-02-10"></a>CID-02-10

**Qué hace:**
Detecta si la tecla Alt está activa en el instante actual.

**Cómo funciona:**
Consulta `GetAsyncKeyState` sobre `VK_MENU` y comprueba el bit alto para decidir si Alt está presionado.

**Pseudocódigo:**

```text
consultar estado asíncrono de Alt
devolver si está activo
```

**Relaciones:**

* Usado por <a href="#cid-02-25">CID-02-25</a>.

---

### <a id="cid-02-11"></a>CID-02-11

**Qué hace:**
Detecta si alguna tecla Windows está activa en el instante actual.

**Cómo funciona:**
Consulta el estado asíncrono de `VK_LWIN` y `VK_RWIN`. Si cualquiera de ambas aparece activa, el bloque devuelve verdadero.

**Pseudocódigo:**

```text
consultar tecla Windows izquierda
consultar tecla Windows derecha
devolver si alguna está activa
```

**Relaciones:**

* Usado por <a href="#cid-02-25">CID-02-25</a>.

---

### <a id="cid-02-12"></a>CID-02-12

**Qué hace:**
Identifica si la virtual key recibida corresponde al pedal principal físico de CID.

**Cómo funciona:**
Compara directamente la virtual key con `VK_SPACE`. En la configuración actual del sistema, la barra espaciadora actúa como pedal principal.

**Pseudocódigo:**

```text
si la virtual key es espacio:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usado por <a href="#cid-02-14">CID-02-14</a> y <a href="#cid-02-31">CID-02-31</a>.

---

### <a id="cid-02-13"></a>CID-02-13

**Qué hace:**
Comprueba si un scan code corresponde a una tecla CID reconocida por la calibración cargada.

**Cómo funciona:**
Primero valida que el scan code sea indexable. Después consulta `NombreTeclaCID_PorScanCode`. Si esta función devuelve un nombre válido, el scan code pertenece a una tecla CID calibrada.

**Pseudocódigo:**

```text
si el scan code no es válido:
    devolver falso
consultar nombre CID por scan code
si existe nombre:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usa <a href="#cid-02-08">CID-02-08</a>.
* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a>.
* Es usado por <a href="#cid-02-14">CID-02-14</a>.

---

### <a id="cid-02-14"></a>CID-02-14

**Qué hace:**
Determina si una tecla física pertenece al conjunto operativo de entrada CID.

**Cómo funciona:**
Primero comprueba si la tecla es el pedal principal físico. Si no lo es, delega en la validación por scan code calibrado. Con esto cubre tanto el pedal como el resto de teclas CID reconocidas por la calibración actual.

**Pseudocódigo:**

```text
si la tecla es el pedal principal:
    devolver verdadero
devolver si el scan code está calibrado como tecla CID
```

**Relaciones:**

* Usa <a href="#cid-02-12">CID-02-12</a> y <a href="#cid-02-13">CID-02-13</a>.
* Es usado por <a href="#cid-02-31">CID-02-31</a>.

---

### <a id="cid-02-15"></a>CID-02-15

**Qué hace:**
Permite pasar ciertas teclas de formato incluso cuando CID está activo.

**Cómo funciona:**
Evalúa la virtual key contra un conjunto cerrado de teclas permitidas, como retroceso, enter, tabulador y shift. Estas teclas no se bloquean en modo CID porque forman parte de la edición o del formato básico.

**Pseudocódigo:**

```text
si la tecla está en la lista de formato permitido:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usado por <a href="#cid-02-30">CID-02-30</a>.

---

### <a id="cid-02-16"></a>CID-02-16

**Qué hace:**
Determina si una virtual key pertenece al conjunto de entrada escribible normal de QWERTY.

**Cómo funciona:**
Acepta letras, números y un conjunto de teclas de puntuación y operadores habituales. Sirve para distinguir teclas que normalmente generan texto de otras que no son escribibles.

**Pseudocódigo:**

```text
si la tecla es letra o número:
    devolver verdadero
si la tecla está en la lista de signos escribibles:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usado por <a href="#cid-02-26">CID-02-26</a> y <a href="#cid-02-34">CID-02-34</a>.

---

### <a id="cid-02-17"></a>CID-02-17

**Qué hace:**
Detecta autorepetición por virtual key y actualiza su estado de pulsación.

**Cómo funciona:**
Si la tecla sale del rango indexable, no detecta repetición. Si el evento es de liberación, limpia el estado y devuelve falso. Si es pulsación, comprueba si ya estaba marcada como abajo, marca la tecla como pulsada y devuelve si era repetida.

**Pseudocódigo:**

```text
si la tecla no está en rango:
    devolver falso
si el evento es liberación:
    limpiar estado
    devolver falso
leer si ya estaba abajo
marcar como abajo
devolver si era repetida
```

**Relaciones:**

* Usa <a href="#cid-02-07">CID-02-07</a>.
* Es usado por <a href="#cid-02-27">CID-02-27</a> y <a href="#cid-02-31">CID-02-31</a>.

---

### <a id="cid-02-18"></a>CID-02-18

**Qué hace:**
Detecta autorepetición por scan code y actualiza su estado de pulsación.

**Cómo funciona:**
Aplica la misma lógica que el control por virtual key, pero sobre el buffer indexado por scan code. Esto es útil para teclas CID físicas reconocidas por su calibración concreta.

**Pseudocódigo:**

```text
si el scan code no está en rango:
    devolver falso
si el evento es liberación:
    limpiar estado
    devolver falso
leer si ya estaba abajo
marcar como abajo
devolver si era repetida
```

**Relaciones:**

* Usa <a href="#cid-02-08">CID-02-08</a>.
* Es usado por <a href="#cid-02-31">CID-02-31</a>.

---

### <a id="cid-02-19"></a>CID-02-19

**Qué hace:**
Reinicia por completo el estado interno de teclas pulsadas del módulo.

**Cómo funciona:**
Recorre ambos buffers de 256 posiciones y marca todas las entradas como no pulsadas. Se usa al arrancar el módulo y al cambiar de modo para evitar estados residuales.

**Pseudocódigo:**

```text
para cada posición de los buffers:
    marcar virtual key como arriba
    marcar scan code como arriba
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-02-05">CID-02-05</a>.
* Es usado por <a href="#cid-02-38">CID-02-38</a>, <a href="#cid-02-44">CID-02-44</a>, <a href="#cid-02-47">CID-02-47</a> y <a href="#cid-02-48">CID-02-48</a>.

---

### <a id="cid-02-20"></a>CID-02-20

**Qué hace:**
Procesa cada evento recibido por el hook global y decide si dejar pasar, notificar o interceptar la tecla.

**Cómo funciona:**
`HookProc` es el núcleo del módulo. Valida el evento, clasifica si es pulsación o liberación, ignora inyección propia, calcula el estado de modificadores, diferencia entre modo QWERTY y modo CID y aplica reglas distintas para teclas CID, teclas QWERTY normales, teclas de formato y teclas no escribibles. Finalmente puede reenviar el evento al sistema o consumirlo devolviendo `1`.

**Pseudocódigo:**

```text
validar evento del hook
extraer tipo de evento y datos de tecla
ignorar inyección propia
leer modificadores
si el modo es QWERTY:
    aplicar reglas QWERTY
si el modo es CID:
    aplicar reglas CID
dejar pasar o bloquear según el caso
```

**Relaciones:**

* Contiene internamente <a href="#cid-02-21">CID-02-21</a> a <a href="#cid-02-35">CID-02-35</a>.
* Usa el estado de <a href="#cid-02-04">CID-02-04</a> y <a href="#cid-02-05">CID-02-05</a>.

---

### <a id="cid-02-21"></a>CID-02-21

**Qué hace:**
Reenvía inmediatamente al siguiente hook cualquier evento inválido o no accionable.

**Cómo funciona:**
Comprueba si `nCode` es negativo, distinto de `HC_ACTION` o si la estructura de teclado es nula. En cualquiera de esos casos no intenta procesar la tecla y delega el evento al siguiente hook del sistema.

**Pseudocódigo:**

```text
si el código del hook no es válido:
    reenviar evento
si el tipo de acción no es procesable:
    reenviar evento
si no existe estructura de teclado:
    reenviar evento
```

**Relaciones:**

* Forma parte de <a href="#cid-02-20">CID-02-20</a>.
* Precede a <a href="#cid-02-22">CID-02-22</a>.

---

### <a id="cid-02-22"></a>CID-02-22

**Qué hace:**
Clasifica el evento como pulsación o liberación y descarta cualquier otro tipo.

**Cómo funciona:**
Compara `wParam` con los mensajes de pulsación y liberación del sistema. Si el evento no es ni una cosa ni la otra, se reenvía sin procesar.

**Pseudocódigo:**

```text
detectar si el evento es pulsación
detectar si el evento es liberación
si no es ninguno:
    reenviar evento
```

**Relaciones:**

* Forma parte de <a href="#cid-02-20">CID-02-20</a>.
* Precede a <a href="#cid-02-23">CID-02-23</a>.

---

### <a id="cid-02-23"></a>CID-02-23

**Qué hace:**
Extrae la virtual key y el scan code de la tecla recibida.

**Cómo funciona:**
Lee ambos valores desde la estructura `KBDLLHOOKSTRUCT` y los guarda en variables locales para reutilizarlos en todas las ramas posteriores del filtrado.

**Pseudocódigo:**

```text
leer virtual key de la estructura
leer scan code de la estructura
guardar ambos valores
```

**Relaciones:**

* Forma parte de <a href="#cid-02-20">CID-02-20</a>.
* Alimenta a casi todos los bloques posteriores del hook, especialmente <a href="#cid-02-24">CID-02-24</a> a <a href="#cid-02-35">CID-02-35</a>.

---

### <a id="cid-02-24"></a>CID-02-24

**Qué hace:**
Evita interceptar eventos generados por la propia inyección de texto del sistema CID.

**Cómo funciona:**
Consulta `InyeccionActiva()`. Si el sistema está inyectando texto, el hook deja pasar inmediatamente el evento para no recapturarlo como si fuese entrada física del usuario.

**Pseudocódigo:**

```text
si la inyección de texto está activa:
    reenviar evento
```

**Relaciones:**

* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/inyeccion_texto.h"><code>inyeccion_texto.h</code></a>.
* Forma parte de <a href="#cid-02-20">CID-02-20</a>.

---

### <a id="cid-02-25"></a>CID-02-25

**Qué hace:**
Calcula el estado actual de modificadores del sistema para evitar interferencias con atajos globales.

**Cómo funciona:**
Lee el estado de Control, Alt y Windows mediante helpers específicos y combina el resultado en una bandera general llamada `hay_modificador_sistema`.

**Pseudocódigo:**

```text
leer estado de Control
leer estado de Alt
leer estado de Windows
combinar si hay algún modificador activo
```

**Relaciones:**

* Usa <a href="#cid-02-09">CID-02-09</a>, <a href="#cid-02-10">CID-02-10</a> y <a href="#cid-02-11">CID-02-11</a>.
* Alimenta a <a href="#cid-02-26">CID-02-26</a> y <a href="#cid-02-29">CID-02-29</a>.

---

### <a id="cid-02-26"></a>CID-02-26

**Qué hace:**
Gestiona el comportamiento del hook cuando el sistema está en modo QWERTY.

**Cómo funciona:**
Si `g_modo_cid` está desactivado, el bloque permite pasar toda la entrada. Solo añade lógica adicional para despertar el panel contextual al detectar pulsaciones escribibles reales sin modificadores, y para limpiar estados internos al liberar teclas.

**Pseudocódigo:**

```text
si el modo actual es QWERTY:
    si es pulsación escribible sin modificadores:
        procesar notificación de actividad
    si es liberación:
        limpiar estado interno
    reenviar evento
```

**Relaciones:**

* Depende de <a href="#cid-02-04">CID-02-04</a>, <a href="#cid-02-16">CID-02-16</a> y <a href="#cid-02-25">CID-02-25</a>.
* Contiene internamente <a href="#cid-02-27">CID-02-27</a> y <a href="#cid-02-28">CID-02-28</a>.

---

### <a id="cid-02-27"></a>CID-02-27

**Qué hace:**
Notifica actividad escribible al panel contextual solo en pulsaciones nuevas y sin modificadores de sistema en modo QWERTY.

**Cómo funciona:**
Cuando se detecta una pulsación escribible, el bloque consulta si es autorepetida mediante la virtual key. Solo si no es repetida dispara la notificación al panel contextual.

**Pseudocódigo:**

```text
si es pulsación escribible válida:
    comprobar si es repetida
    si no es repetida:
        notificar actividad al panel
```

**Relaciones:**

* Usa <a href="#cid-02-16">CID-02-16</a>, <a href="#cid-02-17">CID-02-17</a> y <a href="#cid-02-25">CID-02-25</a>.
* Llama a <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/panel_contexto_texto.h"><code>panel_contexto_texto.h</code></a>.
* Forma parte de <a href="#cid-02-26">CID-02-26</a>.

---

### <a id="cid-02-28"></a>CID-02-28

**Qué hace:**
Limpia el estado interno de una tecla al liberarse en modo QWERTY.

**Cómo funciona:**
Si el evento es de liberación y la virtual key es indexable, marca la tecla como no presionada en el buffer de virtual keys.

**Pseudocódigo:**

```text
si la tecla se libera y está en rango:
    limpiar estado de virtual key
```

**Relaciones:**

* Usa <a href="#cid-02-07">CID-02-07</a> y el estado de <a href="#cid-02-05">CID-02-05</a>.
* Forma parte de <a href="#cid-02-26">CID-02-26</a>.

---

### <a id="cid-02-29"></a>CID-02-29

**Qué hace:**
En modo CID deja pasar combinaciones con modificadores del sistema para no romper atajos externos.

**Cómo funciona:**
Si hay Control, Alt o Windows activos, el módulo no intercepta la tecla. Solo limpia estados internos al liberarse y reenvía el evento al sistema.

**Pseudocódigo:**

```text
si hay modificador del sistema activo:
    si el evento es liberación:
        limpiar estados internos
    reenviar evento
```

**Relaciones:**

* Usa <a href="#cid-02-25">CID-02-25</a>, <a href="#cid-02-07">CID-02-07</a> y <a href="#cid-02-08">CID-02-08</a>.
* Forma parte de <a href="#cid-02-20">CID-02-20</a>.

---

### <a id="cid-02-30"></a>CID-02-30

**Qué hace:**
En modo CID deja pasar ciertas teclas de formato permitidas y limpia su estado al liberarse.

**Cómo funciona:**
Si la virtual key corresponde a una tecla de formato permitida, el hook no la bloquea. Solo actualiza el buffer interno cuando la tecla se libera y luego deja pasar el evento.

**Pseudocódigo:**

```text
si la tecla es de formato permitido:
    si el evento es liberación:
        limpiar estado de virtual key
    reenviar evento
```

**Relaciones:**

* Usa <a href="#cid-02-15">CID-02-15</a> y <a href="#cid-02-07">CID-02-07</a>.
* Forma parte de <a href="#cid-02-20">CID-02-20</a>.

---

### <a id="cid-02-31"></a>CID-02-31

**Qué hace:**
Captura las teclas físicas de CID, detecta autorepetición y las reenvía al flujo del sistema CID.

**Cómo funciona:**
Cuando la tecla pertenece al conjunto físico de CID, el bloque decide si la repetición debe medirse por virtual key o por scan code según sea el pedal principal o una tecla calibrada. Después puede notificar actividad, llamar al callback y finalmente consume el evento devolviendo `1`.

**Pseudocódigo:**

```text
si la tecla física es una tecla CID:
    detectar si es repetida
    si es pulsación nueva:
        notificar actividad
    si existe callback:
        reenviar evento filtrado
    bloquear evento al sistema
```

**Relaciones:**

* Usa <a href="#cid-02-12">CID-02-12</a>, <a href="#cid-02-14">CID-02-14</a>, <a href="#cid-02-17">CID-02-17</a> y <a href="#cid-02-18">CID-02-18</a>.
* Contiene internamente <a href="#cid-02-32">CID-02-32</a> y <a href="#cid-02-33">CID-02-33</a>.
* Es la rama central de captura dentro de <a href="#cid-02-20">CID-02-20</a>.

---

### <a id="cid-02-32"></a>CID-02-32

**Qué hace:**
Notifica actividad escribible al panel contextual solo en pulsaciones nuevas de teclas CID.

**Cómo funciona:**
Si el evento corresponde a una pulsación y no a una autorepetición, despierta el panel contextual para indicar que existe actividad escribible relevante.

**Pseudocódigo:**

```text
si la tecla CID es una pulsación nueva:
    notificar actividad al panel
```

**Relaciones:**

* Usa el resultado de repetición calculado en <a href="#cid-02-31">CID-02-31</a>.
* Llama a <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/panel_contexto_texto.h"><code>panel_contexto_texto.h</code></a>.

---

### <a id="cid-02-33"></a>CID-02-33

**Qué hace:**
Llama al callback registrado evitando reenviar pulsaciones autorepetidas innecesarias.

**Cómo funciona:**
Si existe callback, el bloque lo ejecuta para liberar eventos o para pulsaciones nuevas. Las pulsaciones autorepetidas se suprimen para no saturar al detector o al consumidor del evento.

**Pseudocódigo:**

```text
si existe callback:
    si el evento no es repetición bloqueable:
        llamar al callback con los datos de tecla
```

**Relaciones:**

* Usa el callback guardado en <a href="#cid-02-04">CID-02-04</a>.
* Forma parte de <a href="#cid-02-31">CID-02-31</a>.
* Conecta con el callback registrado desde <a href="#cid-01-34">CID-01-34</a>.

---

### <a id="cid-02-34"></a>CID-02-34

**Qué hace:**
Bloquea teclas escribibles QWERTY normales para evitar texto accidental mientras CID está activo.

**Cómo funciona:**
Si en modo CID llega una tecla escribible típica de QWERTY que no pertenece al conjunto permitido, el bloque la consume devolviendo `1`. Solo limpia el estado de la virtual key cuando el evento es de liberación.

**Pseudocódigo:**

```text
si la tecla es escribible QWERTY normal:
    si el evento es liberación:
        limpiar estado
    bloquear evento
```

**Relaciones:**

* Usa <a href="#cid-02-16">CID-02-16</a> y <a href="#cid-02-07">CID-02-07</a>.
* Forma parte de <a href="#cid-02-20">CID-02-20</a>.

---

### <a id="cid-02-35"></a>CID-02-35

**Qué hace:**
Deja pasar el resto de teclas no escribibles y limpia sus estados internos al liberarse.

**Cómo funciona:**
Para teclas que no encajan en las ramas anteriores, el bloque solo limpia buffers si el evento es liberación y luego reenvía normalmente el mensaje al sistema.

**Pseudocódigo:**

```text
si el evento es liberación:
    limpiar estado de virtual key si aplica
    limpiar estado de scan code si aplica
reenviar evento
```

**Relaciones:**

* Usa <a href="#cid-02-07">CID-02-07</a>, <a href="#cid-02-08">CID-02-08</a> y el estado de <a href="#cid-02-05">CID-02-05</a>.
* Es la salida final de <a href="#cid-02-20">CID-02-20</a> cuando no se consumió la tecla.

---

### <a id="cid-02-36"></a>CID-02-36

**Qué hace:**
Instala el hook global de teclado CID si todavía no está activo.

**Cómo funciona:**
Funciona como punto público de arranque del módulo. Comprueba si el hook ya existe, reinicia estados internos, intenta instalar el hook global de bajo nivel y registra trazas de éxito o error.

**Pseudocódigo:**

```text
si el hook ya existe:
    devolver éxito
reiniciar estados internos
instalar hook global
si falla:
    registrar error
    devolver falso
registrar inicio correcto
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-02-37">CID-02-37</a> a <a href="#cid-02-41">CID-02-41</a>.
* Es llamado desde <a href="#cid-01-35">CID-01-35</a>.

---

### <a id="cid-02-37"></a>CID-02-37

**Qué hace:**
Evita reinstalar el hook si el módulo ya se encuentra iniciado.

**Cómo funciona:**
Comprueba si `g_hook` ya contiene un identificador válido. Si es así, considera que el módulo ya está operativo y devuelve éxito inmediato.

**Pseudocódigo:**

```text
si el hook ya está instalado:
    devolver verdadero
```

**Relaciones:**

* Usa el estado global de <a href="#cid-02-04">CID-02-04</a>.
* Forma parte de <a href="#cid-02-36">CID-02-36</a>.

---

### <a id="cid-02-38"></a>CID-02-38

**Qué hace:**
Reinicia el estado interno de teclas antes de enganchar la captura global.

**Cómo funciona:**
Llama al helper de reinicio completo para asegurarse de que no existan estados residuales previos a la instalación del hook.

**Pseudocódigo:**

```text
reiniciar estados de teclas
```

**Relaciones:**

* Usa <a href="#cid-02-19">CID-02-19</a>.
* Forma parte de <a href="#cid-02-36">CID-02-36</a>.

---

### <a id="cid-02-39"></a>CID-02-39

**Qué hace:**
Instala el hook de bajo nivel para interceptar eventos de teclado en todo el sistema.

**Cómo funciona:**
Llama a `SetWindowsHookExW` con `WH_KEYBOARD_LL`, pasando `HookProc` como callback y el módulo actual como referencia. Si la llamada tiene éxito, el sistema empezará a enviar eventos de teclado a este módulo.

**Pseudocódigo:**

```text
llamar a instalación de hook global de teclado
guardar identificador devuelto
```

**Relaciones:**

* Usa <a href="#cid-02-20">CID-02-20</a>.
* Forma parte de <a href="#cid-02-36">CID-02-36</a>.

---

### <a id="cid-02-40"></a>CID-02-40

**Qué hace:**
Registra error y falla el arranque si no se pudo instalar el hook global.

**Cómo funciona:**
Comprueba si el identificador de hook quedó nulo tras el intento de instalación. Si es así, emite una traza de error y devuelve falso al llamador.

**Pseudocódigo:**

```text
si el hook no se instaló:
    escribir error
    devolver falso
```

**Relaciones:**

* Usa <a href="#cid-02-06">CID-02-06</a>.
* Forma parte de <a href="#cid-02-36">CID-02-36</a>.

---

### <a id="cid-02-41"></a>CID-02-41

**Qué hace:**
Registra el arranque correcto del hook global de teclado.

**Cómo funciona:**
Emite una traza informando de que la instalación del hook fue correcta y devuelve éxito al llamador.

**Pseudocódigo:**

```text
escribir log de arranque correcto
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-02-06">CID-02-06</a>.
* Forma parte de <a href="#cid-02-36">CID-02-36</a>.

---

### <a id="cid-02-42"></a>CID-02-42

**Qué hace:**
Desinstala el hook global de teclado y limpia el estado interno del módulo.

**Cómo funciona:**
Funciona como punto público de parada. Si el hook está activo lo desengancha, después reinicia todos los estados residuales y registra el cierre del módulo.

**Pseudocódigo:**

```text
si el hook está activo:
    desinstalar hook
reiniciar estados internos
registrar cierre del módulo
```

**Relaciones:**

* Contiene internamente <a href="#cid-02-43">CID-02-43</a> y <a href="#cid-02-44">CID-02-44</a>.
* Es llamado desde <a href="#cid-01-11">CID-01-11</a> y <a href="#cid-01-42">CID-01-42</a>.

---

### <a id="cid-02-43"></a>CID-02-43

**Qué hace:**
Desengancha el hook solo si actualmente estaba activo.

**Cómo funciona:**
Comprueba si `g_hook` contiene un identificador válido. Si lo contiene, llama a `UnhookWindowsHookEx` y deja el puntero nulo.

**Pseudocódigo:**

```text
si el hook existe:
    desinstalarlo
    limpiar referencia global
```

**Relaciones:**

* Usa el estado global de <a href="#cid-02-04">CID-02-04</a>.
* Forma parte de <a href="#cid-02-42">CID-02-42</a>.

---

### <a id="cid-02-44"></a>CID-02-44

**Qué hace:**
Reinicia estados residuales y registra el cierre del módulo de teclado.

**Cómo funciona:**
Llama al reinicio completo de estados y emite una traza indicando que el hook global fue detenido.

**Pseudocódigo:**

```text
reiniciar estados de teclas
escribir log de cierre
```

**Relaciones:**

* Usa <a href="#cid-02-19">CID-02-19</a> y <a href="#cid-02-06">CID-02-06</a>.
* Forma parte de <a href="#cid-02-42">CID-02-42</a>.

---

### <a id="cid-02-45"></a>CID-02-45

**Qué hace:**
Registra el callback que recibirá los eventos de teclas CID ya filtrados por el hook.

**Cómo funciona:**
Asigna a `g_callback` la función proporcionada por el llamador. A partir de ese momento, el hook podrá reenviar eventos válidos a ese callback.

**Pseudocódigo:**

```text
guardar callback recibido
```

**Relaciones:**

* Usa el estado global de <a href="#cid-02-04">CID-02-04</a>.
* El callback registrado se usa en <a href="#cid-02-33">CID-02-33</a>.
* Es llamado desde <a href="#cid-01-34">CID-01-34</a>.

---

### <a id="cid-02-46"></a>CID-02-46

**Qué hace:**
Devuelve si el módulo se encuentra actualmente operando en modo CID.

**Cómo funciona:**
Retorna directamente el valor de `g_modo_cid`, sin lógica adicional.

**Pseudocódigo:**

```text
devolver modo CID actual
```

**Relaciones:**

* Usa el estado global de <a href="#cid-02-04">CID-02-04</a>.
* Es consultado desde <a href="#cid-01-18">CID-01-18</a> y <a href="#cid-01-40">CID-01-40</a>.

---

### <a id="cid-02-47"></a>CID-02-47

**Qué hace:**
Alterna entre modo CID y modo QWERTY y reinicia el estado interno del teclado.

**Cómo funciona:**
Invierte el valor de `g_modo_cid`, reinicia el estado de teclas para evitar arrastres entre modos y registra una traza indicando el nuevo estado.

**Pseudocódigo:**

```text
invertir modo actual
reiniciar estados internos
escribir log del nuevo modo
```

**Relaciones:**

* Usa <a href="#cid-02-04">CID-02-04</a>, <a href="#cid-02-19">CID-02-19</a> y <a href="#cid-02-06">CID-02-06</a>.
* Es llamado desde <a href="#cid-01-40">CID-01-40</a>.

---

### <a id="cid-02-48"></a>CID-02-48

**Qué hace:**
Establece explícitamente el modo de funcionamiento del teclado y reinicia sus estados internos.

**Cómo funciona:**
Asigna directamente el valor recibido a `g_modo_cid`, limpia el estado del módulo y registra el modo resultante. A diferencia del bloque anterior, no alterna, sino que fija el modo indicado.

**Pseudocódigo:**

```text
establecer modo recibido
reiniciar estados internos
escribir log del modo fijado
```

**Relaciones:**

* Usa <a href="#cid-02-04">CID-02-04</a>, <a href="#cid-02-19">CID-02-19</a> y <a href="#cid-02-06">CID-02-06</a>.
* Expone una operación pública complementaria a <a href="#cid-02-47">CID-02-47</a>.


## CID-03

La referencia <a href="#cid-03">CID-03</a> corresponde al archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/teclado_cid.h"><code>teclado_cid.h</code></a>. Este archivo define la interfaz pública del módulo de captura de teclado CID. Su responsabilidad es exponer al resto del proyecto las funciones necesarias para iniciar y detener el hook global, registrar el callback de eventos filtrados y consultar o modificar el modo operativo del teclado.

Dentro de <a href="#cid-03">CID-03</a> no hay lógica de ejecución como tal. Su función es fijar el contrato público que implementa <a href="#cid-02">CID-02</a>, manteniendo separada la declaración de la interfaz y la implementación del comportamiento. En términos prácticos, <a href="#cid-03">CID-03</a> es la puerta de entrada formal al módulo de teclado CID desde el resto del motor.

### Índice interno de bloques

* <a href="#cid-03-01">CID-03-01</a>
* <a href="#cid-03-02">CID-03-02</a>
* <a href="#cid-03-03">CID-03-03</a>
* <a href="#cid-03-04">CID-03-04</a>
* <a href="#cid-03-05">CID-03-05</a>
* <a href="#cid-03-06">CID-03-06</a>

---

### <a id="cid-03-01"></a>CID-03-01

**Qué hace:**  
Evita inclusiones múltiples de la interfaz pública del módulo de teclado CID.

**Cómo funciona:**  
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Esto previene redefiniciones y conflictos cuando el archivo es incluido desde varios puntos del proyecto.

**Pseudocódigo:**  
```text
marcar esta cabecera para inclusión única
````

**Relaciones:**

* Protege toda la interfaz declarada en <a href="#cid-03">CID-03</a>.
* Afecta indirectamente a <a href="#cid-03-03">CID-03-03</a>, <a href="#cid-03-04">CID-03-04</a>, <a href="#cid-03-05">CID-03-05</a> y <a href="#cid-03-06">CID-03-06</a>.

---

### <a id="cid-03-02"></a>CID-03-02

**Qué hace:**
Incluye los tipos base de Windows usados por la interfaz del módulo.

**Cómo funciona:**
Importa `windows.h`, que aporta definiciones como `DWORD`, necesarias para declarar correctamente el tipo de callback y las funciones públicas del módulo.

**Pseudocódigo:**

```text
incluir tipos base de Windows
```

**Relaciones:**

* Da soporte a <a href="#cid-03-03">CID-03-03</a>.
* Se apoya en <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/teclado_cid.h"><code>teclado_cid.h</code></a> como cabecera base del módulo.

---

### <a id="cid-03-03"></a>CID-03-03

**Qué hace:**
Define el tipo de callback que recibirá eventos filtrados de teclas CID.

**Cómo funciona:**
Declara un puntero a función llamado `CallbackTeclaCID`. Este callback recibe la virtual key, el scan code y el estado de pulsación, y se usa para que el módulo de captura pueda reenviar eventos ya filtrados a otra parte del sistema.

**Pseudocódigo:**

```text
definir tipo de función callback
recibe virtual key, scan code y estado de pulsación
```

**Relaciones:**

* Usa los tipos disponibles gracias a <a href="#cid-03-02">CID-03-02</a>.
* Es consumido por <a href="#cid-03-05">CID-03-05</a>.
* Se implementa realmente en <a href="#cid-02-45">CID-02-45</a> y se usa en <a href="#cid-02-33">CID-02-33</a>.

---

### <a id="cid-03-04"></a>CID-03-04

**Qué hace:**
Declara las funciones públicas de arranque y parada del hook global de teclado del sistema CID.

**Cómo funciona:**
Expone dos funciones: una para iniciar la captura global de teclado y otra para detenerla. Estas declaraciones permiten que otros módulos arranquen o apaguen el subsistema sin depender de su implementación interna.

**Pseudocódigo:**

```text
declarar función para iniciar teclado CID
declarar función para detener teclado CID
```

**Relaciones:**

* Se implementa en <a href="#cid-02-36">CID-02-36</a> y <a href="#cid-02-42">CID-02-42</a>.
* Es usado desde <a href="#cid-01-11">CID-01-11</a>, <a href="#cid-01-35">CID-01-35</a> y <a href="#cid-01-42">CID-01-42</a>.

---

### <a id="cid-03-05"></a>CID-03-05

**Qué hace:**
Declara la función que registra el callback receptor de eventos del teclado CID.

**Cómo funciona:**
Expone una operación pública que permite al resto del sistema entregar al módulo una función callback compatible con `CallbackTeclaCID`. A partir de ese registro, el módulo podrá reenviar los eventos filtrados al consumidor correspondiente.

**Pseudocódigo:**

```text
declarar función para registrar callback de teclado CID
```

**Relaciones:**

* Usa el tipo definido en <a href="#cid-03-03">CID-03-03</a>.
* Se implementa en <a href="#cid-02-45">CID-02-45</a>.
* Es usado desde <a href="#cid-01-34">CID-01-34</a>.

---

### <a id="cid-03-06"></a>CID-03-06

**Qué hace:**
Declara la consulta y la modificación del modo operativo entre CID y QWERTY.

**Cómo funciona:**
Expone tres funciones públicas: una para consultar el modo actual, otra para alternarlo y otra para fijarlo explícitamente. Estas declaraciones permiten que otros módulos sincronicen la lógica del sistema con el estado actual del teclado.

**Pseudocódigo:**

```text
declarar función para consultar modo actual
declarar función para alternar modo
declarar función para fijar modo explícito
```

**Relaciones:**

* Se implementa en <a href="#cid-02-46">CID-02-46</a>, <a href="#cid-02-47">CID-02-47</a> y <a href="#cid-02-48">CID-02-48</a>.
* Es usado desde <a href="#cid-01-18">CID-01-18</a> y <a href="#cid-01-40">CID-01-40</a>.


## CID-04

La referencia <a href="#cid-04">CID-04</a> corresponde al archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/detector_acorde.cpp"><code>detector_acorde.cpp</code></a>. Este archivo implementa el detector de acordes de CID. Su responsabilidad principal es recibir los eventos filtrados por el módulo de teclado, agrupar las teclas dentro de una ventana temporal, convertir esa agrupación en un acorde textual, resolverlo contra el diccionario y aplicar el resultado sobre la bitácora y la superposición visual.

Dentro de <a href="#cid-04">CID-04</a> también se mantiene el estado interno necesario para sincronizar accesos concurrentes, gestionar la ventana temporal del acorde, distinguir pedales de teclas normales, aplicar el modificador D10, evitar capturas erróneas durante la inyección de texto y coordinarse con el gestor de asentado y con el panel contextual. En términos prácticos, <a href="#cid-04">CID-04</a> es el módulo que transforma pulsaciones físicas CID en piezas lingüísticas reconocidas por el sistema.

### Índice interno de bloques

* <a href="#cid-04-01">CID-04-01</a>
* <a href="#cid-04-02">CID-04-02</a>
* <a href="#cid-04-03">CID-04-03</a>
* <a href="#cid-04-04">CID-04-04</a>
* <a href="#cid-04-05">CID-04-05</a>
* <a href="#cid-04-06">CID-04-06</a>
* <a href="#cid-04-07">CID-04-07</a>
* <a href="#cid-04-08">CID-04-08</a>
* <a href="#cid-04-09">CID-04-09</a>
* <a href="#cid-04-10">CID-04-10</a>
* <a href="#cid-04-11">CID-04-11</a>
* <a href="#cid-04-12">CID-04-12</a>
* <a href="#cid-04-13">CID-04-13</a>
* <a href="#cid-04-14">CID-04-14</a>
* <a href="#cid-04-15">CID-04-15</a>
* <a href="#cid-04-16">CID-04-16</a>
* <a href="#cid-04-17">CID-04-17</a>
* <a href="#cid-04-18">CID-04-18</a>
* <a href="#cid-04-19">CID-04-19</a>
* <a href="#cid-04-20">CID-04-20</a>
* <a href="#cid-04-21">CID-04-21</a>
* <a href="#cid-04-22">CID-04-22</a>
* <a href="#cid-04-23">CID-04-23</a>
* <a href="#cid-04-24">CID-04-24</a>
* <a href="#cid-04-25">CID-04-25</a>
* <a href="#cid-04-26">CID-04-26</a>
* <a href="#cid-04-27">CID-04-27</a>
* <a href="#cid-04-28">CID-04-28</a>
* <a href="#cid-04-29">CID-04-29</a>
* <a href="#cid-04-30">CID-04-30</a>
* <a href="#cid-04-31">CID-04-31</a>
* <a href="#cid-04-32">CID-04-32</a>
* <a href="#cid-04-33">CID-04-33</a>
* <a href="#cid-04-34">CID-04-34</a>
* <a href="#cid-04-35">CID-04-35</a>
* <a href="#cid-04-36">CID-04-36</a>
* <a href="#cid-04-37">CID-04-37</a>
* <a href="#cid-04-38">CID-04-38</a>
* <a href="#cid-04-39">CID-04-39</a>
* <a href="#cid-04-40">CID-04-40</a>
* <a href="#cid-04-41">CID-04-41</a>
* <a href="#cid-04-42">CID-04-42</a>
* <a href="#cid-04-43">CID-04-43</a>
* <a href="#cid-04-44">CID-04-44</a>
* <a href="#cid-04-45">CID-04-45</a>
* <a href="#cid-04-46">CID-04-46</a>
* <a href="#cid-04-47">CID-04-47</a>
* <a href="#cid-04-48">CID-04-48</a>
* <a href="#cid-04-49">CID-04-49</a>
* <a href="#cid-04-50">CID-04-50</a>
* <a href="#cid-04-51">CID-04-51</a>
* <a href="#cid-04-52">CID-04-52</a>
* <a href="#cid-04-53">CID-04-53</a>
* <a href="#cid-04-54">CID-04-54</a>
* <a href="#cid-04-55">CID-04-55</a>
* <a href="#cid-04-56">CID-04-56</a>
* <a href="#cid-04-57">CID-04-57</a>
* <a href="#cid-04-58">CID-04-58</a>
* <a href="#cid-04-59">CID-04-59</a>
* <a href="#cid-04-60">CID-04-60</a>
* <a href="#cid-04-61">CID-04-61</a>
* <a href="#cid-04-62">CID-04-62</a>
* <a href="#cid-04-63">CID-04-63</a>
* <a href="#cid-04-64">CID-04-64</a>
* <a href="#cid-04-65">CID-04-65</a>
* <a href="#cid-04-66">CID-04-66</a>
* <a href="#cid-04-67">CID-04-67</a>
* <a href="#cid-04-68">CID-04-68</a>
* <a href="#cid-04-69">CID-04-69</a>
* <a href="#cid-04-70">CID-04-70</a>

---

### <a id="cid-04-01"></a>CID-04-01

**Qué hace:**  
Incluye la interfaz pública del detector de acordes.

**Cómo funciona:**  
Importa la cabecera del propio módulo para que la implementación de este archivo coincida con las declaraciones públicas que expone al resto del sistema.

**Pseudocódigo:**  
```text
incluir interfaz pública del detector de acordes
````

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-04">CID-04</a>.
* Se corresponde con <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/detector_acorde.h"><code>detector_acorde.h</code></a>.

---

### <a id="cid-04-02"></a>CID-04-02

**Qué hace:**
Incluye módulos del motor usados para bitácora, diccionario, mapas, calibración y asentado.

**Cómo funciona:**
Este bloque conecta el detector con los subsistemas que necesita para resolver acordes, consultar nombres CID, aplicar resultados sobre la bitácora y coordinar el flujo con el asentado.

**Pseudocódigo:**

```text
incluir bitácora
incluir diccionario
incluir mapa de teclas CID
incluir calibración
incluir gestor de asentado
```

**Relaciones:**

* Da soporte a <a href="#cid-04-11">CID-04-11</a>, <a href="#cid-04-16">CID-04-16</a>, <a href="#cid-04-18">CID-04-18</a>, <a href="#cid-04-19">CID-04-19</a>, <a href="#cid-04-25">CID-04-25</a>, <a href="#cid-04-30">CID-04-30</a>, <a href="#cid-04-32">CID-04-32</a>, <a href="#cid-04-49">CID-04-49</a>, <a href="#cid-04-51">CID-04-51</a>, <a href="#cid-04-52">CID-04-52</a> y <a href="#cid-04-61">CID-04-61</a>.

---

### <a id="cid-04-03"></a>CID-04-03

**Qué hace:**
Incluye módulos auxiliares para inyección, superposición, modo de teclado y panel contextual.

**Cómo funciona:**
Permite que el detector evite procesar texto inyectado por el propio sistema, actualice la superposición visual, consulte o coordine el modo del teclado y despierte el panel contextual cuando detecta actividad escribible.

**Pseudocódigo:**

```text
incluir inyección de texto
incluir superposición
incluir teclado CID
incluir panel contextual
```

**Relaciones:**

* Da soporte a <a href="#cid-04-23">CID-04-23</a>, <a href="#cid-04-24">CID-04-24</a>, <a href="#cid-04-26">CID-04-26</a>, <a href="#cid-04-28">CID-04-28</a>, <a href="#cid-04-29">CID-04-29</a>, <a href="#cid-04-57">CID-04-57</a> y <a href="#cid-04-58">CID-04-58</a>.

---

### <a id="cid-04-04"></a>CID-04-04

**Qué hace:**
Incluye cabeceras del sistema y utilidades necesarias para temporización, vectores y texto.

**Cómo funciona:**
Aporta acceso a la API de Windows, al manejo de vectores, a algoritmos de ordenación y a cadenas anchas, que son la base del temporizador, el formateo de acordes y el registro interno del detector.

**Pseudocódigo:**

```text
incluir API de Windows
incluir vectores
incluir algoritmos
incluir cadenas
```

**Relaciones:**

* Da soporte general a todo <a href="#cid-04">CID-04</a>, especialmente a <a href="#cid-04-05">CID-04-05</a>, <a href="#cid-04-19">CID-04-19</a>, <a href="#cid-04-39">CID-04-39</a> y <a href="#cid-04-44">CID-04-44</a>.

---

### <a id="cid-04-05"></a>CID-04-05

**Qué hace:**
Envía mensajes de depuración del detector de acordes al visor de salida de Windows.

**Cómo funciona:**
Recibe una cadena `std::wstring`, añade un salto de línea y la manda al depurador mediante `OutputDebugStringW`. Sirve para registrar errores, arranques y acordes rechazados.

**Pseudocódigo:**

```text
añadir salto de línea al mensaje
enviar mensaje al depurador
```

**Relaciones:**

* Usado por <a href="#cid-04-38">CID-04-38</a>, <a href="#cid-04-39">CID-04-39</a>, <a href="#cid-04-48">CID-04-48</a>, <a href="#cid-04-50">CID-04-50</a>, <a href="#cid-04-51">CID-04-51</a>, <a href="#cid-04-68">CID-04-68</a> y <a href="#cid-04-69">CID-04-69</a>.

---

### <a id="cid-04-06"></a>CID-04-06

**Qué hace:**
Define el estado global de sincronización que protege el acceso concurrente al detector.

**Cómo funciona:**
Mantiene una sección crítica y una bandera que indica si esa sección ya fue inicializada. Toda la lógica sensible del detector usa esta sincronización para evitar estados inconsistentes entre el hook de teclado y el temporizador.

**Pseudocódigo:**

```text
crear sección crítica global
guardar bandera de inicialización
```

**Relaciones:**

* Usado por <a href="#cid-04-30">CID-04-30</a>, <a href="#cid-04-32">CID-04-32</a>, <a href="#cid-04-34">CID-04-34</a>, <a href="#cid-04-40">CID-04-40</a>, <a href="#cid-04-44">CID-04-44</a> y <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-07"></a>CID-04-07

**Qué hace:**
Mantiene el estado interno de teclas físicas presionadas y de teclas acumuladas dentro de la ventana del acorde.

**Cómo funciona:**
Usa dos buffers booleanos de 256 posiciones. `g_presionada` representa el estado físico actual de las teclas; `g_enVentana` representa las teclas candidatas acumuladas dentro de la ventana temporal del acorde.

**Pseudocódigo:**

```text
crear buffer de teclas físicamente presionadas
crear buffer de teclas acumuladas en la ventana
```

**Relaciones:**

* Usado por <a href="#cid-04-13">CID-04-13</a>, <a href="#cid-04-14">CID-04-14</a>, <a href="#cid-04-18">CID-04-18</a>, <a href="#cid-04-19">CID-04-19</a>, <a href="#cid-04-36">CID-04-36</a>, <a href="#cid-04-45">CID-04-45</a>, <a href="#cid-04-46">CID-04-46</a>, <a href="#cid-04-54">CID-04-54</a>, <a href="#cid-04-64">CID-04-64</a>, <a href="#cid-04-65">CID-04-65</a>, <a href="#cid-04-67">CID-04-67</a> y <a href="#cid-04-70">CID-04-70</a>.

---

### <a id="cid-04-08"></a>CID-04-08

**Qué hace:**
Guarda la duración configurada de la ventana temporal usada para capturar cada acorde.

**Cómo funciona:**
Mantiene en milisegundos el tiempo máximo durante el cual se acumulan teclas dentro de una misma ventana de acorde antes de cerrar y resolver la captura.

**Pseudocódigo:**

```text
guardar duración de ventana de acorde en milisegundos
```

**Relaciones:**

* Se establece en <a href="#cid-04-36">CID-04-36</a>.
* Se usa en <a href="#cid-04-39">CID-04-39</a> y <a href="#cid-04-67">CID-04-67</a>.

---

### <a id="cid-04-09"></a>CID-04-09

**Qué hace:**
Mantiene el estado de actividad de la ventana de acorde y del bloqueo hasta liberar todas las teclas.

**Cómo funciona:**
`g_ventana_activa` indica si el detector está acumulando teclas dentro de una ventana abierta. `g_esperando_liberacion` bloquea la apertura de una nueva ventana hasta que se hayan soltado todas las teclas del acorde anterior.

**Pseudocódigo:**

```text
guardar si la ventana del acorde está activa
guardar si el detector espera liberación completa
```

**Relaciones:**

* Usado por <a href="#cid-04-36">CID-04-36</a>, <a href="#cid-04-45">CID-04-45</a>, <a href="#cid-04-54">CID-04-54</a>, <a href="#cid-04-65">CID-04-65</a>, <a href="#cid-04-67">CID-04-67</a>, <a href="#cid-04-68">CID-04-68</a> y <a href="#cid-04-69">CID-04-69</a>.

---

### <a id="cid-04-10"></a>CID-04-10

**Qué hace:**
Define los recursos de temporización usados para disparar el cierre de la ventana de acorde.

**Cómo funciona:**
Mantiene una cola de temporizadores global y un temporizador concreto. Estos recursos permiten que la ventana del acorde se cierre automáticamente cuando transcurre el tiempo configurado.

**Pseudocódigo:**

```text
guardar cola global de temporizadores
guardar temporizador activo de la ventana
```

**Relaciones:**

* Usado por <a href="#cid-04-37">CID-04-37</a>, <a href="#cid-04-38">CID-04-38</a>, <a href="#cid-04-41">CID-04-41</a>, <a href="#cid-04-42">CID-04-42</a>, <a href="#cid-04-54">CID-04-54</a> y <a href="#cid-04-67">CID-04-67</a>.

---

### <a id="cid-04-11"></a>CID-04-11

**Qué hace:**
Guarda referencias globales a la bitácora activa y al diccionario conectado.

**Cómo funciona:**
Mantiene un puntero a la bitácora y un puntero constante al diccionario. El detector usa estas referencias para aplicar resultados reconocidos y para resolver acordes en el momento del cierre de la ventana.

**Pseudocódigo:**

```text
guardar referencia global a bitácora
guardar referencia global a diccionario
```

**Relaciones:**

* Usado por <a href="#cid-04-23">CID-04-23</a>, <a href="#cid-04-25">CID-04-25</a>, <a href="#cid-04-30">CID-04-30</a>, <a href="#cid-04-32">CID-04-32</a>, <a href="#cid-04-50">CID-04-50</a>, <a href="#cid-04-51">CID-04-51</a>, <a href="#cid-04-52">CID-04-52</a> y <a href="#cid-04-60">CID-04-60</a>.

---

### <a id="cid-04-12"></a>CID-04-12

**Qué hace:**
Mantiene el estado del doble toque del pedal principal para borrar el último asentado con bitácora vacía.

**Cómo funciona:**
Guarda el instante del último `up` del pedal principal y una ventana fija de doble toque de 250 ms. Esto permite detectar dos liberaciones consecutivas rápidas del pedal para ejecutar una acción especial de borrado.

**Pseudocódigo:**

```text
guardar instante del último pedal principal liberado
definir ventana temporal de doble toque
```

**Relaciones:**

* Usado por <a href="#cid-04-36">CID-04-36</a> y <a href="#cid-04-60">CID-04-60</a>.

---

### <a id="cid-04-13"></a>CID-04-13

**Qué hace:**
Comprueba si queda alguna tecla física pulsada dentro del estado interno actual del detector.

**Cómo funciona:**
Recorre el buffer `g_presionada` y devuelve verdadero en cuanto encuentra una tecla marcada como activa. Se usa para saber si ya es seguro salir del bloqueo de liberación o si hay que seguir esperando.

**Pseudocódigo:**

```text
recorrer buffer de teclas presionadas
si alguna sigue activa:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-07">CID-04-07</a>.
* Es usado por <a href="#cid-04-49">CID-04-49</a>, <a href="#cid-04-54">CID-04-54</a> y <a href="#cid-04-65">CID-04-65</a>.

---

### <a id="cid-04-14"></a>CID-04-14

**Qué hace:**
Limpia por completo la ventana temporal donde se acumulan teclas candidatas a formar un acorde.

**Cómo funciona:**
Recorre el buffer `g_enVentana` y marca todas sus posiciones como falsas. Esto vacía la captura temporal antes de abrir una nueva ventana o tras haber resuelto una anterior.

**Pseudocódigo:**

```text
recorrer buffer de ventana
marcar todas las teclas como fuera de la ventana
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-07">CID-04-07</a>.
* Es usado por <a href="#cid-04-46">CID-04-46</a> y <a href="#cid-04-67">CID-04-67</a>.

---

### <a id="cid-04-15"></a>CID-04-15

**Qué hace:**
Identifica si la tecla recibida corresponde al pedal principal físico de CID.

**Cómo funciona:**
Compara la virtual key con `VK_SPACE`. En la configuración actual del sistema, la barra espaciadora representa el pedal principal.

**Pseudocódigo:**

```text
si la virtual key es espacio:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usado por <a href="#cid-04-17">CID-04-17</a>, <a href="#cid-04-31">CID-04-31</a>, <a href="#cid-04-59">CID-04-59</a> y <a href="#cid-04-60">CID-04-60</a>.

---

### <a id="cid-04-16"></a>CID-04-16

**Qué hace:**
Identifica si un scan code corresponde a un pedal auxiliar calibrado.

**Cómo funciona:**
Consulta el nombre CID asociado al scan code y, si existe, comprueba si ese nombre pertenece a un pedal auxiliar según el mapa lógico CID.

**Pseudocódigo:**

```text
consultar nombre CID por scan code
si existe nombre y es pedal auxiliar:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usa <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a> y <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/mapa_teclas_cid.h"><code>mapa_teclas_cid.h</code></a>.
* Es usado por <a href="#cid-04-17">CID-04-17</a>.

---

### <a id="cid-04-17"></a>CID-04-17

**Qué hace:**
Determina si una entrada física corresponde a cualquier pedal operativo del sistema CID.

**Cómo funciona:**
Combina la detección del pedal principal y del pedal auxiliar. Devuelve verdadero si la tecla evaluada pertenece a cualquiera de ambos grupos.

**Pseudocódigo:**

```text
devolver si es pedal principal o pedal auxiliar
```

**Relaciones:**

* Usa <a href="#cid-04-15">CID-04-15</a> y <a href="#cid-04-16">CID-04-16</a>.
* Es usado por <a href="#cid-04-59">CID-04-59</a>.

---

### <a id="cid-04-18"></a>CID-04-18

**Qué hace:**
Repesca el estado físico actual de las teclas CID calibradas para completar la ventana del acorde.

**Cómo funciona:**
Obtiene las asignaciones calibradas, recorre sus scan codes válidos y consulta el estado físico real de cada tecla. Si alguna sigue pulsada en el momento de cierre de la ventana, la marca dentro de `g_enVentana` para no perderla.

**Pseudocódigo:**

```text
obtener asignaciones calibradas
para cada asignación válida:
    consultar estado físico de la tecla
    si sigue pulsada:
        marcarla en la ventana
```

**Relaciones:**

* Usa <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a>.
* Usa el estado de <a href="#cid-04-07">CID-04-07</a>.
* Es llamado desde <a href="#cid-04-45">CID-04-45</a>.

---

### <a id="cid-04-19"></a>CID-04-19

**Qué hace:**
Construye la representación textual ordenada del acorde actual y devuelve sus teclas físicas válidas.

**Cómo funciona:**
Limpia el vector de salida, recoge las teclas presentes en la ventana, elimina pedales, ordena las teclas según el orden lógico CID y finalmente une sus nombres con `+` para producir la clave textual del acorde.

**Pseudocódigo:**

```text
vaciar salida de teclas
recoger teclas CID válidas de la ventana
ordenarlas según orden lógico CID
unir sus nombres con "+"
devolver acorde textual
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-20">CID-04-20</a>, <a href="#cid-04-21">CID-04-21</a> y <a href="#cid-04-22">CID-04-22</a>.
* Es llamado desde <a href="#cid-04-46">CID-04-46</a>.

---

### <a id="cid-04-20"></a>CID-04-20

**Qué hace:**
Recorre la ventana temporal y recoge solo teclas CID no pedales para formar el acorde normal.

**Cómo funciona:**
Itera sobre todos los scan codes posibles, consulta su nombre CID y descarta cualquier elemento que no exista o que sea un pedal. Solo las teclas realmente presentes en `g_enVentana` y no pedales pasan al vector del acorde.

**Pseudocódigo:**

```text
recorrer todos los scan codes
consultar nombre CID
descartar teclas no CID
descartar pedales
si la tecla está en la ventana:
    añadirla al acorde
```

**Relaciones:**

* Usa <a href="#cid-04-07">CID-04-07</a>.
* Usa helpers de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a> y <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/mapa_teclas_cid.h"><code>mapa_teclas_cid.h</code></a>.
* Forma parte de <a href="#cid-04-19">CID-04-19</a>.

---

### <a id="cid-04-21"></a>CID-04-21

**Qué hace:**
Ordena las teclas del acorde según el orden lógico definido por el mapa CID.

**Cómo funciona:**
Aplica `std::sort` sobre el vector de teclas usando un comparador que consulta el nombre CID de cada tecla y su orden lógico. Esto garantiza una representación textual estable del acorde independientemente del orden físico de pulsación.

**Pseudocódigo:**

```text
ordenar teclas del acorde
comparar usando orden lógico CID por nombre
```

**Relaciones:**

* Usa utilidades de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a> y <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/mapa_teclas_cid.h"><code>mapa_teclas_cid.h</code></a>.
* Forma parte de <a href="#cid-04-19">CID-04-19</a>.

---

### <a id="cid-04-22"></a>CID-04-22

**Qué hace:**
Une los nombres de las teclas ordenadas para producir la clave textual de búsqueda del acorde.

**Cómo funciona:**
Recorre las teclas ya ordenadas, obtiene el nombre CID de cada una y construye una cadena unida por `+`. Esa cadena es la clave exacta que luego se buscará en el diccionario.

**Pseudocódigo:**

```text
crear cadena vacía
para cada tecla ordenada:
    consultar nombre CID
    añadir separador si hace falta
    añadir nombre a la cadena
devolver cadena final
```

**Relaciones:**

* Usa utilidades de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a>.
* Forma parte de <a href="#cid-04-19">CID-04-19</a>.
* Su salida se usa en <a href="#cid-04-48">CID-04-48</a>, <a href="#cid-04-50">CID-04-50</a> y <a href="#cid-04-51">CID-04-51</a>.

---

### <a id="cid-04-23"></a>CID-04-23

**Qué hace:**
Refresca la superposición visual usando el estado actual de la bitácora conectada.

**Cómo funciona:**
Si existe bitácora activa, consulta su estado visual y se lo entrega a la superposición. No modifica el contenido, solo sincroniza la representación visual con el estado actual.

**Pseudocódigo:**

```text
si no hay bitácora:
    salir
obtener estado visual de la bitácora
enviarlo a la superposición
```

**Relaciones:**

* Usa la referencia de <a href="#cid-04-11">CID-04-11</a>.
* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.h"><code>superposicion_cid.h</code></a>.
* Es usado por <a href="#cid-04-29">CID-04-29</a> y <a href="#cid-04-52">CID-04-52</a>.

---

### <a id="cid-04-24"></a>CID-04-24

**Qué hace:**
Notifica visualmente a la superposición que el acorde actual produjo un error.

**Cómo funciona:**
Invoca la función específica de error visual de la superposición. Se usa para dar retroalimentación inmediata cuando el acorde no es válido o no existe en el diccionario.

**Pseudocódigo:**

```text
notificar error de acorde a la superposición
```

**Relaciones:**

* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.h"><code>superposicion_cid.h</code></a>.
* Es usado por <a href="#cid-04-48">CID-04-48</a> y <a href="#cid-04-51">CID-04-51</a>.

---

### <a id="cid-04-25"></a>CID-04-25

**Qué hace:**
Aplica el modificador D10 sobre la última pieza asentada cuando la bitácora lo permite.

**Cómo funciona:**
Comprueba si existe una última pieza asentada, intenta aplicar el modificador D10 sobre ella y, si lo consigue, actualiza bitácora, superposición y actividad CID. Si no puede aplicarse, informa visualmente de ello sin modificar el estado.

**Pseudocódigo:**

```text
si no hay pieza asentada:
    informar que no hay nada que modificar
intentar aplicar D10
si no tiene efecto:
    informar visualmente
si se aplica:
    anotar token visual
    refrescar superposición
    notificar actividad CID
    informar aplicación correcta
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-26">CID-04-26</a>, <a href="#cid-04-27">CID-04-27</a>, <a href="#cid-04-28">CID-04-28</a> y <a href="#cid-04-29">CID-04-29</a>.
* Es usado por <a href="#cid-04-49">CID-04-49</a>.

---

### <a id="cid-04-26"></a>CID-04-26

**Qué hace:**
Rechaza el modificador si no hay nada asentado todavía y muestra un estado visual neutro.

**Cómo funciona:**
Comprueba si la bitácora no existe o está vacía. En ese caso actualiza la superposición con un mensaje de ausencia de pieza y devuelve falso.

**Pseudocódigo:**

```text
si no hay bitácora o está vacía:
    mostrar que no hay nada que modificar
    devolver falso
```

**Relaciones:**

* Usa la referencia de <a href="#cid-04-11">CID-04-11</a>.
* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.h"><code>superposicion_cid.h</code></a>.
* Forma parte de <a href="#cid-04-25">CID-04-25</a>.

---

### <a id="cid-04-27"></a>CID-04-27

**Qué hace:**
Intenta aplicar el modificador D10 sobre la última pieza de la bitácora.

**Cómo funciona:**
Crea un buffer de error y delega la operación en la bitácora. El resultado de esa llamada determina si el modificador tuvo efecto real o no.

**Pseudocódigo:**

```text
crear buffer de error
pedir a la bitácora aplicar D10
guardar si la operación tuvo éxito
```

**Relaciones:**

* Usa la bitácora referenciada en <a href="#cid-04-11">CID-04-11</a>.
* Forma parte de <a href="#cid-04-25">CID-04-25</a>.

---

### <a id="cid-04-28"></a>CID-04-28

**Qué hace:**
Informa visualmente cuando D10 no produce ningún efecto sobre la pieza actual.

**Cómo funciona:**
Si la operación anterior devuelve falso, el bloque actualiza el texto del último asentado con un mensaje de “sin efecto” y devuelve falso al llamador.

**Pseudocódigo:**

```text
si D10 no tuvo efecto:
    mostrar mensaje de sin efecto
    devolver falso
```

**Relaciones:**

* Usa la superposición de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/superposicion_cid.h"><code>superposicion_cid.h</code></a>.
* Forma parte de <a href="#cid-04-25">CID-04-25</a>.

---

### <a id="cid-04-29"></a>CID-04-29

**Qué hace:**
Registra el modificador aplicado, refresca la superposición y notifica actividad CID.

**Cómo funciona:**
Anota un token visual de modificación en la bitácora, sincroniza la superposición, notifica actividad CID al sistema y actualiza el mensaje del último asentado indicando aplicación correcta.

**Pseudocódigo:**

```text
anotar token visual de modificación
refrescar superposición
notificar actividad CID
mostrar mensaje de D10 aplicado
devolver verdadero
```

**Relaciones:**

* Usa la bitácora de <a href="#cid-04-11">CID-04-11</a>.
* Usa <a href="#cid-04-23">CID-04-23</a>.
* Llama a funcionalidad de asentado y superposición.
* Forma parte de <a href="#cid-04-25">CID-04-25</a>.

---

### <a id="cid-04-30"></a>CID-04-30

**Qué hace:**
Conecta la bitácora activa al detector y sincroniza la superposición con su estado visual actual.

**Cómo funciona:**
Comprueba primero si la sincronización del detector ya fue inicializada. Si lo fue, entra en sección crítica, guarda la nueva referencia de bitácora y sale. Después, fuera del lock, sincroniza la superposición con el estado visual de la bitácora si esta existe.

**Pseudocódigo:**

```text
si la sincronización no está lista:
    salir
entrar en sección crítica
guardar referencia a bitácora
salir de sección crítica
si existe bitácora:
    sincronizar superposición
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-31">CID-04-31</a>.
* Actualiza la referencia global de <a href="#cid-04-11">CID-04-11</a>.
* Es llamado desde <a href="#cid-01-34">CID-01-34</a>.

---

### <a id="cid-04-31"></a>CID-04-31

**Qué hace:**
Ignora la conexión de bitácora si la sincronización interna del detector aún no ha sido inicializada.

**Cómo funciona:**
Consulta la bandera `g_cs_iniciado`. Si la sección crítica aún no existe, el bloque aborta la operación para no trabajar sobre un estado de sincronización inválido.

**Pseudocódigo:**

```text
si la sección crítica no está iniciada:
    salir sin conectar
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-06">CID-04-06</a>.
* Forma parte de <a href="#cid-04-30">CID-04-30</a>.

---

### <a id="cid-04-32"></a>CID-04-32

**Qué hace:**
Conecta el diccionario activo que se usará para resolver acordes reconocidos.

**Cómo funciona:**
Comprueba primero que la sincronización del detector exista. Si existe, entra en sección crítica, actualiza la referencia global al diccionario y sale. No realiza validaciones adicionales.

**Pseudocódigo:**

```text
si la sincronización no está lista:
    salir
entrar en sección crítica
guardar referencia a diccionario
salir de sección crítica
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-33">CID-04-33</a>.
* Actualiza la referencia global de <a href="#cid-04-11">CID-04-11</a>.
* Es llamado desde <a href="#cid-01-34">CID-01-34</a>.

---

### <a id="cid-04-33"></a>CID-04-33

**Qué hace:**
Ignora la conexión de diccionario si la sincronización interna del detector aún no ha sido inicializada.

**Cómo funciona:**
Verifica la misma condición de seguridad que el bloque equivalente de bitácora: si la sección crítica no existe todavía, la conexión se descarta.

**Pseudocódigo:**

```text
si la sección crítica no está iniciada:
    salir sin conectar
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-06">CID-04-06</a>.
* Forma parte de <a href="#cid-04-32">CID-04-32</a>.

---

### <a id="cid-04-34"></a>CID-04-34

**Qué hace:**
Inicializa el detector de acordes, reinicia su estado interno y prepara la temporización base.

**Cómo funciona:**
Se asegura de que la sección crítica exista, entra en ella, configura la duración efectiva de la ventana, reinicia buffers y banderas, crea la cola de temporizadores si no existe, evalúa si la inicialización fue correcta y finalmente registra el resultado.

**Pseudocódigo:**

```text
inicializar sincronización si hace falta
entrar en sección crítica
configurar ventana temporal
reiniciar buffers y banderas
crear cola de temporizadores si no existe
salir de sección crítica
si falló:
    registrar error
    devolver falso
registrar arranque correcto
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-35">CID-04-35</a> a <a href="#cid-04-39">CID-04-39</a>.
* Es llamado desde <a href="#cid-01-33">CID-01-33</a>.

---

### <a id="cid-04-35"></a>CID-04-35

**Qué hace:**
Inicializa la sección crítica interna la primera vez que se arranca el detector.

**Cómo funciona:**
Comprueba la bandera `g_cs_iniciado` y, si todavía no se había creado la sección crítica, la inicializa y marca la bandera como activa.

**Pseudocódigo:**

```text
si la sección crítica no existe:
    inicializar sección crítica
    marcar sincronización como activa
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-06">CID-04-06</a>.
* Forma parte de <a href="#cid-04-34">CID-04-34</a>.

---

### <a id="cid-04-36"></a>CID-04-36

**Qué hace:**
Ajusta la duración efectiva de la ventana y reinicia buffers y banderas internas.

**Cómo funciona:**
Si el valor recibido es válido lo adopta; en caso contrario usa 60 ms. Después limpia `g_presionada`, `g_enVentana`, reinicia el estado de ventana, el bloqueo de liberación y el estado del doble toque del pedal principal.

**Pseudocódigo:**

```text
fijar duración efectiva de ventana
limpiar buffer de teclas presionadas
limpiar buffer de ventana
desactivar ventana
desactivar espera de liberación
reiniciar doble toque del pedal
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-07">CID-04-07</a>, <a href="#cid-04-08">CID-04-08</a>, <a href="#cid-04-09">CID-04-09</a> y <a href="#cid-04-12">CID-04-12</a>.
* Forma parte de <a href="#cid-04-34">CID-04-34</a>.

---

### <a id="cid-04-37"></a>CID-04-37

**Qué hace:**
Crea la cola de temporizadores del detector si todavía no existe.

**Cómo funciona:**
Comprueba si `g_timerQueue` está vacía y, si lo está, llama a `CreateTimerQueue`. Luego deja preparado el valor que permitirá decidir si la inicialización fue correcta.

**Pseudocódigo:**

```text
si no existe cola de temporizadores:
    crearla
comprobar si la cola quedó creada
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-10">CID-04-10</a>.
* Forma parte de <a href="#cid-04-34">CID-04-34</a>.

---

### <a id="cid-04-38"></a>CID-04-38

**Qué hace:**
Informa del fallo de inicialización si no pudo crearse la cola de temporizadores.

**Cómo funciona:**
Si la cola no quedó creada, registra un error en depuración y devuelve falso al llamador, impidiendo que el detector arranque en un estado incompleto.

**Pseudocódigo:**

```text
si no existe cola de temporizadores:
    escribir error
    devolver falso
```

**Relaciones:**

* Usa <a href="#cid-04-05">CID-04-05</a>.
* Forma parte de <a href="#cid-04-34">CID-04-34</a>.

---

### <a id="cid-04-39"></a>CID-04-39

**Qué hace:**
Registra el arranque correcto del detector y la ventana temporal configurada.

**Cómo funciona:**
Construye un mensaje con la duración efectiva de la ventana y lo envía al sistema de log, devolviendo después éxito al llamador.

**Pseudocódigo:**

```text
construir mensaje con ventana temporal
escribir log de arranque
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-04-05">CID-04-05</a> y <a href="#cid-04-08">CID-04-08</a>.
* Forma parte de <a href="#cid-04-34">CID-04-34</a>.

---

### <a id="cid-04-40"></a>CID-04-40

**Qué hace:**
Detiene el detector liberando temporizadores, cola de temporización y sincronización interna.

**Cómo funciona:**
Elimina primero el temporizador activo si existe, después destruye la cola completa de temporizadores y por último libera la sección crítica si había sido inicializada.

**Pseudocódigo:**

```text
si existe temporizador:
    eliminarlo
si existe cola de temporizadores:
    eliminarla
si existe sincronización:
    destruirla
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-41">CID-04-41</a>, <a href="#cid-04-42">CID-04-42</a> y <a href="#cid-04-43">CID-04-43</a>.
* Es llamado desde <a href="#cid-01-11">CID-01-11</a> y <a href="#cid-01-42">CID-01-42</a>.

---

### <a id="cid-04-41"></a>CID-04-41

**Qué hace:**
Elimina el temporizador activo si todavía existe dentro de la cola del detector.

**Cómo funciona:**
Comprueba que tanto `g_timer` como `g_timerQueue` existan. Si existen, elimina el temporizador y limpia la referencia global.

**Pseudocódigo:**

```text
si existe temporizador activo y cola:
    eliminar temporizador
    limpiar referencia al temporizador
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-10">CID-04-10</a>.
* Forma parte de <a href="#cid-04-40">CID-04-40</a>.

---

### <a id="cid-04-42"></a>CID-04-42

**Qué hace:**
Elimina la cola de temporizadores completa cuando el detector se apaga.

**Cómo funciona:**
Si la cola existe, llama a `DeleteTimerQueueEx` y limpia la referencia global para dejar el detector completamente apagado.

**Pseudocódigo:**

```text
si existe cola de temporizadores:
    eliminar cola
    limpiar referencia global
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-10">CID-04-10</a>.
* Forma parte de <a href="#cid-04-40">CID-04-40</a>.

---

### <a id="cid-04-43"></a>CID-04-43

**Qué hace:**
Libera la sección crítica del detector si había sido inicializada previamente.

**Cómo funciona:**
Comprueba la bandera de sincronización y, si era verdadera, destruye la sección crítica y marca el detector como no inicializado a nivel de lock.

**Pseudocódigo:**

```text
si la sincronización estaba iniciada:
    destruir sección crítica
    marcar sincronización como apagada
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-06">CID-04-06</a>.
* Forma parte de <a href="#cid-04-40">CID-04-40</a>.

---

### <a id="cid-04-44"></a>CID-04-44

**Qué hace:**
Cierra la ventana temporal del acorde, resuelve su resultado y actualiza el estado del detector.

**Cómo funciona:**
Es el callback del temporizador. Entra en sección crítica, cierra la ventana, repesca teclas aún pulsadas, construye el acorde, limpia la ventana, procesa el resultado si hay teclas válidas, ajusta el bloqueo de liberación y marca el temporizador como consumido.

**Pseudocódigo:**

```text
entrar en sección crítica
cerrar ventana de acorde
repescar teclas aún pulsadas
construir acorde y limpiar ventana
si hay teclas válidas:
    procesar acorde
actualizar espera de liberación
marcar temporizador como consumido
salir de sección crítica
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-45">CID-04-45</a> a <a href="#cid-04-54">CID-04-54</a>.
* Es instalado desde <a href="#cid-04-67">CID-04-67</a>.

---

### <a id="cid-04-45"></a>CID-04-45

**Qué hace:**
Marca la ventana como cerrada y repesca las teclas físicas que sigan realmente pulsadas.

**Cómo funciona:**
Desactiva la bandera de ventana activa y llama al helper que recorre el estado físico actual de las teclas calibradas para completar la captura antes de resolver el acorde.

**Pseudocódigo:**

```text
marcar ventana como cerrada
repescar teclas aún presionadas físicamente
```

**Relaciones:**

* Usa <a href="#cid-04-09">CID-04-09</a> y <a href="#cid-04-18">CID-04-18</a>.
* Forma parte de <a href="#cid-04-44">CID-04-44</a>.

---

### <a id="cid-04-46"></a>CID-04-46

**Qué hace:**
Construye el acorde desde la ventana actual y limpia el buffer temporal de captura.

**Cómo funciona:**
Declara el vector de teclas, obtiene la cadena textual del acorde a partir de la ventana y luego limpia `g_enVentana` para dejar el detector preparado para futuras capturas.

**Pseudocódigo:**

```text
crear contenedor de teclas
formatear acorde desde la ventana
limpiar ventana temporal
```

**Relaciones:**

* Usa <a href="#cid-04-19">CID-04-19</a> y <a href="#cid-04-14">CID-04-14</a>.
* Forma parte de <a href="#cid-04-44">CID-04-44</a>.

---

### <a id="cid-04-47"></a>CID-04-47

**Qué hace:**
Procesa el acorde solo si la ventana llegó a contener teclas válidas.

**Cómo funciona:**
Comprueba si el vector `teclas` está vacío. Solo si contiene una o más teclas entra en las ramas de validación por tamaño, tratamiento especial de D10, comprobación de diccionario y reconocimiento normal.

**Pseudocódigo:**

```text
si el acorde tiene teclas válidas:
    procesar sus ramas de resolución
```

**Relaciones:**

* Forma parte de <a href="#cid-04-44">CID-04-44</a>.
* Contiene lógicamente <a href="#cid-04-48">CID-04-48</a> a <a href="#cid-04-53">CID-04-53</a>.

---

### <a id="cid-04-48"></a>CID-04-48

**Qué hace:**
Rechaza acordes de más de tres teclas y muestra un error visual al usuario.

**Cómo funciona:**
Si el acorde supera tres teclas, registra un mensaje de error, actualiza el texto de la superposición y dispara la notificación visual de error. No intenta resolver ese acorde en el diccionario.

**Pseudocódigo:**

```text
si el acorde tiene más de tres teclas:
    escribir log de rechazo
    mostrar mensaje visual de acorde demasiado grande
    notificar error visual
```

**Relaciones:**

* Usa <a href="#cid-04-05">CID-04-05</a> y <a href="#cid-04-24">CID-04-24</a>.
* Forma parte de <a href="#cid-04-47">CID-04-47</a>.

---

### <a id="cid-04-49"></a>CID-04-49

**Qué hace:**
Trata una D10 solitaria como modificador sobre la última pieza asentada.

**Cómo funciona:**
Si el acorde tiene exactamente una tecla, obtiene su nombre CID y comprueba si es la marcadora de tilde. Si lo es, aplica el modificador D10, actualiza el bloqueo de liberación, consume el temporizador y sale de forma temprana del callback.

**Pseudocódigo:**

```text
si el acorde tiene una sola tecla:
    consultar nombre CID
    si es D10:
        aplicar modificador D10
        actualizar espera de liberación
        consumir temporizador
        salir del callback
```

**Relaciones:**

* Usa <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a> y <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/mapa_teclas_cid.h"><code>mapa_teclas_cid.h</code></a>.
* Usa <a href="#cid-04-25">CID-04-25</a> y <a href="#cid-04-13">CID-04-13</a>.
* Forma parte de <a href="#cid-04-47">CID-04-47</a>.

---

### <a id="cid-04-50"></a>CID-04-50

**Qué hace:**
Informa error si el acorde llegó a resolverse sin un diccionario conectado.

**Cómo funciona:**
Comprueba si la referencia global al diccionario está vacía. Si lo está, registra un error y actualiza la superposición con un mensaje indicando que el diccionario no está conectado.

**Pseudocódigo:**

```text
si no existe diccionario conectado:
    escribir error
    mostrar mensaje visual de diccionario no conectado
```

**Relaciones:**

* Usa la referencia de <a href="#cid-04-11">CID-04-11</a>.
* Usa <a href="#cid-04-05">CID-04-05</a>.
* Forma parte de <a href="#cid-04-47">CID-04-47</a>.

---

### <a id="cid-04-51"></a>CID-04-51

**Qué hace:**
Busca el acorde en el diccionario y rechaza visualmente los no reconocidos.

**Cómo funciona:**
Declara una entrada de diccionario y consulta la clave textual del acorde. Si la búsqueda falla, registra el acorde desconocido y dispara la notificación visual de error. Si la búsqueda tiene éxito, deja preparada la entrada para la aplicación normal.

**Pseudocódigo:**

```text
crear contenedor de entrada de diccionario
buscar acorde textual
si no existe:
    escribir log de acorde desconocido
    notificar error visual
si existe:
    continuar con aplicación del resultado
```

**Relaciones:**

* Usa la referencia al diccionario de <a href="#cid-04-11">CID-04-11</a>.
* Usa <a href="#cid-04-05">CID-04-05</a> y <a href="#cid-04-24">CID-04-24</a>.
* Precede a <a href="#cid-04-52">CID-04-52</a>.
* Forma parte de <a href="#cid-04-47">CID-04-47</a>.

---

### <a id="cid-04-52"></a>CID-04-52

**Qué hace:**
Anota la pieza reconocida en la bitácora y refresca la superposición visual.

**Cómo funciona:**
Si existe bitácora conectada, añade la pieza reconocida, registra su token visual y sincroniza la superposición con el nuevo estado. Este bloque solo se ejecuta cuando el acorde fue reconocido correctamente por el diccionario.

**Pseudocódigo:**

```text
si existe bitácora:
    anotar resultado crudo
    anotar token visual de pieza
    refrescar superposición
```

**Relaciones:**

* Usa la referencia de <a href="#cid-04-11">CID-04-11</a>.
* Usa <a href="#cid-04-23">CID-04-23</a>.
* Forma parte de <a href="#cid-04-47">CID-04-47</a>.

---

### <a id="cid-04-53"></a>CID-04-53

**Qué hace:**
Notifica actividad CID tras reconocer y aplicar correctamente un acorde válido.

**Cómo funciona:**
Llama a la notificación de actividad CID una vez que el acorde ya fue reconocido y, en su caso, aplicado sobre la bitácora. Sirve para mantener sincronizado el resto del flujo de asentado o actividad reciente.

**Pseudocódigo:**

```text
notificar actividad CID
```

**Relaciones:**

* Forma parte de <a href="#cid-04-47">CID-04-47</a>.
* Se apoya en el éxito de <a href="#cid-04-51">CID-04-51</a> y <a href="#cid-04-52">CID-04-52</a>.

---

### <a id="cid-04-54"></a>CID-04-54

**Qué hace:**
Activa el bloqueo hasta liberar teclas y marca el temporizador como ya consumido.

**Cómo funciona:**
Calcula si aún quedan teclas físicas pulsadas, usa ese resultado para fijar `g_esperando_liberacion` y limpia la referencia al temporizador activo. Con esto impide abrir una nueva ventana de acorde demasiado pronto.

**Pseudocódigo:**

```text
calcular si aún hay teclas presionadas
actualizar espera de liberación
limpiar referencia al temporizador
```

**Relaciones:**

* Usa <a href="#cid-04-13">CID-04-13</a>, <a href="#cid-04-09">CID-04-09</a> y <a href="#cid-04-10">CID-04-10</a>.
* Forma parte de <a href="#cid-04-44">CID-04-44</a>.

---

### <a id="cid-04-55"></a>CID-04-55

**Qué hace:**
Recibe eventos filtrados del módulo de teclado y alimenta la lógica de captura de acordes.

**Cómo funciona:**
Es el punto de entrada del detector desde el módulo de teclado. Valida el evento, ignora inyección propia, despierta el panel contextual, trata pedales con ruta especial, resuelve el nombre CID de teclas calibradas y, para teclas normales, gestiona la apertura y acumulación dentro de la ventana temporal del acorde.

**Pseudocódigo:**

```text
validar evento recibido
ignorar inyección propia
notificar actividad escribible
si la tecla es un pedal:
    procesar ruta de pedal
si no es pedal:
    resolver nombre CID
    descartar no calibradas
    actualizar estado físico
    gestionar bloqueo de liberación
    abrir o ampliar ventana de acorde
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-56">CID-04-56</a> a <a href="#cid-04-70">CID-04-70</a>.
* Es registrado como callback desde <a href="#cid-01-34">CID-01-34</a> a través de <a href="#cid-02-45">CID-02-45</a> y llamado desde <a href="#cid-02-33">CID-02-33</a>.

---

### <a id="cid-04-56"></a>CID-04-56

**Qué hace:**
Descarta eventos si el detector aún no está listo o si el scan code no es utilizable.

**Cómo funciona:**
Primero comprueba si la sincronización interna sigue sin inicializarse. Después valida que el scan code esté en rango, salvo para la barra espaciadora, que se permite como pedal principal aunque no dependa del scan code.

**Pseudocódigo:**

```text
si el detector no está iniciado:
    salir
si el scan code no es válido y no es espacio:
    salir
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-06">CID-04-06</a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-57"></a>CID-04-57

**Qué hace:**
Ignora cualquier evento generado por la propia inyección de texto del sistema CID.

**Cómo funciona:**
Consulta `InyeccionActiva()` y, si la respuesta es positiva, sale inmediatamente sin dejar que el detector procese esos eventos como si fueran pulsaciones físicas reales.

**Pseudocódigo:**

```text
si la inyección de texto está activa:
    salir
```

**Relaciones:**

* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/inyeccion_texto.h"><code>inyeccion_texto.h</code></a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-58"></a>CID-04-58

**Qué hace:**
Notifica actividad escribible al panel contextual al recibir una nueva pulsación física.

**Cómo funciona:**
Cuando el evento recibido es una pulsación, informa al panel contextual de que existe actividad escribible. Esta notificación ocurre antes de decidir si la tecla es pedal o tecla normal.

**Pseudocódigo:**

```text
si el evento es pulsación:
    notificar actividad escribible al panel
```

**Relaciones:**

* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/panel_contexto_texto.h"><code>panel_contexto_texto.h</code></a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-59"></a>CID-04-59

**Qué hace:**
Procesa los pedales CID con tratamiento especial para espacio y doble toque de borrado.

**Cómo funciona:**
Si la entrada física corresponde a cualquier pedal, el bloque deriva la lógica hacia la ruta de pedales. En el caso del pedal principal, además habilita el tratamiento específico de doble toque para borrado cuando la bitácora está vacía.

**Pseudocódigo:**

```text
si la tecla es un pedal CID:
    si es el pedal principal:
        procesar lógica especial de doble toque
    reenviar evento al gestor de pedal
    terminar
```

**Relaciones:**

* Usa <a href="#cid-04-17">CID-04-17</a> y <a href="#cid-04-15">CID-04-15</a>.
* Contiene internamente <a href="#cid-04-60">CID-04-60</a> y <a href="#cid-04-61">CID-04-61</a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-60"></a>CID-04-60

**Qué hace:**
Gestiona el doble toque del pedal principal para borrar el último asentado con bitácora vacía.

**Cómo funciona:**
Cuando se libera el pedal principal, obtiene el instante actual y, si la bitácora existe y está vacía, compara ese instante con el último `up` registrado. Si ambos eventos están dentro de la ventana permitida, notifica el evento de pedal al gestor, borra el último asentado y consume la secuencia especial.

**Pseudocódigo:**

```text
si el evento es liberación del pedal principal:
    leer tiempo actual
    si la bitácora está vacía:
        si hubo liberación previa reciente:
            reenviar evento de pedal
            borrar último asentado
            reiniciar doble toque
            salir
    guardar instante actual como último up
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-11">CID-04-11</a> y <a href="#cid-04-12">CID-04-12</a>.
* Llama a funcionalidad del gestor/asentado.
* Forma parte de <a href="#cid-04-59">CID-04-59</a>.

---

### <a id="cid-04-61"></a>CID-04-61

**Qué hace:**
Reenvía la pulsación o liberación del pedal al gestor correspondiente y termina la ruta.

**Cómo funciona:**
Invoca el gestor del pedal principal con el estado de pulsación recibido y sale inmediatamente de la función, evitando que el evento continúe por la ruta normal de teclas de acorde.

**Pseudocódigo:**

```text
reenviar estado del pedal al gestor correspondiente
salir de la función
```

**Relaciones:**

* Llama a funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/gestor_asentado.h"><code>gestor_asentado.h</code></a>.
* Forma parte de <a href="#cid-04-59">CID-04-59</a>.

---

### <a id="cid-04-62"></a>CID-04-62

**Qué hace:**
Resuelve el nombre CID del scan code recibido y descarta teclas no calibradas.

**Cómo funciona:**
Consulta el nombre CID asociado al scan code. Si no existe nombre, la tecla no pertenece al conjunto calibrado y se descarta.

**Pseudocódigo:**

```text
consultar nombre CID por scan code
si no existe nombre:
    salir
```

**Relaciones:**

* Usa funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/calibracion_teclado.h"><code>calibracion_teclado.h</code></a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.
* Precede a <a href="#cid-04-63">CID-04-63</a>.

---

### <a id="cid-04-63"></a>CID-04-63

**Qué hace:**
Excluye del acorde normal cualquier tecla calibrada que realmente sea un pedal.

**Cómo funciona:**
Aunque la tecla tenga nombre CID, este bloque comprueba si el nombre corresponde a un pedal principal o auxiliar. Si es así, la descarta para que no forme parte del acorde textual normal.

**Pseudocódigo:**

```text
si la tecla calibrada es un pedal:
    salir
```

**Relaciones:**

* Usa funcionalidad de <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/mapa_teclas_cid.h"><code>mapa_teclas_cid.h</code></a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-64"></a>CID-04-64

**Qué hace:**
Actualiza el estado físico de la tecla recibida dentro del detector.

**Cómo funciona:**
Una vez dentro de la sección crítica, marca en `g_presionada` si la tecla asociada al scan code está actualmente pulsada o liberada.

**Pseudocódigo:**

```text
guardar en buffer si la tecla está presionada o no
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-07">CID-04-07</a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-65"></a>CID-04-65

**Qué hace:**
Mantiene el bloqueo hasta que todas las teclas hayan sido liberadas tras el acorde anterior.

**Cómo funciona:**
Si el detector está en modo de espera de liberación, comprueba si ya no queda ninguna tecla pulsada. Si todavía quedan teclas, conserva el bloqueo; en cualquier caso, sale sin abrir ni ampliar ninguna ventana nueva.

**Pseudocódigo:**

```text
si el detector espera liberación:
    si ya no hay teclas presionadas:
        quitar bloqueo
    salir sin procesar más
```

**Relaciones:**

* Usa <a href="#cid-04-09">CID-04-09</a> y <a href="#cid-04-13">CID-04-13</a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-66"></a>CID-04-66

**Qué hace:**
En una nueva pulsación abre la ventana de acorde o añade la tecla a la ya existente.

**Cómo funciona:**
Solo actúa en eventos de pulsación. Si no había ventana abierta, inicia el proceso de apertura y temporización. Si la ventana ya estaba activa, simplemente añade la nueva tecla al buffer temporal.

**Pseudocódigo:**

```text
si el evento es pulsación:
    si no hay ventana activa:
        abrir nueva ventana
    si ya hay ventana activa:
        añadir tecla a la ventana
```

**Relaciones:**

* Contiene internamente <a href="#cid-04-67">CID-04-67</a> a <a href="#cid-04-70">CID-04-70</a>.
* Forma parte de <a href="#cid-04-55">CID-04-55</a>.

---

### <a id="cid-04-67"></a>CID-04-67

**Qué hace:**
Abre una nueva ventana de acorde con temporizador si todavía no había una activa.

**Cómo funciona:**
Activa la bandera de ventana, limpia el buffer temporal, marca la tecla actual dentro de la ventana y, si existe cola de temporizadores, intenta crear un temporizador que disparará el cierre tras `g_ventana_ms`.

**Pseudocódigo:**

```text
activar ventana de acorde
limpiar ventana temporal
añadir tecla actual a la ventana
si existe cola de temporizadores:
    crear temporizador de cierre
```

**Relaciones:**

* Usa <a href="#cid-04-09">CID-04-09</a>, <a href="#cid-04-14">CID-04-14</a>, <a href="#cid-04-10">CID-04-10</a> y <a href="#cid-04-08">CID-04-08</a>.
* Instala <a href="#cid-04-44">CID-04-44</a> como callback del temporizador.
* Forma parte de <a href="#cid-04-66">CID-04-66</a>.

---

### <a id="cid-04-68"></a>CID-04-68

**Qué hace:**
Revierte la apertura de ventana si no pudo crearse el temporizador del acorde.

**Cómo funciona:**
Si `CreateTimerQueueTimer` falla, desactiva la ventana recién abierta, limpia la referencia al temporizador y registra el error en depuración.

**Pseudocódigo:**

```text
si falla la creación del temporizador:
    desactivar ventana
    limpiar referencia al temporizador
    escribir error
```

**Relaciones:**

* Usa <a href="#cid-04-05">CID-04-05</a>, <a href="#cid-04-09">CID-04-09</a> y <a href="#cid-04-10">CID-04-10</a>.
* Forma parte de <a href="#cid-04-67">CID-04-67</a>.

---

### <a id="cid-04-69"></a>CID-04-69

**Qué hace:**
Revierte la apertura de ventana si la cola de temporizadores no existe.

**Cómo funciona:**
Si el detector intenta abrir una ventana pero no tiene cola de temporizadores disponible, cancela la apertura y registra el fallo como error interno.

**Pseudocódigo:**

```text
si no existe cola de temporizadores:
    desactivar ventana
    escribir error
```

**Relaciones:**

* Usa <a href="#cid-04-05">CID-04-05</a> y <a href="#cid-04-09">CID-04-09</a>.
* Forma parte de <a href="#cid-04-67">CID-04-67</a>.

---

### <a id="cid-04-70"></a>CID-04-70

**Qué hace:**
Añade la tecla recién pulsada a la ventana de acorde ya abierta.

**Cómo funciona:**
Si la ventana ya estaba activa, marca el scan code actual dentro del buffer temporal `g_enVentana`, ampliando así el conjunto de teclas que formarán el acorde final.

**Pseudocódigo:**

```text
marcar tecla actual dentro de la ventana activa
```

**Relaciones:**

* Usa el estado de <a href="#cid-04-07">CID-04-07</a>.
* Forma parte de <a href="#cid-04-66">CID-04-66</a>.


## CID-05

La referencia <a href="#cid-05">CID-05</a> corresponde al archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/detector_acorde.h"><code>detector_acorde.h</code></a>. Este archivo define la interfaz pública del detector de acordes CID. Su responsabilidad es exponer al resto del proyecto las funciones necesarias para arrancar y detener el detector, conectar la bitácora y el diccionario activos, y recibir los eventos de teclado ya filtrados por el módulo de captura.

Dentro de <a href="#cid-05">CID-05</a> no hay lógica de ejecución directa. Su función es fijar el contrato público que implementa <a href="#cid-04">CID-04</a>, separando la interfaz del comportamiento interno. En términos prácticos, <a href="#cid-05">CID-05</a> es la puerta de entrada formal al detector de acordes desde el resto del motor.

### Índice interno de bloques

* <a href="#cid-05-01">CID-05-01</a>
* <a href="#cid-05-02">CID-05-02</a>
* <a href="#cid-05-03">CID-05-03</a>
* <a href="#cid-05-04">CID-05-04</a>
* <a href="#cid-05-05">CID-05-05</a>
* <a href="#cid-05-06">CID-05-06</a>

---

### <a id="cid-05-01"></a>CID-05-01

**Qué hace:**  
Evita inclusiones múltiples de la interfaz pública del detector de acordes CID.

**Cómo funciona:**  
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Esto previene redefiniciones cuando el archivo es incluido desde varios puntos del proyecto.

**Pseudocódigo:**  
```text
marcar esta cabecera para inclusión única
````

**Relaciones:**

* Protege toda la interfaz declarada en <a href="#cid-05">CID-05</a>.
* Afecta indirectamente a <a href="#cid-05-03">CID-05-03</a>, <a href="#cid-05-04">CID-05-04</a>, <a href="#cid-05-05">CID-05-05</a> y <a href="#cid-05-06">CID-05-06</a>.

---

### <a id="cid-05-02"></a>CID-05-02

**Qué hace:**
Incluye los tipos base de Windows usados por la interfaz del detector.

**Cómo funciona:**
Importa `windows.h`, que aporta definiciones como `DWORD`, necesarias para declarar correctamente la recepción de eventos de teclado y otras firmas públicas del detector.

**Pseudocódigo:**

```text
incluir tipos base de Windows
```

**Relaciones:**

* Da soporte a <a href="#cid-05-06">CID-05-06</a>.
* Se apoya en <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/detector_acorde.h"><code>detector_acorde.h</code></a> como cabecera base del módulo.

---

### <a id="cid-05-03"></a>CID-05-03

**Qué hace:**
Declara en adelantado los tipos conectables de bitácora y diccionario usados por el detector.

**Cómo funciona:**
Usa declaraciones adelantadas de `BitacoraCID` y `DiccionarioCID` para poder declarar punteros a estos tipos sin incluir todavía sus cabeceras completas. Esto reduce dependencias y evita acoplamientos innecesarios en la interfaz pública.

**Pseudocódigo:**

```text
declarar clase BitacoraCID
declarar clase DiccionarioCID
```

**Relaciones:**

* Da soporte a <a href="#cid-05-05">CID-05-05</a>.
* Se implementa realmente junto al uso de esos tipos en <a href="#cid-04-11">CID-04-11</a>, <a href="#cid-04-30">CID-04-30</a> y <a href="#cid-04-32">CID-04-32</a>.

---

### <a id="cid-05-04"></a>CID-05-04

**Qué hace:**
Declara el arranque y la detención del detector de acordes basado en ventana temporal.

**Cómo funciona:**
Expone dos funciones públicas: una para iniciar el detector con una duración de ventana determinada y otra para apagarlo y liberar sus recursos. Esto permite que el resto del sistema controle el ciclo de vida del detector sin depender de su implementación interna.

**Pseudocódigo:**

```text
declarar función para iniciar detector con ventana temporal
declarar función para detener detector
```

**Relaciones:**

* Se implementa en <a href="#cid-04-34">CID-04-34</a> y <a href="#cid-04-40">CID-04-40</a>.
* Es usado desde <a href="#cid-01-11">CID-01-11</a>, <a href="#cid-01-33">CID-01-33</a> y <a href="#cid-01-42">CID-01-42</a>.

---

### <a id="cid-05-05"></a>CID-05-05

**Qué hace:**
Declara la conexión de bitácora y diccionario al flujo interno del detector.

**Cómo funciona:**
Expone dos funciones públicas para entregar al detector una referencia a la bitácora activa y otra al diccionario conectado. A partir de esa conexión, el detector podrá resolver acordes y aplicar sus resultados sobre el estado del sistema.

**Pseudocódigo:**

```text
declarar función para conectar bitácora
declarar función para conectar diccionario
```

**Relaciones:**

* Usa los tipos adelantados en <a href="#cid-05-03">CID-05-03</a>.
* Se implementa en <a href="#cid-04-30">CID-04-30</a> y <a href="#cid-04-32">CID-04-32</a>.
* Es usado desde <a href="#cid-01-34">CID-01-34</a>.

---

### <a id="cid-05-06"></a>CID-05-06

**Qué hace:**
Declara la recepción de eventos de teclado ya filtrados desde el módulo `teclado_cid`.

**Cómo funciona:**
Expone la función pública que recibe virtual key, scan code y estado de pulsación desde el módulo de teclado. Esa función actúa como punto de entrada del detector para empezar a construir la lógica de acordes a partir de eventos físicos ya filtrados.

**Pseudocódigo:**

```text
declarar función para recibir evento de teclado filtrado
```

**Relaciones:**

* Usa los tipos base de <a href="#cid-05-02">CID-05-02</a>.
* Se implementa en <a href="#cid-04-55">CID-04-55</a>.
* Se conecta al flujo del teclado a través de <a href="#cid-03-05">CID-03-05</a>, <a href="#cid-02-45">CID-02-45</a> y <a href="#cid-02-33">CID-02-33</a>.


## CID-06

La referencia <a href="#cid-06">CID-06</a> corresponde al archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/bitacora_cid.cpp"><code>bitacora_cid.cpp</code></a>. Este archivo implementa la bitácora lógica y visual del sistema CID. Su responsabilidad principal es almacenar las piezas pendientes, registrar sus operaciones asociadas, mantener la representación visual de la línea actual y de las líneas ya asentadas, y ofrecer operaciones de modificación, borrado, reapertura y consulta segura del estado.

Dentro de <a href="#cid-06">CID-06</a> también se concentra la lógica de tildado, la aplicación del modificador D10 sobre la última entrada, la gestión de snapshots para deshacer y reapertura, y la sincronización interna mediante sección crítica. En términos prácticos, <a href="#cid-06">CID-06</a> es la memoria viva del texto en construcción dentro de CID, tanto en su plano lógico como en su plano visual.

### Índice interno de bloques

* <a href="#cid-06-01">CID-06-01</a>
* <a href="#cid-06-02">CID-06-02</a>
* <a href="#cid-06-03">CID-06-03</a>
* <a href="#cid-06-04">CID-06-04</a>
* <a href="#cid-06-05">CID-06-05</a>
* <a href="#cid-06-06">CID-06-06</a>
* <a href="#cid-06-07">CID-06-07</a>
* <a href="#cid-06-08">CID-06-08</a>
* <a href="#cid-06-09">CID-06-09</a>
* <a href="#cid-06-10">CID-06-10</a>
* <a href="#cid-06-11">CID-06-11</a>
* <a href="#cid-06-12">CID-06-12</a>
* <a href="#cid-06-13">CID-06-13</a>
* <a href="#cid-06-14">CID-06-14</a>
* <a href="#cid-06-15">CID-06-15</a>
* <a href="#cid-06-16">CID-06-16</a>
* <a href="#cid-06-17">CID-06-17</a>
* <a href="#cid-06-18">CID-06-18</a>
* <a href="#cid-06-19">CID-06-19</a>
* <a href="#cid-06-20">CID-06-20</a>
* <a href="#cid-06-21">CID-06-21</a>
* <a href="#cid-06-22">CID-06-22</a>
* <a href="#cid-06-23">CID-06-23</a>
* <a href="#cid-06-24">CID-06-24</a>
* <a href="#cid-06-25">CID-06-25</a>
* <a href="#cid-06-26">CID-06-26</a>
* <a href="#cid-06-27">CID-06-27</a>
* <a href="#cid-06-28">CID-06-28</a>
* <a href="#cid-06-29">CID-06-29</a>
* <a href="#cid-06-30">CID-06-30</a>
* <a href="#cid-06-31">CID-06-31</a>
* <a href="#cid-06-32">CID-06-32</a>
* <a href="#cid-06-33">CID-06-33</a>
* <a href="#cid-06-34">CID-06-34</a>
* <a href="#cid-06-35">CID-06-35</a>
* <a href="#cid-06-36">CID-06-36</a>
* <a href="#cid-06-37">CID-06-37</a>
* <a href="#cid-06-38">CID-06-38</a>
* <a href="#cid-06-39">CID-06-39</a>
* <a href="#cid-06-40">CID-06-40</a>
* <a href="#cid-06-41">CID-06-41</a>
* <a href="#cid-06-42">CID-06-42</a>
* <a href="#cid-06-43">CID-06-43</a>
* <a href="#cid-06-44">CID-06-44</a>
* <a href="#cid-06-45">CID-06-45</a>
* <a href="#cid-06-46">CID-06-46</a>
* <a href="#cid-06-47">CID-06-47</a>
* <a href="#cid-06-48">CID-06-48</a>
* <a href="#cid-06-49">CID-06-49</a>
* <a href="#cid-06-50">CID-06-50</a>
* <a href="#cid-06-51">CID-06-51</a>
* <a href="#cid-06-52">CID-06-52</a>
* <a href="#cid-06-53">CID-06-53</a>
* <a href="#cid-06-54">CID-06-54</a>
* <a href="#cid-06-55">CID-06-55</a>
* <a href="#cid-06-56">CID-06-56</a>

---

### <a id="cid-06-01"></a>CID-06-01

**Qué hace:**  
Incluye la implementación de la bitácora lógica y visual del sistema CID.

**Cómo funciona:**  
Importa la cabecera pública del módulo para que la implementación de este archivo coincida con la interfaz y los tipos expuestos al resto del sistema.

**Pseudocódigo:**  
```text
incluir interfaz pública de la bitácora CID
````

**Relaciones:**

* Prepara toda la implementación de <a href="#cid-06">CID-06</a>.
* Se corresponde con <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/bitacora_cid.h"><code>bitacora_cid.h</code></a>.

---

### <a id="cid-06-02"></a>CID-06-02

**Qué hace:**
Incluye utilidades de clasificación de caracteres para vocales y tildes.

**Cómo funciona:**
Importa funciones de `<cwctype>` como `towlower` y `towupper`, necesarias para detectar vocales y aplicar tildes respetando mayúsculas y minúsculas.

**Pseudocódigo:**

```text
incluir utilidades de clasificación y transformación de caracteres anchos
```

**Relaciones:**

* Da soporte a <a href="#cid-06-05">CID-06-05</a> y <a href="#cid-06-06">CID-06-06</a>.

---

### <a id="cid-06-03"></a>CID-06-03

**Qué hace:**
Inicializa la bitácora creando su sección crítica para acceso concurrente seguro.

**Cómo funciona:**
El constructor crea la sección crítica interna y marca la bandera de sincronización como iniciada. A partir de ese momento, el resto de métodos puede usar `EnterCriticalSection` y `LeaveCriticalSection` de forma segura.

**Pseudocódigo:**

```text
inicializar sección crítica interna
marcar sincronización como iniciada
```

**Relaciones:**

* Prepara la sincronización usada por casi todos los métodos de <a href="#cid-06">CID-06</a>.
* Se complementa con <a href="#cid-06-04">CID-06-04</a>.

---

### <a id="cid-06-04"></a>CID-06-04

**Qué hace:**
Destruye la bitácora liberando su sección crítica si fue iniciada correctamente.

**Cómo funciona:**
El destructor comprueba si la sección crítica llegó a inicializarse. Si fue así, la libera y deja la bandera interna como apagada.

**Pseudocódigo:**

```text
si la sincronización estaba iniciada:
    destruir sección crítica
    marcar sincronización como apagada
```

**Relaciones:**

* Complementa a <a href="#cid-06-03">CID-06-03</a>.
* Cierra la sincronización general de <a href="#cid-06">CID-06</a>.

---

### <a id="cid-06-05"></a>CID-06-05

**Qué hace:**
Comprueba si un carácter es una vocal latina sin importar mayúsculas o minúsculas.

**Cómo funciona:**
Convierte el carácter a minúscula y lo compara con las cinco vocales latinas básicas. Devuelve verdadero solo si coincide con una de ellas.

**Pseudocódigo:**

```text
convertir carácter a minúscula
si es a, e, i, o o u:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Usa utilidades de <a href="#cid-06-02">CID-06-02</a>.
* Es usado por <a href="#cid-06-07">CID-06-07</a>.

---

### <a id="cid-06-06"></a>CID-06-06

**Qué hace:**
Devuelve la versión acentuada de una vocal respetando la capitalización original.

**Cómo funciona:**
Detecta si el carácter original estaba en mayúscula, normaliza la base a minúscula, sustituye la vocal por su versión acentuada y, si era necesario, vuelve a elevar el resultado a mayúscula.

**Pseudocódigo:**

```text
detectar si la vocal original es mayúscula
convertir base a minúscula
sustituir por versión acentuada
si era mayúscula:
    convertir resultado a mayúscula
devolver resultado
```

**Relaciones:**

* Usa utilidades de <a href="#cid-06-02">CID-06-02</a>.
* Es usado por <a href="#cid-06-07">CID-06-07</a>.

---

### <a id="cid-06-07"></a>CID-06-07

**Qué hace:**
Aplica una tilde a la vocal indicada por número ordinal dentro de una cadena.

**Cómo funciona:**
Rechaza primero números tildales no válidos. Después recorre la cadena contando vocales hasta llegar a la posición indicada. Cuando la encuentra, reemplaza esa vocal por su variante acentuada. Si no se localiza la vocal buscada, devuelve error.

**Pseudocódigo:**

```text
si el número tildal no es válido:
    devolver error
recorrer cadena contando vocales
si se alcanza la vocal objetivo:
    acentuarla
    devolver éxito
si no se encuentra:
    devolver error
```

**Relaciones:**

* Usa <a href="#cid-06-05">CID-06-05</a> y <a href="#cid-06-06">CID-06-06</a>.
* Es usado por <a href="#cid-06-34">CID-06-34</a> y <a href="#cid-06-37">CID-06-37</a>.

---

### <a id="cid-06-08"></a>CID-06-08

**Qué hace:**
Compara dos líneas visuales completas para saber si sus tokens son exactamente iguales.

**Cómo funciona:**
Primero compara el tamaño de ambas listas de tokens. Si coincide, recorre cada posición y exige igualdad tanto en el tipo como en el texto del token.

**Pseudocódigo:**

```text
si el número de tokens no coincide:
    devolver falso
comparar token a token tipo y texto
si todos coinciden:
    devolver verdadero
devolver falso en cuanto haya diferencia
```

**Relaciones:**

* Es usado por <a href="#cid-06-54">CID-06-54</a>.

---

### <a id="cid-06-09"></a>CID-06-09

**Qué hace:**
Recorta el historial de líneas visuales cerradas para respetar el máximo configurado.

**Cómo funciona:**
Asegura primero que el máximo de líneas sea al menos uno. Después, si el historial supera ese límite, elimina las líneas más antiguas hasta quedar dentro del máximo.

**Pseudocódigo:**

```text
si el máximo visual es menor que uno:
    fijarlo a uno
si hay más líneas cerradas que el máximo:
    eliminar las más antiguas
```

**Relaciones:**

* Usa el estado visual interno de la bitácora.
* Es usado por <a href="#cid-06-15">CID-06-15</a> y <a href="#cid-06-48">CID-06-48</a>.

---

### <a id="cid-06-10"></a>CID-06-10

**Qué hace:**
Registra una operación modificadora pendiente guardando el snapshot previo de la última entrada.

**Cómo funciona:**
Construye una operación pendiente de tipo modificador, marca que contiene snapshot previo y almacena la versión anterior de la entrada para permitir un deshacer posterior.

**Pseudocódigo:**

```text
crear operación pendiente de tipo modificador
marcar que tiene snapshot previo
guardar snapshot de la entrada anterior
añadir operación a la lista pendiente
```

**Relaciones:**

* Es usado por <a href="#cid-06-28">CID-06-28</a>, <a href="#cid-06-34">CID-06-34</a>, <a href="#cid-06-37">CID-06-37</a>, <a href="#cid-06-38">CID-06-38</a>, <a href="#cid-06-39">CID-06-39</a>, <a href="#cid-06-40">CID-06-40</a> y <a href="#cid-06-41">CID-06-41</a>.

---

### <a id="cid-06-11"></a>CID-06-11

**Qué hace:**
Recorta la última pieza lógica junto a sus modificadores y tokens visuales asociados.

**Cómo funciona:**
Primero elimina todos los modificadores pendientes colocados al final y sus tokens visuales correspondientes. Después elimina la última pieza principal y su token visual si existe.

**Pseudocódigo:**

```text
eliminar modificadores finales y sus tokens
eliminar después la última pieza y su token
```

**Relaciones:**

* Contiene internamente <a href="#cid-06-12">CID-06-12</a> y <a href="#cid-06-13">CID-06-13</a>.
* Es usado por <a href="#cid-06-24">CID-06-24</a>.

---

### <a id="cid-06-12"></a>CID-06-12

**Qué hace:**
Elimina primero los modificadores finales asociados a la última pieza visual y lógica.

**Cómo funciona:**
Mientras la última operación pendiente sea de tipo modificador, la elimina. Además, si el último token visual es también de tipo modificador, lo elimina de la línea actual.

**Pseudocódigo:**

```text
mientras la última operación sea modificador:
    eliminar operación
    si el último token visual es modificador:
        eliminar token visual
```

**Relaciones:**

* Forma parte de <a href="#cid-06-11">CID-06-11</a>.

---

### <a id="cid-06-13"></a>CID-06-13

**Qué hace:**
Elimina después la última pieza principal de la línea visual y del historial lógico.

**Cómo funciona:**
Si tras limpiar modificadores la última operación pendiente es una pieza, la elimina y también recorta el último token visual si este corresponde a una pieza.

**Pseudocódigo:**

```text
si la última operación es una pieza:
    eliminar operación
    si el último token visual es una pieza:
        eliminar token visual
```

**Relaciones:**

* Forma parte de <a href="#cid-06-11">CID-06-11</a>.

---

### <a id="cid-06-14"></a>CID-06-14

**Qué hace:**
Configura el tamaño máximo del buffer lógico de entradas pendientes.

**Cómo funciona:**
Entra en sección crítica, ajusta el máximo a un valor mínimo de uno y, si el historial lógico excede ese tamaño, elimina las entradas más antiguas hasta respetar el nuevo límite.

**Pseudocódigo:**

```text
entrar en sección crítica
fijar máximo lógico válido
si hay más entradas que el máximo:
    eliminar las más antiguas
salir de la sección crítica
```

**Relaciones:**

* Ajusta el almacenamiento lógico de la bitácora.
* Es llamado desde <a href="#cid-01-25">CID-01-25</a>.

---

### <a id="cid-06-15"></a>CID-06-15

**Qué hace:**
Configura el máximo de líneas visuales cerradas conservadas por la bitácora.

**Cómo funciona:**
Entra en sección crítica, fija el máximo visual a un mínimo de uno y luego llama al helper que recorta el historial visual si fuera necesario.

**Pseudocódigo:**

```text
entrar en sección crítica
fijar máximo visual válido
recortar líneas visuales cerradas si hace falta
salir de la sección crítica
```

**Relaciones:**

* Usa <a href="#cid-06-09">CID-06-09</a>.
* Es llamado desde <a href="#cid-01-25">CID-01-25</a>.

---

### <a id="cid-06-16"></a>CID-06-16

**Qué hace:**
Limpia por completo el estado lógico, visual y de reapertura de la bitácora.

**Cómo funciona:**
Vacía entradas pendientes, operaciones, líneas cerradas, línea actual y snapshot de reapertura. Deja la bitácora en un estado completamente reinicializado.

**Pseudocódigo:**

```text
entrar en sección crítica
vaciar historial lógico
vaciar operaciones pendientes
vaciar historial visual
vaciar línea actual
borrar snapshot de última línea asentada
salir de la sección crítica
```

**Relaciones:**

* Reinicia todos los planos internos de <a href="#cid-06">CID-06</a>.

---

### <a id="cid-06-17"></a>CID-06-17

**Qué hace:**
Limpia solo las entradas y operaciones lógicas pendientes sin tocar el historial visual.

**Cómo funciona:**
Vacía `m_items` y `m_operaciones_pendientes`, manteniendo intactos la línea visual actual, las líneas cerradas y el snapshot de reapertura.

**Pseudocódigo:**

```text
entrar en sección crítica
vaciar entradas lógicas
vaciar operaciones pendientes
salir de la sección crítica
```

**Relaciones:**

* Afecta solo al plano lógico de <a href="#cid-06">CID-06</a>.

---

### <a id="cid-06-18"></a>CID-06-18

**Qué hace:**
Limpia solo el estado visual activo y el snapshot de la última línea asentada.

**Cómo funciona:**
Vacía el historial de líneas cerradas, la línea actual y el snapshot visual de reapertura, sin tocar las entradas lógicas pendientes.

**Pseudocódigo:**

```text
entrar en sección crítica
vaciar líneas cerradas
vaciar línea actual
borrar snapshot visual de reapertura
salir de la sección crítica
```

**Relaciones:**

* Afecta solo al plano visual de <a href="#cid-06">CID-06</a>.

---

### <a id="cid-06-19"></a>CID-06-19

**Qué hace:**
Devuelve el número de entradas lógicas pendientes actualmente almacenadas.

**Cómo funciona:**
Entra en sección crítica, lee el tamaño de `m_items`, sale del lock y devuelve ese valor.

**Pseudocódigo:**

```text
entrar en sección crítica
leer tamaño del buffer lógico
salir de la sección crítica
devolver tamaño
```

**Relaciones:**

* Es usado por <a href="#cid-06-20">CID-06-20</a>.
* Es consultado desde otros módulos como <a href="#cid-04-26">CID-04-26</a> y <a href="#cid-04-60">CID-04-60</a>.

---

### <a id="cid-06-20"></a>CID-06-20

**Qué hace:**
Indica si existen entradas pendientes comprobando el tamaño lógico actual.

**Cómo funciona:**
Llama a `Tamano()` y devuelve verdadero si el tamaño es mayor que cero.

**Pseudocódigo:**

```text
consultar tamaño lógico
devolver si es mayor que cero
```

**Relaciones:**

* Usa <a href="#cid-06-19">CID-06-19</a>.

---

### <a id="cid-06-21"></a>CID-06-21

**Qué hace:**
Añade una nueva pieza lógica a la bitácora y registra su operación pendiente asociada.

**Cómo funciona:**
Asegura el límite máximo de entradas, crea una nueva `Entrada` con su texto y metadatos de tilde, la añade al buffer lógico y registra una operación pendiente de tipo pieza.

**Pseudocódigo:**

```text
entrar en sección crítica
si se alcanza el máximo:
    eliminar la entrada más antigua
crear nueva entrada lógica
añadirla al buffer
registrar operación pendiente de pieza
salir de la sección crítica
```

**Relaciones:**

* Es usado desde <a href="#cid-04-52">CID-04-52</a>.
* Alimenta después a <a href="#cid-06-22">CID-06-22</a>, <a href="#cid-06-23">CID-06-23</a>, <a href="#cid-06-24">CID-06-24</a>, <a href="#cid-06-29">CID-06-29</a> y <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-22"></a>CID-06-22

**Qué hace:**
Devuelve una copia simple del contenido lógico pendiente en forma de textos planos.

**Cómo funciona:**
Recorre todas las entradas lógicas actuales y extrae únicamente su campo de texto a un nuevo vector que devuelve al llamador.

**Pseudocódigo:**

```text
entrar en sección crítica
crear vector de salida
para cada entrada lógica:
    copiar solo su texto
salir de la sección crítica
devolver copia
```

**Relaciones:**

* Consulta el estado generado por <a href="#cid-06-21">CID-06-21</a>.

---

### <a id="cid-06-23"></a>CID-06-23

**Qué hace:**
Obtiene el texto de la última entrada lógica pendiente si existe.

**Cómo funciona:**
Si la bitácora lógica está vacía devuelve falso y limpia la salida. Si no lo está, copia el texto de la última entrada y devuelve verdadero.

**Pseudocódigo:**

```text
entrar en sección crítica
si no hay entradas:
    salir con falso
copiar texto de la última entrada
salir con verdadero
```

**Relaciones:**

* Consulta el estado lógico actual de la bitácora.

---

### <a id="cid-06-24"></a>CID-06-24

**Qué hace:**
Borra la última entrada lógica y recorta también sus tokens visuales y modificadores asociados.

**Cómo funciona:**
Si no hay entradas, falla. Si existe una última entrada, opcionalmente devuelve su texto, la elimina del buffer lógico y luego llama al helper que recorta su operación y los tokens visuales relacionados.

**Pseudocódigo:**

```text
entrar en sección crítica
si no hay entradas:
    devolver falso
si se pidió texto borrado:
    copiar último texto
eliminar última entrada lógica
recortar operación y tokens visuales asociados
salir de la sección crítica
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-06-11">CID-06-11</a>.
* Es una operación de borrado lógica y visual acoplada.

---

### <a id="cid-06-25"></a>CID-06-25

**Qué hace:**
Borra la última operación pendiente restaurando una modificación o eliminando la última pieza.

**Cómo funciona:**
Examina la última operación pendiente. Si es un modificador, intenta restaurar el snapshot previo. Si es una pieza, borra la última entrada y su token visual principal. Devuelve además información sobre lo borrado y si se trataba de un modificador.

**Pseudocódigo:**

```text
entrar en sección crítica
si no hay operaciones:
    devolver falso
leer última operación pendiente
si es modificador:
    revertir modificación si hay snapshot válido
si es pieza:
    borrar última pieza y su token
salir de la sección crítica
devolver resultado
```

**Relaciones:**

* Contiene internamente <a href="#cid-06-26">CID-06-26</a> y <a href="#cid-06-27">CID-06-27</a>.
* Implementa un deshacer fino a nivel de operación.

---

### <a id="cid-06-26"></a>CID-06-26

**Qué hace:**
Revierte la última operación si era un modificador con snapshot previo válido.

**Cómo funciona:**
Comprueba que exista al menos una entrada lógica y que la operación pendiente contenga un snapshot. Si ambas condiciones se cumplen, restaura la entrada anterior, elimina la operación de modificador y recorta el token visual de modificación.

**Pseudocódigo:**

```text
si no hay entrada o no hay snapshot válido:
    devolver falso
marcar que se borra un modificador
restaurar snapshot previo sobre la última entrada
eliminar operación pendiente
eliminar token visual de modificador si existe
devolver verdadero
```

**Relaciones:**

* Forma parte de <a href="#cid-06-25">CID-06-25</a>.
* Usa snapshots creados por <a href="#cid-06-10">CID-06-10</a>.

---

### <a id="cid-06-27"></a>CID-06-27

**Qué hace:**
Borra la última pieza lógica y su token visual cuando la última operación era una pieza.

**Cómo funciona:**
Si hay una entrada lógica válida, copia opcionalmente su texto, elimina tanto la entrada como la operación pendiente y recorta el último token visual de tipo pieza.

**Pseudocódigo:**

```text
si no hay entradas:
    devolver falso
marcar que se borra una pieza
copiar texto de la última entrada
eliminar entrada lógica
eliminar operación pendiente
eliminar token visual de pieza si existe
devolver verdadero
```

**Relaciones:**

* Forma parte de <a href="#cid-06-25">CID-06-25</a>.

---

### <a id="cid-06-28"></a>CID-06-28

**Qué hace:**
Reemplaza la última entrada solo si coincide con el valor esperado y registra la modificación.

**Cómo funciona:**
Comprueba que exista una última entrada y que su texto sea exactamente el esperado. Si coincide, guarda un snapshot previo, sustituye el texto, invalida su metadato de tilde y registra una operación modificadora para posible deshacer.

**Pseudocódigo:**

```text
entrar en sección crítica
si no hay entradas:
    devolver falso
si la última entrada no coincide con el esperado:
    devolver falso
guardar snapshot previo
reemplazar texto de la última entrada
invalidar metadatos de tilde
registrar operación modificadora
salir de la sección crítica
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-06-10">CID-06-10</a>.
* Es una modificación lógica con soporte de deshacer.

---

### <a id="cid-06-29"></a>CID-06-29

**Qué hace:**
Aplica la tilde pendiente sobre la última entrada cuando su configuración lo permite.

**Cómo funciona:**
Valida que exista una entrada, que esta admita variante acentuada y que la tilde no haya sido aplicada ya. Si todo es correcto, intenta aplicar la tilde real sobre el texto y guarda un snapshot para deshacer.

**Pseudocódigo:**

```text
entrar en sección crítica
validar que exista última entrada
validar que admita tilde
si no requiere tilde o ya estaba aplicada:
    devolver éxito
guardar snapshot previo
intentar aplicar tilde real
si se aplica:
    marcar tilde aplicada
    registrar operación modificadora
devolver resultado
```

**Relaciones:**

* Contiene internamente <a href="#cid-06-30">CID-06-30</a> a <a href="#cid-06-34">CID-06-34</a>.
* Usa <a href="#cid-06-07">CID-06-07</a> y <a href="#cid-06-10">CID-06-10</a>.

---

### <a id="cid-06-30"></a>CID-06-30

**Qué hace:**
Rechaza la operación si no existe ninguna entrada lógica pendiente.

**Cómo funciona:**
Si `m_items` está vacío, escribe el error correspondiente y termina sin hacer cambios.

**Pseudocódigo:**

```text
si no hay entradas lógicas:
    devolver error de bitácora vacía
```

**Relaciones:**

* Forma parte de <a href="#cid-06-29">CID-06-29</a>.

---

### <a id="cid-06-31"></a>CID-06-31

**Qué hace:**
Rechaza la operación si la entrada actual no admite variante acentuada.

**Cómo funciona:**
Comprueba si `numero_tildal` vale `-1`. Ese valor significa que la entrada no tiene forma acentuable y, por tanto, la operación debe rechazarse.

**Pseudocódigo:**

```text
si la entrada no admite tilde:
    devolver error
```

**Relaciones:**

* Forma parte de <a href="#cid-06-29">CID-06-29</a>.

---

### <a id="cid-06-32"></a>CID-06-32

**Qué hace:**
Considera resuelta la operación cuando la entrada no requiere tilde real.

**Cómo funciona:**
Si `numero_tildal` es `0`, interpreta que la entrada admite la operación de forma neutra pero no necesita modificar su texto. Devuelve éxito sin cambios.

**Pseudocódigo:**

```text
si la entrada no requiere tilde real:
    devolver éxito sin cambios
```

**Relaciones:**

* Forma parte de <a href="#cid-06-29">CID-06-29</a>.

---

### <a id="cid-06-33"></a>CID-06-33

**Qué hace:**
Considera resuelta la operación si la tilde ya había sido aplicada anteriormente.

**Cómo funciona:**
Si la bandera `tilde_aplicada` ya está activa, no repite la transformación y devuelve éxito directamente.

**Pseudocódigo:**

```text
si la tilde ya estaba aplicada:
    devolver éxito
```

**Relaciones:**

* Forma parte de <a href="#cid-06-29">CID-06-29</a>.

---

### <a id="cid-06-34"></a>CID-06-34

**Qué hace:**
Intenta aplicar la tilde real y registra un snapshot para posible deshacer.

**Cómo funciona:**
Guarda la entrada previa, delega el tildado en el helper ordinal y, si tiene éxito, marca la tilde como aplicada y registra la operación modificadora.

**Pseudocódigo:**

```text
guardar snapshot previo
intentar aplicar tilde según número
si falla:
    devolver error
marcar tilde como aplicada
registrar operación modificadora
devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-06-07">CID-06-07</a> y <a href="#cid-06-10">CID-06-10</a>.
* Forma parte de <a href="#cid-06-29">CID-06-29</a>.

---

### <a id="cid-06-35"></a>CID-06-35

**Qué hace:**
Aplica el modificador D10 sobre la última entrada siguiendo el orden oficial de transformaciones.

**Cómo funciona:**
Primero valida que exista una entrada. Después intenta aplicar la tilde pendiente si corresponde. Si eso no produce efecto, prueba una serie de transformaciones oficiales sobre signos y símbolos. Si ninguna encaja, informa que D10 no tuvo efecto.

**Pseudocódigo:**

```text
entrar en sección crítica
si no hay entrada:
    devolver error
guardar snapshot previo
intentar aplicar primero tilde
si no cambia nada:
    probar transformaciones especiales de signos
si alguna funciona:
    registrar operación modificadora
    devolver éxito
si ninguna funciona:
    devolver error sin efecto
```

**Relaciones:**

* Contiene internamente <a href="#cid-06-36">CID-06-36</a> a <a href="#cid-06-42">CID-06-42</a>.
* Es usado desde <a href="#cid-04-27">CID-04-27</a> a través de <a href="#cid-04-25">CID-04-25</a>.

---

### <a id="cid-06-36"></a>CID-06-36

**Qué hace:**
Rechaza D10 si la bitácora no contiene ninguna entrada sobre la que actuar.

**Cómo funciona:**
Si `m_items` está vacío, informa de que la bitácora está vacía y termina sin aplicar cambios.

**Pseudocódigo:**

```text
si la bitácora está vacía:
    devolver error
```

**Relaciones:**

* Forma parte de <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-37"></a>CID-06-37

**Qué hace:**
Intenta aplicar primero la tilde si todavía no fue aplicada y realmente cambia el texto.

**Cómo funciona:**
Solo cuando la entrada admite tilde y todavía no la tiene aplicada, prueba el tildado real. Si el texto cambia, marca la tilde como aplicada, registra snapshot y devuelve éxito inmediato.

**Pseudocódigo:**

```text
si la entrada admite tilde y aún no la tiene:
    intentar aplicar tilde
    si el texto cambia:
        marcar tilde aplicada
        registrar operación modificadora
        devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-06-07">CID-06-07</a> y <a href="#cid-06-10">CID-06-10</a>.
* Forma parte de <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-38"></a>CID-06-38

**Qué hace:**
Convierte un cierre de interrogación en apertura cuando D10 actúa sobre un signo de pregunta.

**Cómo funciona:**
Si el texto actual es `?`, lo transforma en `¿`, invalida metadatos de tilde y registra la modificación.

**Pseudocódigo:**

```text
si el texto es ?:
    convertirlo en ¿
    invalidar metadatos de tilde
    registrar operación modificadora
    devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-06-10">CID-06-10</a>.
* Forma parte de <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-39"></a>CID-06-39

**Qué hace:**
Convierte un cierre de exclamación en apertura cuando D10 actúa sobre un signo de admiración.

**Cómo funciona:**
Si el texto actual es `!`, lo transforma en `¡`, invalida metadatos de tilde y registra la modificación.

**Pseudocódigo:**

```text
si el texto es !:
    convertirlo en ¡
    invalidar metadatos de tilde
    registrar operación modificadora
    devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-06-10">CID-06-10</a>.
* Forma parte de <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-40"></a>CID-06-40

**Qué hace:**
Convierte un guion simple en raya larga cuando D10 actúa sobre el símbolo correspondiente.

**Cómo funciona:**
Si el texto actual es `-`, lo transforma en `—`, invalida metadatos de tilde y registra la operación modificadora.

**Pseudocódigo:**

```text
si el texto es -:
    convertirlo en raya larga
    invalidar metadatos de tilde
    registrar operación modificadora
    devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-06-10">CID-06-10</a>.
* Forma parte de <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-41"></a>CID-06-41

**Qué hace:**
Convierte una barra inclinada en barra invertida cuando D10 actúa sobre esa entrada.

**Cómo funciona:**
Si el texto actual es `/`, lo transforma en `\`, invalida metadatos de tilde y registra la modificación.

**Pseudocódigo:**

```text
si el texto es /:
    convertirlo en barra invertida
    invalidar metadatos de tilde
    registrar operación modificadora
    devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-06-10">CID-06-10</a>.
* Forma parte de <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-42"></a>CID-06-42

**Qué hace:**
Informa que D10 no produjo ningún efecto sobre la última entrada disponible.

**Cómo funciona:**
Si ninguna transformación previa fue aplicable, escribe el error final y devuelve falso.

**Pseudocódigo:**

```text
escribir error de D10 sin efecto
devolver falso
```

**Relaciones:**

* Forma parte de <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-06-43"></a>CID-06-43

**Qué hace:**
Añade un token visual de pieza a la línea visual actualmente abierta.

**Cómo funciona:**
Construye un token visual de tipo pieza con el texto recibido y lo añade al final de la línea actual.

**Pseudocódigo:**

```text
entrar en sección crítica
crear token visual de pieza
añadirlo a la línea actual
salir de la sección crítica
```

**Relaciones:**

* Es usado desde <a href="#cid-04-52">CID-04-52</a>.

---

### <a id="cid-06-44"></a>CID-06-44

**Qué hace:**
Añade un token visual de modificador a la línea visual actualmente abierta.

**Cómo funciona:**
Construye un token visual de tipo modificador con el texto fijo `MOD.` y lo añade al final de la línea actual.

**Pseudocódigo:**

```text
entrar en sección crítica
crear token visual de modificador
añadirlo a la línea actual
salir de la sección crítica
```

**Relaciones:**

* Es usado desde <a href="#cid-04-29">CID-04-29</a>.

---

### <a id="cid-06-45"></a>CID-06-45

**Qué hace:**
Borra el último token visual de la línea abierta y devuelve cuál fue eliminado.

**Cómo funciona:**
Si la línea actual no tiene tokens devuelve falso. Si tiene al menos uno, opcionalmente lo devuelve al llamador, lo elimina de la línea actual y confirma el borrado.

**Pseudocódigo:**

```text
entrar en sección crítica
si la línea visual está vacía:
    devolver falso
si se pidió token borrado:
    copiar último token
eliminar último token de la línea
salir de la sección crítica
devolver verdadero
```

**Relaciones:**

* Opera solo sobre la línea visual actual de la bitácora.

---

### <a id="cid-06-46"></a>CID-06-46

**Qué hace:**
Cierra la línea actual por asentado y guarda un snapshot para posible reapertura posterior.

**Cómo funciona:**
Guarda primero un snapshot completo de la línea asentada, luego mueve la línea visual actual al historial de líneas cerradas si contiene tokens, recorta ese historial y finalmente limpia el estado lógico y visual pendiente para abrir una línea nueva vacía.

**Pseudocódigo:**

```text
entrar en sección crítica
guardar snapshot de la línea asentada
si la línea actual tiene contenido:
    moverla a líneas cerradas
    recortar historial visual
limpiar estado lógico pendiente
limpiar línea actual
salir de la sección crítica
```

**Relaciones:**

* Contiene internamente <a href="#cid-06-47">CID-06-47</a>, <a href="#cid-06-48">CID-06-48</a> y <a href="#cid-06-49">CID-06-49</a>.
* Se usa como cierre visual y lógico tras asentado.

---

### <a id="cid-06-47"></a>CID-06-47

**Qué hace:**
Guarda el snapshot completo de la línea asentada para permitir su reapertura posterior.

**Cómo funciona:**
Copia la línea visual actual, las entradas lógicas y las operaciones pendientes al snapshot de “última línea asentada” y marca si realmente había algo que poder reabrir.

**Pseudocódigo:**

```text
copiar línea visual actual al snapshot
copiar estado lógico al snapshot
copiar operaciones al snapshot
marcar si existe una última línea asentada válida
```

**Relaciones:**

* Forma parte de <a href="#cid-06-46">CID-06-46</a>.
* Da soporte a <a href="#cid-06-50">CID-06-50</a>.

---

### <a id="cid-06-48"></a>CID-06-48

**Qué hace:**
Mueve la línea visual activa al historial de líneas cerradas respetando el máximo configurado.

**Cómo funciona:**
Si la línea actual no está vacía, la añade al final del historial de líneas cerradas y luego aplica el recorte visual según el máximo configurado.

**Pseudocódigo:**

```text
si la línea actual tiene tokens:
    añadirla a líneas cerradas
    recortar historial visual
```

**Relaciones:**

* Usa <a href="#cid-06-09">CID-06-09</a>.
* Forma parte de <a href="#cid-06-46">CID-06-46</a>.

---

### <a id="cid-06-49"></a>CID-06-49

**Qué hace:**
Limpia el estado pendiente y deja abierta una nueva línea vacía tras el asentado.

**Cómo funciona:**
Vacía las entradas lógicas pendientes, las operaciones y los tokens de la línea actual, dejando la bitácora lista para empezar una nueva línea.

**Pseudocódigo:**

```text
vaciar entradas pendientes
vaciar operaciones pendientes
vaciar línea visual actual
```

**Relaciones:**

* Forma parte de <a href="#cid-06-46">CID-06-46</a>.

---

### <a id="cid-06-50"></a>CID-06-50

**Qué hace:**
Reabre la última línea asentada si no hay nada vivo actualmente en la bitácora.

**Cómo funciona:**
Comprueba primero que exista un snapshot válido y que no haya contenido activo actual. Si ambas condiciones se cumplen, restaura el estado lógico y visual previo, elimina del historial la línea cerrada correspondiente si coincide y limpia el snapshot para evitar reaperturas repetidas.

**Pseudocódigo:**

```text
entrar en sección crítica
validar que exista snapshot reabrible
validar que no haya contenido activo actual
restaurar estado lógico y visual del snapshot
retirar línea cerrada si coincide
limpiar snapshot de reapertura
salir de la sección crítica
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-06-51">CID-06-51</a> a <a href="#cid-06-55">CID-06-55</a>.
* Se apoya en el snapshot creado por <a href="#cid-06-47">CID-06-47</a>.

---

### <a id="cid-06-51"></a>CID-06-51

**Qué hace:**
Rechaza la reapertura cuando no existe un snapshot válido de la última línea asentada.

**Cómo funciona:**
Comprueba la bandera interna de snapshot disponible y, si no está activa, rechaza la operación de reapertura.

**Pseudocódigo:**

```text
si no hay snapshot válido de última línea asentada:
    devolver falso
```

**Relaciones:**

* Forma parte de <a href="#cid-06-50">CID-06-50</a>.

---

### <a id="cid-06-52"></a>CID-06-52

**Qué hace:**
Rechaza la reapertura si ya hay contenido lógico o visual activo en la línea actual.

**Cómo funciona:**
Comprueba que no existan entradas lógicas activas ni tokens en la línea actual. Si alguno de esos dos planos contiene contenido, no permite reabrir.

**Pseudocódigo:**

```text
si ya hay contenido lógico o visual activo:
    devolver falso
```

**Relaciones:**

* Forma parte de <a href="#cid-06-50">CID-06-50</a>.

---

### <a id="cid-06-53"></a>CID-06-53

**Qué hace:**
Restaura el snapshot lógico y visual previamente asentado como línea activa otra vez.

**Cómo funciona:**
Copia al estado vivo actual las entradas lógicas, las operaciones pendientes y la línea visual almacenadas en el snapshot de última línea asentada.

**Pseudocódigo:**

```text
restaurar entradas lógicas desde snapshot
restaurar operaciones desde snapshot
restaurar línea visual desde snapshot
```

**Relaciones:**

* Forma parte de <a href="#cid-06-50">CID-06-50</a>.

---

### <a id="cid-06-54"></a>CID-06-54

**Qué hace:**
Retira del historial cerrado la línea restaurada si coincide con el último cierre visible.

**Cómo funciona:**
Comprueba si la última línea cerrada coincide exactamente con la línea restaurada. Si coincide, la elimina del historial cerrado para evitar duplicación visual.

**Pseudocódigo:**

```text
si existe una última línea cerrada y coincide con la restaurada:
    eliminarla del historial cerrado
```

**Relaciones:**

* Usa <a href="#cid-06-08">CID-06-08</a>.
* Forma parte de <a href="#cid-06-50">CID-06-50</a>.

---

### <a id="cid-06-55"></a>CID-06-55

**Qué hace:**
Limpia el snapshot de reapertura para evitar restauraciones repetidas de la misma línea.

**Cómo funciona:**
Desactiva la bandera de snapshot disponible y vacía sus estructuras asociadas, dejando la reapertura consumida.

**Pseudocódigo:**

```text
desactivar snapshot de reapertura
vaciar línea visual del snapshot
vaciar lógica del snapshot
vaciar operaciones del snapshot
```

**Relaciones:**

* Forma parte de <a href="#cid-06-50">CID-06-50</a>.

---

### <a id="cid-06-56"></a>CID-06-56

**Qué hace:**
Devuelve una copia del estado visual completo compuesto por líneas cerradas y línea actual.

**Cómo funciona:**
Entra en sección crítica, construye un `EstadoVisualBitacoraCID`, copia dentro de él las líneas cerradas y la línea actual, y devuelve esa estructura al llamador.

**Pseudocódigo:**

```text
entrar en sección crítica
crear estado visual de salida
copiar líneas cerradas
copiar línea actual
salir de la sección crítica
devolver estado visual
```

**Relaciones:**

* Es usado desde <a href="#cid-01-26">CID-01-26</a>, <a href="#cid-04-23">CID-04-23</a> y <a href="#cid-04-30">CID-04-30</a>.


## CID-07

La referencia <a href="#cid-07">CID-07</a> corresponde al archivo <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/bitacora_cid.h"><code>bitacora_cid.h</code></a>. Este archivo define la interfaz pública y los tipos base de la bitácora CID. Su responsabilidad principal es declarar la estructura lógica y visual con la que el sistema representa piezas, modificadores, líneas abiertas, líneas cerradas y snapshots de reapertura, además de exponer las operaciones públicas que implementa <a href="#cid-06">CID-06</a>.

Dentro de <a href="#cid-07">CID-07</a> no hay lógica de ejecución directa. Su función es fijar el contrato formal de la bitácora, tanto hacia el resto del motor como hacia la superposición visual. En términos prácticos, <a href="#cid-07">CID-07</a> es la definición estructural de cómo existe la bitácora CID por dentro y qué operaciones públicas ofrece.

### Índice interno de bloques

* <a href="#cid-07-01">CID-07-01</a>
* <a href="#cid-07-02">CID-07-02</a>
* <a href="#cid-07-03">CID-07-03</a>
* <a href="#cid-07-04">CID-07-04</a>
* <a href="#cid-07-05">CID-07-05</a>
* <a href="#cid-07-06">CID-07-06</a>
* <a href="#cid-07-07">CID-07-07</a>
* <a href="#cid-07-08">CID-07-08</a>
* <a href="#cid-07-09">CID-07-09</a>
* <a href="#cid-07-10">CID-07-10</a>
* <a href="#cid-07-11">CID-07-11</a>
* <a href="#cid-07-12">CID-07-12</a>
* <a href="#cid-07-13">CID-07-13</a>
* <a href="#cid-07-14">CID-07-14</a>
* <a href="#cid-07-15">CID-07-15</a>
* <a href="#cid-07-16">CID-07-16</a>
* <a href="#cid-07-17">CID-07-17</a>
* <a href="#cid-07-18">CID-07-18</a>
* <a href="#cid-07-19">CID-07-19</a>
* <a href="#cid-07-20">CID-07-20</a>
* <a href="#cid-07-21">CID-07-21</a>
* <a href="#cid-07-22">CID-07-22</a>
* <a href="#cid-07-23">CID-07-23</a>
* <a href="#cid-07-24">CID-07-24</a>
* <a href="#cid-07-25">CID-07-25</a>
* <a href="#cid-07-26">CID-07-26</a>
* <a href="#cid-07-27">CID-07-27</a>
* <a href="#cid-07-28">CID-07-28</a>
* <a href="#cid-07-29">CID-07-29</a>

---

### <a id="cid-07-01"></a>CID-07-01

**Qué hace:**  
Evita inclusiones múltiples de la interfaz pública de la bitácora CID.

**Cómo funciona:**  
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Esto previene redefiniciones de tipos, estructuras y la propia clase `BitacoraCID`.

**Pseudocódigo:**  
```text
marcar esta cabecera para inclusión única
````

**Relaciones:**

* Protege toda la interfaz declarada en <a href="#cid-07">CID-07</a>.
* Afecta indirectamente a <a href="#cid-07-04">CID-07-04</a> hasta <a href="#cid-07-29">CID-07-29</a>.

---

### <a id="cid-07-02"></a>CID-07-02

**Qué hace:**
Incluye los tipos base del sistema usados por la sincronización interna de la bitácora.

**Cómo funciona:**
Importa `windows.h`, que aporta tipos y utilidades como `CRITICAL_SECTION`, necesarios para declarar el mecanismo de sincronización interna de la clase.

**Pseudocódigo:**

```text
incluir tipos base de Windows
```

**Relaciones:**

* Da soporte a <a href="#cid-07-26">CID-07-26</a>.
* Se apoya en <a href="https://github.com/Konaruchan/CID/tree/main/Motor_CID/bitacora_cid.h"><code>bitacora_cid.h</code></a> como cabecera base del módulo.

---

### <a id="cid-07-03"></a>CID-07-03

**Qué hace:**
Incluye los tipos de texto y contenedores usados por la interfaz lógica y visual de la bitácora.

**Cómo funciona:**
Importa `std::wstring` y `std::vector`, que se usan para definir tokens visuales, líneas visuales, entradas lógicas, estados completos y múltiples métodos públicos de la bitácora.

**Pseudocódigo:**

```text
incluir soporte de cadenas
incluir soporte de vectores
```

**Relaciones:**

* Da soporte a <a href="#cid-07-05">CID-07-05</a> hasta <a href="#cid-07-29">CID-07-29</a>.

---

### <a id="cid-07-04"></a>CID-07-04

**Qué hace:**
Define los tipos de tokens visuales que pueden aparecer en la representación de la bitácora.

**Cómo funciona:**
Declara una enumeración con dos valores posibles: `Pieza` y `Modificador`. Esta clasificación permite distinguir visualmente entre contenido normal asentable y marcas de modificación como `MOD.`.

**Pseudocódigo:**

```text
definir tipo visual Pieza
definir tipo visual Modificador
```

**Relaciones:**

* Es usado por <a href="#cid-07-05">CID-07-05</a>.
* Se implementa visualmente en <a href="#cid-06-43">CID-06-43</a> y <a href="#cid-06-44">CID-06-44</a>.

---

### <a id="cid-07-05"></a>CID-07-05

**Qué hace:**
Define un token visual individual compuesto por tipo y texto mostrado en pantalla.

**Cómo funciona:**
Declara una estructura simple con dos campos: el tipo visual del token y el texto que debe mostrarse. Cada elemento visual de la línea actual o del historial cerrado se representa mediante esta unidad.

**Pseudocódigo:**

```text
crear token visual
guardar tipo
guardar texto mostrado
```

**Relaciones:**

* Usa <a href="#cid-07-04">CID-07-04</a>.
* Se agrupa en <a href="#cid-07-06">CID-07-06</a>.
* Se manipula desde <a href="#cid-06-43">CID-06-43</a>, <a href="#cid-06-44">CID-06-44</a> y <a href="#cid-06-45">CID-06-45</a>.

---

### <a id="cid-07-06"></a>CID-07-06

**Qué hace:**
Define una línea visual como secuencia ordenada de tokens mostrables.

**Cómo funciona:**
Declara una estructura que contiene un vector de `TokenVisualCID`. Con ello, la bitácora puede representar una línea abierta o una línea cerrada como una secuencia visual ordenada.

**Pseudocódigo:**

```text
crear línea visual
guardar lista ordenada de tokens
```

**Relaciones:**

* Usa <a href="#cid-07-05">CID-07-05</a>.
* Se integra en <a href="#cid-07-07">CID-07-07</a> y <a href="#cid-07-28">CID-07-28</a>.
* Se compara desde <a href="#cid-06-08">CID-06-08</a>.

---

### <a id="cid-07-07"></a>CID-07-07

**Qué hace:**
Define el estado visual completo de la bitácora con historial cerrado y línea actual abierta.

**Cómo funciona:**
Declara una estructura que contiene un historial de líneas cerradas y la línea actual viva. Esta es la forma en que la bitácora expone su estado visual completo a la superposición.

**Pseudocódigo:**

```text
crear estado visual completo
guardar líneas cerradas
guardar línea actual
```

**Relaciones:**

* Usa <a href="#cid-07-06">CID-07-06</a>.
* Se devuelve desde <a href="#cid-07-19">CID-07-19</a>.
* Se construye en <a href="#cid-06-56">CID-06-56</a>.

---

### <a id="cid-07-08"></a>CID-07-08

**Qué hace:**
Declara la clase que gestiona el estado lógico, visual y reaperturas de la bitácora CID.

**Cómo funciona:**
Introduce la clase `BitacoraCID` y delimita sus zonas pública y privada. A partir de esta declaración se organiza toda la interfaz de la bitácora y todo su estado interno.

**Pseudocódigo:**

```text
declarar clase BitacoraCID
separar interfaz pública y estado privado
```

**Relaciones:**

* Agrupa <a href="#cid-07-09">CID-07-09</a> hasta <a href="#cid-07-29">CID-07-29</a>.
* Se implementa en <a href="#cid-06">CID-06</a>.

---

### <a id="cid-07-09"></a>CID-07-09

**Qué hace:**
Declara la construcción y destrucción segura de la bitácora con sincronización interna.

**Cómo funciona:**
Expone el constructor y el destructor de la clase. Estas operaciones inicializan y liberan el mecanismo de sincronización del objeto.

**Pseudocódigo:**

```text
declarar constructor de bitácora
declarar destructor de bitácora
```

**Relaciones:**

* Se implementa en <a href="#cid-06-03">CID-06-03</a> y <a href="#cid-06-04">CID-06-04</a>.

---

### <a id="cid-07-10"></a>CID-07-10

**Qué hace:**
Declara la configuración de límites para entradas lógicas y líneas visuales.

**Cómo funciona:**
Expone dos métodos públicos que permiten fijar el máximo de entradas lógicas pendientes y el máximo de líneas visuales cerradas conservadas.

**Pseudocódigo:**

```text
declarar configuración de máximo lógico
declarar configuración de máximo visual
```

**Relaciones:**

* Se implementa en <a href="#cid-06-14">CID-06-14</a> y <a href="#cid-06-15">CID-06-15</a>.
* Es usado desde <a href="#cid-01-25">CID-01-25</a>.

---

### <a id="cid-07-11"></a>CID-07-11

**Qué hace:**
Declara la limpieza total o parcial del estado lógico y visual de la bitácora.

**Cómo funciona:**
Expone tres métodos públicos: limpieza completa, limpieza solo lógica y limpieza solo visual. Esto permite reiniciar distintos planos de estado según el contexto.

**Pseudocódigo:**

```text
declarar limpieza total
declarar limpieza lógica parcial
declarar limpieza visual parcial
```

**Relaciones:**

* Se implementa en <a href="#cid-06-16">CID-06-16</a>, <a href="#cid-06-17">CID-06-17</a> y <a href="#cid-06-18">CID-06-18</a>.

---

### <a id="cid-07-12"></a>CID-07-12

**Qué hace:**
Declara las operaciones de consulta y anotación del estado lógico pendiente.

**Cómo funciona:**
Expone el tamaño lógico, la consulta de pendientes y la anotación de una nueva pieza lógica con su número tildal asociado.

**Pseudocódigo:**

```text
declarar consulta de tamaño lógico
declarar consulta de pendientes
declarar anotación de nueva pieza lógica
```

**Relaciones:**

* Se implementa en <a href="#cid-06-19">CID-06-19</a>, <a href="#cid-06-20">CID-06-20</a> y <a href="#cid-06-21">CID-06-21</a>.
* Es usado desde <a href="#cid-04-26">CID-04-26</a>, <a href="#cid-04-52">CID-04-52</a> y <a href="#cid-04-60">CID-04-60</a>.

---

### <a id="cid-07-13"></a>CID-07-13

**Qué hace:**
Declara la aplicación de tilde y del modificador D10 sobre la última entrada lógica.

**Cómo funciona:**
Expone dos operaciones públicas de transformación sobre la última pieza pendiente: una para aplicar tilde normal y otra para aplicar el modificador D10 con sus reglas oficiales.

**Pseudocódigo:**

```text
declarar aplicación de tilde
declarar aplicación de modificador D10
```

**Relaciones:**

* Se implementa en <a href="#cid-06-29">CID-06-29</a> y <a href="#cid-06-35">CID-06-35</a>.
* D10 se usa desde <a href="#cid-04-27">CID-04-27</a> dentro de <a href="#cid-04-25">CID-04-25</a>.

---

### <a id="cid-07-14"></a>CID-07-14

**Qué hace:**
Declara el borrado de la última entrada completa junto a modificadores asociados.

**Cómo funciona:**
Expone una operación pública que elimina la última pieza lógica y recorta también la parte visual y modificadora que dependa de ella.

**Pseudocódigo:**

```text
declarar borrado de última entrada completa
```

**Relaciones:**

* Se implementa en <a href="#cid-06-24">CID-06-24</a>.

---

### <a id="cid-07-15"></a>CID-07-15

**Qué hace:**
Declara el borrado o reversión de la última operación pendiente manteniendo la sincronía visual.

**Cómo funciona:**
Expone una operación pública de deshacer fino, capaz de revertir un modificador o eliminar una pieza según cuál fuera la última operación registrada.

**Pseudocódigo:**

```text
declarar deshacer de última operación pendiente
```

**Relaciones:**

* Se implementa en <a href="#cid-06-25">CID-06-25</a>.

---

### <a id="cid-07-16"></a>CID-07-16

**Qué hace:**
Declara la consulta, reemplazo y copia del contenido lógico pendiente de la bitácora.

**Cómo funciona:**
Expone métodos para obtener la última entrada, reemplazarla condicionalmente y devolver una copia plana del contenido lógico pendiente.

**Pseudocódigo:**

```text
declarar obtención de última entrada
declarar reemplazo condicional de última entrada
declarar copia lógica completa
```

**Relaciones:**

* Se implementa en <a href="#cid-06-22">CID-06-22</a>, <a href="#cid-06-23">CID-06-23</a> y <a href="#cid-06-28">CID-06-28</a>.

---

### <a id="cid-07-17"></a>CID-07-17

**Qué hace:**
Declara la anotación y borrado de tokens del estado visual de la línea actual.

**Cómo funciona:**
Expone operaciones visuales puras: añadir una pieza visual, añadir un modificador visual y borrar el último token visual de la línea actual.

**Pseudocódigo:**

```text
declarar anotación de token visual de pieza
declarar anotación de token visual de modificador
declarar borrado de último token visual
```

**Relaciones:**

* Se implementa en <a href="#cid-06-43">CID-06-43</a>, <a href="#cid-06-44">CID-06-44</a> y <a href="#cid-06-45">CID-06-45</a>.
* Es usado desde <a href="#cid-04-29">CID-04-29</a> y <a href="#cid-04-52">CID-04-52</a>.

---

### <a id="cid-07-18"></a>CID-07-18

**Qué hace:**
Declara el cierre por asentado y la posible reapertura de la última línea asentada.

**Cómo funciona:**
Expone dos operaciones públicas que permiten cerrar la línea viva actual como línea asentada y, más tarde, reabrirla si todavía no hay contenido nuevo activo.

**Pseudocódigo:**

```text
declarar cierre de línea por asentado
declarar reapertura de última línea asentada
```

**Relaciones:**

* Se implementa en <a href="#cid-06-46">CID-06-46</a> y <a href="#cid-06-50">CID-06-50</a>.

---

### <a id="cid-07-19"></a>CID-07-19

**Qué hace:**
Declara la obtención del estado visual completo expuesto hacia la superposición.

**Cómo funciona:**
Expone el método que construye y devuelve un `EstadoVisualBitacoraCID`, con las líneas cerradas y la línea actual.

**Pseudocódigo:**

```text
declarar obtención de estado visual completo
```

**Relaciones:**

* Usa el tipo definido en <a href="#cid-07-07">CID-07-07</a>.
* Se implementa en <a href="#cid-06-56">CID-06-56</a>.
* Es usado desde <a href="#cid-01-26">CID-01-26</a>, <a href="#cid-04-23">CID-04-23</a> y <a href="#cid-04-30">CID-04-30</a>.

---

### <a id="cid-07-20"></a>CID-07-20

**Qué hace:**
Define la estructura interna de una entrada lógica con texto, número tildal y estado de tilde.

**Cómo funciona:**
Declara una estructura privada que representa una pieza lógica viva de la bitácora. Guarda su texto, su número ordinal de tilde y si la tilde ya fue aplicada o no.

**Pseudocódigo:**

```text
crear entrada lógica interna
guardar texto
guardar número tildal
guardar bandera de tilde aplicada
```

**Relaciones:**

* Es usada por <a href="#cid-07-21">CID-07-21</a>, <a href="#cid-07-23">CID-07-23</a>, <a href="#cid-07-25">CID-07-25</a>, <a href="#cid-07-27">CID-07-27</a> y <a href="#cid-07-29">CID-07-29</a>.
* Se implementa y manipula en gran parte de <a href="#cid-06">CID-06</a>.

---

### <a id="cid-07-21"></a>CID-07-21

**Qué hace:**
Define la estructura interna de una operación pendiente para piezas y modificadores reversibles.

**Cómo funciona:**
Declara una estructura privada que representa una operación deshacible. Puede ser una pieza o un modificador y puede contener un snapshot previo para restaurar el estado anterior.

**Pseudocódigo:**

```text
crear operación pendiente interna
guardar tipo de operación
guardar datos de reversión si existen
```

**Relaciones:**

* Usa <a href="#cid-07-20">CID-07-20</a>.
* Contiene internamente <a href="#cid-07-22">CID-07-22</a> y <a href="#cid-07-23">CID-07-23</a>.
* Se usa en <a href="#cid-07-27">CID-07-27</a> y <a href="#cid-07-29">CID-07-29</a>.

---

### <a id="cid-07-22"></a>CID-07-22

**Qué hace:**
Define los tipos internos de operación pendiente manejados por la bitácora.

**Cómo funciona:**
Declara una enumeración privada con dos variantes: `Pieza` y `Modificador`. Esto permite distinguir entre operaciones normales de inserción y operaciones reversibles sobre una entrada ya existente.

**Pseudocódigo:**

```text
definir operación pendiente de tipo pieza
definir operación pendiente de tipo modificador
```

**Relaciones:**

* Forma parte de <a href="#cid-07-21">CID-07-21</a>.
* Se usa en <a href="#cid-06-10">CID-06-10</a>, <a href="#cid-06-11">CID-06-11</a>, <a href="#cid-06-25">CID-06-25</a> y <a href="#cid-06-21">CID-06-21</a>.

---

### <a id="cid-07-23"></a>CID-07-23

**Qué hace:**
Conserva el snapshot previo usado para deshacer operaciones modificadoras.

**Cómo funciona:**
Añade a la operación pendiente una bandera que indica si existe snapshot previo y una copia completa de la entrada anterior. Esto es lo que permite restaurar el valor previo al deshacer un modificador.

**Pseudocódigo:**

```text
guardar si existe snapshot previo
guardar copia de la entrada anterior
```

**Relaciones:**

* Usa <a href="#cid-07-20">CID-07-20</a>.
* Forma parte de <a href="#cid-07-21">CID-07-21</a>.
* Se rellena desde <a href="#cid-06-10">CID-06-10</a> y se consume en <a href="#cid-06-26">CID-06-26</a>.

---

### <a id="cid-07-24"></a>CID-07-24

**Qué hace:**
Declara helpers internos para tildado y comparación completa de líneas visuales.

**Cómo funciona:**
Expone como métodos privados estáticos dos utilidades internas: una para aplicar tildes según posición vocálica y otra para comparar líneas visuales completas.

**Pseudocódigo:**

```text
declarar helper de tilde por número
declarar helper de comparación de líneas visuales
```

**Relaciones:**

* Se implementa en <a href="#cid-06-07">CID-06-07</a> y <a href="#cid-06-08">CID-06-08</a>.

---

### <a id="cid-07-25"></a>CID-07-25

**Qué hace:**
Declara helpers internos sin lock para recorte visual y registro de operaciones modificadoras.

**Cómo funciona:**
Expone tres utilidades privadas que deben ejecutarse con el lock ya tomado: limitar líneas visuales, registrar un modificador con snapshot y recortar operación y tokens asociados a la última entrada.

**Pseudocódigo:**

```text
declarar helper de recorte visual sin lock
declarar helper de anotación modificadora sin lock
declarar helper de recorte lógico-visual sin lock
```

**Relaciones:**

* Se implementa en <a href="#cid-06-09">CID-06-09</a>, <a href="#cid-06-10">CID-06-10</a> y <a href="#cid-06-11">CID-06-11</a>.

---

### <a id="cid-07-26"></a>CID-07-26

**Qué hace:**
Define el estado interno de sincronización de acceso concurrente a la bitácora.

**Cómo funciona:**
Declara una sección crítica mutable y una bandera que indica si esta fue inicializada. Casi todos los métodos públicos de la bitácora dependen de este mecanismo para operar de forma segura.

**Pseudocódigo:**

```text
guardar sección crítica interna
guardar bandera de sincronización iniciada
```

**Relaciones:**

* Se inicializa en <a href="#cid-06-03">CID-06-03</a>.
* Se libera en <a href="#cid-06-04">CID-06-04</a>.
* Protege prácticamente toda la implementación de <a href="#cid-06">CID-06</a>.

---

### <a id="cid-07-27"></a>CID-07-27

**Qué hace:**
Define el estado lógico pendiente de la línea viva con límite máximo y operaciones deshacibles.

**Cómo funciona:**
Declara el máximo de entradas lógicas, el vector de entradas vivas y el vector de operaciones pendientes que permiten deshacer piezas y modificadores.

**Pseudocódigo:**

```text
guardar máximo lógico
guardar lista de entradas pendientes
guardar lista de operaciones pendientes
```

**Relaciones:**

* Usa <a href="#cid-07-20">CID-07-20</a> y <a href="#cid-07-21">CID-07-21</a>.
* Se manipula en <a href="#cid-06-14">CID-06-14</a>, <a href="#cid-06-16">CID-06-16</a>, <a href="#cid-06-17">CID-06-17</a>, <a href="#cid-06-21">CID-06-21</a>, <a href="#cid-06-24">CID-06-24</a>, <a href="#cid-06-25">CID-06-25</a>, <a href="#cid-06-29">CID-06-29</a> y <a href="#cid-06-35">CID-06-35</a>.

---

### <a id="cid-07-28"></a>CID-07-28

**Qué hace:**
Define el estado visual con historial de líneas cerradas y línea actual abierta.

**Cómo funciona:**
Declara el máximo visual, el vector de líneas cerradas y la línea actual viva. Este es el núcleo del plano visual de la bitácora.

**Pseudocódigo:**

```text
guardar máximo visual
guardar historial de líneas cerradas
guardar línea actual abierta
```

**Relaciones:**

* Usa <a href="#cid-07-06">CID-07-06</a>.
* Se manipula en <a href="#cid-06-09">CID-06-09</a>, <a href="#cid-06-15">CID-06-15</a>, <a href="#cid-06-18">CID-06-18</a>, <a href="#cid-06-43">CID-06-43</a>, <a href="#cid-06-44">CID-06-44</a>, <a href="#cid-06-45">CID-06-45</a>, <a href="#cid-06-46">CID-06-46</a>, <a href="#cid-06-48">CID-06-48</a> y <a href="#cid-06-56">CID-06-56</a>.

---

### <a id="cid-07-29"></a>CID-07-29

**Qué hace:**
Define el snapshot de la última línea asentada para permitir su reapertura posterior.

**Cómo funciona:**
Declara una bandera que indica si existe una línea reabrible y tres snapshots: uno visual, uno lógico y uno de operaciones. Este bloque es la base de la funcionalidad de reapertura de la última línea asentada.

**Pseudocódigo:**

```text
guardar bandera de snapshot reabrible
guardar snapshot visual de última línea
guardar snapshot lógico de última línea
guardar snapshot de operaciones de última línea
```

**Relaciones:**

* Usa <a href="#cid-07-06">CID-07-06</a>, <a href="#cid-07-20">CID-07-20</a> y <a href="#cid-07-21">CID-07-21</a>.
* Se rellena en <a href="#cid-06-47">CID-06-47</a>.
* Se consume en <a href="#cid-06-50">CID-06-50</a> hasta <a href="#cid-06-55">CID-06-55</a>.


## CID-08

La referencia <a href="#cid-08">CID-08</a> corresponde al archivo <code>gestor_asentado.cpp</code>. Este archivo implementa el gestor de asentado del sistema CID. Su responsabilidad principal es decidir cuándo una línea viva debe asentarse, ya sea por acción manual mediante el pedal CID o por inactividad detectada mediante auto-asentado dinámico.

Dentro de <a href="#cid-08">CID-08</a> también se concentra toda la lógica de sincronización, temporización y adaptación inteligente del ritmo de escritura. Por eso aquí conviven la protección por sección crítica, el temporizador periódico, la gestión del contexto de mayúsculas, el seguimiento del último texto inyectado y el ajuste progresivo del tiempo de auto-asentado. En términos prácticos, <a href="#cid-08">CID-08</a> es la pieza que convierte la actividad CID en texto ya asentado, lo inyecta en el sistema y mantiene coherente la representación visual de la bitácora.

### Índice interno de bloques

* <a href="#cid-08-01">CID-08-01</a>
* <a href="#cid-08-02">CID-08-02</a>
* <a href="#cid-08-03">CID-08-03</a>
* <a href="#cid-08-04">CID-08-04</a>
* <a href="#cid-08-05">CID-08-05</a>
* <a href="#cid-08-06">CID-08-06</a>
* <a href="#cid-08-07">CID-08-07</a>
* <a href="#cid-08-08">CID-08-08</a>
* <a href="#cid-08-09">CID-08-09</a>
* <a href="#cid-08-10">CID-08-10</a>
* <a href="#cid-08-11">CID-08-11</a>
* <a href="#cid-08-12">CID-08-12</a>
* <a href="#cid-08-13">CID-08-13</a>
* <a href="#cid-08-14">CID-08-14</a>
* <a href="#cid-08-15">CID-08-15</a>
* <a href="#cid-08-16">CID-08-16</a>
* <a href="#cid-08-17">CID-08-17</a>
* <a href="#cid-08-18">CID-08-18</a>
* <a href="#cid-08-19">CID-08-19</a>
* <a href="#cid-08-20">CID-08-20</a>
* <a href="#cid-08-21">CID-08-21</a>
* <a href="#cid-08-22">CID-08-22</a>
* <a href="#cid-08-23">CID-08-23</a>
* <a href="#cid-08-24">CID-08-24</a>
* <a href="#cid-08-25">CID-08-25</a>
* <a href="#cid-08-26">CID-08-26</a>
* <a href="#cid-08-27">CID-08-27</a>
* <a href="#cid-08-28">CID-08-28</a>
* <a href="#cid-08-29">CID-08-29</a>
* <a href="#cid-08-30">CID-08-30</a>
* <a href="#cid-08-31">CID-08-31</a>
* <a href="#cid-08-32">CID-08-32</a>
* <a href="#cid-08-33">CID-08-33</a>
* <a href="#cid-08-34">CID-08-34</a>
* <a href="#cid-08-35">CID-08-35</a>
* <a href="#cid-08-36">CID-08-36</a>
* <a href="#cid-08-37">CID-08-37</a>
* <a href="#cid-08-38">CID-08-38</a>
* <a href="#cid-08-39">CID-08-39</a>
* <a href="#cid-08-40">CID-08-40</a>
* <a href="#cid-08-41">CID-08-41</a>
* <a href="#cid-08-42">CID-08-42</a>
* <a href="#cid-08-43">CID-08-43</a>
* <a href="#cid-08-44">CID-08-44</a>
* <a href="#cid-08-45">CID-08-45</a>
* <a href="#cid-08-46">CID-08-46</a>
* <a href="#cid-08-47">CID-08-47</a>
* <a href="#cid-08-48">CID-08-48</a>
* <a href="#cid-08-49">CID-08-49</a>
* <a href="#cid-08-50">CID-08-50</a>
* <a href="#cid-08-51">CID-08-51</a>
* <a href="#cid-08-52">CID-08-52</a>
* <a href="#cid-08-53">CID-08-53</a>
* <a href="#cid-08-54">CID-08-54</a>
* <a href="#cid-08-55">CID-08-55</a>
* <a href="#cid-08-56">CID-08-56</a>
* <a href="#cid-08-57">CID-08-57</a>
* <a href="#cid-08-58">CID-08-58</a>
* <a href="#cid-08-59">CID-08-59</a>
* <a href="#cid-08-60">CID-08-60</a>

---

### <a id="cid-08-01"></a>CID-08-01

**Qué hace:**
Incluye la interfaz pública del gestor de asentado que este archivo implementa.

**Cómo funciona:**
Este bloque incorpora la cabecera `gestor_asentado.h`, que declara las funciones exportadas del subsistema de asentado. Gracias a ello, la implementación actual puede definirse con la misma firma pública esperada por el resto del motor.

**Pseudocódigo:**

```text
incluir interfaz del gestor de asentado
habilitar definición de sus funciones públicas
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-08">CID-08</a>.
* Da soporte directo a <a href="#cid-08-38">CID-08-38</a>, <a href="#cid-08-46">CID-08-46</a>, <a href="#cid-08-50">CID-08-50</a>, <a href="#cid-08-53">CID-08-53</a> y <a href="#cid-08-56">CID-08-56</a>.

---

### <a id="cid-08-02"></a>CID-08-02

**Qué hace:**
Incluye los módulos externos con los que el gestor de asentado interactúa durante su operación real.

**Cómo funciona:**
Este bloque conecta la implementación con la bitácora CID, el sistema de inyección de texto y la superposición visual. A partir de estas inclusiones, el gestor puede leer piezas pendientes, cerrar o reabrir líneas, escribir texto real en el sistema y actualizar el estado visible mostrado al usuario.

**Pseudocódigo:**

```text
incluir módulo de bitácora
incluir módulo de inyección de texto
incluir módulo de superposición visual
```

**Relaciones:**

* Da acceso a funcionalidades usadas por <a href="#cid-08-07">CID-08-07</a>, <a href="#cid-08-23">CID-08-23</a>, <a href="#cid-08-28">CID-08-28</a>, <a href="#cid-08-31">CID-08-31</a>, <a href="#cid-08-59">CID-08-59</a> y <a href="#cid-08-60">CID-08-60</a>.
* Enlaza con <code>bitacora_cid.h</code>, <code>inyeccion_texto.h</code> y <code>superposicion_cid.h</code>.

---

### <a id="cid-08-03"></a>CID-08-03

**Qué hace:**
Incluye cabeceras del sistema y de la biblioteca estándar necesarias para sincronización, texto, contenedores y tratamiento de caracteres.

**Cómo funciona:**
Este bloque habilita el acceso a la API Win32, a `std::wstring`, a `std::vector` y a utilidades de clasificación y transformación de caracteres anchos. No contiene lógica ejecutable, pero establece las dependencias necesarias para compilar el resto del archivo.

**Pseudocódigo:**

```text
incluir API de Windows
incluir soporte de cadenas
incluir soporte de vectores
incluir utilidades de caracteres anchos
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-08">CID-08</a>.
* Da soporte indirecto a <a href="#cid-08-06">CID-08-06</a>, <a href="#cid-08-19">CID-08-19</a>, <a href="#cid-08-21">CID-08-21</a> y al resto de bloques que usan Win32 o tipos estándar.

---

### <a id="cid-08-04"></a>CID-08-04

**Qué hace:**
Proporciona un helper para limitar enteros a un rango cerrado.

**Cómo funciona:**
Recibe un valor y dos límites. Si el valor cae por debajo del mínimo devuelve el mínimo; si supera el máximo devuelve el máximo; en cualquier otro caso devuelve el propio valor. Se usa para garantizar que tiempos y parámetros internos permanezcan dentro de márgenes válidos.

**Pseudocódigo:**

```text
si valor < mínimo:
    devolver mínimo
si valor > máximo:
    devolver máximo
devolver valor
```

**Relaciones:**

* Usado por <a href="#cid-08-18">CID-08-18</a>, <a href="#cid-08-40">CID-08-40</a> y <a href="#cid-08-52">CID-08-52</a>.

---

### <a id="cid-08-05"></a>CID-08-05

**Qué hace:**
Devuelve el valor absoluto de un entero para comparaciones internas del gestor.

**Cómo funciona:**
Comprueba si el entero es negativo. Si lo es, devuelve su opuesto; si no, devuelve el mismo valor. Su uso principal es medir distancia entre tiempos para aplicar la histéresis del auto-asentado.

**Pseudocódigo:**

```text
si x es negativo:
    devolver -x
devolver x
```

**Relaciones:**

* Usado por <a href="#cid-08-18">CID-08-18</a>.

---

### <a id="cid-08-06"></a>CID-08-06

**Qué hace:**
Centraliza el envío de mensajes de depuración del gestor de asentado al visor de salida de Windows.

**Cómo funciona:**
Recibe una cadena ancha, le concatena un salto de línea y la envía mediante `OutputDebugStringW`. Con ello unifica el registro interno del subsistema sin repetir la misma operación de depuración en múltiples puntos.

**Pseudocódigo:**

```text
añadir salto de línea al mensaje
enviar mensaje al depurador de Windows
```

**Relaciones:**

* Usado por <a href="#cid-08-18">CID-08-18</a>, <a href="#cid-08-44">CID-08-44</a>, <a href="#cid-08-45">CID-08-45</a> y <a href="#cid-08-49">CID-08-49</a>.

---

### <a id="cid-08-07"></a>CID-08-07

**Qué hace:**
Refresca la superposición visual a partir del estado actual expuesto por la bitácora conectada.

**Cómo funciona:**
Comprueba primero si la bitácora existe. Si no existe, no hace nada. Si existe, obtiene su estado visual y lo publica en la superposición mediante `Superposicion_SetEstadoVisual`. La función se asume invocada sin bloqueo adicional porque se usa dentro de regiones ya protegidas.

**Pseudocódigo:**

```text
si no hay bitácora:
    salir
obtener estado visual de la bitácora
enviarlo a la superposición
```

**Relaciones:**

* Usa funcionalidad de bitácora y superposición.
* Es llamada desde <a href="#cid-08-31">CID-08-31</a>, <a href="#cid-08-43">CID-08-43</a> y <a href="#cid-08-59">CID-08-59</a>.

---

### <a id="cid-08-08"></a>CID-08-08

**Qué hace:**
Declara el estado global de sincronización encargado de proteger el acceso concurrente al gestor.

**Cómo funciona:**
Reserva una sección crítica global y una bandera que indica si ya ha sido inicializada. La sección crítica se usa para serializar el acceso desde callbacks, temporizadores y llamadas públicas del subsistema.

**Pseudocódigo:**

```text
declarar sección crítica global
declarar bandera de inicialización
```

**Relaciones:**

* Usado por <a href="#cid-08-39">CID-08-39</a>, <a href="#cid-08-49">CID-08-49</a>, <a href="#cid-08-50">CID-08-50</a>, <a href="#cid-08-53">CID-08-53</a> y <a href="#cid-08-56">CID-08-56</a>.
* Protege la lógica ejecutada en <a href="#cid-08-32">CID-08-32</a> y en las funciones públicas del gestor.

---

### <a id="cid-08-09"></a>CID-08-09

**Qué hace:**
Mantiene un puntero global a la bitácora activa sobre la que opera el gestor de asentado.

**Cómo funciona:**
Declara una referencia global inicialmente nula. Este puntero permite al gestor leer la línea viva, cerrarla, reabrirla y publicar su estado visual cuando el sistema ya ha conectado una bitácora real.

**Pseudocódigo:**

```text
declarar puntero global a bitácora
inicializarlo a nulo
```

**Relaciones:**

* Se asigna en <a href="#cid-08-40">CID-08-40</a>.
* Es usado por <a href="#cid-08-07">CID-08-07</a>, <a href="#cid-08-23">CID-08-23</a>, <a href="#cid-08-33">CID-08-33</a>, <a href="#cid-08-35">CID-08-35</a>, <a href="#cid-08-43">CID-08-43</a>, <a href="#cid-08-55">CID-08-55</a> y <a href="#cid-08-59">CID-08-59</a>.

---

### <a id="cid-08-10"></a>CID-08-10

**Qué hace:**
Guarda el estado físico del pedal CID para bloquear el auto-asentado mientras permanezca pulsado.

**Cómo funciona:**
Declara una bandera booleana global inicialmente a `false`. El sistema la pone a `true` al pulsar el pedal y a `false` al soltarlo. Mientras esté activa, el temporizador periódico evita asentar automáticamente.

**Pseudocódigo:**

```text
declarar estado global del pedal
inicializarlo como no pulsado
```

**Relaciones:**

* Se actualiza en <a href="#cid-08-40">CID-08-40</a>, <a href="#cid-08-54">CID-08-54</a> y <a href="#cid-08-55">CID-08-55</a>.
* Es consultado en <a href="#cid-08-34">CID-08-34</a> y <a href="#cid-08-52">CID-08-52</a>.

---

### <a id="cid-08-11"></a>CID-08-11

**Qué hace:**
Mantiene el umbral actual de auto-asentado dinámico en milisegundos.

**Cómo funciona:**
Declara un entero global con valor inicial de 400 ms. Este valor representa la inactividad mínima necesaria para disparar el asentado automático y puede ajustarse con el ritmo observado del usuario.

**Pseudocódigo:**

```text
declarar tiempo global de auto-asentado
inicializarlo a 400 ms
```

**Relaciones:**

* Se actualiza en <a href="#cid-08-18">CID-08-18</a>, <a href="#cid-08-40">CID-08-40</a> y <a href="#cid-08-52">CID-08-52</a>.
* Es consultado en <a href="#cid-08-37">CID-08-37</a> y en el log de <a href="#cid-08-45">CID-08-45</a>.

---

### <a id="cid-08-12"></a>CID-08-12

**Qué hace:**
Declara los recursos de temporización usados para el chequeo periódico de inactividad.

**Cómo funciona:**
Mantiene una cola global de temporizadores, un temporizador concreto y una constante de periodo fijo de chequeo. La cola permite alojar el callback periódico y el periodo determina cada cuántos milisegundos se revisa si debe dispararse el auto-asentado.

**Pseudocódigo:**

```text
declarar cola global de temporizadores
declarar temporizador global
definir periodo fijo de chequeo
```

**Relaciones:**

* Se inicializa en <a href="#cid-08-41">CID-08-41</a> y <a href="#cid-08-42">CID-08-42</a>.
* Se destruye en <a href="#cid-08-47">CID-08-47</a> y <a href="#cid-08-48">CID-08-48</a>.
* Alimenta la ejecución periódica de <a href="#cid-08-32">CID-08-32</a>.

---

### <a id="cid-08-13"></a>CID-08-13

**Qué hace:**
Registra el último instante de actividad CID real para medir la inactividad antes del auto-asentado.

**Cómo funciona:**
Declara un contador global de ticks de 64 bits. Cada vez que ocurre una actividad relevante se actualiza con el tiempo actual, y el temporizador lo compara con el reloj presente para calcular cuántos milisegundos han pasado sin actividad.

**Pseudocódigo:**

```text
declarar tick global de última actividad
```

**Relaciones:**

* Se actualiza en <a href="#cid-08-37">CID-08-37</a>, <a href="#cid-08-40">CID-08-40</a>, <a href="#cid-08-51">CID-08-51</a> y <a href="#cid-08-53">CID-08-53</a>.
* Es usado en <a href="#cid-08-36">CID-08-36</a>.

---

### <a id="cid-08-14"></a>CID-08-14

**Qué hace:**
Conserva el último texto realmente inyectado en el sistema para poder borrarlo más tarde con precisión.

**Cómo funciona:**
Declara una cadena global que almacena la palabra asentada junto con el espacio final que se escribió. Gracias a ello, el borrado del último asentado puede generar exactamente el mismo número de retrocesos que caracteres fueron inyectados.

**Pseudocódigo:**

```text
declarar cadena global del último texto inyectado
```

**Relaciones:**

* Se actualiza en <a href="#cid-08-26">CID-08-26</a>.
* Es consultada en <a href="#cid-08-57">CID-08-57</a> y usada para calcular el tamaño en <a href="#cid-08-58">CID-08-58</a>.
* Se limpia en <a href="#cid-08-40">CID-08-40</a> y <a href="#cid-08-60">CID-08-60</a>.

---

### <a id="cid-08-15"></a>CID-08-15

**Qué hace:**
Mantiene el contexto interno que decide si la siguiente palabra debe comenzar con mayúscula.

**Cómo funciona:**
Declara una bandera booleana global inicialmente a `true`. Esa bandera se consulta antes de asentar una palabra y se actualiza después según el último signo no espaciador asentado.

**Pseudocódigo:**

```text
declarar contexto global de mayúscula inicial
inicializarlo a verdadero
```

**Relaciones:**

* Se consulta en <a href="#cid-08-25">CID-08-25</a>.
* Se actualiza en <a href="#cid-08-29">CID-08-29</a>.
* Se reinicia en <a href="#cid-08-40">CID-08-40</a>.

---

### <a id="cid-08-16"></a>CID-08-16

**Qué hace:**
Declara el estado y las constantes que gobiernan la adaptación inteligente del ritmo de auto-asentado.

**Cómo funciona:**
Mantiene el promedio temporal observado del usuario y un conjunto de constantes que controlan el filtrado exponencial, el factor de expansión hacia el objetivo, el margen fijo añadido, los límites globales, la histéresis y el paso máximo por ajuste. También registra el último tick usado para medir ritmo.

**Pseudocódigo:**

```text
declarar promedio temporal observado
definir alpha del suavizado
definir factor del objetivo
definir margen fijo
definir límites mínimo y máximo
definir histéresis y paso máximo
declarar tick anterior del ritmo
```

**Relaciones:**

* Es usado por <a href="#cid-08-17">CID-08-17</a>, <a href="#cid-08-18">CID-08-18</a>, <a href="#cid-08-40">CID-08-40</a>, <a href="#cid-08-51">CID-08-51</a>, <a href="#cid-08-52">CID-08-52</a>, <a href="#cid-08-54">CID-08-54</a> y <a href="#cid-08-55">CID-08-55</a>.

---

### <a id="cid-08-17"></a>CID-08-17

**Qué hace:**
Decide si un delta temporal es válido para entrenar el ritmo del auto-asentado.

**Cómo funciona:**
Recibe un intervalo temporal y descarta valores demasiado pequeños o demasiado grandes. Los intervalos inferiores a 15 ms se consideran ruido y los superiores a 1200 ms se consideran pausas largas que contaminarían el promedio. Solo los valores intermedios se aceptan como señal útil.

**Pseudocódigo:**

```text
si delta < 15:
    devolver falso
si delta > 1200:
    devolver falso
devolver verdadero
```

**Relaciones:**

* Usado por <a href="#cid-08-52">CID-08-52</a>.

---

### <a id="cid-08-18"></a>CID-08-18

**Qué hace:**
Ajusta el valor actual de auto-asentado hacia un objetivo respetando histéresis, paso máximo y límites globales.

**Cómo funciona:**
Primero compara la distancia entre el objetivo y el valor actual. Si la diferencia es menor que la histéresis, no cambia nada. Si debe ajustar, avanza o retrocede como máximo `PASO_MAX_MS` por llamada, luego limita el resultado entre `AUTO_MIN_MS` y `AUTO_MAX_MS` y finalmente registra una traza con el nuevo valor y el promedio observado.

**Pseudocódigo:**

```text
si diferencia entre objetivo y auto actual es menor que histéresis:
    salir

si objetivo es mayor que auto actual:
    subir auto actual con paso máximo
si no:
    bajar auto actual con paso máximo

limitar auto actual al rango global
escribir log con auto actual y promedio
```

**Relaciones:**

* Usa <a href="#cid-08-05">CID-08-05</a>, <a href="#cid-08-04">CID-08-04</a> y <a href="#cid-08-06">CID-08-06</a>.
* Es llamada desde <a href="#cid-08-52">CID-08-52</a>.

---

### <a id="cid-08-19"></a>CID-08-19

**Qué hace:**
Aplica mayúscula a la primera letra alfabética encontrada en una cadena.

**Cómo funciona:**
Recorre la cadena de izquierda a derecha. Cuando encuentra el primer carácter alfabético según `iswalpha`, lo convierte a mayúscula con `towupper` y termina. Si no encuentra ninguna letra, deja la cadena intacta.

**Pseudocódigo:**

```text
recorrer caracteres de la cadena
si un carácter es alfabético:
    convertirlo a mayúscula
    terminar
```

**Relaciones:**

* Es llamada desde <a href="#cid-08-25">CID-08-25</a>.

---

### <a id="cid-08-20"></a>CID-08-20

**Qué hace:**
Obtiene el último carácter no espaciador de una cadena para inferir el contexto de mayúsculas posterior.

**Cómo funciona:**
Recorre la cadena de derecha a izquierda. Ignora espacios y tabuladores y devuelve el primer carácter significativo que encuentre. Si no existe ninguno, devuelve cero.

**Pseudocódigo:**

```text
recorrer cadena desde el final
si el carácter no es espacio ni tabulador:
    devolver carácter
devolver 0
```

**Relaciones:**

* Es llamada desde <a href="#cid-08-29">CID-08-29</a>.

---

### <a id="cid-08-21"></a>CID-08-21

**Qué hace:**
Inyecta una secuencia física de retrocesos para borrar texto previamente escrito.

**Cómo funciona:**
Recibe un número de caracteres a borrar. Si el valor no es positivo, no hace nada. Si sí lo es, prepara un vector de eventos `INPUT`, reserva capacidad suficiente para pares de pulsación y liberación, delega la construcción de esos eventos y finalmente los envía al sistema mediante `SendInput`.

**Pseudocódigo:**

```text
si n <= 0:
    salir

crear vector de eventos de entrada
reservar espacio para 2 eventos por carácter
construir eventos de backspace
enviar eventos al sistema
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-22">CID-08-22</a>.
* Es llamada desde <a href="#cid-08-58">CID-08-58</a>.

---

### <a id="cid-08-22"></a>CID-08-22

**Qué hace:**
Construye la secuencia de pulsación y liberación de Backspace tantas veces como caracteres haya que borrar.

**Cómo funciona:**
Itera `n` veces. En cada iteración crea un `INPUT` de tecla pulsada con `VK_BACK` y otro de tecla liberada con la misma tecla y la bandera `KEYEVENTF_KEYUP`. Ambos eventos se añaden al vector en orden para representar un retroceso físico completo.

**Pseudocódigo:**

```text
repetir n veces:
    crear evento de pulsación de backspace
    añadirlo
    crear evento de liberación de backspace
    añadirlo
```

**Relaciones:**

* Forma parte de <a href="#cid-08-21">CID-08-21</a>.

---

### <a id="cid-08-23"></a>CID-08-23

**Qué hace:**
Asienta la línea viva actual concatenando piezas, escribiendo texto real y cerrando la línea visual correspondiente.

**Cómo funciona:**
Comprueba primero si existe bitácora y si contiene piezas pendientes. Si no, no hace nada. Si sí, obtiene una copia de las piezas, construye la palabra final, puede aplicar mayúscula inicial, registra el último texto inyectado, actualiza la superposición, inyecta el texto real, recalcula el contexto de mayúsculas, cierra la línea en la bitácora y refresca la representación visual. La función opera bajo la suposición de que el bloqueo ya está tomado.

**Pseudocódigo:**

```text
si no hay bitácora:
    salir
obtener copia de piezas pendientes
si no hay piezas:
    salir

construir palabra final
aplicar mayúscula si corresponde
guardar último texto inyectado
actualizar superposición textual
inyectar texto real
actualizar contexto de mayúscula
cerrar línea en la bitácora
refrescar superposición visual
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-24">CID-08-24</a> a <a href="#cid-08-31">CID-08-31</a>.
* Es llamada desde <a href="#cid-08-37">CID-08-37</a> y <a href="#cid-08-55">CID-08-55</a>.
* Usa la bitácora global de <a href="#cid-08-09">CID-08-09</a>.

---

### <a id="cid-08-24"></a>CID-08-24

**Qué hace:**
Construye la palabra final concatenando todas las piezas pendientes sin insertar espacios internos.

**Cómo funciona:**
Parte de una cadena vacía y recorre las piezas copiadas desde la bitácora. Cada pieza se añade al final de la palabra en el mismo orden en que fue registrada, generando así el texto final que va a asentarse.

**Pseudocódigo:**

```text
crear palabra vacía
para cada pieza pendiente:
    concatenarla a la palabra
```

**Relaciones:**

* Forma parte de <a href="#cid-08-23">CID-08-23</a>.
* Precede a <a href="#cid-08-25">CID-08-25</a>.

---

### <a id="cid-08-25"></a>CID-08-25

**Qué hace:**
Aplica mayúscula inicial a la palabra asentada cuando el contexto interno así lo exige.

**Cómo funciona:**
Consulta la bandera global de contexto. Si está activa, llama al helper que convierte en mayúscula la primera letra alfabética de la palabra. Si no está activa, deja la palabra tal como estaba.

**Pseudocódigo:**

```text
si debe haber mayúscula inicial:
    aplicar mayúscula a la palabra
```

**Relaciones:**

* Usa <a href="#cid-08-15">CID-08-15</a> y <a href="#cid-08-19">CID-08-19</a>.
* Forma parte de <a href="#cid-08-23">CID-08-23</a>.

---

### <a id="cid-08-26"></a>CID-08-26

**Qué hace:**
Guarda el último texto inyectado incluyendo el espacio final para permitir su borrado exacto posterior.

**Cómo funciona:**
Construye una cadena formada por la palabra ya asentada más un espacio al final y la almacena en la variable global dedicada al último inyectado. Ese valor será el que determine cuántos backspaces deben enviarse si se deshace el último asentado.

**Pseudocódigo:**

```text
guardar palabra + espacio como último texto inyectado
```

**Relaciones:**

* Usa el estado global definido en <a href="#cid-08-14">CID-08-14</a>.
* Forma parte de <a href="#cid-08-23">CID-08-23</a>.
* Alimenta después a <a href="#cid-08-57">CID-08-57</a> y <a href="#cid-08-58">CID-08-58</a>.

---

### <a id="cid-08-27"></a>CID-08-27

**Qué hace:**
Actualiza el texto visible de la superposición con la palabra que acaba de asentarse.

**Cómo funciona:**
Entrega la palabra ya finalizada a `Superposicion_SetUltimoAsentado`. Con ello la interfaz visual refleja inmediatamente cuál ha sido el último texto confirmado por el gestor.

**Pseudocódigo:**

```text
publicar palabra asentada en la superposición
```

**Relaciones:**

* Usa funcionalidad de superposición visual.
* Forma parte de <a href="#cid-08-23">CID-08-23</a>.

---

### <a id="cid-08-28"></a>CID-08-28

**Qué hace:**
Inyecta el texto asentado en el sistema marcando temporalmente la escritura como inyección propia del motor.

**Cómo funciona:**
Activa la marca interna de inyección, llama a `InyectarTextoUnicode` con el texto completo guardado en `g_ultimo_inyectado` y después desactiva la marca. Esto evita que la propia escritura provocada por el motor se trate como entrada ajena.

**Pseudocódigo:**

```text
marcar inyección como activa
inyectar texto unicode real
desmarcar inyección como activa
```

**Relaciones:**

* Usa <code>inyeccion_texto.h</code>.
* Depende del valor preparado en <a href="#cid-08-26">CID-08-26</a>.
* Forma parte de <a href="#cid-08-23">CID-08-23</a>.

---

### <a id="cid-08-29"></a>CID-08-29

**Qué hace:**
Actualiza el contexto de mayúscula para la siguiente palabra según el signo final asentado.

**Cómo funciona:**
Obtiene el último carácter significativo de la palabra y comprueba si es punto, exclamación o interrogación. Si lo es, activa el contexto de mayúscula para la siguiente palabra; en caso contrario lo desactiva.

**Pseudocódigo:**

```text
obtener último carácter no espaciador
si es punto, exclamación o interrogación:
    activar mayúscula inicial futura
si no:
    desactivarla
```

**Relaciones:**

* Usa <a href="#cid-08-20">CID-08-20</a> y actualiza <a href="#cid-08-15">CID-08-15</a>.
* Forma parte de <a href="#cid-08-23">CID-08-23</a>.

---

### <a id="cid-08-30"></a>CID-08-30

**Qué hace:**
Cierra la línea actual en la bitácora y vacía los pendientes de la línea viva.

**Cómo funciona:**
Llama al método `CerrarLineaPorAsentado` sobre la bitácora conectada. Ese paso transforma la línea viva en una línea ya asentada dentro del historial visual del sistema.

**Pseudocódigo:**

```text
cerrar línea actual por asentado en la bitácora
```

**Relaciones:**

* Usa la bitácora global de <a href="#cid-08-09">CID-08-09</a>.
* Forma parte de <a href="#cid-08-23">CID-08-23</a>.
* Precede a <a href="#cid-08-31">CID-08-31</a>.

---

### <a id="cid-08-31"></a>CID-08-31

**Qué hace:**
Refresca el panel visual después de completar el asentado real de la línea.

**Cómo funciona:**
Llama al helper de refresco con la bitácora actual, de modo que la superposición muestre la nueva situación: línea ya cerrada y línea viva vacía o actualizada según corresponda.

**Pseudocódigo:**

```text
refrescar superposición visual con la bitácora actual
```

**Relaciones:**

* Usa <a href="#cid-08-07">CID-08-07</a>.
* Forma parte de <a href="#cid-08-23">CID-08-23</a>.

---

### <a id="cid-08-32"></a>CID-08-32

**Qué hace:**
Implementa el callback periódico que chequea la inactividad para disparar el auto-asentado cuando corresponda.

**Cómo funciona:**
Entra en la sección crítica, valida primero que exista bitácora, que el pedal no esté pulsado y que haya piezas pendientes. Después calcula el tiempo transcurrido desde la última actividad CID real y, si dicho tiempo supera el umbral dinámico actual, ejecuta el asentado y actualiza el tick de referencia. Finalmente libera el bloqueo.

**Pseudocódigo:**

```text
entrar en sección crítica

si no hay bitácora:
    salir

si el pedal está abajo:
    salir

si no hay piezas pendientes:
    salir

calcular inactividad actual
si la inactividad supera el auto-asentado:
    asentar
    actualizar último tick

salir de sección crítica
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-33">CID-08-33</a> a <a href="#cid-08-37">CID-08-37</a>.
* Es registrado como callback periódico en <a href="#cid-08-42">CID-08-42</a>.
* Usa la sincronización de <a href="#cid-08-08">CID-08-08</a>.

---

### <a id="cid-08-33"></a>CID-08-33

**Qué hace:**
Sale inmediatamente del callback si no hay una bitácora conectada sobre la que operar.

**Cómo funciona:**
Comprueba el puntero global a bitácora. Si es nulo, libera la sección crítica y termina el callback sin intentar medir inactividad ni asentar nada.

**Pseudocódigo:**

```text
si no hay bitácora:
    liberar sección crítica
    salir
```

**Relaciones:**

* Usa <a href="#cid-08-09">CID-08-09</a>.
* Forma parte de <a href="#cid-08-32">CID-08-32</a>.

---

### <a id="cid-08-34"></a>CID-08-34

**Qué hace:**
Bloquea el auto-asentado mientras el pedal CID permanezca físicamente pulsado.

**Cómo funciona:**
Consulta la bandera global del pedal. Si está activa, libera la sección crítica y termina el callback, impidiendo que una pulsación sostenida del pedal provoque asentados automáticos en paralelo.

**Pseudocódigo:**

```text
si el pedal está abajo:
    liberar sección crítica
    salir
```

**Relaciones:**

* Usa <a href="#cid-08-10">CID-08-10</a>.
* Forma parte de <a href="#cid-08-32">CID-08-32</a>.

---

### <a id="cid-08-35"></a>CID-08-35

**Qué hace:**
Evita trabajo innecesario cuando no existen piezas pendientes en la línea viva.

**Cómo funciona:**
Consulta el tamaño actual de la bitácora viva. Si es cero, libera el bloqueo y sale del callback, porque no hay nada susceptible de asentarse.

**Pseudocódigo:**

```text
si no hay piezas pendientes:
    liberar sección crítica
    salir
```

**Relaciones:**

* Usa la bitácora global de <a href="#cid-08-09">CID-08-09</a>.
* Forma parte de <a href="#cid-08-32">CID-08-32</a>.

---

### <a id="cid-08-36"></a>CID-08-36

**Qué hace:**
Calcula el tiempo de inactividad real desde la última actividad CID registrada.

**Cómo funciona:**
Obtiene el tick actual con `GetTickCount64` y resta el último tick de actividad, protegiéndose ante cualquier caso degenerado donde el valor actual no sea mayor. El resultado representa la inactividad acumulada antes de decidir si debe asentarse.

**Pseudocódigo:**

```text
obtener tick actual
si tick actual >= último tick:
    delta = diferencia
si no:
    delta = 0
```

**Relaciones:**

* Usa <a href="#cid-08-13">CID-08-13</a>.
* Forma parte de <a href="#cid-08-32">CID-08-32</a>.
* Precede a <a href="#cid-08-37">CID-08-37</a>.

---

### <a id="cid-08-37"></a>CID-08-37

**Qué hace:**
Dispara el asentado automático cuando la inactividad acumulada supera el umbral dinámico actual.

**Cómo funciona:**
Compara el delta de inactividad con `g_auto_ms`. Si el delta es suficiente, llama a `Asentar_NoLock` y actualiza `g_ultimo_tick` con el momento actual para reiniciar la referencia temporal tras el asentado.

**Pseudocódigo:**

```text
si inactividad >= auto-asentado actual:
    asentar línea viva
    actualizar último tick
```

**Relaciones:**

* Usa <a href="#cid-08-11">CID-08-11</a>, <a href="#cid-08-13">CID-08-13</a> y <a href="#cid-08-23">CID-08-23</a>.
* Forma parte de <a href="#cid-08-32">CID-08-32</a>.

---

### <a id="cid-08-38"></a>CID-08-38

**Qué hace:**
Inicializa el gestor de asentado, su temporización periódica y su estado base interno.

**Cómo funciona:**
Asegura primero la existencia de la sección crítica, entra en ella, conecta la bitácora, normaliza el tiempo inicial de auto-asentado y reinicia el resto del estado global: pedal, ticks, último inyectado, contexto de mayúsculas y promedio base. Luego crea la cola de temporizadores si no existe, intenta crear el temporizador periódico, publica el estado visual inicial si todo ha ido bien, libera el bloqueo y finalmente informa del resultado devolviendo éxito o fracaso.

**Pseudocódigo:**

```text
inicializar sección crítica si hace falta
entrar en sección crítica

conectar bitácora
normalizar auto-asentado inicial
reiniciar estado interno del gestor

crear cola de temporizadores si hace falta
crear temporizador periódico si hace falta

si todo fue bien y hay bitácora:
    refrescar superposición visual inicial

salir de sección crítica

si falló la infraestructura temporal:
    escribir error
    devolver falso

escribir log de arranque correcto
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-39">CID-08-39</a> a <a href="#cid-08-45">CID-08-45</a>.
* Es una de las funciones públicas declaradas por <a href="#cid-08-01">CID-08-01</a>.
* Prepara el estado utilizado por casi todo el resto de <a href="#cid-08">CID-08</a>.

---

### <a id="cid-08-39"></a>CID-08-39

**Qué hace:**
Inicializa la sección crítica global del gestor la primera vez que este se arranca.

**Cómo funciona:**
Comprueba la bandera `g_cs_iniciado`. Si todavía es falsa, llama a `InitializeCriticalSection` sobre el recurso global y marca la bandera como verdadera. Así evita reinicializaciones repetidas del mismo mecanismo de sincronización.

**Pseudocódigo:**

```text
si la sección crítica no está iniciada:
    inicializar sección crítica
    marcarla como iniciada
```

**Relaciones:**

* Usa <a href="#cid-08-08">CID-08-08</a>.
* Forma parte de <a href="#cid-08-38">CID-08-38</a>.
* Se complementa con la liberación de <a href="#cid-08-49">CID-08-49</a>.

---

### <a id="cid-08-40"></a>CID-08-40

**Qué hace:**
Conecta la bitácora activa y restablece el estado temporal, contextual y adaptativo del gestor.

**Cómo funciona:**
Guarda el puntero a la bitácora, limita el tiempo inicial de auto-asentado al rango permitido, resetea el estado del pedal, fija los ticks de referencia al tiempo actual, borra el último texto inyectado, reactiva el contexto de mayúscula inicial y calcula un promedio inicial coherente con el auto-asentado configurado.

**Pseudocódigo:**

```text
guardar bitácora conectada
limitar auto-asentado inicial
poner pedal como no pulsado

obtener tick actual
guardar tick como última actividad y ritmo previo

vaciar último texto inyectado
activar contexto de mayúscula inicial

calcular promedio inicial a partir del auto-asentado
```

**Relaciones:**

* Usa <a href="#cid-08-04">CID-08-04</a>, <a href="#cid-08-09">CID-08-09</a>, <a href="#cid-08-10">CID-08-10</a>, <a href="#cid-08-11">CID-08-11</a>, <a href="#cid-08-13">CID-08-13</a>, <a href="#cid-08-14">CID-08-14</a>, <a href="#cid-08-15">CID-08-15</a> y <a href="#cid-08-16">CID-08-16</a>.
* Forma parte de <a href="#cid-08-38">CID-08-38</a>.

---

### <a id="cid-08-41"></a>CID-08-41

**Qué hace:**
Crea la cola de temporizadores del gestor si todavía no existe.

**Cómo funciona:**
Comprueba si `g_timerQueue` es nulo. Si lo es, llama a `CreateTimerQueue` y guarda el resultado. Después deriva una bandera de éxito a partir de que la cola haya quedado realmente creada.

**Pseudocódigo:**

```text
si no existe cola de temporizadores:
    crearla
ok = la cola existe
```

**Relaciones:**

* Usa el estado declarado en <a href="#cid-08-12">CID-08-12</a>.
* Forma parte de <a href="#cid-08-38">CID-08-38</a>.
* Precede a <a href="#cid-08-42">CID-08-42</a>.

---

### <a id="cid-08-42"></a>CID-08-42

**Qué hace:**
Crea el temporizador periódico del gestor solo cuando existe cola válida y aún no había uno activo.

**Cómo funciona:**
Comprueba que la infraestructura siga en estado correcto y que `g_timer` siga vacío. Si ambas condiciones se cumplen, llama a `CreateTimerQueueTimer` con el callback del gestor y el periodo fijo `CHEQUEO_MS`, dejando programado el chequeo periódico de inactividad.

**Pseudocódigo:**

```text
si la cola es válida y no hay temporizador activo:
    crear temporizador periódico con el callback del gestor
```

**Relaciones:**

* Usa <a href="#cid-08-12">CID-08-12</a> y registra <a href="#cid-08-32">CID-08-32</a> como callback.
* Forma parte de <a href="#cid-08-38">CID-08-38</a>.

---

### <a id="cid-08-43"></a>CID-08-43

**Qué hace:**
Publica el estado visual inicial del gestor si el arranque fue correcto y existe una bitácora conectada.

**Cómo funciona:**
Comprueba la bandera local de éxito y la existencia de bitácora. Si ambas condiciones se cumplen, llama al helper de refresco visual para que la superposición arranque sincronizada con el estado actual de la bitácora.

**Pseudocódigo:**

```text
si el arranque va bien y hay bitácora:
    refrescar superposición visual
```

**Relaciones:**

* Usa <a href="#cid-08-07">CID-08-07</a> y <a href="#cid-08-09">CID-08-09</a>.
* Forma parte de <a href="#cid-08-38">CID-08-38</a>.

---

### <a id="cid-08-44"></a>CID-08-44

**Qué hace:**
Informa por depuración del fallo cuando no pudo iniciarse la infraestructura temporal del gestor.

**Cómo funciona:**
Tras salir de la sección crítica, comprueba la bandera local `ok`. Si es falsa, envía un mensaje de error al sistema de log y devuelve `false`, indicando que el gestor no pudo arrancar correctamente.

**Pseudocódigo:**

```text
si no se pudo iniciar la infraestructura temporal:
    escribir error
    devolver falso
```

**Relaciones:**

* Usa <a href="#cid-08-06">CID-08-06</a>.
* Forma parte de <a href="#cid-08-38">CID-08-38</a>.

---

### <a id="cid-08-45"></a>CID-08-45

**Qué hace:**
Registra el arranque correcto del gestor e informa del valor inicial de auto-asentado configurado.

**Cómo funciona:**
Construye un mensaje con el tiempo actual de auto-asentado y lo envía al log. Después devuelve `true` para señalar que la inicialización ha concluido con éxito.

**Pseudocódigo:**

```text
escribir log con auto-asentado inicial
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-08-06">CID-08-06</a> y <a href="#cid-08-11">CID-08-11</a>.
* Forma parte de <a href="#cid-08-38">CID-08-38</a>.

---

### <a id="cid-08-46"></a>CID-08-46

**Qué hace:**
Detiene el gestor de asentado liberando su temporizador, su cola temporal y el mecanismo global de sincronización.

**Cómo funciona:**
Comprueba si existe un temporizador activo y lo elimina de la cola. Después destruye la propia cola de temporizadores si existe y, finalmente, borra la sección crítica global si había sido inicializada. Al terminar, emite una traza de apagado.

**Pseudocódigo:**

```text
si existe temporizador activo:
    eliminarlo

si existe cola de temporizadores:
    eliminarla

si la sección crítica estaba iniciada:
    borrarla

escribir log de apagado
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-47">CID-08-47</a> a <a href="#cid-08-49">CID-08-49</a>.
* Es la contraparte de arranque de <a href="#cid-08-38">CID-08-38</a>.
* Es una de las funciones públicas declaradas por <a href="#cid-08-01">CID-08-01</a>.

---

### <a id="cid-08-47"></a>CID-08-47

**Qué hace:**
Elimina el temporizador periódico si todavía existe dentro de la cola del gestor.

**Cómo funciona:**
Comprueba simultáneamente que existan tanto `g_timer` como `g_timerQueue`. Si ambos recursos siguen activos, llama a `DeleteTimerQueueTimer` con espera síncrona y luego borra el handle global del temporizador.

**Pseudocódigo:**

```text
si existen temporizador y cola:
    eliminar temporizador de la cola
    poner handle de temporizador a nulo
```

**Relaciones:**

* Usa los recursos declarados en <a href="#cid-08-12">CID-08-12</a>.
* Forma parte de <a href="#cid-08-46">CID-08-46</a>.

---

### <a id="cid-08-48"></a>CID-08-48

**Qué hace:**
Elimina la cola de temporizadores completa al apagar el gestor.

**Cómo funciona:**
Comprueba si `g_timerQueue` sigue existiendo. Si existe, llama a `DeleteTimerQueueEx` con espera síncrona y después anula el handle global de la cola.

**Pseudocódigo:**

```text
si existe cola de temporizadores:
    eliminar cola
    poner handle de cola a nulo
```

**Relaciones:**

* Usa el estado de <a href="#cid-08-12">CID-08-12</a>.
* Forma parte de <a href="#cid-08-46">CID-08-46</a>.

---

### <a id="cid-08-49"></a>CID-08-49

**Qué hace:**
Libera la sección crítica global del gestor si había sido inicializada.

**Cómo funciona:**
Comprueba la bandera de inicialización. Si está activa, llama a `DeleteCriticalSection` y después marca la bandera como falsa. Finalmente registra por depuración que el gestor se ha detenido.

**Pseudocódigo:**

```text
si la sección crítica estaba iniciada:
    borrar sección crítica
    marcarla como no iniciada

escribir log de gestor detenido
```

**Relaciones:**

* Usa <a href="#cid-08-08">CID-08-08</a> y <a href="#cid-08-06">CID-08-06</a>.
* Forma parte de <a href="#cid-08-46">CID-08-46</a>.
* Complementa a <a href="#cid-08-39">CID-08-39</a>.

---

### <a id="cid-08-50"></a>CID-08-50

**Qué hace:**
Registra una actividad CID real y entrena el auto-asentado dinámico según el ritmo observado.

**Cómo funciona:**
Si el gestor todavía no tiene sincronización inicializada, sale sin actuar. En caso contrario entra en la sección crítica, mide el delta respecto al tick anterior de ritmo, actualiza el último tick global de actividad y, si el pedal no está pulsado y el delta es válido, recalcula el promedio rítmico, construye un nuevo objetivo de auto-asentado y lo aplica. Después actualiza la referencia del ritmo y libera el bloqueo.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
medir delta desde el último ritmo
actualizar último tick global

si el pedal no está abajo:
    si delta es válido:
        actualizar promedio rítmico
        calcular objetivo de auto-asentado
        limitar objetivo
        ajustar auto-asentado actual

actualizar tick anterior del ritmo
salir de sección crítica
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-51">CID-08-51</a> y <a href="#cid-08-52">CID-08-52</a>.
* Usa la sincronización de <a href="#cid-08-08">CID-08-08</a>.
* Es una de las funciones públicas declaradas por <a href="#cid-08-01">CID-08-01</a>.

---

### <a id="cid-08-51"></a>CID-08-51

**Qué hace:**
Calcula el delta desde el último punto de ritmo y actualiza el tick de actividad global.

**Cómo funciona:**
Obtiene el tiempo actual, calcula la diferencia respecto a `g_tick_anterior_ritmo` protegiéndose ante casos degenerados y guarda el momento actual como nuevo valor de `g_ultimo_tick`. Así separa el seguimiento de inactividad global del seguimiento específico del ritmo de tecleo.

**Pseudocódigo:**

```text
obtener tick actual
si tick actual >= tick anterior del ritmo:
    delta = diferencia
si no:
    delta = 0

guardar tick actual como última actividad global
```

**Relaciones:**

* Usa <a href="#cid-08-13">CID-08-13</a> y <a href="#cid-08-16">CID-08-16</a>.
* Forma parte de <a href="#cid-08-50">CID-08-50</a>.
* Precede a <a href="#cid-08-52">CID-08-52</a>.

---

### <a id="cid-08-52"></a>CID-08-52

**Qué hace:**
Entrena el promedio rítmico solo cuando el pedal no está abajo y el delta temporal se considera válido.

**Cómo funciona:**
Si el pedal está suelto, valida el delta con el helper correspondiente. Cuando el delta es útil, actualiza el promedio mediante suavizado exponencial, calcula un objetivo de auto-asentado a partir del promedio multiplicado por un factor más un margen fijo, lo limita al rango global y delega el ajuste progresivo real del valor actual.

**Pseudocódigo:**

```text
si el pedal no está abajo:
    si delta es válido:
        recalcular promedio con suavizado exponencial
        objetivo = promedio * factor + margen
        limitar objetivo al rango global
        ajustar auto-asentado hacia el objetivo
```

**Relaciones:**

* Usa <a href="#cid-08-10">CID-08-10</a>, <a href="#cid-08-16">CID-08-16</a>, <a href="#cid-08-17">CID-08-17</a>, <a href="#cid-08-04">CID-08-04</a> y <a href="#cid-08-18">CID-08-18</a>.
* Forma parte de <a href="#cid-08-50">CID-08-50</a>.

---

### <a id="cid-08-53"></a>CID-08-53

**Qué hace:**
Procesa la pulsación o liberación del pedal CID y ejecuta asentado manual cuando procede.

**Cómo funciona:**
Si la sincronización aún no está iniciada, no hace nada. En caso contrario entra en la sección crítica, actualiza el último tick global y distingue dos casos: pulsación o liberación. Al pulsar, bloquea el auto-asentado y reinicia la referencia temporal del ritmo. Al soltar, reabre el ritmo normal y, si había contenido pendiente en la bitácora, ejecuta un asentado manual inmediato.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
actualizar último tick global

si el evento es pulsación:
    bloquear auto-asentado
    reiniciar referencia del ritmo
    salir

si el evento es liberación:
    desbloquear auto-asentado
    reiniciar referencia del ritmo
    si hay contenido pendiente:
        asentar manualmente

salir de sección crítica
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-54">CID-08-54</a> y <a href="#cid-08-55">CID-08-55</a>.
* Usa la sincronización de <a href="#cid-08-08">CID-08-08</a>.
* Es una de las funciones públicas declaradas por <a href="#cid-08-01">CID-08-01</a>.

---

### <a id="cid-08-54"></a>CID-08-54

**Qué hace:**
Al pulsar el pedal, bloquea el auto-asentado y reinicia la referencia temporal del ritmo.

**Cómo funciona:**
Marca `g_pedal_abajo` como verdadero, guarda el tiempo actual como nuevo `g_tick_anterior_ritmo`, libera la sección crítica y termina inmediatamente. Esto impide que se entrene el ritmo o se dispare el auto-asentado durante la pulsación mantenida.

**Pseudocódigo:**

```text
marcar pedal como abajo
actualizar tick anterior del ritmo
liberar sección crítica
salir
```

**Relaciones:**

* Usa <a href="#cid-08-10">CID-08-10</a> y <a href="#cid-08-16">CID-08-16</a>.
* Forma parte de <a href="#cid-08-53">CID-08-53</a>.

---

### <a id="cid-08-55"></a>CID-08-55

**Qué hace:**
Al soltar el pedal, reabre el ritmo normal y asienta manualmente si había contenido pendiente.

**Cómo funciona:**
Marca `g_pedal_abajo` como falso, reinicia la referencia temporal del ritmo con el tiempo actual y, si existe bitácora y esta contiene piezas, llama a `Asentar_NoLock`. Después libera la sección crítica.

**Pseudocódigo:**

```text
marcar pedal como arriba
actualizar tick anterior del ritmo

si hay bitácora y tiene contenido pendiente:
    asentar manualmente

liberar sección crítica
```

**Relaciones:**

* Usa <a href="#cid-08-10">CID-08-10</a>, <a href="#cid-08-09">CID-08-09</a>, <a href="#cid-08-16">CID-08-16</a> y <a href="#cid-08-23">CID-08-23</a>.
* Forma parte de <a href="#cid-08-53">CID-08-53</a>.

---

### <a id="cid-08-56"></a>CID-08-56

**Qué hace:**
Borra el último texto asentado inyectando retrocesos y reabre su línea visual en la bitácora.

**Cómo funciona:**
Si el gestor aún no está inicializado, no hace nada. En caso contrario entra en la sección crítica, comprueba si existe un último texto inyectado y, si lo hay, calcula cuántos caracteres debe borrar, ejecuta los backspaces como inyección propia, reabre la última línea asentada en la bitácora, refresca la UI y marca visualmente el borrado antes de limpiar el registro del último texto. Finalmente libera el bloqueo.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica

si no hay último texto inyectado:
    salir

calcular cantidad de caracteres a borrar
inyectar retrocesos propios
reabrir última línea asentada si hay bitácora
refrescar UI
mostrar estado de borrado
limpiar registro del último texto

salir de sección crítica
```

**Relaciones:**

* Contiene internamente <a href="#cid-08-57">CID-08-57</a> a <a href="#cid-08-60">CID-08-60</a>.
* Usa la sincronización de <a href="#cid-08-08">CID-08-08</a>.
* Es una de las funciones públicas declaradas por <a href="#cid-08-01">CID-08-01</a>.

---

### <a id="cid-08-57"></a>CID-08-57

**Qué hace:**
Sale sin actuar cuando no existe un texto asentado reciente que pueda borrarse.

**Cómo funciona:**
Comprueba si `g_ultimo_inyectado` está vacío. Si lo está, libera la sección crítica y retorna, ya que no hay referencia fiable para saber qué debe deshacerse.

**Pseudocódigo:**

```text
si el último texto inyectado está vacío:
    liberar sección crítica
    salir
```

**Relaciones:**

* Usa <a href="#cid-08-14">CID-08-14</a>.
* Forma parte de <a href="#cid-08-56">CID-08-56</a>.

---

### <a id="cid-08-58"></a>CID-08-58

**Qué hace:**
Borra físicamente del sistema el último asentado usando retrocesos inyectados.

**Cómo funciona:**
Calcula cuántos caracteres tiene el último texto inyectado, activa temporalmente la marca de inyección propia, llama al helper que genera los backspaces físicos y después desactiva esa marca.

**Pseudocódigo:**

```text
calcular longitud del último texto inyectado
marcar inyección como activa
inyectar backspaces necesarios
desmarcar inyección como activa
```

**Relaciones:**

* Usa <a href="#cid-08-14">CID-08-14</a> y <a href="#cid-08-21">CID-08-21</a>.
* Usa funcionalidad de <code>inyeccion_texto.h</code>.
* Forma parte de <a href="#cid-08-56">CID-08-56</a>.

---

### <a id="cid-08-59"></a>CID-08-59

**Qué hace:**
Reabre visual y lógicamente la última línea asentada si existe una bitácora conectada.

**Cómo funciona:**
Comprueba si hay bitácora. Si la hay, llama a `ReabrirUltimaLineaAsentada` para devolver esa línea al estado editable y luego refresca la superposición visual para que la UI refleje el cambio.

**Pseudocódigo:**

```text
si hay bitácora:
    reabrir última línea asentada
    refrescar superposición visual
```

**Relaciones:**

* Usa <a href="#cid-08-09">CID-08-09</a> y <a href="#cid-08-07">CID-08-07</a>.
* Forma parte de <a href="#cid-08-56">CID-08-56</a>.

---

### <a id="cid-08-60"></a>CID-08-60

**Qué hace:**
Actualiza la superposición tras el borrado y limpia el registro del último texto ya eliminado.

**Cómo funciona:**
Publica el literal `(borrado)` como último asentado visible y vacía la cadena que almacenaba el último texto inyectado. Con ello se deja constancia visual del deshacer y se evita que un mismo asentado pueda borrarse repetidamente sin haberse vuelto a generar.

**Pseudocódigo:**

```text
mostrar "(borrado)" en la superposición
vaciar registro del último texto inyectado
```

**Relaciones:**

* Usa funcionalidad de superposición visual.
* Limpia el estado definido en <a href="#cid-08-14">CID-08-14</a>.
* Forma parte de <a href="#cid-08-56">CID-08-56</a>.

## CID-09

La referencia <a href="#cid-09">CID-09</a> corresponde al archivo <code>gestor_asentado.h</code>. Este archivo actúa como interfaz pública del gestor de asentado CID. Su responsabilidad principal es exponer al resto del motor las funciones necesarias para iniciar, detener y utilizar el subsistema encargado de asentar texto, entrenar el auto-asentado dinámico, procesar el pedal CID y borrar el último asentado.

Dentro de <a href="#cid-09">CID-09</a> también se define el contrato mínimo entre el gestor de asentado y el resto de módulos del sistema. Por eso aquí no aparece la lógica interna del temporizador, la sincronización o la inyección de texto, sino únicamente las declaraciones necesarias para que otros archivos puedan invocar esas capacidades sin conocer su implementación. En términos prácticos, <a href="#cid-09">CID-09</a> es la puerta pública de entrada al subsistema de asentado.

### Índice interno de bloques

* <a href="#cid-09-01">CID-09-01</a>
* <a href="#cid-09-02">CID-09-02</a>
* <a href="#cid-09-03">CID-09-03</a>
* <a href="#cid-09-04">CID-09-04</a>
* <a href="#cid-09-05">CID-09-05</a>
* <a href="#cid-09-06">CID-09-06</a>
* <a href="#cid-09-07">CID-09-07</a>

---

### <a id="cid-09-01"></a>CID-09-01

**Qué hace:**
Evita inclusiones múltiples de la interfaz pública del gestor de asentado CID.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Con ello se previenen redefiniciones de declaraciones y conflictos derivados de inclusiones repetidas.

**Pseudocódigo:**

```text
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-09">CID-09</a>.
* Asegura que <a href="#cid-09-03">CID-09-03</a> a <a href="#cid-09-07">CID-09-07</a> no se dupliquen al incluir la cabecera desde varios puntos del proyecto.

---

### <a id="cid-09-02"></a>CID-09-02

**Qué hace:**
Incluye los tipos base de Windows usados por la interfaz del gestor.

**Cómo funciona:**
Incorpora `<windows.h>` para garantizar disponibilidad de tipos y definiciones del entorno Win32 que pueden ser necesarias en la firma pública o en módulos consumidores de esta cabecera.

**Pseudocódigo:**

```text
incluir tipos base de Windows
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-09">CID-09</a>.
* Da soporte indirecto a la integración de esta cabecera con la implementación correspondiente en <code>gestor_asentado.cpp</code>.

---

### <a id="cid-09-03"></a>CID-09-03

**Qué hace:**
Declara por adelantado la clase `BitacoraCID` usada por la interfaz pública del gestor.

**Cómo funciona:**
Realiza una forward declaration de `BitacoraCID` sin incluir su cabecera completa. Esto permite declarar funciones que reciben punteros a esa clase sin forzar una dependencia más pesada en este punto.

**Pseudocódigo:**

```text
declarar en adelantado la clase BitacoraCID
```

**Relaciones:**

* Prepara la firma expuesta en <a href="#cid-09-04">CID-09-04</a>.
* Reduce el acoplamiento directo entre esta interfaz y la definición completa de la bitácora.

---

### <a id="cid-09-04"></a>CID-09-04

**Qué hace:**
Declara el arranque y la detención del gestor de asentado con auto-asentado configurable.

**Cómo funciona:**
Expone dos funciones públicas: `IniciarGestorAsentado`, que recibe el tiempo base de auto-asentado y una bitácora conectada, y `DetenerGestorAsentado`, que apaga el subsistema. Estas declaraciones permiten controlar el ciclo de vida completo del gestor desde el exterior.

**Pseudocódigo:**

```text
declarar función para iniciar gestor con auto-asentado y bitácora
declarar función para detener gestor
```

**Relaciones:**

* Usa la declaración adelantada de <a href="#cid-09-03">CID-09-03</a>.
* Se implementa en <a href="#cid-08-38">CID-08-38</a> y <a href="#cid-08-46">CID-08-46</a>.
* Es consumido por el punto de entrada del motor durante el arranque y cierre del sistema.

---

### <a id="cid-09-05"></a>CID-09-05

**Qué hace:**
Declara la notificación de actividad CID usada para entrenar el auto-asentado inteligente.

**Cómo funciona:**
Expone una función pública que el resto del sistema puede invocar cada vez que detecta actividad CID real. Esa señal permite que el gestor observe el ritmo de uso y adapte progresivamente el tiempo de auto-asentado.

**Pseudocódigo:**

```text
declarar función para notificar actividad CID real
```

**Relaciones:**

* Se implementa en <a href="#cid-08-50">CID-08-50</a>.
* Forma parte de la interfaz pública del gestor expuesta por <a href="#cid-09">CID-09</a>.

---

### <a id="cid-09-06"></a>CID-09-06

**Qué hace:**
Declara el procesamiento del pedal CID KEY tanto para pulsación como para liberación.

**Cómo funciona:**
Expone una función pública que recibe un booleano indicando si el pedal está siendo pulsado o soltado. Esa llamada permite al gestor bloquear temporalmente el auto-asentado durante la pulsación y ejecutar asentado manual al liberar cuando corresponda.

**Pseudocódigo:**

```text
declarar función para procesar estado presionado o liberado del pedal CID
```

**Relaciones:**

* Se implementa en <a href="#cid-08-53">CID-08-53</a>.
* Forma parte del contrato público entre el detector de teclas CID y el gestor de asentado.

---

### <a id="cid-09-07"></a>CID-09-07

**Qué hace:**
Declara el borrado del último asentado recientemente inyectado por el sistema CID.

**Cómo funciona:**
Expone una función pública sin parámetros que permite al resto del motor solicitar el deshacer del último texto asentado. La implementación asociada se encarga de borrar físicamente el texto, reabrir la línea y actualizar la representación visual.

**Pseudocódigo:**

```text
declarar función para borrar el último asentado
```

**Relaciones:**

* Se implementa en <a href="#cid-08-56">CID-08-56</a>.
* Completa junto a <a href="#cid-09-04">CID-09-04</a>, <a href="#cid-09-05">CID-09-05</a> y <a href="#cid-09-06">CID-09-06</a> la interfaz pública del gestor de asentado.


## CID-10

La referencia <a href="#cid-10">CID-10</a> corresponde al archivo <code>diccionario_cid.cpp</code>. Este archivo implementa la lógica del diccionario CID encargada de cargar entradas desde archivo, validar su formato, normalizar los acordes a una clave canónica oficial y exponer búsquedas sobre el mapa ya cargado.

Dentro de <a href="#cid-10">CID-10</a> también se concentra la normalización textual de acordes escritos con nombres CID, la conversión de codificaciones a Unicode, la limpieza de espacios y BOM, la validación de tokens de tecla y la detección de errores estructurales del archivo fuente. Por eso aquí no solo se lee un archivo, sino que se protege la consistencia interna del diccionario antes de aceptar cualquier entrada. En términos prácticos, <a href="#cid-10">CID-10</a> es la pieza que transforma el contenido bruto de `cid0.cid` en un mapa fiable de acordes canónicos a resultados lingüísticos.

### Índice interno de bloques

* <a href="#cid-10-01">CID-10-01</a>
* <a href="#cid-10-02">CID-10-02</a>
* <a href="#cid-10-03">CID-10-03</a>
* <a href="#cid-10-04">CID-10-04</a>
* <a href="#cid-10-05">CID-10-05</a>
* <a href="#cid-10-06">CID-10-06</a>
* <a href="#cid-10-07">CID-10-07</a>
* <a href="#cid-10-08">CID-10-08</a>
* <a href="#cid-10-09">CID-10-09</a>
* <a href="#cid-10-10">CID-10-10</a>
* <a href="#cid-10-11">CID-10-11</a>
* <a href="#cid-10-12">CID-10-12</a>
* <a href="#cid-10-13">CID-10-13</a>
* <a href="#cid-10-14">CID-10-14</a>
* <a href="#cid-10-15">CID-10-15</a>
* <a href="#cid-10-16">CID-10-16</a>
* <a href="#cid-10-17">CID-10-17</a>
* <a href="#cid-10-18">CID-10-18</a>
* <a href="#cid-10-19">CID-10-19</a>
* <a href="#cid-10-20">CID-10-20</a>
* <a href="#cid-10-21">CID-10-21</a>
* <a href="#cid-10-22">CID-10-22</a>
* <a href="#cid-10-23">CID-10-23</a>
* <a href="#cid-10-24">CID-10-24</a>
* <a href="#cid-10-25">CID-10-25</a>
* <a href="#cid-10-26">CID-10-26</a>
* <a href="#cid-10-27">CID-10-27</a>
* <a href="#cid-10-28">CID-10-28</a>
* <a href="#cid-10-29">CID-10-29</a>
* <a href="#cid-10-30">CID-10-30</a>
* <a href="#cid-10-31">CID-10-31</a>
* <a href="#cid-10-32">CID-10-32</a>
* <a href="#cid-10-33">CID-10-33</a>
* <a href="#cid-10-34">CID-10-34</a>
* <a href="#cid-10-35">CID-10-35</a>
* <a href="#cid-10-36">CID-10-36</a>

---

### <a id="cid-10-01"></a>CID-10-01

**Qué hace:**
Incluye la implementación del diccionario CID a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `diccionario_cid.h`, que declara la clase `DiccionarioCID`, la estructura de entrada del diccionario y las firmas públicas usadas por el resto del sistema. Gracias a esta inclusión, el archivo actual puede definir los métodos reales del subsistema.

**Pseudocódigo:**

```text
incluir interfaz pública del diccionario CID
habilitar definición de sus métodos
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-10">CID-10</a>.
* Da soporte directo a <a href="#cid-10-24">CID-10-24</a> y <a href="#cid-10-36">CID-10-36</a>.

---

### <a id="cid-10-02"></a>CID-10-02

**Qué hace:**
Incluye el mapa oficial de teclas CID usado para validar nombres y construir el orden canónico de los acordes.

**Cómo funciona:**
Este bloque conecta la implementación con `mapa_teclas_cid.h`, desde donde se obtienen funciones como `OrdenTeclaCID` y `NombreTeclaCID`. Estas utilidades permiten convertir tokens textuales en virtual keys válidas y reconstruir una clave de acorde normalizada según el orden oficial del sistema.

**Pseudocódigo:**

```text
incluir mapa oficial de teclas CID
habilitar validación y normalización de acordes
```

**Relaciones:**

* Da soporte directo a <a href="#cid-10-22">CID-10-22</a> y <a href="#cid-10-23">CID-10-23</a>.
* Enlaza con el módulo <code>mapa_teclas_cid.h</code>.

---

### <a id="cid-10-03"></a>CID-10-03

**Qué hace:**
Incluye cabeceras necesarias para lectura de archivos, parsing, contenedores, ordenación y utilidades Win32.

**Cómo funciona:**
Este bloque habilita el uso de `std::ifstream`, `std::vector`, `std::sort` y la API Win32 requerida para convertir texto multibyte a Unicode. No contiene lógica ejecutable, pero define el entorno necesario para compilar el resto del archivo.

**Pseudocódigo:**

```text
incluir soporte de archivos
incluir soporte de parsing
incluir contenedores
incluir ordenación
incluir utilidades de Windows
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-10">CID-10</a>.
* Da soporte indirecto a <a href="#cid-10-06">CID-10-06</a>, <a href="#cid-10-24">CID-10-24</a> y al resto de bloques con lógica de archivo o Unicode.

---

### <a id="cid-10-04"></a>CID-10-04

**Qué hace:**
Recorta espacios ASCII al inicio y al final de una cadena estrecha modificándola en sitio.

**Cómo funciona:**
Define un predicado local que reconoce espacio, tabulador, retorno de carro y salto de línea. Después elimina repetidamente esos caracteres desde el frente y desde el final de la cadena hasta dejar solo el contenido significativo.

**Pseudocódigo:**

```text
definir qué caracteres cuentan como espacio ASCII
mientras la cadena empiece por espacio:
    borrar primer carácter
mientras la cadena termine por espacio:
    borrar último carácter
```

**Relaciones:**

* Es usado por <a href="#cid-10-07">CID-10-07</a> y <a href="#cid-10-27">CID-10-27</a>.

---

### <a id="cid-10-05"></a>CID-10-05

**Qué hace:**
Recorta espacios Unicode típicos, BOM y NBSP al inicio y al final de una cadena ancha.

**Cómo funciona:**
Define un predicado que reconoce espacios comunes, tabuladores, saltos de línea, el BOM Unicode `0xFEFF` y el espacio duro `0x00A0`. Después elimina esos caracteres desde ambos extremos hasta limpiar la cadena.

**Pseudocódigo:**

```text
definir qué caracteres cuentan como espacio Unicode o marcador BOM
mientras la cadena empiece por uno de esos caracteres:
    borrar primer carácter
mientras la cadena termine por uno de esos caracteres:
    borrar último carácter
```

**Relaciones:**

* Es usado por <a href="#cid-10-08">CID-10-08</a>, <a href="#cid-10-10">CID-10-10</a> y <a href="#cid-10-31">CID-10-31</a>.

---

### <a id="cid-10-06"></a>CID-10-06

**Qué hace:**
Convierte una cadena multibyte a Unicode usando la code page indicada.

**Cómo funciona:**
Si la cadena de entrada está vacía devuelve una cadena ancha vacía. En caso contrario, primero pregunta a `MultiByteToWideChar` cuántos caracteres Unicode necesita, reserva ese tamaño y realiza una segunda llamada para rellenar el resultado final. Si el cálculo inicial falla, devuelve vacío.

**Pseudocódigo:**

```text
si la cadena está vacía:
    devolver vacío

preguntar tamaño necesario en Unicode
si el tamaño no es válido:
    devolver vacío

reservar cadena de salida
convertir contenido a Unicode
devolver resultado
```

**Relaciones:**

* Es usado por <a href="#cid-10-30">CID-10-30</a>.
* Depende de las utilidades Win32 incluidas en <a href="#cid-10-03">CID-10-03</a>.

---

### <a id="cid-10-07"></a>CID-10-07

**Qué hace:**
Separa una línea del diccionario en los tres campos esperados: acorde, resultado y número tildal.

**Cómo funciona:**
Busca la primera y la segunda barra vertical. Si alguna falta, la línea se considera inválida. Si ambas existen, extrae los tres fragmentos correspondientes, los recorta con `TrimInPlace` y devuelve `true`.

**Pseudocódigo:**

```text
buscar primera barra vertical
si no existe:
    devolver falso

buscar segunda barra vertical
si no existe:
    devolver falso

extraer campo acorde
extraer campo resultado
extraer campo número
recortar espacios de los tres campos
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-10-04">CID-10-04</a>.
* Es llamado desde <a href="#cid-10-29">CID-10-29</a>.

---

### <a id="cid-10-08"></a>CID-10-08

**Qué hace:**
Divide una cadena de nombres de teclas separados por signo más y devuelve las partes limpias.

**Cómo funciona:**
Vacía primero el vector de salida. Luego recorre la cadena buscando el siguiente `+`, extrae el fragmento entre posiciones, lo limpia con `TrimWideInPlace` y, si no queda vacío, lo añade al vector. Repite hasta agotar la cadena.

**Pseudocódigo:**

```text
vaciar vector de salida
empezar en el inicio de la cadena

mientras queden caracteres:
    buscar siguiente signo más
    extraer fragmento actual
    limpiar espacios del fragmento
    si no está vacío:
        añadirlo al vector
    si no hay más signos más:
        terminar
    avanzar al siguiente tramo
```

**Relaciones:**

* Usa <a href="#cid-10-05">CID-10-05</a>.
* Es llamada desde <a href="#cid-10-19">CID-10-19</a>.

---

### <a id="cid-10-09"></a>CID-10-09

**Qué hace:**
Comprueba si un carácter ancho es un dígito decimal ASCII.

**Cómo funciona:**
Evalúa si el carácter está comprendido entre `L'0'` y `L'9'`. Devuelve `true` solo en ese caso.

**Pseudocódigo:**

```text
devolver si el carácter está entre 0 y 9
```

**Relaciones:**

* Es usado por <a href="#cid-10-14">CID-10-14</a>.

---

### <a id="cid-10-10"></a>CID-10-10

**Qué hace:**
Convierte un token CID textual como `I3` o `D10` en su virtual key oficial del mapa fijo.

**Cómo funciona:**
Recibe el token, lo limpia y valida progresivamente su estructura: token no vacío, prefijo válido, presencia de número y rango permitido según familia. Si todo es correcto, resuelve la virtual key correspondiente y la devuelve por salida. Si algo falla, rellena un mensaje de error y devuelve `false`.

**Pseudocódigo:**

```text
copiar y limpiar token

validar que no esté vacío
validar prefijo I, C o D
validar que tenga parte numérica
parsear número
definir tablas fijas de equivalencia
resolver virtual key según familia y rango
guardar resultado
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-10-11">CID-10-11</a> a <a href="#cid-10-18">CID-10-18</a>.
* Es llamado desde <a href="#cid-10-20">CID-10-20</a>.

---

### <a id="cid-10-11"></a>CID-10-11

**Qué hace:**
Rechaza tokens vacíos después de la limpieza inicial.

**Cómo funciona:**
Comprueba si el token quedó vacío tras `TrimWideInPlace`. Si es así, escribe el error correspondiente y devuelve `false`.

**Pseudocódigo:**

```text
si el token está vacío:
    guardar error de token vacío
    devolver falso
```

**Relaciones:**

* Usa <a href="#cid-10-05">CID-10-05</a>.
* Forma parte de <a href="#cid-10-10">CID-10-10</a>.

---

### <a id="cid-10-12"></a>CID-10-12

**Qué hace:**
Normaliza y valida el prefijo de familia `I`, `C` o `D`.

**Cómo funciona:**
Toma el primer carácter del token, lo convierte a mayúscula si venía en minúscula ASCII y comprueba que pertenezca a una de las tres familias válidas. Si no pertenece, produce un error.

**Pseudocódigo:**

```text
leer primer carácter del token
si es minúscula ASCII:
    convertir a mayúscula

si no es I, C ni D:
    guardar error de prefijo inválido
    devolver falso
```

**Relaciones:**

* Forma parte de <a href="#cid-10-10">CID-10-10</a>.
* Precede a <a href="#cid-10-13">CID-10-13</a>.

---

### <a id="cid-10-13"></a>CID-10-13

**Qué hace:**
Rechaza tokens que no contienen parte numérica tras el prefijo.

**Cómo funciona:**
Comprueba si la longitud del token es menor que 2. Si lo es, significa que solo existe el prefijo y falta el número, por lo que se genera un error.

**Pseudocódigo:**

```text
si el token no tiene caracteres después del prefijo:
    guardar error de número ausente
    devolver falso
```

**Relaciones:**

* Forma parte de <a href="#cid-10-10">CID-10-10</a>.
* Precede a <a href="#cid-10-14">CID-10-14</a>.

---

### <a id="cid-10-14"></a>CID-10-14

**Qué hace:**
Parsea y valida el número de tecla dentro del token textual.

**Cómo funciona:**
Recorre todos los caracteres desde la posición posterior al prefijo. Si alguno no es un dígito decimal ASCII, produce error. Si todos lo son, construye el valor entero acumulando cada cifra.

**Pseudocódigo:**

```text
inicializar número a cero
para cada carácter después del prefijo:
    si no es dígito:
        guardar error de número inválido
        devolver falso
    actualizar número acumulado
```

**Relaciones:**

* Usa <a href="#cid-10-09">CID-10-09</a>.
* Forma parte de <a href="#cid-10-10">CID-10-10</a>.
* Precede a <a href="#cid-10-15">CID-10-15</a>.

---

### <a id="cid-10-15"></a>CID-10-15

**Qué hace:**
Define las tablas fijas que convierten nombres CID en virtual keys oficiales.

**Cómo funciona:**
Declara tres arrays estáticos: uno para la familia `I`, otro para `C` y otro para `D`. Cada posición del array representa el número textual de la tecla y contiene la virtual key Win32 correspondiente.

**Pseudocódigo:**

```text
definir tabla fija para familia I
definir tabla fija para familia C
definir tabla fija para familia D
inicializar vk a cero
```

**Relaciones:**

* Forma parte de <a href="#cid-10-10">CID-10-10</a>.
* Es utilizado por <a href="#cid-10-16">CID-10-16</a>, <a href="#cid-10-17">CID-10-17</a> y <a href="#cid-10-18">CID-10-18</a>.

---

### <a id="cid-10-16"></a>CID-10-16

**Qué hace:**
Resuelve y valida tokens de la familia `I` dentro del rango permitido.

**Cómo funciona:**
Comprueba que el número esté entre 1 y 10. Si no lo está, produce error. Si sí lo está, usa la tabla `VK_I` para obtener la virtual key correspondiente.

**Pseudocódigo:**

```text
si la familia es I:
    si el número no está entre 1 y 10:
        guardar error de rango
        devolver falso
    obtener vk desde tabla I
```

**Relaciones:**

* Usa las tablas declaradas en <a href="#cid-10-15">CID-10-15</a>.
* Forma parte de <a href="#cid-10-10">CID-10-10</a>.

---

### <a id="cid-10-17"></a>CID-10-17

**Qué hace:**
Resuelve y valida tokens de la familia `C` dentro del rango permitido.

**Cómo funciona:**
Comprueba que el número esté entre 1 y 6. Si el valor cae fuera del rango, produce error. Si es válido, usa la tabla `VK_C` para obtener la virtual key.

**Pseudocódigo:**

```text
si la familia es C:
    si el número no está entre 1 y 6:
        guardar error de rango
        devolver falso
    obtener vk desde tabla C
```

**Relaciones:**

* Usa las tablas declaradas en <a href="#cid-10-15">CID-10-15</a>.
* Forma parte de <a href="#cid-10-10">CID-10-10</a>.

---

### <a id="cid-10-18"></a>CID-10-18

**Qué hace:**
Resuelve y valida tokens de la familia `D` dentro del rango permitido.

**Cómo funciona:**
Al llegar a esta rama, la familia restante es `D`. Comprueba que el número esté entre 1 y 10. Si no cumple el rango, produce error; si lo cumple, usa la tabla `VK_D` para resolver la virtual key final.

**Pseudocódigo:**

```text
si la familia es D:
    si el número no está entre 1 y 10:
        guardar error de rango
        devolver falso
    obtener vk desde tabla D
guardar vk en salida
devolver verdadero
```

**Relaciones:**

* Usa las tablas declaradas en <a href="#cid-10-15">CID-10-15</a>.
* Forma parte de <a href="#cid-10-10">CID-10-10</a>.

---

### <a id="cid-10-19"></a>CID-10-19

**Qué hace:**
Normaliza un acorde textual a su forma canónica oficial basada en nombres del mapa CID.

**Cómo funciona:**
Separa primero el acorde en partes con `SplitPlus` y rechaza el caso vacío. Después convierte cada nombre textual en virtual key, detecta repeticiones, ordena las teclas con el criterio canónico del mapa y reconstruye la cadena final usando los nombres oficiales devueltos por `NombreTeclaCID`.

**Pseudocódigo:**

```text
dividir acorde en partes
si no hay partes:
    guardar error de acorde vacío
    devolver falso

convertir cada parte a virtual key
rechazar teclas duplicadas
ordenar teclas según orden canónico
reconstruir acorde canónico con nombres oficiales
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-10-20">CID-10-20</a> a <a href="#cid-10-23">CID-10-23</a>.
* Es llamado desde <a href="#cid-10-33">CID-10-33</a>.

---

### <a id="cid-10-20"></a>CID-10-20

**Qué hace:**
Convierte cada nombre de tecla del acorde en su virtual key oficial.

**Cómo funciona:**
Recorre todas las partes del acorde. Para cada una intenta parsearla con `ParsearTokenTeclaCID`. Si alguna falla, genera un error y detiene la normalización. Si tiene éxito, añade la virtual key al vector acumulado.

**Pseudocódigo:**

```text
para cada nombre de tecla:
    intentar parsearlo a virtual key
    si falla:
        guardar error de tecla desconocida
        devolver falso
    guardar virtual key
```

**Relaciones:**

* Usa <a href="#cid-10-10">CID-10-10</a>.
* Forma parte de <a href="#cid-10-19">CID-10-19</a>.

---

### <a id="cid-10-21"></a>CID-10-21

**Qué hace:**
Rechaza acordes con teclas duplicadas dentro de la misma combinación.

**Cómo funciona:**
Ordena el vector de virtual keys en orden numérico simple y luego recorre sus vecinos inmediatos. Si encuentra dos valores iguales consecutivos, concluye que el acorde contenía una tecla repetida y devuelve error.

**Pseudocódigo:**

```text
ordenar virtual keys
recorrer vecinos consecutivos
si dos vecinos son iguales:
    guardar error de tecla repetida
    devolver falso
```

**Relaciones:**

* Forma parte de <a href="#cid-10-19">CID-10-19</a>.
* Precede a <a href="#cid-10-22">CID-10-22</a>.

---

### <a id="cid-10-22"></a>CID-10-22

**Qué hace:**
Ordena las teclas del acorde según el orden canónico oficial del mapa CID.

**Cómo funciona:**
Vuelve a ordenar el vector de virtual keys, esta vez usando un comparador que consulta `OrdenTeclaCID`. De este modo, cualquier acorde válido queda representado siempre en la misma secuencia oficial, independientemente del orden en que se escribiera en el archivo.

**Pseudocódigo:**

```text
ordenar virtual keys según orden oficial CID
```

**Relaciones:**

* Usa `OrdenTeclaCID` del mapa incluido en <a href="#cid-10-02">CID-10-02</a>.
* Forma parte de <a href="#cid-10-19">CID-10-19</a>.
* Precede a <a href="#cid-10-23">CID-10-23</a>.

---

### <a id="cid-10-23"></a>CID-10-23

**Qué hace:**
Reconstruye la clave canónica final usando los nombres oficiales del mapa.

**Cómo funciona:**
Vacía la salida final y recorre las virtual keys ya ordenadas canónicamente. Para cada una obtiene su nombre oficial con `NombreTeclaCID`; si alguna no tiene nombre, produce error. Si todo es válido, concatena los nombres usando `+` como separador.

**Pseudocódigo:**

```text
vaciar acorde de salida
para cada virtual key ordenada:
    obtener nombre oficial
    si no existe:
        guardar error de inconsistencia del mapa
        devolver falso
    añadir separador si hace falta
    añadir nombre al acorde
devolver verdadero
```

**Relaciones:**

* Usa `NombreTeclaCID` del mapa incluido en <a href="#cid-10-02">CID-10-02</a>.
* Forma parte de <a href="#cid-10-19">CID-10-19</a>.

---

### <a id="cid-10-24"></a>CID-10-24

**Qué hace:**
Carga el diccionario CID desde archivo validando formato, codificación y unicidad de acordes.

**Cómo funciona:**
Limpia primero el mapa interno, intenta abrir el archivo y, si tiene éxito, lo recorre línea a línea. En cada línea útil elimina artefactos de formato, separa campos, convierte texto a Unicode, limpia espacios raros, parsea el número tildal, normaliza el acorde y comprueba que no esté duplicado. Si todo va bien, crea la entrada y la inserta en el mapa. Si algo falla en cualquier punto, devuelve `false` con un mensaje detallado.

**Pseudocódigo:**

```text
vaciar mapa interno
abrir archivo
si no se puede abrir:
    devolver error

recorrer archivo línea a línea
ignorar líneas irrelevantes
separar campos
convertir a Unicode
limpiar campos Unicode
parsear número tildal
normalizar acorde
rechazar duplicados
crear entrada
insertarla en el mapa

devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-10-25">CID-10-25</a> a <a href="#cid-10-35">CID-10-35</a>.
* Implementa un método declarado en <code>diccionario_cid.h</code>.
* Es consumido por el arranque del motor al cargar el archivo base del diccionario.

---

### <a id="cid-10-25"></a>CID-10-25

**Qué hace:**
Recorre el archivo línea a línea y procesa solo entradas útiles del diccionario.

**Cómo funciona:**
Usa `std::getline` dentro de un bucle. En cada iteración incrementa el contador de línea para poder reportar errores con referencia exacta. Todo el procesamiento posterior se aplica solo sobre la línea actual.

**Pseudocódigo:**

```text
mientras se pueda leer una línea:
    incrementar contador de línea
    procesar la línea actual
```

**Relaciones:**

* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Contiene el flujo donde viven <a href="#cid-10-26">CID-10-26</a> a <a href="#cid-10-35">CID-10-35</a>.

---

### <a id="cid-10-26"></a>CID-10-26

**Qué hace:**
Limpia el retorno de carro final conservado por lecturas CRLF.

**Cómo funciona:**
Comprueba si la línea no está vacía y si su último carácter es `'\r'`. Si ambas condiciones se cumplen, elimina ese carácter para dejar la línea normalizada antes de seguir procesándola.

**Pseudocódigo:**

```text
si la línea termina en retorno de carro:
    eliminar último carácter
```

**Relaciones:**

* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-27">CID-10-27</a>.

---

### <a id="cid-10-27"></a>CID-10-27

**Qué hace:**
Ignora líneas vacías tras la limpieza superficial.

**Cómo funciona:**
Copia la línea actual a una variable temporal, le recorta espacios ASCII y, si queda vacía, continúa con la siguiente iteración sin intentar separarla en campos.

**Pseudocódigo:**

```text
copiar línea a temporal
recortar espacios
si queda vacía:
    continuar con la siguiente línea
```

**Relaciones:**

* Usa <a href="#cid-10-04">CID-10-04</a>.
* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-28">CID-10-28</a>.

---

### <a id="cid-10-28"></a>CID-10-28

**Qué hace:**
Ignora comentarios de línea con prefijo almohadilla o doble barra.

**Cómo funciona:**
Comprueba primero si la línea limpia empieza por `#`. Después comprueba el caso de dos caracteres iniciales `/` y `/`. Si se da cualquiera de esos patrones, la línea se descarta y el bucle continúa.

**Pseudocódigo:**

```text
si la línea empieza por #:
    continuar
si la línea empieza por //:
    continuar
```

**Relaciones:**

* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-29">CID-10-29</a>.

---

### <a id="cid-10-29"></a>CID-10-29

**Qué hace:**
Separa los tres campos esperados de la línea actual del diccionario.

**Cómo funciona:**
Declara variables locales para acorde, resultado y número. Después llama a `SepararCampos`. Si esa llamada falla, construye un error con el número de línea y aborta la carga completa.

**Pseudocódigo:**

```text
declarar campos acorde, resultado y número
intentar separar campos
si falla:
    guardar error de formato inválido con número de línea
    devolver falso
```

**Relaciones:**

* Usa <a href="#cid-10-07">CID-10-07</a>.
* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-30">CID-10-30</a>.

---

### <a id="cid-10-30"></a>CID-10-30

**Qué hace:**
Convierte acorde, resultado y número a Unicode usando UTF-8 con fallback a CP1252.

**Cómo funciona:**
Intenta convertir cada campo con `CP_UTF8`. Si el resultado queda vacío pese a que el campo original no estaba vacío, reintenta con la code page 1252. Así tolera tanto archivos UTF-8 como ciertos archivos heredados en codificación occidental.

**Pseudocódigo:**

```text
convertir acorde a Unicode con UTF-8
convertir resultado a Unicode con UTF-8
convertir número a Unicode con UTF-8

si algún campo no vacío quedó vacío:
    reintentar ese campo con CP1252
```

**Relaciones:**

* Usa <a href="#cid-10-06">CID-10-06</a>.
* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-31">CID-10-31</a>.

---

### <a id="cid-10-31"></a>CID-10-31

**Qué hace:**
Limpia BOM y espacios raros de los tres campos ya convertidos a Unicode.

**Cómo funciona:**
Aplica `TrimWideInPlace` al acorde, al resultado y al número. De este modo elimina residuos como BOM, NBSP o saltos de línea que hayan sobrevivido a la lectura y a la conversión.

**Pseudocódigo:**

```text
limpiar acorde Unicode
limpiar resultado Unicode
limpiar número Unicode
```

**Relaciones:**

* Usa <a href="#cid-10-05">CID-10-05</a>.
* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-32">CID-10-32</a>.

---

### <a id="cid-10-32"></a>CID-10-32

**Qué hace:**
Parsea el número tildal y falla si el campo no es un entero válido.

**Cómo funciona:**
Inicializa el número a un valor inválido y llama a `std::stoi` dentro de un `try`. Si la conversión lanza una excepción, genera un mensaje de error con el número de línea y aborta la carga.

**Pseudocódigo:**

```text
inicializar número tildal
intentar convertir texto a entero
si falla:
    guardar error de número tildal inválido
    devolver falso
```

**Relaciones:**

* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-33">CID-10-33</a>.

---

### <a id="cid-10-33"></a>CID-10-33

**Qué hace:**
Normaliza el acorde textual a su clave canónica oficial para almacenarlo en el mapa.

**Cómo funciona:**
Declara variables para la clave de acorde y el posible error. Luego llama a `NormalizarAcordeDesdeNombres`. Si esa operación falla, compone un mensaje con el número de línea y el motivo concreto recibido y aborta la carga.

**Pseudocódigo:**

```text
declarar clave canónica y buffer de error
intentar normalizar acorde textual
si falla:
    guardar error con número de línea y detalle
    devolver falso
```

**Relaciones:**

* Usa <a href="#cid-10-19">CID-10-19</a>.
* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-34">CID-10-34</a>.

---

### <a id="cid-10-34"></a>CID-10-34

**Qué hace:**
Rechaza acordes duplicados ya presentes en el diccionario cargado.

**Cómo funciona:**
Consulta `m_map` con la clave canónica recién construida. Si la encuentra, genera un error que indica el acorde duplicado y la línea donde se detectó el conflicto.

**Pseudocódigo:**

```text
si el acorde canónico ya existe en el mapa:
    guardar error de acorde duplicado con número de línea
    devolver falso
```

**Relaciones:**

* Usa la clave producida en <a href="#cid-10-33">CID-10-33</a>.
* Forma parte de <a href="#cid-10-24">CID-10-24</a>.
* Precede a <a href="#cid-10-35">CID-10-35</a>.

---

### <a id="cid-10-35"></a>CID-10-35

**Qué hace:**
Construye la entrada final del diccionario y la inserta en el mapa por acorde canónico.

**Cómo funciona:**
Crea una instancia local de `EntradaDiccionarioCID`, copia en ella el resultado crudo y el número tildal ya validados y, finalmente, la inserta en `m_map` usando como clave el acorde canónico.

**Pseudocódigo:**

```text
crear entrada de diccionario
guardar resultado crudo
guardar número tildal
insertar entrada en el mapa con la clave canónica
```

**Relaciones:**

* Usa los datos preparados en <a href="#cid-10-32">CID-10-32</a> y <a href="#cid-10-33">CID-10-33</a>.
* Forma parte de <a href="#cid-10-24">CID-10-24</a>.

---

### <a id="cid-10-36"></a>CID-10-36

**Qué hace:**
Busca una entrada del diccionario por acorde ya normalizado y devuelve su contenido si existe.

**Cómo funciona:**
Consulta `m_map` con la clave recibida. Si no encuentra coincidencia, devuelve `false`. Si la encuentra, copia la entrada en el parámetro de salida y devuelve `true`.

**Pseudocódigo:**

```text
buscar acorde en el mapa
si no existe:
    devolver falso
copiar entrada encontrada a salida
devolver verdadero
```

**Relaciones:**

* Implementa un método declarado en <code>diccionario_cid.h</code>.
* Usa el mapa construido por <a href="#cid-10-24">CID-10-24</a>.


## CID-11

La referencia <a href="#cid-11">CID-11</a> corresponde al archivo <code>diccionario_cid.h</code>. Este archivo actúa como interfaz pública del diccionario CID. Su responsabilidad principal es definir la estructura de entrada que representa cada acorde cargado y exponer la clase encargada de cargar el diccionario desde archivo y consultar sus entradas mediante acordes ya normalizados.

Dentro de <a href="#cid-11">CID-11</a> también se fija el contrato mínimo entre el subsistema de diccionario y el resto del motor. Por eso aquí no aparece la lógica de parsing, normalización o validación del archivo, sino únicamente los tipos y métodos públicos necesarios para interactuar con el diccionario cargado. En términos prácticos, <a href="#cid-11">CID-11</a> es la puerta pública de acceso al almacenamiento de acordes canónicos y sus resultados lingüísticos asociados.

### Índice interno de bloques

* <a href="#cid-11-01">CID-11-01</a>
* <a href="#cid-11-02">CID-11-02</a>
* <a href="#cid-11-03">CID-11-03</a>
* <a href="#cid-11-04">CID-11-04</a>
* <a href="#cid-11-05">CID-11-05</a>
* <a href="#cid-11-06">CID-11-06</a>

---

### <a id="cid-11-01"></a>CID-11-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública del diccionario CID.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera debe procesarse una sola vez por unidad de traducción. Así se evitan redefiniciones de tipos y conflictos por inclusión repetida.

**Pseudocódigo:**

```text
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-11">CID-11</a>.
* Asegura que <a href="#cid-11-03">CID-11-03</a> a <a href="#cid-11-06">CID-11-06</a> no se dupliquen al incluir esta cabecera desde distintos módulos.

---

### <a id="cid-11-02"></a>CID-11-02

**Qué hace:**
Incluye los tipos de texto y mapa hash usados por la interfaz del diccionario.

**Cómo funciona:**
Incorpora `<string>` para disponer de `std::wstring` y `<unordered_map>` para poder declarar el contenedor hash interno del diccionario. No contiene lógica ejecutable, pero prepara las dependencias mínimas necesarias para compilar esta interfaz.

**Pseudocódigo:**

```text
incluir soporte de cadenas anchas
incluir soporte de mapa hash
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-11">CID-11</a>.
* Da soporte directo a <a href="#cid-11-03">CID-11-03</a> y <a href="#cid-11-06">CID-11-06</a>.

---

### <a id="cid-11-03"></a>CID-11-03

**Qué hace:**
Define la entrada pública del diccionario con resultado crudo y número tildal asociado.

**Cómo funciona:**
Declara la estructura `EntradaDiccionarioCID`, que contiene el texto bruto resultante de una entrada del diccionario y el número tildal que la acompaña. El campo numérico se inicializa por defecto a `-1`, de modo que el tipo tenga un estado inicial claro incluso antes de rellenarse con datos válidos.

**Pseudocódigo:**

```text
definir estructura de entrada del diccionario
guardar resultado crudo
guardar número tildal con valor inicial -1
```

**Relaciones:**

* Es usada por <a href="#cid-11-05">CID-11-05</a> y <a href="#cid-11-06">CID-11-06</a>.
* Su contenido es rellenado durante la carga implementada en <a href="#cid-10-35">CID-10-35</a>.

---

### <a id="cid-11-04"></a>CID-11-04

**Qué hace:**
Declara la clase que carga y consulta el diccionario normalizado de acordes CID.

**Cómo funciona:**
Define la clase `DiccionarioCID`, separando su interfaz pública de su almacenamiento interno. La parte pública expone operaciones de carga y búsqueda, mientras que la parte privada conserva el mapa hash que contiene las entradas ya validadas y normalizadas.

**Pseudocódigo:**

```text
declarar clase DiccionarioCID
exponer operaciones públicas
reservar almacenamiento interno privado
```

**Relaciones:**

* Contiene internamente <a href="#cid-11-05">CID-11-05</a> y <a href="#cid-11-06">CID-11-06</a>.
* Su implementación concreta vive en <a href="#cid-10">CID-10</a>.

---

### <a id="cid-11-05"></a>CID-11-05

**Qué hace:**
Declara la carga desde archivo y la búsqueda por acorde ya normalizado.

**Cómo funciona:**
Expone dos métodos públicos. `CargarDesdeArchivo` permite leer y validar el contenido del diccionario desde una ruta dada, con buffer opcional de error. `Buscar` permite consultar una entrada usando un acorde ya normalizado y, si existe, copiarla al parámetro de salida.

**Pseudocódigo:**

```text
declarar método para cargar diccionario desde archivo
declarar método para buscar entrada por acorde normalizado
```

**Relaciones:**

* Se implementa en <a href="#cid-10-24">CID-10-24</a> y <a href="#cid-10-36">CID-10-36</a>.
* Usa el tipo de salida definido en <a href="#cid-11-03">CID-11-03</a>.
* Forma parte de la interfaz pública de <a href="#cid-11-04">CID-11-04</a>.

---

### <a id="cid-11-06"></a>CID-11-06

**Qué hace:**
Almacena el mapa interno de acordes canónicos hacia sus entradas de diccionario.

**Cómo funciona:**
Declara un `std::unordered_map` privado cuya clave es el acorde CID ya normalizado y cuyo valor es una `EntradaDiccionarioCID`. Este contenedor actúa como almacenamiento central del diccionario cargado y permite búsquedas directas por clave.

**Pseudocódigo:**

```text
declarar mapa hash privado
usar acorde canónico como clave
usar entrada de diccionario como valor
```

**Relaciones:**

* Pertenece a la clase declarada en <a href="#cid-11-04">CID-11-04</a>.
* Es llenado durante <a href="#cid-10-24">CID-10-24</a> y consultado en <a href="#cid-10-36">CID-10-36</a>.


## CID-12

La referencia <a href="#cid-12">CID-12</a> corresponde al archivo <code>superposicion_cid.cpp</code>. Este archivo implementa la superposición visual del sistema CID. Su responsabilidad principal es crear y mantener la ventana flotante que representa el estado visual de la bitácora, el último asentado, el modo QWERTY compacto y los efectos visuales temporales como el error de acorde.

Dentro de <a href="#cid-12">CID-12</a> también se concentra toda la lógica de sincronización, layout, posicionamiento respecto al caret o control activo, dibujo en backbuffer y proyección del estado visual moderno o legado hacia la interfaz. Por eso aquí conviven la ventana popup, el temporizador de animación, los recursos tipográficos, la lógica de filas visibles y el render completo del panel. En términos prácticos, <a href="#cid-12">CID-12</a> es la pieza que convierte el estado interno del motor CID en una representación visual estable, legible y actualizable en tiempo real.

### Índice interno de bloques

* <a href="#cid-12-01">CID-12-01</a>
* <a href="#cid-12-02">CID-12-02</a>
* <a href="#cid-12-03">CID-12-03</a>
* <a href="#cid-12-04">CID-12-04</a>
* <a href="#cid-12-05">CID-12-05</a>
* <a href="#cid-12-06">CID-12-06</a>
* <a href="#cid-12-07">CID-12-07</a>
* <a href="#cid-12-08">CID-12-08</a>
* <a href="#cid-12-09">CID-12-09</a>
* <a href="#cid-12-10">CID-12-10</a>
* <a href="#cid-12-11">CID-12-11</a>
* <a href="#cid-12-12">CID-12-12</a>
* <a href="#cid-12-13">CID-12-13</a>
* <a href="#cid-12-14">CID-12-14</a>
* <a href="#cid-12-15">CID-12-15</a>
* <a href="#cid-12-16">CID-12-16</a>
* <a href="#cid-12-17">CID-12-17</a>
* <a href="#cid-12-18">CID-12-18</a>
* <a href="#cid-12-19">CID-12-19</a>
* <a href="#cid-12-20">CID-12-20</a>
* <a href="#cid-12-21">CID-12-21</a>
* <a href="#cid-12-22">CID-12-22</a>
* <a href="#cid-12-23">CID-12-23</a>
* <a href="#cid-12-24">CID-12-24</a>
* <a href="#cid-12-25">CID-12-25</a>
* <a href="#cid-12-26">CID-12-26</a>
* <a href="#cid-12-27">CID-12-27</a>
* <a href="#cid-12-28">CID-12-28</a>
* <a href="#cid-12-29">CID-12-29</a>
* <a href="#cid-12-30">CID-12-30</a>
* <a href="#cid-12-31">CID-12-31</a>
* <a href="#cid-12-32">CID-12-32</a>
* <a href="#cid-12-33">CID-12-33</a>
* <a href="#cid-12-34">CID-12-34</a>
* <a href="#cid-12-35">CID-12-35</a>
* <a href="#cid-12-36">CID-12-36</a>
* <a href="#cid-12-37">CID-12-37</a>
* <a href="#cid-12-38">CID-12-38</a>
* <a href="#cid-12-39">CID-12-39</a>
* <a href="#cid-12-40">CID-12-40</a>
* <a href="#cid-12-41">CID-12-41</a>
* <a href="#cid-12-42">CID-12-42</a>
* <a href="#cid-12-43">CID-12-43</a>
* <a href="#cid-12-44">CID-12-44</a>
* <a href="#cid-12-45">CID-12-45</a>
* <a href="#cid-12-46">CID-12-46</a>
* <a href="#cid-12-47">CID-12-47</a>
* <a href="#cid-12-48">CID-12-48</a>
* <a href="#cid-12-49">CID-12-49</a>
* <a href="#cid-12-50">CID-12-50</a>
* <a href="#cid-12-51">CID-12-51</a>
* <a href="#cid-12-52">CID-12-52</a>
* <a href="#cid-12-53">CID-12-53</a>
* <a href="#cid-12-54">CID-12-54</a>
* <a href="#cid-12-55">CID-12-55</a>
* <a href="#cid-12-56">CID-12-56</a>
* <a href="#cid-12-57">CID-12-57</a>
* <a href="#cid-12-58">CID-12-58</a>
* <a href="#cid-12-59">CID-12-59</a>
* <a href="#cid-12-60">CID-12-60</a>
* <a href="#cid-12-61">CID-12-61</a>
* <a href="#cid-12-62">CID-12-62</a>
* <a href="#cid-12-63">CID-12-63</a>
* <a href="#cid-12-64">CID-12-64</a>

---

### <a id="cid-12-01"></a>CID-12-01

**Qué hace:**
Incluye la implementación de la superposición visual del sistema CID a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `superposicion_cid.h`, que declara los tipos y funciones públicas del subsistema de superposición. Gracias a esta inclusión, el archivo puede definir la lógica completa de creación, actualización y destrucción de la ventana visual.

**Pseudocódigo:**

```text
incluir interfaz pública de la superposición CID
habilitar definición de sus funciones y tipos asociados
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-12">CID-12</a>.
* Da soporte directo a <a href="#cid-12-53">CID-12-53</a> a <a href="#cid-12-64">CID-12-64</a>.

---

### <a id="cid-12-02"></a>CID-12-02

**Qué hace:**
Incluye cabeceras del sistema y utilidades de texto, contenedores y caracteres usadas por la superposición.

**Cómo funciona:**
Este bloque habilita el acceso a la API Win32, a `std::wstring`, a `std::vector` y a funciones de transformación de caracteres anchos. No contiene lógica ejecutable, pero prepara el entorno de compilación necesario para el resto del archivo.

**Pseudocódigo:**

```text
incluir API de Windows
incluir soporte de cadenas anchas
incluir soporte de vectores
incluir utilidades de caracteres anchos
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-12">CID-12</a>.
* Da soporte indirecto a <a href="#cid-12-18">CID-12-18</a>, <a href="#cid-12-41">CID-12-41</a>, <a href="#cid-12-53">CID-12-53</a> y al resto de bloques con lógica Win32 o texto.

---

### <a id="cid-12-03"></a>CID-12-03

**Qué hace:**
Declara el estado global de la ventana principal de la superposición CID.

**Cómo funciona:**
Mantiene un `HWND` global inicialmente nulo que representa la ventana popup real del panel. Este handle permite mostrarla, ocultarla, invalidarla, reposicionarla y destruirla cuando corresponda.

**Pseudocódigo:**

```text
declarar handle global de ventana
inicializarlo a nulo
```

**Relaciones:**

* Es usado por <a href="#cid-12-22">CID-12-22</a>, <a href="#cid-12-23">CID-12-23</a>, <a href="#cid-12-28">CID-12-28</a>, <a href="#cid-12-52">CID-12-52</a>, <a href="#cid-12-55">CID-12-55</a> y <a href="#cid-12-57">CID-12-57</a>.

---

### <a id="cid-12-04"></a>CID-12-04

**Qué hace:**
Declara el estado global de sincronización que protege el acceso concurrente a la superposición.

**Cómo funciona:**
Reserva una sección crítica global y una bandera que indica si ya ha sido inicializada. Esa sección crítica protege el acceso a los datos compartidos del panel entre el hilo de ventana y las llamadas externas del sistema.

**Pseudocódigo:**

```text
declarar sección crítica global
declarar bandera de inicialización
```

**Relaciones:**

* Es usada por <a href="#cid-12-42">CID-12-42</a>, <a href="#cid-12-44">CID-12-44</a>, <a href="#cid-12-46">CID-12-46</a>, <a href="#cid-12-53">CID-12-53</a>, <a href="#cid-12-57">CID-12-57</a> y <a href="#cid-12-58">CID-12-58</a> a <a href="#cid-12-64">CID-12-64</a>.

---

### <a id="cid-12-05"></a>CID-12-05

**Qué hace:**
Mantiene el estado textual legado de la bitácora y de la última línea asentada mostrada en el pie del panel.

**Cómo funciona:**
Declara dos cadenas anchas globales: una para la bitácora textual antigua y otra para la línea asentada más reciente. Estos valores permiten sostener compatibilidad con el flujo visual legado y alimentar el pie informativo del panel.

**Pseudocódigo:**

```text
declarar texto global de bitácora legacy
declarar texto global del último asentado
```

**Relaciones:**

* Es usado por <a href="#cid-12-26">CID-12-26</a>, <a href="#cid-12-46">CID-12-46</a>, <a href="#cid-12-56">CID-12-56</a>, <a href="#cid-12-58">CID-12-58</a> y <a href="#cid-12-59">CID-12-59</a>.

---

### <a id="cid-12-06"></a>CID-12-06

**Qué hace:**
Mantiene el estado visual autoritativo de la bitácora y una bandera que indica si el modo visual moderno ya está activo.

**Cómo funciona:**
Declara un `EstadoVisualBitacoraCID` global y una bandera booleana inicialmente falsa. Cuando el sistema moderno proporciona un estado visual completo, este pasa a ser la fuente autoritativa y el flujo legacy deja de proyectarse sobre él.

**Pseudocódigo:**

```text
declarar estado visual global de bitácora
declarar bandera de modo visual autoritativo
inicializar la bandera como falsa
```

**Relaciones:**

* Es usado por <a href="#cid-12-24">CID-12-24</a>, <a href="#cid-12-26">CID-12-26</a>, <a href="#cid-12-27">CID-12-27</a>, <a href="#cid-12-46">CID-12-46</a>, <a href="#cid-12-56">CID-12-56</a> y <a href="#cid-12-60">CID-12-60</a>.

---

### <a id="cid-12-07"></a>CID-12-07

**Qué hace:**
Declara el estado temporal del efecto visual de error de acorde y su duración configurada.

**Cómo funciona:**
Mantiene un tick absoluto hasta el que debe seguir vivo el efecto de error y una constante fija de duración en milisegundos. El panel usa esta información para animar sacudida e indicadores rojos durante un intervalo breve.

**Pseudocódigo:**

```text
declarar tick global de fin de error visual
definir duración fija del error visual
```

**Relaciones:**

* Es usado por <a href="#cid-12-19">CID-12-19</a>, <a href="#cid-12-44">CID-12-44</a>, <a href="#cid-12-46">CID-12-46</a>, <a href="#cid-12-56">CID-12-56</a> y <a href="#cid-12-61">CID-12-61</a>.

---

### <a id="cid-12-08"></a>CID-12-08

**Qué hace:**
Declara los recursos tipográficos usados por el panel principal y por la línea de información.

**Cómo funciona:**
Mantiene dos handles globales de fuente: uno para tokens principales y otro para información secundaria. Ambas fuentes se crean al iniciar la superposición y se liberan al detenerla.

**Pseudocódigo:**

```text
declarar fuente global para tokens
declarar fuente global para información secundaria
```

**Relaciones:**

* Es usado por <a href="#cid-12-47">CID-12-47</a>, <a href="#cid-12-49">CID-12-49</a>, <a href="#cid-12-50">CID-12-50</a>, <a href="#cid-12-54">CID-12-54</a> y <a href="#cid-12-57">CID-12-57</a>.

---

### <a id="cid-12-09"></a>CID-12-09

**Qué hace:**
Define la identidad de clase de ventana y el identificador del temporizador interno de animación.

**Cómo funciona:**
Declara un nombre fijo de clase Win32 para registrar la ventana de la superposición y un identificador entero para el temporizador usado en la animación del efecto de error.

**Pseudocódigo:**

```text
definir nombre de clase de ventana
definir identificador del temporizador de animación
```

**Relaciones:**

* Es usado por <a href="#cid-12-44">CID-12-44</a>, <a href="#cid-12-52">CID-12-52</a>, <a href="#cid-12-55">CID-12-55</a> y <a href="#cid-12-57">CID-12-57</a>.

---

### <a id="cid-12-10"></a>CID-12-10

**Qué hace:**
Define mensajes internos que fuerzan layout e invalidación siempre en el hilo de la ventana.

**Cómo funciona:**
Declara dos mensajes personalizados basados en `WM_APP`: uno para aplicar layout y otro para invalidar. Estos mensajes permiten pedir cambios de interfaz de forma asíncrona sin manipular directamente la ventana desde hilos externos.

**Pseudocódigo:**

```text
definir mensaje interno para aplicar layout
definir mensaje interno para invalidar ventana
```

**Relaciones:**

* Es usado por <a href="#cid-12-22">CID-12-22</a>, <a href="#cid-12-23">CID-12-23</a>, <a href="#cid-12-42">CID-12-42</a> y <a href="#cid-12-43">CID-12-43</a>.

---

### <a id="cid-12-11"></a>CID-12-11

**Qué hace:**
Define las dimensiones y la posición base del panel grande de modo CID.

**Cómo funciona:**
Declara constantes de posición inicial y tamaño por defecto para el panel completo cuando el modo visual activo es el panel CID grande.

**Pseudocódigo:**

```text
definir posición base X e Y del panel grande
definir ancho y alto del panel grande
```

**Relaciones:**

* Es usado por <a href="#cid-12-28">CID-12-28</a> y <a href="#cid-12-55">CID-12-55</a>.

---

### <a id="cid-12-12"></a>CID-12-12

**Qué hace:**
Define las dimensiones del panel reducido usado en modo QWERTY.

**Cómo funciona:**
Declara el ancho y el alto del panel compacto que se muestra cuando la superposición entra en modo QWERTY.

**Pseudocódigo:**

```text
definir ancho del panel QWERTY
definir alto del panel QWERTY
```

**Relaciones:**

* Es usado por <a href="#cid-12-28">CID-12-28</a> y afecta al render específico de <a href="#cid-12-47">CID-12-47</a>.

---

### <a id="cid-12-13"></a>CID-12-13

**Qué hace:**
Define márgenes de pantalla y separación visual respecto al rectángulo de anclaje.

**Cómo funciona:**
Declara constantes empleadas al posicionar el panel cerca del caret o control activo, manteniendo separación visual razonable y evitando que el panel quede pegado al borde del monitor.

**Pseudocódigo:**

```text
definir margen mínimo a bordes de pantalla
definir separación visual respecto al anclaje
```

**Relaciones:**

* Es usado por <a href="#cid-12-28">CID-12-28</a> y <a href="#cid-12-29">CID-12-29</a>.

---

### <a id="cid-12-14"></a>CID-12-14

**Qué hace:**
Define los límites del historial visual y el número de líneas visibles simultáneamente.

**Cómo funciona:**
Declara un máximo seguro para líneas cerradas retenidas por la UI y un número fijo de filas visibles en pantalla. Estos valores gobiernan tanto el almacenamiento visual recortado como la composición final del panel.

**Pseudocódigo:**

```text
definir máximo de líneas cerradas visibles para UI
definir número fijo de líneas visibles
```

**Relaciones:**

* Es usado por <a href="#cid-12-24">CID-12-24</a>, <a href="#cid-12-27">CID-12-27</a>, <a href="#cid-12-49">CID-12-49</a> y <a href="#cid-12-60">CID-12-60</a>.

---

### <a id="cid-12-15"></a>CID-12-15

**Qué hace:**
Declara el estado deseado de visibilidad, anclaje y modo QWERTY de la superposición.

**Cómo funciona:**
Mantiene banderas globales para la visibilidad deseada, la existencia de un rectángulo de anclaje válido y la activación del modo QWERTY, además del propio rectángulo de anclaje. Estas variables determinan cómo y dónde debe mostrarse el panel.

**Pseudocódigo:**

```text
declarar visibilidad deseada
declarar si existe rectángulo de anclaje
declarar rectángulo de anclaje
declarar modo QWERTY
```

**Relaciones:**

* Es usado por <a href="#cid-12-28">CID-12-28</a>, <a href="#cid-12-46">CID-12-46</a>, <a href="#cid-12-47">CID-12-47</a>, <a href="#cid-12-56">CID-12-56</a>, <a href="#cid-12-62">CID-12-62</a>, <a href="#cid-12-63">CID-12-63</a> y <a href="#cid-12-64">CID-12-64</a>.

---

### <a id="cid-12-16"></a>CID-12-16

**Qué hace:**
Interpola linealmente un byte entre dos extremos para construir colores intermedios.

**Cómo funciona:**
Recibe dos valores de byte y una fracción expresada como `t/den`. Calcula el desplazamiento proporcional desde `a` hacia `b` y devuelve el byte resultante. Es una utilidad base para construir degradados.

**Pseudocódigo:**

```text
calcular byte intermedio entre dos extremos
devolver resultado interpolado
```

**Relaciones:**

* Es usado por <a href="#cid-12-17">CID-12-17</a>.

---

### <a id="cid-12-17"></a>CID-12-17

**Qué hace:**
Interpola linealmente un color RGB completo a partir de dos colores base.

**Cómo funciona:**
Extrae por separado los componentes rojo, verde y azul de ambos colores, interpola cada canal con `LerpByte` y recompone el color final con `RGB`.

**Pseudocódigo:**

```text
interpolar componente roja
interpolar componente verde
interpolar componente azul
reconstruir color RGB final
```

**Relaciones:**

* Usa <a href="#cid-12-16">CID-12-16</a>.
* Es usado por <a href="#cid-12-32">CID-12-32</a>.

---

### <a id="cid-12-18"></a>CID-12-18

**Qué hace:**
Convierte una cadena completa a mayúsculas para su representación visual en el panel.

**Cómo funciona:**
Copia la cadena de entrada, la recorre carácter a carácter y aplica `towupper` a cada elemento. Devuelve el resultado transformado sin modificar la cadena original.

**Pseudocódigo:**

```text
copiar cadena de entrada
para cada carácter:
    convertirlo a mayúscula
devolver resultado
```

**Relaciones:**

* Es usado por <a href="#cid-12-36">CID-12-36</a>.

---

### <a id="cid-12-19"></a>CID-12-19

**Qué hace:**
Indica si el efecto visual de error sigue activo en el instante actual.

**Cómo funciona:**
Compara el tick actual con el tick global hasta el que el error debe durar. Si el reloj actual todavía es menor, el efecto sigue activo.

**Pseudocódigo:**

```text
comparar tick actual con tick de fin de error
devolver si el error sigue activo
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-12-07">CID-12-07</a>.
* Es usado por <a href="#cid-12-44">CID-12-44</a> y <a href="#cid-12-46">CID-12-46</a>.

---

### <a id="cid-12-20"></a>CID-12-20

**Qué hace:**
Comprueba si un rectángulo tiene dimensiones positivas utilizables.

**Cómo funciona:**
Verifica que `right` sea mayor que `left` y que `bottom` sea mayor que `top`. Solo en ese caso el rectángulo se considera válido para posicionamiento.

**Pseudocódigo:**

```text
devolver si el rectángulo tiene ancho y alto positivos
```

**Relaciones:**

* Es usado por <a href="#cid-12-21">CID-12-21</a>, <a href="#cid-12-28">CID-12-28</a> y <a href="#cid-12-63">CID-12-63</a>.

---

### <a id="cid-12-21"></a>CID-12-21

**Qué hace:**
Aplica una heurística para detectar si un rectángulo de anclaje parece representar un caret de texto.

**Cómo funciona:**
Comprueba primero que el rectángulo sea válido. Después evalúa si su anchura es pequeña, concretamente de diez píxeles o menos. Si se cumple esa condición, lo trata como un caret estrecho.

**Pseudocódigo:**

```text
si el rectángulo no es válido:
    devolver falso
devolver si su anchura es muy pequeña
```

**Relaciones:**

* Usa <a href="#cid-12-20">CID-12-20</a>.
* Es usado por <a href="#cid-12-29">CID-12-29</a>.

---

### <a id="cid-12-22"></a>CID-12-22

**Qué hace:**
Solicita un repintado asíncrono de la ventana de superposición en su propio hilo.

**Cómo funciona:**
Si la ventana existe, publica el mensaje interno de invalidación mediante `PostMessageW`. Así el repintado se procesa de forma segura en el hilo de la propia ventana.

**Pseudocódigo:**

```text
si existe ventana:
    publicar mensaje interno de invalidación
```

**Relaciones:**

* Usa <a href="#cid-12-03">CID-12-03</a> y <a href="#cid-12-10">CID-12-10</a>.
* Es llamado desde <a href="#cid-12-56">CID-12-56</a> y <a href="#cid-12-58">CID-12-58</a> a <a href="#cid-12-64">CID-12-64</a>.

---

### <a id="cid-12-23"></a>CID-12-23

**Qué hace:**
Solicita un recálculo asíncrono de layout y posición de la superposición en su propio hilo.

**Cómo funciona:**
Si la ventana existe, publica el mensaje interno de aplicar layout. Esto desplaza el cálculo de visibilidad, tamaño y posición al hilo de la ventana.

**Pseudocódigo:**

```text
si existe ventana:
    publicar mensaje interno de aplicar layout
```

**Relaciones:**

* Usa <a href="#cid-12-03">CID-12-03</a> y <a href="#cid-12-10">CID-12-10</a>.
* Es llamado desde <a href="#cid-12-56">CID-12-56</a>, <a href="#cid-12-58">CID-12-58</a>, <a href="#cid-12-60">CID-12-60</a>, <a href="#cid-12-62">CID-12-62</a>, <a href="#cid-12-63">CID-12-63</a> y <a href="#cid-12-64">CID-12-64</a>.

---

### <a id="cid-12-24"></a>CID-12-24

**Qué hace:**
Recorta el historial visual cerrado a un máximo seguro para la interfaz.

**Cómo funciona:**
Comprueba si el número de líneas cerradas supera el límite de UI. Si lo supera, calcula el exceso y elimina las más antiguas del inicio del vector, conservando solo las más recientes.

**Pseudocódigo:**

```text
si hay más líneas cerradas que el máximo:
    calcular exceso
    borrar las más antiguas
```

**Relaciones:**

* Usa <a href="#cid-12-06">CID-12-06</a> y <a href="#cid-12-14">CID-12-14</a>.
* Es llamado desde <a href="#cid-12-26">CID-12-26</a> y <a href="#cid-12-60">CID-12-60</a>.

---

### <a id="cid-12-25"></a>CID-12-25

**Qué hace:**
Convierte la bitácora textual antigua entre corchetes en tokens visuales básicos de piezas.

**Cómo funciona:**
Parte de una cadena de texto legacy, elimina corchetes de apertura y cierre si existen, recorre su contenido por segmentos separados por espacios o tabuladores y convierte cada segmento no vacío en un `TokenVisualCID` de tipo `Pieza`.

**Pseudocódigo:**

```text
crear vector de salida
si el texto es demasiado corto:
    devolver vacío

copiar texto
quitar corchetes externos si existen

recorrer texto por fragmentos no vacíos
para cada fragmento:
    crear token visual de tipo pieza
    añadirlo a salida

devolver tokens
```

**Relaciones:**

* Es llamado desde <a href="#cid-12-26">CID-12-26</a>.
* Produce `TokenVisualCID` usados por el estado visual definido en <a href="#cid-12-06">CID-12-06</a>.

---

### <a id="cid-12-26"></a>CID-12-26

**Qué hace:**
Traduce la bitácora textual heredada al estado visual interno mientras no exista modo autoritativo.

**Cómo funciona:**
Si el modo visual autoritativo ya está activo, no hace nada. Si no lo está, parsea la cadena legacy a tokens visuales. Si no obtiene tokens y la línea actual contenía algo, la cierra visualmente y vacía la línea viva. Si sí obtiene tokens, reemplaza la línea actual del estado visual con ellos.

**Pseudocódigo:**

```text
si el modo visual autoritativo está activo:
    salir

parsear tokens legacy

si no hay tokens:
    si la línea actual no está vacía:
        moverla a líneas cerradas
        recortar historial
    vaciar línea actual
    salir

usar tokens como nueva línea actual
```

**Relaciones:**

* Usa <a href="#cid-12-06">CID-12-06</a>, <a href="#cid-12-24">CID-12-24</a> y <a href="#cid-12-25">CID-12-25</a>.
* Es llamado desde <a href="#cid-12-58">CID-12-58</a>.

---

### <a id="cid-12-27"></a>CID-12-27

**Qué hace:**
Construye las filas visibles finales combinando líneas cerradas recientes y la línea actual.

**Cómo funciona:**
Parte del estado visual actual, selecciona las líneas cerradas más recientes que caben junto a la línea activa, añade la línea actual, rellena con filas vacías por arriba si faltan y recorta por delante si sobran. Finalmente devuelve también el índice de la fila activa.

**Pseudocódigo:**

```text
vaciar filas de salida
calcular desde qué línea cerrada empezar
copiar líneas cerradas recientes
añadir línea actual
rellenar con líneas vacías por arriba si faltan
recortar por arriba si sobran
marcar índice de la fila activa
```

**Relaciones:**

* Usa <a href="#cid-12-14">CID-12-14</a>.
* Es llamado desde <a href="#cid-12-49">CID-12-49</a>.

---

### <a id="cid-12-28"></a>CID-12-28

**Qué hace:**
Aplica visibilidad, tamaño y posición de la ventana según modo, anclaje y monitor activo.

**Cómo funciona:**
Si no existe ventana, no hace nada. Si la visibilidad deseada está desactivada, oculta la ventana. Si debe mostrarse, elige el tamaño según el modo QWERTY o CID, calcula una posición base y, si existe un rectángulo de anclaje válido, delega el ajuste fino en lógica relativa al caret, al control y al área útil del monitor. Finalmente llama a `SetWindowPos` para aplicar el resultado.

**Pseudocódigo:**

```text
si no existe ventana:
    salir

si no debe ser visible:
    ocultar ventana
    salir

elegir tamaño según modo visual
partir de posición base

si existe rectángulo de anclaje válido:
    calcular mejor posición relativa

aplicar posición y tamaño a la ventana
```

**Relaciones:**

* Contiene internamente <a href="#cid-12-29">CID-12-29</a>.
* Usa <a href="#cid-12-03">CID-12-03</a>, <a href="#cid-12-11">CID-12-11</a>, <a href="#cid-12-12">CID-12-12</a>, <a href="#cid-12-13">CID-12-13</a>, <a href="#cid-12-15">CID-12-15</a>, <a href="#cid-12-20">CID-12-20</a> y <a href="#cid-12-21">CID-12-21</a>.
* Es llamado desde <a href="#cid-12-42">CID-12-42</a>.

---

### <a id="cid-12-29"></a>CID-12-29

**Qué hace:**
Si existe un rectángulo de anclaje válido, calcula la mejor posición relativa al caret o control.

**Cómo funciona:**
Busca el monitor más cercano al rectángulo de anclaje y recupera su área de trabajo. Si el rectángulo parece un caret, centra el panel respecto a él; si no, lo alinea con margen respecto al control. Luego calcula el espacio libre arriba y abajo y decide si mostrar el panel por debajo o por encima. Finalmente limita la posición a los márgenes seguros del monitor.

**Pseudocódigo:**

```text
si hay rectángulo de anclaje válido:
    obtener monitor más cercano
    obtener área útil de trabajo

    si parece caret:
        centrar horizontalmente respecto al caret
    si no:
        alinear respecto al control

    calcular espacio arriba y abajo
    decidir si colocar arriba o abajo

    limitar posición a márgenes seguros de pantalla
```

**Relaciones:**

* Usa <a href="#cid-12-13">CID-12-13</a>, <a href="#cid-12-15">CID-12-15</a>, <a href="#cid-12-20">CID-12-20</a> y <a href="#cid-12-21">CID-12-21</a>.
* Forma parte de <a href="#cid-12-28">CID-12-28</a>.

---

### <a id="cid-12-30"></a>CID-12-30

**Qué hace:**
Rellena un rectángulo completo con un color sólido.

**Cómo funciona:**
Crea un pincel sólido con el color indicado, llama a `FillRect` sobre el rectángulo y luego libera el pincel temporal.

**Pseudocódigo:**

```text
crear pincel sólido del color pedido
rellenar rectángulo
liberar pincel
```

**Relaciones:**

* Es usado por <a href="#cid-12-45">CID-12-45</a>, <a href="#cid-12-47">CID-12-47</a> y <a href="#cid-12-48">CID-12-48</a>.

---

### <a id="cid-12-31"></a>CID-12-31

**Qué hace:**
Dibuja el borde de un rectángulo usando un color de línea simple.

**Cómo funciona:**
Crea un lápiz del color indicado, selecciona un pincel hueco para evitar relleno, traza el contorno rectangular y después restaura y libera los recursos GDI usados.

**Pseudocódigo:**

```text
crear lápiz del color de borde
seleccionar lápiz y pincel hueco
dibujar contorno rectangular
restaurar objetos previos
liberar lápiz
```

**Relaciones:**

* Es usado por <a href="#cid-12-47">CID-12-47</a> y <a href="#cid-12-48">CID-12-48</a>.

---

### <a id="cid-12-32"></a>CID-12-32

**Qué hace:**
Dibuja un degradado vertical por líneas interpolando entre tres colores.

**Cómo funciona:**
Calcula la altura del rectángulo y su mitad. Recorre cada línea horizontal del rectángulo, interpolando de `top` a `mid` en la primera mitad y de `mid` a `bottom` en la segunda. Para cada línea crea un lápiz del color correspondiente y traza un segmento horizontal.

**Pseudocódigo:**

```text
calcular altura del rectángulo
si la altura no es válida:
    salir

calcular mitad del rectángulo
para cada línea vertical:
    elegir color interpolado entre top, mid y bottom
    crear lápiz de ese color
    dibujar una línea horizontal
    liberar lápiz
```

**Relaciones:**

* Usa <a href="#cid-12-17">CID-12-17</a>.
* Es llamado desde <a href="#cid-12-33">CID-12-33</a> y <a href="#cid-12-47">CID-12-47</a>.

---

### <a id="cid-12-33"></a>CID-12-33

**Qué hace:**
Dibuja una fila del panel con estilo distinto según esté activa o alternada.

**Cómo funciona:**
Selecciona una paleta de colores según si la fila está activa, si es alterna o si es una fila normal. Después dibuja el degradado de fondo y una línea inferior de borde para separar visualmente la fila.

**Pseudocódigo:**

```text
elegir colores según tipo de fila
dibujar degradado de fondo
dibujar línea inferior de borde
```

**Relaciones:**

* Usa <a href="#cid-12-32">CID-12-32</a>.
* Es llamado desde <a href="#cid-12-49">CID-12-49</a>.

---

### <a id="cid-12-34"></a>CID-12-34

**Qué hace:**
Devuelve el ancho aproximado de un carácter monoespaciado para cálculos de wrapping.

**Cómo funciona:**
Mide el ancho visual de la letra `M` con `GetTextExtentPoint32W`. Si la medida es válida, la devuelve; si no, usa un ancho por defecto de 8 píxeles.

**Pseudocódigo:**

```text
medir ancho de un carácter de referencia
si la medida es válida:
    devolverla
devolver ancho por defecto
```

**Relaciones:**

* Es usado por <a href="#cid-12-36">CID-12-36</a>.

---

### <a id="cid-12-35"></a>CID-12-35

**Qué hace:**
Parte un token largo en varias líneas cuando no contiene espacios y supera el ancho útil.

**Cómo funciona:**
Asegura un mínimo razonable de caracteres por línea. Luego comprueba si el texto contiene espacios o si ya cabe en una sola línea. Si debe partirlo, inserta saltos de línea cada `maxCharsPorLinea` caracteres.

**Pseudocódigo:**

```text
asegurar mínimo de caracteres por línea

si el texto tiene espacios o ya cabe:
    devolver texto sin cambios

crear salida vacía
recorrer caracteres
insertar salto de línea cada cierto número de caracteres
devolver resultado
```

**Relaciones:**

* Es usado por <a href="#cid-12-36">CID-12-36</a>.

---

### <a id="cid-12-36"></a>CID-12-36

**Qué hace:**
Dibuja texto centrado y con wrapping dentro de una caja calculando su altura visual real.

**Cómo funciona:**
Calcula el ancho aproximado por carácter y estima cuántos caracteres caben por línea. Convierte el texto a mayúsculas, parte tokens largos si es necesario y usa `DrawTextW` primero en modo de cálculo para medir la altura real del bloque. Después centra verticalmente el resultado dentro de la caja y lo dibuja definitivamente.

**Pseudocódigo:**

```text
calcular ancho aproximado por carácter
estimar máximo de caracteres por línea
convertir texto a mayúsculas
partir token largo si hace falta

medir altura real del bloque de texto
calcular desplazamiento vertical para centrar
dibujar texto centrado y con wrapping
```

**Relaciones:**

* Usa <a href="#cid-12-18">CID-12-18</a>, <a href="#cid-12-34">CID-12-34</a> y <a href="#cid-12-35">CID-12-35</a>.
* Es llamado desde <a href="#cid-12-38">CID-12-38</a> y <a href="#cid-12-39">CID-12-39</a>.

---

### <a id="cid-12-37"></a>CID-12-37

**Qué hace:**
Dibuja los tokens de una línea distribuyéndolos de forma equilibrada dentro de su fila.

**Cómo funciona:**
Si la línea no tiene tokens, no hace nada. Si tiene uno solo, delega a un caso especial que ocupa todo el ancho útil. Si tiene varios, calcula espacios, anchura de celdas y posición de inicio para centrar el conjunto, y después dibuja cada token dentro de su caja horizontal correspondiente.

**Pseudocódigo:**

```text
si no hay tokens:
    salir

configurar estilo de texto
calcular área útil interna

si hay un solo token:
    dibujarlo ocupando todo el ancho útil
    salir

calcular separación y anchura de celdas
centrar bloque de tokens
dibujar cada token en su celda
```

**Relaciones:**

* Contiene internamente <a href="#cid-12-38">CID-12-38</a> y <a href="#cid-12-39">CID-12-39</a>.
* Usa <a href="#cid-12-36">CID-12-36</a>.
* Es llamado desde <a href="#cid-12-49">CID-12-49</a>.

---

### <a id="cid-12-38"></a>CID-12-38

**Qué hace:**
Gestiona el caso especial de una sola pieza ocupando visualmente todo el ancho útil de la fila.

**Cómo funciona:**
Construye un rectángulo que cubre toda la zona útil de la fila y delega el dibujo del texto en la función centrada con wrapping.

**Pseudocódigo:**

```text
si solo hay un token:
    construir caja de ancho completo
    dibujar texto centrado dentro de ella
```

**Relaciones:**

* Usa <a href="#cid-12-36">CID-12-36</a>.
* Forma parte de <a href="#cid-12-37">CID-12-37</a>.

---

### <a id="cid-12-39"></a>CID-12-39

**Qué hace:**
Dibuja cada token de la línea en su celda horizontal correspondiente.

**Cómo funciona:**
Recorre el conjunto de tokens, construye para cada uno un rectángulo de celda según la posición actual, lo dibuja centrado y luego avanza la coordenada horizontal sumando ancho de celda y separación.

**Pseudocódigo:**

```text
para cada token:
    construir rectángulo de celda
    dibujar texto centrado en la celda
    avanzar posición horizontal
```

**Relaciones:**

* Usa <a href="#cid-12-36">CID-12-36</a>.
* Forma parte de <a href="#cid-12-37">CID-12-37</a>.

---

### <a id="cid-12-40"></a>CID-12-40

**Qué hace:**
Dibuja las marcas diagonales rojas en las esquinas cuando hay error visual activo.

**Cómo funciona:**
Crea un lápiz rojo y traza pequeñas diagonales repetidas en las cuatro esquinas del rectángulo del panel, generando un adorno visual agresivo que comunica error de acorde.

**Pseudocódigo:**

```text
crear lápiz rojo
dibujar diagonales en esquina superior izquierda
dibujar diagonales en esquina superior derecha
dibujar diagonales en esquina inferior izquierda
dibujar diagonales en esquina inferior derecha
restaurar y liberar lápiz
```

**Relaciones:**

* Es usado por <a href="#cid-12-51">CID-12-51</a>.

---

### <a id="cid-12-41"></a>CID-12-41

**Qué hace:**
Define el procedimiento principal de ventana que procesa entrada, temporización, layout y repintado.

**Cómo funciona:**
Implementa el `WndProc` de la superposición. Gestiona mensajes de activación del ratón, borrado de fondo, layout interno, invalidación, temporizador, pintado completo y destrucción. Para ello delega en funciones auxiliares y usa el estado protegido del subsistema.

**Pseudocódigo:**

```text
según el mensaje recibido:
    ignorar activación
    suprimir borrado de fondo
    aplicar layout
    invalidar ventana
    procesar temporizador
    pintar ventana
    limpiar al destruir
    delegar en comportamiento por defecto en otros casos
```

**Relaciones:**

* Contiene internamente <a href="#cid-12-42">CID-12-42</a> a <a href="#cid-12-52">CID-12-52</a>.
* Es registrado como callback de la clase de ventana en <a href="#cid-12-55">CID-12-55</a>.

---

### <a id="cid-12-42"></a>CID-12-42

**Qué hace:**
Aplica layout y posición solicitados de forma segura en el hilo de la ventana.

**Cómo funciona:**
Cuando llega el mensaje interno correspondiente, comprueba que la sincronización esté iniciada, entra en la sección crítica, recalcula visibilidad y posición mediante el helper correspondiente y sale del bloqueo.

**Pseudocódigo:**

```text
si la sincronización está iniciada:
    entrar en sección crítica
    aplicar visibilidad y posición
    salir de sección crítica
devolver procesado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-10">CID-12-10</a> y <a href="#cid-12-28">CID-12-28</a>.
* Forma parte de <a href="#cid-12-41">CID-12-41</a>.

---

### <a id="cid-12-43"></a>CID-12-43

**Qué hace:**
Invalida completamente la ventana para solicitar un nuevo repintado.

**Cómo funciona:**
Responde al mensaje interno de invalidación llamando a `InvalidateRect` sobre toda la ventana, forzando que Windows programe un nuevo `WM_PAINT`.

**Pseudocódigo:**

```text
invalidar toda la ventana
devolver procesado
```

**Relaciones:**

* Usa <a href="#cid-12-10">CID-12-10</a>.
* Forma parte de <a href="#cid-12-41">CID-12-41</a>.

---

### <a id="cid-12-44"></a>CID-12-44

**Qué hace:**
Anima repintados periódicos solo mientras siga vivo el efecto visual de error.

**Cómo funciona:**
Cuando llega el `WM_TIMER` del temporizador de animación, comprueba si se trata del temporizador propio del panel. Si es así, lee bajo protección si el efecto de error sigue activo y, solo en ese caso, invalida la ventana para que continúe la animación.

**Pseudocódigo:**

```text
si el temporizador es el de animación:
    leer si el error sigue activo
    si sigue activo:
        invalidar ventana
devolver procesado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-09">CID-12-09</a> y <a href="#cid-12-19">CID-12-19</a>.
* Forma parte de <a href="#cid-12-41">CID-12-41</a>.

---

### <a id="cid-12-45"></a>CID-12-45

**Qué hace:**
Dibuja el panel completo en backbuffer y lo copia luego a pantalla para evitar parpadeos.

**Cómo funciona:**
Abre el ciclo de pintado con `BeginPaint`, crea un DC compatible y un bitmap temporal como backbuffer, captura una instantánea local del estado protegido, pinta el fondo, calcula posible sacudida por error y después dibuja el panel en modo QWERTY o en modo CID grande. Al final copia el backbuffer a pantalla con `BitBlt` y libera todos los recursos temporales.

**Pseudocódigo:**

```text
iniciar pintado
crear backbuffer compatible
capturar instantánea local del estado
dibujar fondo base
calcular desplazamiento visual por error

si el modo es QWERTY:
    dibujar panel compacto
si no:
    dibujar panel grande con filas y pie

copiar backbuffer a pantalla
liberar recursos temporales
cerrar pintado
```

**Relaciones:**

* Contiene internamente <a href="#cid-12-46">CID-12-46</a> a <a href="#cid-12-51">CID-12-51</a>.
* Usa múltiples helpers gráficos y de layout definidos en <a href="#cid-12-27">CID-12-27</a>, <a href="#cid-12-30">CID-12-30</a>, <a href="#cid-12-31">CID-12-31</a>, <a href="#cid-12-33">CID-12-33</a>, <a href="#cid-12-37">CID-12-37</a> y <a href="#cid-12-40">CID-12-40</a>.
* Forma parte de <a href="#cid-12-41">CID-12-41</a>.

---

### <a id="cid-12-46"></a>CID-12-46

**Qué hace:**
Captura una instantánea local del estado protegido antes de dibujar.

**Cómo funciona:**
Entra en la sección crítica, copia el estado visual, el último asentado, la bandera de error activo y el modo QWERTY a variables locales y sale del bloqueo. Esto evita mantener la sección crítica tomada durante todo el render.

**Pseudocódigo:**

```text
entrar en sección crítica
copiar estado visual a variables locales
copiar texto asentado
copiar estado de error visual
copiar modo QWERTY
salir de sección crítica
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-05">CID-12-05</a>, <a href="#cid-12-06">CID-12-06</a>, <a href="#cid-12-15">CID-12-15</a> y <a href="#cid-12-19">CID-12-19</a>.
* Forma parte de <a href="#cid-12-45">CID-12-45</a>.

---

### <a id="cid-12-47"></a>CID-12-47

**Qué hace:**
Dibuja el panel compacto de modo QWERTY cuando ese modo está activo.

**Cómo funciona:**
Traza una sombra, dibuja un panel con degradado y borde, selecciona la fuente de información y escribe el texto fijo `MODO QWERTY` centrado. Después vuelca el backbuffer, libera recursos y termina el pintado sin seguir por el camino del panel grande.

**Pseudocódigo:**

```text
dibujar sombra del panel compacto
dibujar fondo degradado y borde
seleccionar fuente de información
dibujar texto "MODO QWERTY" centrado
copiar backbuffer a pantalla
liberar recursos temporales
terminar pintado
```

**Relaciones:**

* Usa <a href="#cid-12-08">CID-12-08</a>, <a href="#cid-12-30">CID-12-30</a>, <a href="#cid-12-31">CID-12-31</a> y <a href="#cid-12-32">CID-12-32</a>.
* Forma parte de <a href="#cid-12-45">CID-12-45</a>.

---

### <a id="cid-12-48"></a>CID-12-48

**Qué hace:**
Dibuja la caja general del panel grande del modo CID con sombra y borde.

**Cómo funciona:**
Genera una sombra desplazada del panel, rellena el fondo del panel principal y dibuja su borde exterior. Después prepara los rectángulos internos de líneas y de pie informativo para el resto del render.

**Pseudocódigo:**

```text
dibujar sombra del panel grande
rellenar fondo del panel
dibujar borde exterior
calcular rectángulo de líneas
calcular rectángulo de pie
```

**Relaciones:**

* Usa <a href="#cid-12-30">CID-12-30</a> y <a href="#cid-12-31">CID-12-31</a>.
* Forma parte de <a href="#cid-12-45">CID-12-45</a>.
* Precede a <a href="#cid-12-49">CID-12-49</a> y <a href="#cid-12-50">CID-12-50</a>.

---

### <a id="cid-12-49"></a>CID-12-49

**Qué hace:**
Dibuja cada fila visible del historial y la línea activa con sus tokens.

**Cómo funciona:**
Construye primero las filas visibles y el índice activo. Luego calcula la altura por fila, selecciona la fuente principal y recorre todas las filas visibles dibujando el fondo de cada una y, si existe contenido para esa posición, también sus tokens.

**Pseudocódigo:**

```text
construir filas visibles e índice activo
calcular altura de fila
seleccionar fuente principal

para cada fila visible:
    calcular rectángulo de fila
    decidir si está activa o alterna
    dibujar fondo de fila
    dibujar tokens si existen
```

**Relaciones:**

* Usa <a href="#cid-12-08">CID-12-08</a>, <a href="#cid-12-14">CID-12-14</a>, <a href="#cid-12-27">CID-12-27</a>, <a href="#cid-12-33">CID-12-33</a> y <a href="#cid-12-37">CID-12-37</a>.
* Forma parte de <a href="#cid-12-45">CID-12-45</a>.

---

### <a id="cid-12-50"></a>CID-12-50

**Qué hace:**
Dibuja la línea divisoria y el texto informativo del último asentado en el pie del panel.

**Cómo funciona:**
Crea una línea horizontal separadora en la parte superior del pie, selecciona la fuente secundaria, construye el texto informativo si existe un último asentado y lo dibuja alineado a la izquierda con elipsis al final si no cabe.

**Pseudocódigo:**

```text
dibujar línea divisoria del pie
seleccionar fuente secundaria
si hay texto asentado:
    construir texto "ASENTADO: ..."
dibujar texto informativo con elipsis si hace falta
```

**Relaciones:**

* Usa <a href="#cid-12-08">CID-12-08</a> y el estado textual copiado en <a href="#cid-12-46">CID-12-46</a>.
* Forma parte de <a href="#cid-12-45">CID-12-45</a>.

---

### <a id="cid-12-51"></a>CID-12-51

**Qué hace:**
Dibuja el adorno de error visual sobre el panel cuando el estado de error está activo.

**Cómo funciona:**
Comprueba la bandera local de error visual y, si está activa, llama a la rutina que dibuja las esquinas diagonales rojas encima del panel.

**Pseudocódigo:**

```text
si el error visual está activo:
    dibujar esquinas de error
```

**Relaciones:**

* Usa <a href="#cid-12-40">CID-12-40</a>.
* Forma parte de <a href="#cid-12-45">CID-12-45</a>.

---

### <a id="cid-12-52"></a>CID-12-52

**Qué hace:**
Limpia el temporizador y la referencia global cuando la ventana es destruida.

**Cómo funciona:**
Mata el temporizador de animación asociado a la ventana y pone a nulo el handle global de la superposición. No realiza aquí la liberación de fuentes ni de la sección crítica, porque eso se hace en el cierre explícito del subsistema.

**Pseudocódigo:**

```text
detener temporizador de animación
poner handle global de ventana a nulo
devolver procesado
```

**Relaciones:**

* Usa <a href="#cid-12-03">CID-12-03</a> y <a href="#cid-12-09">CID-12-09</a>.
* Forma parte de <a href="#cid-12-41">CID-12-41</a>.
* Es complementado por <a href="#cid-12-57">CID-12-57</a>.

---

### <a id="cid-12-53"></a>CID-12-53

**Qué hace:**
Inicializa la clase de ventana, los recursos gráficos y el estado base de la superposición CID.

**Cómo funciona:**
Asegura primero la inicialización de la sección crítica. Después crea las dos fuentes del panel, registra la clase de ventana, crea la ventana popup transparente, configura atributos visuales y temporizador, inicializa el estado interno protegido y finalmente deja la ventana oculta, pidiendo layout e invalidación iniciales.

**Pseudocódigo:**

```text
inicializar sección crítica si hace falta
crear fuentes del panel
registrar clase de ventana
crear ventana popup transparente
si falla la creación:
    devolver falso

configurar transparencia y temporizador
inicializar estado interno base
ocultar ventana
solicitar layout inicial
solicitar repintado inicial
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-12-54">CID-12-54</a> a <a href="#cid-12-56">CID-12-56</a>.
* Es una de las funciones públicas declaradas por <code>superposicion_cid.h</code>.
* Su cierre natural es <a href="#cid-12-57">CID-12-57</a>.

---

### <a id="cid-12-54"></a>CID-12-54

**Qué hace:**
Construye las dos fuentes usadas por el panel para tokens e información secundaria.

**Cómo funciona:**
Rellena dos estructuras `LOGFONTW`, una para una fuente monoespaciada de tokens y otra para una fuente de interfaz ligera. Después crea ambos recursos con `CreateFontIndirectW` y los almacena globalmente.

**Pseudocódigo:**

```text
configurar fuente de tokens
configurar fuente de información
crear ambas fuentes
guardar handles globales
```

**Relaciones:**

* Usa <a href="#cid-12-08">CID-12-08</a>.
* Forma parte de <a href="#cid-12-53">CID-12-53</a>.

---

### <a id="cid-12-55"></a>CID-12-55

**Qué hace:**
Registra la clase de ventana y crea la ventana popup transparente de la superposición.

**Cómo funciona:**
Prepara una estructura `WNDCLASSEXW` con el `WndProc` del panel, registra la clase con `RegisterClassExW` y crea la ventana con `CreateWindowExW` usando estilos topmost, toolwindow, layered y no activable. Si la creación falla, devuelve error. Si tiene éxito, configura opacidad alfa y arranca el temporizador de animación.

**Pseudocódigo:**

```text
configurar clase de ventana
registrar clase
crear ventana popup transparente
si no se crea:
    devolver falso

configurar transparencia
arrancar temporizador de animación
```

**Relaciones:**

* Usa <a href="#cid-12-03">CID-12-03</a>, <a href="#cid-12-09">CID-12-09</a>, <a href="#cid-12-11">CID-12-11</a> y <a href="#cid-12-41">CID-12-41</a>.
* Forma parte de <a href="#cid-12-53">CID-12-53</a>.

---

### <a id="cid-12-56"></a>CID-12-56

**Qué hace:**
Inicializa el estado interno base de la superposición tras crear la ventana.

**Cómo funciona:**
Entra en la sección crítica y restablece todos los campos globales relevantes: bitácora legacy, último asentado, estado visual, modo autoritativo, tick de error, visibilidad, anclaje y modo QWERTY. Después deja la ventana oculta y solicita tanto layout como repintado inicial.

**Pseudocódigo:**

```text
entrar en sección crítica
restablecer texto legacy y último asentado
vaciar estado visual
desactivar modo autoritativo
apagar error visual
restablecer visibilidad y anclaje
desactivar modo QWERTY
salir de sección crítica

ocultar ventana
solicitar layout
solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-05">CID-12-05</a>, <a href="#cid-12-06">CID-12-06</a>, <a href="#cid-12-07">CID-12-07</a>, <a href="#cid-12-15">CID-12-15</a>, <a href="#cid-12-22">CID-12-22</a> y <a href="#cid-12-23">CID-12-23</a>.
* Forma parte de <a href="#cid-12-53">CID-12-53</a>.

---

### <a id="cid-12-57"></a>CID-12-57

**Qué hace:**
Detiene la superposición liberando ventana, fuentes y sincronización interna.

**Cómo funciona:**
Si la ventana existe, la destruye. Después libera ambas fuentes si estaban creadas y, por último, borra la sección crítica si había sido inicializada.

**Pseudocódigo:**

```text
si existe ventana:
    destruirla

si existe fuente de tokens:
    liberarla

si existe fuente de información:
    liberarla

si la sección crítica estaba iniciada:
    borrarla
```

**Relaciones:**

* Usa <a href="#cid-12-03">CID-12-03</a>, <a href="#cid-12-04">CID-12-04</a> y <a href="#cid-12-08">CID-12-08</a>.
* Es la contraparte de arranque de <a href="#cid-12-53">CID-12-53</a>.

---

### <a id="cid-12-58"></a>CID-12-58

**Qué hace:**
Actualiza la bitácora textual heredada y la proyecta al estado visual cuando procede.

**Cómo funciona:**
Si la sincronización no está inicializada, no hace nada. Si sí lo está, entra en la sección crítica, actualiza la cadena legacy de bitácora y la proyecta sobre el estado visual mientras no exista modo autoritativo. Después solicita recálculo de layout e invalidación.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
guardar nueva bitácora textual
aplicarla al estado visual legacy si procede
salir de sección crítica

solicitar layout
solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-05">CID-12-05</a>, <a href="#cid-12-26">CID-12-26</a>, <a href="#cid-12-22">CID-12-22</a> y <a href="#cid-12-23">CID-12-23</a>.
* Es una de las funciones públicas del subsistema de superposición.

---

### <a id="cid-12-59"></a>CID-12-59

**Qué hace:**
Actualiza el texto mostrado como último asentado en el pie del panel.

**Cómo funciona:**
Si la sincronización no está activa, no hace nada. Si lo está, entra en la sección crítica, sustituye el valor global del último asentado y sale. Después solicita solo repintado, ya que no necesita recalcular layout.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
guardar nuevo texto asentado
salir de sección crítica

solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-05">CID-12-05</a> y <a href="#cid-12-22">CID-12-22</a>.
* Es una de las funciones públicas del subsistema de superposición.

---

### <a id="cid-12-60"></a>CID-12-60

**Qué hace:**
Sustituye el estado visual completo por uno autoritativo proveniente de la bitácora moderna.

**Cómo funciona:**
Si la sincronización no está activa, sale. Si está activa, entra en la sección crítica, reemplaza el estado visual completo, activa el modo autoritativo y recorta las líneas cerradas al máximo permitido. Después solicita layout e invalidación.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
copiar estado visual completo
activar modo visual autoritativo
recortar líneas cerradas a máximo UI
salir de sección crítica

solicitar layout
solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-06">CID-12-06</a>, <a href="#cid-12-24">CID-12-24</a>, <a href="#cid-12-22">CID-12-22</a> y <a href="#cid-12-23">CID-12-23</a>.
* Es una de las funciones públicas del subsistema de superposición.

---

### <a id="cid-12-61"></a>CID-12-61

**Qué hace:**
Activa temporalmente el efecto visual de error de acorde.

**Cómo funciona:**
Si la sincronización no está activa, no hace nada. Si está activa, entra en la sección crítica, fija el tick de fin del error al tiempo actual más la duración configurada y sale. Después solicita un repintado inmediato.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
fijar fin del error visual a ahora + duración
salir de sección crítica

solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-07">CID-12-07</a> y <a href="#cid-12-22">CID-12-22</a>.
* Es una de las funciones públicas del subsistema de superposición.

---

### <a id="cid-12-62"></a>CID-12-62

**Qué hace:**
Establece la visibilidad deseada del panel y solicita recalcular layout.

**Cómo funciona:**
Si la sincronización no está activa, sale. Si está activa, entra en la sección crítica, actualiza la bandera de visibilidad deseada y sale. Después solicita layout e invalidación para reflejar el cambio.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
guardar nueva visibilidad deseada
salir de sección crítica

solicitar layout
solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-15">CID-12-15</a>, <a href="#cid-12-22">CID-12-22</a> y <a href="#cid-12-23">CID-12-23</a>.
* Es una de las funciones públicas del subsistema de superposición.

---

### <a id="cid-12-63"></a>CID-12-63

**Qué hace:**
Actualiza el rectángulo de anclaje usado para posicionar el panel cerca del caret o control activo.

**Cómo funciona:**
Si la sincronización no está activa, no hace nada. Si está activa, entra en la sección crítica y valida el rectángulo recibido. Si es válido, lo guarda como anclaje activo. Si no lo es, desactiva el anclaje y reinicia el rectángulo a cero. Después solicita layout e invalidación.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
si el rectángulo es válido:
    activar anclaje y guardar rectángulo
si no:
    desactivar anclaje y reiniciar rectángulo
salir de sección crítica

solicitar layout
solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-15">CID-12-15</a>, <a href="#cid-12-20">CID-12-20</a>, <a href="#cid-12-22">CID-12-22</a> y <a href="#cid-12-23">CID-12-23</a>.
* Es una de las funciones públicas del subsistema de superposición.

---

### <a id="cid-12-64"></a>CID-12-64

**Qué hace:**
Activa o desactiva el modo visual compacto QWERTY de la superposición.

**Cómo funciona:**
Si la sincronización no está activa, no hace nada. Si está activa, entra en la sección crítica, actualiza la bandera global de modo QWERTY y sale. Después solicita layout e invalidación para aplicar el nuevo formato visual.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
guardar nuevo estado de modo QWERTY
salir de sección crítica

solicitar layout
solicitar repintado
```

**Relaciones:**

* Usa <a href="#cid-12-04">CID-12-04</a>, <a href="#cid-12-15">CID-12-15</a>, <a href="#cid-12-22">CID-12-22</a> y <a href="#cid-12-23">CID-12-23</a>.
* Es una de las funciones públicas del subsistema de superposición.


## CID-13

La referencia <a href="#cid-13">CID-13</a> corresponde al archivo <code>superposicion_cid.h</code>. Este archivo actúa como interfaz pública de la superposición CID. Su responsabilidad principal es exponer al resto del motor las funciones necesarias para iniciar y detener el panel visual, actualizar su contenido, notificar errores visuales y controlar su visibilidad, anclaje y modo compacto QWERTY.

Dentro de <a href="#cid-13">CID-13</a> también se define el contrato entre la superposición y el resto de subsistemas del motor. Por eso aquí no aparece la lógica interna de ventana, layout, dibujo o animación, sino únicamente las declaraciones públicas que permiten interactuar con ese comportamiento sin conocer su implementación. En términos prácticos, <a href="#cid-13">CID-13</a> es la puerta pública de acceso al subsistema visual principal de CID.

### Índice interno de bloques

* <a href="#cid-13-01">CID-13-01</a>
* <a href="#cid-13-02">CID-13-02</a>
* <a href="#cid-13-03">CID-13-03</a>
* <a href="#cid-13-04">CID-13-04</a>
* <a href="#cid-13-05">CID-13-05</a>
* <a href="#cid-13-06">CID-13-06</a>
* <a href="#cid-13-07">CID-13-07</a>
* <a href="#cid-13-08">CID-13-08</a>
* <a href="#cid-13-09">CID-13-09</a>

---

### <a id="cid-13-01"></a>CID-13-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública de la superposición CID.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Con ello se evitan redefiniciones de declaraciones y conflictos por inclusión repetida.

**Pseudocódigo:**

```text
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-13">CID-13</a>.
* Asegura que <a href="#cid-13-05">CID-13-05</a> a <a href="#cid-13-09">CID-13-09</a> no se dupliquen al incluir la cabecera desde varios módulos.

---

### <a id="cid-13-02"></a>CID-13-02

**Qué hace:**
Incluye los tipos de texto usados por la interfaz pública del panel.

**Cómo funciona:**
Incorpora `<string>` para disponer de `std::wstring`, tipo usado en varias funciones públicas de la superposición para recibir texto legado y el último asentado mostrado en el panel.

**Pseudocódigo:**

```text
incluir soporte de cadenas anchas
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-13">CID-13</a>.
* Da soporte directo a <a href="#cid-13-06">CID-13-06</a>.

---

### <a id="cid-13-03"></a>CID-13-03

**Qué hace:**
Incluye los tipos base de Windows usados para ventana, instancia y rectángulos.

**Cómo funciona:**
Incorpora `<windows.h>` para disponer de tipos como `HINSTANCE` y `RECT`, necesarios en varias firmas públicas de la superposición.

**Pseudocódigo:**

```text
incluir tipos base de Windows
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-13">CID-13</a>.
* Da soporte directo a <a href="#cid-13-05">CID-13-05</a> y <a href="#cid-13-08">CID-13-08</a>.

---

### <a id="cid-13-04"></a>CID-13-04

**Qué hace:**
Incluye la definición del estado visual de bitácora consumido por la superposición.

**Cómo funciona:**
Conecta esta interfaz con `bitacora_cid.h`, desde donde se obtiene la definición completa de `EstadoVisualBitacoraCID`. Gracias a ello, la superposición puede exponer una API moderna basada en estado visual autoritativo.

**Pseudocódigo:**

```text
incluir definición del estado visual de bitácora
```

**Relaciones:**

* Da soporte directo a <a href="#cid-13-07">CID-13-07</a>.
* Enlaza esta cabecera con el módulo <code>bitacora_cid.h</code>.

---

### <a id="cid-13-05"></a>CID-13-05

**Qué hace:**
Declara el arranque y la detención de la superposición visual principal del sistema CID.

**Cómo funciona:**
Expone dos funciones públicas: `IniciarSuperposicionCID`, que recibe la instancia del proceso para crear y preparar la ventana visual, y `DetenerSuperposicionCID`, que apaga el subsistema y libera sus recursos internos.

**Pseudocódigo:**

```text
declarar función para iniciar la superposición
declarar función para detener la superposición
```

**Relaciones:**

* Usa el tipo Win32 incluido en <a href="#cid-13-03">CID-13-03</a>.
* Se implementa en <a href="#cid-12-53">CID-12-53</a> y <a href="#cid-12-57">CID-12-57</a>.
* Forma parte del ciclo de vida público del subsistema visual.

---

### <a id="cid-13-06"></a>CID-13-06

**Qué hace:**
Declara la compatibilidad temporal con el flujo heredado basado en texto simple.

**Cómo funciona:**
Expone dos funciones públicas que aceptan cadenas anchas: una para actualizar la bitácora textual heredada y otra para actualizar el último asentado visible. Estas funciones permiten mantener el panel compatible con el flujo antiguo mientras convive con la API visual moderna.

**Pseudocódigo:**

```text
declarar función para actualizar bitácora textual heredada
declarar función para actualizar último asentado textual
```

**Relaciones:**

* Usa el soporte de texto incluido en <a href="#cid-13-02">CID-13-02</a>.
* Se implementa en <a href="#cid-12-58">CID-12-58</a> y <a href="#cid-12-59">CID-12-59</a>.
* Representa la capa legacy frente a la API moderna de <a href="#cid-13-07">CID-13-07</a>.

---

### <a id="cid-13-07"></a>CID-13-07

**Qué hace:**
Declara la API visual moderna basada en estado autoritativo y notificación de error.

**Cómo funciona:**
Expone una función para sustituir el estado visual completo de la superposición mediante un `EstadoVisualBitacoraCID` y otra para activar temporalmente el efecto visual de error de acorde. Esto permite que el panel trabaje con una representación rica y autoritativa de la bitácora moderna.

**Pseudocódigo:**

```text
declarar función para fijar estado visual autoritativo
declarar función para notificar error visual de acorde
```

**Relaciones:**

* Usa el tipo incluido en <a href="#cid-13-04">CID-13-04</a>.
* Se implementa en <a href="#cid-12-60">CID-12-60</a> y <a href="#cid-12-61">CID-12-61</a>.
* Sustituye progresivamente el flujo textual heredado de <a href="#cid-13-06">CID-13-06</a>.

---

### <a id="cid-13-08"></a>CID-13-08

**Qué hace:**
Declara la API de visibilidad y posicionamiento del panel respecto al contexto activo.

**Cómo funciona:**
Expone una función para establecer si el panel debe estar visible y otra para actualizar el rectángulo de anclaje usado al colocarlo cerca del caret o del control activo. Estas llamadas no dibujan directamente, sino que comunican el estado deseado al subsistema visual.

**Pseudocódigo:**

```text
declarar función para fijar visibilidad del panel
declarar función para fijar rectángulo de anclaje
```

**Relaciones:**

* Usa el tipo `RECT` incluido en <a href="#cid-13-03">CID-13-03</a>.
* Se implementa en <a href="#cid-12-62">CID-12-62</a> y <a href="#cid-12-63">CID-12-63</a>.
* Controla parte del layout y posicionamiento ejecutado internamente por la superposición.

---

### <a id="cid-13-09"></a>CID-13-09

**Qué hace:**
Declara el cambio al modo visual compacto que sustituye el panel grande por un aviso mínimo.

**Cómo funciona:**
Expone una función pública que activa o desactiva el modo QWERTY compacto. Cuando este estado cambia, la implementación ajusta el tamaño, el contenido y el estilo visual del panel para mostrar una versión reducida.

**Pseudocódigo:**

```text
declarar función para activar o desactivar modo QWERTY compacto
```

**Relaciones:**

* Se implementa en <a href="#cid-12-64">CID-12-64</a>.
* Completa junto a <a href="#cid-13-08">CID-13-08</a> la API pública de control visual del panel.


## CID-14

La referencia <a href="#cid-14">CID-14</a> corresponde al archivo <code>calibracion_teclado.cpp</code>. Este archivo implementa el sistema de calibración persistente del teclado CID. Su responsabilidad principal es cargar, validar, mantener en memoria y guardar las asignaciones entre nombres CID y scanCodes físicos del teclado, garantizando coherencia bidireccional entre ambas direcciones de consulta.

Dentro de <a href="#cid-14">CID-14</a> también se concentra toda la lógica de persistencia en JSON UTF-8, sincronización interna, validación de nombres calibrables, detección de duplicados y serialización ordenada según el mapa oficial del sistema. Por eso aquí no solo se guardan pares nombre-scanCode, sino que se protege la integridad de la calibración antes de publicarla al resto del motor. En términos prácticos, <a href="#cid-14">CID-14</a> es la pieza que convierte una calibración de teclado en un estado persistente, validado y reutilizable por el sistema CID.

### Índice interno de bloques

* <a href="#cid-14-01">CID-14-01</a>
* <a href="#cid-14-02">CID-14-02</a>
* <a href="#cid-14-03">CID-14-03</a>
* <a href="#cid-14-04">CID-14-04</a>
* <a href="#cid-14-05">CID-14-05</a>
* <a href="#cid-14-06">CID-14-06</a>
* <a href="#cid-14-07">CID-14-07</a>
* <a href="#cid-14-08">CID-14-08</a>
* <a href="#cid-14-09">CID-14-09</a>
* <a href="#cid-14-10">CID-14-10</a>
* <a href="#cid-14-11">CID-14-11</a>
* <a href="#cid-14-12">CID-14-12</a>
* <a href="#cid-14-13">CID-14-13</a>
* <a href="#cid-14-14">CID-14-14</a>
* <a href="#cid-14-15">CID-14-15</a>
* <a href="#cid-14-16">CID-14-16</a>
* <a href="#cid-14-17">CID-14-17</a>
* <a href="#cid-14-18">CID-14-18</a>
* <a href="#cid-14-19">CID-14-19</a>
* <a href="#cid-14-20">CID-14-20</a>
* <a href="#cid-14-21">CID-14-21</a>
* <a href="#cid-14-22">CID-14-22</a>
* <a href="#cid-14-23">CID-14-23</a>
* <a href="#cid-14-24">CID-14-24</a>
* <a href="#cid-14-25">CID-14-25</a>
* <a href="#cid-14-26">CID-14-26</a>
* <a href="#cid-14-27">CID-14-27</a>
* <a href="#cid-14-28">CID-14-28</a>
* <a href="#cid-14-29">CID-14-29</a>
* <a href="#cid-14-30">CID-14-30</a>
* <a href="#cid-14-31">CID-14-31</a>
* <a href="#cid-14-32">CID-14-32</a>
* <a href="#cid-14-33">CID-14-33</a>
* <a href="#cid-14-34">CID-14-34</a>
* <a href="#cid-14-35">CID-14-35</a>

---

### <a id="cid-14-01"></a>CID-14-01

**Qué hace:**
Incluye la implementación del sistema de calibración persistente del teclado CID a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `calibracion_teclado.h`, que declara las funciones públicas del subsistema de calibración. Gracias a ello, el archivo actual puede definir la lógica real de carga, guardado, consulta y modificación de asignaciones.

**Pseudocódigo:**

```text
incluir interfaz pública de calibración de teclado
habilitar definición de sus funciones públicas
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-14">CID-14</a>.
* Da soporte directo a <a href="#cid-14-26">CID-14-26</a> a <a href="#cid-14-35">CID-14-35</a>.

---

### <a id="cid-14-02"></a>CID-14-02

**Qué hace:**
Incluye el mapa oficial de teclas CID usado para validar nombres y ordenar asignaciones.

**Cómo funciona:**
Este bloque conecta la implementación con `mapa_teclas_cid.h`, desde donde se obtienen funciones como `EsNombreTeclaCIDValido` y `OrdenTeclaCID_PorNombre`. Estas utilidades permiten decidir qué nombres son calibrables y mantener un orden oficial al devolver asignaciones.

**Pseudocódigo:**

```text
incluir mapa oficial de teclas CID
habilitar validación y orden oficial de nombres
```

**Relaciones:**

* Da soporte directo a <a href="#cid-14-13">CID-14-13</a> y <a href="#cid-14-35">CID-14-35</a>.
* Enlaza con el módulo <code>mapa_teclas_cid.h</code>.

---

### <a id="cid-14-03"></a>CID-14-03

**Qué hace:**
Incluye utilidades estándar para ordenación, archivo, mapas, regex y streams.

**Cómo funciona:**
Este bloque habilita contenedores ordenados, lectura y escritura de archivos, expresiones regulares y flujos de texto necesarios para persistencia y parsing del JSON de calibración. No contiene lógica ejecutable, pero prepara el entorno de compilación requerido por el resto del archivo.

**Pseudocódigo:**

```text
incluir soporte de ordenación
incluir soporte de archivos
incluir soporte de mapas
incluir soporte de regex
incluir soporte de streams
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-14">CID-14</a>.
* Da soporte indirecto a <a href="#cid-14-11">CID-14-11</a>, <a href="#cid-14-12">CID-14-12</a>, <a href="#cid-14-20">CID-14-20</a> y <a href="#cid-14-25">CID-14-25</a>.

---

### <a id="cid-14-04"></a>CID-14-04

**Qué hace:**
Abre un espacio interno anónimo para encapsular el estado y los helpers privados de calibración.

**Cómo funciona:**
Agrupa en un `namespace` anónimo toda la lógica que no debe exponerse fuera de este archivo: estado global, utilidades de codificación, parsing JSON, helpers de limpieza y serialización. Así se limita su visibilidad al propio módulo.

**Pseudocódigo:**

```text
abrir espacio interno privado del módulo
encapsular estado y helpers no públicos
```

**Relaciones:**

* Contiene internamente <a href="#cid-14-05">CID-14-05</a> a <a href="#cid-14-25">CID-14-25</a>.
* Separa la implementación privada de las funciones públicas definidas en <a href="#cid-14-26">CID-14-26</a> a <a href="#cid-14-35">CID-14-35</a>.

---

### <a id="cid-14-05"></a>CID-14-05

**Qué hace:**
Define el estado global de calibración con sincronización y mapas bidireccionales nombre-scanCode.

**Cómo funciona:**
Declara una estructura interna que contiene una sección crítica, banderas de inicialización y de carga, y dos mapas ordenados: uno que asocia nombre CID a scanCode y otro inverso que asocia scanCode a nombre CID. Esto permite mantener coherencia y consultas en ambos sentidos.

**Pseudocódigo:**

```text
definir estructura de estado global
guardar sección crítica y banderas
guardar mapa nombre a scanCode
guardar mapa scanCode a nombre
```

**Relaciones:**

* Su instancia única se declara en <a href="#cid-14-06">CID-14-06</a>.
* Es usada por casi todo el módulo, especialmente <a href="#cid-14-07">CID-14-07</a>, <a href="#cid-14-15">CID-14-15</a>, <a href="#cid-14-16">CID-14-16</a>, <a href="#cid-14-26">CID-14-26</a> y <a href="#cid-14-35">CID-14-35</a>.

---

### <a id="cid-14-06"></a>CID-14-06

**Qué hace:**
Declara la instancia global única del estado de calibración del teclado.

**Cómo funciona:**
Crea una sola variable global `g_state` del tipo `CalibracionTecladoState`. Esa instancia centraliza toda la información persistente y temporal del subsistema de calibración.

**Pseudocódigo:**

```text
crear instancia global única del estado de calibración
```

**Relaciones:**

* Usa la estructura definida en <a href="#cid-14-05">CID-14-05</a>.
* Es utilizada por todos los helpers y funciones públicas del módulo.

---

### <a id="cid-14-07"></a>CID-14-07

**Qué hace:**
Inicializa la sección crítica interna la primera vez que se necesita.

**Cómo funciona:**
Comprueba la bandera `csIniciado` del estado global. Si todavía es falsa, llama a `InitializeCriticalSection` sobre la sección crítica y marca la bandera como verdadera. Así evita reinicializaciones repetidas.

**Pseudocódigo:**

```text
si la sección crítica no está iniciada:
    inicializar sección crítica
    marcarla como iniciada
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-14-05">CID-14-05</a>.
* Es llamado desde <a href="#cid-14-26">CID-14-26</a> a <a href="#cid-14-35">CID-14-35</a>.

---

### <a id="cid-14-08"></a>CID-14-08

**Qué hace:**
Envía mensajes de depuración del módulo de calibración al visor de salida de Windows.

**Cómo funciona:**
Recibe una cadena ancha, le añade un salto de línea y la envía mediante `OutputDebugStringW`. Con ello unifica el registro interno del subsistema de calibración.

**Pseudocódigo:**

```text
añadir salto de línea al mensaje
enviar mensaje al depurador de Windows
```

**Relaciones:**

* Es usado por <a href="#cid-14-26">CID-14-26</a> y <a href="#cid-14-27">CID-14-27</a>.

---

### <a id="cid-14-09"></a>CID-14-09

**Qué hace:**
Convierte una cadena estrecha UTF-8 a Unicode.

**Cómo funciona:**
Si la cadena de entrada está vacía devuelve una cadena ancha vacía. En caso contrario, primero calcula cuántos caracteres Unicode necesita, reserva el tamaño adecuado y realiza la conversión con `MultiByteToWideChar`.

**Pseudocódigo:**

```text
si la cadena está vacía:
    devolver vacío

calcular tamaño Unicode necesario
si el tamaño no es válido:
    devolver vacío

reservar salida
convertir UTF-8 a Unicode
devolver resultado
```

**Relaciones:**

* Es usado por <a href="#cid-14-11">CID-14-11</a>.

---

### <a id="cid-14-10"></a>CID-14-10

**Qué hace:**
Convierte una cadena Unicode a UTF-8 para persistencia en archivo.

**Cómo funciona:**
Si la entrada está vacía devuelve una cadena estrecha vacía. Si no, calcula el tamaño UTF-8 necesario, reserva la salida y realiza la conversión con `WideCharToMultiByte`.

**Pseudocódigo:**

```text
si la cadena está vacía:
    devolver vacío

calcular tamaño UTF-8 necesario
si el tamaño no es válido:
    devolver vacío

reservar salida
convertir Unicode a UTF-8
devolver resultado
```

**Relaciones:**

* Es usado por <a href="#cid-14-12">CID-14-12</a>.

---

### <a id="cid-14-11"></a>CID-14-11

**Qué hace:**
Lee un archivo de texto UTF-8, elimina BOM si existe y devuelve su contenido Unicode.

**Cómo funciona:**
Abre el archivo en binario, lee todos sus bytes y cierra el flujo. Si detecta el BOM UTF-8 al inicio, lo elimina. Después convierte el contenido restante a Unicode mediante `NarrowToWideUtf8`. Si el archivo no puede abrirse, devuelve error.

**Pseudocódigo:**

```text
abrir archivo en binario
si falla:
    devolver error

leer todos los bytes
cerrar archivo

si existe BOM UTF-8:
    eliminarlo

convertir bytes a Unicode
devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-14-09">CID-14-09</a>.
* Es llamado desde <a href="#cid-14-26">CID-14-26</a>.

---

### <a id="cid-14-12"></a>CID-14-12

**Qué hace:**
Escribe un archivo de texto UTF-8 con BOM a partir de una cadena Unicode.

**Cómo funciona:**
Abre el archivo en modo binario truncado. Si falla, devuelve error. Si tiene éxito, convierte el texto a UTF-8, escribe primero el BOM estándar y luego el contenido UTF-8 completo.

**Pseudocódigo:**

```text
abrir archivo en modo escritura binaria truncada
si falla:
    devolver error

convertir texto Unicode a UTF-8
escribir BOM UTF-8
escribir contenido UTF-8
cerrar archivo
devolver éxito
```

**Relaciones:**

* Usa <a href="#cid-14-10">CID-14-10</a>.
* Es llamado desde <a href="#cid-14-27">CID-14-27</a>.

---

### <a id="cid-14-13"></a>CID-14-13

**Qué hace:**
Decide si un nombre CID puede participar en calibración persistente.

**Cómo funciona:**
Rechaza nombres nulos o vacíos, excluye expresamente `CID_KEY` y acepta el resto solo si `EsNombreTeclaCIDValido` confirma que pertenecen al conjunto oficial de nombres CID válidos.

**Pseudocódigo:**

```text
si el nombre es nulo o vacío:
    devolver falso
si el nombre es CID_KEY:
    devolver falso
devolver si el nombre CID es válido
```

**Relaciones:**

* Usa el mapa oficial incluido en <a href="#cid-14-02">CID-14-02</a>.
* Es llamado desde <a href="#cid-14-16">CID-14-16</a> y <a href="#cid-14-21">CID-14-21</a>.

---

### <a id="cid-14-14"></a>CID-14-14

**Qué hace:**
Devuelve la lista ordenada oficial de nombres CID que deben guardarse en calibración.

**Cómo funciona:**
Construye y devuelve un vector con la secuencia fija de teclas calibrables del sistema: familias `I`, `C`, `D` y `AUX_CID`. Esta lista define el orden de serialización canónico del archivo de calibración.

**Pseudocódigo:**

```text
crear lista ordenada de nombres calibrables
devolverla
```

**Relaciones:**

* Es usada por <a href="#cid-14-25">CID-14-25</a>.
* Define el orden persistente del JSON construido por el módulo.

---

### <a id="cid-14-15"></a>CID-14-15

**Qué hace:**
Limpia completamente el estado interno de calibración y marca el sistema como no cargado.

**Cómo funciona:**
Vacía ambos mapas bidireccionales y pone la bandera `cargada` a falso. Está pensada para ejecutarse bajo bloqueo ya adquirido.

**Pseudocódigo:**

```text
vaciar mapa nombre a scanCode
vaciar mapa scanCode a nombre
marcar calibración como no cargada
```

**Relaciones:**

* Usa el estado global definido en <a href="#cid-14-05">CID-14-05</a>.
* Es llamada desde <a href="#cid-14-24">CID-14-24</a> y <a href="#cid-14-28">CID-14-28</a>.

---

### <a id="cid-14-16"></a>CID-14-16

**Qué hace:**
Establece una asignación nombre-scanCode manteniendo coherencia bidireccional sin duplicados.

**Cómo funciona:**
Primero valida que el nombre sea calibrable y que el scanCode esté dentro de rango. Después elimina cualquier asociación previa del mismo nombre y cualquier asociación previa del mismo scanCode, evitando duplicados en ambos sentidos. Finalmente inserta la nueva pareja y marca el sistema como cargado.

**Pseudocódigo:**

```text
si el nombre no es calibrable:
    devolver falso
si el scanCode es inválido:
    devolver falso

eliminar asociación previa del mismo nombre
eliminar asociación previa del mismo scanCode

guardar nueva asociación nombre a scanCode
guardar nueva asociación scanCode a nombre
marcar calibración como cargada
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-14-17">CID-14-17</a> y <a href="#cid-14-18">CID-14-18</a>.
* Usa <a href="#cid-14-13">CID-14-13</a> y el estado de <a href="#cid-14-05">CID-14-05</a>.
* Es llamada desde <a href="#cid-14-24">CID-14-24</a> y <a href="#cid-14-30">CID-14-30</a>.

---

### <a id="cid-14-17"></a>CID-14-17

**Qué hace:**
Si el nombre ya existía, elimina antes su asociación inversa anterior.

**Cómo funciona:**
Busca el nombre CID en el mapa `nombreAScan`. Si lo encuentra, recupera el scanCode antiguo, elimina la entrada inversa correspondiente del mapa `scanANombre` y luego borra la entrada directa del nombre.

**Pseudocódigo:**

```text
buscar nombre en mapa nombre a scanCode
si existe:
    recuperar scanCode antiguo
    borrar asociación inversa
    borrar asociación directa
```

**Relaciones:**

* Forma parte de <a href="#cid-14-16">CID-14-16</a>.
* Usa los mapas bidireccionales del estado definido en <a href="#cid-14-05">CID-14-05</a>.

---

### <a id="cid-14-18"></a>CID-14-18

**Qué hace:**
Si el scanCode ya estaba asignado, elimina la asociación previa del nombre antiguo.

**Cómo funciona:**
Busca el scanCode en el mapa `scanANombre`. Si lo encuentra, recupera el nombre antiguo, elimina la entrada directa correspondiente en `nombreAScan` y luego borra la asociación inversa del scanCode.

**Pseudocódigo:**

```text
buscar scanCode en mapa scanCode a nombre
si existe:
    recuperar nombre antiguo
    borrar asociación directa del nombre antiguo
    borrar asociación inversa del scanCode
```

**Relaciones:**

* Forma parte de <a href="#cid-14-16">CID-14-16</a>.
* Usa los mapas bidireccionales del estado definido en <a href="#cid-14-05">CID-14-05</a>.

---

### <a id="cid-14-19"></a>CID-14-19

**Qué hace:**
Escapa una cadena Unicode para poder escribirla con seguridad dentro de JSON.

**Cómo funciona:**
Recorre carácter a carácter la cadena de entrada y sustituye barras invertidas, comillas dobles y ciertos caracteres de control por sus secuencias escapadas JSON. El resto de caracteres se copian tal cual.

**Pseudocódigo:**

```text
crear salida vacía
para cada carácter:
    si es barra invertida:
        añadir escape correspondiente
    si es comilla:
        añadir escape correspondiente
    si es retorno, salto o tabulación:
        añadir escape correspondiente
    en otro caso:
        copiar carácter
devolver resultado
```

**Relaciones:**

* Es usada por <a href="#cid-14-25">CID-14-25</a>.

---

### <a id="cid-14-20"></a>CID-14-20

**Qué hace:**
Parsea el JSON de calibración, valida asignaciones y las aplica al estado global.

**Cómo funciona:**
Busca primero el bloque `"keys"` mediante regex. Después extrae pares nombre-scanCode, filtra los nombres calibrables, valida rangos, comprueba que exista al menos una asignación, detecta scanCodes duplicados y, si todo es correcto, sustituye el estado global por las asignaciones validadas.

**Pseudocódigo:**

```text
buscar bloque keys en el JSON
si no existe:
    devolver error

extraer pares nombre-scanCode
filtrar nombres calibrables
validar scanCodes
si no queda ninguna asignación:
    devolver error

detectar scanCodes duplicados
si hay duplicados:
    devolver error

limpiar estado global
aplicar asignaciones validadas
marcar calibración como cargada
devolver verdadero
```

**Relaciones:**

* Contiene internamente <a href="#cid-14-21">CID-14-21</a> a <a href="#cid-14-24">CID-14-24</a>.
* Es llamada desde <a href="#cid-14-26">CID-14-26</a>.

---

### <a id="cid-14-21"></a>CID-14-21

**Qué hace:**
Extrae pares nombre-scanCode válidos desde el bloque JSON `keys`.

**Cómo funciona:**
Recorre las coincidencias de la regex que detecta entradas JSON simples tipo `"NOMBRE": número`. Para cada coincidencia convierte el número a `DWORD`, descarta nombres no calibrables y valida el rango del scanCode antes de guardar la pareja en un mapa temporal.

**Pseudocódigo:**

```text
recorrer pares nombre-scanCode del bloque keys
para cada par:
    leer nombre
    leer scanCode
    si el nombre no es calibrable:
        ignorarlo
    si el scanCode es inválido:
        devolver error
    guardar par en mapa temporal
```

**Relaciones:**

* Usa <a href="#cid-14-13">CID-14-13</a>.
* Forma parte de <a href="#cid-14-20">CID-14-20</a>.

---

### <a id="cid-14-22"></a>CID-14-22

**Qué hace:**
Falla si el JSON no aporta ninguna asignación calibrable válida.

**Cómo funciona:**
Comprueba si el mapa temporal de asignaciones ha quedado vacío tras la extracción y el filtrado. Si lo está, produce un error y aborta el parseo.

**Pseudocódigo:**

```text
si no hay asignaciones válidas extraídas:
    devolver error
```

**Relaciones:**

* Forma parte de <a href="#cid-14-20">CID-14-20</a>.
* Depende del resultado de <a href="#cid-14-21">CID-14-21</a>.

---

### <a id="cid-14-23"></a>CID-14-23

**Qué hace:**
Detecta scanCodes duplicados entre distintas teclas CID antes de aplicar el estado.

**Cómo funciona:**
Recorre las asignaciones temporales ya validadas y construye un mapa auxiliar de scanCodes vistos. Si encuentra un scanCode repetido asociado a otro nombre, produce un error detallado indicando ambas teclas en conflicto.

**Pseudocódigo:**

```text
crear mapa de scanCodes vistos
para cada asignación temporal:
    si el scanCode ya fue visto:
        devolver error indicando conflicto
    marcar scanCode como visto
```

**Relaciones:**

* Forma parte de <a href="#cid-14-20">CID-14-20</a>.
* Precede a <a href="#cid-14-24">CID-14-24</a>.

---

### <a id="cid-14-24"></a>CID-14-24

**Qué hace:**
Sustituye el estado global por las asignaciones temporales ya validadas.

**Cómo funciona:**
Limpia primero todo el estado global de calibración. Después recorre el mapa temporal validado y aplica cada asignación mediante `EstablecerAsignacionNoLock`. Finalmente marca el sistema como cargado.

**Pseudocódigo:**

```text
limpiar estado global
para cada asignación temporal validada:
    establecer asignación en estado global
marcar calibración como cargada
```

**Relaciones:**

* Usa <a href="#cid-14-15">CID-14-15</a> y <a href="#cid-14-16">CID-14-16</a>.
* Forma parte de <a href="#cid-14-20">CID-14-20</a>.

---

### <a id="cid-14-25"></a>CID-14-25

**Qué hace:**
Construye el JSON completo de calibración a partir del estado interno actual.

**Cómo funciona:**
Crea un `wstringstream`, escribe la estructura JSON base con versión y bloque `keys`, obtiene la lista ordenada oficial de nombres calibrables y recorre esa lista. Para cada nombre presente en el estado global, escribe la entrada JSON correspondiente usando escape seguro de nombre. El resultado final es un texto Unicode listo para persistirse.

**Pseudocódigo:**

```text
crear stream de salida JSON
escribir cabecera JSON
obtener lista ordenada de nombres calibrables

para cada nombre en orden oficial:
    si el nombre tiene asignación:
        escribir par JSON nombre-scanCode

cerrar estructura JSON
devolver texto final
```

**Relaciones:**

* Usa <a href="#cid-14-14">CID-14-14</a>, <a href="#cid-14-19">CID-14-19</a> y el estado definido en <a href="#cid-14-05">CID-14-05</a>.
* Es llamada desde <a href="#cid-14-27">CID-14-27</a>.

---

### <a id="cid-14-26"></a>CID-14-26

**Qué hace:**
Carga la calibración desde JSON, la valida y la publica en el estado global del sistema.

**Cómo funciona:**
Asegura primero la existencia de la sección crítica. Después lee el archivo como texto Unicode UTF-8. Si la lectura tiene éxito, entra en la sección crítica y delega el parseo y validación al helper correspondiente. Si todo sale bien, deja una traza de depuración con la ruta cargada.

**Pseudocódigo:**

```text
asegurar sección crítica
leer archivo de calibración
si falla:
    devolver error

entrar en sección crítica
parsear y validar JSON
salir de sección crítica

si falla el parseo:
    devolver error

escribir log de carga correcta
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a>, <a href="#cid-14-11">CID-14-11</a>, <a href="#cid-14-20">CID-14-20</a> y <a href="#cid-14-08">CID-14-08</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-27"></a>CID-14-27

**Qué hace:**
Guarda la calibración actual en disco serializándola como JSON UTF-8 con BOM.

**Cómo funciona:**
Asegura la sección crítica y entra en ella. Si no existen asignaciones en memoria, devuelve error. Si existen, construye el JSON de calibración, sale de la sección crítica y lo escribe a disco en UTF-8 con BOM. Si la escritura tiene éxito, registra una traza de guardado correcto.

**Pseudocódigo:**

```text
asegurar sección crítica
entrar en sección crítica

si no hay asignaciones:
    salir de sección crítica
    devolver error

construir JSON de calibración
salir de sección crítica

escribir archivo UTF-8 con BOM
si falla:
    devolver falso

escribir log de guardado correcto
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a>, <a href="#cid-14-25">CID-14-25</a>, <a href="#cid-14-12">CID-14-12</a> y <a href="#cid-14-08">CID-14-08</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-28"></a>CID-14-28

**Qué hace:**
Limpia completamente la calibración cargada actualmente en memoria.

**Cómo funciona:**
Asegura la sección crítica, entra en ella, vacía el estado global mediante el helper de limpieza y sale del bloqueo. No actúa sobre disco, solo sobre el estado en memoria.

**Pseudocódigo:**

```text
asegurar sección crítica
entrar en sección crítica
limpiar estado de calibración en memoria
salir de sección crítica
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a> y <a href="#cid-14-15">CID-14-15</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-29"></a>CID-14-29

**Qué hace:**
Informa si existe una calibración cargada y con asignaciones reales en memoria.

**Cómo funciona:**
Asegura la sección crítica, entra en ella y comprueba dos condiciones: que la bandera `cargada` esté activa y que el mapa de nombre a scanCode no esté vacío. Devuelve el resultado de esa conjunción.

**Pseudocódigo:**

```text
asegurar sección crítica
entrar en sección crítica
comprobar si está cargada y hay asignaciones
salir de sección crítica
devolver resultado
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a> y el estado definido en <a href="#cid-14-05">CID-14-05</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-30"></a>CID-14-30

**Qué hace:**
Establece o sustituye la asignación de una tecla CID hacia un scanCode concreto.

**Cómo funciona:**
Rechaza primero nombres nulos. Después asegura la sección crítica, entra en ella y delega la operación en el helper interno que mantiene la coherencia bidireccional. Finalmente devuelve si la operación tuvo éxito.

**Pseudocódigo:**

```text
si el nombre es nulo:
    devolver falso

asegurar sección crítica
entrar en sección crítica
intentar establecer asignación
salir de sección crítica
devolver resultado
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a> y <a href="#cid-14-16">CID-14-16</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-31"></a>CID-14-31

**Qué hace:**
Elimina la asignación existente de una tecla CID por su nombre.

**Cómo funciona:**
Rechaza nombres nulos o vacíos. Después asegura la sección crítica, entra en ella, busca el nombre en el mapa directo y, si existe, elimina tanto la asociación directa como la inversa. Finalmente recalcula la bandera `cargada` según si siguen quedando asignaciones.

**Pseudocódigo:**

```text
si el nombre es nulo o vacío:
    devolver falso

asegurar sección crítica
entrar en sección crítica

buscar nombre en mapa directo
si no existe:
    salir de sección crítica
    devolver falso

recuperar scanCode asociado
borrar asociación directa
borrar asociación inversa
actualizar bandera de cargada
salir de sección crítica
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a> y el estado definido en <a href="#cid-14-05">CID-14-05</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-32"></a>CID-14-32

**Qué hace:**
Comprueba si un scanCode ya está asociado a alguna tecla CID calibrada.

**Cómo funciona:**
Rechaza scanCodes fuera del rango manejable. Si el valor es válido, asegura la sección crítica, entra en ella y consulta el mapa inverso `scanANombre`, devolviendo si la clave existe.

**Pseudocódigo:**

```text
si el scanCode está fuera de rango:
    devolver falso

asegurar sección crítica
entrar en sección crítica
comprobar si existe en mapa inverso
salir de sección crítica
devolver resultado
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a> y el mapa inverso del estado definido en <a href="#cid-14-05">CID-14-05</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-33"></a>CID-14-33

**Qué hace:**
Devuelve el nombre CID asociado a un scanCode calibrado si existe actualmente.

**Cómo funciona:**
Rechaza scanCodes fuera de rango. Si el valor es válido, asegura la sección crítica, entra en ella y busca el scanCode en el mapa inverso. Si no existe, devuelve `nullptr`. Si existe, devuelve el puntero al buffer interno de la cadena almacenada.

**Pseudocódigo:**

```text
si el scanCode está fuera de rango:
    devolver nulo

asegurar sección crítica
entrar en sección crítica
buscar scanCode en mapa inverso
si no existe:
    salir de sección crítica
    devolver nulo

obtener puntero al nombre asociado
salir de sección crítica
devolver puntero
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a> y el mapa inverso del estado definido en <a href="#cid-14-05">CID-14-05</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-34"></a>CID-14-34

**Qué hace:**
Obtiene el scanCode asociado a un nombre CID calibrado concreto.

**Cómo funciona:**
Inicializa la salida a cero y rechaza nombres nulos o vacíos. Después asegura la sección crítica, entra en ella, consulta el mapa directo y, si encuentra el nombre, escribe el scanCode asociado en la variable de salida y devuelve `true`.

**Pseudocódigo:**

```text
poner salida a cero
si el nombre es nulo o vacío:
    devolver falso

asegurar sección crítica
entrar en sección crítica
buscar nombre en mapa directo
si no existe:
    salir de sección crítica
    devolver falso

copiar scanCode a salida
salir de sección crítica
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a> y el mapa directo del estado definido en <a href="#cid-14-05">CID-14-05</a>.
* Es una de las funciones públicas del subsistema de calibración.

---

### <a id="cid-14-35"></a>CID-14-35

**Qué hace:**
Devuelve todas las asignaciones calibradas ordenadas según el orden oficial del mapa CID.

**Cómo funciona:**
Asegura la sección crítica, entra en ella y copia todas las asignaciones del mapa directo a un vector de pares. Después sale del bloqueo y ordena ese vector usando `OrdenTeclaCID_PorNombre` para garantizar un orden externo coherente con el sistema oficial de teclas.

**Pseudocódigo:**

```text
asegurar sección crítica
entrar en sección crítica

crear vector de salida
copiar asignaciones del mapa directo al vector

salir de sección crítica

ordenar vector según orden oficial CID
devolver vector
```

**Relaciones:**

* Usa <a href="#cid-14-07">CID-14-07</a>, el estado definido en <a href="#cid-14-05">CID-14-05</a> y el mapa oficial incluido en <a href="#cid-14-02">CID-14-02</a>.
* Es una de las funciones públicas del subsistema de calibración.


## CID-15

La referencia <a href="#cid-15">CID-15</a> corresponde al archivo <code>calibracion_teclado.h</code>. Este archivo actúa como interfaz pública del sistema de calibración del teclado CID. Su responsabilidad principal es exponer al resto del motor las funciones necesarias para cargar, guardar, limpiar, consultar y modificar la calibración persistente que relaciona nombres CID con scanCodes físicos.

Dentro de <a href="#cid-15">CID-15</a> también se fija el contrato entre el subsistema de calibración y el resto de módulos del sistema. Por eso aquí no aparece la lógica interna de JSON, sincronización, validación o mapas bidireccionales, sino únicamente las declaraciones públicas necesarias para operar con la calibración ya desde fuera de su implementación. En términos prácticos, <a href="#cid-15">CID-15</a> es la puerta pública de acceso al estado persistente del teclado calibrado.

### Índice interno de bloques

* <a href="#cid-15-01">CID-15-01</a>
* <a href="#cid-15-02">CID-15-02</a>
* <a href="#cid-15-03">CID-15-03</a>
* <a href="#cid-15-04">CID-15-04</a>
* <a href="#cid-15-05">CID-15-05</a>
* <a href="#cid-15-06">CID-15-06</a>
* <a href="#cid-15-07">CID-15-07</a>
* <a href="#cid-15-08">CID-15-08</a>

---

### <a id="cid-15-01"></a>CID-15-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública de calibración del teclado CID.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Así se evitan redefiniciones de declaraciones y conflictos por inclusión repetida.

**Pseudocódigo:**

```text
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-15">CID-15</a>.
* Asegura que <a href="#cid-15-04">CID-15-04</a> a <a href="#cid-15-08">CID-15-08</a> no se dupliquen al incluir la cabecera desde distintos módulos.

---

### <a id="cid-15-02"></a>CID-15-02

**Qué hace:**
Incluye los tipos base de Windows usados por la API pública de calibración.

**Cómo funciona:**
Incorpora `<windows.h>` para disponer de tipos como `DWORD`, empleados en las firmas públicas que representan scanCodes y otros valores Win32 asociados a la calibración.

**Pseudocódigo:**

```text
incluir tipos base de Windows
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-15">CID-15</a>.
* Da soporte directo a <a href="#cid-15-06">CID-15-06</a>, <a href="#cid-15-07">CID-15-07</a> y <a href="#cid-15-08">CID-15-08</a>.

---

### <a id="cid-15-03"></a>CID-15-03

**Qué hace:**
Incluye tipos de texto y contenedores usados por la interfaz de calibración.

**Cómo funciona:**
Incorpora `<string>` para disponer de `std::wstring` y `<vector>` para poder declarar listas ordenadas de asignaciones. No contiene lógica ejecutable, pero prepara las dependencias mínimas necesarias para compilar esta interfaz.

**Pseudocódigo:**

```text
incluir soporte de cadenas anchas
incluir soporte de vectores
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-15">CID-15</a>.
* Da soporte directo a <a href="#cid-15-04">CID-15-04</a> y <a href="#cid-15-08">CID-15-08</a>.

---

### <a id="cid-15-04"></a>CID-15-04

**Qué hace:**
Declara la carga y el guardado del archivo JSON de calibración del teclado.

**Cómo funciona:**
Expone dos funciones públicas: `CargarCalibracionTeclado`, que lee y valida un archivo JSON desde una ruta dada, y `GuardarCalibracionTeclado`, que serializa el estado actual de calibración a disco. Ambas aceptan opcionalmente un buffer de error para informar del motivo de fallo.

**Pseudocódigo:**

```text
declarar función para cargar calibración desde JSON
declarar función para guardar calibración a JSON
```

**Relaciones:**

* Usa `std::wstring` incluido en <a href="#cid-15-03">CID-15-03</a>.
* Se implementa en <a href="#cid-14-26">CID-14-26</a> y <a href="#cid-14-27">CID-14-27</a>.
* Forma parte del ciclo de persistencia pública del subsistema de calibración.

---

### <a id="cid-15-05"></a>CID-15-05

**Qué hace:**
Declara la limpieza y la consulta del estado global de calibración cargado en memoria.

**Cómo funciona:**
Expone una función para vaciar por completo la calibración actualmente residente en memoria y otra para consultar si existe una calibración real cargada con asignaciones válidas.

**Pseudocódigo:**

```text
declarar función para limpiar calibración en memoria
declarar función para consultar si hay calibración cargada
```

**Relaciones:**

* Se implementa en <a href="#cid-14-28">CID-14-28</a> y <a href="#cid-14-29">CID-14-29</a>.
* Completa el control público del estado global de calibración junto a <a href="#cid-15-04">CID-15-04</a>.

---

### <a id="cid-15-06"></a>CID-15-06

**Qué hace:**
Declara la creación, sustitución y eliminación de asignaciones entre nombre CID y scanCode.

**Cómo funciona:**
Expone una función para establecer o reemplazar una asignación concreta de tecla CID a scanCode, y otra para quitar una asignación existente a partir del nombre CID. Estas operaciones permiten modificar en memoria la calibración activa.

**Pseudocódigo:**

```text
declarar función para establecer o sustituir asignación
declarar función para quitar asignación por nombre CID
```

**Relaciones:**

* Usa `DWORD` incluido en <a href="#cid-15-02">CID-15-02</a>.
* Se implementa en <a href="#cid-14-30">CID-14-30</a> y <a href="#cid-14-31">CID-14-31</a>.
* Forma parte de la API pública de edición de calibración.

---

### <a id="cid-15-07"></a>CID-15-07

**Qué hace:**
Declara las consultas de existencia y resolución entre scanCode y nombre CID.

**Cómo funciona:**
Expone tres funciones públicas: una para comprobar si un scanCode ya está calibrado, otra para obtener el nombre CID asociado a un scanCode y otra para resolver el scanCode asociado a un nombre CID concreto.

**Pseudocódigo:**

```text
declarar función para comprobar si existe scanCode calibrado
declarar función para obtener nombre CID desde scanCode
declarar función para obtener scanCode desde nombre CID
```

**Relaciones:**

* Usa `DWORD` incluido en <a href="#cid-15-02">CID-15-02</a>.
* Se implementa en <a href="#cid-14-32">CID-14-32</a>, <a href="#cid-14-33">CID-14-33</a> y <a href="#cid-14-34">CID-14-34</a>.
* Representa la API pública de consulta bidireccional del subsistema de calibración.

---

### <a id="cid-15-08"></a>CID-15-08

**Qué hace:**
Declara la obtención ordenada de todas las asignaciones calibradas para UI o depuración.

**Cómo funciona:**
Expone una función pública que devuelve un vector de pares `nombre CID / scanCode`, ya ordenado según el criterio oficial del sistema. Este resultado está pensado para alimentar interfaces de configuración, diagnósticos o salidas de depuración.

**Pseudocódigo:**

```text
declarar función para obtener todas las asignaciones calibradas ordenadas
```

**Relaciones:**

* Usa `std::vector`, `std::pair` y `std::wstring` soportados por <a href="#cid-15-03">CID-15-03</a> y `DWORD` de <a href="#cid-15-02">CID-15-02</a>.
* Se implementa en <a href="#cid-14-35">CID-14-35</a>.
* Completa la API pública del subsistema de calibración con una vista global ordenada del estado actual.


## CID-16

La referencia <a href="#cid-16">CID-16</a> corresponde al archivo <code>setup_teclado_cid.cpp</code>. Este archivo implementa el asistente completo de configuración del teclado CID. Su responsabilidad principal es guiar al usuario por el proceso de calibración inicial, mostrar un teclado visual interactivo, capturar scanCodes físicos, construir asignaciones nombre CID → scanCode, guardarlas en disco y permitir una fase final de prueba y corrección.

Dentro de <a href="#cid-16">CID-16</a> también se concentra toda la lógica visual y de flujo del asistente: creación de ventana, cabecera explicativa, render del teclado, detección de hover y clic, reasignación manual, navegación entre pasos, reinicio completo de calibración y traducción del resultado final a éxito o error. Por eso aquí no solo se captura teclado, sino que se organiza una experiencia guiada completa para dejar listo el mapa físico del usuario. En términos prácticos, <a href="#cid-16">CID-16</a> es la pieza que convierte el primer arranque del sistema en una calibración usable, persistente y corregible.

### Índice interno de bloques

* <a href="#cid-16-01">CID-16-01</a>
* <a href="#cid-16-02">CID-16-02</a>
* <a href="#cid-16-03">CID-16-03</a>
* <a href="#cid-16-04">CID-16-04</a>
* <a href="#cid-16-05">CID-16-05</a>
* <a href="#cid-16-06">CID-16-06</a>
* <a href="#cid-16-07">CID-16-07</a>
* <a href="#cid-16-08">CID-16-08</a>
* <a href="#cid-16-09">CID-16-09</a>
* <a href="#cid-16-10">CID-16-10</a>
* <a href="#cid-16-11">CID-16-11</a>
* <a href="#cid-16-12">CID-16-12</a>
* <a href="#cid-16-13">CID-16-13</a>
* <a href="#cid-16-14">CID-16-14</a>
* <a href="#cid-16-15">CID-16-15</a>
* <a href="#cid-16-16">CID-16-16</a>
* <a href="#cid-16-17">CID-16-17</a>
* <a href="#cid-16-18">CID-16-18</a>
* <a href="#cid-16-19">CID-16-19</a>
* <a href="#cid-16-20">CID-16-20</a>
* <a href="#cid-16-21">CID-16-21</a>
* <a href="#cid-16-22">CID-16-22</a>
* <a href="#cid-16-23">CID-16-23</a>
* <a href="#cid-16-24">CID-16-24</a>
* <a href="#cid-16-25">CID-16-25</a>
* <a href="#cid-16-26">CID-16-26</a>
* <a href="#cid-16-27">CID-16-27</a>
* <a href="#cid-16-28">CID-16-28</a>
* <a href="#cid-16-29">CID-16-29</a>
* <a href="#cid-16-30">CID-16-30</a>
* <a href="#cid-16-31">CID-16-31</a>
* <a href="#cid-16-32">CID-16-32</a>
* <a href="#cid-16-33">CID-16-33</a>
* <a href="#cid-16-34">CID-16-34</a>
* <a href="#cid-16-35">CID-16-35</a>
* <a href="#cid-16-36">CID-16-36</a>
* <a href="#cid-16-37">CID-16-37</a>
* <a href="#cid-16-38">CID-16-38</a>
* <a href="#cid-16-39">CID-16-39</a>
* <a href="#cid-16-40">CID-16-40</a>
* <a href="#cid-16-41">CID-16-41</a>
* <a href="#cid-16-42">CID-16-42</a>
* <a href="#cid-16-43">CID-16-43</a>
* <a href="#cid-16-44">CID-16-44</a>
* <a href="#cid-16-45">CID-16-45</a>
* <a href="#cid-16-46">CID-16-46</a>
* <a href="#cid-16-47">CID-16-47</a>
* <a href="#cid-16-48">CID-16-48</a>
* <a href="#cid-16-49">CID-16-49</a>
* <a href="#cid-16-50">CID-16-50</a>
* <a href="#cid-16-51">CID-16-51</a>
* <a href="#cid-16-52">CID-16-52</a>
* <a href="#cid-16-53">CID-16-53</a>
* <a href="#cid-16-54">CID-16-54</a>
* <a href="#cid-16-55">CID-16-55</a>
* <a href="#cid-16-56">CID-16-56</a>
* <a href="#cid-16-57">CID-16-57</a>
* <a href="#cid-16-58">CID-16-58</a>
* <a href="#cid-16-59">CID-16-59</a>
* <a href="#cid-16-60">CID-16-60</a>
* <a href="#cid-16-61">CID-16-61</a>
* <a href="#cid-16-62">CID-16-62</a>
* <a href="#cid-16-63">CID-16-63</a>
* <a href="#cid-16-64">CID-16-64</a>
* <a href="#cid-16-65">CID-16-65</a>
* <a href="#cid-16-66">CID-16-66</a>
* <a href="#cid-16-67">CID-16-67</a>
* <a href="#cid-16-68">CID-16-68</a>
* <a href="#cid-16-69">CID-16-69</a>
* <a href="#cid-16-70">CID-16-70</a>
* <a href="#cid-16-71">CID-16-71</a>
* <a href="#cid-16-72">CID-16-72</a>
* <a href="#cid-16-73">CID-16-73</a>
* <a href="#cid-16-74">CID-16-74</a>
* <a href="#cid-16-75">CID-16-75</a>

---

### <a id="cid-16-01"></a>CID-16-01

**Qué hace:**
Incluye la implementación del asistente de configuración del teclado CID a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `setup_teclado_cid.h`, que declara la función pública encargada de ejecutar el asistente. Gracias a ello, el archivo actual puede definir toda la lógica de setup interactivo.

**Pseudocódigo:**

```text
incluir interfaz pública del asistente de setup
habilitar definición de su función principal
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-16">CID-16</a>.
* Da soporte directo a <a href="#cid-16-69">CID-16-69</a>.

---

### <a id="cid-16-02"></a>CID-16-02

**Qué hace:**
Incluye módulos de calibración, mapa CID y layout visual del teclado.

**Cómo funciona:**
Conecta el asistente con el subsistema de calibración persistente, el mapa oficial de teclas CID y el sistema de layout visual del teclado. Gracias a estas inclusiones, el setup puede asignar scanCodes, validar nombres, ordenar pasos y dibujar el teclado real del usuario.

**Pseudocódigo:**

```text
incluir módulo de calibración
incluir mapa oficial CID
incluir layout visual del teclado
```

**Relaciones:**

* Da soporte directo a <a href="#cid-16-15">CID-16-15</a>, <a href="#cid-16-26">CID-16-26</a>, <a href="#cid-16-33">CID-16-33</a>, <a href="#cid-16-50">CID-16-50</a> y <a href="#cid-16-71">CID-16-71</a>.
* Enlaza con <code>calibracion_teclado.h</code>, <code>mapa_teclas_cid.h</code> y <code>layout_teclado_visual.h</code>.

---

### <a id="cid-16-03"></a>CID-16-03

**Qué hace:**
Incluye cabeceras del sistema, utilidades de interfaz y contenedores estándar.

**Cómo funciona:**
Este bloque habilita la API Win32, helpers de coordenadas de ratón, cadenas anchas, vectores, mapas, algoritmos y utilidades de caracteres. No contiene lógica ejecutable, pero prepara el entorno necesario para compilar el resto del archivo.

**Pseudocódigo:**

```text
incluir helpers de interfaz Win32
incluir API base de Windows
incluir soporte de cadenas
incluir soporte de vectores
incluir soporte de mapas
incluir soporte de algoritmos
incluir utilidades de caracteres anchos
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-16">CID-16</a>.
* Da soporte indirecto a <a href="#cid-16-46">CID-16-46</a>, <a href="#cid-16-55">CID-16-55</a>, <a href="#cid-16-68">CID-16-68</a> y al resto de bloques con lógica Win32 o de contenedores.

---

### <a id="cid-16-04"></a>CID-16-04

**Qué hace:**
Abre un espacio interno anónimo para encapsular estado y helpers privados del asistente de setup.

**Cómo funciona:**
Agrupa toda la lógica interna del asistente dentro de un `namespace` anónimo. Así se limita su visibilidad al propio archivo y se separa la implementación privada de la función pública final.

**Pseudocódigo:**

```text
abrir espacio interno privado del asistente
encapsular estado y helpers no públicos
```

**Relaciones:**

* Contiene internamente <a href="#cid-16-05">CID-16-05</a> a <a href="#cid-16-68">CID-16-68</a>.
* Se separa de la API pública definida en <a href="#cid-16-69">CID-16-69</a>.

---

### <a id="cid-16-05"></a>CID-16-05

**Qué hace:**
Define el nombre de la clase de ventana registrada por el asistente de configuración.

**Cómo funciona:**
Declara una cadena constante con el nombre Win32 de la clase de ventana usada exclusivamente por el setup. Esta identidad se reutiliza al registrar la clase y al crear la ventana principal del asistente.

**Pseudocódigo:**

```text
definir nombre fijo de clase de ventana del setup
```

**Relaciones:**

* Es usado por <a href="#cid-16-68">CID-16-68</a> y <a href="#cid-16-73">CID-16-73</a>.

---

### <a id="cid-16-06"></a>CID-16-06

**Qué hace:**
Define la paleta base de colores usada por el asistente visual de configuración.

**Cómo funciona:**
Declara una serie de constantes `COLORREF` para fondo, texto, estados, tarjetas, bordes y sombras. Esta paleta unifica el aspecto visual del asistente en todos sus elementos renderizados.

**Pseudocódigo:**

```text
definir colores base de fondo
definir colores de texto y estados
definir colores de tarjeta, borde y sombra
```

**Relaciones:**

* Es usada por <a href="#cid-16-45">CID-16-45</a>, <a href="#cid-16-46">CID-16-46</a>, <a href="#cid-16-51">CID-16-51</a>, <a href="#cid-16-52">CID-16-52</a> y <a href="#cid-16-66">CID-16-66</a>.

---

### <a id="cid-16-07"></a>CID-16-07

**Qué hace:**
Define el estado global del asistente con ventana, layout, pasos, captura y UI interactiva.

**Cómo funciona:**
Declara una estructura que contiene todos los datos persistentes del setup mientras está abierto: instancia, ventana, rutas, layout, pasos, progreso, estados finales, captura de scanCodes, reasignación, mensaje de estado y datos del botón de reinicio.

**Pseudocódigo:**

```text
definir estructura de estado global del setup
guardar handles, rutas y layout
guardar pasos y progreso actual
guardar estados de finalización y prueba
guardar captura de scanCodes y reasignación
guardar estado de UI interactiva
```

**Relaciones:**

* Su instancia única se declara en <a href="#cid-16-08">CID-16-08</a>.
* Es utilizada prácticamente por todo <a href="#cid-16">CID-16</a>, especialmente <a href="#cid-16-17">CID-16-17</a> a <a href="#cid-16-34">CID-16-34</a> y <a href="#cid-16-55">CID-16-55</a> a <a href="#cid-16-75">CID-16-75</a>.

---

### <a id="cid-16-08"></a>CID-16-08

**Qué hace:**
Declara la instancia global única del estado del asistente de setup.

**Cómo funciona:**
Crea una sola variable global `g_setup` de tipo `SetupState`. Esa instancia concentra todo el estado vivo del asistente durante su ejecución.

**Pseudocódigo:**

```text
crear instancia global única del estado del setup
```

**Relaciones:**

* Usa la estructura definida en <a href="#cid-16-07">CID-16-07</a>.
* Es empleada por todos los helpers y por la función principal <a href="#cid-16-69">CID-16-69</a>.

---

### <a id="cid-16-09"></a>CID-16-09

**Qué hace:**
Envía mensajes de depuración del asistente al visor de salida de Windows.

**Cómo funciona:**
Recibe una cadena ancha, le añade un salto de línea y la envía mediante `OutputDebugStringW`. Sirve como helper unificado de trazas del módulo.

**Pseudocódigo:**

```text
añadir salto de línea al mensaje
enviar mensaje al depurador de Windows
```

**Relaciones:**

* Es un helper disponible para el módulo completo <a href="#cid-16">CID-16</a>.

---

### <a id="cid-16-10"></a>CID-16-10

**Qué hace:**
Obtiene el directorio del ejecutable actual para resolver rutas auxiliares del setup.

**Cómo funciona:**
Llama a `GetModuleFileNameW`, convierte la ruta completa del ejecutable en `std::wstring` y elimina el nombre del archivo para quedarse solo con el directorio base.

**Pseudocódigo:**

```text
obtener ruta completa del ejecutable
quedarse con el directorio padre
devolver directorio
```

**Relaciones:**

* Es usada por <a href="#cid-16-69">CID-16-69</a> para construir la ruta de `keyboard-layout.json`.

---

### <a id="cid-16-11"></a>CID-16-11

**Qué hace:**
Une dos segmentos de ruta garantizando un separador válido entre ambos.

**Cómo funciona:**
Si la primera parte está vacía devuelve la segunda. Si la primera ya termina en separador, concatena directamente. Si no, inserta una contrabarra intermedia.

**Pseudocódigo:**

```text
si la primera parte está vacía:
    devolver la segunda
si la primera parte ya termina en separador:
    devolver concatenación directa
devolver primera parte + separador + segunda parte
```

**Relaciones:**

* Es usada por <a href="#cid-16-69">CID-16-69</a>.

---

### <a id="cid-16-12"></a>CID-16-12

**Qué hace:**
Recorta espacios en blanco al inicio y final de una cadena ancha.

**Cómo funciona:**
Avanza un índice inicial mientras haya espacios al principio y retrocede un índice final mientras haya espacios al final. Luego devuelve la subcadena útil delimitada por ambos.

**Pseudocódigo:**

```text
avanzar índice inicial mientras haya espacios
retroceder índice final mientras haya espacios
devolver subcadena recortada
```

**Relaciones:**

* Es usada por <a href="#cid-16-15">CID-16-15</a>.

---

### <a id="cid-16-13"></a>CID-16-13

**Qué hace:**
Convierte una cadena completa a mayúsculas de forma simple para comparaciones visuales.

**Cómo funciona:**
Copia la cadena y recorre todos sus caracteres aplicando `towupper`. Devuelve el resultado transformado.

**Pseudocódigo:**

```text
copiar cadena de entrada
para cada carácter:
    convertir a mayúscula
devolver resultado
```

**Relaciones:**

* Es usada por <a href="#cid-16-15">CID-16-15</a>.

---

### <a id="cid-16-14"></a>CID-16-14

**Qué hace:**
Divide un texto multilinea en líneas individuales separadas por salto de línea.

**Cómo funciona:**
Recorre la cadena carácter a carácter acumulando texto en una línea actual. Cuando encuentra `\n`, empuja la línea acumulada al vector y empieza una nueva. Al final añade también la última línea.

**Pseudocódigo:**

```text
crear vector de líneas
crear línea actual vacía

para cada carácter:
    si es salto de línea:
        guardar línea actual
        vaciar línea actual
    si no:
        añadir carácter a línea actual

guardar última línea
devolver vector
```

**Relaciones:**

* Es usada por <a href="#cid-16-15">CID-16-15</a>.

---

### <a id="cid-16-15"></a>CID-16-15

**Qué hace:**
Extrae la pista secundaria visible de una tecla a partir de su texto original de layout.

**Cómo funciona:**
Divide `textoOriginal` en líneas, recorta cada una y conserva solo las útiles. Después recorre esas líneas y descarta las que coinciden con el identificador CID principal o con etiquetas especiales como `CID KEY`, `AUX CID` o `MOD.`. La primera línea restante se devuelve como pista auxiliar.

**Pseudocódigo:**

```text
dividir texto original en líneas
recortar y conservar líneas útiles
si no hay líneas útiles:
    devolver vacío

para cada línea útil:
    normalizar a mayúsculas
    ignorar si coincide con id principal o etiquetas especiales
    devolver primera línea válida

devolver vacío
```

**Relaciones:**

* Usa <a href="#cid-16-12">CID-16-12</a>, <a href="#cid-16-13">CID-16-13</a> y <a href="#cid-16-14">CID-16-14</a>.
* Es llamada desde <a href="#cid-16-47">CID-16-47</a>.

---

### <a id="cid-16-16"></a>CID-16-16

**Qué hace:**
Obtiene el texto principal mostrado dentro de una tecla visual del asistente.

**Cómo funciona:**
Si la tecla tiene `idCid`, usa ese valor como texto principal, con casos especiales para `CID_KEY` y `AUX_CID`. Si no tiene identificador CID, cae al texto visible original de la tecla.

**Pseudocódigo:**

```text
si la tecla tiene id CID:
    si es CID_KEY:
        devolver "CID KEY"
    si es AUX_CID:
        devolver "AUX CID"
    devolver id CID

devolver texto visible original
```

**Relaciones:**

* Es usada por <a href="#cid-16-47">CID-16-47</a>.

---

### <a id="cid-16-17"></a>CID-16-17

**Qué hace:**
Devuelve el nombre CID del paso actual de calibración si todavía existe.

**Cómo funciona:**
Comprueba si el índice actual ha superado el número de pasos. Si es así devuelve vacío. Si no, devuelve el nombre contenido en la posición actual del vector de pasos.

**Pseudocódigo:**

```text
si el índice actual está fuera de rango:
    devolver vacío
devolver nombre del paso actual
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-22">CID-16-22</a>, <a href="#cid-16-47">CID-16-47</a> y <a href="#cid-16-34">CID-16-34</a>.

---

### <a id="cid-16-18"></a>CID-16-18

**Qué hace:**
Comprueba si un scanCode figura actualmente como pulsado dentro del asistente.

**Cómo funciona:**
Recorre el vector de `scanCodesAbajo` y devuelve `true` si encuentra el valor buscado. Si no lo encuentra, devuelve `false`.

**Pseudocódigo:**

```text
recorrer scanCodes actualmente pulsados
si alguno coincide:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Es usada por <a href="#cid-16-19">CID-16-19</a> y <a href="#cid-16-47">CID-16-47</a>.

---

### <a id="cid-16-19"></a>CID-16-19

**Qué hace:**
Marca un scanCode como pulsado dentro del estado visual del asistente.

**Cómo funciona:**
Rechaza scanCodes nulos o fuera de rango. Si el scanCode todavía no figuraba como pulsado, lo añade al vector `scanCodesAbajo`.

**Pseudocódigo:**

```text
si el scanCode es inválido:
    salir
si todavía no está marcado como pulsado:
    añadirlo al vector
```

**Relaciones:**

* Usa <a href="#cid-16-18">CID-16-18</a>.
* Es llamada desde <a href="#cid-16-59">CID-16-59</a>.

---

### <a id="cid-16-20"></a>CID-16-20

**Qué hace:**
Elimina un scanCode del conjunto de teclas actualmente pulsadas.

**Cómo funciona:**
Recorre el vector `scanCodesAbajo` hasta encontrar el scanCode indicado. Cuando lo encuentra, lo borra del vector y termina.

**Pseudocódigo:**

```text
recorrer scanCodes actualmente pulsados
si uno coincide:
    borrarlo del vector
    salir
```

**Relaciones:**

* Es llamada desde <a href="#cid-16-64">CID-16-64</a>.

---

### <a id="cid-16-21"></a>CID-16-21

**Qué hace:**
Devuelve el título principal del asistente según su fase actual.

**Cómo funciona:**
Si el asistente ya está en modo de prueba final, devuelve un título celebrando que el teclado ya está configurado. En cualquier otra fase, devuelve el título principal de configuración inicial.

**Pseudocódigo:**

```text
si está en modo de prueba final:
    devolver título de configuración completada
devolver título de configuración inicial
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-46">CID-16-46</a>.

---

### <a id="cid-16-22"></a>CID-16-22

**Qué hace:**
Devuelve el texto principal explicativo según paso, reasignación o estado final.

**Cómo funciona:**
Genera mensajes distintos según el contexto: modo de prueba final, estados terminados, modo de reasignación manual o paso normal de calibración. Si no queda ningún paso pendiente, devuelve una frase neutral de ausencia de pasos.

**Pseudocódigo:**

```text
si está en modo de prueba final:
    si hay reasignación en curso:
        devolver instrucción de nueva tecla
    devolver texto de prueba final

si ya terminó:
    devolver texto según éxito, cancelación o error

si hay reasignación manual:
    devolver instrucción de nueva tecla

obtener nombre del paso actual
si no hay paso:
    devolver texto sin pasos pendientes

devolver instrucción para pulsar la tecla del paso actual
```

**Relaciones:**

* Usa <a href="#cid-16-17">CID-16-17</a> y el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-46">CID-16-46</a>.

---

### <a id="cid-16-23"></a>CID-16-23

**Qué hace:**
Devuelve el texto secundario de ayuda y controles rápidos del asistente.

**Cómo funciona:**
Produce una ayuda distinta en modo de prueba final, en estado terminado o durante la calibración normal. En la calibración normal incluye además el progreso actual en forma `Paso X de N`.

**Pseudocódigo:**

```text
si está en modo de prueba final:
    devolver ayuda de prueba y reasignación

si ya terminó:
    devolver ayuda de cierre según estado

construir texto con paso actual y controles rápidos
devolver resultado
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-46">CID-16-46</a>.

---

### <a id="cid-16-24"></a>CID-16-24

**Qué hace:**
Devuelve el texto inferior de estado o error mostrado en la franja final de la ventana.

**Cómo funciona:**
Prioriza primero el error final, luego el mensaje de estado actual y, si no hay ninguno, produce un texto fijo cuando se está en modo de prueba final. Si no aplica nada, devuelve una cadena vacía.

**Pseudocódigo:**

```text
si existe error final:
    devolver texto de error
si existe mensaje de estado:
    devolver mensaje de estado
si está en modo de prueba final:
    devolver texto fijo de prueba final
devolver vacío
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-51">CID-16-51</a>.

---

### <a id="cid-16-25"></a>CID-16-25

**Qué hace:**
Invalida la ventana del asistente para forzar redibujado.

**Cómo funciona:**
Si la ventana principal existe, llama a `InvalidateRect` sobre toda ella para pedir un nuevo repintado.

**Pseudocódigo:**

```text
si existe ventana del asistente:
    invalidarla completamente
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde muchos helpers de flujo como <a href="#cid-16-27">CID-16-27</a>, <a href="#cid-16-28">CID-16-28</a>, <a href="#cid-16-29">CID-16-29</a>, <a href="#cid-16-30">CID-16-30</a>, <a href="#cid-16-33">CID-16-33</a> y <a href="#cid-16-53">CID-16-53</a>.

---

### <a id="cid-16-26"></a>CID-16-26

**Qué hace:**
Comprueba si un scanCode ya estaba asignado a otra tecla CID distinta del objetivo actual.

**Cómo funciona:**
Recupera todas las asignaciones calibradas actuales y las recorre. Si encuentra el mismo scanCode asociado a otra tecla distinta de la objetivo, devuelve `true` y rellena el nombre existente en conflicto.

**Pseudocódigo:**

```text
obtener asignaciones calibradas
para cada asignación:
    si el scanCode coincide y el nombre es distinto del objetivo:
        devolver verdadero e informar del nombre existente
vaciar nombre existente
devolver falso
```

**Relaciones:**

* Usa <a href="#cid-15-08">CID-15-08</a> / <a href="#cid-14-35">CID-14-35</a>.
* Es llamada desde <a href="#cid-16-33">CID-16-33</a>.

---

### <a id="cid-16-27"></a>CID-16-27

**Qué hace:**
Retrocede un paso o cancela una reasignación según el contexto actual del asistente.

**Cómo funciona:**
Distingue varios contextos: modo de prueba final, estado terminado, reasignación manual o calibración secuencial normal. Según el caso, cancela la reasignación, informa de que ya se está en el primer paso o retrocede el índice y elimina las asignaciones del paso actual y previo para rehacerlas.

**Pseudocódigo:**

```text
si está en modo de prueba final:
    cancelar reasignación activa
    informar
    refrescar
    salir

si ya terminó:
    salir

si hay reasignación manual:
    cancelarla
    informar
    refrescar
    salir

si ya está en el primer paso:
    informar
    refrescar
    salir

si el índice actual es válido:
    quitar asignación del paso actual

retroceder índice

si el nuevo índice sigue siendo válido:
    quitar asignación del paso previo

informar del retroceso
refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a>, <a href="#cid-16-17">CID-16-17</a> y <a href="#cid-15-06">CID-15-06</a> / <a href="#cid-14-31">CID-14-31</a>.
* Es llamada desde <a href="#cid-16-63">CID-16-63</a>.

---

### <a id="cid-16-28"></a>CID-16-28

**Qué hace:**
Guarda en disco la calibración actual y actualiza el estado final del asistente.

**Cómo funciona:**
Intenta guardar la calibración usando la ruta configurada. Si falla, marca el estado interno como no guardado, conserva el error, actualiza el mensaje de estado y fuerza un repintado. Si tiene éxito, marca `guardadoOk`.

**Pseudocódigo:**

```text
intentar guardar calibración actual
si falla:
    marcar guardado como fallido
    guardar error final
    actualizar mensaje de estado
    refrescar
    devolver falso

marcar guardado como correcto
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25">CID-16-25</a> y <a href="#cid-15-04">CID-15-04</a> / <a href="#cid-14-27">CID-14-27</a>.
* Es llamada desde <a href="#cid-16-31">CID-16-31</a> y <a href="#cid-16-33">CID-16-33</a>.

---

### <a id="cid-16-29"></a>CID-16-29

**Qué hace:**
Reinicia el asistente por completo borrando calibración, pasos y estado de prueba final.

**Cómo funciona:**
Limpia la calibración cargada, reinicia el índice y todos los flags de progreso, borra errores, mensajes, scanCodes capturados, reasignación y hover del botón. Después informa del reinicio y refresca la ventana.

**Pseudocódigo:**

```text
limpiar calibración cargada

reiniciar índice y flags del flujo
borrar errores y mensajes
resetear scanCodes y reasignación
apagar hover del botón

informar del reinicio
refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a> y <a href="#cid-15-05">CID-15-05</a> / <a href="#cid-14-28">CID-14-28</a>.
* Es llamada desde <a href="#cid-16-58">CID-16-58</a>.

---

### <a id="cid-16-30"></a>CID-16-30

**Qué hace:**
Entra en la fase final de prueba del teclado tras guardar correctamente la calibración.

**Cómo funciona:**
Activa `modoPruebaFinal`, marca el asistente como terminado, limpia cualquier reasignación pendiente, establece un mensaje de estado apropiado y refresca la ventana.

**Pseudocódigo:**

```text
activar modo de prueba final
marcar asistente como terminado
limpiar reasignación pendiente
actualizar mensaje de estado
refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a>.
* Es llamada desde <a href="#cid-16-31">CID-16-31</a>.

---

### <a id="cid-16-31"></a>CID-16-31

**Qué hace:**
Cierra el flujo de pasos pendientes guardando la calibración y entrando en modo prueba.

**Cómo funciona:**
Llama a `GuardarCalibracionActual` y, si el guardado tiene éxito, entra inmediatamente en la fase final de prueba del teclado.

**Pseudocódigo:**

```text
si se puede guardar la calibración actual:
    entrar en modo de prueba final
```

**Relaciones:**

* Usa <a href="#cid-16-28">CID-16-28</a> y <a href="#cid-16-30">CID-16-30</a>.
* Es llamada desde <a href="#cid-16-32">CID-16-32</a>.

---

### <a id="cid-16-32"></a>CID-16-32

**Qué hace:**
Avanza automáticamente mientras los pasos secuenciales ya estén cubiertos por asignaciones válidas.

**Cómo funciona:**
Mientras el índice actual siga dentro del vector de pasos, consulta si el paso actual ya tiene scanCode asignado. Si lo tiene, incrementa el índice y continúa. Si se agotan todos los pasos, dispara el cierre con guardado final.

**Pseudocódigo:**

```text
mientras queden pasos:
    si el paso actual no tiene asignación:
        salir del bucle
    avanzar al siguiente paso

si ya no quedan pasos:
    finalizar y guardar
```

**Relaciones:**

* Usa <a href="#cid-16-31">CID-16-31</a> y <a href="#cid-15-07">CID-15-07</a> / <a href="#cid-14-34">CID-14-34</a>.
* Es llamada desde <a href="#cid-16-33">CID-16-33</a>.

---

### <a id="cid-16-33"></a>CID-16-33

**Qué hace:**
Acepta un scanCode para una tecla objetivo concreta y actualiza progreso o reasignación.

**Cómo funciona:**
Rechaza el caso de asistente ya terminado fuera de prueba final y también scanCodes inválidos. Después guarda el último scanCode, detecta si la tecla ya estaba usada por otro paso, intenta establecer la nueva asignación y actualiza el mensaje de estado. Según el contexto, guarda la calibración en modo prueba o avanza en la secuencia normal. Finalmente limpia el modo de reasignación y refresca.

**Pseudocódigo:**

```text
si el asistente ya terminó y no está en prueba final:
    salir

si el scanCode es inválido:
    informar
    refrescar
    salir

guardar último scanCode
comprobar si ya estaba usado por otra tecla
actualizar mensaje de estado según conflicto o asignación nueva

intentar establecer asignación
si falla:
    informar
    refrescar
    salir

si está en modo de prueba final:
    guardar calibración actual
si no y debe avanzar en secuencia:
    avanzar automáticamente

limpiar modo de reasignación
refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a>, <a href="#cid-16-26">CID-16-26</a>, <a href="#cid-16-28">CID-16-28</a>, <a href="#cid-16-32">CID-16-32</a> y <a href="#cid-15-06">CID-15-06</a> / <a href="#cid-14-30">CID-14-30</a>.
* Es llamada desde <a href="#cid-16-34">CID-16-34</a>.

---

### <a id="cid-16-34"></a>CID-16-34

**Qué hace:**
Acepta un scanCode detectado y lo enruta según paso normal, prueba final o reasignación manual.

**Cómo funciona:**
Si existe una reasignación manual activa, delega directamente en ella. Si está en modo de prueba final sin reasignación, solo informa del scanCode detectado. En calibración normal, obtiene el nombre del paso actual y delega la aceptación del scanCode a la función de asignación concreta.

**Pseudocódigo:**

```text
si el asistente ya terminó y no está en prueba final:
    salir

si hay reasignación manual activa:
    aceptar scanCode para esa tecla
    salir

si está en modo de prueba final:
    informar del scanCode detectado
    guardar último scanCode
    refrescar
    salir

obtener nombre del paso actual
si no existe:
    salir

aceptar scanCode para el paso actual
```

**Relaciones:**

* Usa <a href="#cid-16-17">CID-16-17</a>, <a href="#cid-16-25">CID-16-25</a> y <a href="#cid-16-33">CID-16-33</a>.
* Es llamada desde <a href="#cid-16-60">CID-16-60</a>, <a href="#cid-16-74">CID-16-74</a> y desde el propio flujo de prueba final.

---

### <a id="cid-16-35"></a>CID-16-35

**Qué hace:**
Calcula el rectángulo de la tarjeta de cabecera del asistente.

**Cómo funciona:**
Parte del rectángulo cliente completo y aplica márgenes fijos horizontales y verticales, dejando una tarjeta superior de altura fija.

**Pseudocódigo:**

```text
copiar rectángulo cliente
aplicar márgenes laterales y superiores
fijar altura de la cabecera
devolver rectángulo resultante
```

**Relaciones:**

* Es llamada desde <a href="#cid-16-46">CID-16-46</a>.

---

### <a id="cid-16-36"></a>CID-16-36

**Qué hace:**
Calcula el área disponible para dibujar el teclado visual dentro del asistente.

**Cómo funciona:**
Parte del rectángulo cliente y reserva una banda central amplia situada entre la cabecera y la franja inferior de estado, aplicando márgenes laterales y verticales fijos.

**Pseudocódigo:**

```text
copiar rectángulo cliente
aplicar márgenes laterales
fijar inicio bajo la cabecera
reservar margen inferior
devolver área del teclado
```

**Relaciones:**

* Es llamada desde <a href="#cid-16-50">CID-16-50</a> y <a href="#cid-16-53">CID-16-53</a>.

---

### <a id="cid-16-37"></a>CID-16-37

**Qué hace:**
Calcula la franja inferior donde se dibuja el estado textual del asistente.

**Cómo funciona:**
Parte del rectángulo cliente, aplica márgenes laterales y fija una banda inferior de altura corta a cierta distancia del borde inferior.

**Pseudocódigo:**

```text
copiar rectángulo cliente
aplicar márgenes laterales
fijar franja inferior de estado
devolver rectángulo resultante
```

**Relaciones:**

* Es llamada desde <a href="#cid-16-51">CID-16-51</a>.

---

### <a id="cid-16-38"></a>CID-16-38

**Qué hace:**
Calcula el rectángulo del botón de reinicio disponible en modo prueba final.

**Cómo funciona:**
Construye un rectángulo fijo anclado a la esquina inferior derecha del cliente, con anchura y altura definidas para alojar el botón de reinicio de calibración.

**Pseudocódigo:**

```text
crear rectángulo vacío
anclarlo a la esquina inferior derecha
fijar ancho y alto del botón
devolver rectángulo
```

**Relaciones:**

* Es llamada desde <a href="#cid-16-52">CID-16-52</a>, <a href="#cid-16-56">CID-16-56</a> y <a href="#cid-16-58">CID-16-58</a>.

---

### <a id="cid-16-39"></a>CID-16-39

**Qué hace:**
Comprueba si un punto de ratón cae dentro de un rectángulo dado.

**Cómo funciona:**
Evalúa si la coordenada X e Y están dentro de los límites izquierdo, derecho, superior e inferior del rectángulo usando la convención habitual de límites inclusivos por la izquierda y arriba, exclusivos por la derecha y abajo.

**Pseudocódigo:**

```text
devolver si el punto está dentro del rectángulo
```

**Relaciones:**

* Es usada por <a href="#cid-16-56">CID-16-56</a> y <a href="#cid-16-58">CID-16-58</a>.

---

### <a id="cid-16-40"></a>CID-16-40

**Qué hace:**
Calcula la métrica real del teclado dibujado según el layout y el área disponible.

**Cómo funciona:**
Empieza con valores por defecto. Si el layout cargado tiene dimensiones válidas, calcula el máximo ancho y alto disponibles, deriva una unidad base a partir de la escala posible, la reduce ligeramente para dejar respiración visual y centra el teclado dentro del área disponible.

**Pseudocódigo:**

```text
inicializar origen y unidades por defecto

si el layout tiene dimensiones válidas:
    calcular ancho y alto máximos disponibles
    calcular unidad máxima por ancho y por alto
    elegir unidad válida
    reducirla ligeramente
    calcular tamaño final del teclado
    centrar teclado dentro del área
```

**Relaciones:**

* Usa el layout almacenado en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-50">CID-16-50</a> y <a href="#cid-16-53">CID-16-53</a>.

---

### <a id="cid-16-41"></a>CID-16-41

**Qué hace:**
Aclara un color base sumando luminosidad a sus tres canales.

**Cómo funciona:**
Extrae los componentes RGB, suma un valor fijo a cada uno, los limita a 255 y recompone el color final.

**Pseudocódigo:**

```text
sumar luminosidad a rojo, verde y azul
limitar cada canal a 255
devolver color resultante
```

**Relaciones:**

* Es usada por <a href="#cid-16-47">CID-16-47</a>.

---

### <a id="cid-16-42"></a>CID-16-42

**Qué hace:**
Oscurece un color base restando intensidad a sus tres canales.

**Cómo funciona:**
Extrae los componentes RGB, resta un delta fijo a cada uno, los limita a cero y recompone el color resultante.

**Pseudocódigo:**

```text
restar intensidad a rojo, verde y azul
limitar cada canal a cero mínimo
devolver color resultante
```

**Relaciones:**

* Es usada por <a href="#cid-16-47">CID-16-47</a>.

---

### <a id="cid-16-43"></a>CID-16-43

**Qué hace:**
Rellena un rectángulo redondeado con un color sólido.

**Cómo funciona:**
Crea un pincel del color pedido, selecciona temporalmente un lápiz nulo para evitar borde y dibuja un `RoundRect` relleno. Después restaura los objetos GDI previos y libera el pincel.

**Pseudocódigo:**

```text
crear pincel del color indicado
seleccionar pincel y lápiz nulo
dibujar rectángulo redondeado relleno
restaurar objetos previos
liberar pincel
```

**Relaciones:**

* Es usada por <a href="#cid-16-45">CID-16-45</a>, <a href="#cid-16-47">CID-16-47</a> y <a href="#cid-16-52">CID-16-52</a>.

---

### <a id="cid-16-44"></a>CID-16-44

**Qué hace:**
Dibuja el borde de un rectángulo redondeado con grosor y color configurables.

**Cómo funciona:**
Crea un lápiz del grosor y color pedidos, selecciona un pincel hueco y traza el contorno del `RoundRect`. Después restaura los objetos GDI previos y libera el lápiz.

**Pseudocódigo:**

```text
crear lápiz del color y grosor indicados
seleccionar lápiz y pincel hueco
dibujar contorno del rectángulo redondeado
restaurar objetos previos
liberar lápiz
```

**Relaciones:**

* Es usada por <a href="#cid-16-45">CID-16-45</a>, <a href="#cid-16-47">CID-16-47</a> y <a href="#cid-16-52">CID-16-52</a>.

---

### <a id="cid-16-45"></a>CID-16-45

**Qué hace:**
Dibuja la tarjeta visual de cabecera con sombra, fondo y borde suave.

**Cómo funciona:**
Construye primero una sombra desplazada hacia abajo, luego rellena la tarjeta principal con el color de tarjeta y finalmente dibuja un borde suave alrededor.

**Pseudocódigo:**

```text
crear rectángulo de sombra desplazado
rellenar sombra
rellenar tarjeta principal
dibujar borde de la tarjeta
```

**Relaciones:**

* Usa <a href="#cid-16-06">CID-16-06</a>, <a href="#cid-16-43">CID-16-43</a> y <a href="#cid-16-44">CID-16-44</a>.
* Es llamada desde <a href="#cid-16-46">CID-16-46</a>.

---

### <a id="cid-16-46"></a>CID-16-46

**Qué hace:**
Dibuja título, texto principal y texto secundario de la cabecera del asistente.

**Cómo funciona:**
Calcula la tarjeta de cabecera, la pinta y luego crea tres fuentes distintas para título, texto principal y cuerpo. Después dibuja el título, el texto principal y el texto secundario en rectángulos específicos dentro de la tarjeta, usando las funciones de texto del estado actual.

**Pseudocódigo:**

```text
calcular tarjeta de cabecera
pintar tarjeta
crear fuentes de título, principal y cuerpo

dibujar título
dibujar texto principal
dibujar texto secundario

restaurar fuente previa
liberar fuentes temporales
```

**Relaciones:**

* Usa <a href="#cid-16-21">CID-16-21</a>, <a href="#cid-16-22">CID-16-22</a>, <a href="#cid-16-23">CID-16-23</a>, <a href="#cid-16-35">CID-16-35</a> y <a href="#cid-16-45">CID-16-45</a>.
* Es llamada desde <a href="#cid-16-66">CID-16-66</a>.

---

### <a id="cid-16-47"></a>CID-16-47

**Qué hace:**
Dibuja una tecla individual del teclado visual con estados de objetivo, asignación y pulsación.

**Cómo funciona:**
Determina primero si la tecla es el objetivo actual, si está en reasignación, si ya tiene scanCode asignado, si coincide con la última pulsada y si está físicamente abajo. A partir de esos estados elige colores y dibuja sombra, base, tapa y borde. Después obtiene pista secundaria y texto principal, crea fuentes y dibuja ambas capas de texto sobre la tecla.

**Pseudocódigo:**

```text
obtener paso actual
calcular si la tecla es objetivo actual o de reasignación
consultar si está asignada y su scanCode
calcular si es la última pulsada o está abajo

elegir color base según estados
dibujar sombra, base, cara superior y borde

obtener pista auxiliar y texto principal
crear fuentes de pista y principal

dibujar pista superior si existe
dibujar texto principal centrado

restaurar y liberar fuentes
```

**Relaciones:**

* Contiene internamente <a href="#cid-16-48">CID-16-48</a> y <a href="#cid-16-49">CID-16-49</a>.
* Usa <a href="#cid-16-15">CID-16-15</a>, <a href="#cid-16-16">CID-16-16</a>, <a href="#cid-16-17">CID-16-17</a>, <a href="#cid-16-18">CID-16-18</a>, <a href="#cid-16-41">CID-16-41</a>, <a href="#cid-16-42">CID-16-42</a>, <a href="#cid-16-43">CID-16-43</a>, <a href="#cid-16-44">CID-16-44</a> y <a href="#cid-15-07">CID-15-07</a> / <a href="#cid-14-34">CID-14-34</a>.
* Es llamada desde <a href="#cid-16-50">CID-16-50</a>.

---

### <a id="cid-16-48"></a>CID-16-48

**Qué hace:**
Dibuja la pista pequeña superior de la tecla cuando existe texto auxiliar útil.

**Cómo funciona:**
Si la pista no está vacía, construye un pequeño rectángulo en la parte alta de la tecla, selecciona un color de texto suave y dibuja la pista alineada arriba a la izquierda.

**Pseudocódigo:**

```text
si existe pista auxiliar:
    calcular rectángulo superior pequeño
    fijar color de texto suave
    dibujar pista
```

**Relaciones:**

* Forma parte de <a href="#cid-16-47">CID-16-47</a>.

---

### <a id="cid-16-49"></a>CID-16-49

**Qué hace:**
Dibuja la etiqueta principal grande de la tecla en el centro visual.

**Cómo funciona:**
Construye un rectángulo central dentro de la tecla, selecciona la fuente principal grande, fija un color oscuro y dibuja el texto principal centrado tanto horizontal como verticalmente.

**Pseudocódigo:**

```text
calcular rectángulo central de la tecla
seleccionar fuente principal
fijar color de texto oscuro
dibujar texto principal centrado
```

**Relaciones:**

* Forma parte de <a href="#cid-16-47">CID-16-47</a>.

---

### <a id="cid-16-50"></a>CID-16-50

**Qué hace:**
Dibuja el teclado completo a partir del layout visual cargado.

**Cómo funciona:**
Si no hay layout cargado, no hace nada. Si lo hay, calcula el área del teclado y su métrica real en píxeles. Después recorre todas las teclas del layout y, para cada tecla renderizable, obtiene su rectángulo en píxeles y la pinta individualmente.

**Pseudocódigo:**

```text
si no hay layout cargado:
    salir

calcular área del teclado
calcular métrica real del teclado

para cada tecla del layout:
    si no es renderizable:
        continuar
    calcular rectángulo en píxeles
    pintar tecla individual
```

**Relaciones:**

* Usa <a href="#cid-16-36">CID-16-36</a>, <a href="#cid-16-40">CID-16-40</a> y <a href="#cid-16-47">CID-16-47</a>.
* Es llamada desde <a href="#cid-16-66">CID-16-66</a>.

---

### <a id="cid-16-51"></a>CID-16-51

**Qué hace:**
Dibuja la línea de estado inferior con color normal o de error según el contexto.

**Cómo funciona:**
Obtiene el texto de estado inferior y, si está vacío, no dibuja nada. Si existe, calcula su rectángulo, crea una fuente de cuerpo, elige color informativo o de error según haya error final y dibuja el texto alineado a la izquierda con elipsis al final.

**Pseudocódigo:**

```text
obtener texto de estado inferior
si está vacío:
    salir

calcular rectángulo inferior
crear fuente de texto
elegir color normal o de error
dibujar texto con elipsis
restaurar y liberar fuente
```

**Relaciones:**

* Usa <a href="#cid-16-24">CID-16-24</a>, <a href="#cid-16-37">CID-16-37</a> y el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-66">CID-16-66</a>.

---

### <a id="cid-16-52"></a>CID-16-52

**Qué hace:**
Dibuja el botón de reinicio solo durante el modo final de prueba y corrección.

**Cómo funciona:**
Si no se está en modo de prueba final, no hace nada. Si sí se está, calcula el rectángulo del botón, lo guarda en el estado global, elige colores según hover, dibuja sombra, fondo y borde, crea una fuente seminegrita y dibuja el texto centrado del botón.

**Pseudocódigo:**

```text
si no está en modo de prueba final:
    salir

calcular rectángulo del botón
guardarlo en el estado global
elegir colores según hover
dibujar sombra, fondo y borde
crear fuente del botón
dibujar texto centrado
restaurar y liberar fuente
```

**Relaciones:**

* Usa <a href="#cid-16-38">CID-16-38</a>, <a href="#cid-16-43">CID-16-43</a>, <a href="#cid-16-44">CID-16-44</a> y el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-66">CID-16-66</a>.

---

### <a id="cid-16-53"></a>CID-16-53

**Qué hace:**
Activa el modo de reasignación manual al hacer clic sobre una tecla visual válida.

**Cómo funciona:**
Rechaza primero el caso de asistente ya cerrado fuera del modo de prueba final y también el caso de layout no cargado. Si puede continuar, calcula el área y métrica del teclado, localiza la tecla visual bajo el puntero y, si la tecla clicada tiene un `idCid` válido distinto de `CID_KEY`, activa el modo de reasignación para esa tecla y actualiza el mensaje de estado.

**Pseudocódigo:**

```text
si el asistente ya terminó fuera de prueba final o no hay layout:
    salir

calcular área y métrica del teclado
buscar tecla visual bajo el ratón
si no hay tecla:
    salir

obtener tecla clicada
si no tiene id CID válido o es CID_KEY:
    salir

activar modo de reasignación para esa tecla
actualizar mensaje de estado
refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a>, <a href="#cid-16-36">CID-16-36</a>, <a href="#cid-16-40">CID-16-40</a> y el layout visual del módulo incluido en <a href="#cid-16-02">CID-16-02</a>.
* Es llamada desde <a href="#cid-16-58">CID-16-58</a>.

---

### <a id="cid-16-54"></a>CID-16-54

**Qué hace:**
Inicia el seguimiento de salida del ratón para gestionar el hover del botón inferior.

**Cómo funciona:**
Si el seguimiento ya estaba activo, no hace nada. Si no lo estaba, configura una estructura `TRACKMOUSEEVENT` con la bandera `TME_LEAVE` y la registra para la ventana actual. Si la llamada tiene éxito, marca el estado de seguimiento como activo.

**Pseudocódigo:**

```text
si ya se está siguiendo el ratón:
    salir

configurar TrackMouseEvent para detectar salida
si se pudo registrar:
    marcar seguimiento como activo
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Es llamada desde <a href="#cid-16-56">CID-16-56</a>.

---

### <a id="cid-16-55"></a>CID-16-55

**Qué hace:**
Define el procedimiento de ventana del asistente que gestiona ratón, teclado, pintura y cierre.

**Cómo funciona:**
Implementa el `WndProc` principal del setup. Gestiona creación, hover y salida del ratón, clics, pulsaciones y liberaciones de teclas, cambios de idioma de entrada, repintado completo y destrucción de la ventana. Para ello delega gran parte del comportamiento a helpers del propio módulo.

**Pseudocódigo:**

```text
según el mensaje recibido:
    manejar creación
    manejar hover del ratón
    manejar salida del ratón
    manejar clics
    manejar pulsaciones de teclado
    manejar liberaciones de teclado
    manejar cambio de layout de entrada
    pintar ventana
    cerrar bucle al destruir
    delegar en comportamiento por defecto en otros casos
```

**Relaciones:**

* Contiene internamente <a href="#cid-16-56">CID-16-56</a> a <a href="#cid-16-67">CID-16-67</a>.
* Es registrado como procedimiento de la clase de ventana en <a href="#cid-16-68">CID-16-68</a>.

---

### <a id="cid-16-56"></a>CID-16-56

**Qué hace:**
Gestiona el hover del botón de reinicio durante el modo de prueba final.

**Cómo funciona:**
Activa primero el seguimiento de salida del ratón. Si se está en modo de prueba final, obtiene la posición del cursor, calcula el rectángulo del botón de reinicio y actualiza la bandera de hover. Si el estado ha cambiado, repinta la ventana.

**Pseudocódigo:**

```text
iniciar seguimiento de salida del ratón

si está en modo de prueba final:
    leer posición del ratón
    calcular rectángulo del botón
    comprobar si el cursor está encima
    si cambia el hover:
        actualizarlo
        refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a>, <a href="#cid-16-38">CID-16-38</a>, <a href="#cid-16-39">CID-16-39</a> y <a href="#cid-16-54">CID-16-54</a>.
* Forma parte de <a href="#cid-16-55">CID-16-55</a>.

---

### <a id="cid-16-57"></a>CID-16-57

**Qué hace:**
Limpia el estado hover cuando el ratón abandona la ventana del asistente.

**Cómo funciona:**
Desactiva la bandera de seguimiento y, si el botón de reinicio estaba marcado como hovered, apaga también ese estado y fuerza un repintado.

**Pseudocódigo:**

```text
desactivar seguimiento del ratón
si el botón estaba en hover:
    apagar hover
    refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a> y el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Forma parte de <a href="#cid-16-55">CID-16-55</a>.

---

### <a id="cid-16-58"></a>CID-16-58

**Qué hace:**
Gestiona clics sobre el botón de reinicio o sobre teclas para reasignación manual.

**Cómo funciona:**
Obtiene la posición del clic y el rectángulo cliente. Si está en modo de prueba final y el clic cae sobre el botón de reinicio, reinicia toda la calibración y consume el evento. Si no, intenta activar modo de reasignación manual sobre la tecla visual clicada.

**Pseudocódigo:**

```text
leer posición del clic
obtener rectángulo cliente

si está en modo de prueba final:
    calcular rectángulo del botón
    si el clic cae en el botón:
        reiniciar calibración
        consumir evento

intentar activar reasignación manual por clic
```

**Relaciones:**

* Usa <a href="#cid-16-29">CID-16-29</a>, <a href="#cid-16-38">CID-16-38</a>, <a href="#cid-16-39">CID-16-39</a> y <a href="#cid-16-53">CID-16-53</a>.
* Forma parte de <a href="#cid-16-55">CID-16-55</a>.

---

### <a id="cid-16-59"></a>CID-16-59

**Qué hace:**
Procesa pulsaciones del asistente para captura de scanCodes, navegación y cierre.

**Cómo funciona:**
Extrae el scanCode desde `lParam`. Si la tecla no es espacio, la marca como pulsada, actualiza el último scanCode y repinta. Después distingue varios contextos: modo prueba final, asistente terminado, cancelación con Escape, retroceso con Retroceso o simple consumo del evento.

**Pseudocódigo:**

```text
extraer scanCode desde lParam

si la tecla no es espacio:
    marcar scanCode como pulsado
    guardar último scanCode
    refrescar

si está en modo de prueba final:
    gestionar cierre o captura de prueba
    salir

si el asistente ya terminó:
    permitir solo cierre con Enter o Esc
    salir

si se pulsó Escape:
    cancelar calibración
    marcar terminado
    informar
    refrescar
    salir

si se pulsó Retroceso:
    retroceder paso
    salir

consumir evento
```

**Relaciones:**

* Contiene internamente <a href="#cid-16-60">CID-16-60</a> a <a href="#cid-16-63">CID-16-63</a>.
* Usa <a href="#cid-16-19">CID-16-19</a> y <a href="#cid-16-25">CID-16-25</a>.
* Forma parte de <a href="#cid-16-55">CID-16-55</a>.

---

### <a id="cid-16-60"></a>CID-16-60

**Qué hace:**
En modo prueba final captura teclas para comprobación o cierra con Enter y Esc.

**Cómo funciona:**
Si en modo de prueba final se pulsa Enter o Escape, destruye la ventana y termina el asistente. Si se pulsa otra tecla distinta de espacio, acepta el scanCode capturado para lógica de prueba o reasignación manual.

**Pseudocódigo:**

```text
si se pulsa Enter o Escape:
    destruir ventana
    salir

si la tecla no es espacio:
    aceptar scanCode capturado
    salir

consumir evento
```

**Relaciones:**

* Usa <a href="#cid-16-34">CID-16-34</a>.
* Forma parte de <a href="#cid-16-59">CID-16-59</a>.

---

### <a id="cid-16-61"></a>CID-16-61

**Qué hace:**
Si el asistente ya terminó, solo permite cerrar con Enter o Esc.

**Cómo funciona:**
Cuando el asistente está en estado terminado pero no en flujo activo de calibración, comprueba si se ha pulsado Enter o Escape. Si ocurre, destruye la ventana; si no, simplemente consume la tecla.

**Pseudocódigo:**

```text
si se pulsa Enter o Escape:
    destruir ventana
    salir
consumir evento
```

**Relaciones:**

* Forma parte de <a href="#cid-16-59">CID-16-59</a>.

---

### <a id="cid-16-62"></a>CID-16-62

**Qué hace:**
Cancela el asistente actual cuando el usuario pulsa Escape durante la calibración.

**Cómo funciona:**
Marca el estado como cancelado y terminado, actualiza el mensaje de estado indicando la cancelación por el usuario y repinta la ventana.

**Pseudocódigo:**

```text
marcar calibración como cancelada
marcar asistente como terminado
actualizar mensaje de estado
refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a>.
* Forma parte de <a href="#cid-16-59">CID-16-59</a>.

---

### <a id="cid-16-63"></a>CID-16-63

**Qué hace:**
Retrocede un paso cuando el usuario pulsa Retroceso durante la calibración.

**Cómo funciona:**
Delega completamente el comportamiento al helper de retroceso de paso y consume el evento.

**Pseudocódigo:**

```text
retroceder un paso
consumir evento
```

**Relaciones:**

* Usa <a href="#cid-16-27">CID-16-27</a>.
* Forma parte de <a href="#cid-16-59">CID-16-59</a>.

---

### <a id="cid-16-64"></a>CID-16-64

**Qué hace:**
Actualiza el estado visual de teclas pulsadas al soltarlas.

**Cómo funciona:**
Extrae el scanCode desde `lParam`, lo elimina del conjunto de teclas actualmente pulsadas y fuerza un redibujado del asistente.

**Pseudocódigo:**

```text
extraer scanCode desde lParam
marcar scanCode como soltado
refrescar
```

**Relaciones:**

* Usa <a href="#cid-16-20">CID-16-20</a> y <a href="#cid-16-25">CID-16-25</a>.
* Forma parte de <a href="#cid-16-55">CID-16-55</a>.

---

### <a id="cid-16-65"></a>CID-16-65

**Qué hace:**
Fuerza redibujado si cambia el layout de entrada del sistema.

**Cómo funciona:**
Cuando llega `WM_INPUTLANGCHANGE`, invalida la ventana del asistente para garantizar que el render siga coherente si el sistema cambia de layout de entrada.

**Pseudocódigo:**

```text
refrescar ventana
consumir evento
```

**Relaciones:**

* Usa <a href="#cid-16-25">CID-16-25</a>.
* Forma parte de <a href="#cid-16-55">CID-16-55</a>.

---

### <a id="cid-16-66"></a>CID-16-66

**Qué hace:**
Dibuja el fondo, cabecera, teclado, estado inferior y botón de reinicio.

**Cómo funciona:**
Abre el ciclo de pintura con `BeginPaint`, rellena el fondo general de la ventana con el color base del asistente y luego delega el dibujo de cabecera, teclado, estado inferior y botón de reinicio. Finalmente cierra el ciclo con `EndPaint`.

**Pseudocódigo:**

```text
iniciar pintado
obtener rectángulo cliente
rellenar fondo base
activar modo de fondo transparente

pintar cabecera
pintar teclado
pintar estado inferior
pintar botón de reinicio

cerrar pintado
```

**Relaciones:**

* Usa <a href="#cid-16-06">CID-16-06</a>, <a href="#cid-16-46">CID-16-46</a>, <a href="#cid-16-50">CID-16-50</a>, <a href="#cid-16-51">CID-16-51</a> y <a href="#cid-16-52">CID-16-52</a>.
* Forma parte de <a href="#cid-16-55">CID-16-55</a>.

---

### <a id="cid-16-67"></a>CID-16-67

**Qué hace:**
Cierra el bucle del asistente al destruir la ventana principal.

**Cómo funciona:**
Cuando la ventana recibe `WM_DESTROY`, publica `PostQuitMessage(0)` para terminar el bucle modal del setup.

**Pseudocódigo:**

```text
publicar mensaje de salida del bucle modal
consumir evento
```

**Relaciones:**

* Forma parte de <a href="#cid-16-55">CID-16-55</a>.
* Su efecto se observa en el bucle definido en <a href="#cid-16-74">CID-16-74</a>.

---

### <a id="cid-16-68"></a>CID-16-68

**Qué hace:**
Registra la clase de ventana del asistente de configuración si todavía no existe.

**Cómo funciona:**
Rellena una estructura `WNDCLASSEXW` con el `SetupWndProc`, cursor, clase y estilos visuales. Luego intenta registrar la clase. Si falla por un motivo distinto a “clase ya existente”, informa error.

**Pseudocódigo:**

```text
configurar estructura de clase de ventana
intentar registrar clase
si falla y no era porque ya existía:
    devolver error
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-16-05">CID-16-05</a> y <a href="#cid-16-55">CID-16-55</a>.
* Es llamada desde <a href="#cid-16-72">CID-16-72</a>.

---

### <a id="cid-16-69"></a>CID-16-69

**Qué hace:**
Ejecuta el asistente completo de calibración del teclado CID hasta guardado o cancelación.

**Cómo funciona:**
Reinicia el estado global del setup, fija instancia y rutas, limpia la calibración previa y construye los pasos de calibración. Después carga el layout visual, registra la clase, crea la ventana principal, inicializa el estado visible, ejecuta un bucle modal de mensajes que intercepta ciertos `WM_KEYDOWN` para capturar scanCodes antes del despacho normal y, al final, traduce el estado final del asistente a éxito o error para el llamador.

**Pseudocódigo:**

```text
reiniciar estado global del setup
guardar instancia y rutas
limpiar calibración previa

construir pasos de calibración
cargar layout visual
registrar clase de ventana
crear ventana principal
si falla:
    devolver error

inicializar estado visible
mostrar y enfocar ventana

entrar en bucle modal de mensajes
interceptar ciertas teclas antes del despacho normal

al salir del bucle:
    traducir estado final a éxito o error
devolver resultado
```

**Relaciones:**

* Contiene internamente <a href="#cid-16-70">CID-16-70</a> a <a href="#cid-16-75">CID-16-75</a>.
* Usa <a href="#cid-16-10">CID-16-10</a>, <a href="#cid-16-11">CID-16-11</a>, <a href="#cid-16-68">CID-16-68</a>, <a href="#cid-15-05">CID-15-05</a> / <a href="#cid-14-28">CID-14-28</a> y el layout visual incluido por <a href="#cid-16-02">CID-16-02</a>.
* Implementa la función pública declarada en <code>setup_teclado_cid.h</code>.

---

### <a id="cid-16-70"></a>CID-16-70

**Qué hace:**
Construye la secuencia ordenada de pasos de calibración para todas las teclas CID físicas.

**Cómo funciona:**
Añade manualmente al vector `pasos` toda la secuencia de teclas calibrables del sistema en orden fijo: `I1..I10`, `C1..C6`, `D1..D10` y `AUX_CID`.

**Pseudocódigo:**

```text
añadir pasos I1 a I10
añadir pasos C1 a C6
añadir pasos D1 a D10
añadir paso AUX_CID
```

**Relaciones:**

* Forma parte de <a href="#cid-16-69">CID-16-69</a>.
* Alimenta el flujo progresivo gestionado por <a href="#cid-16-17">CID-16-17</a>, <a href="#cid-16-22">CID-16-22</a> y <a href="#cid-16-32">CID-16-32</a>.

---

### <a id="cid-16-71"></a>CID-16-71

**Qué hace:**
Carga el layout visual externo usado para mostrar el teclado del asistente.

**Cómo funciona:**
Intenta cargar `keyboard-layout.json` en la estructura de layout del estado global. Si falla, devuelve error detallado al llamador y aborta la ejecución del setup. Si tiene éxito, marca `layoutCargado` como verdadero.

**Pseudocódigo:**

```text
intentar cargar layout visual desde JSON
si falla:
    devolver error
marcar layout como cargado
```

**Relaciones:**

* Usa el módulo de layout visual incluido en <a href="#cid-16-02">CID-16-02</a>.
* Forma parte de <a href="#cid-16-69">CID-16-69</a>.
* Prepara el render usado por <a href="#cid-16-50">CID-16-50</a>.

---

### <a id="cid-16-72"></a>CID-16-72

**Qué hace:**
Registra la clase del asistente antes de crear la ventana principal.

**Cómo funciona:**
Llama al helper de registro de clase. Si este falla, el setup completo aborta sin intentar crear la ventana.

**Pseudocódigo:**

```text
intentar registrar clase del asistente
si falla:
    devolver falso
```

**Relaciones:**

* Usa <a href="#cid-16-68">CID-16-68</a>.
* Forma parte de <a href="#cid-16-69">CID-16-69</a>.
* Precede a <a href="#cid-16-73">CID-16-73</a>.

---

### <a id="cid-16-73"></a>CID-16-73

**Qué hace:**
Crea la ventana principal del asistente de calibración del teclado.

**Cómo funciona:**
Llama a `CreateWindowExW` con la clase registrada, el título del asistente y un estilo de ventana tradicional con caption, menú de sistema y minimizar. Si la creación falla, devuelve error. Si tiene éxito, guarda el `HWND`, inicializa el mensaje de estado, muestra y actualiza la ventana y la trae al frente.

**Pseudocódigo:**

```text
crear ventana principal del asistente
si falla:
    devolver error

guardar handle de ventana
inicializar mensaje de estado
mostrar ventana
actualizarla
traerla al frente y darle foco
```

**Relaciones:**

* Usa <a href="#cid-16-05">CID-16-05</a> y el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Forma parte de <a href="#cid-16-69">CID-16-69</a>.
* Precede a <a href="#cid-16-74">CID-16-74</a>.

---

### <a id="cid-16-74"></a>CID-16-74

**Qué hace:**
Mantiene el bucle modal del asistente y captura scanCodes antes del despacho normal.

**Cómo funciona:**
Ejecuta `GetMessageW` en un bucle. Cuando recibe un `WM_KEYDOWN` o `WM_SYSKEYDOWN` dirigido a la ventana del asistente, extrae el scanCode y, si no se está en modo prueba final y la tecla no es espacio, lo acepta directamente y consume el mensaje sin despacharlo. En el resto de casos, traduce y despacha normalmente.

**Pseudocódigo:**

```text
mientras haya mensajes válidos:
    si el mensaje es keydown del asistente:
        extraer scanCode
        si la tecla no es espacio y no está en prueba final:
            aceptar scanCode
            continuar

    traducir mensaje
    despachar mensaje
```

**Relaciones:**

* Usa <a href="#cid-16-34">CID-16-34</a>.
* Forma parte de <a href="#cid-16-69">CID-16-69</a>.
* El cierre del bucle viene dado por <a href="#cid-16-67">CID-16-67</a>.

---

### <a id="cid-16-75"></a>CID-16-75

**Qué hace:**
Traduce el resultado final del asistente a éxito real o mensaje de error para el llamador.

**Cómo funciona:**
Si `guardadoOk` no quedó activado, construye un error de salida priorizando `errorFinal`, luego cancelación del usuario y finalmente un error genérico de calibración incompleta. Si `guardadoOk` sí es verdadero, devuelve éxito.

**Pseudocódigo:**

```text
si no se guardó correctamente:
    si existe error final:
        devolver ese error
    si el usuario canceló:
        devolver error de cancelación
    devolver error genérico
    devolver falso

devolver verdadero
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-16-07">CID-16-07</a>.
* Forma parte de <a href="#cid-16-69">CID-16-69</a>.


## CID-17

La referencia <a href="#cid-17">CID-17</a> corresponde al archivo <code>setup_teclado_cid.h</code>. Este archivo actúa como interfaz pública del asistente de setup del teclado CID. Su responsabilidad principal es exponer al resto del motor la función encargada de ejecutar el asistente completo de calibración visual, capturar las asignaciones físicas del teclado y persistir el resultado final en disco.

Dentro de <a href="#cid-17">CID-17</a> también se define el contrato mínimo entre el arranque del motor y el subsistema de setup. Por eso aquí no aparece la lógica interna de ventana, render, pasos de calibración, captura de scanCodes o guardado de JSON, sino únicamente la declaración pública necesaria para invocar todo ese flujo desde fuera. En términos prácticos, <a href="#cid-17">CID-17</a> es la puerta pública de acceso al asistente de configuración inicial del teclado CID.

### Índice interno de bloques

* <a href="#cid-17-01">CID-17-01</a>
* <a href="#cid-17-02">CID-17-02</a>
* <a href="#cid-17-03">CID-17-03</a>
* <a href="#cid-17-04">CID-17-04</a>

---

### <a id="cid-17-01"></a>CID-17-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública del asistente de setup del teclado CID.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Así se evitan redefiniciones de declaraciones y conflictos por inclusión repetida.

**Pseudocódigo:**

```text
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-17">CID-17</a>.
* Asegura que <a href="#cid-17-04">CID-17-04</a> no se duplique al incluir esta cabecera desde distintos módulos.

---

### <a id="cid-17-02"></a>CID-17-02

**Qué hace:**
Incluye los tipos base de Windows usados por la API del asistente.

**Cómo funciona:**
Incorpora `<windows.h>` para disponer de tipos como `HINSTANCE`, necesarios en la firma pública del asistente de setup.

**Pseudocódigo:**

```text
incluir tipos base de Windows
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-17">CID-17</a>.
* Da soporte directo a <a href="#cid-17-04">CID-17-04</a>.

---

### <a id="cid-17-03"></a>CID-17-03

**Qué hace:**
Incluye el tipo de texto usado para rutas y mensajes de error del asistente.

**Cómo funciona:**
Incorpora `<string>` para disponer de `std::wstring`, tipo usado tanto para la ruta del archivo de calibración como para el buffer opcional de error.

**Pseudocódigo:**

```text
incluir soporte de cadenas anchas
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-17">CID-17</a>.
* Da soporte directo a <a href="#cid-17-04">CID-17-04</a>.

---

### <a id="cid-17-04"></a>CID-17-04

**Qué hace:**
Declara la ejecución completa del asistente de calibración y guardado del teclado CID.

**Cómo funciona:**
Expone una única función pública, `EjecutarSetupTecladoCID`, que recibe la instancia del proceso, la ruta del archivo de calibración a generar o sobrescribir y un buffer opcional donde dejar un mensaje de error detallado si el asistente falla o es cancelado.

**Pseudocódigo:**

```text
declarar función para ejecutar el asistente completo de setup del teclado
recibir instancia del proceso
recibir ruta del archivo de calibración
recibir buffer opcional de error
```

**Relaciones:**

* Usa `HINSTANCE` de <a href="#cid-17-02">CID-17-02</a> y `std::wstring` de <a href="#cid-17-03">CID-17-03</a>.
* Se implementa en <a href="#cid-16-69">CID-16-69</a>.
* Es consumida por el arranque del motor cuando aún no existe una calibración persistente válida.


## CID-18

La referencia <a href="#cid-18">CID-18</a> corresponde al archivo <code>panel_contexto_texto.cpp</code>. Este archivo implementa el panel de contexto de texto del sistema CID. Su responsabilidad principal es detectar si el foco actual del usuario se encuentra en un contexto realmente editable, decidir si la superposición CID debe mostrarse o esconderse, y mantener actualizada su posición de anclaje respecto al caret o al control activo.

Dentro de <a href="#cid-18">CID-18</a> también se concentra toda la lógica de temporización, debounce de aparición, ventana de activación por input escribible, detección Win32 directa, fallback mediante UI Automation y control de visibilidad del panel contextual. Por eso aquí no se dibuja el panel en sí, sino que se decide cuándo tiene sentido enseñarlo, dónde colocarlo y cuándo retirarlo para evitar apariciones agresivas o falsas. En términos prácticos, <a href="#cid-18">CID-18</a> es la pieza que hace que la superposición CID aparezca solo cuando realmente hay un contexto de escritura útil y reciente.

### Índice interno de bloques

* <a href="#cid-18-01">CID-18-01</a>
* <a href="#cid-18-02">CID-18-02</a>
* <a href="#cid-18-03">CID-18-03</a>
* <a href="#cid-18-04">CID-18-04</a>
* <a href="#cid-18-05">CID-18-05</a>
* <a href="#cid-18-06">CID-18-06</a>
* <a href="#cid-18-07">CID-18-07</a>
* <a href="#cid-18-08">CID-18-08</a>
* <a href="#cid-18-09">CID-18-09</a>
* <a href="#cid-18-10">CID-18-10</a>
* <a href="#cid-18-11">CID-18-11</a>
* <a href="#cid-18-12">CID-18-12</a>
* <a href="#cid-18-13">CID-18-13</a>
* <a href="#cid-18-14">CID-18-14</a>
* <a href="#cid-18-15">CID-18-15</a>
* <a href="#cid-18-16">CID-18-16</a>
* <a href="#cid-18-17">CID-18-17</a>
* <a href="#cid-18-18">CID-18-18</a>
* <a href="#cid-18-19">CID-18-19</a>
* <a href="#cid-18-20">CID-18-20</a>
* <a href="#cid-18-21">CID-18-21</a>
* <a href="#cid-18-22">CID-18-22</a>
* <a href="#cid-18-23">CID-18-23</a>
* <a href="#cid-18-24">CID-18-24</a>
* <a href="#cid-18-25">CID-18-25</a>
* <a href="#cid-18-26">CID-18-26</a>
* <a href="#cid-18-27">CID-18-27</a>
* <a href="#cid-18-28">CID-18-28</a>
* <a href="#cid-18-29">CID-18-29</a>
* <a href="#cid-18-30">CID-18-30</a>
* <a href="#cid-18-31">CID-18-31</a>
* <a href="#cid-18-32">CID-18-32</a>
* <a href="#cid-18-33">CID-18-33</a>
* <a href="#cid-18-34">CID-18-34</a>
* <a href="#cid-18-35">CID-18-35</a>
* <a href="#cid-18-36">CID-18-36</a>
* <a href="#cid-18-37">CID-18-37</a>
* <a href="#cid-18-38">CID-18-38</a>
* <a href="#cid-18-39">CID-18-39</a>
* <a href="#cid-18-40">CID-18-40</a>
* <a href="#cid-18-41">CID-18-41</a>
* <a href="#cid-18-42">CID-18-42</a>
* <a href="#cid-18-43">CID-18-43</a>
* <a href="#cid-18-44">CID-18-44</a>
* <a href="#cid-18-45">CID-18-45</a>
* <a href="#cid-18-46">CID-18-46</a>
* <a href="#cid-18-47">CID-18-47</a>

---

### <a id="cid-18-01"></a>CID-18-01

**Qué hace:**
Incluye la implementación del panel de contexto de texto del sistema CID a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `panel_contexto_texto.h`, que declara las funciones públicas del subsistema de contexto. Gracias a esta inclusión, el archivo actual puede definir su lógica real de arranque, parada, actualización inmediata y notificación de actividad escribible.

**Pseudocódigo:**

```text
incluir interfaz pública del panel de contexto de texto
habilitar definición de sus funciones públicas
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-18">CID-18</a>.
* Da soporte directo a <a href="#cid-18-44">CID-18-44</a> a <a href="#cid-18-47">CID-18-47</a>.

---

### <a id="cid-18-02"></a>CID-18-02

**Qué hace:**
Incluye la superposición visual controlada por el detector de contexto editable.

**Cómo funciona:**
Conecta este módulo con `superposicion_cid.h`, permitiéndole mostrar u ocultar el panel visual y actualizar su rectángulo de anclaje en función del contexto de texto detectado.

**Pseudocódigo:**

```text
incluir módulo de superposición visual
habilitar control de visibilidad y anclaje del panel
```

**Relaciones:**

* Da soporte directo a <a href="#cid-18-37">CID-18-37</a>, <a href="#cid-18-39">CID-18-39</a>, <a href="#cid-18-40">CID-18-40</a>, <a href="#cid-18-41">CID-18-41</a> y <a href="#cid-18-45">CID-18-45</a>.
* Enlaza con el subsistema documentado en <a href="#cid-12">CID-12</a> y <a href="#cid-13">CID-13</a>.

---

### <a id="cid-18-03"></a>CID-18-03

**Qué hace:**
Incluye cabeceras del sistema, UI Automation y utilidades de texto.

**Cómo funciona:**
Este bloque habilita acceso a la API Win32, a UI Automation y a `std::wstring`. No contiene lógica ejecutable, pero prepara las dependencias necesarias para detección de foco, caret, rectángulos y elementos editables modernos.

**Pseudocódigo:**

```text
incluir API base de Windows
incluir UI Automation
incluir soporte de cadenas anchas
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-18">CID-18</a>.
* Da soporte indirecto a <a href="#cid-18-31">CID-18-31</a>, <a href="#cid-18-32">CID-18-32</a>, <a href="#cid-18-43">CID-18-43</a> y al resto de bloques con lógica Win32 o COM.

---

### <a id="cid-18-04"></a>CID-18-04

**Qué hace:**
Vincula explícitamente las bibliotecas necesarias para UI Automation y COM.

**Cómo funciona:**
Usa dos directivas `#pragma comment(lib, ...)` para pedir al enlazador las bibliotecas `Uiautomationcore.lib` y `Ole32.lib`, requeridas por la lógica de UI Automation y por la infraestructura COM.

**Pseudocódigo:**

```text
vincular biblioteca de UI Automation
vincular biblioteca base de COM
```

**Relaciones:**

* Da soporte de enlace a <a href="#cid-18-31">CID-18-31</a>.
* Prepara el uso de COM y UIA dentro de <a href="#cid-18">CID-18</a>.

---

### <a id="cid-18-05"></a>CID-18-05

**Qué hace:**
Declara el estado global de sincronización y del ciclo de vida del panel de contexto.

**Cómo funciona:**
Reserva una sección crítica global, una bandera de inicialización, la cola y el temporizador periódicos y una bandera `g_iniciado`. Estos elementos controlan tanto la sincronización como el arranque y la parada efectiva del subsistema.

**Pseudocódigo:**

```text
declarar sección crítica global
declarar bandera de inicialización
declarar cola y temporizador periódicos
declarar bandera de subsistema iniciado
```

**Relaciones:**

* Es usado por <a href="#cid-18-43">CID-18-43</a>, <a href="#cid-18-44">CID-18-44</a>, <a href="#cid-18-45">CID-18-45</a>, <a href="#cid-18-46">CID-18-46</a> y <a href="#cid-18-47">CID-18-47</a>.

---

### <a id="cid-18-06"></a>CID-18-06

**Qué hace:**
Define los parámetros temporales de chequeo, debounce de aparición y ventana de activación por input.

**Cómo funciona:**
Declara tres constantes: el intervalo periódico de chequeo, el tiempo mínimo estable antes de mostrar el panel y la ventana máxima durante la cual una actividad escribible reciente sigue habilitando la aparición del panel.

**Pseudocódigo:**

```text
definir periodo de chequeo periódico
definir debounce mínimo para mostrar
definir ventana de activación por input escribible
```

**Relaciones:**

* Es usado por <a href="#cid-18-38">CID-18-38</a>, <a href="#cid-18-39">CID-18-39</a>, <a href="#cid-18-44">CID-18-44</a> y <a href="#cid-18-47">CID-18-47</a>.

---

### <a id="cid-18-07"></a>CID-18-07

**Qué hace:**
Declara el último estado visible aplicado y los últimos datos de foco, rectángulo y logging.

**Cómo funciona:**
Mantiene banderas y valores globales para recordar si el panel está visible, cuál fue el último rectángulo aplicado, qué ventanas estaban implicadas y qué clase u origen se registró por última vez. Esto permite evitar logs repetidos y cambios visuales innecesarios.

**Pseudocódigo:**

```text
declarar última visibilidad aplicada
declarar último rectángulo aplicado
declarar últimas ventanas foreground y focus
declarar última clase y último origen registrados
```

**Relaciones:**

* Es usado por <a href="#cid-18-36">CID-18-36</a> a <a href="#cid-18-41">CID-18-41</a> y reiniciado en <a href="#cid-18-44">CID-18-44</a> y <a href="#cid-18-45">CID-18-45</a>.

---

### <a id="cid-18-08"></a>CID-18-08

**Qué hace:**
Mantiene la marca temporal del último input realmente escribible detectado.

**Cómo funciona:**
Declara un tick global inicialmente a cero que se actualiza cuando el sistema detecta actividad escribible reciente. Ese tick se usa más tarde para decidir si aún tiene sentido mostrar el panel contextual.

**Pseudocódigo:**

```text
declarar tick global de último input escribible
inicializarlo a cero
```

**Relaciones:**

* Es usado por <a href="#cid-18-36">CID-18-36</a>, reiniciado en <a href="#cid-18-44">CID-18-44</a> y <a href="#cid-18-45">CID-18-45</a>, y actualizado en <a href="#cid-18-47">CID-18-47</a>.

---

### <a id="cid-18-09"></a>CID-18-09

**Qué hace:**
Define la estructura del contexto de texto detectado en un momento dado.

**Cómo funciona:**
Agrupa en una sola estructura la visibilidad detectada, el rectángulo de anclaje, la ventana foreground, la ventana de foco, la clase del foco y el origen de la detección. Esta instantánea se usa como resultado del resolvedor de contexto.

**Pseudocódigo:**

```text
definir estructura de contexto detectado
guardar visibilidad
guardar rectángulo de anclaje
guardar foreground y focus
guardar clase y origen de detección
```

**Relaciones:**

* Es usada por <a href="#cid-18-10">CID-18-10</a>, <a href="#cid-18-32">CID-18-32</a>, <a href="#cid-18-36">CID-18-36</a>, <a href="#cid-18-42">CID-18-42</a> y <a href="#cid-18-45">CID-18-45</a>.

---

### <a id="cid-18-10"></a>CID-18-10

**Qué hace:**
Declara el estado del candidato pendiente antes de mostrar el panel tras debounce.

**Cómo funciona:**
Mantiene una bandera que indica si existe un candidato actual de contexto, la propia estructura candidata y el tick desde el que se viene observando. Esto permite exigir estabilidad mínima antes de enseñar el panel por primera vez.

**Pseudocódigo:**

```text
declarar si existe candidato pendiente
guardar contexto candidato
guardar tick de inicio del candidato
```

**Relaciones:**

* Usa la estructura definida en <a href="#cid-18-09">CID-18-09</a>.
* Es usado por <a href="#cid-18-37">CID-18-37</a>, <a href="#cid-18-38">CID-18-38</a>, <a href="#cid-18-39">CID-18-39</a>, <a href="#cid-18-40">CID-18-40</a>, <a href="#cid-18-44">CID-18-44</a> y <a href="#cid-18-45">CID-18-45</a>.

---

### <a id="cid-18-11"></a>CID-18-11

**Qué hace:**
Envía mensajes de depuración del panel de contexto al visor de salida de Windows.

**Cómo funciona:**
Recibe una cadena ancha, le concatena un salto de línea y la envía mediante `OutputDebugStringW`. Con ello unifica el registro interno del subsistema.

**Pseudocódigo:**

```text
añadir salto de línea al mensaje
enviar mensaje al depurador de Windows
```

**Relaciones:**

* Es usado por <a href="#cid-18-36">CID-18-36</a> a <a href="#cid-18-41">CID-18-41</a>.

---

### <a id="cid-18-12"></a>CID-18-12

**Qué hace:**
Libera de forma segura una interfaz COM y la pone a null.

**Cómo funciona:**
Comprueba si el puntero recibido existe. Si existe, llama a `Release()` y luego lo pone a `nullptr`. Esto evita duplicar código de liberación de interfaces COM.

**Pseudocódigo:**

```text
si el puntero COM existe:
    liberar interfaz
    poner puntero a nulo
```

**Relaciones:**

* Es usada por <a href="#cid-18-31">CID-18-31</a>.

---

### <a id="cid-18-13"></a>CID-18-13

**Qué hace:**
Devuelve el valor absoluto entero usado en comparaciones geométricas.

**Cómo funciona:**
Si el entero es negativo devuelve su opuesto; si no, devuelve el mismo valor.

**Pseudocódigo:**

```text
si x es negativo:
    devolver -x
devolver x
```

**Relaciones:**

* Es usada por <a href="#cid-18-15">CID-18-15</a>.

---

### <a id="cid-18-14"></a>CID-18-14

**Qué hace:**
Comprueba si dos rectángulos son exactamente iguales.

**Cómo funciona:**
Compara los cuatro bordes de ambos rectángulos y devuelve `true` solo si todos coinciden exactamente.

**Pseudocódigo:**

```text
comparar left, top, right y bottom
devolver si todos son iguales
```

**Relaciones:**

* Es un helper geométrico disponible para el módulo <a href="#cid-18">CID-18</a>.

---

### <a id="cid-18-15"></a>CID-18-15

**Qué hace:**
Comprueba si dos rectángulos son suficientemente parecidos dentro de una tolerancia dada.

**Cómo funciona:**
Calcula la diferencia absoluta entre los cuatro bordes de ambos rectángulos y exige que todas queden dentro del umbral `tol`.

**Pseudocódigo:**

```text
comparar diferencias absolutas de los cuatro bordes
devolver si todas están dentro de la tolerancia
```

**Relaciones:**

* Usa <a href="#cid-18-13">CID-18-13</a>.
* Es usada por <a href="#cid-18-39">CID-18-39</a> y <a href="#cid-18-41">CID-18-41</a>.

---

### <a id="cid-18-16"></a>CID-18-16

**Qué hace:**
Comprueba si un rectángulo tiene dimensiones positivas utilizables.

**Cómo funciona:**
Verifica que `right` sea mayor que `left` y que `bottom` sea mayor que `top`. Solo en ese caso el rectángulo se considera válido.

**Pseudocódigo:**

```text
devolver si el rectángulo tiene ancho y alto positivos
```

**Relaciones:**

* Es usada por <a href="#cid-18-21">CID-18-21</a>, <a href="#cid-18-25">CID-18-25</a>, <a href="#cid-18-31">CID-18-31</a> y <a href="#cid-18-32">CID-18-32</a>.

---

### <a id="cid-18-17"></a>CID-18-17

**Qué hace:**
Normaliza el rectángulo de caret para asegurar ancho y alto mínimos visibles.

**Cómo funciona:**
Si el rectángulo no tiene ancho, le fuerza dos píxeles. Si no tiene alto, le fuerza veinte. Además, si el alto final sigue siendo muy pequeño, lo lleva al menos a dieciocho píxeles.

**Pseudocódigo:**

```text
si el ancho no es válido:
    forzar ancho mínimo
si el alto no es válido:
    forzar alto mínimo
si el alto sigue siendo pequeño:
    ampliarlo
```

**Relaciones:**

* Es usada por <a href="#cid-18-26">CID-18-26</a>.

---

### <a id="cid-18-18"></a>CID-18-18

**Qué hace:**
Devuelve el nombre de clase Win32 asociado a una ventana dada.

**Cómo funciona:**
Si la ventana es nula devuelve vacío. Si existe, llama a `GetClassNameW` y devuelve la clase como `std::wstring`.

**Pseudocódigo:**

```text
si la ventana es nula:
    devolver vacío
leer nombre de clase de la ventana
devolver clase
```

**Relaciones:**

* Es usada por <a href="#cid-18-20">CID-18-20</a>, <a href="#cid-18-22">CID-18-22</a>, <a href="#cid-18-23">CID-18-23</a>, <a href="#cid-18-30">CID-18-30</a> y <a href="#cid-18-32">CID-18-32</a>.

---

### <a id="cid-18-19"></a>CID-18-19

**Qué hace:**
Comprueba si una cadena contiene otra subcadena.

**Cómo funciona:**
Llama a `find` sobre la cadena principal y devuelve si la subcadena aparece en alguna posición válida.

**Pseudocódigo:**

```text
buscar subcadena dentro de la cadena principal
devolver si se encontró
```

**Relaciones:**

* Es usada por <a href="#cid-18-22">CID-18-22</a>.

---

### <a id="cid-18-20"></a>CID-18-20

**Qué hace:**
Comprueba si una ventana pertenece exactamente a una clase Win32 dada.

**Cómo funciona:**
Obtiene la clase de la ventana y la compara con el nombre objetivo usando comparación insensible a mayúsculas/minúsculas.

**Pseudocódigo:**

```text
obtener clase de la ventana
compararla con el nombre objetivo
devolver si coinciden
```

**Relaciones:**

* Usa <a href="#cid-18-18">CID-18-18</a>.
* Es usada por <a href="#cid-18-21">CID-18-21</a> y <a href="#cid-18-24">CID-18-24</a>.

---

### <a id="cid-18-21"></a>CID-18-21

**Qué hace:**
Identifica controles Win32 que son claramente editables sin recurrir a UI Automation.

**Cómo funciona:**
Si la ventana es nula devuelve falso. Si existe, comprueba si su clase coincide con una lista de controles conocidos editables como `Edit`, varias variantes de `RichEdit` o `Scintilla`.

**Pseudocódigo:**

```text
si no hay ventana:
    devolver falso

devolver si la clase pertenece a una lista de controles editables claros
```

**Relaciones:**

* Usa <a href="#cid-18-20">CID-18-20</a>.
* Es usada por <a href="#cid-18-34">CID-18-34</a>.

---

### <a id="cid-18-22"></a>CID-18-22

**Qué hace:**
Identifica clases modernas o wrappers donde suele ser necesario usar UI Automation.

**Cómo funciona:**
Compara la clase recibida con varias clases modernas conocidas de Firefox, Windows moderno, Chromium, Internet Explorer embebido y wrappers WPF, incluyendo coincidencias parciales con `HwndWrapper[`.

**Pseudocódigo:**

```text
comparar la clase con una lista de wrappers modernos conocidos
devolver verdadero si coincide alguno
```

**Relaciones:**

* Usa <a href="#cid-18-19">CID-18-19</a>.
* Es usada por <a href="#cid-18-30">CID-18-30</a>.

---

### <a id="cid-18-23"></a>CID-18-23

**Qué hace:**
Identifica clases Win32 claramente no editables para evitar falsos positivos.

**Cómo funciona:**
Si la ventana es nula la considera no editable. Si existe, obtiene su clase y la compara con una lista de clases de botones, estáticos, listas, barras, árbol y elementos de shell que no deben activar el panel contextual.

**Pseudocódigo:**

```text
si no hay ventana:
    devolver verdadero

obtener clase de la ventana
devolver si pertenece a una lista de clases claramente no editables
```

**Relaciones:**

* Usa <a href="#cid-18-18">CID-18-18</a>.
* Es usada por <a href="#cid-18-34">CID-18-34</a> y <a href="#cid-18-35">CID-18-35</a>.

---

### <a id="cid-18-24"></a>CID-18-24

**Qué hace:**
En controles Edit puros comprueba además que no estén en modo solo lectura.

**Cómo funciona:**
Si la ventana es nula devuelve falso. Si la clase no es `Edit`, devuelve verdadero porque la restricción solo aplica a ese caso. Si sí es `Edit`, lee el estilo y exige que no tenga activado `ES_READONLY`.

**Pseudocódigo:**

```text
si no hay ventana:
    devolver falso
si no es clase Edit:
    devolver verdadero
leer estilo de la ventana
devolver si no tiene solo lectura
```

**Relaciones:**

* Usa <a href="#cid-18-20">CID-18-20</a>.
* Es usada por <a href="#cid-18-34">CID-18-34</a>.

---

### <a id="cid-18-25"></a>CID-18-25

**Qué hace:**
Obtiene el rectángulo en pantalla de una ventana válida.

**Cómo funciona:**
Comprueba que la ventana exista y sea válida, llama a `GetWindowRect` y además exige que el rectángulo resultante sea geométricamente válido antes de devolverlo.

**Pseudocódigo:**

```text
si la ventana no existe o no es válida:
    devolver falso
obtener rectángulo de pantalla
si falla:
    devolver falso
si el rectángulo no es válido:
    devolver falso
devolver rectángulo y éxito
```

**Relaciones:**

* Usa <a href="#cid-18-16">CID-18-16</a>.
* Es usada por <a href="#cid-18-28">CID-18-28</a> y <a href="#cid-18-34">CID-18-34</a>.

---

### <a id="cid-18-26"></a>CID-18-26

**Qué hace:**
Obtiene y normaliza el rectángulo real del caret en coordenadas de pantalla.

**Cómo funciona:**
Comprueba que exista una ventana de caret válida, toma `rcCaret`, exige que el alto sea positivo, lo transforma a coordenadas de escritorio con `MapWindowPoints`, normaliza su tamaño mínimo y devuelve el resultado.

**Pseudocódigo:**

```text
si no hay caret válido:
    devolver falso

copiar rectángulo del caret
si el alto no es válido:
    devolver falso

convertir a coordenadas de pantalla
normalizar tamaño del caret
devolver rectángulo y éxito
```

**Relaciones:**

* Usa <a href="#cid-18-17">CID-18-17</a>.
* Es usada por <a href="#cid-18-33">CID-18-33</a>.

---

### <a id="cid-18-27"></a>CID-18-27

**Qué hace:**
Intenta obtener el foco real del hilo foreground mediante `AttachThreadInput`.

**Cómo funciona:**
Parte de la ventana foreground, obtiene su thread id y el thread actual, une temporalmente ambos hilos de input, consulta `GetFocus()` y luego deshace el acoplamiento. Si algo falla, devuelve nulo.

**Pseudocódigo:**

```text
si no hay ventana foreground:
    devolver nulo

obtener thread del foreground y thread actual
si no hay thread foreground:
    devolver nulo

adjuntar input entre hilos
si funciona:
    leer foco real
    desadjuntar input

devolver foco obtenido
```

**Relaciones:**

* Es usada por <a href="#cid-18-32">CID-18-32</a>.

---

### <a id="cid-18-28"></a>CID-18-28

**Qué hace:**
Comprueba si un rectángulo UIA es sospechosamente grande respecto a la ventana foreground.

**Cómo funciona:**
Obtiene el rectángulo de la ventana foreground, calcula anchuras, alturas y áreas de ambos rectángulos y considera sospechoso el rectángulo UIA si su área supera aproximadamente el 65% del área de la ventana completa.

**Pseudocódigo:**

```text
obtener rectángulo de la ventana foreground
si no se puede o las dimensiones no son válidas:
    devolver falso

calcular áreas del rectángulo UIA y de la ventana
calcular ratio entre áreas
devolver si el ratio es demasiado grande
```

**Relaciones:**

* Usa <a href="#cid-18-25">CID-18-25</a>.
* Es usada por <a href="#cid-18-31">CID-18-31</a>.

---

### <a id="cid-18-29"></a>CID-18-29

**Qué hace:**
Identifica `HRESULT` de desconexión o elementos UIA no disponibles.

**Cómo funciona:**
Compara el código recibido con varios `HRESULT` típicos de desconexión RPC, objeto COM no conectado o elemento UIA no disponible y devuelve si pertenece a ese conjunto tolerable.

**Pseudocódigo:**

```text
comparar HRESULT con lista de errores tolerables de desconexión
devolver si coincide alguno
```

**Relaciones:**

* Es usada por <a href="#cid-18-31">CID-18-31</a>.

---

### <a id="cid-18-30"></a>CID-18-30

**Qué hace:**
Decide si conviene activar el fallback de UI Automation según clases modernas detectadas.

**Cómo funciona:**
Obtiene las clases del foco y de la ventana foreground. Si cualquiera de las dos parece un wrapper moderno compatible, devuelve verdadero.

**Pseudocódigo:**

```text
obtener clase del foco
obtener clase del foreground

si la clase del foco es wrapper moderno:
    devolver verdadero
si la clase del foreground es wrapper moderno:
    devolver verdadero

devolver falso
```

**Relaciones:**

* Usa <a href="#cid-18-18">CID-18-18</a> y <a href="#cid-18-22">CID-18-22</a>.
* Es usada por <a href="#cid-18-35">CID-18-35</a>.

---

### <a id="cid-18-31"></a>CID-18-31

**Qué hace:**
Intenta localizar un elemento enfocado editable mediante UI Automation y obtener su rectángulo.

**Cómo funciona:**
Inicializa COM, crea una instancia de `IUIAutomation`, obtiene el elemento enfocado y extrae información como tipo de control, foco de teclado, rectángulo, clase y nombre. Luego intenta obtener `ValuePattern` y `TextPattern`. Si el elemento tiene rectángulo válido, es focusable, soporta texto y además es un `Edit` o un `Document` no sospechosamente gigante, acepta el rectángulo y devuelve éxito. Finalmente libera todos los recursos COM y desinicializa COM si procede.

**Pseudocódigo:**

```text
inicializar COM si hace falta
crear automatización UIA
obtener elemento enfocado
leer tipo de control, focusable, rectángulo, clase y nombre
intentar obtener patrones de valor y texto
construir información de depuración

si el rectángulo es válido, el elemento es focusable y soporta texto:
    si es control Edit:
        aceptar
    si es Documento y no es gigantesco respecto a la ventana:
        aceptar

si fue aceptado:
    devolver rectángulo y éxito

liberar patrones, elemento y automatización
desinicializar COM si procede
devolver resultado
```

**Relaciones:**

* Usa <a href="#cid-18-12">CID-18-12</a>, <a href="#cid-18-16">CID-18-16</a>, <a href="#cid-18-28">CID-18-28</a> y <a href="#cid-18-29">CID-18-29</a>.
* Es usada por <a href="#cid-18-35">CID-18-35</a>.

---

### <a id="cid-18-32"></a>CID-18-32

**Qué hace:**
Resuelve el mejor contexto de texto editable disponible usando caret, Win32 claro o UIA.

**Cómo funciona:**
Parte de la ventana foreground actual y obtiene información GUI del hilo. Intenta recuperar el foco real, rellena un contexto base y luego prueba tres estrategias en orden: caret Win32 real, control Win32 claramente editable y fallback estricto mediante UI Automation. Devuelve el primer contexto válido que encuentre.

**Pseudocódigo:**

```text
crear contexto vacío
obtener ventana foreground
si no existe o no sirve:
    devolver contexto vacío

obtener thread del foreground
obtener información GUI del hilo
resolver foco real si hace falta

rellenar contexto base
probar caso caret Win32
probar control editable Win32 claro
probar fallback UIA estricto

devolver contexto detectado o vacío
```

**Relaciones:**

* Contiene internamente <a href="#cid-18-33">CID-18-33</a> a <a href="#cid-18-35">CID-18-35</a>.
* Usa <a href="#cid-18-26">CID-18-26</a>, <a href="#cid-18-27">CID-18-27</a>, <a href="#cid-18-21">CID-18-21</a>, <a href="#cid-18-23">CID-18-23</a>, <a href="#cid-18-24">CID-18-24</a>, <a href="#cid-18-25">CID-18-25</a>, <a href="#cid-18-30">CID-18-30</a> y <a href="#cid-18-31">CID-18-31</a>.
* Es llamada desde <a href="#cid-18-42">CID-18-42</a>.

---

### <a id="cid-18-33"></a>CID-18-33

**Qué hace:**
Implementa el caso preferente basado en un caret Win32 real.

**Cómo funciona:**
Intenta obtener el rectángulo del caret en pantalla. Si lo consigue, marca el contexto como visible, usa ese rectángulo como anclaje y fija el origen como `caret-win32`.

**Pseudocódigo:**

```text
intentar obtener rectángulo del caret en pantalla
si funciona:
    marcar contexto visible
    usar caret como rectángulo de anclaje
    marcar origen caret-win32
    devolver contexto
```

**Relaciones:**

* Usa <a href="#cid-18-26">CID-18-26</a>.
* Forma parte de <a href="#cid-18-32">CID-18-32</a>.

---

### <a id="cid-18-34"></a>CID-18-34

**Qué hace:**
Implementa el fallback sobre controles editables Win32 claramente reconocibles.

**Cómo funciona:**
Si existe ventana de foco, comprueba que su clase sea claramente editable, que no sea readonly cuando proceda y que no pertenezca a una clase claramente no editable. Si todo cuadra, obtiene el rectángulo de pantalla del control y lo usa como anclaje visible con origen `control-win32`.

**Pseudocódigo:**

```text
si hay foco y la clase es claramente editable
y no es readonly
y no es claramente no editable:
    obtener rectángulo del control
    si funciona:
        marcar contexto visible
        usar rectángulo del control como anclaje
        marcar origen control-win32
        devolver contexto
```

**Relaciones:**

* Usa <a href="#cid-18-21">CID-18-21</a>, <a href="#cid-18-24">CID-18-24</a>, <a href="#cid-18-23">CID-18-23</a> y <a href="#cid-18-25">CID-18-25</a>.
* Forma parte de <a href="#cid-18-32">CID-18-32</a>.

---

### <a id="cid-18-35"></a>CID-18-35

**Qué hace:**
Implementa el fallback estricto por UI Automation solo para wrappers modernos compatibles.

**Cómo funciona:**
Exige que exista foco, que no se trate de una clase claramente no editable y que realmente convenga usar UI Automation según las clases modernas detectadas. Si esas condiciones se cumplen, intenta resolver un rectángulo UIA y lo usa como anclaje visible con el origen descriptivo devuelto por UIA.

**Pseudocódigo:**

```text
si hay foco
y no es claramente no editable
y necesita fallback UIA:
    intentar obtener rectángulo UIA
    si funciona:
        marcar contexto visible
        usar rectángulo UIA como anclaje
        guardar origen descriptivo
        devolver contexto
```

**Relaciones:**

* Usa <a href="#cid-18-23">CID-18-23</a>, <a href="#cid-18-30">CID-18-30</a> y <a href="#cid-18-31">CID-18-31</a>.
* Forma parte de <a href="#cid-18-32">CID-18-32</a>.

---

### <a id="cid-18-36"></a>CID-18-36

**Qué hace:**
Aplica el contexto detectado si cambia, con debounce de aparición y control de foco activo.

**Cómo funciona:**
Registra cambios de clase de foco, calcula si hubo actividad escribible reciente y luego gestiona cuatro grandes casos: desaparición total del contexto, bloqueo de aparición por falta de actividad reciente, debounce antes de la primera aparición y actualización cuando el panel ya está visible. En este último caso puede ocultar por cambio de foco o reposicionar por cambio apreciable del rectángulo.

**Pseudocódigo:**

```text
registrar cambios de clase de foco si hace falta
calcular si hubo actividad escribible reciente

si no hay contexto visible:
    ocultar panel si estaba visible
    limpiar candidato
    salir

si el panel aún no está visible y no hubo actividad reciente:
    limpiar candidato
    salir

si el panel aún no está visible:
    gestionar candidato y debounce
    si ya pasó el debounce:
        mostrar panel y fijar anclaje
    salir

si el panel ya estaba visible:
    si cambió de foco real:
        ocultar panel y reiniciar candidato
        salir
    si cambió el rectángulo de forma apreciable:
        actualizar anclaje
```

**Relaciones:**

* Contiene internamente <a href="#cid-18-37">CID-18-37</a> a <a href="#cid-18-41">CID-18-41</a>.
* Usa <a href="#cid-18-06">CID-18-06</a>, <a href="#cid-18-07">CID-18-07</a>, <a href="#cid-18-08">CID-18-08</a>, <a href="#cid-18-10">CID-18-10</a>, <a href="#cid-18-11">CID-18-11</a>, <a href="#cid-18-15">CID-18-15</a> y el control visual de <a href="#cid-18-02">CID-18-02</a>.
* Es llamada desde <a href="#cid-18-42">CID-18-42</a>.

---

### <a id="cid-18-37"></a>CID-18-37

**Qué hace:**
Oculta el panel y limpia el candidato si ya no hay contexto editable visible.

**Cómo funciona:**
Resetea el estado de candidato y, si el panel estaba visible, apaga la visibilidad, limpia el rectángulo recordado, actualiza las ventanas recordadas y pide a la superposición que se esconda.

**Pseudocódigo:**

```text
limpiar candidato pendiente

si el panel estaba visible:
    marcarlo como no visible
    limpiar rectángulo recordado
    actualizar foreground y focus recordados
    escribir log de ocultación
    ocultar superposición
```

**Relaciones:**

* Usa el estado de <a href="#cid-18-07">CID-18-07</a>, <a href="#cid-18-10">CID-18-10</a>, <a href="#cid-18-11">CID-18-11</a> y la superposición de <a href="#cid-18-02">CID-18-02</a>.
* Forma parte de <a href="#cid-18-36">CID-18-36</a>.

---

### <a id="cid-18-38"></a>CID-18-38

**Qué hace:**
Mientras el panel aún no está visible, exige actividad escribible reciente para mostrarlo.

**Cómo funciona:**
Si el panel todavía no está visible y no existe actividad escribible dentro de la ventana temporal permitida, limpia cualquier candidato pendiente y retorna sin mostrar nada.

**Pseudocódigo:**

```text
si el panel no está visible y no hubo actividad reciente:
    limpiar candidato
    salir
```

**Relaciones:**

* Usa <a href="#cid-18-06">CID-18-06</a>, <a href="#cid-18-08">CID-18-08</a> y <a href="#cid-18-10">CID-18-10</a>.
* Forma parte de <a href="#cid-18-36">CID-18-36</a>.

---

### <a id="cid-18-39"></a>CID-18-39

**Qué hace:**
Gestiona el debounce inicial antes de hacer visible el panel por primera vez.

**Cómo funciona:**
Comprueba si el contexto actual coincide aproximadamente con el candidato pendiente. Si no coincide, reemplaza el candidato y reinicia su tick. Si coincide pero aún no ha transcurrido el debounce, espera. Si ya ha pasado el tiempo mínimo, hace visible el panel, registra el origen, actualiza ventanas y rectángulo recordados y comunica el anclaje a la superposición.

**Pseudocódigo:**

```text
comprobar si el contexto actual coincide con el candidato pendiente
si no coincide:
    guardar nuevo candidato
    reiniciar tick de candidato
    salir

si aún no ha pasado el debounce:
    salir

marcar panel como visible
guardar rectángulo y ventanas actuales
registrar origen si cambió
escribir log de aparición
enviar rectángulo de anclaje
mostrar superposición
```

**Relaciones:**

* Usa <a href="#cid-18-06">CID-18-06</a>, <a href="#cid-18-07">CID-18-07</a>, <a href="#cid-18-10">CID-18-10</a>, <a href="#cid-18-11">CID-18-11</a>, <a href="#cid-18-15">CID-18-15</a> y la superposición de <a href="#cid-18-02">CID-18-02</a>.
* Forma parte de <a href="#cid-18-36">CID-18-36</a>.

---

### <a id="cid-18-40"></a>CID-18-40

**Qué hace:**
Si cambia la ventana o el foco real, esconde el panel y reinicia el ciclo de candidato.

**Cómo funciona:**
Compara la ventana foreground y la de foco del contexto actual con las últimas recordadas. Si alguna cambió, considera que el panel ya no debe seguir visible en continuidad y lo oculta, reseteando además el estado de candidato.

**Pseudocódigo:**

```text
comprobar si cambió foreground o focus
si cambió:
    marcar panel como no visible
    limpiar candidato
    ocultar superposición
    salir
```

**Relaciones:**

* Usa <a href="#cid-18-07">CID-18-07</a>, <a href="#cid-18-10">CID-18-10</a> y la superposición de <a href="#cid-18-02">CID-18-02</a>.
* Forma parte de <a href="#cid-18-36">CID-18-36</a>.

---

### <a id="cid-18-41"></a>CID-18-41

**Qué hace:**
Si cambia de forma apreciable el rectángulo de anclaje, reposiciona la superposición.

**Cómo funciona:**
Compara el rectángulo actual con el último recordado usando una tolerancia pequeña. Si difieren más de lo permitido, actualiza el rectángulo almacenado, registra el origen si cambió y envía el nuevo rectángulo de anclaje a la superposición.

**Pseudocódigo:**

```text
si el rectángulo actual difiere apreciablemente del último:
    guardar nuevo rectángulo
    registrar origen si cambió
    escribir log de nueva posición
    enviar nuevo rectángulo a la superposición
```

**Relaciones:**

* Usa <a href="#cid-18-07">CID-18-07</a>, <a href="#cid-18-11">CID-18-11</a>, <a href="#cid-18-15">CID-18-15</a> y la superposición de <a href="#cid-18-02">CID-18-02</a>.
* Forma parte de <a href="#cid-18-36">CID-18-36</a>.

---

### <a id="cid-18-42"></a>CID-18-42

**Qué hace:**
Resuelve el contexto actual y aplica los cambios necesarios sobre el panel.

**Cómo funciona:**
Llama al resolvedor de contexto para obtener la mejor instantánea posible del entorno editable actual y, a continuación, delega la decisión de visibilidad, debounce y reposicionamiento en el aplicador de contexto.

**Pseudocódigo:**

```text
resolver contexto editable actual
aplicar cambios sobre el panel según ese contexto
```

**Relaciones:**

* Usa <a href="#cid-18-32">CID-18-32</a> y <a href="#cid-18-36">CID-18-36</a>.
* Es llamada desde <a href="#cid-18-43">CID-18-43</a>, <a href="#cid-18-44">CID-18-44</a> y <a href="#cid-18-46">CID-18-46</a>.

---

### <a id="cid-18-43"></a>CID-18-43

**Qué hace:**
Implementa el callback periódico del temporizador que refresca el contexto editable actual.

**Cómo funciona:**
Comprueba primero que la sincronización exista. Si existe, entra en la sección crítica, llama a la rutina de actualización de contexto y sale del bloqueo.

**Pseudocódigo:**

```text
si no hay sincronización iniciada:
    salir

entrar en sección crítica
actualizar contexto actual
salir de sección crítica
```

**Relaciones:**

* Usa <a href="#cid-18-05">CID-18-05</a> y <a href="#cid-18-42">CID-18-42</a>.
* Es registrado como callback en <a href="#cid-18-44">CID-18-44</a>.

---

### <a id="cid-18-44"></a>CID-18-44

**Qué hace:**
Inicializa el panel de contexto, su temporizador y su estado base de detección.

**Cómo funciona:**
Inicializa la sección crítica si hace falta, entra en ella y reinicia todos los campos internos: visibilidad, rectángulos, ventanas, logs, actividad reciente y candidato. Luego crea la cola de temporizadores si no existe, intenta crear el temporizador periódico y, si todo va bien, marca el subsistema como iniciado y fuerza una primera actualización inmediata del contexto.

**Pseudocódigo:**

```text
inicializar sección crítica si hace falta
entrar en sección crítica

reiniciar estado interno del panel de contexto

crear cola de temporizadores si hace falta
crear temporizador periódico si hace falta

si todo fue bien:
    marcar subsistema como iniciado
    actualizar contexto ahora

salir de sección crítica
devolver resultado
```

**Relaciones:**

* Usa <a href="#cid-18-05">CID-18-05</a>, <a href="#cid-18-06">CID-18-06</a>, <a href="#cid-18-07">CID-18-07</a>, <a href="#cid-18-08">CID-18-08</a>, <a href="#cid-18-10">CID-18-10</a>, <a href="#cid-18-42">CID-18-42</a> y <a href="#cid-18-43">CID-18-43</a>.
* Es una de las funciones públicas del subsistema de contexto.

---

### <a id="cid-18-45"></a>CID-18-45

**Qué hace:**
Detiene el panel de contexto liberando temporizador, estado interno y visibilidad.

**Cómo funciona:**
Elimina primero el temporizador periódico y su cola si existen. Después, si la sincronización estaba iniciada, entra en la sección crítica, marca el subsistema como no iniciado, reinicia todo el estado interno y luego destruye la propia sección crítica. Finalmente oculta la superposición.

**Pseudocódigo:**

```text
si existe temporizador:
    eliminarlo
si existe cola:
    eliminarla

si la sincronización estaba iniciada:
    entrar en sección crítica
    marcar subsistema como no iniciado
    reiniciar estado interno completo
    salir de sección crítica
    borrar sección crítica

ocultar superposición
```

**Relaciones:**

* Usa <a href="#cid-18-05">CID-18-05</a>, <a href="#cid-18-07">CID-18-07</a>, <a href="#cid-18-08">CID-18-08</a>, <a href="#cid-18-10">CID-18-10</a> y la superposición de <a href="#cid-18-02">CID-18-02</a>.
* Es la contraparte de arranque de <a href="#cid-18-44">CID-18-44</a>.

---

### <a id="cid-18-46"></a>CID-18-46

**Qué hace:**
Fuerza una actualización inmediata del contexto sin esperar al siguiente tick periódico.

**Cómo funciona:**
Comprueba que exista sincronización y que el subsistema esté iniciado. Si ambas condiciones se cumplen, entra en la sección crítica, actualiza el contexto actual y sale del bloqueo.

**Pseudocódigo:**

```text
si no hay sincronización o el subsistema no está iniciado:
    salir

entrar en sección crítica
actualizar contexto actual
salir de sección crítica
```

**Relaciones:**

* Usa <a href="#cid-18-05">CID-18-05</a> y <a href="#cid-18-42">CID-18-42</a>.
* Es una de las funciones públicas del subsistema de contexto.

---

### <a id="cid-18-47"></a>CID-18-47

**Qué hace:**
Registra actividad escribible reciente para permitir la aparición del panel contextual.

**Cómo funciona:**
Comprueba que exista sincronización y que el subsistema esté iniciado. Si ambas condiciones se cumplen, entra en la sección crítica y actualiza `g_ultimo_input_escribible_tick` con el tick actual.

**Pseudocódigo:**

```text
si no hay sincronización o el subsistema no está iniciado:
    salir

entrar en sección crítica
guardar tick actual como último input escribible
salir de sección crítica
```

**Relaciones:**

* Usa <a href="#cid-18-05">CID-18-05</a>, <a href="#cid-18-06">CID-18-06</a> y <a href="#cid-18-08">CID-18-08</a>.
* Es una de las funciones públicas del subsistema de contexto.

## CID-19

La referencia <a href="#cid-19">CID-19</a> corresponde al archivo <code>panel_contexto_texto.h</code>. Este archivo actúa como interfaz pública del panel de contexto de texto. Su responsabilidad principal es exponer al resto del motor las funciones necesarias para arrancar, detener, refrescar y alimentar el observador que detecta si el usuario está en un contexto realmente editable donde la superposición CID debe poder aparecer.

Dentro de <a href="#cid-19">CID-19</a> también se fija el contrato mínimo entre el detector de actividad escribible y el subsistema que decide la visibilidad contextual del panel. Por eso aquí no aparece la lógica interna de temporizadores, caret, UI Automation o debounce, sino únicamente las declaraciones públicas necesarias para que otros módulos puedan activar ese comportamiento. En términos prácticos, <a href="#cid-19">CID-19</a> es la puerta pública de acceso al observador de contexto editable del sistema CID.

### Índice interno de bloques

* <a href="#cid-19-01">CID-19-01</a>
* <a href="#cid-19-02">CID-19-02</a>
* <a href="#cid-19-03">CID-19-03</a>
* <a href="#cid-19-04">CID-19-04</a>
* <a href="#cid-19-05">CID-19-05</a>

---

### <a id="cid-19-01"></a>CID-19-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública del panel de contexto de texto.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Así se evitan redefiniciones de declaraciones y conflictos por inclusión repetida.

**Pseudocódigo:**

```text id="w0y2tq"
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-19">CID-19</a>.
* Asegura que <a href="#cid-19-03">CID-19-03</a> a <a href="#cid-19-05">CID-19-05</a> no se dupliquen al incluir esta cabecera desde distintos módulos.

---

### <a id="cid-19-02"></a>CID-19-02

**Qué hace:**
Incluye los tipos base de Windows usados por la API del observador de contexto.

**Cómo funciona:**
Incorpora `<windows.h>` para disponer de los tipos y definiciones base del entorno Win32 que necesita esta interfaz pública, aunque sus firmas actuales sean mínimas.

**Pseudocódigo:**

```text id="7n22eb"
incluir tipos base de Windows
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-19">CID-19</a>.
* Da soporte general a la integración de esta cabecera con su implementación en <code>panel_contexto_texto.cpp</code>.

---

### <a id="cid-19-03"></a>CID-19-03

**Qué hace:**
Declara el arranque y la detención del observador de contexto de texto editable.

**Cómo funciona:**
Expone dos funciones públicas: `IniciarPanelContextoTexto`, que pone en marcha el sistema de observación periódica del contexto editable, y `DetenerPanelContextoTexto`, que apaga ese observador y limpia su estado interno.

**Pseudocódigo:**

```text id="4dvk2q"
declarar función para iniciar observador de contexto editable
declarar función para detener observador de contexto editable
```

**Relaciones:**

* Se implementa en <a href="#cid-18-44">CID-18-44</a> y <a href="#cid-18-45">CID-18-45</a>.
* Forma parte del ciclo de vida público del subsistema documentado en <a href="#cid-18">CID-18</a>.

---

### <a id="cid-19-04"></a>CID-19-04

**Qué hace:**
Declara la actualización inmediata del contexto sin esperar al temporizador periódico.

**Cómo funciona:**
Expone una función pública que permite forzar una comprobación instantánea del contexto editable actual, evitando esperar al siguiente tick del temporizador interno del observador.

**Pseudocódigo:**

```text id="e6fwq7"
declarar función para refrescar inmediatamente el contexto editable
```

**Relaciones:**

* Se implementa en <a href="#cid-18-46">CID-18-46</a>.
* Complementa el funcionamiento periódico iniciado por <a href="#cid-19-03">CID-19-03</a>.

---

### <a id="cid-19-05"></a>CID-19-05

**Qué hace:**
Declara la notificación de actividad escribible reciente para habilitar la aparición del panel.

**Cómo funciona:**
Expone una función pública que otros módulos pueden invocar cuando detectan input realmente escribible. Esa señal actualiza la ventana temporal de activación usada por el observador para decidir si el panel contextual puede aparecer.

**Pseudocódigo:**

```text id="oif1wp"
declarar función para notificar actividad escribible reciente
```

**Relaciones:**

* Se implementa en <a href="#cid-18-47">CID-18-47</a>.
* Alimenta la lógica de aparición contextual descrita en <a href="#cid-18-36">CID-18-36</a>.


## CID-20

La referencia <a href="#cid-20">CID-20</a> corresponde al archivo <code>inyeccion_texto.cpp</code>. Este archivo implementa el módulo de inyección de texto Unicode del sistema CID. Su responsabilidad principal es marcar cuándo el propio sistema está generando entrada sintética y convertir una cadena Unicode en una secuencia completa de eventos de teclado enviada al sistema operativo.

Dentro de <a href="#cid-20">CID-20</a> también se concentra la separación entre entrada humana y entrada generada por CID. Por eso aquí no solo se envían caracteres, sino que también se mantiene un estado global atómico que permite a otros módulos saber si una pulsación observada pertenece al propio sistema o a una entrada real del usuario. En términos prácticos, <a href="#cid-20">CID-20</a> es la pieza que permite escribir texto resuelto por CID dentro de la aplicación activa sin confundir esa escritura con input manual.

### Índice interno de bloques

* <a href="#cid-20-01">CID-20-01</a>
* <a href="#cid-20-02">CID-20-02</a>
* <a href="#cid-20-03">CID-20-03</a>
* <a href="#cid-20-04">CID-20-04</a>
* <a href="#cid-20-05">CID-20-05</a>
* <a href="#cid-20-06">CID-20-06</a>
* <a href="#cid-20-07">CID-20-07</a>
* <a href="#cid-20-08">CID-20-08</a>

---

### <a id="cid-20-01"></a>CID-20-01

**Qué hace:**
Incluye la implementación del módulo de inyección de texto Unicode a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `inyeccion_texto.h`, que declara las funciones públicas del subsistema de inyección. Gracias a esta inclusión, el archivo actual puede definir la lógica real de marcado de inyección y envío de texto Unicode.

**Pseudocódigo:**

```text id="wp5ihn"
incluir interfaz pública del módulo de inyección de texto
habilitar definición de sus funciones públicas
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-20">CID-20</a>.
* Da soporte directo a <a href="#cid-20-04">CID-20-04</a>, <a href="#cid-20-05">CID-20-05</a> y <a href="#cid-20-06">CID-20-06</a>.

---

### <a id="cid-20-02"></a>CID-20-02

**Qué hace:**
Incluye las cabeceras del sistema y contenedores usados por la inyección.

**Cómo funciona:**
Incorpora `<windows.h>` para poder construir estructuras `INPUT` y usar `SendInput`, y `<vector>` para acumular los eventos de teclado antes de enviarlos en bloque.

**Pseudocódigo:**

```text id="6ld4xn"
incluir API base de Windows
incluir soporte de vectores
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-20">CID-20</a>.
* Da soporte directo a <a href="#cid-20-04">CID-20-04</a>, <a href="#cid-20-05">CID-20-05</a> y <a href="#cid-20-06">CID-20-06</a>.

---

### <a id="cid-20-03"></a>CID-20-03

**Qué hace:**
Declara el estado global atómico que marca si el sistema CID está inyectando entrada propia.

**Cómo funciona:**
Mantiene una variable global `LONG` marcada como volátil, usada como bandera atómica. Su valor permite señalar a otros módulos si el input observado en ese instante proviene del propio sistema CID.

**Pseudocódigo:**

```text id="nmty4z"
declarar bandera global atómica de inyección propia
inicializarla a cero
```

**Relaciones:**

* Es usada por <a href="#cid-20-04">CID-20-04</a> y <a href="#cid-20-05">CID-20-05</a>.
* Sirve de apoyo al resto del sistema para distinguir input propio de input externo.

---

### <a id="cid-20-04"></a>CID-20-04

**Qué hace:**
Activa o desactiva la marca global de inyección propia del sistema CID.

**Cómo funciona:**
Recibe un booleano y actualiza la bandera global mediante `InterlockedExchange`, escribiendo `1` cuando la inyección propia está activa y `0` cuando deja de estarlo. Así garantiza una actualización atómica y segura entre hilos.

**Pseudocódigo:**

```text id="1j4f67"
si activa es verdadero:
    escribir 1 en la bandera global
si activa es falso:
    escribir 0 en la bandera global
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-20-03">CID-20-03</a>.
* Es consumida por módulos que rodean la inyección real de texto para marcar intervalos de input sintético.

---

### <a id="cid-20-05"></a>CID-20-05

**Qué hace:**
Devuelve si el sistema se encuentra actualmente en medio de una inyección propia.

**Cómo funciona:**
Lee el valor actual de la bandera global usando `InterlockedCompareExchange` sin modificarla. Si el valor leído es distinto de cero, concluye que hay una inyección propia activa.

**Pseudocódigo:**

```text id="nprdlm"
leer atómicamente la bandera global sin modificarla
devolver si su valor es distinto de cero
```

**Relaciones:**

* Usa el estado definido en <a href="#cid-20-03">CID-20-03</a>.
* Complementa a <a href="#cid-20-04">CID-20-04</a> como consulta pública del estado de inyección.

---

### <a id="cid-20-06"></a>CID-20-06

**Qué hace:**
Inyecta una cadena Unicode completa simulando pulsación y liberación de cada carácter.

**Cómo funciona:**
Si la cadena está vacía, devuelve éxito inmediato. Si no lo está, reserva un vector de eventos `INPUT`, construye para cada carácter un evento de pulsación y otro de liberación en modo `KEYEVENTF_UNICODE`, y finalmente envía la secuencia completa al sistema con `SendInput`. La función devuelve si todos los eventos fueron enviados.

**Pseudocódigo:**

```text id="allxx3"
si el texto está vacío:
    devolver verdadero

crear vector de eventos de entrada
reservar espacio suficiente

para cada carácter del texto:
    construir evento de pulsación Unicode
    construir evento de liberación Unicode
    añadir ambos al vector

enviar todos los eventos al sistema
devolver si se enviaron completos
```

**Relaciones:**

* Contiene internamente <a href="#cid-20-07">CID-20-07</a> y <a href="#cid-20-08">CID-20-08</a>.
* Usa las cabeceras incluidas en <a href="#cid-20-02">CID-20-02</a>.
* Es la operación principal del subsistema de inyección de texto.

---

### <a id="cid-20-07"></a>CID-20-07

**Qué hace:**
Construye la secuencia de eventos `KEYEVENTF_UNICODE` para cada carácter del texto.

**Cómo funciona:**
Recorre cada carácter ancho de la cadena. Para cada uno crea dos estructuras `INPUT`: una de pulsación Unicode y otra de liberación Unicode. Ambas se añaden al vector acumulado en orden.

**Pseudocódigo:**

```text id="8m5992"
para cada carácter del texto:
    crear evento de pulsación Unicode
    añadirlo al vector
    crear evento de liberación Unicode
    añadirlo al vector
```

**Relaciones:**

* Forma parte de <a href="#cid-20-06">CID-20-06</a>.
* Prepara los datos enviados finalmente en <a href="#cid-20-08">CID-20-08</a>.

---

### <a id="cid-20-08"></a>CID-20-08

**Qué hace:**
Envía todos los eventos acumulados y devuelve si la inyección fue completa.

**Cómo funciona:**
Llama a `SendInput` con el vector completo de eventos ya construido. Compara el número de eventos realmente enviados con el tamaño total del vector y devuelve `true` solo si ambos coinciden exactamente.

**Pseudocódigo:**

```text id="8i6ykv"
enviar vector completo de eventos con SendInput
comparar cuántos eventos se enviaron realmente
devolver si el envío fue completo
```

**Relaciones:**

* Forma parte de <a href="#cid-20-06">CID-20-06</a>.
* Consume la secuencia preparada en <a href="#cid-20-07">CID-20-07</a>.


## CID-21

La referencia <a href="#cid-21">CID-21</a> corresponde al archivo <code>inyeccion_texto.h</code>. Este archivo actúa como interfaz pública del módulo de inyección de texto del sistema CID. Su responsabilidad principal es exponer al resto del motor las funciones necesarias para marcar cuándo CID está generando entrada propia y para inyectar una cadena Unicode completa en la aplicación activa.

Dentro de <a href="#cid-21">CID-21</a> también se define el contrato mínimo entre el subsistema que resuelve texto y el subsistema que lo escribe físicamente en el sistema operativo. Por eso aquí no aparece la lógica interna de `SendInput`, la construcción de eventos `KEYEVENTF_UNICODE` ni el estado atómico real, sino únicamente las declaraciones públicas que permiten activar ese comportamiento desde otros módulos. En términos prácticos, <a href="#cid-21">CID-21</a> es la puerta pública de acceso a la escritura sintética de texto Unicode por parte de CID.

### Índice interno de bloques

* <a href="#cid-21-01">CID-21-01</a>
* <a href="#cid-21-02">CID-21-02</a>
* <a href="#cid-21-03">CID-21-03</a>
* <a href="#cid-21-04">CID-21-04</a>

---

### <a id="cid-21-01"></a>CID-21-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública del módulo de inyección de texto.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Así se evitan redefiniciones de declaraciones y conflictos por inclusión repetida.

**Pseudocódigo:**

```text id="h8d4uc"
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-21">CID-21</a>.
* Asegura que <a href="#cid-21-03">CID-21-03</a> y <a href="#cid-21-04">CID-21-04</a> no se dupliquen al incluir esta cabecera desde distintos módulos.

---

### <a id="cid-21-02"></a>CID-21-02

**Qué hace:**
Incluye el tipo de texto Unicode usado por la API de inyección.

**Cómo funciona:**
Incorpora `<string>` para disponer de `std::wstring`, tipo usado por la función pública que recibe la cadena Unicode a inyectar.

**Pseudocódigo:**

```text id="apmau1"
incluir soporte de cadenas Unicode
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-21">CID-21</a>.
* Da soporte directo a <a href="#cid-21-04">CID-21-04</a>.

---

### <a id="cid-21-03"></a>CID-21-03

**Qué hace:**
Declara el control del estado global de inyección propia del sistema CID.

**Cómo funciona:**
Expone dos funciones públicas. `MarcarInyeccionActiva` permite activar o desactivar la bandera global que indica que CID está generando entrada sintética. `InyeccionActiva` permite consultar ese mismo estado desde otros módulos.

**Pseudocódigo:**

```text id="jlwm2b"
declarar función para activar o desactivar la marca de inyección
declarar función para consultar si hay inyección activa
```

**Relaciones:**

* Se implementa en <a href="#cid-20-04">CID-20-04</a> y <a href="#cid-20-05">CID-20-05</a>.
* Forma parte del contrato público del módulo de inyección documentado en <a href="#cid-20">CID-20</a>.

---

### <a id="cid-21-04"></a>CID-21-04

**Qué hace:**
Declara la inyección de una cadena Unicode completa en el sistema activo.

**Cómo funciona:**
Expone una función pública que recibe una `std::wstring` y devuelve si la cadena pudo inyectarse completamente. La implementación asociada se encarga de traducir ese texto a eventos de teclado Unicode y enviarlos al sistema operativo.

**Pseudocódigo:**

```text id="96w0qd"
declarar función para inyectar una cadena Unicode completa
devolver si la inyección fue exitosa
```

**Relaciones:**

* Usa `std::wstring` incluido en <a href="#cid-21-02">CID-21-02</a>.
* Se implementa en <a href="#cid-20-06">CID-20-06</a>.
* Completa junto a <a href="#cid-21-03">CID-21-03</a> la interfaz pública del subsistema de inyección.


