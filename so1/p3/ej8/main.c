#include "barrier_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
/* Testeamos el trabajo */

#define N 5
barrier_t barrier;

void *test(void *ptr)
{
    int id = *(int *)ptr;
    printf("Thread %d: antes de la barrera\n", id);
    sleep(rand() % 5);

    barrier_wait(&barrier);

    printf("Thread %d: después de la barrera\n", id);
    return NULL;
}

int main()
{
    pthread_t threads[N];
    int ids[N];
    barrier_init(&barrier, N);

    for (int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, test, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    return 0;
}