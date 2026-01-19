
/* 

6. (1,5 puntos) Define la clase Conjunto como una especialización del T.D.A. Lista mediante
herencia. La clase debe sobrescribir el método de inserción para evitar duplicados, utilizando
el método pertenece definido en la clase base. Realiza los siguientes apartados teniendo en
cuenta que debes incluir la interfaz de ambas clases (Lista y Conjunto) y todo lo necesario
para que el programa funcione.
    
    a. (1 punto) Define la clase Conjunto como una especialización del T.D.A. Lista
    mediante herencia. La clase debe sobrescribir el método de inserción para evitar
    duplicados, utilizando el método pertenece definido en la clase base.
    
    b. (0,5 puntos) Implementa el método insertar, asegurándote que no existan elementos
    duplicados. ¿Cómo incluirías esta especificación en la clase?

*/


template <class T>

class Lista {
public:
    bool insertar(const T& x);        // inserta (permite duplicados)
    bool pertenece(const T& x) const; // true si x está en la lista
    // ...
};



template <class T>

class Conjunto : public Lista<T> {
public:
    // sobrescribimos insertar
    bool insertar(const T& x) {
        if (this->pertenece(x)) return false;  // ya está, no insertar
        return Lista<T>::insertar(x);          // inserta usando implementación base
    }
};

/// Inserta x si no existe ya en el conjunto.
/// @return true si se insertó; false si ya estaba.
/// @post No existen duplicados en la estructura.