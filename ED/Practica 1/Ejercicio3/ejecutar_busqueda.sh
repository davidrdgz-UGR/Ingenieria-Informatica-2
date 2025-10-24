#!/bin/bash

set -e
echo -n > tiemposBusqueda.dat

for n in $(seq 1000 1000 50000000); do
  ./busquedaSecuencial "$n" >> tiemposBusqueda.dat
done

echo "Listo -> tiemposBusqueda.dat"