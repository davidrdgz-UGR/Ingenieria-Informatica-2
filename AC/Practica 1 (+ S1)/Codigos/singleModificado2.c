#include <stdio.h>
#include <omp.h>

int main() {
    int n = 9, i, a, b[n];

    for (i = 0; i < n; i++)
        b[i] = -1;

    #pragma omp parallel shared(a, b, n) private(i)
    {
        #pragma omp single
        {
            printf("Introduce valor de inicialización a: ");
            scanf("%d", &a);
            printf("Single de entrada ejecutada por el thread %d\n",
                   omp_get_thread_num());
        }

        #pragma omp for
        for (i = 0; i < n; i++)
            b[i] = a;

        #pragma omp barrier

        #pragma omp master
        {
            printf("Master de impresión ejecutada por el thread %d\n",
                   omp_get_thread_num());
            printf("Después de la región parallel:\n");
            for (i = 0; i < n; i++)
                printf("b[%d] = %d\t", i, b[i]);
            printf("\n");
        }
    }

    return 0;
}