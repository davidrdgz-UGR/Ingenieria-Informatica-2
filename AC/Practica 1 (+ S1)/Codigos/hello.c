#include <stdio.h>

#ifdef _OPENMP
        #include <omp.h>
#else
        #define omp_get_thread_num() 0
#endif

int main(int argc, char* argv[]){
        int ID;
        #pragma omp parallel private(ID) 
        {
                ID = omp_get_thread_num(); 
                printf("Hola. Soy el hilo: %d\n",ID);
        }
        return 0;
}
