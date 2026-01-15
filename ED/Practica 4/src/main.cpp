#include "AgendaEvento.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std; 


static bool leerEventoDeLinea(const string& linea, Evento& outEvento){
    istringstream iss(linea);

    int dia, mes, anio;
    if (!(iss >> dia >> mes >> anio)) {
        return false; // línea inválida o vacía
    }

    string descripcion;
    getline(iss, descripcion);

    if (!descripcion.empty() && descripcion[0] == ' ') descripcion.erase(0, 1);

    outEvento = Evento(dia, mes, anio, descripcion);
    return true;
}

int main(int argc, char* argv[]){

    string ruta = "datos/agendaEventos.txt";
    if (argc >= 2) {
        ruta = argv[1];
    }

    ifstream fin(ruta);
    if (!fin) {
        cerr << "No se pudo abrir el fichero '" << ruta << "'\n";
        return 1;
    }

    AgendaEvento agenda;

    string linea;
    int numLeidas = 0;
    int numInsertadas = 0;

    while (getline(fin, linea)) {
        // Saltar líneas vacías
        if (linea.size() == 0) continue;

        Evento ev;
        if (!leerEventoDeLinea(linea, ev)) {
            cerr << "línea inválida ignorada: " << linea << "\n";
            continue;
        }

        numLeidas++;

        if (agenda.insertar(ev, true)) {
            numInsertadas++;
        }
    }

    fin.close();

    cout << "Eventos leidos: " << numLeidas << "\n";
    cout << "Eventos insertados: " << numInsertadas << "\n";
    cout << "Nodos en el arbol: " << agenda.numNodos() << "\n";
    cout << "Altura del arbol: " << agenda.alturaArbol() << "\n\n";

    cout << "--- Eventos en orden cronologico --- \n";

    AgendaEvento::Iterador it = agenda.iterador();
    while (it.tieneSiguiente()) {
        Evento ev = it.siguienteEvento();
        cout << ev.toString() << "\n";
    }

    return 0;
}