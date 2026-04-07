#!/bin/bash

mkdir -p results

K_VALUES=(1 10 100)
SMALL_N=(10 20 30 40 50)
LARGE_N=($(seq 1000 1000 50000))

for k in "${K_VALUES[@]}"; do
  for n in "${SMALL_N[@]}"; do
    for algo in insertion quick hybrid; do
      ./main $algo $n $k
    done
  done

  for n in "${LARGE_N[@]}"; do
    for algo in quick hybrid; do
      ./main $algo $n $k
    done
  done
done
