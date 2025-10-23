#!/bin/bash

set -e
echo -n > tiempos_busqueda.dat

for n in $(seq 10000 10000 5000000); do
  ./busquedaSecuencial "$n" >> tiempos_busqueda.dat
done

echo "Listo -> tiempos_busqueda.dat"