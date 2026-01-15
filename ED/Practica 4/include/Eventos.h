// #warning "USANDO include/evento.h DE PRACTICA 4"

#include <cassert>
#include <string>

using namespace std;


class Evento {

    private:
        int dia;            /* 1-31 */
        int mes;            /* 1-12 */
        int anio;           /*  */

        string descripcion;
    
    
    public:
        
        /* -------------- CONSTRUCTORES -------------- */

        Evento();   /* Por Defecto */
        Evento(int dia, int mes, int anio, string descripcion);

        Evento(const Evento& otroEvento); /* Copia */

        /* -------------- METODOS -------------- */

        bool comprobarFecha() const;

        string toString() const;

        /* Ambos funcionan por fechas */
        bool operator<(const Evento& otroEvento) const; 
        bool operator==(const Evento& otroEvento) const;

        /* -------------- SETTERS / GETTERS -------------- */

        int getDia() const;
        int getMes() const;
        int getAnio() const;
        string getDescripcion() const;
        
        void setDia(int nuevoDia);
        void setMes(int nuevoMes);
        void setAnio(int nuevoAnio);
        void setDescripcion(string nuevaDescripcion);

};