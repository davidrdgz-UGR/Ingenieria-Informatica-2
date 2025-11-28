#include "Evento.h"
#include <string>

using namespace std;

class AgendaEventos {

    private:
        Evento *eventos;   /* Array de eventos */
        
        int num_eventos;   
        int capacidad; 


        /* ------------------ METODOS PRIVADOS ------------------ */
        void redimensionar(int nueva_capacidad);
        
    public:
        
        /* ------------------ CONSTRUCTOR / DESTRUCTOR ------------------ */

        AgendaEventos(int capacidad_inicial = 3);              /* INICIAL */
        AgendaEventos(string nombre_fichero);      /* CARGAR DESDE FICHERO */

        ~AgendaEventos();
        
        /* ------------------ METODOS ------------------ */

        bool agregarEvento(Evento nuevoEvento);

        bool eliminarEvento(string nombreEvento);

        string buscarEventoPorNombre(string nombreEvento);

        string buscarEventoPorDia(int diaBuscar);

        string mostrarTodosLosEventos();

        string detectarFranjasLibresPorDia(int diaBuscar);

        string resumenSemanal();

        bool guardarArchivo();
        
        bool eventoExistente(Evento nuevoEvento);

        /* ------------------ SETTERS / GETTERS ------------------ */


        int getNumEventos();

        int getCapacidad();

        void setNumEventos(int numEventos);

        void setCapacidad(int capacidad);




};