#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void imprimir_funciones(char *zona)
{
    printf("\n--- %s ---\n", zona);
    printf("omp_get_num_threads() = %d\n", omp_get_num_threads());
    printf("omp_get_num_procs() = %d\n", omp_get_num_procs());
    printf("omp_in_parallel() = %d\n", omp_in_parallel());
}

int main(int argc, char **argv)
{
    int i, n = 200, chunk, a[200], suma = 0;

    if (argc < 3) {
        fprintf(stderr, "\nFalta iteraciones o chunk\n");
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n > 200) n = 200;

    chunk = atoi(argv[2]);

    for (i = 0; i < n; i++)
        a[i] = i;

    imprimir_funciones("Fuera de la region paralela");

    #pragma omp parallel
    {
        #pragma omp single
        imprimir_funciones("Dentro de la region paralela");

        #pragma omp for firstprivate(suma) lastprivate(suma) schedule(dynamic, chunk)
        for (i = 0; i < n; i++) {
            suma = suma + a[i];
            printf("thread %d suma a[%d]=%d suma=%d\n",
                   omp_get_thread_num(), i, a[i], suma);
        }
    }

    printf("Fuera de 'parallel for' suma=%d\n", suma);

    return 0;
}