
#include <iostream>

using namespace std;

struct Arista {
    int v;
    Arista* sig;
    Arista(int _v, Arista* _sig=nullptr) : v(_v), sig(_sig) {}
};

struct Grafo {
    int V;
    Arista** adj; // array de punteros a listas

    Grafo(int n) : V(n) {
        adj = new Arista*[V];
        for (int i = 0; i < V; ++i) adj[i] = nullptr;
    }

    void addArista(int u, int v) {
        // inserta al principio (u -> v)
        adj[u] = new Arista(v, adj[u]);
    }

    ~Grafo() {
        for (int i = 0; i < V; ++i) {
            Arista* p = adj[i];
            while (p) { Arista* aux = p; p = p->sig; delete aux; }
        }
        delete[] adj;
    }
};

struct Pila {
    int* a;
    int top;
    int cap;
    Pila(int c) : top(0), cap(c) { a = new int[cap]; }
    ~Pila(){ delete[] a; }
    bool vacia() const { return top == 0; }
    void push(int x){ a[top++] = x; }
    int pop(){ return a[--top]; }
};

struct Cola {
    int* a;
    int ini, fin, tam, cap;
    Cola(int c) : ini(0), fin(0), tam(0), cap(c) { a = new int[cap]; }
    ~Cola(){ delete[] a; }
    bool vacia() const { return tam == 0; }
    void push(int x){ a[fin] = x; fin = (fin+1)%cap; tam++; }
    int pop(){ int x = a[ini]; ini = (ini+1)%cap; tam--; return x; }
};

void DFS(const Grafo& g, int inicio) {
    bool* vis = new bool[g.V];
    for (int i = 0; i < g.V; ++i) vis[i] = false;

    Pila st(g.V);
    st.push(inicio);

    while (!st.vacia()) {
        int u = st.pop();
        if (vis[u]) continue;
        vis[u] = true;
        cout << u << " ";

        // apilar vecinos
        for (Arista* p = g.adj[u]; p != nullptr; p = p->sig) {
            if (!vis[p->v]) st.push(p->v);
        }
    }

    delete[] vis;
}

void BFS(const Grafo& g, int inicio) {
    bool* vis = new bool[g.V];
    for (int i = 0; i < g.V; ++i) vis[i] = false;

    Cola q(g.V);
    vis[inicio] = true;
    q.push(inicio);

    while (!q.vacia()) {
        int u = q.pop();
        cout << u << " ";

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
