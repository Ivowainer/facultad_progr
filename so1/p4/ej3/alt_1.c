#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 500000000

int main() {
    srand(time(NULL));

    int *arr = malloc(sizeof(int) * N);
    int min = 0;

    printf("Inicializando array...\n");
    for (unsigned long long int i = 0; i < N; i++)
        arr[i] = (i % 2 == 0 ? 1 : -1) * (rand() % N);

    printf("Buscando min: \n");
#pragma omp parallel
    {
        int min_local = 0;
#pragma omp for
        for (unsigned long long int i = 0; i < N; i++) {
            if (arr[i] < min_local) min_local = arr[i];
        }

#pragma omp barrier
#pragma omp critical
        if (min_local < min) min = min_local;
    }

    printf("Min: %d\n", min);
    return 0;
}