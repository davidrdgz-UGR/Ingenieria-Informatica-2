
#include "contactos.h"

#include <string>
#include <set>
#include <map>

using namespace std;

/**
 * @brief TDA AgendaContactos.
 *
 * Gestiona un conjunto de contactos identificados por su nombre y permite
 * buscar contactos por etiquetas.
 *
 * La estructura principal es un map (nombre -> Contacto) y se mantiene un
 * índice auxiliar con un multimap (etiqueta -> nombreContacto) para obtener
 * rápidamente los contactos asociados a una etiqueta.
 *
 * Invariante de representación:
 * - listaContactos asocia cada nombre con un Contacto válido.
 * - etiquetas contiene pares (etiqueta, nombre) coherentes con las etiquetas
 *   almacenadas en los Contactos de listaContactos.
 *
 * Función de abstracción:
 * - El objeto AgendaContactos representa una agenda de contactos donde cada
 *   contacto tiene teléfonos, correos y etiquetas, y es accesible por su nombre.
 */
class AgendaContactos {

private:
    /** @brief Contenedor principal: nombre -> Contacto. */
    map<string, Contacto> listaContactos;

    /** @brief Índice por etiquetas: etiqueta -> nombreContacto. */
    multimap<string, string> etiquetas;

public:
    /* -------------- CONSTRUCTOR -------------- */

    /**
     * @brief Constructor que crea la agenda cargándola desde un fichero.
     *
     * El fichero debe tener una línea por contacto con el formato:
     * nombre|tel1,tel2|correo1,correo2|et1,et2
     *
     * @param nombre_fichero Ruta del fichero a cargar.
     */
    AgendaContactos(const string& nombre_fichero);

    /* -------------- MÉTODOS -------------- */

    /**
     * @brief Inserta un contacto en la agenda.
     *
     * Si ya existe un contacto con el mismo nombre, no se inserta.
     * Si se inserta correctamente, actualiza el índice de etiquetas.
     *
     * @param nuevoContacto Contacto a insertar.
     * @return true si se inserta, false si ya existía.
     */
    bool insertarContacto(const Contacto& nuevoContacto);

    /**
     * @brief Elimina un contacto por nombre.
     *
     * Si el contacto existe, se elimina del contenedor principal y se eliminan
     * también sus referencias del índice de etiquetas.
     *
     * @param borrarContacto Nombre del contacto a eliminar.
     * @return true si se elimina, false si no existe.
     */
    bool eliminarContacto(const string& borrarContacto);

    /**
     * @brief Comprueba si existe un contacto con un nombre dado.
     *
     * @param nombre Nombre a comprobar.
     * @return true si existe, false en caso contrario.
     */
    bool existeContacto(const string& nombre) const;

    /**
     * @brief Busca un contacto por nombre.
     *
     * @param nombre Nombre del contacto.
     * @return Puntero constante al contacto si existe, nullptr si no existe.
     */
    const Contacto* buscarContacto(const string& nombre) const;

    /**
     * @brief Devuelve en formato texto los contactos asociados a una etiqueta.
     *
     * Se apoya en el índice multimap (etiqueta -> nombreContacto) para obtener
     * la lista de contactos asociados.
     *
     * @param etiqueta Etiqueta a buscar.
     * @return Cadena con los contactos que tienen esa etiqueta.
     */
    string contactosPorEtiqueta(const string& etiqueta) const;

    /**
     * @brief Devuelve una representación textual de toda la agenda.
     *
     * Muestra todos los contactos almacenados con sus datos.
     *
     * @return Cadena con la agenda completa.
     */
    string toString() const;

    /**
     * @brief Modifica un contacto existente mediante un submenú interactivo.
     *
     * Permite añadir/borrar teléfonos, correos y etiquetas. Cuando se modifican
     * etiquetas, el índice multimap se actualiza para mantener coherencia.
     *
     * @param nombre Nombre del contacto a modificar.
     * @return true si existe y se modifica, false si no existe.
     */
    bool modificarContacto(const string& nombre);

    /**
     * @brief Carga la agenda desde un fichero.
     *
     * Vacía la agenda actual y carga los contactos del fichero con el formato:
     * nombre|tel1,tel2|correo1,correo2|et1,et2
     *
     * @param nombre_fichero Ruta del fichero.
     * @return true si se carga correctamente, false si no se puede abrir o hay error.
     */
    bool cargar(const string& nombre_fichero);

    /**
     * @brief Guarda la agenda en un fichero.
     *
     * Genera un fichero con una línea por contacto en el formato:
     * nombre|tel1,tel2|correo1,correo2|et1,et2
     *
     * @param nombre_fichero Ruta del fichero de salida.
     * @return true si se guarda correctamente, false si no se puede abrir.
     */
    bool guardar(const string& nombre_fichero) const;

    /* -------------- SETTERS / GETTERS -------------- */

    /**
     * @brief Devuelve el número de contactos almacenados.
     *
     * @return Número de contactos.
     */
    int getNumeroContactos() const;

    /**
     * @brief Devuelve un listado textual de las etiquetas existentes.
     *
     * Recorre el índice de etiquetas y construye un texto con las claves.
     *
     * @return Cadena con las etiquetas.
     */
    string getEtiquetas() const;
};

