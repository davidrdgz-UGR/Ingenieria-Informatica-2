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

    /* Comprobacion de que existe. */
    

    if ( this->existeContacto(borrarContacto) ) {
        return false;
    }

    /* Buscamos etiquetas y borramos */
    for (auto i = etiquetas.begin(); i != etiquetas.end(); ) {
        if (i->second == borrarContacto) {
            i = etiquetas.erase(i);   
        } else {
            ++i;
        }
    }

    /* Borramos el contacto */
    listaContactos.erase(borrarContacto);

    return true;
}


bool AgendaContactos::existeContacto(const string& nombre) const{
    return ( listaContactos.find(nombre) != listaContactos.end() );
}


const Contacto* AgendaContactos::buscarContacto(const string& nombre) const{
    auto contactoMap = listaContactos.find(nombre);

    if (contactoMap == listaContactos.end()) {
        return nullptr;
    }

    return &(contactoMap->second);
}

string AgendaContactos::contactosPorEtiqueta(const std::string& etiqueta) const{
    
    string resultado = "\n Contactos con la etiqueta '" + etiqueta + "':\n";
    
    auto rango = etiquetas.equal_range(etiqueta);

    /* Significaria que las dos partes del multimap están vacias. */
    if (rango.first == rango.second) {
        return "No hay contactos con la etiqueta '" + etiqueta + "'.";
    }

    for (auto it = rango.first; it != rango.second; ++it) {
        resultado += " - " + it->second + "\n";
    }

    return resultado;
}

string AgendaContactos::toString() const{
    if (listaContactos.empty()) {
        return "Agenda vacia.";
    }

    string resultado = "\n AGENDA DE CONTACTOS \n";

    for (const auto& par : listaContactos) {
        resultado += "\n----------------------\n";
        resultado += par.second.toString();
    }

    return resultado;
}

bool AgendaContactos::modificarContacto(const string& nombre) {

    auto it = listaContactos.find(nombre);
    if (it == listaContactos.end()) return false;

    Contacto& contactoModificar = it->second;

    int operacion = -1;

    while (operacion != 0) {
        cout << "\n\n--- MODIFICAR CONTACTO ---\n";
        cout << contactoModificar.toString() << "\n";
        cout << "1. Añadir telefono\n";
        cout << "2. Borrar telefono\n";
        cout << "3. Añadir correo\n";
        cout << "4. Borrar correo\n";
        cout << "5. Añadir etiqueta\n";
        cout << "6. Borrar etiqueta\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> operacion;
        cin.ignore(10000, '\n');

        string dato;

        switch (operacion) {
            case 1:
                cout << "Telefono a añadir: ";
                cin >> dato;
                cout << (contactoModificar.añadirTelefono(dato) ? "Añadido\n" : "Ya existia\n");
                break;

            case 2:
                cout << "Telefono a borrar: ";
                cin >> dato;
                cout << (contactoModificar.borrarTelefono(dato) ? "Borrado\n" : "No existia\n");
                break;

            case 3:
                cout << "Correo a añadir: ";
                cin >> dato;
                cout << (contactoModificar.añadirCorreo(dato) ? "Añadido\n" : "Ya existia\n");
                break;

            case 4:
                cout << "Correo a borrar: ";
                cin >> dato;
                cout << (contactoModificar.borrarCorreo(dato) ? "Borrado\n" : "No existia\n");
                break;

            case 5:
                cout << "Etiqueta a añadir: ";
                cin >> dato;

                if (contactoModificar.añadirEtiqueta(dato)) {
                    etiquetas.insert({dato, nombre});   
                    cout << "Añadida\n";
                } else {
                    cout << "Ya existia\n";
                }
                break;

            case 6:
                cout << "Etiqueta a borrar: ";
                cin >> dato;
                
                if (contactoModificar.borrarEtiqueta(dato)) {
                    auto rango = etiquetas.equal_range(dato);
                    for (auto mit = rango.first; mit != rango.second; ) {
                        if (mit->second == nombre) mit = etiquetas.erase(mit);
                        else ++mit;
                    }
                    cout << "Borrada\n";
                } else {
                    cout << "No existia\n";
                }
                break;

            case 0:
                break;

            default:
                cout << "Opcion no valida\n";
        }
    }

    return true;
}


bool AgendaContactos::cargar(const string& nombre_fichero){

    ifstream fichero(nombre_fichero);
    if (!fichero) return false;

    // Si hiciese falta limpiar la Agenda
    // listaContactos.clear();
    // etiquetas.clear();

    string linea;
    
    while (getline(fichero, linea)) {
        
        string nombre, telefonos, correos, tags;
        stringstream ss(linea);

        getline(ss, nombre, '|');
        getline(ss, telefonos, '|');
        getline(ss, correos, '|');
        getline(ss, tags, '|');

        Contacto nuevoContacto = Contacto();

        nuevoContacto.setNombre(nombre);

        string dato;
        
        stringstream ssTel(telefonos);
        while ( getline(ssTel, dato, ',' )) {
            if (!dato.empty()) nuevoContacto.añadirTelefono(dato);
        }

        stringstream ssCor(correos);
        while (getline(ssCor, dato, ',')) {
            if (!dato.empty()) nuevoContacto.añadirCorreo(dato);
        }


        stringstream ssTag(tags);
        while (getline(ssTag, dato, ',')) {
            if (!dato.empty()) nuevoContacto.añadirEtiqueta(dato);
            
        }

        if( !this->insertarContacto(nuevoContacto) ){
            return false;
        }
    }

    return true;
}

bool AgendaContactos::guardar(const string& nombre_fichero ) const{

    ofstream fichero(nombre_fichero);
    if (!fichero) return false;

    for (auto it = listaContactos.begin(); it != listaContactos.end(); ++it) {

        const Contacto& c = it->second;

        // Nombre
        fichero << c.getNombre() << "|";

        // Telefonos
        const set<string>& telefonos = c.getTelefonos();
        for (auto itTel = telefonos.begin(); itTel != telefonos.end(); ++itTel) {
            fichero << *itTel;
            auto sig = itTel;
            ++sig;
            if (sig != telefonos.end()) fichero << ",";
        }
        fichero << "|";

        // Correos
        const set<string>& correos = c.getCorreos();
        for (auto itCor = correos.begin(); itCor != correos.end(); ++itCor) {
            fichero << *itCor;
            auto sig = itCor;
            ++sig;
            if (sig != correos.end()) fichero << ",";
        }
        fichero << "|";

        // Etiquetas
        const set<string>& etiquetasContacto = c.getEtiquetas();
        for (auto itEt = etiquetasContacto.begin(); itEt != etiquetasContacto.end(); ++itEt) {
            fichero << *itEt;
            auto sig = itEt;
            ++sig;
            if (sig != etiquetasContacto.end()) fichero << ",";
        }

        // Salto de línea salvo último (opcional)
        fichero << "\n";
    }

    return true;
}


/* -------------- SETTERS / GETTERS -------------- */


const int AgendaContactos::getNumeroContactos() const{
    return this->listaContactos.size();
}


const string AgendaContactos::getEtiquetas() const{
    string resultado = "\n ETIQUETAS: ";

    for (const auto& Etiqueta : this->etiquetas) {
        resultado += "\n - " + Etiqueta.first + " - " + Etiqueta.second;
    }

    return resultado;
}

