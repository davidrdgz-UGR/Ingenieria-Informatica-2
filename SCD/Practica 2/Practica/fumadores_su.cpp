#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// número de fumadores
const int num_fumadores = 3 ;

class Estanco : public HoareMonitor{

   private:
      int     mostrador;                        
      CondVar mostrador_vacio;                  
      CondVar ingr_disp[num_fumadores];         

   public:
      Estanco();                                
      void ponerIngrediente(int i);             
      void esperarRecogidaIngrediente();        
      void obtenerIngrediente(int i);  
};
   
void Estanco::ponerIngrediente(int i){
   while (mostrador != -1)
      mostrador_vacio.wait();

   mostrador = i;

   cout << "Estanquero : pone ingrediente " << i << endl;

   ingr_disp[i].signal();
}

void Estanco::esperarRecogidaIngrediente(){
   while (mostrador != -1)
      mostrador_vacio.wait();
}

void Estanco::obtenerIngrediente(int i){
   while (mostrador != i)
      ingr_disp[i].wait();

   assert(mostrador == i);

   cout << "Fumador " << i << " : retira su ingrediente" << endl;

   mostrador = -1;

   mostrador_vacio.signal();
}

Estanco::Estanco(){
   mostrador = -1;                           
   mostrador_vacio = newCondVar();
   for (int i = 0; i < num_fumadores; i++)
       ingr_disp[i] = newCondVar();
}

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero( MRef<Estanco> monitor )
{
   while ( true )
   {
      const int i = producir_ingrediente();
      monitor->ponerIngrediente( i );
      monitor->esperarRecogidaIngrediente();
   }
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void funcion_hebra_fumador( MRef<Estanco> monitor, int num_fumador )
{
   while( true )
   {
      monitor->obtenerIngrediente( num_fumador );
      fumar( num_fumador );
   }
}

//----------------------------------------------------------------------

int main()
{
   cout << "---------------------------------------------\n"
        << "Problema de los fumadores (SCD, monitor SU)\n"
        << "---------------------------------------------\n" << flush;

   MRef<Estanco> estanco = Create<Estanco>();

   thread hebra_estanquero( funcion_hebra_estanquero, estanco );
   thread hebra_fumadores[num_fumadores];

   for (int i = 0; i < num_fumadores; i++)
      hebra_fumadores[i] = thread( funcion_hebra_fumador, estanco, i );

   hebra_estanquero.join();
   for (int i = 0; i < num_fumadores; i++)
      hebra_fumadores[i].join();

   return 0;
}

