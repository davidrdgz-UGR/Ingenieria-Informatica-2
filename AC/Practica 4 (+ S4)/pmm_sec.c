/*** Código para multimplicación secuencial de matrices: m3 = m1 * m2 pmm-secuencial.c **/
// NCC <Ceuta> Version
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void showMatrix(int N, const char* name, double** matrix){
    printf("%s\n", name);
    if(N>9){
        printf("[0][0] = %.2lf, (...), [%d][%d] = %.2lf\n", matrix[0][0], N-1, N-1, matrix[N-1][N-1]);
        return;
    }
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            printf("%.2f\t ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n------------------\n");
}

double** getDoubleMatrix(int N){
    size_t total = (size_t) N * N;
    double* matrix_container = malloc(sizeof(double)*total);
    if(!matrix_container){
        printf("Error: No se puede reservar espacio para la matriz\n");
        return 0;
    }
    double** matrix = malloc(sizeof(double*)*N);
    if(!matrix){
        printf("Error: No se puede reservar espacio para la carcasa de la matriz\n");
        free(matrix_container);
        return 0;
    }
    for(int i = 0; i<N; i++){
        matrix[i] = &(matrix_container[i*N]);
    }
    return matrix;
}

void fillMatrix(int N, double** matrix, double val){
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            matrix[i][j] = val;
        }
    }
}

void freeDoubleMatrix(double** matrix){
    if(matrix){
        free(matrix[0]);
    }
    free(matrix);
}

void naiveProduct(int N, double** m1, double** m2, double** m3){
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                m3[i][j] += m1[i][k] * m2[k][j];
    }
}

void fastProduct(int N, double** m1, double** m2, double** m3){
    for(int i = 0; i < N; i++){

        for(int k = 0; k < N; k++){

            double temp = m1[i][k];

            int j;

            for(j = 0; j <= N - 4; j += 4){
                m3[i][j]     += temp * m2[k][j];
                m3[i][j + 1] += temp * m2[k][j + 1];
                m3[i][j + 2] += temp * m2[k][j + 2];
                m3[i][j + 3] += temp * m2[k][j + 3];
            }

            for(; j < N; j++){
                m3[i][j] += temp * m2[k][j];
            }
        }
    }
}

void testMethod(const char* name, void (*func)(int , double** , double** , double**), int N, double** m1, double** m2, double** m3){
    struct timespec cgt1,cgt2; double ncgt;
    fillMatrix(N, m3, 0.0);
	clock_gettime(CLOCK_MONOTONIC, &cgt1);
	func(N, m1, m2, m3);
	clock_gettime(CLOCK_MONOTONIC, &cgt2);
	ncgt = (cgt2.tv_sec-cgt1.tv_sec) + (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	printf("\n\n%s\n", name);
	printf("Tiempo: %11.9f\t Tamaño: %d\n", ncgt, N);
	showMatrix(N, "Matriz Resultado (m3):", m3);
	printf("-------------------------\n");
}

int main(int argc, char** argv){
    if (argc < 2){
        printf("Uso: %s tamaño\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    if(N<1){
        printf("Aviso. Valores negativos no admitidos. Asumiendo: 5\n");
        N = 5;
    }

    double** m1 = getDoubleMatrix(N);
    double** m2 = getDoubleMatrix(N);
    double** m3 = getDoubleMatrix(N);
    if(!m1 || !m2 || !m3){
        printf("Error: No se han podido reservar todas las matrices!\n");
        freeDoubleMatrix(m1);
        freeDoubleMatrix(m2);
        freeDoubleMatrix(m3);
        return 1;
    }else{
        fillMatrix(N, m1, 1.0);
        fillMatrix(N, m2, 2.0);
    }

    showMatrix(N, "Matriz 1 (m1):", m1);
    showMatrix(N, "Matriz 2 (m2):", m2);
    testMethod("Version inicial:", naiveProduct, N, m1, m2, m3);
    testMethod("Version mejorada:", fastProduct, N, m1, m2, m3);

    freeDoubleMatrix(m1);
    freeDoubleMatrix(m2);
    freeDoubleMatrix(m3);
    return 0;
}
