#include "Evento.h"
#include <cassert>
#include <string>

using namespace std;

/* ------------------ CONSTRUCTOR ------------------ */

/* Provisional y revisar */
Evento::Evento(){
    this->nombre = "";
    this->dia = 1;
    this->hora_inicio = 0.0;
    this->hora_fin = 1.0;
}

Evento::Evento(string nombre, int dia, double hora_inicio, double hora_fin){
    this->nombre = nombre;
    this->dia = dia;
    this->hora_inicio = hora_inicio;
    this->hora_fin = hora_fin;
    
    assert(dia >= 1 && dia <= 7);
    assert(hora_inicio >= 0.0 && hora_inicio < 24.0);
    assert(hora_fin > hora_inicio && hora_fin <= 24.0);
}


/* ------------------ METODOS ------------------ */

/* Se podría añadir como static y ser un método de clase ?¿ */
bool Evento::eventoSolapado(Evento &otroEvento){
    /* No se si se tienen que cambiar los getters, en principio no, son publicos y los atributos privados. */

    if(this->dia == otroEvento.getDia() ){

        if(this->hora_fin < otroEvento.getHoraInicio() || otroEvento.getHoraFin() < this->hora_inicio ){
            
            return true;
            // return "CUIDADO: Hay Solapamiento de horario entre: "+ this->nombre + " y " + otroEvento.getNombre();
        }

        return false;
        // return "Se solapan los días pero no hay problema.";
    }

    return false;
    // return "No se solapand"; /* Temporal, se cambia */
}

string Evento::mostrarInfo(){
    string info = "Información de Evento \n\n";

    info += "Nombre: "+ this->nombre + "\n";
    info += "Dia: "+ to_string( this->dia ) + "\n";
    info += "Hora Inicio: "+ to_string( this->hora_inicio ) + "\n";
    info += "Hora Fin: "+ to_string( this->hora_fin ) + "\n\n";

    return info;

}

/* string static compararEventos(int cantidadEventos,Evento arrayEventos[]){
    for (int i = 0; i < cantidadEventos; i++){
        for (int j = 0; j < cantidadEventos; j++){

            if( arrayEventos[j].getNombre().compare(arrayEventos[j+1].getNombre()) > 0 ){
                
                Evento tmp = arrayEventos[j];
                arrayEventos[j] = arrayEventos[j+1];
                arrayEventos[j+1] = tmp;
            }
            
        }
        
    }
    
} */


/* ------------------ SETTERS / GETTERS ------------------ */

string Evento::getNombre() {
    return this->nombre;
}

int Evento::getDia() {
    return this->dia;
}

double Evento::getHoraInicio() {
    return this->hora_inicio;
}

double Evento::getHoraFin() {
    return this->hora_fin;
}




void Evento::setNombre(string nuevoNombre) {
    this->nombre = nuevoNombre;
}

void Evento::setDia(int nuevoDia) {
    assert(nuevoDia >= 1 && nuevoDia <= 7);
    this->dia = nuevoDia;
}

void Evento::setHoraInicio(double nuevaHoraInicio) {
    assert(nuevaHoraInicio >= 0.0 && nuevaHoraInicio < hora_fin);
    this->hora_inicio = nuevaHoraInicio;
}

void Evento::setHoraFin(double nuevaHoraFin) {
    assert(nuevaHoraFin > hora_inicio && nuevaHoraFin <= 24.0);
    this->hora_fin = nuevaHoraFin;
}