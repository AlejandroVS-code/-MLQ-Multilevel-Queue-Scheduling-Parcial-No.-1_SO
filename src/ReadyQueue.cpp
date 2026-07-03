/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Implementación de la clase ReadyQueue, la cual representa
   una cola de procesos listos dentro del planificador MLQ. Este archivo
   define los métodos necesarios para agregar procesos a la cola, obtener
   el siguiente proceso según el algoritmo de planificación asociado y
   consultar el estado de la Ready Queue.
*/

#include "ReadyQueue.h"

//Constructor por defecto
ReadyQueue::ReadyQueue()
{
    algorithm = nullptr;
}

//Constructor que recibe el algoritmo de planificacion
ReadyQueue::ReadyQueue(SchedulingAlgorithm* algorithm)
{
    this->algorithm = algorithm;
}

//Destructor de la clase
ReadyQueue::~ReadyQueue()
{
    //Se libera la memoria del algoritmo asociado a la Ready Queue
    delete algorithm;
}

//Agrega un proceso a la Ready Queue
void ReadyQueue::addProcess(Process* p)
{
    processes.push_back(p);
}

//Obtiene el siguiente proceso segun el algoritmo de planificacion
Process* ReadyQueue::getNext()
{
    Process* selected = algorithm->selectNext(processes);

    if(selected == nullptr)
    {
        return nullptr;
    }

    //Una vez seleccionado el proceso se elimina de la Ready Queue
    for(size_t i = 0; i < processes.size(); i++)
    {
        if(processes.at(i) == selected)
        {
            processes.erase(processes.begin() + i);
            break;
        }
    }

    return selected;
}

//Revisa si la Ready Queue esta vacia
bool ReadyQueue::isEmpty() const
{
    return processes.empty();
}

Process* ReadyQueue::peekNext() const
{
    return algorithm->selectNext(const_cast<std::vector<Process*>&>(processes));
}

//getter para obtener el algoritmo de planificacion
SchedulingAlgorithm* ReadyQueue::getAlgorithm() const
{
    return algorithm;
}