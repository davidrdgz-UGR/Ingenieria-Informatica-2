#ifndef CONTACTOS_H
#define CONTACTOS_H

#include <string>
#include <set>

using namespace std;

/**
 * @brief TDA Contacto.
 *
 * Representa un contacto de una agenda identificado por un nombre
 * y que contiene un conjunto de teléfonos, correos electrónicos
 * y etiquetas asociadas.
 *
 * Invariante de representación:
 * - El nombre identifica de forma única al contacto.
 * - No existen teléfonos duplicados.
 * - No existen correos duplicados.
 * - No existen etiquetas duplicadas.
 *
 * Función de abstracción:
 * - El objeto Contacto representa a una persona con un nombre y
 *   varios datos de contacto (teléfonos, correos y etiquetas).
 */
class Contacto {

private:
    /** @brief Nombre del contacto. */
    string nombre;

    /** @brief Conjunto de teléfonos del contacto. */
    set<string> telefonos;

    /** @brief Conjunto de correos electrónicos del contacto. */
    set<string> correos;

    /** @brief Conjunto de etiquetas asociadas al contacto. */
    set<string> etiquetas;

public:
    /* -------------- CONSTRUCTORES -------------- */

    /**
     * @brief Constructor con nombre.
     *
     * Crea un contacto con el nombre indicado.
     *
     * @param nombreContacto Nombre del contacto.
     */
    Contacto(string nombreContacto);

    /**
     * @brief Constructor por defecto.
     *
     * Crea un contacto vacío. Se utiliza principalmente
     * al cargar contactos desde fichero.
     */
    Contacto();

    /* -------------- MÉTODOS -------------- */

    /**
     * @brief Añade un teléfono al contacto.
     *
     * @param numTelefono Teléfono a añadir.
     * @return true si se añade correctamente, false si ya existía.
     */
    bool añadirTelefono(const string& numTelefono);

    /**
     * @brief Elimina un teléfono del contacto.
     *
     * @param numTelefono Teléfono a eliminar.
     * @return true si se elimina, false si no existía.
     */
    bool borrarTelefono(const string& numTelefono);

    /**
     * @brief Comprueba si el contacto tiene un teléfono concreto.
     *
     * @param numTelefono Teléfono a comprobar.
     * @return true si existe, false en caso contrario.
     */
    bool tieneEsteTelefono(const string& numTelefono) const;

    /**
     * @brief Añade un correo electrónico al contacto.
     *
     * @param nuevoCorreo Correo a añadir.
     * @return true si se añade correctamente, false si ya existía.
     */
    bool añadirCorreo(const string& nuevoCorreo);

    /**
     * @brief Elimina un correo electrónico del contacto.
     *
     * @param correoBorrar Correo a eliminar.
     * @return true si se elimina, false si no existía.
     */
    bool borrarCorreo(const string& correoBorrar);

    /**
     * @brief Comprueba si el contacto tiene un correo concreto.
     *
     * @param correoBuscar Correo a comprobar.
     * @return true si existe, false en caso contrario.
     */
    bool tieneEsteCorreo(const string& correoBuscar) const;

    /**
     * @brief Añade una etiqueta al contacto.
     *
     * @param nuevaEtiqueta Etiqueta a añadir.
     * @return true si se añade correctamente, false si ya existía.
     */
    bool añadirEtiqueta(const string& nuevaEtiqueta);

    /**
     * @brief Elimina una etiqueta del contacto.
     *
     * @param etiquetaBorrar Etiqueta a eliminar.
     * @return true si se elimina, false si no existía.
     */
    bool borrarEtiqueta(const string& etiquetaBorrar);

    /**
     * @brief Comprueba si el contacto tiene una etiqueta concreta.
     *
     * @param etiquetaBuscar Etiqueta a comprobar.
     * @return true si existe, false en caso contrario.
     */
    bool tieneEsteEtiqueta(const string& etiquetaBuscar) const;

    /**
     * @brief Solicita los datos del contacto por entrada estándar.
     *
     * Permite introducir teléfonos, correos y etiquetas
     * de forma interactiva.
     */
    void preguntarConstructor();

    /**
     * @brief Devuelve una representación textual del contacto.
     *
     * @return Cadena con los datos del contacto.
     */
    string toString() const;

    /* -------------- SETTERS / GETTERS -------------- */

    /**
     * @brief Devuelve el nombre del contacto.
     *
     * @return Referencia constante al nombre.
     */
    const string& getNombre() const;

    /**
     * @brief Devuelve los teléfonos del contacto.
     *
     * @return Conjunto de teléfonos.
     */
    const set<string>& getTelefonos() const;

    /**
     * @brief Devuelve los correos del contacto.
     *
     * @return Conjunto de correos.
     */
    const set<string>& getCorreos() const;

    /**
     * @brief Devuelve las etiquetas del contacto.
     *
     * @return Conjunto de etiquetas.
     */
    const set<string>& getEtiquetas() const;

    /**
     * @brief Establece el nombre del contacto.
     *
     * @param nuevoNombre Nuevo nombre.
     */
    void setNombre(string nuevoNombre);
};

#endif
