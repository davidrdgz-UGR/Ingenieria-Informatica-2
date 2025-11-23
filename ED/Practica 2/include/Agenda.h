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

        AgendaEventos(int capacidad_inicial = 10);              /* INICIAL */
        AgendaEventos(string nombre_fichero);      /* CARGAR DESDE FICHERO */


        ~AgendaEventos();


        
        
        /* ------------------ METODOS ------------------ */






        /* ------------------ SETTERS / GETTERS ------------------ */







};