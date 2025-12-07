// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos (sin camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_filosofos = 5,
   num_filo_ten = 2*num_filosofos,  // 10 (filósofos + tenedores)
   id_camarero = num_filo_ten,     // 10
   num_procesos_esperado = num_filo_ten + 1, // 11 procesos en total

   etiq_coger       = 0,
   etiq_soltar      = 1,
   etiq_sentarse    = 2,
   etiq_levantarse  = 3;


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

void funcion_filosofos( int id )
{
  int id_ten_izq = (id+1) % num_filo_ten, //id. tenedor izq.
      id_ten_der = (id+num_filo_ten-1) % num_filo_ten; //id. tenedor der.

   
   int mensaje = 0; 

  while ( true )
  {
     // 1. SENTARSE
    cout << "Filósofo " << id << " pide SENTARSE" << endl;
    MPI_Ssend(&mensaje, 1, MPI_INT,
              id_camarero, etiq_sentarse, MPI_COMM_WORLD);

    // 2. TENEDORES 
    cout <<"Filósofo " <<id << " solicita ten. izq. " <<id_ten_izq <<endl;
    MPI_Ssend(&mensaje, 1, MPI_INT,
              id_ten_izq, etiq_coger, MPI_COMM_WORLD);

    cout <<"Filósofo " <<id <<" solicita ten. der. " <<id_ten_der <<endl;
    MPI_Ssend(&mensaje, 1, MPI_INT,
              id_ten_der, etiq_coger, MPI_COMM_WORLD);

    // 3. COMER
    cout <<"Filósofo " <<id <<" comienza a comer" <<endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );

    // 4. SOLTAR TENEDORES
    cout <<"Filósofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
    MPI_Ssend(&mensaje, 1, MPI_INT,
              id_ten_izq, etiq_soltar, MPI_COMM_WORLD);

    cout<< "Filósofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
    MPI_Ssend(&mensaje, 1, MPI_INT,
              id_ten_der, etiq_soltar, MPI_COMM_WORLD);

    // 5. LEVANTARSE
    cout << "Filósofo " << id << " se LEVANTA" << endl;
    MPI_Ssend(&mensaje, 1, MPI_INT,
              id_camarero, etiq_levantarse, MPI_COMM_WORLD);

    // 6. PENSAR
    cout << "Filosofo " << id << " comienza a pensar" << endl;
    sleep_for( milliseconds( aleatorio<10,100>() ) );
 }
}
// ---------------------------------------------------------------------

void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true )
  {
     MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_coger, MPI_COMM_WORLD, &estado);

     id_filosofo = estado.MPI_SOURCE;
     cout <<"Ten. " <<id <<" ha sido cogido por filo. " <<id_filosofo <<endl;

     MPI_Recv(&valor, 1, MPI_INT, id_filosofo, etiq_soltar, MPI_COMM_WORLD, &estado);

     cout <<"Ten. "<< id<< " ha sido liberado por filo. " <<id_filosofo <<endl ;
  }
}

void funcion_camarero(){
   int sentados = 0;          // número de filósofos sentados
   int valor;
   MPI_Status estado;

   while ( true ){
      int etiq_aceptable;

      // si ya hay 4 sentados, solo aceptamos LEVANTARSE
      if ( sentados == 4 )
         etiq_aceptable = etiq_levantarse;
      else
         etiq_aceptable = MPI_ANY_TAG; 

      // Peticion de filosofo
      MPI_Recv(&valor, 1, MPI_INT,
               MPI_ANY_SOURCE, etiq_aceptable,
               MPI_COMM_WORLD, &estado);

      if ( estado.MPI_TAG == etiq_sentarse ){
         sentados++;
         cout << "Camarero: se sienta el filosofo " << estado.MPI_SOURCE << ". Sentados = " << sentados << endl;

      }else if ( estado.MPI_TAG == etiq_levantarse ){
         sentados--;
         cout << "Camarero: se levanta el filosofo " << estado.MPI_SOURCE << ". Sentados = " << sentados << endl;
      }
   }
}

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


    if ( num_procesos_esperado == num_procesos_actual ){
      if ( id_propio == id_camarero )
          funcion_camarero();
      else if ( id_propio % 2 == 0 )            // par y < num_filo_ten → filósofo
          funcion_filosofos( id_propio );
      else                                      // impar → tenedor
          funcion_tenedores( id_propio );
    }else{
      if ( id_propio == 0 )
      {
          cout << "el número de procesos esperados es:    " << num_procesos_esperado << endl
            << "el número de procesos en ejecución es: " << num_procesos_actual << endl << "(programa abortado)" << endl ;
      }
    }


   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
