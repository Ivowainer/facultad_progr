#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 500000000
int main()
{
    srandom(time(NULL));
    double *arr = malloc(N * sizeof(double));
    for (unsigned long long int i = 0; i < N; i++)
        arr[i] = ((-1) ^ random() % 2) * ((random() % 1000) * 1.0) / ((random() % 15 * 1.0) + 1);

    double sum = 0;

#pragma omp parallel
    {
#pragma omp for reduction(+ : sum)
        for (int i = 0; i < N; i++)
            sum += arr[i];
    }

    printf("Suma: %lf\n", sum);

    free(arr);

    return 0;
}