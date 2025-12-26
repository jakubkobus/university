#!/bin/bash

mkdir -p ./bin
mkdir -p ./obj

gcc zad1.c -o ./bin/zad1 -pthread

gcc zad2.c -o ./bin/zad2 -lrt -pthread

gcc zad3.c -o ./bin/zad3

nasm -f elf32 -g zad4.asm -o ./obj/zad4.o
ld -m elf_i386 ./obj/zad4.o -o ./bin/zad4

nasm -f elf32 zad5.asm -o ./obj/zad5.o
ld -m elf_i386 ./obj/zad5.o -o ./bin/zad5

nasm -f elf32 zad6.asm -o ./obj/zad6.o
ld -m elf_i386 ./obj/zad6.o -o ./bin/zad6

