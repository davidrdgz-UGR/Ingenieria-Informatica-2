#include <cassert>
#include <string>
#include <iosfwd>


#include <set>
#include <list>
#include <vector>
// #include <multiset>
#include <map>

using namespace std;

class Contacto{

	private:
	
		/* Set evita los duplicados directamente  */
		string nombre;
		set<string> telefonos;
		set<string> correos;
		set<string> etiquetas;

	public:

	/* -------------- CONSTRUCTOR -------------- */
	Contacto();




	/* -------------- SETTERS / GETTERS -------------- */

	string& getNombre();

	const set<string>& getTelefonos() const;

	const set<string>& getCorreos() const;

	const set<string>& getEtiquetas() const;


	void setNombre(string nuevoNombre);

	bool añadirTelefono(const string& numTelefono);
    bool borrarTelefono(const string& numTelefono);

	bool añadirCorreo(const string& correo);
    bool borrarCorreo(const string& correo);

	bool añadirEtiqueta(const string& etiqueta);
    bool borrarEtiqueta(const string& etiqueta);


	




		

};