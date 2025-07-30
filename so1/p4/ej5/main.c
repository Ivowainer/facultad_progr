#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
int A[N][N], B[N][N], C[N][N];

void mult_secuencial(int A[N][N], int B[N][N], int C[N][N]) {
    int i, j, k;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
}

void mult_parallel(int A[N][N], int B[N][N], int C[N][N]) {
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++) C[i][j] += A[i][k] * B[k][j];
    }
}

void print_matrix(int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}
int main() {
    srand(time(NULL));
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = random() % 1000;
            B[i][j] = random() % 1000;
        }
    }
    mult_parallel(A, B, C);

    /* print_matrix(C); */
    return 0;
}
