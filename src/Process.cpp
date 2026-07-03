/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Versión: 1.0
   Descripción: Implementación de la clase Process, la cual representa un
   proceso dentro del planificador(Scheduler) de CPU. Este archivo define
   los métodos necesarios para crear un proceso, validar la información
   ingresada, ejecutar el proceso, calcular las metricas al finalizar el proceso
   y consultar la información almacenada mediante sus respectivos
   métodos get. 
   Esta clase es la base para que los algoritmos de
   planificación administren la ejecución de los procesos y calculen sus
   métricas finales.
*/


#include "Process.h"

// Constructor de la clase Process. Inicializa los atributos principales
// del proceso y las métricas las inicializa en 0.
Process::Process(std::string processId, float burstTime, float arrivalTime,
                 int queue, int priority)
{
    this->processId = processId;
    this->burstTime = burstTime;
    this->arrivalTime = arrivalTime;
    this->queue = queue;
    this->priority = priority;

    remainingTime = burstTime;
    firstExecuted = false;
    timeInCurrentQuantum = 0;

    waitingTime = 0;
    completionTime = 0;
    responseTime = 0;
    turnaroundTime = 0;
}

// Revisa que el tiempo de ráfaga y el tiempo de llegada sean válidos
//verificando que los valores sean positivos
bool Process::isValidData(float burstTime, float arrivalTime)
{
    if(burstTime > 0 && arrivalTime >= 0)
    {
        return true;
    }
    std::cout << "Error: El proceso fue ignorado porque posee datos invalidos."
              << std::endl;
    std::cout << "Burst Time = " << burstTime
              << ", Arrival Time = " << arrivalTime << std::endl;
    return false;
}

// Ejecuta el proceso durante un intervalo de tiempo determinado, asi mismo 
// guarda cuando entro a cpu por primera vez
void Process::execute(float timeSlice, float currentTime)
{
    if(firstExecuted == false)
    {
        responseTime = currentTime;
        firstExecuted = true;
    }

    remainingTime = remainingTime - timeSlice;

    if(remainingTime < 0)
    {
        remainingTime = 0;
    }

    timeInCurrentQuantum = timeInCurrentQuantum + timeSlice;
}

// Verifica si el proceso terminó su ejecución en cpu.
bool Process::isFinished() const
{
    if(remainingTime <= 0) { return true;}
    return false;
}

// Reinicia el valor del quantum, devolviendolo a su valor original
void Process::resetQuantum()
{
    timeInCurrentQuantum = 0;
}

// Calcula las métricas cuando el proceso ya termino de ser ejecutado.
void Process::finalizeMetrics(float finishTime)
{
    completionTime = finishTime;
    turnaroundTime = completionTime - arrivalTime;
    waitingTime = turnaroundTime - burstTime;
}

// Métodos para obtener diversa informacion del proceso

std::string Process::getProcessId() const{return processId;}

float Process::getBurstTime() const{return burstTime;}

float Process::getArrivalTime() const{return arrivalTime;}

int Process::getQueue() const{return queue;}

int Process::getPriority() const{return priority;}

float Process::getRemainingTime() const{return remainingTime;}

bool Process::hasFirstExecuted() const{return firstExecuted;}

float Process::getTimeInCurrentQuantum() const{return timeInCurrentQuantum;}

float Process::getWaitingTime() const{return waitingTime;}

float Process::getCompletionTime() const{return completionTime;}

float Process::getResponseTime() const{return responseTime;}

float Process::getTurnaroundTime() const {return turnaroundTime;}