#include <iostream>
#include <string>
// #include "../include/agendaEventos.h"  /* No hace falta, se incluye en el makefile */
#include "agendaEventos.h"

#include <limits>  /* Libreria útil para comprobaciones. */

using namespace std;



void mostrarMenu() {
    cout << "\n========= AGENDA DE EVENTOS =========\n";
    cout << "1. Mostrar todos los eventos\n";
    cout << "2. Buscar evento por nombre\n";
    cout << "3. Buscar eventos por dia\n";
    cout << "4. Agregar nuevo evento\n";
    cout << "5. Eliminar evento por nombre\n";
    cout << "6. Detectar franjas libres en un dia\n";
    cout << "7. Mostrar resumen semanal\n";
    cout << "8. Guardar Agenda\n";
    cout << "0. Salir\n\n";
    cout << "Seleccione una opcion: ";
}

int main(){
    
    AgendaEventos agenda("datos/agenda.txt");

    int opcion = -1;

    while (opcion != 0){
        mostrarMenu();

        cin >> opcion;

        /* REVISAR SWITCH PARA COMPROBACIONES (cin sobretodo) */
        switch (opcion){
            case 1: {
                cout << agenda.mostrarTodosLosEventos() << endl;
                break;
            }

            case 2: {
                
                string nombre;
                
                cout << "Introduce el nombre del evento a buscar: ";

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                getline(cin, nombre);

                cout << agenda.buscarEventoPorNombre(nombre) << endl;
                break;
            }

            case 3: {
                int dia;
                
                cout << "Introduce el dia a buscar (1-7): ";
                cin >> dia;
                
                string resultado = agenda.buscarEventoPorDia(dia);
                cout << resultado << endl;
                break;
            }

            case 4: {
                string nombre;
                int dia;
                double horaInicio, horaFin;

                cout << "Nombre del evento: ";
                cin >> nombre;

                cout << "Dia de la semana (1-7): ";
                cin >> dia;

                cout << "Hora de inicio (formato decimal, ej. 9.5 = 9:30): ";
                cin >> horaInicio;

                cout << "Hora de fin (formato decimal, ej. 11.0): ";
                cin >> horaFin;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                
                Evento nuevo(nombre, dia, horaInicio, horaFin);

                if (agenda.agregarEvento(nuevo)) {
                    cout << "Evento agregado correctamente.\n";
                } else {
                    cout << "No se ha podido agregar el evento: hay solapamiento con otro existente.\n";
                }
                

                break;
            }

            case 5: {
                string nombre;
                
                cout << "Introduce el nombre del evento a eliminar: ";
                cin >> nombre;

                if ( agenda.eliminarEvento(nombre) ) {
                    cout << "Evento eliminado correctamente.\n";
                } else {
                    cout << "No se ha encontrado ningun evento con ese nombre.\n";
                }

                break;
            }

            case 6: {
                int dia;
                
                cout << "Introduce el dia (1-7) para ver las franjas libres: ";
                cin >> dia;

                cout << agenda.detectarFranjasLibresPorDia(dia) << endl;

                break;
            }

            case 7: {
                cout << agenda.resumenSemanal() << endl;
                break;
            }

            case 8: {
                cout << "Guardando Agenda en 'agenda.txt' ";

                if (agenda.guardarArchivo()) {
                    cout << "Archivo guardado correctamente.\n";
                } else {
                    cout << "Error: no se pudo guardar el archivo.\n";
                }

                break;
            }

            case 0:
                agenda.~AgendaEventos();
                cout << "\n Saliendo del programa. \n";
                break;
        
        default:
            cout << "\n Opción no válida. \n";
            break;
        }
    }
    


}