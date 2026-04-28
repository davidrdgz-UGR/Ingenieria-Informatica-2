#include <stdio.h>
#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

int main() {
   int i, n = 7;
   int a[7], suma = 100; 
   
   for (i=0; i<n; i++) a[i] = i;

   #pragma omp parallel for firstprivate(suma)
   for (i=0; i<n; i++)
   {
       suma = suma + a[i]; 
       printf("thread %d suma a[%d]=%d acumulado=%d\n", omp_get_thread_num(), i, a[i], suma);
   }

   printf("\nFuera de la región parallel suma=%d\n", suma); 
   return 0;
}