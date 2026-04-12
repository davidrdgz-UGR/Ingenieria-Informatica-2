/* Archivos con funciones */

#include "bubble.cpp"
#include "insertion.cpp"
#include "selection.cpp"
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "heapsort.cpp"
#include "fibonacci.cpp"
#include "hanoi.cpp"


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


int main(int argc, char *argv[]) {

	if (argc <= 3) {
        cerr << "Error: El programa se debe ejecutar de la siguiente forma:\n";
        cerr << argv[0] << " NombreAlgoritmo Semilla tamCaso1 tamCaso2 ... tamCasoN\n";
        return 0;
    }

	int *vectorAlgoritmo;
    int tam, i;
    unsigned long int tiempoInicio, tiempoFin;
    double tiempoEjecucion;
    unsigned long int semilla;
    ofstream fsalida;
    string algoritmo;

	algoritmo = argv[1];
	
	fsalida.open(algoritmo + ".dat");
    if (!fsalida.is_open()) {
        cerr << "Error: No se pudo abrir el fichero " << algoritmo << ".dat\n";
        return 0;
    }

	semilla = atoi(argv[2]);
    srand(semilla);

	for (int argumento = 3; argumento < argc; argumento++) {

		tam = atoi(argv[argumento]);

		vectorAlgoritmo = new int[tam];

		for (i = 0; i < tam; i++) {
			vectorAlgoritmo[i] = rand() % tam;
		}

		tiempoInicio = clock();

		/* SWITCH CON LOS ALGORITMOS  */

		tiempoFin = clock();

		tiempoEjecucion = 1000.0 * (tiempoFin - tiempoInicio) / CLOCKS_PER_SEC;

		fsalida << tam << " " << tiempoEjecucion << "\n";

		cerr << "Tam: " << tam << " Tiempo: " << tiempoEjecucion << endl;

		delete[] vectorAlgoritmo;

	}

	fsalida.close();
	return 0;


}