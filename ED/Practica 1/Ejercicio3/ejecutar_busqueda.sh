#!/bin/bash

set -e
echo -n > tiemposBusqueda.dat

for n in $(seq 1000 1000 200000); do
  ./comparacionBusquedas.exe "$n" >> tiemposBusqueda.dat
done

echo "Listo -> tiemposBusqueda.dat"