#!/bin/bash

RUST_DIR="../zad3/target/release"

gcc -std=c99 main.c -o main_static ../zad1/libmy_lib_c.a ../zad2/libmy_lib_ada.a $RUST_DIR/libmy_lib_rust.a -lgnat -lpthread -lm -ldl

gcc -std=c99 main.c -o main_dynamic -L../zad1/ -L../zad2/ -L$RUST_DIR/ -lmy_lib_c -lmy_lib_ada -lmy_lib_rust -lgnat -lpthread -lm -ldl
