#include <iostream>
#include <ctime>
#include <cstdlib>
// #include <chrono>

using namespace std;


int** generarMatriz(int dimensiones){

    int** matriz = new int*[dimensiones];

    // cout << endl;

    for (int filas=0; filas<dimensiones; filas++){

        matriz[filas] = new int[dimensiones];

        for(int col=0; col<dimensiones; col++){
            
            matriz[filas][col] = rand() % 10;
            
            // cout << matriz[filas][col] << " ";
        }
        // cout << endl;
        
    }
    
    // cout << "Matriz creada" << endl;
    return matriz;
}


/* Se podría hacer el proceso para crear matrices válidas, pero vamos a hacerlo para matrices Cuadradas (que las dimensiones resultantes son las mismas) */
void multiplicarMatricesCuadradas(int** matriz1,int** matriz2,int dimensiones){


    int** nuevaMatriz = new int*[dimensiones];

    for (int i = 0; i < dimensiones; i++) {
        nuevaMatriz[i] = new int[dimensiones];
    }

    
    for (int i = 0; i < dimensiones; i++) {
        for (int j = 0; j < dimensiones; j++) {
            int suma = 0;
            for (int k = 0; k < dimensiones; k++) {
                suma += matriz1[i][k] * matriz2[k][j];
            }
            nuevaMatriz[i][j] = suma;
        }
    }

    /* Visualizar Nueva Matriz - Comentar Despues -> Comprobacion de Multiplicacion Hecha, Correcta */
/*     cout << endl;
    for (int filas=0; filas<dimensiones; filas++){
        for(int col=0; col<dimensiones; col++){
            
            cout << nuevaMatriz[filas][col] << " ";
        }
        cout << endl;
        
    }  */

    // return nuevaMatriz;
}



int main(int argc,char* argv[]) {

    int dimensionMat = ( argc < 2 ) ? 3 : atoi(argv[1]);

    srand(time(nullptr)); 

    int** matriz1 = generarMatriz(dimensionMat);
    int** matriz2 = generarMatriz(dimensionMat);
    
    

    clock_t start = clock();
    multiplicarMatricesCuadradas(matriz1, matriz2, dimensionMat);
    clock_t end = clock();

    double tiempo = (end - start) / (double)CLOCKS_PER_SEC;

    cout << dimensionMat;
    cout <<" "<< tiempo << endl;

}