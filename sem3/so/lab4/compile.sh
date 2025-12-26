#!/bin/bash

files=$(ls *.c)

mkdir -p bin

for file in $files; do
    gcc -Wall -Wextra -pedantic -o "./bin/${file%.c}" "$file"
done