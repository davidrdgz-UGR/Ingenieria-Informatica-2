// #include <cassert>
// #include <iosfwd>
#include <string>

#include <set>
// #include <list>
// #include <vector>


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
	Contacto(string nombreContacto);

	Contacto();

	/* -------------- MÉTODOS -------------- */

	bool añadirTelefono(const string& numTelefono);
    bool borrarTelefono(const string& numTelefono);
	bool tieneEsteTelefono(const string& numTelefono) const;

	bool añadirCorreo(const string& nuevoCorreo);
    bool borrarCorreo(const string& correoBorrar);
	bool tieneEsteCorreo(const string& correoBuscar) const;

	bool añadirEtiqueta(const string& nuevaEtiqueta);
    bool borrarEtiqueta(const string& etiquetaBorrar);
	bool tieneEsteEtiqueta(const string& etiquetaBuscar) const;

	
	void preguntarConstructor();

	string toString() const;

	/* -------------- SETTERS / GETTERS -------------- */

	/* Los const significa que no copian ni modifican el valor devuelto, lo pasa por referencia. */
	const string& getNombre() const;
	const set<string>& getTelefonos() const;
	const set<string>& getCorreos() const;
	const set<string>& getEtiquetas() const;


	void setNombre( string nuevoNombre);	

};