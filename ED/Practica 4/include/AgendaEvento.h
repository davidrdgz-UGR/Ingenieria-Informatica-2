#include "Eventos.h"

#include <cassert>
#include <string>

using namespace std;


/**
 * @brief TDA AgendaEvento basado en un Árbol Binario de Búsqueda (ABB) de eventos.
 *
 * Almacena objetos Evento ordenados cronológicamente (según Evento::operator<).
 * El árbol mantiene la propiedad del ABB:
 *  - Subárbol izquierdo: eventos "menores" (anteriores)
 *  - Subárbol derecho:  eventos "mayores" (posteriores)
 *
 * Permite insertar, buscar, obtener información estructural (altura, número de nodos)
 * y recorrer en orden mediante un iterador inorden.
 */
class AgendaEvento{

    private:

        /* Estructura Nodo como en el temario. -> Abstraccion */
        /**
         * @brief Nodo (celda) del ABB.
         *
         * Representa la estructura enlazada interna del árbol: cada nodo contiene un Evento
         * y dos punteros a sus hijos (izquierdo y derecho).
         */
        struct Nodo {
            Evento evento;
            Nodo* HijoIzq;
            Nodo* HijoDer;

            /* Constructor Nodo */
            /**
             * @brief Constructor de Nodo.
             * @param evento Evento que se almacenará en el nodo.
             * @post HijoIzq y HijoDer quedan a nullptr.
             */
            Nodo(const Evento& evento){
                this->evento = evento;
               
                this->HijoIzq = nullptr ;
                this->HijoDer = nullptr ;
            }
        };
        
        /** @brief Puntero a la raíz del árbol (nullptr si el árbol está vacío). */
        Nodo* raiz;

        /* Funciones Recursivas */

        /**
         * @brief Clona recursivamente un subárbol.
         * @param nodo Raíz del subárbol a clonar.
         * @return Puntero a la raíz del nuevo subárbol clonado (copia profunda).
         */
        Nodo* clonarNodo(const Nodo* nodo);

        /**
         * @brief Libera recursivamente la memoria de un subárbol.
         * @param nodo Raíz del subárbol a liberar.
         * @post El subárbol queda liberado (se eliminan todos sus nodos).
         */
        void liberarNodo(Nodo* nodo);

        /**
         * @brief Inserta recursivamente un Evento en el ABB.
         * @param nodo Referencia al puntero del nodo actual (permite crear nodos).
         * @param evento Evento a insertar.
         * @param actualizarSiExiste Si ya existe un evento con la misma fecha, indica si se actualiza.
         * @return true si se insertó (o actualizó), false si no se modificó el árbol.
         */
        bool insertarNodo( Nodo*& nodo, const Evento& evento, bool actualizarSiExiste);
        
        /**
         * @brief Busca recursivamente un Evento (por clave/fecha) en el ABB.
         * @param nodo Nodo actual desde el que se busca.
         * @param clave Evento “clave” (normalmente solo interesa la fecha).
         * @return Puntero al Nodo encontrado, o nullptr si no existe.
         */
        Nodo* buscarNodo(Nodo* nodo, const Evento& clave) const;

        /**
         * @brief Calcula la altura de un subárbol.
         * @param nodo Raíz del subárbol.
         * @return Altura del subárbol (0 si nodo es nullptr).
         */
        int alturaNodo(Nodo* nodo) const;

        /**
         * @brief Cuenta el número de nodos de un subárbol.
         * @param nodo Raíz del subárbol.
         * @return Número de nodos (0 si nodo es nullptr).
         */
        int cantidadNodos(Nodo* nodo) const;

    
    public:

        /* -------------- ITERADOR --------------  */


        /* El iterador se declara dentro de la clase -> Abstraccion */
        /**
         * @brief Iterador inorden para recorrer el árbol en orden cronológico.
         *
         * Implementa un recorrido inorden (izq, nodo, der) usando una pila enlazada propia,
         * sin STL, para devolver los eventos de menor a mayor fecha.
         */
        class Iterador{
            private:

                /**
                 * @brief Nodo de la pila interna del iterador.
                 *
                 * Cada elemento almacena un puntero a un Nodo del árbol y el siguiente elemento
                 * de la pila.
                 */
                struct PilaNodo {
                    Nodo* nodo;
                    PilaNodo* sig;
                    
                    /**
                     * @brief Constructor de PilaNodo.
                     * @param nodo Puntero a nodo del árbol.
                     * @param sig Siguiente elemento de la pila.
                     */
                    PilaNodo(Nodo* nodo, PilaNodo* sig){
                        this->nodo = nodo;
                        this->sig = sig;
                    }
                };

                /** @brief Puntero auxiliar al nodo “actual” (puede no usarse). */
                Nodo* actual; /* Puede que no se use, no es obligatorio con pila */

                /** @brief Puntero al tope de la pila del iterador. */
                PilaNodo* pila;
                    
                /**
                 * @brief Inserta un nodo del árbol en la pila (push).
                 * @param nodo Nodo del árbol a apilar.
                 */
                void push(Nodo* nodo);

                /**
                 * @brief Extrae el nodo superior de la pila (pop).
                 * @return Puntero al Nodo del árbol extraído, o nullptr si la pila está vacía.
                 */
                Nodo* pop();

                /**
                 * @brief Apila el camino hacia el nodo más a la izquierda desde un nodo dado.
                 * @param nodo Nodo desde el que empezar a bajar por la izquierda.
                 */
                void bajarIzquierda(Nodo* nodo);
                // void bajarDerecha(Nodo* nodo);


            public:

                /** @brief Constructor por defecto (iterador vacío). */
                Iterador();

                /**
                 * @brief Constructor que inicializa el iterador desde la raíz del árbol.
                 * @param raiz Raíz del árbol a recorrer.
                 * @post El iterador queda posicionado para devolver el primer elemento en inorden.
                 */
                explicit Iterador(Nodo* raiz);

                /**
                 * @brief Constructor de copia del iterador.
                 * @param otroIterador Iterador a copiar.
                 */
                Iterador(const Iterador& otroIterador);

                /**
                 * @brief Operador de asignación del iterador.
                 * @param iterador Iterador fuente.
                 * @return Referencia a *this.
                 */
                Iterador& operator=(const Iterador& iterador);

                /** @brief Destructor. Libera la pila interna del iterador. */
                ~Iterador();

                /**
                 * @brief Indica si quedan eventos por recorrer.
                 * @return true si existe un siguiente evento, false en caso contrario.
                 */
                bool tieneSiguiente() const;

                /**
                 * @brief Devuelve el siguiente Evento en orden cronológico (inorden).
                 * @return Evento siguiente.
                 * @pre tieneSiguiente() == true.
                 */
                Evento siguienteEvento(); // devuelve el siguiente Evento en orden cronológico
            
        };
        
        /**
         * @brief Crea un iterador para recorrer el árbol en orden cronológico.
         * @return Iterador inicializado con la raíz del árbol.
         */
        Iterador iterador() const;
        



        /* -------------- CONSTRUCTORES / DESTRUCTOR -------------- */

        /** @brief Constructor por defecto. Crea un árbol vacío. */
        AgendaEvento();

        /**
         * @brief Constructor de copia (copia profunda del árbol).
         * @param otraAgenda AgendaEvento a copiar.
         */
        AgendaEvento(const AgendaEvento& otraAgenda);

        /**
         * @brief Operador de asignación (copia profunda).
         * @param otraAgenda AgendaEvento fuente.
         * @return Referencia a *this.
         */
        AgendaEvento& operator=(const AgendaEvento& otraAgenda); 

        /** @brief Destructor. Libera toda la memoria del árbol. */
        ~AgendaEvento();


        /* -------------- METODOS -------------- */

        /**
         * @brief Inserta un evento en el ABB.
         * @param nuevoEvento Evento a insertar.
         * @param actualizarSiExiste Si ya existe un evento con la misma fecha, indica si se actualiza.
         * @return true si se insertó o actualizó, false si no se modificó el árbol.
         */
        bool insertar(const Evento& nuevoEvento, bool actualizarSiExiste = true);

        /**
         * @brief Comprueba si existe un evento con la clave indicada.
         * @param clave Evento “clave” (normalmente solo interesa la fecha).
         * @return true si existe, false si no.
         */
        bool existe(const Evento& clave) const;

        /**
         * @brief Obtiene el evento asociado a una clave.
         * @param clave Evento “clave” (normalmente solo interesa la fecha).
         * @param out Evento de salida (se rellena si se encuentra).
         * @return true si se encontró, false en caso contrario.
         */
        bool obtener(const Evento& clave, Evento& out) const;


        /**
         * @brief Devuelve la altura del árbol.
         * @return Altura del árbol (0 si está vacío).
         */
        int alturaArbol() const;   

        /**
         * @brief Devuelve el número total de nodos del árbol.
         * @return Número de nodos.
         */
        int numNodos() const;     

        /**
         * @brief Indica si el árbol está vacío.
         * @return true si no hay nodos, false en caso contrario.
         */
        bool estaVacia() const;

};
