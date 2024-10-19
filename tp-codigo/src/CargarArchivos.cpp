#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <thread>

#include "CargarArchivos.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Ejercicio 4
        hashMap.incrementar(palabraActual); //Agregado
        cant++; //Agregado
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}


void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    //Ejercicio 4
    std::vector<std::thread> threads(cantThreads);
    long unsigned int archivoACargar = 0;
    std::mutex cargar_Archivo;
    int contador = 0;

    for (auto &t : threads)
    {
        if(archivoACargar >= filePaths.size()) break;

        contador++;

        t = std::thread([&hashMap, &filePaths, &cargar_Archivo, &archivoACargar] () {
            while(archivoACargar < filePaths.size()){
                cargar_Archivo.lock();
                if (archivoACargar < filePaths.size())
                {
                    int temp = archivoACargar;
                    archivoACargar++;
                    cargar_Archivo.unlock();
                    cargarArchivo(hashMap, filePaths[temp]);
                }
                else {

                    cargar_Archivo.unlock();
                    return;
                }
            }
            return;
        });
    }

    for(int i = 0; i<contador; i++){
        threads[i].join();
    }

    return;
}

#endif
