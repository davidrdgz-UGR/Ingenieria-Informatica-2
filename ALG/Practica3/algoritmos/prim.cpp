#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;



class Grafo {
    public:
        vector<vector<pair<int, int>>> adj;
        vector<int> pred;
        vector<int> color;
        Grafo(int N) {
            adj.resize(N+1);
            pred.resize(N+1);
            color.resize(N+1);
            for (int i=0; i<N+1; i++) {
                pred[i] = -1;
                color[i] = 1;
            }
        };
        void addArista(int a, int b, int w) {
            adj[a].push_back({w,b});
            adj[b].push_back({w,a});
        }
};


vector<vector<int>> PrimARM(Grafo & G, int a) {
    vector<vector<int>> A;

    // Instancia de la cola con prioridad (consultar documentación C++)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    q.push({0,a});

    pair<int,int> pa;
    int u, v;
    int padre = a;
    while (!q.empty()) {
        pa = q.top(); q.pop();
        u = pa.second;
        if (G.color[u] == 2) continue;
        A.push_back({padre,u});
        G.pred[u] = padre;

        for (int i=0; i < G.adj[u].size(); i++) {
            pa = G.adj[u][i];
            v = pa.second;
            cout << "ady de " << u << ": " << v << endl;
            if (G.color[v] == 1) {
                q.push(pa);
                cout << "push " << v << " a la cola" << endl;
            }
        }
        G.color[u] = 2;

        // El predecesor para el próximo elemento de la cola
        padre = u;
    }

    return A;
}



int main() {

    Grafo G(6);
    G.addArista(1, 2, 2);
    G.addArista(1, 6, 5);
    G.addArista(1, 3, 3);
    G.addArista(2, 4, 2);
    G.addArista(3, 4, 1);
    G.addArista(3, 5, 5);
    G.addArista(4, 6, 7);
    G.addArista(5, 6, 2);

    vector<vector<int>> sol = PrimARM(G, 1);

    cout << "Solución:\n";
    for (int i=0; i<sol.size(); i++) {
        cout << sol[i][0] << "-" << sol[i][1] << endl;
    }

}

