
/* 

1.- (2,5 puntos) Una estación ferroviaria se compone de N vías para el tránsito de trenes (solo
puede haber un tren en cada una), una vía muerta para el estacionamiento de trenes sin salida
inmediata y otra vía de maniobras que se utilizará sólo para el movimiento de trenes dentro de la
estación cuando sea necesario (ambas, supuestamente, de capacidad ilimitada). Los trenes que
circulan por la estación de identifican mediante un código de tren.
	
	a. Especifica e implementa el TDA estación con las siguientes operaciones:
		• Crear una estación de N vías en tránsito
		• Llegada de un tren concreto a la estación
		• Salida de la estación del tren situado en una vía dada
		• Llevar un determinado tren desde una vía de tránsito a la vía de
		estacionamiento
		• Llevar un tren determinado desde la vía de estacionamiento a una de las vías
		de tránsito
		• Vía en la que se encuentra el tren
		• Código del tren situado en una vía de tránsito
		• Destruir una estación
		
	b. Dada la información relativa al horario de salidas y llegadas de trenes a la estación
	un día cualquiera, implementa un subprograma que devuelva el estado de la estación
	(qué trenes se encuentran en qué vías) a una hora determinada. Por simplificar el
	problema, se supone que todos los trenes que parten de la estación están en alguna
	vía, bien porque se han efectuado su llegada previamente o bien porque se
	encontraban en la estación desde el principio del día. 

*/

#include <iostream>

using namespace std;


class Estacion{

private:
	/* Son las celdas que contienen a los trenes. */
	struct Nodo{
		int tren;
		Nodo* sig;

		Nodo(int t,Nodo* s=nullptr){
			this->tren = t;
			this->sig = s;
		}
	};

	int N;
    int* transito;     // -1 = vacía
    Nodo* estacionamiento;	 // lista enlazada de trenes, puntero al primer nodo

    /* Se busca la primera via( transito[N] ) que tenga como valor -1, es decir, que este vacía */
	int primeraViaLibre() const {
        for (int i = 0; i < N; ++i)
            if (transito[i] == -1) return i;
        return -1;
    }

	bool quitarDeLista(Nodo*& head, int tren) {
        Nodo* ant = nullptr;
        Nodo* act = head;
        while (act) {
            if (act->tren == tren) {
                if (ant) ant->sig = act->sig;
                else head = act->sig;
                delete act;
                return true;
            }
            ant = act;
            act = act->sig;
        }
        return false;
    }

	bool estaEnLista(Nodo* head, int tren) const {
        while (head) {
            if (head->tren == tren) return true;
            head = head->sig;
        }
        return false;
    }

public:

	Estacion(int n) : N(n), estacionamiento(nullptr) {
        transito = new int[N];
        for (int i = 0; i < N; ++i) transito[i] = -1;
    }

	// Destruir estación
    ~Estacion() {
        destruir();
        delete[] transito;
    }


	void destruir() {
        // Vaciar transito
        for (int i = 0; i < N; ++i) transito[i] = -1;
        // Vaciar lista estacionamiento
        while (estacionamiento) {
            Nodo* aux = estacionamiento;
            estacionamiento = estacionamiento->sig;
            delete aux;
        }
    }

	// Llegada de un tren (a una vía libre)
    bool llegada(int tren) {
        // si ya está en tránsito
        for (int i = 0; i < N; ++i)
            if (transito[i] == tren) return false;
        // si ya está en estacionamiento
        if (estaEnLista(estacionamiento, tren)) return false;

        int via = primeraViaLibre();
        if (via == -1) return false; // no hay hueco
        transito[via] = tren;
        return true;
    }

	// Salida del tren en una vía dada
    bool salida(int via) {
        if (via < 0 || via >= N) return false;
        if (transito[via] == -1) return false;
        transito[via] = -1;
        return true;
    }

	// Tránsito -> estacionamiento
    bool moverAEstacionamiento(int via) {
        if (via < 0 || via >= N) return false;
        if (transito[via] == -1) return false;
        int tren = transito[via];
        transito[via] = -1;
        estacionamiento = new Nodo(tren, estacionamiento); // inserta al principio
        return true;
    }

	// Estacionamiento -> alguna vía de tránsito libre
    bool moverATransito(int tren) {
        int via = primeraViaLibre();
        if (via == -1) return false; // no hay hueco en tránsito

        // quitar tren de estacionamiento
        bool ok = quitarDeLista(estacionamiento, tren);
        if (!ok) return false; // no estaba en estacionamiento

        transito[via] = tren;
        return true;
    }

	// Vía donde está el tren:
    // devuelve: >=0 si está en vía de tránsito, -2 si está en estacionamiento, -1 si no está
    int viaDelTren(int tren) const {
        for (int i = 0; i < N; ++i)
            if (transito[i] == tren) return i;
        if (estaEnLista(estacionamiento, tren)) return -2;
        return -1;
    }

	// Código del tren situado en una vía de tránsito
    int trenEnVia(int via) const {
        if (via < 0 || via >= N) return -1;
        return transito[via]; // -1 si vacía
    }

    // (Opcional) imprimir estado rápido
    void imprimirEstado() const {
        cout << "Transito:\n";
        for (int i = 0; i < N; ++i)
            cout << "  via " << i << ": " << transito[i] << "\n";

        cout << "Estacionamiento:";
        Nodo* p = estacionamiento;
        while (p) { cout << " " << p->tren; p = p->sig; }
        cout << "\n";
    }


};


struct Evento {
    int minuto;        // 0..1439
    int tipo;          // 0 = llegada, 1 = salida
    int tren;          // si llegada
    int via;           // si salida
};

void estadoA(Estacion& e, Evento* ev, int M, int horaObjetivoMin) {
    for (int i = 0; i < M; ++i) {
        if (ev[i].minuto > horaObjetivoMin) break;

        if (ev[i].tipo == 0) {          // llegada
            e.llegada(ev[i].tren);
        } else {                         // salida
            e.salida(ev[i].via);
        }
    }
}