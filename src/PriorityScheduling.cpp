/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Implementación de la clase PriorityScheduling, la cual
   representa el algoritmo Priority expropiativo dentro del planificador
   MLQ. Este archivo define los métodos necesarios para seleccionar el
   proceso con mayor prioridad de la Ready Queue y determinar si un
   proceso nuevo debe expropiar al que se encuentra actualmente en CPU.
*/

#include "PriorityScheduling.h"

//Constructor de la clase PriorityScheduling
PriorityScheduling::PriorityScheduling()
{
}

//Destructor de la clase PriorityScheduling
PriorityScheduling::~PriorityScheduling()
{
}

//Selecciona el proceso con mayor prioridad de la Ready Queue, para ejecutar a continuacion
Process* PriorityScheduling::selectNext(std::vector<Process*>& ready)
{
    if(ready.empty())
    {
        return nullptr;
    }

    Process* best = ready[0];

    for(size_t i = 1; i < ready.size(); i++)
    {
        if(ready[i]->getPriority() > best->getPriority())
        {
            best = ready[i];
        }
    }

    return best;
}

//Revisa si el proceso nuevo debe expropiar al que esta en CPU, en caso 
//de tener una prioridad mayor al que esta en cpu, expropia 
bool PriorityScheduling::shouldPreempt(Process* running, Process* arriving)
{
    if(running == nullptr)
    {
        return false;
    }

    if(arriving->getPriority() > running->getPriority())
    {
        return true;
    }

    return false;
}

//Priority no utiliza expropiacion por Quantum
bool PriorityScheduling::needsTimeBasedPreemption() const
{
    return false;
}