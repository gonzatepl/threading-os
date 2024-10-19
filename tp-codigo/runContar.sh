#!/bin/bash
for i in $(seq "$1")
do
    for j in $(seq "$2")
        do
            echo "Contar Palabras con "$i " Threads para maximo y " $j "para cargar archivos"
            ./build/ContarPalabras ${j} ${i} data/corpus data/corpus data/corpus 
        done
done
