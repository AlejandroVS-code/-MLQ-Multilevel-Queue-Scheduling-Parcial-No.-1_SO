/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co

   Version: 1.0
   Descripcion: Implementacion de la clase MLQScheduler, la cual se
   encarga de controlar el algoritmo MLQ. Desde esta
   clase se administran las Ready Queue, la llegada de nuevos procesos,
   las expropiaciones y la ejecucion de los procesos hasta que todos
   finalicen su ejecucion. Basicamente sta es la clase que organiza y gestiona en gran parte todo.
*/

#include "MLQScheduler.h"
#include "RRScheduling.h"
#include "PriorityScheduling.h"

MLQScheduler::MLQScheduler()
{
    currentTime = 0;
    runningProcess = nullptr;
    runningQueueIndex = -1;
}

//Constructor que recibe las Ready Queue
MLQScheduler::MLQScheduler(std::vector<ReadyQueue*> queues)
{
    this->queues = queues;

    currentTime = 0;
    runningProcess = nullptr;
    runningQueueIndex = -1;
}

//Destructor de la clase
MLQScheduler::~MLQScheduler()
{
    //Libera memoria de las Ready Queue utilizadas.
    for(size_t i = 0; i < queues.size(); i++)
    {
        delete queues.at(i);
    }
}

//Carga los procesos que seran ejecutados
void MLQScheduler::loadProcesses(std::vector<Process*> processes)
{
    pendingProcesses = processes;
}

//Revisa si todas las Ready Queue se encuentran vacias
bool MLQScheduler::allQueuesEmpty() const
{
    for(size_t i = 0; i < queues.size(); i++)
    {
        if(!queues.at(i)->isEmpty())
        {
            return false;
        }
    }

    return true;
}

//Busca la Ready Queue de mayor prioridad que tenga procesos disponibles
int MLQScheduler::findHighestPriorityReadyQueue() const
{
    //Las Ready Queue se almacenan de mayor a menor prioridad
    for(size_t i = 0; i < queues.size(); i++)
    {
        if(!queues.at(i)->isEmpty())
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}
//Agrega a las Ready Queue los procesos cuyo tiempo de llegada ya se cumplio
void MLQScheduler::handleArrivals()
{
    for(size_t i = 0; i < pendingProcesses.size(); )
    {
        Process* p = pendingProcesses.at(i);

        if(p->getArrivalTime() <= currentTime)
        {
            
            int queueIndex = p->getQueue() - 1;

            queues.at(queueIndex)->addProcess(p);

           
            pendingProcesses.erase(pendingProcesses.begin() + i);
        }
        else
        {
            i++;
        }
    }
}
//Asigna a CPU el siguiente proceso de la Ready Queue seleccionada
void MLQScheduler::dispatch(int queueIndex)
{
    runningProcess = queues.at(queueIndex)->getNext();
    runningQueueIndex = queueIndex;

    if(runningProcess != nullptr)
    {
        //Cada vez que el proceso entra a CPU inicia un nuevo Quantum
        runningProcess->resetQuantum();
    }
}

//Devuelve el proceso actual a su Ready Queue
void MLQScheduler::requeueRunning()
{
    if(runningProcess != nullptr)
    {
        queues.at(runningQueueIndex)->addProcess(runningProcess);

        runningProcess = nullptr;
    }
}
//Revisa si una Ready Queue de mayor prioridad debe tomar la CPU
void MLQScheduler::checkInterQueuePreemption()
{
    if(runningProcess == nullptr)
    {
        return;
    }

    int bestReady = findHighestPriorityReadyQueue();

    if(bestReady != -1 && bestReady < runningQueueIndex)
    {
        requeueRunning();
        dispatch(bestReady);
    }
}

//Revisa si dentro de la misma Ready Queue debe ocurrir una expropiacion
void MLQScheduler::checkIntraQueuePreemption()
{
    if(runningProcess == nullptr)
    {
        return;
    }

    SchedulingAlgorithm* algorithm = queues.at(runningQueueIndex)->getAlgorithm();

    if(algorithm->needsTimeBasedPreemption())
    {
      
        RRScheduling* rr = dynamic_cast<RRScheduling*>(algorithm);

        if(rr != nullptr &&
           runningProcess->getTimeInCurrentQuantum() >= rr->getQuantum())
        {
            int queueIndex = runningQueueIndex;

            requeueRunning();
            dispatch(queueIndex);
        }
    }
    else
    {
        
        Process* nextProcess = queues.at(runningQueueIndex)->peekNext();

        if(nextProcess != nullptr &&
           algorithm->shouldPreempt(runningProcess, nextProcess))
        {
            int queueIndex = runningQueueIndex;

            requeueRunning();
            dispatch(queueIndex);
        }
    }
}
//Ejecuta una unidad de tiempo
void MLQScheduler::executeTick()
{
    if(runningProcess == nullptr)
    {
        return;
    }

    runningProcess->execute(1.0f, currentTime);

    if(runningProcess->isFinished())
    {
        
        runningProcess->finalizeMetrics(currentTime + 1);

        finishedProcesses.push_back(runningProcess);
        runningProcess = nullptr;
    }
}

//Inicia la ejecucion de todos los procesos
void MLQScheduler::run()
{
    currentTime = 0;

    while(!(pendingProcesses.empty() &&
            allQueuesEmpty() &&
            runningProcess == nullptr))
    {
        
        handleArrivals();

        if(runningProcess == nullptr)
        {
            int nextQueue = findHighestPriorityReadyQueue();

            if(nextQueue != -1)
            {
                dispatch(nextQueue);
            }
        }
        else
        {
            
            checkInterQueuePreemption();
            checkIntraQueuePreemption();
        }

        executeTick();

        currentTime++;
    }
}

//Obtiene los procesos finalizados
std::vector<Process*> MLQScheduler::getFinishedProcesses() const
{
    return finishedProcesses;
}