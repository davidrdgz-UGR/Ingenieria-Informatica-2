#include <iostream>
#include <vector>
using namespace std;

struct Resultado {
    int minimo;
    int maximo;
    int comparaciones;
};

Resultado calcularMinMax(const vector<int>& v) {
    int n = v.size();

    int minimo, maximo;
    int comparaciones = 0;
    int i;

    // Caso inicial: distinguimos si n es par o impar
    if (n % 2 == 0) {
        comparaciones++;

        if (v[0] < v[1]) {
            minimo = v[0];
            maximo = v[1];
        } else {
            minimo = v[1];
            maximo = v[0];
        }

        i = 2;
    } else {
        minimo = v[0];
        maximo = v[0];
        i = 1;
    }

    // Procesamos el resto de elementos por parejas
    while (i < n - 1) {
        int menorPareja, mayorPareja;

        comparaciones++;

        if (v[i] < v[i + 1]) {
            menorPareja = v[i];
            mayorPareja = v[i + 1];
        } else {
            menorPareja = v[i + 1];
            mayorPareja = v[i];
        }


		
        comparaciones++;

        if (menorPareja < minimo) {
            minimo = menorPareja;
        }

        comparaciones++;

        if (mayorPareja > maximo) {
            maximo = mayorPareja;
        }

        i += 2;
    }

    return {minimo, maximo, comparaciones};
}

int main() {
    vector<int> v = {5, 19, 30, 904, 13, 54, 3};

    Resultado resultado = calcularMinMax(v);

    cout << "Minimo: " << resultado.minimo << endl;
    cout << "Maximo: " << resultado.maximo << endl;
    cout << "Comparaciones realizadas: " << resultado.comparaciones << endl;

    return 0;
}