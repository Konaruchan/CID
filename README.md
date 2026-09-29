# CID

**CID** es un sistema de escritura por acordes pensado principalmente para el español.

Este repositorio contiene su implementación principal actual: el **motor CID para Windows**, diseñado para permitir escritura rápida sin dejar de apoyarse en hardware común, especialmente teclados convencionales como QWERTY.

## Qué contiene este repositorio

El repositorio oficial de CID reúne principalmente:

- el motor actual de CID para Windows
- el código fuente del proyecto
- archivos y recursos asociados a su implementación
- acceso a la documentación general del sistema y del proyecto

CID no se reduce a este repositorio. El sistema de escritura y su implementación concreta no son exactamente la misma cosa: aquí se publica el motor y los materiales que le dan forma práctica.

## Documentación

La documentación principal de CID se encuentra en la **wiki** del repositorio.

Allí se organiza en tres bloques principales:

- **Manual de desarrollo**  
  Arquitectura general del proyecto, organización interna del código, referencias `CID-XX-YY`, bloques del sistema y detalles técnicos de desarrollo.

- **Manual de funcionamiento práctico**  
  Explicación del sistema CID desde el punto de vista del uso: qué es, cómo se escribe con él, cómo se interpretan los acordes y cómo se utiliza en la práctica.

- **Manual de información legal y de interés general**  
  Información complementaria del proyecto: referencias utilizadas, licencia, uso de IA y otras notas generales.

👉 **Wiki principal:**  
<https://github.com/Konaruchan/CID/wiki>

## Estado del proyecto

CID se encuentra en desarrollo y evolución activa.

La implementación disponible en este repositorio representa el estado actual del motor y de la documentación asociada, pero el sistema puede seguir cambiando, ampliándose y refinándose con el tiempo.

## Releases

Las versiones públicas compiladas del motor CID, cuando estén disponibles, pueden consultarse en la sección de **Releases** del repositorio.

👉 **Releases:**  
<https://github.com/Konaruchan/CID/releases>

## Recorrido recomendado

Si llegaste aquí por primera vez, el recorrido recomendado es este:

1. leer la **wiki**
2. empezar por el **manual de funcionamiento práctico** si quieres entender el sistema
3. pasar al **manual de desarrollo** si quieres estudiar o modificar la implementación
4. consultar el **manual de información legal y de interés general** para referencias, licencia y notas complementarias

## Licencia

El contenido distribuido en este repositorio se publica bajo la licencia indicada en el propio proyecto.

Para conocer con precisión los permisos, condiciones y limitaciones aplicables, consulta directamente el archivo **`LICENSE`** incluido en la raíz del repositorio.

## Build 0.2 beta

Consulta [los cambios](CHANGELOG.md) y la [guía rápida](GUIA-RAPIDA.md). Para compilar y generar el ZIP con sus recursos, ejecuta `./scripts/build.ps1 -Platform x64` en PowerShell con Visual Studio 2022 y la carga de trabajo C++. También se genera la variante de 32 bits con `-Platform Win32`. El script ejecuta las pruebas antes de empaquetar.

El diccionario fuente vigente es `Motor_CID/cid0.cid`. Al compilar se copia como `Diccionarios/cid0.cid` junto al ejecutable; la copia histórica bajo `Motor_CID/Diccionarios/` no se empaqueta.
