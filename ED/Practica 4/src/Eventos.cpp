#include "Eventos.h"

#include <cassert>

#include <sstream>
// #include <iomanip>

using namespace std;


/* -------------- CONSTRUCTORES -------------- */

Evento::Evento(){
    this->dia = 1;
    this->mes = 1;
    this->anio = 1;
    this->descripcion = " ";
}


Evento::Evento(int dia, int mes, int anio, string descripcion){
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
    this->descripcion = descripcion;
}


Evento::Evento(const Evento& otroEvento){
    this->dia = otroEvento.dia;
    this->mes = otroEvento.mes;
    this->anio = otroEvento.anio;
    this->descripcion = otroEvento.descripcion;
}


/* -------------- METODOS -------------- */

bool Evento::comprobarFecha() const{
    if (this->anio <= 0) return false;
    
    if (this->mes < 1 || this->mes > 12) return false;
    
    if (this->dia < 1 || this->dia > 31) return false;
    
    return true;
}

string Evento::toString() const{
    string texto;

    texto += "Evento: " + this->descripcion;
    texto += "\n Fecha: " + to_string( this->dia ) + "/" + to_string( this->mes ) + "/" + to_string( this->anio ) + "\n" ;
    
    return texto;
    
}

bool Evento::operator<(const Evento& otroEvento) const{

    if (this->anio != otroEvento.anio) return this->anio < otroEvento.anio;
    if (this->mes  != otroEvento.mes)  return this->mes  < otroEvento.mes;
    return this->dia < otroEvento.dia;
}

bool Evento::operator==(const Evento& otroEvento) const{
    return (dia == otroEvento.dia && mes == otroEvento.mes && anio == otroEvento.anio);
}

/* -------------- SETTERS / GETTERS -------------- */

int Evento::getDia() const{
    return dia;
}

int Evento::getMes() const{
    return mes;
}

int Evento::getAnio() const{
    return anio;
}

string Evento::getDescripcion() const{
    return descripcion;
}


void Evento::setDia(int nuevoDia){
    this->dia = nuevoDia;
    assert(comprobarFecha());
}

void Evento::setMes(int nuevoMes){
    this->mes = nuevoMes;
    assert(comprobarFecha());
}

void Evento::setAnio(int nuevoAnio){
    this->anio = nuevoAnio;
    assert(comprobarFecha());
}

void Evento::setDescripcion(string nuevaDescripcion){
    this->descripcion = nuevaDescripcion;
}