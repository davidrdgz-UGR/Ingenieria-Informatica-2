#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// número de hebras lectoras y escritoras
const int num_lectores   = 5 ;
const int num_escritores = 3 ;


/* Funcion para generar tiempo aleatorio */
template<int min, int max> int aleatorio_tiempo() {
    static default_random_engine gen( (random_device())() );
    static uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}


class Lec_Esc : public HoareMonitor{
private:
    int     n_lec;        // número de lectores leyendo
    bool    escrib;       // true si hay un escritor escribiendo
    CondVar lectura;      // cola de lectores
    CondVar escritura;    // cola de escritores

public:
    Lec_Esc();            // constructor

    void ini_lectura();   // inicio de sección de lectura
    void fin_lectura();   // fin de sección de lectura
    void ini_escritura(); // inicio de sección de escritura
    void fin_escritura(); // fin de sección de escritura
};

Lec_Esc::Lec_Esc()
{
    n_lec  = 0;
    escrib = false;
    lectura   = newCondVar();
    escritura = newCondVar();
}

void Lec_Esc::ini_lectura()
{
    // si hay un escritor escribiendo, esperar
    if (escrib)
        lectura.wait();

    // aumentar número de lectores
    n_lec++;

    // permitir que más lectores entren en cadena
    lectura.signal();
}

void Lec_Esc::fin_lectura()
{
    n_lec--;

    // si ya no quedan lectores, un escritor puede entrar
    if (n_lec == 0)
        escritura.signal();
}

void Lec_Esc::ini_escritura()
{
    // si hay lectores leyendo o un escritor escribiendo, esperar
    if (n_lec > 0 || escrib)
        escritura.wait();

    escrib = true;  // un escritor entra
}

void Lec_Esc::fin_escritura()
{
    escrib = false;

    // si hay lectores esperando, dales prioridad
    if (!lectura.empty())
        lectura.signal();
    else
        escritura.signal();
}

void leer(int i)
{
    chrono::milliseconds dur( aleatorio_tiempo<20,100>() );
    cout << "Lector " << i << " lee (" << dur.count() << " ms)" << endl;
    this_thread::sleep_for(dur);
}

void escribir(int i)
{
    chrono::milliseconds dur( aleatorio_tiempo<20,100>() );
    cout << "Escritor " << i << " escribe (" << dur.count() << " ms)" << endl;
    this_thread::sleep_for(dur);
}

void funcion_hebra_lectora(MRef<Lec_Esc> monitor, int i)
{
    while (true)
    {
        monitor->ini_lectura();
        leer(i);
        monitor->fin_lectura();

        // pequeño descanso aleatorio fuera del monitor
        this_thread::sleep_for( chrono::milliseconds( aleatorio_tiempo<20,100>() ) );
    }
}

void funcion_hebra_escritora(MRef<Lec_Esc> monitor, int i)
{
    while (true)
    {
        monitor->ini_escritura();
        escribir(i);
        monitor->fin_escritura();

        this_thread::sleep_for( chrono::milliseconds( aleatorio_tiempo<20,100>() ) );
    }
}


int main(){
    cout << "---------------------------------------------\n"
         << "Problema de Lectores-Escritores (Monitor SU)\n"
         << "---------------------------------------------\n" << flush;

    MRef<Lec_Esc> monitor = Create<Lec_Esc>();

    thread lectores[num_lectores];
    thread escritores[num_escritores];

    for(int i=0; i<num_lectores; i++)
        lectores[i] = thread(funcion_hebra_lectora, monitor, i);

    for(int i=0; i<num_escritores; i++)
        escritores[i] = thread(funcion_hebra_escritora, monitor, i);

    for(int i=0; i<num_lectores; i++)
        lectores[i].join();
    for(int i=0; i<num_escritores; i++)
        escritores[i].join();

    return 0;
}
