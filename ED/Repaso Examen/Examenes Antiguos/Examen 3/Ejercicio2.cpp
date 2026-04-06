/* 

5. (2,5 puntos) Un compilador necesita validar expresiones matemáticas para comprobar que
los paréntesis, corchetes y llaves están correctamente balanceados. Para ello, se utilizará
una pila como estructura principal.

    a. (0,5 puntos) Especifica la interfaz del T.D.A. PilaBalanceo, que incluye al menos
    las operaciones básicas de una pila (push, pop, top) y un método adicional para
    comprobar si una expresión está balanceada.

    b. (0,5 puntos) ¿Cuál es su función de abstracción y el invariante de representación?

    c. (1 punto) Implementa la función esBalanceada que recibe una expresión matemática
    en forma de cadena (por ejemplo, "(a + b) * [c - d]") y devuelve un valor booleano
    indicando si los delimitadores (paréntesis, corchetes y llaves) están correctamente
    balanceados.

    d. (0,5 puntos) Analiza la eficiencia teórica de la función esBalanceada. ¿Qué ocurriría
    en el caso extremo de una expresión que contenga únicamente delimitadores de
    apertura (por ejemplo, (((([[{{))?

    -> Solo tiene asignaciones, en el peor caso será O(n).

*/

/* 

FA -> Pila abstracta S = ( s1,s2,....,sk), donde top() devuelve sk, que es el ultimo valor añadido.

IR -> tam >= 0 tam <= capacidad / Elementos validos en posiciones 0 - tam-1 / Estructura LIFO

*/
class PilaBalanceo {

    private:
        char* a; /* Puntero de caracteres. */
        int tam;
        int cap;

    public:
        PilaBalanceo(int c=1024) : tam(0), cap(c) { a = new char[cap]; }
        ~PilaBalanceo(){ delete[] a; }

        /* Para las pilas jugamos siempre con su tamaño. */
        bool vacia() const { return tam == 0; }
        void push(char c) { a[tam++] = c; }
        void pop() { tam--; }
        char top() const { return a[tam-1]; }



        static bool esApertura(char c) {
            return c=='(' || c=='[' || c=='{';
        }
        static bool esCierre(char c) {
            return c==')' || c==']' || c=='}';
        }
        static bool empareja(char apertura, char cierre) {
            return (apertura=='(' && cierre==')') ||
                   (apertura=='[' && cierre==']') ||
                   (apertura=='{' && cierre=='}');
        }

        bool esBalanceada(const char* expr) const {
        // Creamos una pila auxiliar mutable (porque este método es const)
        PilaBalanceo st(cap);

        for (int i = 0; expr[i] != '\0'; ++i) {
            char c = expr[i];

            if (esApertura(c)) {
                st.push(c);
            } else if (esCierre(c)) {
                if (st.vacia()) return false;          // cierre sin apertura
                char t = st.top();
                if (!empareja(t, c)) return false;     // tipo incorrecto
                st.pop();
            }
        }
        return st.vacia(); // si quedan aperturas sin cerrar -> false
    }
};