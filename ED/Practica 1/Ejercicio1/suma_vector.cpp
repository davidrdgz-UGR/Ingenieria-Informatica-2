#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int suma(const int *v, int n) {
    int total = 0;
    for (int i = 0; i < n; i++)
    total += v[i];
    return total;
}

int main(int argc, char *argv[]) {
   
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " TAM" << endl;
        return 1;
    }

    int tam = atoi(argv[1]);
    int *v = new int[tam];
    
    for (int i = 0; i < tam; i++) v[i] = rand() % 1000;

    clock_t start = clock();
    
    int resultado = suma(v, tam);
    
    clock_t end = clock();
    
    double tiempo = (end - start) / (double)CLOCKS_PER_SEC;
    
    cout << tam << "\t" << tiempo << endl;
    
    delete[] v;
    
    return 0;
}
