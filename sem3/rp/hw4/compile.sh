#!/bin/bash

mkdir -p bin
mkdir -p results

g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops task1.cpp -o bin/task1

g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops task2.cpp -o bin/task2
    
g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops task3.cpp -o bin/task3

g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops task4.cpp -o bin/task4