#include "agendacontactos.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <string>

using namespace std;

/* -------------- CONSTRUCTOR -------------- */

AgendaContactos::AgendaContactos(const string& nombre_fichero) {
    cargar(nombre_fichero);
}


/* -------------- MÉTODOS -------------- */

bool AgendaContactos::insertarContacto(const Contacto& nuevoContacto) {

    pair<map<string, Contacto>::iterator, bool> haInsertado = this->listaContactos.insert({ nuevoContacto.getNombre(), nuevoContacto });
    
    const set<string>& etiquetasContacto = nuevoContacto.getEtiquetas();

    for (const string& etiqueta : etiquetasContacto) {
        
        this->etiquetas.insert({ etiqueta, nuevoContacto.getNombre() });
    }
    
    return haInsertado.second;
}

bool AgendaContactos::eliminarContacto(const string& borrarContacto){

}


bool AgendaContactos::existeContacto(const string& nombre) const{

}


const Contacto* AgendaContactos::buscarContacto(const string& nombre) const{

}

string AgendaContactos::contactosPorEtiqueta(const std::string& etiqueta) const{

}

string AgendaContactos::toString() const{

}

bool AgendaContactos::cargar(const string& nombre_fichero){

}


/* -------------- SETTERS / GETTERS -------------- */


const int AgendaContactos::getNumeroContactos() const{
    return this->listaContactos.size();
}


const string AgendaContactos::getEtiquetas() const{
    string resultado = "\n ETIQUETAS: ";

    for (const auto& Etiqueta : this->etiquetas) {
        resultado += "\n - " + Etiqueta.first;
    }

    return resultado;
}

