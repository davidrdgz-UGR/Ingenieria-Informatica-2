#include "contactos.h"

#include <iostream>
// #include <cassert>
#include <iosfwd>
#include <sstream>

#include <string>

#include <set>
#include <map>

using namespace std;


/* -------------- CONSTRUCTOR -------------- */

Contacto::Contacto(string nombreContacto){

    this->nombre = nombreContacto;

    this->preguntarConstructor();
    
}

/* SOLO SE USA AL USAR CARGAR ARCHIVO */
Contacto::Contacto(){
    this->nombre = "";

}



/* -------------- MÉTODOS -------------- */

/* Hacen falta los metodos tiene, set no crea duplicados ?¿?¿?¿?¿?¿?¿ */

bool Contacto::añadirTelefono(const string& numTelefono){
    return this->telefonos.insert(numTelefono).second;
}

bool Contacto::borrarTelefono(const string& numTelefono){
    return this->telefonos.erase(numTelefono) > 0;
}

/* bool Contacto::tieneEsteTelefono(const string& numTelefono) const{
    return ( this->telefonos.find(numTelefono) != this->telefonos.end() );
} */



bool Contacto::añadirCorreo(const string& nuevoCorreo){
    return this->correos.insert(nuevoCorreo).second;
}

bool Contacto::borrarCorreo(const string& correoBorrar){
    return this->correos.erase(correoBorrar) > 0;

}

/* bool Contacto::tieneEsteCorreo(const string& correoBuscar) const{
    return ( this->correos.find(correoBuscar) != this->correos.end() );
} */




bool Contacto::añadirEtiqueta(const string& nuevaEtiqueta){
    return this->etiquetas.insert(nuevaEtiqueta).second;

}

bool Contacto::borrarEtiqueta(const string& etiquetaBorrar){
    return this->etiquetas.erase(etiquetaBorrar) > 0;

}

/* bool Contacto::tieneEsteEtiqueta(const string& etiquetaBuscar) const{
    return ( this->etiquetas.find(etiquetaBuscar) != this->etiquetas.end() );
} */


void Contacto::preguntarConstructor(){
    
    int cantidadTelefonos,cantidadCorreos,cantidadEtiquetas;

    string añadirTelefono,añadirCorreo,añadirEtiquetas;

    cout << "\n Cuantos telefonos tiene? ";
    cin >> cantidadTelefonos;

    cout << "\n Escribe el numero de los telefonos:";
    for(int i = 0; i<cantidadTelefonos; i++){
        
        cout << "\n" + to_string(i) + ": ";
        cin >> añadirTelefono;

        this->añadirTelefono(añadirTelefono);
    }


    cout << "\n Cuantos correos tiene?";
    cin >> cantidadCorreos;

    cout << "\n Escribe el nombre de los correos:";
    for(int i = 0; i<cantidadCorreos; i++){
        
        cout << "\n" + to_string(i) + ": ";
        cin >> añadirCorreo;

        this->añadirCorreo(añadirCorreo);
    }


        
    cout << "\n Cuantas etiquetas tiene?";
    cin >> cantidadEtiquetas;

    cout << "\n Escribe las etiquetas: ";
    for(int i = 0; i<cantidadEtiquetas; i++){
    
        cout << "\n" + to_string(i) + ": ";
        cin >> añadirEtiquetas;

        this->añadirEtiqueta(añadirEtiquetas);
    }


}

string Contacto::toString() const {
    /* los foreach usan ya cons_iterator/begin/end por defecto ?¿ */
    string texto;

    texto = " Contacto: " + nombre;

    texto += "\n Telefonos: ";
    if (telefonos.empty()) {
        texto += "No tiene telefonos";
    } else {
        for (const auto& telefono : telefonos) {
            texto += telefono + "  ";
        }
    }

    texto += "\n Correos: ";
    if (correos.empty()) {
        texto += "No tiene correos";
    } else {
        for (const auto& correo : correos) {
            texto += correo + "  ";
        }
    }

    texto += "\n Etiquetas: ";
    if (etiquetas.empty()) {
        texto += "No tiene etiquetas";
    } else {
        for (const auto& etiqueta : etiquetas) {
            texto += etiqueta + "  ";
        }
    }

    return texto;
}


/* -------------- SETTERS / GETTERS -------------- */

const string& Contacto::getNombre() const{
    return this->nombre;
}

const set<string>& Contacto::getTelefonos() const{
    return this->telefonos;
}

const set<string>& Contacto::getCorreos() const{
    return this->correos;
}

const set<string>& Contacto::getEtiquetas() const{
    return this->etiquetas;
}


void Contacto::setNombre( string nuevoNombre){
    this->nombre = nuevoNombre;
}