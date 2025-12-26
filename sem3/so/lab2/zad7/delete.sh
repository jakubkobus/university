#!/bin/bash

shopt -s extglob
shopt -s nullglob

for file in !(*.sh); do
  if [ -f "$file" ]; then
    rm -f -- "$file"
  fi
done

shopt -u extglob
shopt -u nullglob

