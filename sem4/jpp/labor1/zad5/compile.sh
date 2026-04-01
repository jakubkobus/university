#!/bin/bash

RUST_DIR="../zad3/target/release"

gnatmake main.adb -o main_static -largs ../zad1/libmy_lib_c.a ../zad2/my_lib.o $RUST_DIR/libmy_lib_rust.a -lpthread -lm -ldl

gnatmake main.adb -o main_dynamic -largs -L../zad1/ -L../zad2/ -L$RUST_DIR/ -lmy_lib_c -lmy_lib_ada -lmy_lib_rust -lpthread -lm -ldl
