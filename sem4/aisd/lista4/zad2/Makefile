CXX = g++
CXX_FLAGS = -Wall -Wextra -fopenmp -O3

TARGET = main
TARGET_DIR = bin
RESULTS_DIR = results
PLOTS_DIR = plots

.PHONY: compile setup run plot clean

compile:
	mkdir -p ${TARGET_DIR} ${RESULTS_DIR} ${PLOTS_DIR}
	${CXX} ${CXX_FLAGS} ${TARGET}.cpp -o ${TARGET_DIR}/${TARGET}

setup:
	python -m venv .venv
	.venv/bin/python -m pip install --upgrade pip
	.venv/bin/pip install pandas matplotlib

run:
	ulimit -s unlimited
	./${TARGET_DIR}/${TARGET}

plot:
	.venv/bin/python plot.py

clean:
	rm -rf ${TARGET_DIR}
