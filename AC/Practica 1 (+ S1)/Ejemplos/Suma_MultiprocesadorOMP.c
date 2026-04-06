#include <stdio.h>
#include <omp.h>
//Ejemplo minimo de modo de programacion para multiprocesador: Suma de elementos de vector (OpenMP). N.C. Cruz, UGR

int NUM_THREADS = 4;
int LEN_VEC = 12;
int vec[12];
int suma;

int main(void){
	suma = 0;
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		#pragma omp master
		{
			for(int i = 0; i<LEN_VEC; i++){
				vec[i] = i;
			}
		}
		#pragma omp barrier // Sincronizacion Explicita
		int myRes = 0;
		for(int i = omp_get_thread_num(); i<LEN_VEC; i+=NUM_THREADS){
			myRes += vec[i];	// Comunicacion Implicita
		}
		#pragma omp atomic
		suma += myRes;
		
	}//BARRIER (implicito) incluido por OpenMP
	printf("La suma total es: %d\n", suma);
	return 0;
}
