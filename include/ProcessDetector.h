/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co

   Versión: 1.0
   Descripción: Este archivo define la clase ProcessDetector, la cual
   se encarga de leer la información de los procesos desde un archivo
   de entrada y generar el archivo de salida con los resultados
   También permite crear los objetos Process que actuan como procesos y son utilizados
   por el planificador.
*/

#ifndef PROCESS_DETECTOR_H
#define PROCESS_DETECTOR_H

#include <vector>
#include <string>
#include "Process.h"

class ProcessDetector
{
public:
    ProcessDetector();
    ~ProcessDetector();

    std::vector<Process*> readInput(std::string path);
    void writeOutput(std::string path, std::vector<Process*> results);
};
#endif