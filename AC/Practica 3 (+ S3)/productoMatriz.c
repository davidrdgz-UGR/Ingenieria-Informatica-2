#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 16375
double v1[MAX], v2[MAX], m[MAX][MAX];

//Código para multimplicación secuencial matriz cuadrada triangular superior por vector: v2 = m * v1

int main(int argc, char** argv){
        unsigned int N;
        struct timespec cgt1,cgt2;
        double ncgt;
        int i, j;

        if (argc < 2){
                printf("Uso: %s tamaño\n", argv[0]);
                return 1;
        }

        N = atoi(argv[1]);

        if (N > MAX)
                N = MAX;
        // Inicializar vector y matriz
        for (i = 0; i < N; i++){
                v1[i] = 1.0;//0.1*i;
                v2[i] = 0;
                for (j = 0; j < i; j++)
                        m[i][j] = 0;
                for (j = i; j < N; j++)
                        m[i][j] = 1.0;//i*N+j;
        }

        // Calcular v2 = m * v1
        clock_gettime(CLOCK_REALTIME, &cgt1);
        for(i = 0; i < N; i++){
                for (j = i; j < N; j++)
                        v2[i] += m[i][j] * v1[j];
        }
        clock_gettime(CLOCK_REALTIME, &cgt2);

        ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec) + (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

        // Imprimir resultados
        if (N < 10){
                printf("Tiempo: %11.9f\t Tamaño: %u\nMatriz:\n\t", ncgt, N);
                for (i = 0; i < N; i++){
                        for (j = 0; j < N; j++)
                                printf("%8.6f \t ", m[i][j]);
                        printf("\n\t");
                }
                printf("\nVector:\n\t");
                for (i = 0; i < N; i++)
                        printf("%8.6f ", v1[i]);
                printf("\n\nVector resultado:\n\t");
                for (i = 0; i < N; i++)
                        printf("%8.6f ", v2[i]);
                printf("\n");
        }else{
                printf("Tiempo: %11.9f \t Tamaño: %u \t v2[0]: %8.6f \t v2[N-1]: %8.6f \n",ncgt, N, v2[0], v2[N-1]);
        }
        return 0;
}