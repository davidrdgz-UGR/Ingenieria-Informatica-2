#include <stdio.h> 
#ifdef _OPENMP
	#include <omp.h> 
#else
	#define omp_get_thread_num() 0 
#endif

int main() {
   int i, n = 7;
   int a[7], suma = 0; 

   for (i=0; i<n; i++) a[i] = i;

   suma = a[i]; 
   #pragma omp parallel for private(suma)
   for (i=0; i<n; i++)
   {
       
       printf("thread %d suma a[%d]=%d\n", omp_get_thread_num(), i, suma);
   }

   printf("\nFuera de la región parallel suma=%d\n", suma); 
   return 0;
}
