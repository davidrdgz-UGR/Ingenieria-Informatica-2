#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Arista {
    int origen;
    int destino;
    int peso;
};

void cargadoCorrectamente(vector<string>& nombres, vector<Arista>& Aristas){

	cout << "Grafo cargado correctamente:" << endl;

    for (Arista arista : Aristas) {
        cout << nombres[arista.origen] << " -> " << nombres[arista.destino] << " = " << arista.peso << endl;
    }

}

void mostrarEstado(vector<int>& d, vector<int>& pred, vector<string>& nombres) {
    const int INF = 999999;

    cout << "Vertice\t d\t pi" << endl;

    for (int i = 0; i < d.size(); i++) {
        cout << nombres[i] << "\t ";

        if (d[i] == INF)
            cout << "INF";
        else
            cout << d[i];

        cout << "\t ";

        if (pred[i] == -1)
            cout << "-";
        else
            cout << nombres[pred[i]];

        cout << endl;
    }
}

void bellmanFord(int V, vector<Arista>& aristas, int origen, vector<string>& nombres) {
    const int INF = 999999;

    vector<int> d(V, INF);
    vector<int> pred(V, -1);

    d[origen] = 0;

    cout << "\nEstado inicial:" << endl;
    mostrarEstado(d, pred, nombres);

    for (int i = 1; i <= V - 1; i++) {
        cout << "\nPaso " << i << ":" << endl;

        for (Arista a : aristas) {
            if (d[a.origen] != INF && d[a.origen] + a.peso < d[a.destino]) {
                d[a.destino] = d[a.origen] + a.peso;
                pred[a.destino] = a.origen;
            }
        }

        mostrarEstado(d, pred, nombres);
    }
}



int main() {
    const int V = 5;

    // Índices de los vértices
    int s = 0, t = 1, x = 2, y = 3, z = 4;

    vector<string> nombres1 = {"s", "t", "x", "y", "z"};

    vector<Arista> aristas1 = {
        {s, t, 6},
        {s, y, 7},
        {t, x, 5},
        {t, y, 8},
        {t, z, -4},
        {x, t, -2},
        {y, x, -3},
        {y, z, 9},
        {z, x, 7},
        {z, s, 2}
    };

	cargadoCorrectamente(nombres1,aristas1);


	cout << "Bellman-Ford con origen z\n" << endl;
	bellmanFord(V, aristas1, z, nombres1);

    return 0;
}