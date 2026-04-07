#!/bin/bash

THREADS_FOR=6
THREADS_SECTIONS=2

echo
echo "=== VARIABLES DE ENTORNO OPENMP ==="
echo "OMP_NUM_THREADS=$OMP_NUM_THREADS"
echo "OMP_DYNAMIC=$OMP_DYNAMIC"
echo "OMP_SCHEDULE=$OMP_SCHEDULE"
echo

sizes=(16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388608 16777216 33554432 67108864)

echo "=============================="
echo "VERSION SECUENCIAL"
echo "=============================="
for n in "${sizes[@]}"
do
    echo "----- N=$n -----"
    ./secuencial "$n"
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
    ./openmp_for "$n"
    echo
done

echo "=============================="
echo "VERSION OPENMP SECTIONS"
echo "Threads usados: $THREADS_SECTIONS"
echo "=============================="
export OMP_NUM_THREADS=$THREADS_SECTIONS
for n in "${sizes[@]}"
do
    echo "----- N=$n -----"
    ./openmp_sections "$n"
    echo
done