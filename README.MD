# Simulador MLQ (Multilevel Queue Scheduling)

**Universidad del Valle — Sistemas Operativos**
**Parcial No. 1**

**Autor:** Alejandro Valencia Sandoval
**Código:** 2515411
**Correo:** alejandro.valencia.sandoval@correounivalle.edu.co

---

## Descripción

Simulador de planificación de procesos usando **Multilevel Queue (MLQ)**, implementado en C++ con paradigma orientado a objetos.

El sistema organiza los procesos en 3 colas, cada una con su propio algoritmo de planificación:

- **Cola 1:** Round Robin, quantum = 3
- **Cola 2:** Round Robin, quantum = 5
- **Cola 3:** Priority (expropiativo)

Entre colas, la de mayor prioridad **siempre** expropia a una de menor prioridad. El simulador calcula, para cada proceso, el tiempo de espera (WT), el tiempo de finalización (CT), el tiempo de respuesta (RT) y el tiempo de retorno (TAT), además de los promedios de estas 4 métricas.

---

## Requisitos previos

- [Docker Desktop](https://www.docker.com/products/docker-desktop/) instalado y corriendo en Windows (usa WSL2 automáticamente, no requiere configuración adicional).
- Git instalado.

---

## Cómo ejecutar el proyecto — paso a paso

### 1. Descargar el proyecto

Si aún no lo tienes en tu máquina, clónalo desde GitHub:

```bash
git clone https://github.com/AlejandroVS-code/-MLQ-Multilevel-Queue-Scheduling-Parcial-No.-1_SO.git
```

### 2. Entrar a la carpeta del proyecto

Abre una terminal (CMD o PowerShell) y muévete a la carpeta descargada:

```bash
cd  -MLQ-Multilevel-Queue-Scheduling-Parcial-No.-1_SO
```

### 3. Levantar el entorno Docker (solo la primera vez, o si cambia el Dockerfile)

Este paso construye una imagen de Ubuntu con `g++`, `make` y `gdb` ya instalados, para no depender de instalar un compilador directamente en Windows:

```bash
docker compose up -d --build
```

Espera a que termine (puede tardar 1-2 minutos la primera vez).

### 4. Entrar al contenedor

Esto te abre una terminal dentro del Ubuntu del contenedor:

```bash
docker compose exec dev bash
```

Vas a ver que el prompt cambia a algo como `root@xxxxxxxx:/app#` — eso confirma que ya estás dentro.

### 5. Compilar el proyecto

Ya dentro del contenedor (con el prompt `root@...`), compila con:

```bash
make
```

Esto genera un ejecutable llamado **`Project`** en la carpeta raíz del proyecto.

### 6. Ejecutar el simulador

El programa recibe dos argumentos: el archivo de entrada y el archivo de salida.

```bash
./Project inputs/mlq001.txt outputs/mlq001_output.txt
```

- **`inputs/mlq001.txt`** → aquí va el archivo con los procesos a simular (ver formato abajo).
- **`outputs/mlq001_output.txt`** → aquí se va a escribir el resultado con las métricas de cada proceso.

### 7. Ver el resultado

```bash
cat outputs/mlq001_output.txt
```

### 8. Salir del contenedor (sin detenerlo)

```bash
exit
```

---

## Formato del archivo de entrada

Cada línea representa un proceso, con los campos separados por `;`:

```
# etiqueta;BT;AT;Q;Prioridad
A;6;0;1;5
```

| Campo | Significado |
|---|---|
| etiqueta | Identificador del proceso (ej. "A") |
| BT | Burst Time — tiempo total de CPU que necesita |
| AT | Arrival Time — momento en que llega al sistema |
| Q | Cola a la que pertenece (1, 2 o 3) |
| Prioridad | Prioridad del proceso (5 = más alta, 1 = más baja) |

Las líneas que empiezan con `#` son comentarios y se ignoran. Las líneas con datos inválidos (BT ≤ 0, AT < 0, o menos de 5 campos) se descartan automáticamente, y el programa sigue procesando el resto del archivo.

**Para agregar tu propio archivo de entrada:** créalo dentro de la carpeta `inputs/` (por ejemplo, `inputs/mi_prueba.txt`), con el mismo formato de arriba, y ejecútalo con:

```bash
./Project inputs/mi_prueba.txt outputs/mi_prueba_output.txt
```

---

## Formato del archivo de salida

```
# etiqueta;BT;AT;Q;Pr;WT;CT;RT;TAT
A;6;0;1;5;3;9;0;9
# WT=10.6; CT=18.8; RT=12.2; TAT=16
```

La última línea muestra los promedios de las 4 métricas sobre todos los procesos.

## Estructura del proyecto

```
mlq-scheduler-SO/
├── include/          # Headers (.h) — declaraciones de clases
├── src/              # Implementación (.cpp)
├── inputs/           # Archivos de entrada de prueba
├── outputs/          # Resultados generados por el simulador
├── docs/             # Diagrama de clases UML
├── main.cpp
├── Dockerfile
├── docker-compose.yml
├── Makefile
└── README.md
```