#include <iostream>
#include <vector>
using namespace std;

int minimoDivideVenceras(const vector<int>& v, int inicio, int fin) {
    // Caso base: si solo hay un elemento, ese es el mínimo
    if (inicio == fin) {
        return v[inicio];
    }

    int medio = (inicio + fin) / 2;

    int minimoIzquierda = minimoDivideVenceras(v, inicio, medio);
    int minimoDerecha = minimoDivideVenceras(v, medio + 1, fin);

    if (minimoIzquierda < minimoDerecha) {
        return minimoIzquierda;
    } else {
        return minimoDerecha;
    }
}

int maximoDivideVenceras(const vector<int>& v, int inicio, int fin) {
    // Caso base: si solo hay un elemento, ese es el máximo
    if (inicio == fin) {
        return v[inicio];
    }

    int medio = (inicio + fin) / 2;

    int maximoIzquierda = maximoDivideVenceras(v, inicio, medio);
    int maximoDerecha = maximoDivideVenceras(v, medio + 1, fin);

    if (maximoIzquierda > maximoDerecha) {
        return maximoIzquierda;
    } else {
        return maximoDerecha;
    }
}

int main() {
    vector<int> v = {5, 19, 30, 904, 13, 54, 3};
	// vector<int> v = {5};

    int minimo = minimoDivideVenceras(v, 0, v.size() - 1);
    int maximo = maximoDivideVenceras(v, 0, v.size() - 1);

    cout << "Minimo: " << minimo << endl;
    cout << "Maximo: " << maximo << endl;

    return 0;
}