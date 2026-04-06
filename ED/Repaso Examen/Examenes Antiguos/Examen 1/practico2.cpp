#include <iostream>
using namespace std;

// --------------------
// Grafo (sin STL): lista de adyacencia con listas enlazadas
// --------------------
struct Arista {
    int v;
    Arista* sig;
    Arista(int _v, Arista* _sig = nullptr) : v(_v), sig(_sig) {}
};

struct Grafo {
    int V;
    Arista** adj; // adj[u] -> lista enlazada de vecinos

    Grafo(int n) : V(n) {
        adj = new Arista*[V];
        for (int i = 0; i < V; ++i) adj[i] = nullptr;
    }

    // Añade arista dirigida u -> v
    void addArista(int u, int v) {
        adj[u] = new Arista(v, adj[u]); // inserta al principio
    }

    // Añade arista no dirigida (u <-> v)
    void addAristaNoDir(int u, int v) {
        addArista(u, v);
        addArista(v, u);
    }

    ~Grafo() {
        for (int i = 0; i < V; ++i) {
            Arista* p = adj[i];
            while (p) {
                Arista* aux = p;
                p = p->sig;
                delete aux;
            }
        }
        delete[] adj;
    }
};

// --------------------
// Pila (sin STL): array dinámico
// --------------------
struct Pila {
    int* a;
    int top;
    int cap;

    Pila(int c) : top(0), cap(c) { a = new int[cap]; }
    ~Pila() { delete[] a; }

    bool vacia() const { return top == 0; }
    void push(int x) { a[top++] = x; }
    int pop() { return a[--top]; }
};

// --------------------
// Cola (sin STL): cola circular con array dinámico
// --------------------
struct Cola {
    int* a;
    int ini, fin, tam, cap;

    Cola(int c) : ini(0), fin(0), tam(0), cap(c) { a = new int[cap]; }
    ~Cola() { delete[] a; }

    bool vacia() const { return tam == 0; }
    void push(int x) { a[fin] = x; fin = (fin + 1) % cap; tam++; }
    int pop() { int x = a[ini]; ini = (ini + 1) % cap; tam--; return x; }
};

// --------------------
// DFS iterativo (pila)
// --------------------
void DFS(const Grafo& g, int inicio, const char* etiqueta) {
    bool* vis = new bool[g.V];
    for (int i = 0; i < g.V; ++i) vis[i] = false;

    Pila st(g.V);
    st.push(inicio);

    while (!st.vacia()) {
        int u = st.pop();
        if (vis[u]) continue;
        vis[u] = true;

        cout << etiqueta[u] << " ";

        // OJO: el orden exacto depende del orden de inserción en adj[u]
        for (Arista* p = g.adj[u]; p != nullptr; p = p->sig) {
            int v = p->v;
            if (!vis[v]) st.push(v);
        }
    }

    delete[] vis;
}

// --------------------
// BFS (cola)
// --------------------
void BFS(const Grafo& g, int inicio, const char* etiqueta) {
    bool* vis = new bool[g.V];
    for (int i = 0; i < g.V; ++i) vis[i] = false;

    Cola q(g.V);
    vis[inicio] = true;
    q.push(inicio);

    while (!q.vacia()) {
        int u = q.pop();
        cout << etiqueta[u] << " ";

        for (Arista* p = g.adj[u]; p != nullptr; p = p->sig) {
            int v = p->v;
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    delete[] vis;
}

// --------------------
// MAIN: 2 ejemplos (cada uno con DFS y BFS)
// --------------------
int main() {
    // Ejemplo 1: Grafo NO dirigido con 6 nodos (A..F)
    {
        cout << "===== EJEMPLO 1 (No dirigido) =====\n";
        // Nodos: 0=A,1=B,2=C,3=D,4=E,5=F
        const int V = 6;
        char etiqueta[V] = {'A','B','C','D','E','F'};

        Grafo g(V);

        // Estructura (no dirigida):
        // A-B, A-C, B-D, C-D, C-E, E-F
        g.addAristaNoDir(0, 1); // A-B
        g.addAristaNoDir(0, 2); // A-C
        g.addAristaNoDir(1, 3); // B-D
        g.addAristaNoDir(2, 3); // C-D
        g.addAristaNoDir(2, 4); // C-E
        g.addAristaNoDir(4, 5); // E-F

        cout << "Inicio: A\n";
        cout << "DFS (pila): ";
        DFS(g, 0, etiqueta);
        cout << "\n";

        cout << "BFS (cola): ";
        BFS(g, 0, etiqueta);
        cout << "\n\n";
    }

    // Ejemplo 2: Grafo DIRIGIDO con 7 nodos (A..G)
    {
        cout << "===== EJEMPLO 2 (Dirigido) =====\n";
        // Nodos: 0=A,1=B,2=C,3=D,4=E,5=F,6=G
        const int V = 7;
        char etiqueta[V] = {'A','B','C','D','E','F','G'};

        Grafo g(V);

        // Aristas dirigidas:
        // A->B, A->C, B->D, C->D, D->E, E->C (ciclo), E->F, F->G
        g.addArista(0, 1); // A->B
        g.addArista(0, 2); // A->C
        g.addArista(1, 3); // B->D
        g.addArista(2, 3); // C->D
        g.addArista(3, 4); // D->E
        g.addArista(4, 2); // E->C (ciclo)
        g.addArista(4, 5); // E->F
        g.addArista(5, 6); // F->G

        cout << "Inicio: A\n";
        cout << "DFS (pila): ";
        DFS(g, 0, etiqueta);
        cout << "\n";

        cout << "BFS (cola): ";
        BFS(g, 0, etiqueta);
        cout << "\n\n";
    }

    cout << "Nota: El orden exacto puede variar segun el orden de insercion en la lista de adyacencia.\n";
    return 0;
}
