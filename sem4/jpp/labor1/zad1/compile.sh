#!/bin/bash

gcc -c -fPIC my_lib.c -o my_lib.o
ar rcs libmy_lib_c.a my_lib.o

gcc -shared -o libmy_lib_c.so my_lib.o
