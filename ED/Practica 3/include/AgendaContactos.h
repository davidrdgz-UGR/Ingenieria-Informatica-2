#include "contactos.h"

#include <string>
#include <set>
#include <map>

using namespace std;

class AgendaContactos{

private:
	map<string,Contacto> listaContactos;
    multimap<string, string> etiquetas;

    // void añadirContacto(const Contacto& contactoAñadir);
    // void quitarContacto(const Contacto& contactoBorrar);

public:

    
    /* -------------- CONSTRUCTOR -------------- */

    AgendaContactos(const string& nombre_fichero);



    /* -------------- MÉTODOS -------------- */

    bool insertarContacto(const Contacto& nuevoContacto);
    bool eliminarContacto(const string& borrarContacto);
    
    bool existeContacto(const string& nombre) const;

    // Contacto* buscarContacto(const string& nombre);
    const Contacto* buscarContacto(const string& nombre) const;

    string contactosPorEtiqueta(const std::string& etiqueta) const;

    string toString() const;

    bool cargar(const string& nombre_fichero);


 
    /* -------------- SETTERS / GETTERS -------------- */

    const int getNumeroContactos() const;

    const string getEtiquetas() const;



};