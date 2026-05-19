#!/bin/bash

N=18432
THREADS=3

export OMP_NUM_THREADS=$THREADS

gcc -O2 -fopenmp -o pmtv-OpenMP pmtv-OpenMP.c

echo "N = $N"
echo "Threads = $OMP_NUM_THREADS"

echo "===== EJECUCION 1 ====="

export OMP_SCHEDULE="monotonic:static"
echo "Static por defecto"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:dynamic"
echo "Dynamic por defecto"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:guided"
echo "Guided por defecto"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:static,1"
echo "Static chunk 1"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:dynamic,1"
echo "Dynamic chunk 1"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:guided,1"
echo "Guided chunk 1"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:static,64"
echo "Static chunk 64"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:dynamic,64"
echo "Dynamic chunk 64"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:guided,64"
echo "Guided chunk 64"
./pmtv-OpenMP $N

echo "===== EJECUCION 2 ====="

export OMP_SCHEDULE="monotonic:static"
echo "Static por defecto"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:dynamic"
echo "Dynamic por defecto"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:guided"
echo "Guided por defecto"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:static,1"
echo "Static chunk 1"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:dynamic,1"
echo "Dynamic chunk 1"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:guided,1"
echo "Guided chunk 1"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:static,64"
echo "Static chunk 64"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:dynamic,64"
echo "Dynamic chunk 64"
./pmtv-OpenMP $N

export OMP_SCHEDULE="monotonic:guided,64"
echo "Guided chunk 64"
./pmtv-OpenMP $N