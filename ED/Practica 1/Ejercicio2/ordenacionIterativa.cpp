#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void burbujaOptimizadoDavid(int *array, int longitud){
    
    int aux;
    bool ordenado = false;
    int interacciones;
    
    while(!ordenado){
    
        interacciones = 0;

        for( int n=0; n<longitud-1;n++ ){
        
            
            
            if(array[n]>array[n+1]){
                aux = array[n+1];
                array[n+1] = array[n];
                array[n] = aux;
                
                if(array[n+1] != 0 ){
                    interacciones++;
                }
                
            }

            // cout << "Interaccion "<< n << endl;
        }

        if(interacciones == 0 ) ordenado = true;
        
    }

 /*    for( int n=0; n<longitud;n++ ){
        
        cout << array[n] << " ";

    }
    cout << endl << endl; */
}


int main(int argc,char* argv[]) {

    int longitud = ( argc < 2 ) ? 5 : atoi(argv[1]);
    int arrayOrdenar[longitud]; 

    for (int i = 0; i < longitud; ++i) {
        arrayOrdenar[i] = rand() % 1000;
    }

    
    clock_t start = clock();
    burbujaOptimizadoDavid(arrayOrdenar,longitud);
    clock_t end = clock();

    double tiempo = (end - start) / (double)CLOCKS_PER_SEC;
    
    cout << longitud << "\t" << tiempo << endl;





    
}