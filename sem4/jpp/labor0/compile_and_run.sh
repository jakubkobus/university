#!/bin/bash

echo "[C]"
gcc hello.c -o hello_c
./hello_c
rm -f hello_c
echo ""

echo "[C++]"
g++ hello.cpp -o hello_cpp
./hello_cpp
rm -f hello_cpp
echo ""

echo "[Ada]"
gnatmake -q hello.adb
./hello
rm -f hello.o hello.ali hello
echo ""

echo "[Java]"
javac Hello.java
java Hello
rm -f Hello.class
echo ""

echo "[Go]"
go run hello.go
echo ""

echo "[Haskell]"
runhaskell hello.hs
echo ""

echo "[Common Lisp]"
clisp hello.lisp
echo ""

echo "[Standard ML]"
smlnj hello.sml
echo ""

echo "[OCaml]"
ocaml hello.ml
echo ""

echo "[Prolog]"
swipl -q -s hello.pl -g main -t halt
echo ""
