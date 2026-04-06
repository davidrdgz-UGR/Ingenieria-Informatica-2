#include <stdio.h>
#include <pthread.h>
//Ejemplo minimo de modo de programacion para multiprocesador: Suma de elementos de vector. N.C. Cruz, UGR

int NUM_THREADS = 4;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int LEN_VEC = 12;
int vec[12];
int suma;

void* func(void* arg){
	int id = (int) arg;
	int localSum = 0;
	for(int i = id; i<LEN_VEC; i+=NUM_THREADS){//Comunicacion implicita
		localSum += vec[i];
	}
	pthread_mutex_lock(&mutex);//Sincronizacion explicita
	suma += localSum;
	pthread_mutex_unlock(&mutex);
	return 0;
}

int main(void){
	suma = 0;
	for(int i = 0; i<LEN_VEC; i++){
		vec[i] = i;
	}
	pthread_t threads[NUM_THREADS];//Nos vamos a dejar el 0 como el propio hilo principal
	for(int i = 1; i<NUM_THREADS; i++){
		pthread_create(&threads[i], 0, func, (void*) i);
	}
	func(0);//Entro yo como principal
	for(int i = 1; i<NUM_THREADS; i++){
		pthread_join(threads[i], 0);//Sincronizacion explicita
	}
	printf("La suma total es: %d\n", suma);
	return 0;
}
