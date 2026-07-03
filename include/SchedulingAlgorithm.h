/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Este archivo define la clase abstracta SchedulingAlgorithm,
   la cual sirve como interfaz para los algoritmos de planificación
   implementados. Esta clase establece los métodos que
   deben implementar los algoritmos Round Robin y Priority, permitiendo
   que el planificador MLQ pueda utilizarlos sin depender de una
   implementación específica.
*/

#ifndef SCHEDULING_ALGORITHM_H
#define SCHEDULING_ALGORITHM_H

#include <vector>
#include "Process.h"

class SchedulingAlgorithm
{
public:

    //Destructor de la clase
    virtual ~SchedulingAlgorithm() = default;

    //Selecciona el siguiente proceso de la Ready Queue
    virtual Process* selectNext(std::vector<Process*>& ready) = 0;

    //Revisa si un proceso nuevo debe expropiar al proceso que esta en CPU
    virtual bool shouldPreempt(Process* running, Process* arriving) = 0;

    //Indica el tipo de expropiacion que utiliza el algoritmo
    virtual bool needsTimeBasedPreemption() const = 0;
};

#endif // SCHEDULING_ALGORITHM_H