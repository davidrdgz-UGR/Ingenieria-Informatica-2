#include <cassert>
#include <string>

using namespace std;


/**
 * @brief TDA Evento.
 *
 * Representa un suceso asociado a una fecha (día/mes/año) y una descripción textual.
 * Se usa como elemento almacenado en el ABB (AgendaEvento), ordenándose cronológicamente
 * mediante el operador < (por fecha).
 *
 * Invariante (validación básica):
 *  - 1 <= mes <= 12
 *  - 1 <= dia <= 31
 *  - anio > 0 (según criterio del proyecto)
 */
class Evento {

    private:
        int dia;            /* 1-31 */
        int mes;            /* 1-12 */
        int anio;           /*  */

        string descripcion;
    
    
    public:
        
        /* -------------- CONSTRUCTORES -------------- */

        /**
         * @brief Constructor por defecto.
         * @post El evento queda inicializado con una fecha válida básica y descripción vacía.
         */
        Evento();   /* Por Defecto */

        /**
         * @brief Constructor con parámetros.
         * @param dia Día del mes (1..31).
         * @param mes Mes del año (1..12).
         * @param anio Año (>0).
         * @param descripcion Texto descriptivo del evento.
         * @pre Los parámetros deben representar una fecha válida (al menos a nivel básico).
         * @post El evento queda inicializado con la fecha y descripción proporcionadas.
         */
        Evento(int dia, int mes, int anio, string descripcion);

        /**
         * @brief Constructor de copia.
         * @param otroEvento Evento a copiar.
         * @post El nuevo evento contiene la misma fecha y descripción que otroEvento.
         */
        Evento(const Evento& otroEvento); /* Copia */

        /* -------------- METODOS -------------- */

        /**
         * @brief Comprueba si la fecha almacenada es válida (validación básica).
         * @return true si (anio>0, 1<=mes<=12, 1<=dia<=31), false en caso contrario.
         */
        bool comprobarFecha() const;

        /**
         * @brief Devuelve una representación en texto del evento.
         * @return Cadena con formato "dd/mm/aaaa descripcion".
         */
        string toString() const;

        /* Ambos funcionan por fechas */

        /**
         * @brief Comparación cronológica estricta por fecha.
         * @param otroEvento Evento con el que comparar.
         * @return true si *this es anterior a otroEvento (por fecha), false en caso contrario.
         */
        bool operator<(const Evento& otroEvento) const; 

        /**
         * @brief Igualdad por fecha.
         * @param otroEvento Evento con el que comparar.
         * @return true si ambos eventos tienen la misma fecha (día, mes y año).
         */
        bool operator==(const Evento& otroEvento) const;

        /* -------------- SETTERS / GETTERS -------------- */

        /**
         * @brief Obtiene el día del evento.
         * @return Día (1..31).
         */
        int getDia() const;

        /**
         * @brief Obtiene el mes del evento.
         * @return Mes (1..12).
         */
        int getMes() const;

        /**
         * @brief Obtiene el año del evento.
         * @return Año (>0).
         */
        int getAnio() const;

        /**
         * @brief Obtiene la descripción del evento.
         * @return Descripción del evento.
         */
        string getDescripcion() const;
        
        /**
         * @brief Establece el día del evento.
         * @param nuevoDia Nuevo día.
         * @post El día pasa a ser nuevoDia (se espera que la fecha siga siendo válida).
         */
        void setDia(int nuevoDia);

        /**
         * @brief Establece el mes del evento.
         * @param nuevoMes Nuevo mes.
         * @post El mes pasa a ser nuevoMes (se espera que la fecha siga siendo válida).
         */
        void setMes(int nuevoMes);

        /**
         * @brief Establece el año del evento.
         * @param nuevoAnio Nuevo año.
         * @post El año pasa a ser nuevoAnio (se espera que la fecha siga siendo válida).
         */
        void setAnio(int nuevoAnio);

        /**
         * @brief Establece la descripción del evento.
         * @param nuevaDescripcion Nueva descripción.
         * @post La descripción pasa a ser nuevaDescripcion.
         */
        void setDescripcion(string nuevaDescripcion);

};
