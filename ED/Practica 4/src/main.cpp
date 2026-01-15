#include "AgendaEvento.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std; 

/**
 * @brief Lee y parsea una línea de texto con un evento.
 *
 * Formato esperado por línea:
 *   dia mes anio descripcion...
 * Ejemplo:
 *   12 10 2025 Examen de Estructura de Datos
 *
 * @param linea Línea completa del fichero.
 * @param outEvento Evento de salida (se rellena si el parseo es correcto).
 * @return true si la línea contiene un evento válido a nivel de formato, false si no.
 */
static bool leerEventoDeLinea(const string& linea, Evento& outEvento){
    istringstream iss(linea);

    int dia, mes, anio;
    if (!(iss >> dia >> mes >> anio)) {
        return false; // línea inválida o vacía
    }

    string descripcion;
    getline(iss, descripcion);

    // Elimina el espacio inicial típico tras leer anio y luego hacer getline
    if (!descripcion.empty() && descripcion[0] == ' ') descripcion.erase(0, 1);

    outEvento = Evento(dia, mes, anio, descripcion);
    return true;
}

/**
 * @brief Programa principal de la práctica.
 *
 * - Lee un fichero de eventos (por defecto: "datos/agendaEventos.txt").
 * - Inserta cada evento en un ABB (AgendaEvento) ordenado por fecha.
 * - Muestra información estructural del árbol (nº nodos y altura).
 * - Recorre y muestra los eventos en orden cronológico usando un iterador inorden.
 *
 * Uso:
 *   practica4.exe [ruta_fichero]
 *
 * Si se proporciona ruta por argumento, se utilizará en lugar de la ruta por defecto.
 *
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos (argv[1] puede contener la ruta del fichero).
 * @return 0 si finaliza correctamente, 1 si no se puede abrir el fichero.
 */
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

        // Inserta el evento; si ya existe esa fecha, se actualiza (actualizarSiExiste = true)
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

    // Recorrido ordenado mediante iterador inorden
    AgendaEvento::Iterador it = agenda.iterador();
    while (it.tieneSiguiente()) {
        Evento ev = it.siguienteEvento();
        cout << ev.toString() << "\n";
    }

    return 0;
}
