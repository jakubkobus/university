#!/bin/bash

RUST_DIR="../zad3/target/release"

echo -e "\n--- STATIC ---\n"
./main_static

echo -e "\n--- DYNAMIC ---\n"
LD_LIBRARY_PATH=../zad1/:../zad2/:$RUST_DIR ./main_dynamic
