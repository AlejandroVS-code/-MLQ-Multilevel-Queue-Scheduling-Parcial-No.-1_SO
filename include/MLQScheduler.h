/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Version: 1.0
   Descripcion: Este archivo define la clase MLQScheduler, la cual representa
   el planificador principal. La clase se encarga de administrar
   las Ready Queue, controlar la ejecucion de los procesos, atender la llegada
   de nuevos procesos y realizar las expropiaciones necesarias segun el
   algoritmo de planificacion utilizado en cada cola.
*/

#ifndef MLQ_SCHEDULER_H
#define MLQ_SCHEDULER_H

#include <vector>
#include "ReadyQueue.h"
#include "Process.h"

class MLQScheduler
{
private:


    std::vector<ReadyQueue*> queues;
    float currentTime;
    Process* runningProcess;
    int runningQueueIndex;

    std::vector<Process*> pendingProcesses;
    std::vector<Process*> finishedProcesses;

    bool allQueuesEmpty() const;
    int findHighestPriorityReadyQueue() const;

    void handleArrivals();
    void dispatch(int queueIndex);
    void requeueRunning();

    void checkInterQueuePreemption();
    void checkIntraQueuePreemption();

    void executeTick();

public:

    
    MLQScheduler();

    //Constructor que recibe las Ready Queue
    MLQScheduler(std::vector<ReadyQueue*> queues);

    
    ~MLQScheduler();

    //Carga los procesos que seran ejecutados
    void loadProcesses(std::vector<Process*> processes);

    //Inicia el planificador
    void run();

     //Obtiene los procesos finalizados
    std::vector<Process*> getFinishedProcesses() const;
};

#endif // MLQ_SCHEDULER_H