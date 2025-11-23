#include "Agenda.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>


using namespace std;

class AgendaEventos {

    private:
        Evento *eventos;   /* Array de eventos */
        
        int num_eventos;   
        int capacidad; 


        /* ------------------ METODOS PRIVADOS ------------------ */
        void redimensionar(int nueva_capacidad){
            Evento *eventosNuevo = new Evento[nueva_capacidad];
            
                for (int i = 0; i < this->num_eventos; i++) {
                    eventosNuevo[i] = this->eventos[i];
                }

            delete[] this->eventos;

            this->eventos = eventosNuevo;
            this->capacidad = nueva_capacidad;
        }
        
    public:
        
        /* ------------------ CONSTRUCTOR / DESTRUCTOR ------------------ */
        
        /* INICIAL */
        AgendaEventos(int capacidad_base = 1){
            
            this->eventos = nullptr;
            this->num_eventos = 0;
            this->capacidad = capacidad_base;
            
        }

        /* CARGAR DESDE FICHERO */
        AgendaEventos(string nombre_fichero){
            
        }


        ~AgendaEventos(){
            delete[] this->eventos;
        }


        
        
        /* ------------------ METODOS ------------------ */






        /* ------------------ SETTERS / GETTERS ------------------ */







};