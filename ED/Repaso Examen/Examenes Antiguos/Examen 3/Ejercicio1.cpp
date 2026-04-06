
/* 

4. (2 puntos) Dado un árbol binario de búsqueda con interfaz:
    
    template <class T>
    
    class ABB {
        public:
            ABB();
            ABB(T valor);
            Arbol(const ABB<T> & a);
            ~ABB();
            bool inserter (T valor);
            bool borrar(T valor);
            void vaciar();
            int numNodos() const;
            bool estaVacio() const;
            ABB<T> & operator = (const ABB<T> &a);
    };

a) (0,75 punto) Implementa la función de búsqueda de manera recursiva. Utiliza las
propiedades de los ABB para optimizar la búsqueda. Explica brevemente cómo funciona
tu implementación.

b) (0,75 puntos) Implementa la función de búsqueda de manera iterativa. Explica
brevemente cómo funciona tu implementación.

c) (0,5 puntos) Compara ambas implementaciones en términos de ventajas y desventajas.

*/

#include <iostream>

using namespace std;

template <class T>
    
class ABB {
    public:

        struct Nodo {
            T key;
            Nodo* izq;
            Nodo* der;
            Nodo(const T& k) : key(k), izq(nullptr), der(nullptr) {}
        };
        Nodo* raiz;

        ABB();
        ABB(T valor);
        Arbol(const ABB<T> & a);
        ~ABB();
        bool inserter (T valor);
        bool borrar(T valor);
        void vaciar();
        int numNodos() const;
        bool estaVacio() const;
        ABB<T> & operator = (const ABB<T> &a);


        /* n será el nodo raiz y x el valor a buscar */
        int busquedaBinaria(Nodo* n,const T& x) const{

            if (n == nullptr) return -1;

            if (x == n->key) return 0;

            if (x < n->key)  return busquedaBinaria(n->izq, x);

            if (x > n->key)  return busquedaBinaria(n->der, x);
            
        }

        template <class T>
        
        bool ABB<T>::buscarIter(const T& x) const {
            /* En vez de usar recursividad o pila de llamadas, usamos un puntero y un while */
            Nodo* n = raiz;

            while (n != nullptr) {

                if (x == n->key) return true;
                if (x < n->key) n = n->izq;
                else            n = n->der;
            }

            return false;
        }

        /* 
        
        c)
        
        Ambos  tienen el mismo orden de crecimiento, que tiende a ser O(log n)

        A al usar recursividad puede que consuma más recursos, mientras que B al usar punteros es mas
        segura y sobrecarga menos.
        
        */
};