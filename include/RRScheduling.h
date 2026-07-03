/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Este archivo define la clase RRScheduling, la cual implementa
   el algoritmo de planificación Round Robin(RR). Este algoritmo asigna un
   quantum de tiempo fijo a cada proceso de la cola de listos, ejecutándolos
   en el orden en que llegan. Cuando un proceso consume completamente su
   quantum sin finalizar su ejecución, es enviado nuevamente al final de la
   cola para esperar un nuevo turno. 
   En esta clase se define los métodos necesarios para seleccionar el siguiente proceso, 
   indicar el tipo de expropiación utilizado por el algoritmo y consultar el valor del quantum asignado.
*/

#ifndef RR_SCHEDULING_H
#define RR_SCHEDULING_H

#include "SchedulingAlgorithm.h"

class RRScheduling : public SchedulingAlgorithm {
private:
    // Quantum de tiempo asignado a cada proceso
    int quantum;

public:
    // Constructor de la clase
    explicit RRScheduling(int quantumSize);

    // Selecciona el siguiente proceso siguiendo el orden de llegada
    Process* selectNext(std::vector<Process*>& readyQueue) override;

    // La llegada de un nuevo proceso no genera expropiación inmediata
    bool shouldPreempt(Process* currentRunning,
                       Process* newIncoming) override;

    // Round Robin utiliza expropiación basada en quantum
    bool needsTimeBasedPreemption() const override;

    // Retorna el valor del quantum configurado.
    // pues dependiendo de la fila el valor del quantum cambia
    int getQuantum() const;
};

#endif // RR_SCHEDULING_H