#include <cassert>
#include <string>

using namespace std;

/**
 * @brief Tipo de dato que representa un evento.
 *
 * Un Evento contiene:
 *  - un nombre (string)
 *  - un día de la semana (1-7)
 *  - una hora de inicio en formato decimal (0.0 - 24.0)
 *  - una hora de fin en formato decimal (0.0 - 24.0)
 *
 * Invariante de representación:
 *  - 1 <= dia <= 7
 *  - 0.0 <= hora_inicio < hora_fin <= 24.0
 *
 * Función de abstracción:
 *  El objeto Evento representa el intervalo de tiempo
 *  [hora_inicio, hora_fin] del día 'dia', dedicado a la actividad
 *  identificada por 'nombre'.
 */
class Evento {
    
private:
    string nombre;        ///< Nombre del evento
    int dia;              ///< Día de la semana (1-7)
    double hora_inicio;   ///< Hora de inicio en formato decimal
    double hora_fin;      ///< Hora de fin en formato decimal

public:

    /* ------------------ CONSTRUCTORES ------------------ */

    /**
     * @brief Constructor por defecto.
     *
     * Crea un evento genérico en el día 1 entre 0.0 y 1.0.
     */
    Evento();

    /**
     * @brief Constructor parametrizado.
     *
     * @param nombre Nombre del evento.
     * @param dia Día de la semana (1-7).
     * @param hora_inicio Hora de inicio (0.0 - 24.0).
     * @param hora_fin Hora de fin (0.0 - 24.0, > hora_inicio).
     *
     * Lanza una aserción si los valores no cumplen el invariante.
     */
    Evento(string nombre, int dia, double hora_inicio, double hora_fin);


    /* ------------------ METODOS ------------------ */

    /**
     * @brief Indica si dos eventos se solapan en el tiempo.
     *
     * Dos eventos se solapan únicamente si:
     *   - ocurren el mismo día
     *   - la franja horaria se superpone estrictamente
     *
     * @param otroEvento Evento con el que se compara.
     * @return true si las franjas se solapan, false en caso contrario.
     */
    bool eventoSolapado(Evento &otroEvento);

    /**
     * @brief Devuelve un string con la información del evento.
     *
     * Incluye nombre, día y horario.
     *
     * @return Descripción textual del evento.
     */
    string mostrarInfo();


    /* ------------------ SETTERS / GETTERS ------------------ */

    /** @brief Obtiene el nombre del evento. */
    string getNombre();

    /** @brief Obtiene el día de la semana (1-7). */
    int getDia();

    /** @brief Obtiene la hora de inicio. */
    double getHoraInicio();

    /** @brief Obtiene la hora de finalización. */
    double getHoraFin();

    
    /** @brief Modifica el nombre del evento. */
    void setNombre(string nuevoNombre);
    
    /**
     * @brief Modifica el día del evento.
     *
     * Debe cumplir 1 <= nuevoDia <= 7.
     */
    void setDia(int nuevoDia);
    
    /**
     * @brief Modifica la hora de inicio.
     *
     * Debe cumplir 0.0 <= nuevaHoraInicio < hora_fin.
     */
    void setHoraInicio(double nuevaHoraInicio);
    
    /**
     * @brief Modifica la hora de finalización.
     *
     * Debe cumplir hora_inicio < nuevaHoraFin <= 24.0.
     */
    void setHoraFin(double nuevaHoraFin);
};
