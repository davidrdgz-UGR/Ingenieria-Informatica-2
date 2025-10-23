#!/bin/bash
set -e
echo -n > tiemposOrdenacion1.dat
echo -n > tiemposOrdenacion2.dat
echo -n > tiemposOrdenacion3.dat

for n in $(seq 5 5 1000); do
  ./ordenacionIterativa $n 1 >> tiemposOrdenacion1.dat
done

for n in $(seq 5 5 1000); do
  ./ordenacionIterativa $n 2 >> tiemposOrdenacion2.dat
done

for n in $(seq 5 5 1000); do
  ./ordenacionIterativa $n 3 >> tiemposOrdenacion3.dat
done


echo "Listo, datos generados"
