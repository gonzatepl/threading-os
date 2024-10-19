#include <iostream>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"

enum { NS_PER_SECOND = 1000000000 };

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

void testCargarArchivos(int threads, std::vector<std::string> filepaths){

    struct timespec start_archivos, finish_archivos;

    HashMapConcurrente hashMap{};
    clock_gettime(CLOCK_REALTIME,&start_archivos);

    cargarMultiplesArchivos(hashMap, threads, filepaths);

    clock_gettime(CLOCK_REALTIME,&finish_archivos);
    long seconds = finish_archivos.tv_sec - start_archivos.tv_sec;
    long nanoseconds = finish_archivos.tv_nsec - start_archivos.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    std::cout <<" el tiempo de ejecucion es " << elapsed << std::endl;

    return;

}

void testCalcularMaximo(int threads, HashMapConcurrente &hashMap){

    struct timespec start_maximo, finish_maximo;
    clock_gettime(CLOCK_REALTIME,&start_maximo);

    auto maximo = hashMap.maximoParalelo(threads);   

    clock_gettime(CLOCK_REALTIME,&finish_maximo);
    long seconds = finish_maximo.tv_sec - start_maximo.tv_sec;
    long nanoseconds = finish_maximo.tv_nsec - start_maximo.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    std::cout <<" el tiempo de ejecucion es " << elapsed << std::endl;

    return;

}

int main() {      

    //Correspondientes a la/s hipótesis: H1

    std::cout<<"Cargando archivo de 915.000 palabras con la version singlethread,";
    testCargarArchivos(1,{"../data/GigaData"});
    
    //sleep(2);

    std::cout<<"Dividiendo el archivo en 10 partes iguales y cargandolo con 4 threads,";
    testCargarArchivos(4,{"../data/GigaData10/GigaData_1", "../data/GigaData10/GigaData_2", 
    "../data/GigaData10/GigaData_3", "../data/GigaData10/GigaData_4", "../data/GigaData10/GigaData_5", "../data/GigaData20/GigaData_6", "../data/GigaData20/GigaData_7", 
    "../data/GigaData20/GigaData_8", "../data/GigaData20/GigaData_9", "../data/GigaData20/GigaData_10" });

    //sleep(2);

    std::cout<<"Dividiendo el archivo en 10 partes iguales y cargandolo con 8 threads,";
    testCargarArchivos(8,{"../data/GigaData10/GigaData_1", "../data/GigaData10/GigaData_2", 
    "../data/GigaData10/GigaData_3", "../data/GigaData10/GigaData_4", "../data/GigaData10/GigaData_5", "../data/GigaData20/GigaData_6", "../data/GigaData20/GigaData_7", 
    "../data/GigaData20/GigaData_8", "../data/GigaData20/GigaData_9", "../data/GigaData20/GigaData_10" });
    
    //sleep(2);

    std::cout<<"Dividiendo el archivo en 10 partes iguales y cargandolo con 10 threads,";
    testCargarArchivos(10,{"../data/GigaData10/GigaData_1", "../data/GigaData10/GigaData_2", 
    "../data/GigaData10/GigaData_3", "../data/GigaData10/GigaData_4", "../data/GigaData10/GigaData_5", "../data/GigaData20/GigaData_6", "../data/GigaData20/GigaData_7", 
    "../data/GigaData20/GigaData_8", "../data/GigaData20/GigaData_9", "../data/GigaData20/GigaData_10" });

    //sleep(2);

    std::cout<<"Dividiendo el archivo en 20 partes iguales y cargandolo con 8 threads,";
    testCargarArchivos(8,{"../data/GigaData20/GigaData_1", "../data/GigaData20/GigaData_2", "../data/GigaData20/GigaData_3", 
    "../data/GigaData20/GigaData_4", "../data/GigaData20/GigaData_5", "../data/GigaData20/GigaData_6", "../data/GigaData20/GigaData_7", 
    "../data/GigaData20/GigaData_8", "../data/GigaData20/GigaData_9", "../data/GigaData20/GigaData_10", "../data/GigaData20/GigaData_11", 
    "../data/GigaData20/GigaData_12", "../data/GigaData20/GigaData_13", "../data/GigaData20/GigaData_14", "../data/GigaData20/GigaData_15", 
    "../data/GigaData20/GigaData_16", "../data/GigaData20/GigaData_17", "../data/GigaData20/GigaData_18", "../data/GigaData20/GigaData_19", 
    "../data/GigaData20/GigaData_20"});
   
    //sleep(2);

    std::cout<<"Dividiendo el archivo en 20 partes iguales y cargandolo con 16 threads,";
    testCargarArchivos(16,{"../data/GigaData20/GigaData_1", "../data/GigaData20/GigaData_2", "../data/GigaData20/GigaData_3", 
    "../data/GigaData20/GigaData_4", "../data/GigaData20/GigaData_5", "../data/GigaData20/GigaData_6", "../data/GigaData20/GigaData_7", 
    "../data/GigaData20/GigaData_8", "../data/GigaData20/GigaData_9", "../data/GigaData20/GigaData_10", "../data/GigaData20/GigaData_11", 
    "../data/GigaData20/GigaData_12", "../data/GigaData20/GigaData_13", "../data/GigaData20/GigaData_14", "../data/GigaData20/GigaData_15", 
    "../data/GigaData20/GigaData_16", "../data/GigaData20/GigaData_17", "../data/GigaData20/GigaData_18", "../data/GigaData20/GigaData_19", 
    "../data/GigaData20/GigaData_20"});

    //sleep(2);

        std::cout<<"Dividiendo el archivo en 20 partes iguales y cargandolo con 20 threads,";
    testCargarArchivos(20,{"../data/GigaData20/GigaData_1", "../data/GigaData20/GigaData_2", "../data/GigaData20/GigaData_3", 
    "../data/GigaData20/GigaData_4", "../data/GigaData20/GigaData_5", "../data/GigaData20/GigaData_6", "../data/GigaData20/GigaData_7", 
    "../data/GigaData20/GigaData_8", "../data/GigaData20/GigaData_9", "../data/GigaData20/GigaData_10", "../data/GigaData20/GigaData_11", 
    "../data/GigaData20/GigaData_12", "../data/GigaData20/GigaData_13", "../data/GigaData20/GigaData_14", "../data/GigaData20/GigaData_15", 
    "../data/GigaData20/GigaData_16", "../data/GigaData20/GigaData_17", "../data/GigaData20/GigaData_18", "../data/GigaData20/GigaData_19", 
    "../data/GigaData20/GigaData_20" });

    
        std::cout<<"Dividiendo el archivo en 30 partes iguales y cargandolo con 30 threads,";
    testCargarArchivos(30,{"../data/GigaData30/GigaData_1", "../data/GigaData30/GigaData_2", "../data/GigaData30/GigaData_3", 
    "../data/GigaData30/GigaData_4", "../data/GigaData30/GigaData_5", "../data/GigaData30/GigaData_6", "../data/GigaData30/GigaData_7", 
    "../data/GigaData30/GigaData_8", "../data/GigaData30/GigaData_9", "../data/GigaData30/GigaData_10", "../data/GigaData30/GigaData_11", 
    "../data/GigaData30/GigaData_12", "../data/GigaData30/GigaData_13", "../data/GigaData30/GigaData_14", "../data/GigaData30/GigaData_15", 
    "../data/GigaData30/GigaData_16", "../data/GigaData30/GigaData_17", "../data/GigaData30/GigaData_18", "../data/GigaData30/GigaData_19", 
    "../data/GigaData30/GigaData_20", "../data/GigaData30/GigaData_21", "../data/GigaData30/GigaData_22", "../data/GigaData30/GigaData_23", "../data/GigaData30/GigaData_24", "../data/GigaData30/GigaData_25", 
    "../data/GigaData30/GigaData_26", "../data/GigaData30/GigaData_27", "../data/GigaData30/GigaData_28", "../data/GigaData30/GigaData_29", 
    "../data/GigaData30/GigaData_30" });

   

        std::cout<<"Dividiendo el archivo en 50 partes iguales y cargandolo con 50 threads,";
    testCargarArchivos(50,{"../data/GigaData50/GigaData_01", "../data/GigaData50/GigaData_02", "../data/GigaData50/GigaData_03", 
    "../data/GigaData50/GigaData_04", "../data/GigaData50/GigaData_05", "../data/GigaData50/GigaData_06", "../data/GigaData50/GigaData_07", 
    "../data/GigaData50/GigaData_08", "../data/GigaData50/GigaData_09", "../data/GigaData50/GigaData_10", "../data/GigaData50/GigaData_11", 
    "../data/GigaData50/GigaData_12", "../data/GigaData50/GigaData_13", "../data/GigaData50/GigaData_14", "../data/GigaData50/GigaData_15", 
    "../data/GigaData50/GigaData_16", "../data/GigaData50/GigaData_17", "../data/GigaData50/GigaData_18", "../data/GigaData50/GigaData_19", 
    "../data/GigaData50/GigaData_20", "../data/GigaData50/GigaData_21", "../data/GigaData50/GigaData_22", "../data/GigaData50/GigaData_23", "../data/GigaData50/GigaData_24", "../data/GigaData50/GigaData_25", 
    "../data/GigaData50/GigaData_26", "../data/GigaData50/GigaData_27", "../data/GigaData50/GigaData_28", "../data/GigaData50/GigaData_29", 
    "../data/GigaData50/GigaData_30", "../data/GigaData50/GigaData_31", "../data/GigaData50/GigaData_32", "../data/GigaData50/GigaData_33", "../data/GigaData50/GigaData_34", "../data/GigaData50/GigaData_35", 
    "../data/GigaData50/GigaData_36", "../data/GigaData50/GigaData_37", "../data/GigaData50/GigaData_38", "../data/GigaData50/GigaData_39", "../data/GigaData50/GigaData_40", "../data/GigaData50/GigaData_41", 
    "../data/GigaData50/GigaData_42", "../data/GigaData50/GigaData_43", "../data/GigaData50/GigaData_44", "../data/GigaData50/GigaData_45", 
    "../data/GigaData50/GigaData_46", "../data/GigaData50/GigaData_47", "../data/GigaData50/GigaData_48", "../data/GigaData50/GigaData_49", "../data/GigaData50/GigaData_50" });

    
    //Correspondientes a la/s hipótesis: H2, H3

    //sleep(2);

    std::cout<<"Cargando 5 archivos de 50.000 palabras con la version singlethread,";
    testCargarArchivos(1,{"../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData"});

    //sleep(2);

    std::cout<<"Cargando 5 archivos de 50.000 palabras con 5 threads,";
    testCargarArchivos(5,{"../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData"});

    //sleep(2);

    std::cout<<"Cargando 5 archivos de 915.000 palabras con 1 thread,";
    testCargarArchivos(1,{"../data/GigaData", "../data/GigaData", "../data/GigaData", 
    "../data/GigaData", "../data/GigaData"});

    //sleep(2);

    std::cout<<"Cargando 5 archivos de 915.000 palabras con 5 threads,";
    testCargarArchivos(5,{"../data/GigaData", "../data/GigaData", "../data/GigaData", 
    "../data/GigaData", "../data/GigaData"});

    //sleep(2);

    std::cout<<"Cargando 20 archivos de 50000 palabras con la version singlethread,";
    testCargarArchivos(1,{"../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData"});

    //sleep(2);

    std::cout<<"Cargando 20 archivos de 50000 palabras con 8 threads,";
    testCargarArchivos(8,{"../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData"});

    //sleep(2);

    std::cout<<"Cargando 20 archivos de 50000 palabras con 16 threads,";
    testCargarArchivos(16,{"../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData"});

    //sleep(2);

    std::cout<<"Cargando 20 archivos de 50000 palabras con 20 threads,";
    testCargarArchivos(20,{"../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", "../data/bigData", 
    "../data/bigData", "../data/bigData"});

    //sleep(2);


    std::cout<<"Cargando 5 archivos de 390625 palabras distintas con la version singlethread,";
    testCargarArchivos(1,{"../data/GigaVariatedData", "../data/GigaVariatedData", "../data/GigaVariatedData", 
    "../data/GigaVariatedData", "../data/GigaVariatedData"});
    
    //sleep(2);

    std::cout<<"Cargando 5 archivos de 390625 palabras distintas con 5 threads,";

    testCargarArchivos(5,{"../data/GigaVariatedData", "../data/GigaVariatedData", "../data/GigaVariatedData", 
    "../data/GigaVariatedData", "../data/GigaVariatedData"});
    
    //sleep(2);            


    HashMapConcurrente hashMap{};

    cargarMultiplesArchivos(hashMap, 10, {"../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_1", "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_2", 
    "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_3", "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_4", "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_5", 
    "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_6", "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_7", "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_8", 
    "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_9", "../data/RandomizedGigaVariatedData10/RandomizedGigaVariatedData_10" });

    //sleep(2);

    //Correspondientes a la/s hipótesis: H4

    std::cout<<"Cargando 3 archivos de 50000 palabras con la version singlethread,";
    testCargarArchivos(1,{"../data/bigData", "../data/bigData", "../data/bigData"});

    //sleep(2);

    std::cout<<"Cargando 3 archivos de 50000 palabras con 2 threads,";
    testCargarArchivos(2,{"../data/bigData", "../data/bigData", "../data/bigData"});

    //sleep(2);

    std::cout<<"Cargando 3 archivos de 50000 palabras con 3 threads,";
    testCargarArchivos(3,{"../data/bigData", "../data/bigData", "../data/bigData"});

    //sleep(2);

    //Correspondientes a la/s hipótesis: H5

    std::cout <<"Buscando maximo entre 390625 claves randomizadas con la version singlethread, ";
    testCalcularMaximo(1, hashMap);

    //sleep(2);

    std::cout <<"Buscando maximo entre 390625 claves randomizadas con 4 threads, ";
    testCalcularMaximo(4, hashMap);

    //sleep(2);

    std::cout <<"Buscando maximo entre 390625 claves randomizadas con 8 threads, ";
    testCalcularMaximo(8, hashMap);

    //sleep(2);

    std::cout <<"Buscando maximo entre 390625 claves randomizadas con 16 threads, ";
    testCalcularMaximo(16, hashMap);

    //sleep(2);

    std::cout <<"Buscando maximo entre 390625 claves randomizadas con 20 threads, ";
    testCalcularMaximo(20, hashMap);

    //sleep(2);

    std::cout <<"Buscando maximo entre 390625 claves randomizadas con 26 threads, ";
    testCalcularMaximo(26, hashMap);

    //sleep(2);


    HashMapConcurrente hashMap1{};

    cargarMultiplesArchivos(hashMap1, 1, {"../data/bigData" });

    //sleep(2);

    //Correspondientes a la/s hipótesis: H6
   
    std::cout <<"Buscando maximo entre 1.000 claves con la version singlethread, ";
    testCalcularMaximo(1, hashMap1);

    //sleep(2);

    std::cout <<"Buscando maximo entre 1.000 claves con 2 threads, ";
    testCalcularMaximo(2, hashMap1);

    //sleep(2);

    std::cout <<"Buscando maximo entre 1.000 claves con 5 threads, ";
    testCalcularMaximo(5, hashMap1);
     
    //sleep(2);

    std::cout <<"Buscando maximo entre 1.000 claves con 10 threads, ";
    testCalcularMaximo(10, hashMap1);
     
    //sleep(2);

    std::cout <<"Buscando maximo entre 1.000 claves con 26 threads, ";
    testCalcularMaximo(26, hashMap1);


    

    return 0;
}

