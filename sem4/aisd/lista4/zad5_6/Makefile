CXX = g++
CXX_FLAGS = -Wall -Wextra -pedantic -O3 -fopenmp

SRC = main.cpp
BIN = main
BIN_DIR = bin

RESULTS_DIR = results
PLOTS_DIR = plots

.PHONY: compile setup run plot clean

compile:
	mkdir -p ${BIN_DIR} ${RESULTS_DIR} ${PLOTS_DIR}
	${CXX} ${CXX_FLAGS} ${SRC} -o ${BIN_DIR}/${BIN}

setup:
	python -m venv .venv
	.venv/bin/python -m pip install --upgrade pip
	.venv/bin/pip install pandas matplotlib

run:
	./${BIN_DIR}/${BIN}

plot:
	.venv/bin/python plot.py

clean:
	rm -rf ${BIN_DIR}
