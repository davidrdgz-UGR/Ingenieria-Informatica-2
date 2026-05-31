#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool comparador(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

class Grafo {
    public:
        vector<vector<int>> aristas;
        int numVertices;
        Grafo(int N){
            numVertices = N;
        }
        void addArista(int u, int v, int w) {
            aristas.push_back({u,v,w});
        }
        void sortAr(){
            sort(aristas.begin(), aristas.end(), comparador);
        }
        void toString(){
            for (int i=0; i<aristas.size(); i++){
                cout << aristas[i][0] << "-" << aristas[i][1] << " " << aristas[i][2] << endl;
            }
        }
};


class CD {
    public:
        vector<int> padre;
        vector<int> rango;
        CD(int N) {
            padre.resize(N+1);
            rango.resize(N+1);
            for (int i=1; i<N+1; i++) {
                padre[i] = i;
                rango[i] = 0;
            }
        }

        int find(int x) {
            if (x != padre[x])
                padre[x] = find(padre[x]);
            return padre[x];
        }

        void union_(int x, int y){
            link(find(x), find(y));
        }

        void link(int x, int y) {
            if (rango[x] > rango[y]) {
                padre[y] = x;
            } else {
                padre[x] = y;
                if (rango[x] == rango[y]) {
                    rango[y] += 1;
                }
            }
        }
};


vector<pair<int,int>> kruskalARM(Grafo & g) {
    // Make-set
    CD cd(g.numVertices);
    // Ordena aristas O(E log(E))
    g.sortAr();
    cout << "Ordenación:\n";
    g.toString();
    // Bucle Kruskal O(E log V)
    int u,v;
    vector<pair<int,int>> A;
    for (int i=0; i<g.aristas.size(); i++) {
        u = g.aristas[i][0];
        v = g.aristas[i][1];
        if (cd.find(u) != cd.find(v)) {
            A.push_back({u,v});
            cd.union_(u,v);
        }
    }

    return A;
}


int main(){

    Grafo G(6);
    G.addArista(1, 2, 2);
    G.addArista(1, 6, 5);
    G.addArista(1, 3, 3);
    G.addArista(2, 4, 2);
    G.addArista(3, 4, 1);
    G.addArista(3, 5, 5);
    G.addArista(4, 6, 7);
    G.addArista(5, 6, 2);

    // G.sortAr();
    // G.toString();

    vector<pair<int,int>> sol;
    sol = kruskalARM(G);

    cout << "Solución:\n";
    for (int i=0; i<sol.size(); i++) {
        cout << sol[i].first << "-" << sol[i].second << endl;
    }
    
    return 0;
}