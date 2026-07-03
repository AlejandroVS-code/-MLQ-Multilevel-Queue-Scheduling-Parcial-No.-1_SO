/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co
   Version: 1.0
   Descripcion: Este archivo define la clase Process, la cual representa la
   información de un proceso dentro de la CPU.
   Esta clase almacena los datos principales y mas comunes de un proceso, como su
   ID(ProcessId), BR(Burstime), AT(Arrivaltime), Q(Queue) y Pr(Priority).
   Además, las clase es la encargada brindar la información necesaria para que los processos 
   se puedan ejecutar en los algoritmos de planificación, 
   permitiendo actualizar el tiempo restante que necesita el proceso en cpu,
   calcular las métricas como WT(waitingTime), TAT(Turnedarountime)  
   RT(ResponseTime) CT(completionTime) y consultar la información
   del proceso mediante sus respectivos métodos.
*/

#ifndef PROCESS_H
#define PROCESS_H

#include <string>


class Process {
private:
    // Informacion principal de proceso
    std::string processId;
    float burstTime;
    float arrivalTime;
    int queue;
    int priority;

    // Variables necesarias para determinar informacion de tiempo restante
    //cuando se ejecuto por primera vez y cuanto tiempo del quantum ha usado
    float remainingTime;
    bool firstExecuted;
    float timeInCurrentQuantum;

    // Métricas del proceso
    float waitingTime;
    float completionTime;
    float responseTime;
    float turnaroundTime;

public:
    // Constructor de la clase Process, este es el encargado de crear un proceso
    Process(std::string processId, float burstTime, float arrivalTime, 
        int queue, int priority);

    // Verifica que los datos ingresados para el proceso sean válidos
    static bool isValidData(float burstTime, float arrivalTime);

    // Ejecuta el proceso durante un intervalo de tiempo
    void execute(float timeSlice, float currentTime);

    // Verifica si el proceso terminó su ejecución
    bool isFinished() const;

    // Reinicia el tiempo del quantum
    void resetQuantum();

    // Calcula las métricas cuando el proceso termina
    void finalizeMetrics(float finishTime);

    // Métodos para consultar la información del proceso
    std::string getProcessId() const;
    float getBurstTime() const;
    float getArrivalTime() const;
    int getQueue() const;
    int getPriority() const;
    float getRemainingTime() const;
    bool hasFirstExecuted() const;
    float getTimeInCurrentQuantum() const;
    float getWaitingTime() const;
    float getCompletionTime() const;
    float getResponseTime() const;
    float getTurnaroundTime() const;
};

#endif // PROCESS_H