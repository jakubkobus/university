CC = g++
C_FLAGS = -Wall -Wextra -fopenmp -O3

PYTHON = .venv/bin/python
JUPYTER = .venv/bin/jupyter
PIP = .venv/bin/pip

.PHONY: compile setup run test plot report clean

compile:
	mkdir -p bin
	${CC} ${C_FLAGS} main.cpp -o bin/main
	${CC} ${C_FLAGS} test.cpp -o bin/test

setup:
	python3 -m venv .venv
	${PIP} install --upgrade pip
	${PIP} install -r requirements.txt

run:
	./bin/main

test:
	./bin/test

plot:
	${PYTHON} plot.py

report:
	${JUPYTER} nbconvert --execute --to html analysis/analysis.ipynb
	mv analysis/analysis.html analysis/sprawozdanie.html

clean:
	rm -rf bin/
