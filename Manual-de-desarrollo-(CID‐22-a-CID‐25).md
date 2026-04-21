## CID-22

La referencia <a href="#cid-22">CID-22</a> corresponde al archivo <code>layout_teclado_visual.cpp</code>. Este archivo implementa el sistema de layout visual del teclado CID. Su responsabilidad principal es cargar el archivo JSON del layout visual, parsearlo con un parser mínimo propio, convertirlo en una colección de teclas renderizables y ofrecer utilidades para transformar esas teclas a píxeles o localizarlas por posición o por identificador CID.

Dentro de <a href="#cid-22">CID-22</a> también se concentra la lógica que traduce el formato KLE del teclado a un modelo visual usable por el asistente de configuración. Por eso aquí no solo se leen colores y geometría, sino que también se detectan IDs CID a partir del texto multilínea de cada tecla, se decide qué teclas merecen renderizado y se calculan las métricas globales del teclado cargado. En términos prácticos, <a href="#cid-22">CID-22</a> es la pieza que convierte `keyboard-layout.json` en un teclado visual real sobre el que el resto del sistema puede dibujar, buscar teclas y reaccionar a clics.

### Índice interno de bloques

* <a href="#cid-22-01">CID-22-01</a>
* <a href="#cid-22-02">CID-22-02</a>
* <a href="#cid-22-03">CID-22-03</a>
* <a href="#cid-22-04">CID-22-04</a>
* <a href="#cid-22-05">CID-22-05</a>
* <a href="#cid-22-06">CID-22-06</a>
* <a href="#cid-22-07">CID-22-07</a>
* <a href="#cid-22-08">CID-22-08</a>
* <a href="#cid-22-09">CID-22-09</a>
* <a href="#cid-22-10">CID-22-10</a>
* <a href="#cid-22-11">CID-22-11</a>
* <a href="#cid-22-12">CID-22-12</a>
* <a href="#cid-22-13">CID-22-13</a>
* <a href="#cid-22-14">CID-22-14</a>
* <a href="#cid-22-15">CID-22-15</a>
* <a href="#cid-22-16">CID-22-16</a>
* <a href="#cid-22-17">CID-22-17</a>
* <a href="#cid-22-18">CID-22-18</a>
* <a href="#cid-22-19">CID-22-19</a>
* <a href="#cid-22-20">CID-22-20</a>
* <a href="#cid-22-21">CID-22-21</a>
* <a href="#cid-22-22">CID-22-22</a>
* <a href="#cid-22-23">CID-22-23</a>
* <a href="#cid-22-24">CID-22-24</a>
* <a href="#cid-22-25">CID-22-25</a>
* <a href="#cid-22-26">CID-22-26</a>
* <a href="#cid-22-27">CID-22-27</a>
* <a href="#cid-22-28">CID-22-28</a>
* <a href="#cid-22-29">CID-22-29</a>
* <a href="#cid-22-30">CID-22-30</a>
* <a href="#cid-22-31">CID-22-31</a>
* <a href="#cid-22-32">CID-22-32</a>
* <a href="#cid-22-33">CID-22-33</a>
* <a href="#cid-22-34">CID-22-34</a>
* <a href="#cid-22-35">CID-22-35</a>
* <a href="#cid-22-36">CID-22-36</a>
* <a href="#cid-22-37">CID-22-37</a>
* <a href="#cid-22-38">CID-22-38</a>

---

### <a id="cid-22-01"></a>CID-22-01

**Qué hace:**
Incluye la implementación del layout visual del teclado CID a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `layout_teclado_visual.h`, que declara los tipos y funciones públicas del subsistema. Gracias a esta inclusión, el archivo actual puede definir la lógica real de carga, limpieza y búsqueda sobre el layout visual.

**Pseudocódigo:**

```text id="2v8jlwm"
incluir interfaz pública del layout visual
habilitar definición de sus tipos y funciones
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-22">CID-22</a>.
* Da soporte directo a <a href="#cid-22-34">CID-22-34</a> a <a href="#cid-22-38">CID-22-38</a>.

---

### <a id="cid-22-02"></a>CID-22-02

**Qué hace:**
Incluye cabeceras del sistema y utilidades estándar para parsing y contenedores.

**Cómo funciona:**
Este bloque habilita acceso a la API Win32, cadenas, vectores, mapas, archivos, streams, utilidades de caracteres y algoritmos. No contiene lógica ejecutable, pero prepara el entorno de compilación necesario para el parser JSON mínimo y para el procesado del layout.

**Pseudocódigo:**

```text id="6hr6ec"
incluir API base de Windows
incluir soporte de cadenas y vectores
incluir soporte de mapas, archivos y streams
incluir utilidades de caracteres y algoritmos
```

**Relaciones:**

* Prepara el entorno de compilación para todo <a href="#cid-22">CID-22</a>.
* Da soporte indirecto a <a href="#cid-22-05">CID-22-05</a>, <a href="#cid-22-17">CID-22-17</a>, <a href="#cid-22-29">CID-22-29</a> y al resto de bloques con lógica de parsing o contenedores.

---

### <a id="cid-22-03"></a>CID-22-03

**Qué hace:**
Abre un espacio interno anónimo para encapsular el parser JSON mínimo y los helpers privados del layout.

**Cómo funciona:**
Agrupa dentro de un `namespace` anónimo todos los tipos y funciones auxiliares que solo deben existir dentro de este archivo, como el parser, la lectura UTF-8, la detección de IDs CID y el constructor del layout.

**Pseudocódigo:**

```text id="e5q2v6"
abrir espacio interno privado del módulo
encapsular parser y helpers no públicos
```

**Relaciones:**

* Contiene internamente <a href="#cid-22-04">CID-22-04</a> a <a href="#cid-22-33">CID-22-33</a>.
* Separa la implementación privada de las funciones públicas de <a href="#cid-22-34">CID-22-34</a> a <a href="#cid-22-38">CID-22-38</a>.

---

### <a id="cid-22-04"></a>CID-22-04

**Qué hace:**
Representa un valor JSON mínimo con soporte para null, bool, número, string, array y objeto.

**Cómo funciona:**
Declara una estructura `JsonValue` con un enumerado `Type` y campos suficientes para almacenar cualquiera de los tipos JSON que el parser soporta. Según el valor de `type`, se usan distintos campos de la estructura.

**Pseudocódigo:**

```text id="52glj2"
definir estructura de valor JSON
guardar tipo del valor
guardar posibles campos bool, número, string, array y objeto
```

**Relaciones:**

* Es usada por <a href="#cid-22-05">CID-22-05</a>, <a href="#cid-22-18">CID-22-18</a>, <a href="#cid-22-19">CID-22-19</a> y <a href="#cid-22-29">CID-22-29</a>.

---

### <a id="cid-22-05"></a>CID-22-05

**Qué hace:**
Define un parser JSON mínimo usado para leer el archivo KLE del teclado visual.

**Cómo funciona:**
Declara una estructura `JsonParser` con referencia al texto, posición actual y buffer de error. Esta estructura agrupa todos los métodos necesarios para parsear strings, números, arrays, objetos y valores JSON genéricos.

**Pseudocódigo:**

```text id="rjjlwm"
definir parser JSON mínimo
guardar texto fuente, posición actual y error
agrupar métodos de parsing JSON
```

**Relaciones:**

* Contiene internamente <a href="#cid-22-06">CID-22-06</a> a <a href="#cid-22-14">CID-22-14</a>.
* Es usado por <a href="#cid-22-34">CID-22-34</a>.

---

### <a id="cid-22-06"></a>CID-22-06

**Qué hace:**
Devuelve el carácter actual sin avanzar la posición del parser.

**Cómo funciona:**
Comprueba si existe texto y si la posición sigue dentro de sus límites. Si todo es válido, devuelve el carácter actual; si no, devuelve cero.

**Pseudocódigo:**

```text id="nzjzz1"
si no hay texto o la posición está al final:
    devolver 0
devolver carácter actual sin avanzar
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Es usada por <a href="#cid-22-08">CID-22-08</a>, <a href="#cid-22-09">CID-22-09</a>, <a href="#cid-22-11">CID-22-11</a> y <a href="#cid-22-12">CID-22-12</a>.

---

### <a id="cid-22-07"></a>CID-22-07

**Qué hace:**
Devuelve el carácter actual y avanza la posición del parser.

**Cómo funciona:**
Comprueba si existe texto y si todavía quedan caracteres. Si los hay, devuelve el actual y avanza `pos`; si no, devuelve cero.

**Pseudocódigo:**

```text id="lk7g9u"
si no hay texto o la posición está al final:
    devolver 0
devolver carácter actual
avanzar posición
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Es usada por <a href="#cid-22-10">CID-22-10</a>, <a href="#cid-22-13">CID-22-13</a> y <a href="#cid-22-14">CID-22-14</a>.

---

### <a id="cid-22-08"></a>CID-22-08

**Qué hace:**
Salta espacios en blanco JSON entre tokens.

**Cómo funciona:**
Mientras el carácter actual sea espacio, tabulador, retorno o salto de línea, avanza la posición del parser. Se detiene cuando encuentra un carácter útil o el final del texto.

**Pseudocódigo:**

```text id="jlwm0w"
mientras el carácter actual sea espacio JSON:
    avanzar posición
detenerse al llegar a un token o al final
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Es usada por <a href="#cid-22-12">CID-22-12</a>, <a href="#cid-22-13">CID-22-13</a> y <a href="#cid-22-14">CID-22-14</a>.

---

### <a id="cid-22-09"></a>CID-22-09

**Qué hace:**
Intenta consumir un literal JSON exacto desde la posición actual.

**Cómo funciona:**
Recorre carácter a carácter el literal esperado. Si todos coinciden con el texto fuente, avanza la posición y devuelve verdadero. Si alguno falla, devuelve falso.

**Pseudocódigo:**

```text id="jlwm53"
recorrer literal esperado
si un carácter no coincide:
    devolver falso
avanzar posición en cada coincidencia
devolver verdadero
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Es usada por <a href="#cid-22-12">CID-22-12</a> para `true`, `false` y `null`.

---

### <a id="cid-22-10"></a>CID-22-10

**Qué hace:**
Parsea una cadena JSON con escapes básicos y unicode simple.

**Cómo funciona:**
Exige primero una comilla inicial. Después recorre el texto hasta la comilla de cierre, interpretando secuencias escapadas comunes y escapes `\uXXXX`. Si encuentra un final inesperado o un escape inválido, registra un error.

**Pseudocódigo:**

```text id="41qarf"
exigir comilla inicial
mientras no aparezca comilla de cierre:
    leer carácter
    si llega fin inesperado:
        devolver error
    si aparece barra invertida:
        leer escape
        interpretar escape básico o unicode
    si no:
        añadir carácter literal
devolver éxito al cerrar string
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Es usada por <a href="#cid-22-12">CID-22-12</a> y <a href="#cid-22-14">CID-22-14</a>.

---

### <a id="cid-22-11"></a>CID-22-11

**Qué hace:**
Parsea un número JSON simple con soporte para signo, decimales y exponente.

**Cómo funciona:**
Consume opcionalmente signo, parte entera, parte decimal y exponente. Si no llega a ver ningún dígito, considera el número inválido. Al final convierte el token capturado a `double` con `_wtof`.

**Pseudocódigo:**

```text id="hl7rgr"
guardar posición inicial
consumir signo opcional
consumir dígitos enteros
consumir parte decimal opcional
consumir exponente opcional
si no se vio ningún dígito:
    devolver error
convertir token capturado a número
devolver éxito
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Es usada por <a href="#cid-22-12">CID-22-12</a>.

---

### <a id="cid-22-12"></a>CID-22-12

**Qué hace:**
Parsea cualquier valor JSON delegando al subtipo correspondiente.

**Cómo funciona:**
Ignora primero espacios en blanco y mira el carácter actual. Según ese carácter decide si debe parsear un string, objeto, array, booleano, null o número. Si no reconoce el valor, registra un error.

**Pseudocódigo:**

```text id="hma541"
saltar espacios
mirar carácter actual
si es string:
    parsear string
si es objeto:
    parsear objeto
si es array:
    parsear array
si es true, false o null:
    consumir literal correspondiente
si es número:
    parsear número
si no coincide nada:
    devolver error
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Usa <a href="#cid-22-08">CID-22-08</a>, <a href="#cid-22-09">CID-22-09</a>, <a href="#cid-22-10">CID-22-10</a>, <a href="#cid-22-11">CID-22-11</a>, <a href="#cid-22-13">CID-22-13</a> y <a href="#cid-22-14">CID-22-14</a>.
* Es llamada desde <a href="#cid-22-13">CID-22-13</a>, <a href="#cid-22-14">CID-22-14</a> y <a href="#cid-22-34">CID-22-34</a>.

---

### <a id="cid-22-13"></a>CID-22-13

**Qué hace:**
Parsea un array JSON y acumula sus elementos en orden.

**Cómo funciona:**
Exige el carácter `[` inicial, prepara un `JsonValue` de tipo array y luego parsea valores sucesivos separados por comas hasta encontrar `]`. También soporta arrays vacíos.

**Pseudocódigo:**

```text id="jvd5p5"
exigir corchete inicial
marcar valor como array
si el siguiente token es ]:
    devolver array vacío

mientras haya elementos:
    parsear valor
    añadirlo al array
    leer separador
    si es ]:
        devolver éxito
    si no es coma:
        devolver error
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Usa <a href="#cid-22-08">CID-22-08</a> y <a href="#cid-22-12">CID-22-12</a>.

---

### <a id="cid-22-14"></a>CID-22-14

**Qué hace:**
Parsea un objeto JSON y almacena sus pares clave-valor.

**Cómo funciona:**
Exige el carácter `{` inicial, prepara un `JsonValue` de tipo objeto y luego parsea claves string seguidas de `:` y un valor cualquiera. Los pares se almacenan en un mapa y se repiten hasta encontrar `}`. También soporta objetos vacíos.

**Pseudocódigo:**

```text id="6wy07g"
exigir llave inicial
marcar valor como objeto
si el siguiente token es }:
    devolver objeto vacío

mientras haya pares:
    parsear clave string
    exigir dos puntos
    parsear valor
    guardar par clave-valor
    leer separador
    si es }:
        devolver éxito
    si no es coma:
        devolver error
```

**Relaciones:**

* Forma parte de <a href="#cid-22-05">CID-22-05</a>.
* Usa <a href="#cid-22-08">CID-22-08</a>, <a href="#cid-22-10">CID-22-10</a> y <a href="#cid-22-12">CID-22-12</a>.

---

### <a id="cid-22-15"></a>CID-22-15

**Qué hace:**
Envía mensajes de depuración del módulo de layout visual al visor de salida.

**Cómo funciona:**
Recibe una cadena ancha, le añade un salto de línea y la envía mediante `OutputDebugStringW`.

**Pseudocódigo:**

```text id="2jrhnw"
añadir salto de línea al mensaje
enviar mensaje al depurador
```

**Relaciones:**

* Es usada por <a href="#cid-22-34">CID-22-34</a>.

---

### <a id="cid-22-16"></a>CID-22-16

**Qué hace:**
Convierte una cadena UTF-8 a Unicode para cargar archivos JSON.

**Cómo funciona:**
Si la entrada está vacía devuelve una cadena vacía. Si no, calcula el tamaño Unicode necesario, reserva la salida y usa `MultiByteToWideChar` para hacer la conversión.

**Pseudocódigo:**

```text id="2xt6b0"
si la entrada está vacía:
    devolver vacío
calcular tamaño Unicode necesario
si el tamaño no es válido:
    devolver vacío
reservar salida
convertir UTF-8 a Unicode
devolver resultado
```

**Relaciones:**

* Es usada por <a href="#cid-22-17">CID-22-17</a>.

---

### <a id="cid-22-17"></a>CID-22-17

**Qué hace:**
Lee un archivo de texto UTF-8 y elimina BOM si existe.

**Cómo funciona:**
Abre el archivo en binario, lee todos sus bytes, elimina el BOM UTF-8 si aparece al principio y convierte el contenido restante a Unicode mediante `NarrowToWideUtf8`. Si no puede abrir el archivo, informa error.

**Pseudocódigo:**

```text id="o3szyj"
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

* Usa <a href="#cid-22-16">CID-22-16</a>.
* Es llamada desde <a href="#cid-22-34">CID-22-34</a>.

---

### <a id="cid-22-18"></a>CID-22-18

**Qué hace:**
Obtiene un número desde una clave de un objeto JSON.

**Cómo funciona:**
Comprueba que el valor recibido sea un objeto, busca la clave indicada en su mapa interno y verifica que el valor asociado sea numérico. Si todo cuadra, copia ese número en la salida.

**Pseudocódigo:**

```text id="8gh0eg"
si el valor no es un objeto:
    devolver falso
buscar clave en el objeto
si no existe o no es número:
    devolver falso
copiar número a salida
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-22-04">CID-22-04</a>.
* Es llamada desde <a href="#cid-22-31">CID-22-31</a>.

---

### <a id="cid-22-19"></a>CID-22-19

**Qué hace:**
Obtiene una cadena desde una clave de un objeto JSON.

**Cómo funciona:**
Comprueba que el valor recibido sea un objeto, busca la clave indicada y verifica que su contenido sea de tipo string. Si lo es, copia la cadena a la salida.

**Pseudocódigo:**

```text id="csmnzz"
si el valor no es un objeto:
    devolver falso
buscar clave en el objeto
si no existe o no es string:
    devolver falso
copiar string a salida
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-22-04">CID-22-04</a>.
* Es llamada desde <a href="#cid-22-31">CID-22-31</a>.

---

### <a id="cid-22-20"></a>CID-22-20

**Qué hace:**
Convierte un color hexadecimal tipo `#RRGGBB` a `COLORREF`.

**Cómo funciona:**
Acepta una cadena opcionalmente precedida por `#`, exige exactamente seis dígitos hexadecimales y los convierte a un entero. Si la conversión funciona, extrae rojo, verde y azul y devuelve el `COLORREF`; si no, devuelve un gris por defecto y marca el resultado como no válido.

**Pseudocódigo:**

```text id="la1lr3"
marcar conversión como no válida
si la cadena está vacía:
    devolver color por defecto
quitar almohadilla inicial si existe
si la longitud no es 6:
    devolver color por defecto
convertir hex a entero
si falla:
    devolver color por defecto
marcar conversión como válida
extraer r, g y b
devolver color RGB
```

**Relaciones:**

* Es usada por <a href="#cid-22-32">CID-22-32</a>.

---

### <a id="cid-22-21"></a>CID-22-21

**Qué hace:**
Determina si un color es aproximadamente gris para depuración y filtrado visual.

**Cómo funciona:**
Calcula el máximo y el mínimo entre los tres canales RGB. Si la diferencia entre ambos es pequeña y además los tres canales están dentro de una franja media, considera el color como gris aproximado.

**Pseudocódigo:**

```text id="w0wa3t"
leer canales rojo, verde y azul
calcular máximo, mínimo y delta
si el delta es pequeño y los canales están en rango medio:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Es usada por <a href="#cid-22-32">CID-22-32</a>.

---

### <a id="cid-22-22"></a>CID-22-22

**Qué hace:**
Recorta espacios en blanco al inicio y final de una cadena ancha.

**Cómo funciona:**
Avanza un índice inicial mientras haya espacios al principio y retrocede un índice final mientras haya espacios al final. Después devuelve la subcadena útil comprendida entre ambos.

**Pseudocódigo:**

```text id="fdj2to"
avanzar índice inicial mientras haya espacios
retroceder índice final mientras haya espacios
devolver subcadena recortada
```

**Relaciones:**

* Es usada por <a href="#cid-22-23">CID-22-23</a>, <a href="#cid-22-26">CID-22-26</a> y <a href="#cid-22-28">CID-22-28</a>.

---

### <a id="cid-22-23"></a>CID-22-23

**Qué hace:**
Divide un texto multilinea en líneas individuales.

**Cómo funciona:**
Recorre la cadena carácter a carácter, acumulando texto hasta encontrar un salto de línea. Cada vez que lo encuentra, guarda la línea acumulada y empieza otra nueva. Al final también añade la última línea.

**Pseudocódigo:**

```text id="mjlwm0"
crear vector de líneas
crear línea actual vacía
para cada carácter:
    si es salto de línea:
        guardar línea actual
        vaciar línea actual
    si no:
        añadir carácter a línea actual
guardar última línea
devolver líneas
```

**Relaciones:**

* Es usada por <a href="#cid-22-26">CID-22-26</a> y <a href="#cid-22-27">CID-22-27</a>.

---

### <a id="cid-22-24"></a>CID-22-24

**Qué hace:**
Comprueba si una cadena parece un identificador CID válido.

**Cómo funciona:**
Acepta explícitamente `AUX_CID` y `CID_KEY`. También acepta cualquier cadena de al menos dos caracteres que empiece por `I`, `C` o `D`. No valida aquí rangos concretos, solo apariencia básica de ID.

**Pseudocódigo:**

```text id="jtjlwm"
si la cadena es AUX_CID o CID_KEY:
    devolver verdadero
si la cadena empieza por I, C o D y tiene al menos dos caracteres:
    devolver verdadero
devolver falso
```

**Relaciones:**

* Es usada por <a href="#cid-22-26">CID-22-26</a>.

---

### <a id="cid-22-25"></a>CID-22-25

**Qué hace:**
Convierte un texto a mayúsculas para detección robusta de IDs CID.

**Cómo funciona:**
Copia la cadena y aplica `towupper` a cada carácter. Devuelve la versión normalizada.

**Pseudocódigo:**

```text id="70hjlwm"
copiar cadena
para cada carácter:
    convertir a mayúscula
devolver resultado
```

**Relaciones:**

* Es usada por <a href="#cid-22-26">CID-22-26</a>.

---

### <a id="cid-22-26"></a>CID-22-26

**Qué hace:**
Intenta detectar el id CID de una tecla a partir de su texto original multilínea.

**Cómo funciona:**
Divide el texto raw en líneas, recorta cada línea y la normaliza a mayúsculas. Luego intenta reconocer varios casos: `CID KEY`, `TECLA CID`, `AUX CID`, `AUX_CID` o cualquier texto que parezca un identificador CID válido. Devuelve el primer identificador encontrado.

**Pseudocódigo:**

```text id="67xjlwm"
dividir texto raw en líneas
para cada línea:
    recortar espacios
    convertir a mayúsculas
    si representa CID KEY:
        devolver CID_KEY
    si representa AUX CID:
        devolver AUX_CID
    si parece un ID CID válido:
        devolver ese ID
devolver vacío
```

**Relaciones:**

* Usa <a href="#cid-22-22">CID-22-22</a>, <a href="#cid-22-23">CID-22-23</a>, <a href="#cid-22-24">CID-22-24</a> y <a href="#cid-22-25">CID-22-25</a>.
* Es llamada desde <a href="#cid-22-32">CID-22-32</a>.

---

### <a id="cid-22-27"></a>CID-22-27

**Qué hace:**
Escoge el texto visible principal de una tecla a partir del raw o de su id CID detectado.

**Cómo funciona:**
Si ya existe un `idCid`, construye un texto visible canónico a partir de él, con casos especiales para `CID_KEY` y `AUX_CID`. Si no existe, recorre las líneas del raw y devuelve la primera línea no vacía.

**Pseudocódigo:**

```text id="7jlwm4"
si existe id CID:
    si es CID_KEY:
        devolver CID KEY
    si es AUX_CID:
        devolver AUX CID
    devolver id CID

dividir raw en líneas
devolver la primera línea no vacía
si no hay ninguna:
    devolver vacío
```

**Relaciones:**

* Usa <a href="#cid-22-22">CID-22-22</a> y <a href="#cid-22-23">CID-22-23</a>.
* Es llamada desde <a href="#cid-22-32">CID-22-32</a>.

---

### <a id="cid-22-28"></a>CID-22-28

**Qué hace:**
Decide si una tecla debe formar parte del layout renderizable final.

**Cómo funciona:**
Rechaza teclas completamente vacías de texto e identificador. Acepta teclas con `idCid` o con texto visible no vacío. Si solo queda una tecla gris sin información útil, la descarta.

**Pseudocódigo:**

```text id="jlwm9e"
si no hay texto original, texto visible ni id CID:
    devolver falso
si hay id CID:
    devolver verdadero
si hay texto visible:
    devolver verdadero
si la tecla es gris:
    devolver falso
devolver falso
```

**Relaciones:**

* Usa <a href="#cid-22-22">CID-22-22</a>.
* Es llamada desde <a href="#cid-22-32">CID-22-32</a>.

---

### <a id="cid-22-29"></a>CID-22-29

**Qué hace:**
Parsea el JSON KLE y construye el layout visual renderizable del teclado.

**Cómo funciona:**
Exige que la raíz sea un array, limpia el layout de salida y recorre cada fila del KLE. Dentro de cada fila mantiene un estado heredable de geometría y color, procesando objetos como cambios de estado y strings como teclas concretas. Cada string se convierte en `TeclaVisualCID`, se decide si es renderizable y, si lo es, se añade al layout actualizando el tamaño total. Al final falla si no quedó ninguna tecla usable.

**Pseudocódigo:**

```text id="jlwmay"
si la raíz no es un array:
    devolver error

limpiar layout de salida
inicializar coordenada y

para cada fila del KLE:
    si no es un array:
        continuar

    inicializar coordenada x
    inicializar estado heredable de tecla

    recorrer elementos de la fila:
        si el elemento es un objeto:
            actualizar estado heredable
            continuar

        si el elemento es un string:
            aplicar desplazamientos pendientes
            construir tecla visual
            parsear color
            detectar id CID
            escoger texto visible
            decidir si es renderizable

            si es renderizable:
                añadir tecla al layout
                actualizar ancho y alto totales

            avanzar x por el ancho de la tecla
            reiniciar estado heredable puntual

    avanzar y al terminar la fila
    actualizar alto total

si no quedó ninguna tecla renderizable:
    devolver error

devolver éxito
```

**Relaciones:**

* Contiene internamente <a href="#cid-22-30">CID-22-30</a> a <a href="#cid-22-33">CID-22-33</a>.
* Usa <a href="#cid-22-18">CID-22-18</a>, <a href="#cid-22-19">CID-22-19</a>, <a href="#cid-22-20">CID-22-20</a>, <a href="#cid-22-21">CID-22-21</a>, <a href="#cid-22-26">CID-22-26</a>, <a href="#cid-22-27">CID-22-27</a> y <a href="#cid-22-28">CID-22-28</a>.
* Es llamada desde <a href="#cid-22-34">CID-22-34</a>.

---

### <a id="cid-22-30"></a>CID-22-30

**Qué hace:**
Recorre cada fila KLE acumulando geometría y estado heredable de teclas.

**Cómo funciona:**
Para cada fila válida del array raíz, inicializa la coordenada `x` y una serie de valores heredables como ancho, alto, desplazamientos pendientes y color actual. Ese estado se irá usando después para construir cada tecla de la fila.

**Pseudocódigo:**

```text id="jlwmn4"
para cada fila del array raíz:
    si la fila no es un array:
        continuar
    reiniciar x
    reiniciar ancho, alto, desplazamientos y color heredables
```

**Relaciones:**

* Forma parte de <a href="#cid-22-29">CID-22-29</a>.
* Prepara a <a href="#cid-22-31">CID-22-31</a> y <a href="#cid-22-32">CID-22-32</a>.

---

### <a id="cid-22-31"></a>CID-22-31

**Qué hace:**
Recorre objetos de estado y strings de teclas dentro de una fila KLE.

**Cómo funciona:**
Si el elemento actual es un objeto JSON, intenta leer de él claves como `x`, `y`, `w`, `h` y `c`, actualizando el estado heredable que se aplicará a la siguiente tecla string.

**Pseudocódigo:**

```text id="mjlwm5"
si el elemento de la fila es un objeto:
    leer desplazamiento x si existe
    leer desplazamiento y si existe
    leer ancho si existe
    leer alto si existe
    leer color si existe
    continuar
```

**Relaciones:**

* Usa <a href="#cid-22-18">CID-22-18</a> y <a href="#cid-22-19">CID-22-19</a>.
* Forma parte de <a href="#cid-22-29">CID-22-29</a>.

---

### <a id="cid-22-32"></a>CID-22-32

**Qué hace:**
Convierte una entrada string KLE en una tecla visual concreta y renderizable.

**Cómo funciona:**
Aplica primero los desplazamientos pendientes, construye una `TeclaVisualCID` con texto original, geometría y color, detecta si el color es gris, intenta extraer el `idCid`, escoge el texto visible principal y decide si debe renderizarse. Si la tecla es válida, la añade al layout y actualiza las métricas globales. Después avanza `x` y reinicia el estado puntual de ancho y alto heredados.

**Pseudocódigo:**

```text id="6j4phw"
aplicar desplazamientos pendientes a x e y
crear tecla visual
copiar texto raw y geometría
parsear color y detectar si es gris
detectar id CID
escoger texto visible
decidir si es renderizable

si es renderizable:
    añadir tecla al layout
    actualizar ancho y alto totales

avanzar x por el ancho de la tecla
reiniciar ancho y alto heredados
```

**Relaciones:**

* Usa <a href="#cid-22-20">CID-22-20</a>, <a href="#cid-22-21">CID-22-21</a>, <a href="#cid-22-26">CID-22-26</a>, <a href="#cid-22-27">CID-22-27</a> y <a href="#cid-22-28">CID-22-28</a>.
* Forma parte de <a href="#cid-22-29">CID-22-29</a>.

---

### <a id="cid-22-33"></a>CID-22-33

**Qué hace:**
Falla si el layout no produce ninguna tecla utilizable para render.

**Cómo funciona:**
Comprueba si el vector final de teclas renderizables quedó vacío tras procesar todo el KLE. Si es así, informa un error.

**Pseudocódigo:**

```text id="bjlwm6"
si no hay teclas renderizables:
    devolver error
devolver éxito
```

**Relaciones:**

* Forma parte de <a href="#cid-22-29">CID-22-29</a>.
* Garantiza que <a href="#cid-22-34">CID-22-34</a> solo devuelva layouts útiles.

---

### <a id="cid-22-34"></a>CID-22-34

**Qué hace:**
Carga el archivo JSON del layout visual, lo parsea y construye el teclado renderizable.

**Cómo funciona:**
Limpia primero el layout de salida. Luego lee el archivo UTF-8, crea un `JsonParser`, parsea el valor raíz y delega la construcción del layout a `ParsearLayoutKLE`. Si todo sale bien, registra una traza con el número de teclas renderizables cargadas.

**Pseudocódigo:**

```text id="jlwm7k"
limpiar layout de salida
leer archivo UTF-8
si falla:
    devolver falso

crear parser JSON
parsear valor raíz
si falla:
    devolver error

parsear layout KLE
si falla:
    devolver falso

registrar cuántas teclas renderizables se cargaron
devolver verdadero
```

**Relaciones:**

* Usa <a href="#cid-22-15">CID-22-15</a>, <a href="#cid-22-17">CID-22-17</a>, <a href="#cid-22-29">CID-22-29</a> y <a href="#cid-22-35">CID-22-35</a>.
* Es una de las funciones públicas principales del subsistema.

---

### <a id="cid-22-35"></a>CID-22-35

**Qué hace:**
Limpia completamente el layout visual y reinicia sus métricas totales.

**Cómo funciona:**
Vacía el vector de teclas y pone a cero el ancho y el alto totales del layout.

**Pseudocódigo:**

```text id="mjlwm8"
vaciar lista de teclas
poner ancho total a cero
poner alto total a cero
```

**Relaciones:**

* Es usada por <a href="#cid-22-34">CID-22-34</a>.
* Es una función pública de mantenimiento del layout.

---

### <a id="cid-22-36"></a>CID-22-36

**Qué hace:**
Convierte una tecla visual abstracta a su rectángulo en píxeles dentro de un lienzo dado.

**Cómo funciona:**
Parte del origen del canvas y del tamaño de unidad en píxeles. A partir de la geometría abstracta `x`, `y`, `w`, `h` de la tecla calcula `left`, `top`, `right` y `bottom` en coordenadas de pantalla o de cliente.

**Pseudocódigo:**

```text id="jjlwm9"
calcular left a partir de origenX y x
calcular top a partir de origenY y y
calcular right a partir de x + w
calcular bottom a partir de y + h
devolver rectángulo
```

**Relaciones:**

* Es usada por <a href="#cid-22-37">CID-22-37</a> y por otros módulos de render como el setup visual.
* Es una función pública de geometría del layout.

---

### <a id="cid-22-37"></a>CID-22-37

**Qué hace:**
Busca la tecla visual situada bajo un punto de pantalla ya transformado al canvas del layout.

**Cómo funciona:**
Recorre todas las teclas renderizables del layout, calcula el rectángulo en píxeles de cada una y comprueba si el punto consultado cae dentro de ese rectángulo. Devuelve el índice de la primera coincidencia o `-1` si no encuentra ninguna.

**Pseudocódigo:**

```text id="pjlwm0"
para cada tecla del layout:
    si no es renderizable:
        continuar
    calcular su rectángulo en píxeles
    si el punto cae dentro:
        devolver índice
devolver -1
```

**Relaciones:**

* Usa <a href="#cid-22-36">CID-22-36</a>.
* Es usada por el asistente de setup para detectar clics sobre teclas visuales.

---

### <a id="cid-22-38"></a>CID-22-38

**Qué hace:**
Busca una tecla visual por su identificador CID dentro del layout cargado.

**Cómo funciona:**
Recorre todas las teclas del layout y compara su `idCid` con el identificador buscado. Devuelve el índice de la primera coincidencia o `-1` si no existe.

**Pseudocódigo:**

```text id="00jlwm"
para cada tecla del layout:
    si su id CID coincide:
        devolver índice
devolver -1
```

**Relaciones:**

* Es una función pública de búsqueda lógica del layout.
* Complementa la búsqueda geométrica de <a href="#cid-22-37">CID-22-37</a>.


## CID-23

La referencia <a href="#cid-23">CID-23</a> corresponde al archivo <code>layout_teclado_visual.h</code>. Este archivo actúa como interfaz pública del layout visual del teclado CID. Su responsabilidad principal es definir las estructuras de datos que representan una tecla visual y el layout completo del teclado, además de exponer las funciones necesarias para cargarlo, limpiarlo y operar sobre él mediante búsquedas geométricas o lógicas.

Dentro de <a href="#cid-23">CID-23</a> también se fija el contrato entre el parser del layout y los módulos que lo consumen, como el asistente de setup. Por eso aquí no aparece la lógica interna de parsing JSON/KLE ni la detección de IDs CID, sino únicamente los tipos y funciones públicas necesarios para trabajar con un teclado visual ya interpretado. En términos prácticos, <a href="#cid-23">CID-23</a> es la puerta pública de acceso al modelo visual del teclado CID.

### Índice interno de bloques

* <a href="#cid-23-01">CID-23-01</a>
* <a href="#cid-23-02">CID-23-02</a>
* <a href="#cid-23-03">CID-23-03</a>
* <a href="#cid-23-04">CID-23-04</a>
* <a href="#cid-23-05">CID-23-05</a>
* <a href="#cid-23-06">CID-23-06</a>
* <a href="#cid-23-07">CID-23-07</a>
* <a href="#cid-23-08">CID-23-08</a>
* <a href="#cid-23-09">CID-23-09</a>

---

### <a id="cid-23-01"></a>CID-23-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública del layout visual del teclado CID.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Así se evitan redefiniciones de estructuras y declaraciones por inclusión repetida.

**Pseudocódigo:**

```text id="fvm4u0"
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-23">CID-23</a>.
* Asegura que <a href="#cid-23-04">CID-23-04</a> a <a href="#cid-23-09">CID-23-09</a> no se dupliquen al incluir esta cabecera desde distintos módulos.

---

### <a id="cid-23-02"></a>CID-23-02

**Qué hace:**
Incluye los tipos base de Windows usados por geometría y color del layout.

**Cómo funciona:**
Incorpora `<windows.h>` para disponer de tipos como `COLORREF` y `RECT`, necesarios tanto en las estructuras públicas del layout como en las funciones geométricas expuestas.

**Pseudocódigo:**

```text id="jlwm11"
incluir tipos base de Windows para color y rectángulos
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-23">CID-23</a>.
* Da soporte directo a <a href="#cid-23-04">CID-23-04</a> y <a href="#cid-23-09">CID-23-09</a>.

---

### <a id="cid-23-03"></a>CID-23-03

**Qué hace:**
Incluye tipos de texto y contenedores usados por la interfaz del layout visual.

**Cómo funciona:**
Incorpora `<string>` para disponer de `std::wstring` y `<vector>` para almacenar la colección de teclas del layout. No contiene lógica ejecutable, pero prepara las dependencias mínimas necesarias para definir las estructuras públicas.

**Pseudocódigo:**

```text id="jlwm12"
incluir soporte de cadenas anchas
incluir soporte de vectores
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-23">CID-23</a>.
* Da soporte directo a <a href="#cid-23-04">CID-23-04</a>, <a href="#cid-23-05">CID-23-05</a>, <a href="#cid-23-06">CID-23-06</a> y <a href="#cid-23-08">CID-23-08</a>.

---

### <a id="cid-23-04"></a>CID-23-04

**Qué hace:**
Define una tecla visual del layout con identidad CID, texto, geometría y flags de render.

**Cómo funciona:**
Declara la estructura `TeclaVisualCID`, que agrupa toda la información necesaria para representar una tecla en el layout: su identificador lógico CID, el texto visible que se mostrará, el texto original leído del JSON, su geometría abstracta, su color y dos banderas auxiliares que indican si es gris y si debe renderizarse.

**Pseudocódigo:**

```text id="jlwm13"
definir estructura de tecla visual
guardar id CID
guardar texto visible y texto original
guardar posición y tamaño abstractos
guardar color
guardar flags de gris y renderizable
```

**Relaciones:**

* Usa `std::wstring` de <a href="#cid-23-03">CID-23-03</a> y `COLORREF` de <a href="#cid-23-02">CID-23-02</a>.
* Es consumida por <a href="#cid-23-05">CID-23-05</a> y <a href="#cid-23-09">CID-23-09</a>.
* Su implementación efectiva se alimenta desde el parser documentado en <a href="#cid-22">CID-22</a>.

---

### <a id="cid-23-05"></a>CID-23-05

**Qué hace:**
Define el layout visual completo del teclado con sus teclas y tamaño total abstracto.

**Cómo funciona:**
Declara la estructura `LayoutTecladoVisual`, que contiene el vector de todas las `TeclaVisualCID` del teclado y dos métricas globales: el ancho total y el alto total abstractos del layout cargado.

**Pseudocódigo:**

```text id="jlwm14"
definir estructura de layout visual
guardar lista de teclas visuales
guardar ancho total abstracto
guardar alto total abstracto
```

**Relaciones:**

* Usa `std::vector` de <a href="#cid-23-03">CID-23-03</a> y la estructura definida en <a href="#cid-23-04">CID-23-04</a>.
* Es usada por <a href="#cid-23-06">CID-23-06</a>, <a href="#cid-23-07">CID-23-07</a> y <a href="#cid-23-08">CID-23-08</a>.

---

### <a id="cid-23-06"></a>CID-23-06

**Qué hace:**
Declara la carga y limpieza del layout visual desde su archivo JSON/KLE.

**Cómo funciona:**
Expone dos funciones públicas. `CargarLayoutTecladoVisual` recibe la ruta del archivo, construye el layout resultante y puede devolver un error detallado. `LimpiarLayoutTecladoVisual` reinicia el estado del layout en memoria borrando sus teclas y sus métricas globales.

**Pseudocódigo:**

```text id="jlwm15"
declarar función para cargar layout visual desde JSON/KLE
declarar función para limpiar layout visual
```

**Relaciones:**

* Usa `std::wstring` de <a href="#cid-23-03">CID-23-03</a> y `LayoutTecladoVisual` de <a href="#cid-23-05">CID-23-05</a>.
* Se implementa en <a href="#cid-22-34">CID-22-34</a> y <a href="#cid-22-35">CID-22-35</a>.
* Forma parte del ciclo de vida público del layout visual.

---

### <a id="cid-23-07"></a>CID-23-07

**Qué hace:**
Declara el hit-test sobre el dibujo del teclado para localizar teclas por coordenadas.

**Cómo funciona:**
Expone una función pública que recibe un layout cargado, un punto en píxeles y la transformación actual del canvas del teclado. La implementación recorre las teclas renderizables y devuelve el índice de la tecla situada bajo ese punto o `-1` si no hay ninguna.

**Pseudocódigo:**

```text id="jlwm16"
declarar función para buscar tecla visual por coordenadas de pantalla
recibir layout, punto y transformación del canvas
devolver índice de tecla o -1
```

**Relaciones:**

* Usa `LayoutTecladoVisual` de <a href="#cid-23-05">CID-23-05</a>.
* Se implementa en <a href="#cid-22-37">CID-22-37</a>.
* Es consumida por módulos interactivos como el asistente de setup.

---

### <a id="cid-23-08"></a>CID-23-08

**Qué hace:**
Declara la búsqueda de una tecla visual por su identificador CID lógico.

**Cómo funciona:**
Expone una función pública que recibe un layout y un `idCid`, y devuelve el índice de la primera tecla visual cuyo identificador coincida o `-1` si no existe.

**Pseudocódigo:**

```text id="jlwm17"
declarar función para buscar tecla visual por id CID
recibir layout e identificador CID
devolver índice o -1
```

**Relaciones:**

* Usa `LayoutTecladoVisual` de <a href="#cid-23-05">CID-23-05</a> y `std::wstring` de <a href="#cid-23-03">CID-23-03</a>.
* Se implementa en <a href="#cid-22-38">CID-22-38</a>.
* Complementa la búsqueda geométrica declarada en <a href="#cid-23-07">CID-23-07</a>.

---

### <a id="cid-23-09"></a>CID-23-09

**Qué hace:**
Declara la conversión de una tecla visual abstracta a su rectángulo de píxeles en pantalla.

**Cómo funciona:**
Expone una función pública que recibe una `TeclaVisualCID` y una transformación de origen y unidad en píxeles. La implementación convierte la geometría abstracta de la tecla en un `RECT` utilizable por los módulos de dibujo o hit-test.

**Pseudocódigo:**

```text id="jlwm18"
declarar función para convertir tecla abstracta a rectángulo en píxeles
recibir tecla, origen y tamaño de unidad
devolver rectángulo resultante
```

**Relaciones:**

* Usa `TeclaVisualCID` de <a href="#cid-23-04">CID-23-04</a> y `RECT` de <a href="#cid-23-02">CID-23-02</a>.
* Se implementa en <a href="#cid-22-36">CID-22-36</a>.
* Es una utilidad geométrica base para <a href="#cid-23-07">CID-23-07</a> y para el render de teclas en otros módulos.


## CID-24

La referencia <a href="#cid-24">CID-24</a> corresponde al archivo <code>mapa_teclas_cid.cpp</code>. Este archivo implementa el mapa lógico y de compatibilidad de teclas CID. Su responsabilidad principal es definir el inventario oficial de nombres CID válidos, su orden lógico interno, sus propiedades especiales y una capa de compatibilidad temporal que traduce virtual keys heredadas a nombres CID del sistema.

Dentro de <a href="#cid-24">CID-24</a> también se concentra la lógica que permite al resto del motor razonar sobre las teclas CID sin depender directamente de scanCodes ni de layouts visuales. Por eso aquí no solo se valida si un nombre existe, sino que también se resuelve el orden canónico de impresión, se identifican teclas especiales como la marcadora de tilde y los pedales, y se mantiene un mapa provisional desde VK heredadas al sistema lógico moderno. En términos prácticos, <a href="#cid-24">CID-24</a> es la pieza que da identidad lógica estable a las teclas CID y mantiene el puente con el sistema heredado basado en virtual keys.

### Índice interno de bloques

* <a href="#cid-24-01">CID-24-01</a>
* <a href="#cid-24-02">CID-24-02</a>
* <a href="#cid-24-03">CID-24-03</a>
* <a href="#cid-24-04">CID-24-04</a>
* <a href="#cid-24-05">CID-24-05</a>
* <a href="#cid-24-06">CID-24-06</a>
* <a href="#cid-24-07">CID-24-07</a>
* <a href="#cid-24-08">CID-24-08</a>
* <a href="#cid-24-09">CID-24-09</a>
* <a href="#cid-24-10">CID-24-10</a>
* <a href="#cid-24-11">CID-24-11</a>
* <a href="#cid-24-12">CID-24-12</a>
* <a href="#cid-24-13">CID-24-13</a>
* <a href="#cid-24-14">CID-24-14</a>

---

### <a id="cid-24-01"></a>CID-24-01

**Qué hace:**
Incluye la implementación del mapa lógico y de compatibilidad de teclas CID a partir de su interfaz pública.

**Cómo funciona:**
Este bloque incorpora `mapa_teclas_cid.h`, que declara las funciones públicas del subsistema. Gracias a esta inclusión, el archivo actual puede definir la lógica real de validación por nombre, orden lógico, propiedades especiales y compatibilidad por virtual key.

**Pseudocódigo:**

```text id="cid2401"
incluir interfaz pública del mapa lógico CID
habilitar definición de sus funciones públicas
```

**Relaciones:**

* Prepara la implementación completa de <a href="#cid-24">CID-24</a>.
* Da soporte directo a <a href="#cid-24-06">CID-24-06</a> a <a href="#cid-24-14">CID-24-14</a>.

---

### <a id="cid-24-02"></a>CID-24-02

**Qué hace:**
Incluye utilidades de comparación de cadenas anchas para el mapa CID.

**Cómo funciona:**
Incorpora `<cwchar>` para disponer de funciones como `wcscmp`, usadas al comparar nombres CID dentro de la tabla lógica maestra.

**Pseudocódigo:**

```text id="cid2402"
incluir utilidades de comparación de cadenas anchas
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-24">CID-24</a>.
* Da soporte directo a <a href="#cid-24-05">CID-24-05</a>.

---

### <a id="cid-24-03"></a>CID-24-03

**Qué hace:**
Define la estructura lógica interna de cada tecla CID con orden y propiedades especiales.

**Cómo funciona:**
Declara `TeclaCIDLogica`, una estructura interna que agrupa el nombre oficial de la tecla, su orden lógico y tres banderas funcionales: si es marcadora de tilde, si es pedal principal y si es pedal auxiliar.

**Pseudocódigo:**

```text id="cid2403"
definir estructura lógica de tecla CID
guardar nombre
guardar orden lógico
guardar banderas de tilde y pedales
```

**Relaciones:**

* Es usada por <a href="#cid-24-04">CID-24-04</a> y <a href="#cid-24-05">CID-24-05</a>.
* Da soporte interno a todas las consultas por nombre de <a href="#cid-24-06">CID-24-06</a> a <a href="#cid-24-10">CID-24-10</a>.

---

### <a id="cid-24-04"></a>CID-24-04

**Qué hace:**
Define la tabla maestra de teclas CID con su orden lógico y banderas funcionales.

**Cómo funciona:**
Declara un array constante de `TeclaCIDLogica` que contiene todas las teclas oficiales del sistema: familias `I`, `C`, `D`, la tecla `CID_KEY` y `AUX_CID`. Cada entrada fija su orden lógico y sus propiedades especiales.

**Pseudocódigo:**

```text id="cid2404"
crear tabla maestra de teclas CID
registrar familias I, C y D
registrar CID_KEY y AUX_CID
guardar orden y propiedades especiales de cada una
```

**Relaciones:**

* Usa la estructura definida en <a href="#cid-24-03">CID-24-03</a>.
* Es recorrida por <a href="#cid-24-05">CID-24-05</a>.
* Constituye la base lógica de <a href="#cid-24-06">CID-24-06</a> a <a href="#cid-24-10">CID-24-10</a>.

---

### <a id="cid-24-05"></a>CID-24-05

**Qué hace:**
Busca una tecla CID lógica por nombre y devuelve su descriptor interno si existe.

**Cómo funciona:**
Rechaza nombres nulos o vacíos. Si el nombre es utilizable, recorre la tabla maestra `g_teclasCid` y compara cada entrada con `wcscmp`. Si encuentra coincidencia, devuelve un puntero a esa entrada; si no, devuelve `nullptr`.

**Pseudocódigo:**

```text id="cid2405"
si el nombre es nulo o vacío:
    devolver nulo

recorrer tabla maestra de teclas CID
si el nombre coincide con una entrada:
    devolver su descriptor

devolver nulo
```

**Relaciones:**

* Usa <a href="#cid-24-02">CID-24-02</a>, <a href="#cid-24-03">CID-24-03</a> y <a href="#cid-24-04">CID-24-04</a>.
* Es llamada por <a href="#cid-24-06">CID-24-06</a>, <a href="#cid-24-07">CID-24-07</a>, <a href="#cid-24-08">CID-24-08</a>, <a href="#cid-24-09">CID-24-09</a> y <a href="#cid-24-10">CID-24-10</a>.

---

### <a id="cid-24-06"></a>CID-24-06

**Qué hace:**
Comprueba si un nombre corresponde a una tecla CID válida del mapa lógico.

**Cómo funciona:**
Delegra completamente en `BuscarTeclaCIDLogica`. Si el helper devuelve un descriptor no nulo, considera el nombre válido; si devuelve nulo, lo considera inválido.

**Pseudocódigo:**

```text id="cid2406"
buscar tecla lógica por nombre
devolver si existe descriptor
```

**Relaciones:**

* Usa <a href="#cid-24-05">CID-24-05</a>.
* Es una función pública de validación por nombre dentro del subsistema lógico.

---

### <a id="cid-24-07"></a>CID-24-07

**Qué hace:**
Devuelve el orden lógico oficial de una tecla CID a partir de su nombre.

**Cómo funciona:**
Busca el descriptor interno de la tecla por nombre. Si lo encuentra, devuelve su campo `orden`; si no, devuelve `1000` como valor de orden muy tardío para nombres desconocidos.

**Pseudocódigo:**

```text id="cid2407"
buscar tecla lógica por nombre
si existe:
    devolver su orden
devolver orden alto por defecto
```

**Relaciones:**

* Usa <a href="#cid-24-05">CID-24-05</a>.
* Es reutilizada por <a href="#cid-24-12">CID-24-12</a>.
* Sirve como orden canónico para impresión y ordenación de acordes.

---

### <a id="cid-24-08"></a>CID-24-08

**Qué hace:**
Indica si una tecla CID por nombre es la marcadora de tilde del sistema.

**Cómo funciona:**
Busca el descriptor lógico por nombre y, si existe, devuelve su bandera `esMarcadoraTilde`. Si no existe, devuelve `false`.

**Pseudocódigo:**

```text id="cid2408"
buscar tecla lógica por nombre
si existe:
    devolver bandera de marcadora de tilde
devolver falso
```

**Relaciones:**

* Usa <a href="#cid-24-05">CID-24-05</a>.
* Es reutilizada por <a href="#cid-24-14">CID-24-14</a>.

---

### <a id="cid-24-09"></a>CID-24-09

**Qué hace:**
Indica si una tecla CID por nombre corresponde al pedal principal del sistema.

**Cómo funciona:**
Busca el descriptor lógico por nombre y, si existe, devuelve su bandera `esPedalPrincipal`. Si no existe, devuelve `false`.

**Pseudocódigo:**

```text id="cid2409"
buscar tecla lógica por nombre
si existe:
    devolver bandera de pedal principal
devolver falso
```

**Relaciones:**

* Usa <a href="#cid-24-05">CID-24-05</a>.
* Es una función pública de consulta lógica sobre teclas especiales.

---

### <a id="cid-24-10"></a>CID-24-10

**Qué hace:**
Indica si una tecla CID por nombre corresponde al pedal auxiliar del sistema.

**Cómo funciona:**
Busca el descriptor lógico por nombre y, si existe, devuelve su bandera `esPedalAuxiliar`. Si no existe, devuelve `false`.

**Pseudocódigo:**

```text id="cid2410"
buscar tecla lógica por nombre
si existe:
    devolver bandera de pedal auxiliar
devolver falso
```

**Relaciones:**

* Usa <a href="#cid-24-05">CID-24-05</a>.
* Es una función pública de consulta lógica sobre teclas especiales.

---

### <a id="cid-24-11"></a>CID-24-11

**Qué hace:**
Implementa el mapa temporal de compatibilidad que traduce virtual keys antiguas a nombres CID.

**Cómo funciona:**
Usa un `switch` sobre `DWORD vk` para resolver cada virtual key heredada a su nombre CID oficial. Cubre las familias `C`, `I`, `D` y también `VK_SPACE` como `CID_KEY`. Si no reconoce la VK, devuelve `nullptr`.

**Pseudocódigo:**

```text id="cid2411"
según la virtual key recibida:
    devolver nombre CID equivalente de familia C
    o de familia I
    o de familia D
    o CID_KEY si es espacio
si no coincide ninguna:
    devolver nulo
```

**Relaciones:**

* Es la base de compatibilidad heredada usada por <a href="#cid-24-12">CID-24-12</a>, <a href="#cid-24-13">CID-24-13</a> y <a href="#cid-24-14">CID-24-14</a>.
* Conecta el sistema antiguo por VK con el sistema lógico moderno por nombre.

---

### <a id="cid-24-12"></a>CID-24-12

**Qué hace:**
Devuelve el orden lógico oficial de una tecla a partir de su virtual key heredada.

**Cómo funciona:**
Primero traduce la virtual key a nombre CID usando `NombreTeclaCID`. Después delega en `OrdenTeclaCID_PorNombre` para obtener el orden lógico oficial.

**Pseudocódigo:**

```text id="cid2412"
traducir virtual key a nombre CID
devolver orden lógico de ese nombre
```

**Relaciones:**

* Usa <a href="#cid-24-11">CID-24-11</a> y <a href="#cid-24-07">CID-24-07</a>.
* Permite mantener orden canónico también en el flujo heredado basado en VK.

---

### <a id="cid-24-13"></a>CID-24-13

**Qué hace:**
Comprueba si una virtual key pertenece al sistema CID heredado por VK.

**Cómo funciona:**
Llama a `NombreTeclaCID` y devuelve `true` si la traducción a nombre CID no es nula. Si no existe correspondencia, devuelve `false`.

**Pseudocódigo:**

```text id="cid2413"
traducir virtual key a nombre CID
devolver si existe traducción válida
```

**Relaciones:**

* Usa <a href="#cid-24-11">CID-24-11</a>.
* Es una función pública de validación sobre el mapa heredado por virtual key.

---

### <a id="cid-24-14"></a>CID-24-14

**Qué hace:**
Comprueba si una virtual key heredada corresponde a la marcadora de tilde.

**Cómo funciona:**
Primero traduce la virtual key a nombre CID con `NombreTeclaCID`. Luego delega en `EsMarcadoraTilde_PorNombre` para saber si esa tecla lógica es la marcadora de tilde del sistema.

**Pseudocódigo:**

```text id="cid2414"
traducir virtual key a nombre CID
consultar si ese nombre es la marcadora de tilde
devolver resultado
```

**Relaciones:**

* Usa <a href="#cid-24-11">CID-24-11</a> y <a href="#cid-24-08">CID-24-08</a>.
* Completa la capa de compatibilidad heredada con una consulta de propiedad especial.


## CID-25

La referencia <a href="#cid-25">CID-25</a> corresponde al archivo <code>mapa_teclas_cid.h</code>. Este archivo actúa como interfaz pública del mapa lógico de teclas CID. Su responsabilidad principal es exponer al resto del motor las funciones necesarias para validar nombres CID, consultar su orden lógico y sus propiedades especiales, además de mantener una capa temporal de compatibilidad con el sistema heredado basado en virtual keys.

Dentro de <a href="#cid-25">CID-25</a> también se define el contrato entre el sistema lógico moderno por nombre y la compatibilidad antigua por VK. Por eso aquí no aparece la tabla maestra de teclas ni el switch de traducción heredada, sino únicamente las declaraciones públicas que permiten consultar esa información desde otros módulos. En términos prácticos, <a href="#cid-25">CID-25</a> es la puerta pública de acceso a la identidad lógica de las teclas CID y al puente de compatibilidad con el mapa heredado.

### Índice interno de bloques

* <a href="#cid-25-01">CID-25-01</a>
* <a href="#cid-25-02">CID-25-02</a>
* <a href="#cid-25-03">CID-25-03</a>
* <a href="#cid-25-04">CID-25-04</a>

---

### <a id="cid-25-01"></a>CID-25-01

**Qué hace:**
Previene inclusiones múltiples de la interfaz pública del mapa lógico de teclas CID.

**Cómo funciona:**
Usa `#pragma once` para indicar al compilador que esta cabecera solo debe procesarse una vez por unidad de traducción. Así se evitan redefiniciones de declaraciones y conflictos por inclusión repetida.

**Pseudocódigo:**

```text id="cid2501"
marcar esta cabecera para inclusión única
```

**Relaciones:**

* Protege todo <a href="#cid-25">CID-25</a>.
* Asegura que <a href="#cid-25-03">CID-25-03</a> y <a href="#cid-25-04">CID-25-04</a> no se dupliquen al incluir esta cabecera desde distintos módulos.

---

### <a id="cid-25-02"></a>CID-25-02

**Qué hace:**
Incluye los tipos base de Windows usados por la compatibilidad heredada por virtual key.

**Cómo funciona:**
Incorpora `<windows.h>` para disponer de tipos como `DWORD`, usados por las funciones públicas que trabajan con virtual keys del sistema antiguo.

**Pseudocódigo:**

```text id="cid2502"
incluir tipos base de Windows
```

**Relaciones:**

* Prepara el entorno de compilación para <a href="#cid-25">CID-25</a>.
* Da soporte directo a <a href="#cid-25-04">CID-25-04</a>.

---

### <a id="cid-25-03"></a>CID-25-03

**Qué hace:**
Declara la validación y propiedades lógicas de teclas CID identificadas por nombre.

**Cómo funciona:**
Expone cinco funciones públicas que trabajan sobre nombres CID: una para validar si el nombre existe en el sistema, una para obtener su orden lógico oficial y tres para consultar si esa tecla es la marcadora de tilde, el pedal principal o el pedal auxiliar.

**Pseudocódigo:**

```text id="cid2503"
declarar función para validar nombre CID
declarar función para obtener orden lógico por nombre
declarar función para consultar si es marcadora de tilde
declarar función para consultar si es pedal principal
declarar función para consultar si es pedal auxiliar
```

**Relaciones:**

* Se implementa en <a href="#cid-24-06">CID-24-06</a>, <a href="#cid-24-07">CID-24-07</a>, <a href="#cid-24-08">CID-24-08</a>, <a href="#cid-24-09">CID-24-09</a> y <a href="#cid-24-10">CID-24-10</a>.
* Representa la API pública del sistema lógico moderno por nombre.

---

### <a id="cid-25-04"></a>CID-25-04

**Qué hace:**
Declara la capa temporal de compatibilidad del sistema antiguo basado en virtual keys.

**Cómo funciona:**
Expone cuatro funciones públicas que operan sobre `DWORD vk`: una para traducir la VK a nombre CID, una para obtener su orden lógico, una para comprobar si la VK pertenece al sistema CID y una última para consultar si esa VK corresponde a la marcadora de tilde heredada.

**Pseudocódigo:**

```text id="cid2504"
declarar función para traducir virtual key a nombre CID
declarar función para obtener orden lógico por virtual key
declarar función para comprobar si una virtual key es tecla CID
declarar función para comprobar si una virtual key es marcadora de tilde
```

**Relaciones:**

* Usa `DWORD` incluido en <a href="#cid-25-02">CID-25-02</a>.
* Se implementa en <a href="#cid-24-11">CID-24-11</a>, <a href="#cid-24-12">CID-24-12</a>, <a href="#cid-24-13">CID-24-13</a> y <a href="#cid-24-14">CID-24-14</a>.
* Completa junto a <a href="#cid-25-03">CID-25-03</a> la interfaz pública total del mapa lógico CID.
