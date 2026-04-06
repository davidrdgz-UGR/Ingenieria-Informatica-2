#include <stdio.h>
#include <omp.h>

int VE[4096],VR[4096],A[4096*4096];

int prodesc(int *x, int *y, int N) {
        int j,z;
        z = 0;
        for (j=0 ; j<N; j++)
                z += x[j]*y[j];
        return z;
}

void prodmv(int* z,int* x, int* y, int M, int N){ 
        int i;
        #pragma omp for
        for (i = 0; i<M; i++)
                z[i] = prodesc(&x[i*N],y,N);
}

int main(){
        int j, N=4096, i, M=4096;
        for(j=0; j<N; j++)
                VE[j]= j;
        for(i=0; i<M; i++)
                for(j=0; j<N; j++)
                        A[i*N+j]= i+j;
        #pragma omp parallel
        prodmv(VR,A,VE,M,N);
        return 0;
}
