#include <iostream>

using namespace std;

template <class T>
class Arbol {
    public:
    Arbol();
    Arbol(T valor);
    Arbol(const Arbol<T> & a);
    ~Arbol();
    void setRaiz(T valor);
    Nodo getRaiz();
    T getEtiqueta(Nodo n);
    void setEtiqueta(Nodo &n, T valor);
    Nodo getPadre(Nodo n);
    Nodo getHijoIzq(Nodo n);
    Nodo getHermanoDcha(Nodo n);
    Nodo getHermanoIzq(Nodo n);
    void insertarHijoIzq(Nodo &p, T valor);
    void insertarHermanoDcha(Nodo &p, T valor);
    void vaciar();
    bool estaVacio() const;
    Arbol<T> & operator= (const Arbol<T> &a);
    bool operator== (const Arbol<T> &a) const;

    string operator<< (const Arbol<T>& a){
        if (a.estaVacio()) return "Esta vacio.";

        return preordenAux( a, a.getRaiz());
    }

    /* Preorden es: R -> Hi -> Hd */
    static string preordenAux(const Arbol<T>& a, Nodo n){

        texto;

        texto += a->getEtiqueta(n);

        if(a->getHijoIzq(n)){   /* En caso de que al devolver null no ejecute el if */
            texto += preordenAux(a,a->getHijoIzq(n));

            
        }else(a->getHermanoDcha(n)){
            texto += preordenAux(a,a->getHijoIzq(n));
        }

        return texto;
        
    }

    static int getAltura(const Arbol<T>& a, Nodo n){

        if (n) return -1; 

        Nodo h = a.getHijoIzq(n);

        if (h) return 0; /* Hoja */

        int maxAlt = -1;
        
        while (h) {
            int altH = getAltura(a, h);
            if (altH > maxAlt) maxAlt = altH;
            h = a.getHermanoDcha(h);
        }

        return 1 + maxAlt;
    }

    int profundidadNodo(const Arbol<T>& a, Nodo n) {
        
        if (a.estaVacio() || n ) return -1;

        Nodo r = a.getRaiz();
        int d = 0;

        while (n != r) {
            n = a.getPadre(n);
            if (n) return -1; // por si pasaron un nodo que no pertenece al árbol
            d++;
        }
        return d;
    }
};
