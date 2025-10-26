#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales

constexpr unsigned num_items = 60 ;   // número de items
constexpr unsigned tam_vec   = 10 ;   // tamaño del buffer

constexpr unsigned np = 4 ;           // nº productores
constexpr unsigned nc = 3 ;           // nº consumidores

static_assert( (num_items % np) == 0, "num_items debe ser múltiplo de np");
static_assert( (num_items % nc) == 0, "num_items debe ser multiplo de nc");

constexpr unsigned p = num_items/np ; // items por productor
constexpr unsigned c = num_items/nc ; // items por consumidor


unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha consumido.
   
   vectorItems[tam_vec],
   primera_libre = 0 ;
   

   Semaphore libres(tam_vec) ;
   Semaphore ocupadas(0) ;
   Semaphore sem_mutex(1) ;

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato( unsigned valor )
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   cont_prod[valor] ++ ;
   cout << "producido: " << valor << endl << flush ;
   return valor ;
}

//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void funcion_hebra_productora( unsigned id_prod )
{
   for( unsigned k = 0 ; k < p ; k++ )
   {
      const unsigned valor = id_prod * p + k ;
      const unsigned dato  = producir_dato( valor ) ;

      sem_wait( libres );
      sem_wait( sem_mutex );

      vectorItems[primera_libre] = dato ;
      primera_libre++ ;

      cout << "Productor " << id_prod << ": inserta " << dato
           << "   (ocupadas=" << primera_libre << ")" << endl ;

      sem_signal( sem_mutex );
      sem_signal( ocupadas );
   }
}


//----------------------------------------------------------------------

void funcion_hebra_consumidora( unsigned id_cons )
{
   for( unsigned j = 0 ; j < c ; j++ )
   {
      unsigned dato ;

      sem_wait( ocupadas );
      sem_wait( sem_mutex );

      primera_libre-- ;
      dato = vectorItems[primera_libre] ;

      cout << "                Consumidor " << id_cons << ": extrae " << dato
           << "   (ocupadas=" << primera_libre << ")" << endl ;

      sem_signal( sem_mutex );
      sem_signal( libres );

      consumir_dato( dato ) ;
   }
}

//----------------------------------------------------------------------

void  funcion_hebra_productora( unsigned id_prod );
void  funcion_hebra_consumidora( unsigned id_cons );


int main()
{
   cout << "-----------------------------------------------------------------" << endl
     << "Productor-Consumidor MULTI (LIFO), np=" << np << ", nc=" << nc
     << ", num_items=" << num_items << ", tam_vec=" << tam_vec << endl
     << "------------------------------------------------------------------" << endl
     << flush ;


   thread productores[np] ;
   thread consumidores[nc] ;

   for( unsigned i = 0 ; i < np ; i++ )
      productores[i] = thread( funcion_hebra_productora, i );

   for( unsigned j = 0 ; j < nc ; j++ )
      consumidores[j] = thread( funcion_hebra_consumidora, j );

   for( unsigned i = 0 ; i < np ; i++ )
      productores[i].join() ;

   for( unsigned j = 0 ; j < nc ; j++ )
   consumidores[j].join() ;


   test_contadores();
}
