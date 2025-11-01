#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_ARR 10000

int iterator = 0;
int result = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int *make_arr(int *n)
{
    int *arr = malloc(sizeof(int) * (*n));
    for (int i = 0; i < *n; i++)
        arr[i] = i + 1;

    return arr;
}

int sum_n(int n) { return (n * (n + 1)) / 2; }

void *sum_arr1(void **p)
{
    int n = *(int *)p[0];
    while (iterator < n)
    {
        pthread_mutex_lock(&mutex);
        result += *(int *)(p[1] + (iterator * 4));
        iterator++;
        pthread_mutex_unlock(&mutex);
    }
}

void *sum_arr2(void **p)
{
    int n = *(int *)p[0];
    while (iterator < n)
    {
        pthread_mutex_lock(&mutex);
        result += *(int *)(p[1] + (iterator * 4));
        iterator++;
        pthread_mutex_unlock(&mutex);
    }
}

void print_arr(int *arr, int n)
{
    for (int j = 0; j < n; j++)
        printf("%d\n", arr[j]);
}

int main()
{
    srand(time(NULL));
    int n = rand() % MAX_ARR;
    int *arr = make_arr(&n);

    int **as = malloc(sizeof(int) * 2);
    as[0] = &n;
    as[1] = arr;

    pthread_t hilo1;
    pthread_t hilo2;

    pthread_create(&hilo1, NULL, sum_arr1, as);
    pthread_create(&hilo2, NULL, sum_arr2, as);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("N general: %d\n", n);
    printf("SUMA ARR RESULT: %d\n", result);
    printf("SUMA GOD MATE Y TOTO: %d\n", sum_n(n));

    return 0;
}