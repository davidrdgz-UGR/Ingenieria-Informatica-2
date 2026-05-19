#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void imprimir_variables(char *zona)
{
    omp_sched_t kind;
    int chunk;

    omp_get_schedule(&kind, &chunk);

    printf("\n--- %s ---\n", zona);
    printf("dyn-var = %d\n", omp_get_dynamic());
    printf("nthreads-var = %d\n", omp_get_max_threads());
    printf("run-sched-var: kind = %d, chunk = %d\n", kind, chunk);
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

    imprimir_variables("Antes de modificar fuera");

    omp_set_dynamic(0);
    omp_set_num_threads(4);
    omp_set_schedule(omp_sched_static, 2);

    imprimir_variables("Despues de modificar fuera");

    #pragma omp parallel
    {
        #pragma omp single
        {
            imprimir_variables("Antes de modificar dentro");

            omp_set_dynamic(1);
            omp_set_num_threads(2);
            omp_set_schedule(omp_sched_guided, 1);

            imprimir_variables("Despues de modificar dentro");
        }

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