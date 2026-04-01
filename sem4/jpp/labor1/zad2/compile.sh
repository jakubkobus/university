#!/bin/bash

gcc -c -fPIC my_lib.adb

gnatbind -n my_lib.ali
gcc -c -fPIC b~my_lib.adb

ar rcs libmy_lib_ada.a my_lib.o b~my_lib.o

gcc -shared -o libmy_lib_ada.so my_lib.o b~my_lib.o -lgnat
