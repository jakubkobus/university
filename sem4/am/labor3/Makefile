CC = g++
C_FLAGS = -Wall -Wextra -fopenmp -O3 -std=c++20
PY = .venv/bin/python

.PHONY: compile test analyze run plot clean

compile:
	mkdir -p bin results/txt results/plots
	$(CC) $(C_FLAGS) main.cpp -o bin/main
	$(CC) $(C_FLAGS) test.cpp -o bin/test

test:
	./bin/test data/wi29.tsp data/dj38.tsp data/qa194.tsp data/uy734.tsp data/zi929.tsp

analyze:
	.venv/bin/jupyter nbconvert --execute --to html analysis/analysis.ipynb

run:
	./bin/main

plot:
	$(PY) plot.py

clean:
	rm -rf bin/
