#include <iostream>
#include <ctime>
#include <cstdlib>
// #include <chrono>

using namespace std;

void multiplicarMatrices(){


}

int main(int argc,char* argv[]) {

    int dimensionMat = ( argc < 2 ) ? 3 : atoi(argv[1]);

    int matriz[dimensionMat][dimensionMat];
    
    srand(time(nullptr)); 
    
    for (int filas=0; filas<dimensionMat; filas++){

        for(int col=0; col<dimensionMat; col++){
            matriz[filas][col] = rand() % 10;
            // cout << matriz[filas][col] << " ";
        }
        // cout << endl;
    }
    

}