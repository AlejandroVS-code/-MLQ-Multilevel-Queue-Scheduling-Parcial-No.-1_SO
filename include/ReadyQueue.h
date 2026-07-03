/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Este archivo define la clase ReadyQueue, la cual representa
   una cola de procesos listos dentro del planificador MLQ. Cada ReadyQueue
   almacena los procesos que se encuentran esperando por CPU y tiene asociado
   un algoritmo de planificación, el cual se encarga de seleccionar el
   siguiente proceso que será ejecutado.
*/

#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include <vector>
#include "Process.h"
#include "SchedulingAlgorithm.h"

class ReadyQueue
{
private:
    //Vector donde se almacenan los procesos listos
    std::vector<Process*> processes;

    //Algoritmo de planificacion asociado a la cola
    SchedulingAlgorithm* algorithm;

public:

    //Constructor por defecto
    ReadyQueue();

    //Constructor que recibe el algoritmo de planificacion
    ReadyQueue(SchedulingAlgorithm* algorithm);

    //Destructor de la clase
    ~ReadyQueue();

    //Agrega un proceso a la Ready Queue
    void addProcess(Process* p);

    //Obtiene el siguiente proceso segun el algoritmo
    Process* getNext();

    //Revisa si la Ready Queue esta vacia
    bool isEmpty() const;
Process* peekNext() const; 
    //getter para obtener el algoritmo de planificacion
    SchedulingAlgorithm* getAlgorithm() const;
};

#endif // READY_QUEUE_H