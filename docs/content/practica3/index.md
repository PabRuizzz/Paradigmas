---
title: "Práctica 3: Haskell"
date: 2026-04-01
draft: false
---

# Reporte de Actividad — Haskell

# Práctica 3

Pablo Fernando Ruiz Perez  379207

Jose Carlos Gallegos Mariscal  
1 de Mayo de 2026  

## 1. Introducción

En la siguiente practica se tiene como objetivo introducir el paradigma funcional mendiante el lenguaje Haskell, en la cual se mostrar como se instala el entorno de desarrollo, como se compilan archivos y crean proyectos con este lenguaje. 

Haskell se caracteriza por ser un lenguaje de programación funcional puro y estrictamente tipado, lo que significa que las funciones no tienen efectos secundarios y el compilador garantiza una alta seguridad frente a errores en tiempo de ejecución. Su evaluación es perezosa (lazy evaluation), retrasando el cálculo de expresiones hasta que su resultado es realmente necesario, lo que permite trabajar con estructuras de datos infinitas de forma eficiente.

## 2. Instalacion Entorno de desarrollo 

Para la instalacion del entorno de desarrollo de Haskell se tiene que introducir el siguiente comando de la pagina https://www.haskell.org/ghcup/ en powershell.
```
Set-ExecutionPolicy Bypass -Scope Process -Force;[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; try { & ([ScriptBlock]::Create((Invoke-WebRequest https://www.haskell.org/ghcup/sh/bootstrap-haskell.ps1 -UseBasicParsing))) -Interactive -DisableCurl } catch { Write-Error $_ }
```
Al ejecutar el comando tenemos que asegurarnos de que se instalen los siguientes elementos: 

GHCup → Herramienta de instalación e entorno de desarrollo, el enlace ejecutado desacarga y realiza la instalación utilizando esta herramienta.

GHC → Compilador de Haskell.

Hugs → Interprete interactivo de Haskell.

HLS → Haskell Language Server, este no lo utilizan directamente. contiene las librerías estándar y código de funcionamiento de Haskell, del cual hacen uso GHC y Hugs.

Cabal → Herramienta de empaquetado de binarios (buildtool), se encarga de utilizar Stack para descargar dependencias y GHC para compilar el código en un solo comando.

## 3. Crear Ejecutables

Para crear ejecutables de Haskell simplemente se deben de crear un arcvhivo en extension "hs" con la sintaxis aporpiada del lenguaje. A continuacion ejemplos de la sintaxis del lenguaje:

``` haskell
    main :: IO ()
    main = putStrLn "Hola mundo desde Haskell"
```
main → nombre de la función principal (punto de entrada del programa)

:: → operador que indica el tipo de la función

IO () → tipo que representa una acción de entrada/salida

``` haskell
    main :: IO ()
    main = do
    let a = 5
    let b = 3
    print (a + b)
```

main → función principal

= → asignación

do → indica un bloque de acciones secuenciales (necesario en IO)

let → define una variable local

a → nombre de la variable

5 → valor entero

print → función que muestra un valor en pantalla

( ) → agrupan la operación

\+ → operador de suma

Para crear el ejecutable de los archivos tan solo es necesario el siguiente comando:

``` BASH
    ghc main.hs
```

y para ejecutarlo:

``` BASH
    main.exe
```

## 3. Instalar Stack

Para la instalacion del stack que nos permita crear una aplicacion es necesario el siguiente comando:

``` BASH
ghcup install stack
```

![](imagenes/stack1.png)

posteriormente:

``` BASH
ghcup set stack
```

![](imagenes/stack4.png)

para crear la app:

``` BASH
stack new mi-app
```

![](imagenes/stack2.png)

Para comprobar que todo funcione, tendremos que correr la app y esperar "SomeFuc":

``` BASH
cd mi-app
stack run
```

![](imagenes/stack5.png)

## 4. Conclusion

En esta práctica se logró comprender el uso básico del lenguaje Haskell, desde la creación de archivos .hs hasta su compilación y ejecución en la terminal. Se identificó la importancia del compilador GHC, el cual permite transformar el código fuente en programas ejecutables, así como el uso de herramientas que facilitan el desarrollo.

Se exploró el uso de Stack como gestor de proyectos, destacando su capacidad para automatizar la compilación, ejecución y manejo de dependencias, lo que resulta especialmente útil en aplicaciones más completas. También se comprobó que el entorno de desarrollo puede integrarse con herramientas como Visual Studio Code, mejorando la experiencia de programación.

Repositorio: https://github.com/PabRuizzz/Paradigmas/actions/runs/22252480222

Página: https://pabruizzz.github.io/Paradigmas/