#include <iostream>
#include <vector>
#include <string>
// #include <limits>
using namespace std;

const int INF = 999999;

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

    for (Arista a : aristas) {
        if (d[a.origen] != INF && d[a.origen] + a.peso < d[a.destino]) {
            cout << "\nEl grafo contiene un ciclo negativo." << endl;
            return;
        }
    }

    cout << "\nNo hay ciclos negativos alcanzables desde el origen." << endl;
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
	const int V = 5;

    int s = 0, t = 1, x = 2, y = 3, z = 4;

    vector<string> nombres = {"s", "t", "x", "y", "z"};

	// Grafo del ejercicio 1
    vector<Arista> grafo1 = {
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

	cout << "\n===== BELLMAN-FORD - GRAFO EJERCICIO 1 - ORIGEN z =====\n";
    cargadoCorrectamente(nombres, grafo1);
    bellmanFord(V, grafo1, z, nombres);

    // Grafo del ejercicio 1 modificado: z -> x cambia de 7 a 4
    vector<Arista> grafo1Modificado = {
        {s, t, 6},
        {s, y, 7},
        {t, x, 5},
        {t, y, 8},
        {t, z, -4},
        {x, t, -2},
        {y, x, -3},
        {y, z, 9},
        {z, x, 4},
        {z, s, 2}
    };


	cout << "\n===== BELLMAN-FORD - GRAFO EJERCICIO 1 MODIFICADO - ORIGEN s =====\n";
    cargadoCorrectamente(nombres, grafo1Modificado);
    bellmanFord(V, grafo1Modificado, s, nombres);

    // Grafo del ejercicio 3
    vector<Arista> grafo3 = {
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

	cout << "\n===== DIJKSTRA - GRAFO EJERCICIO 3 - ORIGEN s =====\n";
    cargadoCorrectamente(nombres, grafo3);
    dijkstra(V, grafo3, s, nombres);


    cout << "\n===== DIJKSTRA - GRAFO EJERCICIO 3 - ORIGEN z =====\n";
    cargadoCorrectamente(nombres, grafo3);
    dijkstra(V, grafo3, z, nombres);


	return 0;
}
