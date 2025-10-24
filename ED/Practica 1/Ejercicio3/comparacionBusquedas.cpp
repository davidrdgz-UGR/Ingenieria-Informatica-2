#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int busquedaSecuencial (int *array, int longitud, int valorBuscado){
    
    for(int i = 0; i < longitud; i++) {
       
        if(array[i] == valorBuscado){
            
            // cout << "Elemento Encontrado :" << valorBuscado << "(pos " << i << ")"<<endl;
            return i;
        } 
    }

    return -1;
    
}

int BusquedaBinaria(int *array, int longitud, int valorBuscado){
    int inicio = 0;
    int fin = longitud-1;
   

    /* SOLO SIRVE PARA ARRAYS ORDENADOS */
    
    while(inicio <= fin) {
        
        int medio = (inicio + fin) / 2;
        
        if(array[medio] == valorBuscado){
            
            // cout << "Elemento Encontrado :" << valorBuscado << "(pos " << medio << ")"<<endl;
            return medio;

        }else if(array[medio] < valorBuscado){

            inicio = medio + 1;

        }else{
            fin = medio - 1;
        }
    }

    

    return -1; // No encontrado
}


/* Se le va a pasar la longitud del array */
int main(int argc,char* argv[]) {

    int longitud = ( argc < 2 ) ? 5 : atoi(argv[1]);
    int arrayBuscar[longitud];
    
     

    for (int i = 0; i < longitud; ++i) {
        arrayBuscar[i] = i;
    }
   
    /* Elegir elemento a buscar */
    srand(time(nullptr)); 
    int posicion = rand() % longitud - 1;
    int elementoBuscar = arrayBuscar[posicion];

    // cout << endl << "Elemento a buscar: " << elementoBuscar <<endl;
    cout << endl << longitud;
    
    /* Doble Proceso de Busqueda y sus tiempos */
    clock_t start = clock();
    busquedaSecuencial(arrayBuscar,longitud,elementoBuscar);
    clock_t end = clock();
    double tiempo = (end - start) / (double)CLOCKS_PER_SEC;

    cout <<" "<< tiempo;

    start = clock();
    BusquedaBinaria(arrayBuscar,longitud,elementoBuscar);
    end = clock();
    tiempo = (end - start) / (double)CLOCKS_PER_SEC;

    cout <<" "<< tiempo << endl ;


    cout << endl; 
}