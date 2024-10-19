#ifndef HMC_HPP
#define HMC_HPP

#include <atomic>
#include <string>
#include <vector>
#include <mutex>
//#include <array>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static const unsigned int cantLetras = 26;

    HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    hashMapPair maximo();
    hashMapPair maximoParalelo(unsigned int cantThreads);

    //Agregado por nosotros
    void auxMaximoParalelo(
      unsigned int &fila, 
      std::mutex &fila_mutex, 
      std::mutex &max_mutex, 
      hashMapPair *max
    );

 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];
    
    static unsigned int hashIndex(std::string clave);

    //Agregado 
    std::mutex  hashMutex[HashMapConcurrente::cantLetras];
};

#endif  /* HMC_HPP */
