// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que gestiona un buffer finito y recibe peticiones
// en orden arbitrario
// (versión con un único productor y un único consumidor)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <mpi.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_items  = 20,     // nº total de ítems producidos/consumidos
   tam_vector = 10,     // tamaño del buffer

   np         = 4,      // nº de productores
   nc         = 5,      // nº de consumidores

   id_buffer  = np,                 // id del proceso buffer
   num_procesos_esperado = np+nc+1, // total de procesos

   etiq_prod  = 0,      // etiqueta mensajes de productores
   etiq_cons  = 1;      // etiqueta mensajes de consumidores

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}
// ---------------------------------------------------------------------
// ptoducir produce los numeros en secuencia (1,2,3,....)
// y lleva espera aleatorio
int producir( int orden_prod )
{
   static int contadores[np] = {0};   // un contador por productor
   const int k = num_items / np;

   sleep_for( milliseconds( aleatorio<10,100>() ) );

   int valor = orden_prod * k + contadores[orden_prod];
   contadores[orden_prod]++;

   cout << "Productor " << orden_prod
        << " ha producido valor " << valor << endl << flush;

   return valor;
}
// ---------------------------------------------------------------------

void funcion_productor( int orden_prod )
{
   const int num_items_prod = num_items / np;

   for ( int i = 0 ; i < num_items_prod ; i++ )
   {
      int valor_prod = producir( orden_prod );
      cout << "Productor " << orden_prod
           << " va a enviar valor " << valor_prod << endl << flush;

      MPI_Ssend( &valor_prod, 1, MPI_INT,
                 id_buffer, etiq_prod, MPI_COMM_WORLD );
   }
}
// ---------------------------------------------------------------------

void consumir(int valor_cons)
{
   sleep_for(milliseconds( aleatorio<110,200>() ));
   cout << "Consumidor ha consumido valor " << valor_cons << endl << flush;
}
// ---------------------------------------------------------------------

void funcion_consumidor( int orden_cons )
{
   int peticion = 1 ;
   int valor_rec ;
   MPI_Status estado ;
   const int num_items_cons = num_items / nc;

   for( int i = 0 ; i < num_items_cons ; i++ )
   {
      // enviar petición al buffer
      MPI_Ssend( &peticion, 1, MPI_INT,
                 id_buffer, etiq_cons, MPI_COMM_WORLD );

      // recibir dato del buffer
      MPI_Recv( &valor_rec, 1, MPI_INT,
                id_buffer, etiq_cons, MPI_COMM_WORLD, &estado );

      cout << "Consumidor " << orden_cons
           << " ha recibido valor " << valor_rec << endl << flush ;

      consumir( valor_rec );
   }
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int  buffer[tam_vector];      // celdas del buffer
   int  valor;
   int  primera_libre       = 0;
   int  primera_ocupada     = 0;
   int  num_celdas_ocupadas = 0;
   MPI_Status estado;

   // en total llegarán num_items mensajes de productores
   // y num_items mensajes de consumidores (peticiones)
   for (int i = 0; i < num_items*2; i++)
   {
      int tag_aceptable;

      // determinar qué tipo de emisor es aceptable según estado del buffer
      if ( num_celdas_ocupadas == 0 )              // buffer vacío
         tag_aceptable = etiq_prod;                // sólo productores
      else if ( num_celdas_ocupadas == tam_vector) // buffer lleno
         tag_aceptable = etiq_cons;                // sólo consumidores
      else
         tag_aceptable = MPI_ANY_TAG;              // cualquiera

      // recibir mensaje de algún productor o consumidor
      MPI_Recv(&valor, 1, MPI_INT,
               MPI_ANY_SOURCE, tag_aceptable,
               MPI_COMM_WORLD, &estado);

      switch (estado.MPI_TAG)
      {
         // mensaje de productor: insertar en buffer
         case etiq_prod:
            buffer[primera_libre] = valor;
            primera_libre = (primera_libre + 1) % tam_vector;
            num_celdas_ocupadas++;
            cout << "Buffer ha recibido valor " << valor
                 << " de productor " << estado.MPI_SOURCE << endl;
            break;

         // mensaje de consumidor: extraer de buffer y enviarle
         case etiq_cons:
            valor = buffer[primera_ocupada];
            primera_ocupada = (primera_ocupada + 1) % tam_vector;
            num_celdas_ocupadas--;
            cout << "Buffer va a enviar valor " << valor
                 << " a consumidor " << estado.MPI_SOURCE << endl;

            MPI_Ssend(&valor, 1, MPI_INT,
                      estado.MPI_SOURCE, etiq_cons, MPI_COMM_WORLD);
            break;
      }
   }
}


// ---------------------------------------------------------------------

int main( int argc, char *argv[] )
{

   int id_propio, num_procesos_actual;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procesos_actual);



    if (num_procesos_actual == num_procesos_esperado){
      if (id_propio < np)                         // productores
      {
         int orden_prod = id_propio;              // 0..np-1
         funcion_productor(orden_prod);
      }
      else if (id_propio == id_buffer)            // buffer
      {
         funcion_buffer();
      }
      else                                        // consumidores
      {
         int orden_cons = id_propio - (np + 1);   // 0..nc-1
         funcion_consumidor(orden_cons);
      }
   }else if (id_propio == 0){
      cerr << "Número de procesos actual (" << num_procesos_actual
           << ") distinto de " << num_procesos_esperado << endl;
   }

   MPI_Finalize();
   return 0;
}
