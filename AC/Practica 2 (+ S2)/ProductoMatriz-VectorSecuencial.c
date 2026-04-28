#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 16375	
double v1[MAX], v2[MAX], m[MAX][MAX];

// m*v1 = v2

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Uso: ./prog tam_matriz_cuadrada\n");
		return 1;
	}
	int N = atoi(argv[1]);
	if(N<0){
		printf("N = %d no es un tamaño válido\n", N);
		return 2;
	}
	if(N>MAX){
		N = MAX;
		printf("Aviso: N es demasiado grande. Se trunca a %d\n", MAX);
	}
	struct timespec cgt1, cgt2; 
	double ncgt;
	//Inicializacion:
	for(int i = 0; i<N; i++){
		v1[i] = 1;
		v2[i] = 0;
		for(int j = 0; j<N; j++){
			m[i][j] = 1;
		}
	}
	//Producto:
	clock_gettime(CLOCK_REALTIME,&cgt1);
	for(int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			v2[i] += m[i][j]*v1[j];
		}
	}
	clock_gettime(CLOCK_REALTIME,&cgt2);
	ncgt = (double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	//Mostrado:
    if(N<10){
    	for(int i = 0; i<N; i++){
    		printf("v2[%d] = %.2lf\n", i, v2[i]);
    	}
    }else{
    	printf("v2[0] = %.2lf\n", v2[0]);
    	printf("v2[%d] = %.2lf\n", N-1, v2[N-1]);
	}
	printf("Tiempo: %11.9f\t Tamaño: %u\n", ncgt, N);
	return 0;
}