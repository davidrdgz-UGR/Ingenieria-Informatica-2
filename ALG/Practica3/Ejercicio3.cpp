#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

const int INF = 999999;

struct Arista {
	int origen;
    int destino;
    int peso;
};

void mostrarEstado(vector<int>& d, vector<int>& pred, vector<string>& nombres) {
    cout << "Vertice\tDistancia\tPredecesor" << endl;

    for (int i = 0; i < d.size(); i++) {
        cout << nombres[i] << "\t";

        if (d[i] == INF)
            cout << "INF";
        else
            cout << d[i];

        cout << "\t\t";

        if (pred[i] == -1)
            cout << "-";
        else
            cout << nombres[pred[i]];

        cout << endl;
    }
}

void dijkstra(int V, vector<Arista>& aristas, int origen, vector<string>& nombres) {
    vector<int> d(V, INF);
    vector<int> pred(V, -1);
    vector<bool> visitado(V, false);

    d[origen] = 0;

    cout << "Estado inicial:" << endl;
    mostrarEstado(d, pred, nombres);

    for (int paso = 1; paso <= V; paso++) {
        int u = -1;
        int menor = INF;

        // Buscar el vertice no visitado con menor distancia
        for (int i = 0; i < V; i++) {
            if (!visitado[i] && d[i] < menor) {
                menor = d[i];
                u = i;
            }
        }

        if (u == -1) {
            break;
        }

        visitado[u] = true;

        // Relajar las aristas que salen de u
        for (Arista a : aristas) {
            if (a.origen == u) {
                if (d[u] != INF && d[u] + a.peso < d[a.destino]) {
                    d[a.destino] = d[u] + a.peso;
                    pred[a.destino] = u;
                }
            }
        }

        cout << "\nPaso " << paso << " - se selecciona " << nombres[u] << ":" << endl;
        mostrarEstado(d, pred, nombres);
    }
}





int main(){
	// vector<vector<Arista>> grafo(5);
	const int V = 5;
	int s = 0, t = 1, x = 2, y = 3, z = 4;
	vector<string> nombres = {"s", "t", "x", "y", "z"};

	vector<Arista> aristas = {
		{s, t, 3},
		{s, y, 5},
		{s, z, 3},

		{t, x, 6},
		{t, y, 2},

		{y, t, 1},
		{y, x, 4},
		{y, z, 6},

		{x, z, 2},

		{z, x, 7}
	};

	dijkstra(V, aristas, s, nombres);
	dijkstra(V, aristas, z, nombres);

	return 0;
}
