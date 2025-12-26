#!/bin/bash

set -e

mkdir -p results

echo "Compiling..."
g++ -std=c++11 -O3 -march=native -ffast-math \
    -funroll-loops simulation.cpp -o simulation

echo "Running simulation..."
./simulation
rm -f simulation

if [ ! -d ".venv" ]; then
    echo -e "\nCreating virtual environment..."
    python3 -m venv .venv
    .venv/bin/pip install --upgrade pip
    .venv/bin/pip install -r requirements.txt
fi

echo -e "\nGenerating plots..."
.venv/bin/python plot.py