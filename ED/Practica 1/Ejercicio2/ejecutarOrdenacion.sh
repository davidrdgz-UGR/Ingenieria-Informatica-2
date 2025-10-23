#!/bin/bash
set -e
echo -n > tiemposOrdenacion.dat

for n in $(seq 5 5 1000); do
  ./ordenacionIterativa $n >> tiemposOrdenacion.dat
done


echo "Listo, datos generados: tiemposOrdenacion.dat"
