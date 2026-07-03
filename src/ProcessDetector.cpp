/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co

   Versión: 1.0
   Descripción: Implementación de la clase ProcessDetector, la cual se
   encarga de leer la información de los procesos desde un archivo de
   entrada y generar el archivo de salida con los resultados obtenidos
   durante la ejecucion.
*/

#include "ProcessDetector.h"
#include <fstream>
#include <sstream>
#include <iostream>


ProcessDetector::ProcessDetector()
{

}

ProcessDetector::~ProcessDetector()
{

}

//Lee el archivo de entrada y crea los procesos
std::vector<Process*> ProcessDetector::readInput(std::string path)
{
    std::vector<Process*> processes;

    std::ifstream archivo(path);

    if(!archivo.is_open())
    {
        std::cout<<"No se pudo abrir el archivo: "<<path<<std::endl;
        return processes;
    }

    std::string linea;

    while(std::getline(archivo, linea))
    {
        
        if(linea.empty() || linea.at(0) == '#')
        {
            continue;
        }

        std::stringstream ss(linea);
        std::string campo;
        std::vector<std::string> campos;

      
        while(std::getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }


        if(campos.size() != 5)
        {
            std::cout<<"Linea con formato invalido: "<<linea<<std::endl;
            continue;
        }

        std::string processId = campos.at(0);
        float burstTime = std::stof(campos.at(1));
        float arrivalTime = std::stof(campos.at(2));
        int queue = std::stoi(campos.at(3));
        int priority = std::stoi(campos.at(4));

       
        if(Process::isValidData(burstTime, arrivalTime))
        {
            processes.push_back(
                new Process(processId,
                            burstTime,
                            arrivalTime,
                            queue,
                            priority));
        }
    }

    archivo.close();

    return processes;
}

//Genera el archivo con los resultados
void ProcessDetector::writeOutput(std::string path,
                                  std::vector<Process*> results)
{
    std::ofstream archivo(path);

    if(!archivo.is_open())
    {
        std::cout<<"No se pudo crear el archivo: "<<path<<std::endl;
        return;
    }

    archivo<<"# etiqueta;BT;AT;Q;Pr;WT;CT;RT;TAT"<<std::endl;

    for(size_t i = 0; i < results.size(); i++)
    {
        Process* p = results.at(i);

        archivo<<p->getProcessId()<<";"
               <<p->getBurstTime()<<";"
               <<p->getArrivalTime()<<";"
               <<p->getQueue()<<";"
               <<p->getPriority()<<";"
               <<p->getWaitingTime()<<";"
               <<p->getCompletionTime()<<";"
               <<p->getResponseTime()<<";"
               <<p->getTurnaroundTime()
               <<std::endl;
    }

    archivo.close();
}