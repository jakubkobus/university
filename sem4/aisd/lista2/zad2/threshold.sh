#!/bin/bash

for k in {1..5}; do
  echo -e "\nIteration $k"
  time ./findThreshold
done
