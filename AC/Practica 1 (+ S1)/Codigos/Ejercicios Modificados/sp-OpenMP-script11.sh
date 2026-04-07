#!/bin/bash

THREADS_FOR=6
sizes=(8388608 16777216 33554432 67108864)

echo
echo "=== VARIABLES DE ENTORNO OPENMP ==="
echo "OMP_NUM_THREADS=$OMP_NUM_THREADS"
echo "OMP_DYNAMIC=$OMP_DYNAMIC"
echo "OMP_SCHEDULE=$OMP_SCHEDULE"
echo

echo "=============================="
echo "VERSION SECUENCIAL"
echo "=============================="
for n in "${sizes[@]}"
do
    echo "----- N=$n -----"
    /usr/bin/time -f "Elapsed=%e User=%U Sys=%S" ./secuencial "$n"
    echo
done

echo "=============================="
echo "VERSION OPENMP FOR"
echo "Threads usados: $THREADS_FOR"
echo "=============================="
export OMP_NUM_THREADS=$THREADS_FOR
for n in "${sizes[@]}"
do
    echo "----- N=$n -----"
    /usr/bin/time -f "Elapsed=%e User=%U Sys=%S" ./openmp_for "$n"
    echo
done