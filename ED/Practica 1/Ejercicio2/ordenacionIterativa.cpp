#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void burbujaOptimizadoDavid(int *arrayOrdenar, int longitud){

    int cambios = 0;
    int aux;

    for( int n=0; n<longitud-1;n++ ){
        
        if(arrayOrdenar[n]>arrayOrdenar[n+1]){
            aux = arrayOrdenar[n+1];
            arrayOrdenar[n+1] = arrayOrdenar[n];
             arrayOrdenar[n] = aux;
            

        }

    }


}


int main(int argc, char *argv[]) {

    int longitud = 5;
    int arrayOrdenar[longitud] = {5,4,3,2,1}; 

    burbujaOptimizadoDavid(arrayOrdenar,longitud);

    for( int n=0; n<longitud;n++ ){
        
        cout << arrayOrdenar[n] << " ";

    }
}