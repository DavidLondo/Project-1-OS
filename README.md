# Simulador de Planificador

Este proyecto es un **simulador de ejecución de procesos** que lee un archivo de definición de procesos y sus instrucciones, los carga en memoria y simula su ejecución usando un ciclo de CPU.

## Descripción

- Lee un archivo de texto que describe procesos con su PID, registros (`AX`, `BX`, `CX`), y quantum asignado.
- Para cada proceso, carga sus instrucciones desde archivos separados en la carpeta `instructions/`.
- Soporta instrucciones simples como:
  - `ADD reg, valor|reg`
  - `SUB reg, valor|reg`
  - `MUL reg, valor|reg`
  - `INC reg`
  - `NOP`
- Simula la ejecución instrucción por instrucción, actualizando los registros y mostrando el estado del proceso.

---

## Estructura del proyecto

```plaintext
├── Makefile
├── test.txt
├── build/
│   └── instructions/
│       ├── 1.txt
│       ├── 2.txt
│       ├── 3.txt
│       ├── 4.txt
│       └── 5.txt
├── src/
│   ├── main.c
│   ├── Models/
│   │   ├── instruction.c
│   │   ├── process.c
│   │   └── scheduler.c
│   └── Utils/
│       ├── loader.c
│       ├── parser.c
│       └── queue.c
```

---

## Requisitos

- **Sistema operativo**: Linux, macOS o cualquier sistema con soporte para GCC.
- **Compilador**: [GCC](https://gcc.gnu.org/) instalado.
- **Herramienta de construcción**: `make`

---

## Instalación y compilación

1. Clonar este repositorio o copiar el proyecto en tu máquina.
2. Abrir una terminal y ubicarse en la carpeta raíz del proyecto.
3. Ejecutar:

```bash
make
```

## Uso

1. Asegúrate de que en la carpeta instructions/ existan los archivos con las instrucciones correspondientes a los PIDs que aparecerán en tu archivo de entrada (por ejemplo 1.txt, 2.txt, etc.).
2. Es neceario que en la misma carpeta donde se encuentre app, exista una carpeta /instructions la cual almacene todos los *.txt de las instruciones 
3. Desde la carpeta raíz del proyecto, después de compilar, ejecuta:

```bash
cd build
./app ../process.txt
```

