#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {

    

    int longitud = ( argc < 2 ) ? 5 : atoi(argv[1]) ;
    
    srand(time(nullptr)); 
    int* arrayBuscar = new int[longitud];

 /*    for (int n = 0; n < longitud; n++){
        cout << arrayBuscar[n] << endl;
    } */

    for (int i = 0; i < longitud; ++i) {
        arrayBuscar[i] = rand() % 10000;
    }

    int numBuscar = 10000;
    
 /*    for (int n = 0; n < longitud; n++){
        cout << arrayBuscar[n] << endl;
    } */

    // Temporizador

    clock_t start = clock();
    
    for (int i = 0; i < longitud; ++i) {
        
        if (arrayBuscar[i] == numBuscar) {
            return i;
        }
    }

    clock_t end = clock();

    double tiempo = (end - start) / (double)CLOCKS_PER_SEC;

    // cout << endl << "Tiempo empleado: "<< tiempo << endl ;
    
    cout << endl << longitud <<" "<< tiempo << endl ;

    return 0;
}