/* 
4) Implementar TDA Cola usando TDA Pila
Idea

Una cola es FIFO. Con dos pilas puedes simular FIFO:

in (pila de entrada): aquí apilas al encolar.

out (pila de salida): aquí desapilas al desencolar.

Cuando out está vacía y necesitas desencolar, vuelcas todo in → out (invirtiendo el orden), así el más antiguo queda arriba en out.

*/

#include <stack>
#include <stdexcept>

template <class T>
class ColaConPilas {
private:
    std::stack<T> in, out;

    void volcarSiHaceFalta() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
    }

public:
    bool vacia() const { return in.empty() && out.empty(); }

    void encolar(const T& x) {  // inserción
        in.push(x);
    }

    void desencolar() {         // borrado
        volcarSiHaceFalta();
        if (out.empty()) throw std::logic_error("Cola vacia");
        out.pop();
    }

    T primero() {
        volcarSiHaceFalta();
        if (out.empty()) throw std::logic_error("Cola vacia");
        return out.top();
    }
};
