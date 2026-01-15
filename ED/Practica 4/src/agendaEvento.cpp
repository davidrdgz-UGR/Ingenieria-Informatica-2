#include "AgendaEvento.h"

#include <cassert>
#include <string>

using namespace std;



/* ---------------- Parte Recursiva ----------------  */

AgendaEvento::Nodo* AgendaEvento::clonarNodo(const Nodo* nodo){
    if (nodo == nullptr) return nullptr;

    Nodo* nuevo = new Nodo(nodo->evento);
    nuevo->HijoIzq = clonarNodo(nodo->HijoIzq);
    nuevo->HijoDer = clonarNodo(nodo->HijoDer);
    return nuevo;
}


void AgendaEvento::liberarNodo(Nodo* nodo){
    if (nodo == nullptr) return;

    liberarNodo(nodo->HijoIzq);
    liberarNodo(nodo->HijoDer);
    delete nodo;
}


bool AgendaEvento::insertarNodo(Nodo*& nodo, const Evento& evento, bool actualizarSiExiste){
    if (nodo == nullptr) {
        nodo = new Nodo(evento);
        return true;
    }

    if (evento < nodo->evento) {
        return insertarNodo(nodo->HijoIzq, evento, actualizarSiExiste);
    }
    else if (nodo->evento < evento) {
        return insertarNodo(nodo->HijoDer, evento, actualizarSiExiste);
    }
    else {

        if (actualizarSiExiste) {
            nodo->evento.setDescripcion( evento.getDescripcion() );
            return true;
        }
        return false;
    }
}

AgendaEvento::Nodo* AgendaEvento::buscarNodo(Nodo* nodo, const Evento& clave) const{
    if (nodo == nullptr) return nullptr;

    if (clave == nodo->evento) return nodo;

    if (clave < nodo->evento)
        return buscarNodo(nodo->HijoIzq, clave);

    return buscarNodo(nodo->HijoDer, clave);
}

int AgendaEvento::alturaNodo(Nodo* nodo) const{
    if (nodo == nullptr) return 0;

    int hi = alturaNodo(nodo->HijoIzq);
    int hd = alturaNodo(nodo->HijoDer);

    return 1 + (hi > hd ? hi : hd);
}


int AgendaEvento::cantidadNodos(Nodo* nodo) const{
    if (nodo == nullptr) return 0;
    return 1 + cantidadNodos(nodo->HijoIzq) + cantidadNodos(nodo->HijoDer);
}



/* ----------------  Parte Pública ----------------  */

/* ----------------  CONSTRUCTOR / DESTRUCTOR ----------------  */

AgendaEvento::AgendaEvento(){
    this->raiz = nullptr;
}

AgendaEvento::AgendaEvento(const AgendaEvento& otraAgenda){
    this->raiz = clonarNodo(otraAgenda.raiz);
}


AgendaEvento& AgendaEvento::operator=(const AgendaEvento& otraAgenda){
    if (this == &otraAgenda) return *this;

    liberarNodo(this->raiz);
    this->raiz = nullptr;

    this->raiz = clonarNodo(otraAgenda.raiz);

    return *this;
}

AgendaEvento::~AgendaEvento(){
    liberarNodo(this->raiz);
    this->raiz = nullptr;
}


/* ----------------  METODOS ----------------  */


bool AgendaEvento::insertar(const Evento& nuevoEvento, bool actualizarSiExiste){
    return insertarNodo(this->raiz, nuevoEvento, actualizarSiExiste);
}

bool AgendaEvento::existe(const Evento& clave) const{
    return (buscarNodo(this->raiz, clave) != nullptr);
}

bool AgendaEvento::obtener(const Evento& clave, Evento& out) const{
    Nodo* n = buscarNodo(this->raiz, clave);
    if (n == nullptr) return false;

    out = n->evento;
    return true;
}


int AgendaEvento::alturaArbol() const{
    return alturaNodo(this->raiz);
}

int AgendaEvento::numNodos() const{
    return cantidadNodos(this->raiz);
}

bool AgendaEvento::estaVacia() const{
    return (this->raiz == nullptr);
}



/* ---------------- Parte ITERADOR ----------------  */


void AgendaEvento::Iterador::push(Nodo* nodo){
    pila = new PilaNodo(nodo, pila);
}

AgendaEvento::Nodo* AgendaEvento::Iterador::pop(){
    if (pila == nullptr) return nullptr;

    PilaNodo* top = pila;
    Nodo* n = top->nodo;

    pila = top->sig;
    delete top;

    return n;
}

void AgendaEvento::Iterador::bajarIzquierda(Nodo* nodo){
    Nodo* cur = nodo;
    while (cur != nullptr) {
        push(cur);
        cur = cur->HijoIzq;
    }
}

/* ---------------- Constructores Iterador ----------------   */

AgendaEvento::Iterador::Iterador(){
    this->actual = nullptr;
    this->pila = nullptr;
}

AgendaEvento::Iterador::Iterador(Nodo* raiz){
    this->actual = nullptr;
    this->pila = nullptr;

    bajarIzquierda(raiz);
}


AgendaEvento::Iterador::Iterador(const Iterador& otroIterador){
    int count = 0;
    for (PilaNodo* p = otroIterador.pila; p != nullptr; p = p->sig) count++;

    Nodo** arr = nullptr;
    if (count > 0) arr = new Nodo*[count];

    int i = count - 1;
    for (PilaNodo* p = otroIterador.pila; p != nullptr; p = p->sig) {
        arr[i--] = p->nodo;
    }

    this->pila = nullptr;
    for (int k = 0; k < count; k++) {
        this->pila = new PilaNodo(arr[k], this->pila);
    }

    delete[] arr;

    this->actual = otroIterador.actual;
}

AgendaEvento::Iterador::~Iterador(){
    while (pila != nullptr) {
        PilaNodo* tmp = pila;
        pila = pila->sig;
        delete tmp;
    }
    actual = nullptr;
}

/* Sobrecarga de =  */
AgendaEvento::Iterador& AgendaEvento::Iterador::operator=(const Iterador& iterador){
    if (this == &iterador) return *this;

    // liberar mi pila
    while (this->pila != nullptr) {
        PilaNodo* tmp = this->pila;
        this->pila = this->pila->sig;
        delete tmp;
    }

    // copiar pila del otro 
    int count = 0;
    for (PilaNodo* p = iterador.pila; p != nullptr; p = p->sig) count++;

    Nodo** arr = nullptr;
    if (count > 0) arr = new Nodo*[count];

    int i = count - 1;
    for (PilaNodo* p = iterador.pila; p != nullptr; p = p->sig) {
        arr[i--] = p->nodo;
    }

    this->pila = nullptr;
    for (int k = 0; k < count; k++) {
        this->pila = new PilaNodo(arr[k], this->pila);
    }

    delete[] arr;

    this->actual = iterador.actual;

    return *this;
}

/* ---------------- Metodos Iterador ---------------- */

bool AgendaEvento::Iterador::tieneSiguiente() const{
    return (pila != nullptr);
}

Evento AgendaEvento::Iterador::siguienteEvento(){
    Nodo* nodo = pop();
    actual = nodo;

    if (nodo != nullptr && nodo->HijoDer != nullptr) {
        bajarIzquierda(nodo->HijoDer);
    }

    return nodo->evento;
}

AgendaEvento::Iterador AgendaEvento::iterador() const{
    return Iterador(this->raiz);
}