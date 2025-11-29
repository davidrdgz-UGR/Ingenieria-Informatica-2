#include "Evento.h"
#include <string>

using namespace std;

/**
 * @brief TDA AgendaEventos.
 *
 * La agenda gestiona un conjunto dinámico de eventos mediante
 * un array dinámico redimensionable.
 *
 * Invariante de representación:
 *  - 0 <= num_eventos <= capacidad
 *  - 'eventos' apunta a un array válido de tamaño 'capacidad'
 *  - Las primeras 'num_eventos' posiciones contienen eventos válidos
 *
 * Función de abstracción:
 *  La agenda representa el conjunto:
 *     { eventos[0], ..., eventos[num_eventos-1] }.
 */
class AgendaEventos {

    private:
        /// Array dinámico de eventos
        Evento *eventos;
        
        /// Número actual de eventos almacenados
        int num_eventos;

        /// Capacidad actual del array dinámico
        int capacidad; 

        /* ------------------ METODOS PRIVADOS ------------------ */

        /**
         * @brief Redimensiona el array dinámico de eventos.
         *
         * Copia los eventos existentes a un nuevo array de tamaño
         * @p nueva_capacidad y libera la memoria anterior.
         *
         * @param nueva_capacidad Nueva capacidad del array (>= num_eventos).
         */
        void redimensionar(int nueva_capacidad);
        
    public:
        
        /* ------------------ CONSTRUCTOR / DESTRUCTOR ------------------ */

        /**
         * @brief Constructor con capacidad inicial.
         *
         * Reserva memoria para un array de eventos con capacidad
         * @p capacidad_inicial y deja la agenda vacía.
         *
         * @param capacidad_inicial Capacidad inicial del array (por defecto, 3).
         */
        AgendaEventos(int capacidad_inicial = 3);

        /**
         * @brief Constructor que carga los eventos desde un fichero de texto.
         *
         * El fichero debe tener un evento por línea con el formato:
         *  nombre,dia,hora_inicio,hora_fin
         *
         * @param nombre_fichero Ruta del fichero de entrada.
         */
        AgendaEventos(string nombre_fichero);

        /**
         * @brief Destructor.
         *
         * Libera la memoria dinámica asociada al array de eventos.
         */
        ~AgendaEventos();
        
        /* ------------------ METODOS ------------------ */

        /**
         * @brief Añade un nuevo evento a la agenda.
         *
         * Antes de insertar comprueba que el evento no se solapa en
         * el tiempo con ninguno de los ya existentes. Si el array
         * está lleno, se redimensiona.
         *
         * @param nuevoEvento Evento que se desea añadir.
         * @return true si se ha insertado correctamente, false si hay solapamiento.
         */
        bool agregarEvento(Evento nuevoEvento);

        /**
         * @brief Elimina un evento por su nombre.
         *
         * Si encuentra un evento con el nombre @p nombreEvento,
         * lo elimina sustituyéndolo por el último evento del array
         * y decrementa @c num_eventos.
         *
         * @param nombreEvento Nombre del evento a eliminar.
         * @return true si se elimina algún evento, false si no se encuentra.
         */
        bool eliminarEvento(string nombreEvento);

        /**
         * @brief Busca un evento por su nombre.
         *
         * Recorre la agenda en busca de un evento cuyo nombre coincida
         * exactamente con @p nombreEvento.
         *
         * @param nombreEvento Nombre del evento a buscar.
         * @return Cadena con la información del evento encontrado o
         *         "Evento no encontrado." si no existe.
         */
        string buscarEventoPorNombre(string nombreEvento);

        /**
         * @brief Busca todos los eventos de un día concreto.
         *
         * @param diaBuscar Día de la semana (1-7).
         * @return Cadena con la lista de eventos de ese día o
         *         "Evento no encontrado." si no hay ninguno.
         */
        string buscarEventoPorDia(int diaBuscar);

        /**
         * @brief Muestra todos los eventos ordenados por día y hora.
         *
         * Devuelve un string con todos los eventos ordenados primero por
         * día de la semana y, en caso de empate, por hora de inicio.
         *
         * @return Cadena con la lista de eventos ordenados o un mensaje
         *         indicando que no hay eventos.
         */
        string mostrarTodosLosEventos();

        /**
         * @brief Detecta las franjas horarias libres de un día.
         *
         * Construye las franjas libres en [0.0, 24.0) teniendo en cuenta
         * los eventos existentes del día @p diaBuscar.
         *
         * @param diaBuscar Día de la semana (1-7).
         * @return Cadena con las franjas libres o un mensaje si no hay huecos.
         */
        string detectarFranjasLibresPorDia(int diaBuscar);

        /**
         * @brief Genera un resumen semanal de la agenda.
         *
         * Para cada día de la semana indica el número de eventos
         * y el total de horas ocupadas.
         *
         * @return Cadena con el resumen semanal o un mensaje si no hay eventos.
         */
        string resumenSemanal();

        /**
         * @brief Guarda el contenido actual de la agenda en un fichero de texto.
         *
         * El fichero generado tendrá el mismo formato que el usado en el
         * constructor desde fichero:
         *  nombre,dia,hora_inicio,hora_fin
         *
         * @return true si el fichero se guarda correctamente, false en caso de error.
         */
        bool guardarArchivo();
        
        /**
         * @brief Comprueba si existe ya un evento con el mismo nombre.
         *
         * @param nuevoEvento Evento que se desea comprobar.
         * @return true si hay un evento con el mismo nombre, false en caso contrario.
         */
        bool eventoExistente(Evento nuevoEvento);

        /* ------------------ SETTERS / GETTERS ------------------ */

        /**
         * @brief Devuelve el número de eventos almacenados.
         * @return Número actual de eventos en la agenda.
         */
        int getNumEventos();

        /**
         * @brief Devuelve la capacidad actual del array de eventos.
         * @return Capacidad del array dinámico.
         */
        int getCapacidad();

        /**
         * @brief Establece manualmente el número de eventos.
         *
         * @param numEventos Nuevo valor de @c num_eventos.
         */
        void setNumEventos(int numEventos);

        /**
         * @brief Establece la capacidad de la agenda.
         *
         * No realiza redimensionamiento; solo modifica el valor del atributo.
         *
         * @param capacidad Nueva capacidad lógica de la agenda.
         */
        void setCapacidad(int capacidad);
};
