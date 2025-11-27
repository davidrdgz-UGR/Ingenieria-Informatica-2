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

            this->capacidad = 1;       /* Agregamos una capacidad inicial, pero en agregar evento se redimensiona solo. */
            this->num_eventos = 0;
            this->eventos = new Evento[this->capacidad];


            /* Comprobacion de que el archivo existe/se encuentra */
            
            ifstream file(nombre_fichero);

            if (!file) {
                cout << "No existe el archivo ' " << nombre_fichero << " '" << endl;
                return;
            }


            string linea;

            stringstream campo(linea);

            /* Va obteniendo cada línea de texto del fichero y crea un evento. */
            while (getline(file, linea)){
                string nombre;
                string dia;
                string hora_inicio;
                string hora_fin;

                getline(campo, nombre, ',');
                getline(campo, dia, ',');
                getline(campo, hora_inicio, ',');
                getline(campo, hora_fin, ',');


                int dia_final = stoi(dia);
                double hora_inicio_final = stod(hora_inicio);
                double hora_fin_final = stod(hora_fin);

                Evento nuevoEvento(nombre, dia_final, hora_inicio_final, hora_fin_final);

                this->agregarEvento(nuevoEvento);
            }

            file.close();
            
        }


        ~AgendaEventos(){
            delete[] this->eventos;
        }


        
        
        /* ------------------ METODOS ------------------ */

        bool agregarEvento(Evento nuevoEvento){
            
            if (this->num_eventos == this->capacidad) {
                this->redimensionar(this->capacidad + 1);
            }
            

            for(int i=0; i<this->num_eventos ; i++){

                if( this->eventos[i].eventoSolapado(nuevoEvento) ){
                    return false;
                }
                
            }

            
            this->eventos[this->num_eventos+1] = nuevoEvento;
            this->num_eventos++;

            return true;

        }

        bool eliminarEvento(string nombreEvento){

            int indiceBorrar;

            for(int i=0;i= this->num_eventos;i++){
                if(nombreEvento == this->eventos[i].getNombre()){
                    indiceBorrar = i;
                    break;
                }
            }

                if (indiceBorrar) {
                    return false;
                }

            this->eventos[indiceBorrar] = this->eventos[this->num_eventos - 1];
            this->num_eventos--;

            // this->redimensionar(capacidad-1);
            
            return true;
        }

        string buscarEventoPorNombre(string nombreEvento){

            bool encontrado = false;
            Evento objetoEncontrado;

            for (int i = 0; i < this->num_eventos; i++){
                if( nombreEvento == this->eventos[i].getNombre() ){
                    objetoEncontrado = this->eventos[i];
                    encontrado = true;
                    break;
                }
            }

            if(!encontrado){
                return "Evento no encontrado.";
            }
            
            string texto = " \n Evento Encontrado: \n\n " + objetoEncontrado.getNombre() + " | " + to_string( objetoEncontrado.getDia()) + " | " + to_string( objetoEncontrado.getHoraInicio()) + " - " + to_string( objetoEncontrado.getHoraFin());

            return texto;

        }

        string buscarEventoPorDia(int diaBuscar){

            int encontrados = 0;
            string texto;

            for (int i = 0; i < this->num_eventos; i++){
                if( diaBuscar == this->eventos[i].getDia() ){
                    encontrados++;
                    texto += " \n Evento Encontrado: \n\n " + this->eventos[i].getNombre() + " | " + to_string( this->eventos[i].getDia()) + " | " + to_string( this->eventos[i].getHoraInicio()) + " - " + to_string( this->eventos[i].getHoraFin()) + " \n";
                }
            }

            if(encontrados == 0){
                return "Evento no encontrado.";
            }else{

                return texto;
            }

        }




        /* ------------------ SETTERS / GETTERS ------------------ */







};