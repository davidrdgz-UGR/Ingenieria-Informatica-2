#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void burbujaOptimizado(int *array, int longitud){
    
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

  /*   for( int n=0; n<longitud;n++ ){
        
        cout << array[n] << " ";

    }
    cout << endl << endl; */
}


int main(int argc,char* argv[]) {

    int longitud = ( argc < 2 ) ? 5 : atoi(argv[1]);
    int arrayOrdenar[longitud]; 
    int opcion = ( argc < 3 || atoi(argv[2])<1 || atoi(argv[2])>3) ? 1 : atoi(argv[2]);

    switch (opcion){
        case 1:
            
            for (int i = 0; i < longitud; ++i) {
                arrayOrdenar[i] = rand() % 1000;
            }
            break;
        case 2:
            
            for (int i = 0; i < longitud; ++i) {
                arrayOrdenar[i] = i+1;
            }
            break;

        case 3:
            for (int i = 0; i < longitud; ++i) {
                arrayOrdenar[i] = longitud-i;
            }
            break;

    }

    
    clock_t start = clock();
    burbujaOptimizado(arrayOrdenar,longitud);
    clock_t end = clock();

    double tiempo = (end - start) / (double)CLOCKS_PER_SEC;
    
    cout << longitud << "\t" << tiempo << endl;





    
}