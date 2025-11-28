#include <iostream>
#include <string>
#include "Agenda.h"

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
    cout << "0. Salir\n\n";
    cout << "Seleccione una opcion: ";
}