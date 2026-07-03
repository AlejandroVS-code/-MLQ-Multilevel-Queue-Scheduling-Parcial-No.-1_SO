/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co

   Version: 1.0
   Descripcion: Este archivo define la clase MetricsCalculator, la cual
   se encarga de calcular las metricas promedio de los procesos una vez
   finalizan. Entre estas metricas se encuentran el Waiting
   Time, Completion Time, Response Time y Turnaround Time.
*/

#ifndef METRICS_CALCULATOR_H
#define METRICS_CALCULATOR_H

#include <vector>
#include <tuple>
#include "Process.h"

class MetricsCalculator
{
public:

    MetricsCalculator();

    ~MetricsCalculator();

    //Calcula los promedios de las metricas de los procesos
    std::tuple<float, float, float, float> calculateAverages(std::vector<Process*> processes);
};

#endif // METRICS_CALCULATOR_H