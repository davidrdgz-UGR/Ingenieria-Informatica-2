#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

bool estaEnCache(const vector<char>& cache, char elemento) {
    return find(cache.begin(), cache.end(), elemento) != cache.end();
}

int siguienteUso(const vector<char>& peticiones, char elemento, int posicionActual) {
    for (int i = posicionActual + 1; i < peticiones.size(); i++) {
        if (peticiones[i] == elemento) {
            return i;
        }
    }

    // Si no se vuelve a usar, devolvemos infinito
    return numeric_limits<int>::max();
}

int elegirElementoAExpulsar(const vector<char>& cache,
                            const vector<char>& peticiones,
                            int posicionActual) {
    int posicionExpulsar = 0;
    int usoMasLejano = -1;

    for (int i = 0; i < cache.size(); i++) {
        int proximoUso = siguienteUso(peticiones, cache[i], posicionActual);

        if (proximoUso > usoMasLejano) {
            usoMasLejano = proximoUso;
            posicionExpulsar = i;
        }
    }

    return posicionExpulsar;
}

void mostrarCache(const vector<char>& cache) {
    cout << "{ ";
    for (char elemento : cache) {
        cout << elemento << " ";
    }
    cout << "}";
}

int main() {
    vector<char> peticiones = {'d','b','d','b','d','a','c','d','b','a','c','b'};
    int k = 3;

    vector<char> cache;

    int aciertos = 0;
    int fallos = 0;

    cout << "Tamano de cache: " << k << endl;
    cout << "Secuencia de peticiones: ";

    for (char p : peticiones) {
        cout << p << " ";
    }

    cout << endl << endl;

    for (int i = 0; i < peticiones.size(); i++) {
        char peticion = peticiones[i];

        cout << "Peticion " << i + 1 << ": " << peticion << " -> ";

        if (estaEnCache(cache, peticion)) {
            aciertos++;
            cout << "acierto. Cache: ";
            mostrarCache(cache);
            cout << endl;
        } else {
            fallos++;
            cout << "fallo. ";

            if (cache.size() < k) {
                cache.push_back(peticion);

                cout << "Se inserta " << peticion << ". Cache: ";
                mostrarCache(cache);
                cout << endl;
            } else {
                int posicionExpulsar = elegirElementoAExpulsar(cache, peticiones, i);
                char expulsado = cache[posicionExpulsar];

                cache[posicionExpulsar] = peticion;

                cout << "Se expulsa " << expulsado;
                cout << " y se inserta " << peticion << ". Cache: ";
                mostrarCache(cache);
                cout << endl;
            }
        }
    }

    cout << endl;
    cout << "Aciertos totales: " << aciertos << endl;
    cout << "Fallos totales: " << fallos << endl;

    return 0;
}