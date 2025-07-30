#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
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

    int A[10][10] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},      {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                     {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, {20, 18, 16, 14, 12, 10, 8, 6, 4, 2},
                     {1, 3, 5, 7, 9, 11, 13, 15, 17, 19},  {19, 17, 15, 13, 11, 9, 7, 5, 3, 1},
                     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},       {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
                     {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},       {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}};
    int B[10][10] = {{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                     {0, 1, 0, 1, 0, 1, 0, 1, 0, 1},  {1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
                     {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},  {0, 9, 0, 9, 0, 9, 0, 9, 0, 9},
                     {8, 0, 8, 0, 8, 0, 8, 0, 8, 0},  {0, 7, 0, 7, 0, 7, 0, 7, 0, 7},
                     {6, 0, 6, 0, 6, 0, 6, 0, 6, 0},  {0, 5, 0, 5, 0, 5, 0, 5, 0, 5}};

    mult_parallel(A, B, C);

    print_matrix(C);
    return 0;
}
