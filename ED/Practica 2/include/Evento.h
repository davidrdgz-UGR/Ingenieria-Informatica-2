#include <cassert>
#include <string>

using namespace std;


class Evento {
    
    private:
        string nombre;
        int dia;    /* Dia de la semana 1-7 */              
        double hora_inicio;      
        double hora_fin;         

    public:
        
        /* ------------------ CONSTRUCTOR ------------------ */
        Evento();
        Evento(string nombre, int dia, double hora_inicio, double hora_fin);


        /* ------------------ METODOS ------------------ */

        bool eventoSolapado(Evento &otroEvento);

        string mostrarInfo();

        
        string compaarEventos(Evento otroEvento); 

        bool eventoExistente();


        /* ------------------ SETTERS / GETTERS ------------------ */

        string getNombre();
        int getDia();
        double getHoraInicio();
        double getHoraFin();

        void setNombre(string nuevoNombre);
        void setDia(int nuevoDia);
        void setHoraInicio(double nuevaHoraInicio);
        void setHoraFin(double nuevaHoraFin);

};