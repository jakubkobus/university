CXX = g++
CXX_FLAGS = -Wall -Wextra -O2

TARGET_DIR = bin
TARGET = main

.PHONY: compile run clean

compile:
	mkdir -p ${TARGET_DIR}
	${CXX} ${CXX_FLAGS} ${TARGET}.cpp -o ${TARGET_DIR}/${TARGET}

run:
	./${TARGET_DIR}/${TARGET}

clean:
	rm -rf ${TARGET_DIR}
