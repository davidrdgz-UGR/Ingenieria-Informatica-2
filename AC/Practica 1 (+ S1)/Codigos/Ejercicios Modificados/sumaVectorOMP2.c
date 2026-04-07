#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define VECTOR_GLOBAL
#ifdef VECTOR_GLOBAL
#define MAX 67108864
double v1[MAX], v2[MAX], v3[MAX];
#endif

int main(int argc, char **argv) {
    int i;
    unsigned int N;
    double t1, t2, tiempo;
    int nthreads = 0;
    int mitad;

    if (argc < 2) {
        printf("Faltan nº componentes del vector\n");
        exit(-1);
    }

    N = atoi(argv[1]);

    #ifdef VECTOR_GLOBAL
    if (N > MAX) N = MAX;
    #endif

    mitad = N / 2;

    #pragma omp parallel
    {
        #pragma omp single
        {
            nthreads = omp_get_num_threads();
        }

        #pragma omp sections
        {
            #pragma omp section
            {
                for (i = 0; i < mitad; i++) {
                    v1[i] = N * 0.1 + i * 0.1;
                    v2[i] = N * 0.1 - i * 0.1;
                }
            }

            #pragma omp section
            {
                for (i = mitad; i < (int)N; i++) {
                    v1[i] = N * 0.1 + i * 0.1;
                    v2[i] = N * 0.1 - i * 0.1;
                }
            }
        }
    }

    t1 = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                for (i = 0; i < mitad; i++) {
                    v3[i] = v1[i] + v2[i];
                }
            }

            #pragma omp section
            {
                for (i = mitad; i < (int)N; i++) {
                    v3[i] = v1[i] + v2[i];
                }
            }
        }
    }

    t2 = omp_get_wtime();
    tiempo = t2 - t1;

    printf("Tamaño vectores: %u\n", N);
    printf("Numero de hilos: %d\n", nthreads);
    printf("Tiempo(seg.): %11.9f\n", tiempo);

    if (N > 0) {
        printf("V1[0]=%8.6f  V2[0]=%8.6f  V3[0]=%8.6f\n",
               v1[0], v2[0], v3[0]);
        printf("V1[%u]=%8.6f  V2[%u]=%8.6f  V3[%u]=%8.6f\n",
               N-1, v1[N-1], N-1, v2[N-1], N-1, v3[N-1]);
    }

    if (N < 12) {
        printf("Vector resultado completo:\n");
        for (i = 0; i < (int)N; i++) {
            printf("V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f)\n",
                   i, i, i, v1[i], v2[i], v3[i]);
        }
    }

    return 0;
}