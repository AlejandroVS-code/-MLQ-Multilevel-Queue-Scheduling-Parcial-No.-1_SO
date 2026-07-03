/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Implementación de la clase RRScheduling, la cual representa
   el algoritmo Round Robin dentro del planificador MLQ. Este archivo define
   los métodos necesarios para seleccionar el siguiente proceso de la Ready
   Queue, indicar el tipo de expropiación utilizado por el algoritmo y
   consultar el valor del Quantum asignado para cada proceso.
*/

#include "RRScheduling.h"

//Constructor de la clase RRScheduling
RRScheduling::RRScheduling(int quantumSize){quantum = quantumSize;}

//Selecciona el siguiente proceso de la Ready Queue
Process* RRScheduling::selectNext(std::vector<Process*>& ready)
{
    if(ready.empty())
    {
        return nullptr;
    }
    //Round Robin ejecuta el primer proceso que se encuentra en la cola.
    return ready.front();
}

//Revisa si un proceso nuevo debe expropiar al que esta en ejecucion
bool RRScheduling::shouldPreempt(Process* running, Process* arriving)
{
    //Round Robin no expropia cuando llega un proceso nuevo.
    //El proceso simplemente espera su turno en la Ready Queue.
    (void)running;
    (void)arriving;

    return false;
}

//Indica que Round Robin utiliza expropiacion por Quantum
bool RRScheduling::needsTimeBasedPreemption() const{return true;}

//getter para obtener el Quantum
int RRScheduling::getQuantum() const{return quantum;}