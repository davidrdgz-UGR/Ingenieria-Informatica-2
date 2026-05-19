#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int i, n = 20, tid;
    int a[20], suma = 0, sumalocal;
    int x;

    if (argc < 3) {
        fprintf(stderr, "[ERROR] Uso: %s <iteraciones> <num_threads>\n", argv[0]);
        exit(-1);
    }

    n = atoi(argv[1]);
    if (n > 20) n = 20;

    x = atoi(argv[2]);

    for (i = 0; i < n; i++) {
        a[i] = i;
    }

    #pragma omp parallel if(n > 4) num_threads(x) default(none) \
        private(sumalocal, tid, i) shared(a, suma, n)
    {
        sumalocal = 0;
        tid = omp_get_thread_num();

        #pragma omp for schedule(static) nowait
        for (i = 0; i < n; i++) {
            sumalocal += a[i];
            printf("thread %d suma de a[%d]=%d sumalocal=%d\n",
                   tid, i, a[i], sumalocal);
        }

        #pragma omp atomic
        suma += sumalocal;

        #pragma omp barrier

        #pragma omp master
        printf("thread master=%d imprime suma=%d\n", tid, suma);
    }

    return 0;
}