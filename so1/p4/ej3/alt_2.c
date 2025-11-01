#include <limits.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500000000

int main() {
    srand(time(NULL));

    int *arr = malloc(sizeof(int) * N);

    int max_threads = omp_get_max_threads();
    int *arr_min = malloc(sizeof(int) * max_threads);
    for (int i = 0; i < max_threads; i++) arr_min[i] = INT_MAX;

    printf("Inicializando array...\n");
    for (unsigned int i = 0; i < N; i++) arr[i] = (i % 2 == 0 ? 1 : -1) * (rand() % (N));

    printf("Buscando min: \n");
#pragma omp parallel
    {
        int id = omp_get_thread_num();
#pragma omp for
        for (unsigned int i = 0; i < N; i++) {
            if (arr[i] < arr_min[id]) {
                arr_min[id] = arr[i];
                printf("Thread %d: nuevo min %d en i = %u\n", id, arr[i], i);
            }
        }
    }

    int min = arr_min[0];
    int indice = 0;
    for (int i = 1; i < max_threads; i++) {
        if (arr_min[i] < min) {
            min = arr_min[i];
            indice = i;
        }
    }

    printf("Min: %d, indice: %d\n", min, indice);
    return 0;
}