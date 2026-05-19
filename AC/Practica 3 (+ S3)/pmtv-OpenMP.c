#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int N, i, j;
    double **M, *v, *res;
    double t;

    if (argc < 2) {
        printf("Uso: %s <tamano_matriz>\n", argv[0]);
        return -1;
    }

    N = atoi(argv[1]);

    M = malloc(N * sizeof(double *));
    v = malloc(N * sizeof(double));
    res = malloc(N * sizeof(double));

    for (i = 0; i < N; i++) {
        M[i] = malloc(N * sizeof(double));
    }

    for (i = 0; i < N; i++) {
        v[i] = 1.0;
        res[i] = 0.0;
        for (j = 0; j < N; j++) {
            if (j >= i)
                M[i][j] = 1.0;
            else
                M[i][j] = 0.0;
        }
    }

    t = omp_get_wtime();

    #pragma omp parallel for private(j) schedule(runtime)
    for (i = 0; i < N; i++) {
        for (j = i; j < N; j++) {
            res[i] += M[i][j] * v[j];
        }
    }

    t = omp_get_wtime() - t;

    printf("Tiempo: %f segundos\n", t);

    if (N <= 20) {
        printf("Resultado:\n");
        for (i = 0; i < N; i++) {
            printf("res[%d] = %.2f\n", i, res[i]);
        }
    }

    for (i = 0; i < N; i++) {
        free(M[i]);
    }

    free(M);
    free(v);
    free(res);

    return 0;
}