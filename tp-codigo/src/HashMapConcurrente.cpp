#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <thread>
//#include <pthread.h>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned bucket = hashIndex(clave);
    bool found = false;
    hashMutex[bucket].lock();

    //Inicializamos un iterador y buscamos el valor en la lista.     
    for(auto it = tabla[bucket]->crearIt();
        it.haySiguiente();
        it.avanzar()
        ){
            auto &elem = it.siguiente();
            if(elem.first == clave){
                elem.second ++;
                found = true;
                break;
            }
    }

    //Si el valor no se encuentra, creamos un nuevo nodo con valor (clave,1)
    if(!found){
        hashMapPair *elem = new hashMapPair();
        elem->first = clave;
        elem->second = 1;
        tabla[bucket]->insertar(*elem); 
    }

    hashMutex[bucket].unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    // Ejercicio 2
    std:: vector <std::string> result={};   
    for (int i= 0; i < HashMapConcurrente::cantLetras; i++){    
        for(auto it = tabla[i]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ){
            auto &elem = it.siguiente();
            result.push_back(elem.first);
        }
    }
    return result;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Ejercicio 2
    for(int i = 0; i < HashMapConcurrente::cantLetras; i++){
            
        for(auto it = tabla[i]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ){  
            auto &elem = it.siguiente();
            if(clave == elem.first){
                return elem.second;
            }
        }

       
    }
    return 0;
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        
        //Agregados Ej3
        hashMutex[index].lock();
        
        for (
            auto it = tabla[index]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ) {
            if (it.siguiente().second > max->second) {
                max->first = it.siguiente().first;
                max->second = it.siguiente().second;
            }
        }
    }

    //Agregados Ej3
    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        hashMutex[index].unlock();
    }

    return *max;
}

void HashMapConcurrente::auxMaximoParalelo(unsigned int &fila, std::mutex &fila_mutex, std::mutex &max_mutex, hashMapPair *max){
    
    while(fila < HashMapConcurrente::cantLetras){        
        hashMapPair *tmp1 = new hashMapPair();
        tmp1->second = max->second;

        fila_mutex.lock();

        if (fila < HashMapConcurrente::cantLetras)
        {
            int tmp2 = fila;
            fila++;
            fila_mutex.unlock();
            hashMutex[tmp2].lock();
            for (
                auto it = tabla[tmp2]->crearIt();
                it.haySiguiente();
                it.avanzar()
            ) {
                auto &elem = it.siguiente();
                if (elem.second > tmp1->second) {
                    tmp1->second = elem.second;
                    tmp1->first = elem.first;
                }
            }

            max_mutex.lock();

            if(tmp1->second > max->second){
                max->first = tmp1->first;
                max->second = tmp1->second;
            }
            
            max_mutex.unlock();
        }
        else {

            fila_mutex.unlock();
            return;
        }
    }

    return;
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads) {
    // Ejercicio 3
    if (cantThreads == 1){
        return maximo();    
    }

    std::vector<std::thread> threads(cantThreads);
    hashMapPair *max = new hashMapPair();
    max->second = 0;
    unsigned int fila = 0;
    std::mutex fila_mutex;
    std::mutex max_mutex;

    int contador = 0;
    for (auto &t : threads)
    {
        if(fila >= HashMapConcurrente::cantLetras) break;

        contador++;
        t = std::thread(&HashMapConcurrente::auxMaximoParalelo, this, std::ref(fila), std::ref(fila_mutex), std::ref(max_mutex), max);
    }

    for(int i = 0; i<contador; i++){
        threads[i].join(); 
    }

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        hashMutex[index].unlock();
    }

    return *max;
}

#endif
