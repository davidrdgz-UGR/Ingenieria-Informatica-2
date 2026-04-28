#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv) {
    int i, j, N;
    double **M, *v1, *v2;
    double inicio, fin;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <N>\n", argv[0]);
        exit(-1);
    }

    N = atoi(argv[1]);

    M = (double **) malloc(N * sizeof(double *));
    v1 = (double *) malloc(N * sizeof(double));
    v2 = (double *) malloc(N * sizeof(double));

    if (M == NULL || v1 == NULL || v2 == NULL) {
        fprintf(stderr, "Error al reservar memoria\n");
        exit(-1);
    }

    for (i = 0; i < N; i++) {
        M[i] = (double *) malloc(N * sizeof(double));
        if (M[i] == NULL) {
            fprintf(stderr, "Error al reservar memoria\n");
            exit(-1);
        }
    }

    #pragma omp parallel for private(j)
    for (i = 0; i < N; i++) {
        v1[i] = 1.0;
        v2[i] = 0.0;

        for (j = 0; j < N; j++) {
            M[i][j] = 1.0;
        }
    }

    inicio = omp_get_wtime();

    for (i = 0; i < N; i++) {
        double suma = 0.0;

        #pragma omp parallel for reduction(+:suma)
        for (j = 0; j < N; j++) {
            suma += M[i][j] * v1[j];
        }

        v2[i] = suma;
    }

    fin = omp_get_wtime();

    printf("Tiempo de ejecucion: %f segundos\n", fin - inicio);
    printf("Numero de hilos usados: %d\n", omp_get_max_threads());
    printf("Primer componente v2[0] = %f\n", v2[0]);
    printf("Ultimo componente v2[%d] = %f\n", N - 1, v2[N - 1]);

    if (N <= 11) {
        printf("Vector resultado v2:\n");
        for (i = 0; i < N; i++) {
            printf("v2[%d] = %f\n", i, v2[i]);
        }
    }

    for (i = 0; i < N; i++) {
        free(M[i]);
    }

    free(M);
    free(v1);
    free(v2);

    return 0;
}