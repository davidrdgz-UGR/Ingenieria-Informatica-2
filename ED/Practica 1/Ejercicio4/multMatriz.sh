#!/bin/bash

set -e
echo -n > multiplicacionMatrices.dat

for n in $(seq 10 10 1500); do
  ./multiplicacionMatrices.exe "$n" >> multiplicacionMatrices.dat
  echo "" >> multiplicacionMatrices.dat 
done

echo "Listo -> multiplicacionMatrices.dat"