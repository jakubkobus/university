#!/bin/bash

TASK1_PARAMS=(10000  1000000  10000  50  "./results/results1.csv")
TASK2_PARAMS=(100    10000    100    50  "./results/results2.csv")
TASK3_PARAMS=(100    10000    100    50  "./results/results3.csv")


set -e
mkdir -p results
mkdir -p results/plots


echo "Compiling..."

g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops task1.cpp -o task1

g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops task2.cpp -o task2

g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops task3.cpp -o task3


echo "Running simulations..."

echo -e "\n--- TASK 1 ---"
./task1 "${TASK1_PARAMS[@]}"

echo -e "\n--- TASK 2 ---"
./task2 "${TASK2_PARAMS[@]}"

echo -e "\n--- TASK 3 ---"
./task3 "${TASK3_PARAMS[@]}"

rm -f task1 task2 task3


if [ ! -d ".venv" ]; then
    echo -e "\nCreating virtual environment..."
    python3 -m venv .venv
    .venv/bin/pip install --upgrade pip
    .venv/bin/pip install -r requirements.txt
fi


echo -e "\nGenerating plots..."
.venv/bin/python plot.py