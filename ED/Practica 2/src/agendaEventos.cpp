#include "agendaEventos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>
using namespace std;



/* ------------------ METODOS PRIVADOS ------------------ */
void AgendaEventos::redimensionar(int nueva_capacidad){
    Evento *eventosNuevo = new Evento[nueva_capacidad];
    
        for (int i = 0; i < this->num_eventos; i++) {
            eventosNuevo[i] = this->eventos[i];
        }

    delete[] this->eventos;

    this->eventos = eventosNuevo;
    this->capacidad = nueva_capacidad;
}


/* ------------------ CONSTRUCTOR / DESTRUCTOR ------------------ */

/* INICIAL */
AgendaEventos::AgendaEventos(int capacidad_base){
    
    this->num_eventos = 0;
    this->capacidad = capacidad_base;
    this->eventos = new Evento[this->capacidad];
    
}

/* CARGAR DESDE FICHERO */
AgendaEventos::AgendaEventos(string nombre_fichero){

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

    

    /* Va obteniendo cada línea de texto del fichero y crea un evento. */
    while (getline(file, linea)){

        stringstream campo(linea);

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


AgendaEventos::~AgendaEventos(){
    delete[] this->eventos;
}




/* ------------------ METODOS ------------------ */

bool AgendaEventos::agregarEvento(Evento nuevoEvento){
    
    if (this->num_eventos == this->capacidad) {
        this->redimensionar(this->capacidad + 1);
    }
    

    for(int i=0; i<this->num_eventos ; i++){

        if( this->eventos[i].eventoSolapado(nuevoEvento) ){
            return false;
        }
        
    }

    
    this->eventos[this->num_eventos] = nuevoEvento;
    this->num_eventos++;

    return true;

}

bool AgendaEventos::eliminarEvento(string nombreEvento){

    int indiceBorrar = -1;

    for(int i=0;i <this->num_eventos;i++){
        if(nombreEvento == this->eventos[i].getNombre()){
            indiceBorrar = i;
            break;
        }
    }

    if (indiceBorrar == -1) {
        return false;
    }

    this->eventos[indiceBorrar] = this->eventos[this->num_eventos - 1];
    this->num_eventos--;

    // this->redimensionar(capacidad-1);
    
    return true;
}

string AgendaEventos::buscarEventoPorNombre(string nombreEvento){

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

string AgendaEventos::buscarEventoPorDia(int diaBuscar){

    int encontrados = 0;
    string texto = " \n Evento Encontrado: \n\n ";

    for (int i = 0; i < this->num_eventos; i++){
        if( diaBuscar == this->eventos[i].getDia() ){
            encontrados++;
            texto += this->eventos[i].getNombre() + " | " + to_string( this->eventos[i].getDia()) + " | " + to_string( this->eventos[i].getHoraInicio()) + " - " + to_string( this->eventos[i].getHoraFin()) + " \n";
        }
    }

    if(encontrados == 0){
        return "Evento no encontrado.";
    }else{

        return texto;
    }

}

/* SE ORDENA MEDIANTE METODO DE BURBUJA */
string AgendaEventos::mostrarTodosLosEventos(){

    if (this->num_eventos == 0) {
        return "No hay eventos registrados.";
    }

    /* Nuevo array para meter los eventos ordenados. */
    Evento* copia = new Evento[this->num_eventos];
    
    for (int i = 0; i < this->num_eventos; i++) {
        copia[i] = this->eventos[i];
    }

    for (int i = 0; i < this->num_eventos - 1; i++) {

        for (int j = 0; j < this->num_eventos - 1 - i; j++) {

            bool desordenado = false;

            if (copia[j].getDia() > copia[j+1].getDia()) { /* Comprobacion dia */
                desordenado = true;
            }else if (copia[j].getDia() == copia[j+1].getDia() && copia[j].getHoraInicio() > copia[j+1].getHoraInicio()){ /* Comprobacion hora Inicio */
                desordenado = true;
            }

            if (desordenado) {
                Evento temp = copia[j];
                copia[j] = copia[j+1];
                copia[j+1] = temp;
            }

        }
    }

    string texto = "\n Lista de eventos (ordenados por día y hora): \n\n";

    for (int i = 0; i < this->num_eventos; i++) {
        texto += copia[i].getNombre() + " | " + to_string(copia[i].getDia()) + " | " + to_string(copia[i].getHoraInicio()) + " - " + to_string(copia[i].getHoraFin()) + "\n";
    }

    delete[] copia;
    return texto;

}

string AgendaEventos::detectarFranjasLibresPorDia(int diaBuscar){

    /* Comprobacion de día y numero de eventos*/

    if (diaBuscar < 1 || diaBuscar > 7) {
        return "Día no válido. Debe estar entre 1 y 7.";
    }
    
    int numEventosDia = 0;
    for (int i = 0; i < this->num_eventos; i++){
        if (this->eventos[i].getDia() == diaBuscar){
            numEventosDia++;
        }
    }
    if (numEventosDia == 0){
        return "Franjas libres para el día " + to_string(diaBuscar) + ":\n\n0.0 - 24.0\n";
    }

    // Array temporal
    Evento* eventosDia = new Evento[numEventosDia];
    int indice = 0;

    for (int i = 0; i < this->num_eventos; i++){
        if (this->eventos[i].getDia() == diaBuscar){
            eventosDia[indice] = this->eventos[i];
            indice++;
        }
    }

    // Ordenamos el array nuevo / (Podria crear la función para ordenar)
    for (int i = 0; i < numEventosDia - 1; i++){
        for (int j = 0; j < numEventosDia - 1 - i; j++){
            if (eventosDia[j].getHoraInicio() > eventosDia[j+1].getHoraInicio()){
                Evento temp = eventosDia[j];
                eventosDia[j] = eventosDia[j+1];
                eventosDia[j+1] = temp;
            }
        }
    }

    // Buscamos huecos libres
    string texto = "Franjas libres para el día " + to_string(diaBuscar) + ":\n\n";

    double inicio_libre = 0.0;
    bool hayLibres = false;

    for (int i = 0; i < numEventosDia; i++){

        double inicio_evento = eventosDia[i].getHoraInicio();
        double fin_evento    = eventosDia[i].getHoraFin();

        if (inicio_evento > inicio_libre){
            texto += to_string(inicio_libre) + " - " + to_string(inicio_evento) + "\n";
            hayLibres = true;
        }

        if (fin_evento > inicio_libre){
            inicio_libre = fin_evento;
        }
    }

    if (inicio_libre < 24.0){
        texto += to_string(inicio_libre) + " - 24.0\n"; /* Contamos que 24.0 / 0.0 = 00:00 */
        hayLibres = true;
    }

    delete[] eventosDia;

    if (!hayLibres){
        return "No hay franjas libres para el día " + to_string(diaBuscar) + ".\n";
    }

    return texto;
}

string AgendaEventos::resumenSemanal(){

    if (this->num_eventos == 0){
        return "No hay eventos en la agenda.\n";
    }

    string texto = "\n RESUMEN SEMANAL \n\n";
    int numEventosDia;
    double horasPorDia;

    for(int i = 1; i <= 7; i++){
        numEventosDia=0;
        horasPorDia = 0.00;

        for( int j = 0; j < this->num_eventos ; j++ ){
            if( this->eventos[j].getDia() == i ){
                numEventosDia++;
                horasPorDia += this->eventos[j].getHoraFin() - this->eventos[j].getHoraInicio();
            }
        }

        /* Se podría hacer un switch para el dia de la semana ( 1 - Lunes / 2 - Martes etc.) */

        string nombreDia;

        switch (i){
            case 1:{ nombreDia = "Lunes"; break; }
            case 2:{ nombreDia = "Martes"; break; }
            case 3:{ nombreDia = "Miercoles"; break; }
            case 4:{ nombreDia = "Jueves"; break; }
            case 5:{ nombreDia = "Viernes"; break; }
            case 6:{ nombreDia = "Sabado"; break; }
            case 7:{ nombreDia = "Domingo"; break; }
        }

        if(numEventosDia == 0){
            texto += nombreDia + ": No hay eventos este día";
        }else{
            texto += nombreDia + ": " + to_string(numEventosDia) + " Eventos | " + to_string(horasPorDia) + " horas \n"; 
        }

        

    }
    return texto;
}

bool AgendaEventos::guardarArchivo(){

    ofstream file("datos/agenda.txt");

    if (!file) {
        return false;  // no se pudo abrir
    }

    for (int i = 0; i < this->num_eventos; i++) {

        file << this->eventos[i].getNombre() << ","
            << this->eventos[i].getDia() << ","
            << this->eventos[i].getHoraInicio() << ","
            << this->eventos[i].getHoraFin();

        if (i < this->num_eventos - 1)
            file << "\n";
    }

    file.close();
    return true;
}



bool AgendaEventos::eventoExistente(Evento nuevoEvento){

    bool existe = false;
    
    for(int i = 0; i < this->num_eventos; i++){

        if(nuevoEvento.getNombre() == this->eventos[i].getNombre() ){
            existe = true;
        }

    }

    return existe;
}



/* ------------------ SETTERS / GETTERS ------------------ */

int AgendaEventos::getNumEventos(){
    return this->num_eventos;
}

int AgendaEventos::getCapacidad(){
    return this->capacidad;
}

void AgendaEventos::setNumEventos(int numEventos){
    this->num_eventos = numEventos;
}

void AgendaEventos::setCapacidad(int capacidad){
    this->capacidad = capacidad;
}




