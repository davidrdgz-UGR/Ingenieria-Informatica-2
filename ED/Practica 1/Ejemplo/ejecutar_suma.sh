#!/bin/bash
echo -n > tiempos_suma.dat
for tam in $(seq 1000 1000 30000); do
    ./suma_vector $tam >> tiempos_suma.dat
done
