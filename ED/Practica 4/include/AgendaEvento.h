#include "Eventos.h"

#include <cassert>
#include <string>

using namespace std;


class AgendaEvento{

    private:

        /* Estructura Nodo como en el temario. -> Abstraccion */
        struct Nodo {
            Evento evento;
            Nodo* HijoIzq;
            Nodo* HijoDer;

            /* Constructor Nodo */
            Nodo(const Evento& evento){
                this->evento = evento;
               
                this->HijoIzq = nullptr ;
                this->HijoDer = nullptr ;
            }
        };
        
        Nodo* raiz;

        /* Funciones Recursivas */

        Nodo* clonarNodo(const Nodo* nodo);

        void liberarNodo(Nodo* nodo);
        bool insertarNodo( Nodo*& nodo, const Evento& evento, bool actualizarSiExiste);
        
        Nodo* buscarNodo(Nodo* nodo, const Evento& clave) const;

        int alturaNodo(Nodo* nodo) const;
        int cantidadNodos(Nodo* nodo) const;

    
    public:

        /* -------------- ITERADOR --------------  */


        /* El iterador se declara dentro de la clase -> Abstraccion */
        class Iterador{
            private:

                struct PilaNodo {
                    Nodo* nodo;
                    PilaNodo* sig;
                    
                    PilaNodo(Nodo* nodo, PilaNodo* sig){
                        this->nodo = nodo;
                        this->sig = sig;
                    }
                };

                Nodo* actual; /* Puede que no se use, no es obligatorio con pila */

                PilaNodo* pila;
                    
                void push(Nodo* nodo);
                Nodo* pop();

                void bajarIzquierda(Nodo* nodo);
                // void bajarDerecha(Nodo* nodo);


            public:

                Iterador();
                explicit Iterador(Nodo* raiz);

                Iterador(const Iterador& otroIterador);
                Iterador& operator=(const Iterador& iterador);

                ~Iterador();

                bool tieneSiguiente() const;
                Evento siguienteEvento(); // devuelve el siguiente Evento en orden cronológico
            
        };
        
        Iterador iterador() const;
        



        /* -------------- CONSTRUCTORES / DESTRUCTOR -------------- */

        AgendaEvento();
        AgendaEvento(const AgendaEvento& otraAgenda);
        AgendaEvento& operator=(const AgendaEvento& otraAgenda); 
        ~AgendaEvento();


        /* -------------- METODOS -------------- */

        bool insertar(const Evento& nuevoEvento, bool actualizarSiExiste = true);
        bool existe(const Evento& clave) const;
        bool obtener(const Evento& clave, Evento& out) const;


        int alturaArbol() const;   
        int numNodos() const;     
        bool estaVacia() const;

};