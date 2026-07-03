/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co

   Version: 1.0
   Descripcion: Implementacion de la clase MetricsCalculator, la cual se
   encarga de calcular los promedios de las metricas obtenidas al finalizar
   los procesos.
*/

#include "MetricsCalculator.h"

MetricsCalculator::MetricsCalculator()
{

}

MetricsCalculator::~MetricsCalculator()
{

}

//Calcula el promedio de las metricas de todos los procesos
std::tuple<float, float, float, float> MetricsCalculator::calculateAverages(std::vector<Process*> processes)
{
    if(processes.empty())
    {
        return std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f);
    }

    float totalWT = 0;
    float totalCT = 0;
    float totalRT = 0;
    float totalTAT = 0;

    for(size_t i = 0; i < processes.size(); i++)
    {
        Process* process = processes.at(i);

        totalWT += process->getWaitingTime();
        totalCT += process->getCompletionTime();
        totalRT += process->getResponseTime();
        totalTAT += process->getTurnaroundTime();
    }

    float processCount = static_cast<float>(processes.size());

    float averageWT = totalWT / processCount;
    float averageCT = totalCT / processCount;
    float averageRT = totalRT / processCount;
    float averageTAT = totalTAT / processCount;

    return std::make_tuple(averageWT,
                           averageCT,
                           averageRT,
                           averageTAT);
}