/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Clase PriorityScheduling, Se define el 
   algoritmo Priority expropiativo. En este caso el proceso el cual poseea mayor prioridad
   (siendo 5 más alta y 1 como el más bajo) corre primero, y si durante su ejecucion
   llega un proceso con prioridad mayor al que está corriendo actualmente, este sera
   expropiado de inmediato.
   Se definen funciones las cuales ayuden a cumplir el funcionamiento anteriormente mencionado
*/

#ifndef PRIORITY_SCHEDULING_H
#define PRIORITY_SCHEDULING_H

#include "SchedulingAlgorithm.h"

// La clase PriorityScheduling hereda de SchedulingAlgorithm e implementa
// la lógica en este caso esta enfocado para ser expropiativo 
class PriorityScheduling : public SchedulingAlgorithm
{
public:
    // Constructor por defecto
    PriorityScheduling();

    // Destructor
    ~PriorityScheduling();

    // Selecciona el proceso con mayor prioridad de la cola de listos
    Process* selectNext(std::vector<Process*>& readyQueue) override;

    // Determina si un nuevo proceso debe expropiar al que está ejecutándose
    bool shouldPreempt(Process* currentRunning,
                       Process* newIncoming) override;

    // Como es por prioridad en este caso no se expropia por quantum, si no por importancia
    bool needsTimeBasedPreemption() const override;
};

#endif // PRIORITY_SCHEDULING_H