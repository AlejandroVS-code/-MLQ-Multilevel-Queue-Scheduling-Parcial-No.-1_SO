/* Autor: Alejandro Valencia Sandoval
   Correo: alejandro.valencia.sandoval@correounivalle.edu.co

   Version: 1.0
   Descripcion: Programa principal del MLQ. Desde este archivo
   se crean las Ready Queue, se cargan los procesos desde el archivo de
   entrada, se ejecutan y finalmente se generan los resultados
   junto con las metricas promedio.
*/

#include <iostream>
#include <tuple>
#include <fstream>

#include "Process.h"
#include "RRScheduling.h"
#include "PriorityScheduling.h"
#include "ReadyQueue.h"
#include "MLQScheduler.h"
#include "ProcessDetector.h"
#include "MetricsCalculator.h"

int main(int argc, char* argv[])
{
    //Verifica que se hayan recibido los archivos de entrada y salida
    if(argc != 3)
    {
        std::cout<<"Uso correcto: ./simulator <archivo_entrada> <archivo_salida>"
                 <<std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    //Crea las Ready Queue utilizadas por el planificador
    std::vector<ReadyQueue*> readyQueues;

    readyQueues.push_back(new ReadyQueue(new RRScheduling(3)));
    readyQueues.push_back(new ReadyQueue(new RRScheduling(5)));
    readyQueues.push_back(new ReadyQueue(new PriorityScheduling()));

    MLQScheduler scheduler(readyQueues);

    //Carga los procesos desde el archivo de entrada
    ProcessDetector detector;

    std::vector<Process*> processes =
        detector.readInput(inputPath);

    if(processes.empty())
    {
        std::cout<<"No se encontraron procesos validos."<<std::endl;
        return 1;
    }

    std::cout<<"Se cargaron "
             <<processes.size()
             <<" procesos."<<std::endl;

    scheduler.loadProcesses(processes);

    //Ejecuta el planificador 
    scheduler.run();

    std::vector<Process*> results =
        scheduler.getFinishedProcesses();

    //Genera el archivo con los resultados
    detector.writeOutput(outputPath, results);

    MetricsCalculator calculator;

    std::tuple<float, float, float, float> averages =
        calculator.calculateAverages(results);

    std::ofstream outputFile(outputPath, std::ios::app);

    if(outputFile.is_open())
    {
        outputFile<<"# WT="<<std::get<0>(averages)
                  <<"; CT="<<std::get<1>(averages)
                  <<"; RT="<<std::get<2>(averages)
                  <<"; TAT="<<std::get<3>(averages)
                  <<std::endl;

        outputFile.close();
    }

    std::cout<<"Ejecucion terminada."<<std::endl;
    std::cout<<"Resultados guardados en: "
             <<outputPath
             <<std::endl;

    //Libera la memoria de los procesos creados
    for(size_t i = 0; i < results.size(); i++)
    {
        delete results.at(i);
    }

    return 0;
}