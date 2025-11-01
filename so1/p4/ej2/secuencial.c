#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 500000000

double sum = 0;
unsigned long long int i = 0;
double *arr;

pthread_mutex_t mutex_sum = PTHREAD_MUTEX_INITIALIZER;

void *routine(void *ptr)
{
    for (; i < N; i++)
    {
        pthread_mutex_lock(&mutex_sum);
        sum += arr[i];
        pthread_mutex_unlock(&mutex_sum);
    }
    return NULL;
}
int main()
{
    pthread_t hilos[12]; // cant. de hilos ryzen 5 5600g

    arr = malloc(N * sizeof(double));

    srandom(time(NULL));
    for (unsigned long long int j = 0; j < N; j++)
        arr[j] = ((-1) ^ random() % 2) * ((random() % 1000) * 1.0) / ((random() % 15 * 1.0) + 1);

    for (int k = 0; k < 12; k++)
        pthread_create(&hilos[k], NULL, routine, NULL);

    for (int k = 0; k < 12; k++)
        pthread_join(hilos[k], NULL);

    printf("Suma: %lf\n", sum);

    return 0;
}