#include <iostream>
#include "AgendaContactos.h"

using namespace std;

void mostrarMenu() {
    cout << "\n\n====== AGENDA DE CONTACTOS ======\n";
    cout << "1. Mostrar agenda completa\n";
    cout << "2. Insertar nuevo contacto\n";
    cout << "3. Eliminar contacto\n";
    cout << "4. Buscar contacto por nombre\n";
    cout << "5. Comprobar si existe contacto\n";
    cout << "6. Buscar contactos por etiqueta\n";
    cout << "7. Guardar Archivo\n";
    cout << "8. Modificar Contacto\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

int leerOpcion() {
    int opcion;
    cin >> opcion;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada no valida. Introduce un numero: ";
        cin >> opcion;
    }

    cin.ignore(10000, '\n'); 
    return opcion;
}

int main(){
    
    AgendaContactos agenda("./datos/agendaContactos.txt");

    cout << "Agenda Actual: \n";
    cout << agenda.toString();

    int opcion = -1;

    do{
        
        mostrarMenu();    
        
        opcion = leerOpcion();

        switch(opcion){
            
            case 1:{
                cout << agenda.toString();
                break;
            }

            case 2:{
                string nombre;

                cout << "Nombre del contacto: ";
                getline(cin, nombre);

                Contacto nuevo(nombre);

                if (agenda.insertarContacto(nuevo))
                    cout << "Contacto insertado correctamente.\n";
                else
                    cout << "El contacto ya existe.\n";

                break;
            }

            case 3:{
                string nombre;
                cout << "Nombre del contacto a eliminar: ";
                cin >> nombre;

                if (agenda.eliminarContacto(nombre))
                    cout << "Contacto eliminado.\n";
                else
                    cout << "Contacto no encontrado.\n";

                break;
            }

            case 4:{
                string nombre;
                cout << "Nombre del contacto: ";
                cin >> nombre;


                const Contacto* c = agenda.buscarContacto(nombre);
                if (c != nullptr)
                    cout << c->toString() << endl;
                else
                    cout << "Contacto no encontrado.\n";

                break;
            }

            case 5:{
                string nombre;
                cout << "Nombre del contacto: ";
                cin >> nombre;

                if (agenda.existeContacto(nombre))
                    cout << "El contacto existe.\n";
                else
                    cout << "El contacto NO existe.\n";

                break;
            }

            case 6:{
                string etiqueta;
                cout << "Etiqueta: ";
                cin >> etiqueta;

                cout << agenda.contactosPorEtiqueta(etiqueta) << endl;
                break;
            }



            case 7:{
                
                if(agenda.guardar("./datos/agendaContactos.txt")){
                    cout << "\n Guardado Correctamente.";
                }else{
                    cout << "\n Fallo al guardar.";
                }
                break;

            }

            case 8:{

                string nombre;
                cout << "Nombre del contacto: ";
                cin >> nombre;

                if (!agenda.modificarContacto(nombre)) cout << "Contacto no encontrado.\n";

                break;

            }


            case 0:{
                cout << "Saliendo de la agenda...\n";
                break;
            }

            default: {
                cout << "Opcion no valida.\n";
                
            }
        }
        
    } while (opcion != 0);

    return 0;
}