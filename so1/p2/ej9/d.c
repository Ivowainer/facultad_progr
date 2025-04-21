#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_VISITANTES 20000000

int visitantes = 0, turno = 0;
int intencion[2] = {0, 0};

pthread_mutex_t molinete = PTHREAD_MUTEX_INITIALIZER;

void *molinete0(void *p)
{
    for (int i = 0; i < MAX_VISITANTES / 2; i++)
    {
        pthread_mutex_lock(&molinete);
        visitantes++;
        pthread_mutex_unlock(&molinete);
    }

    return NULL;
}

void *molinete1(void *p)
{
    for (int i = 0; i < MAX_VISITANTES / 2; i++)
    {
        pthread_mutex_lock(&molinete);
        visitantes++;
        pthread_mutex_unlock(&molinete);
    }

    return NULL;
}

int main()
{
    pthread_t hilo1;
    pthread_t hilo2;

    pthread_create(&hilo1, NULL, molinete0, NULL);
    pthread_create(&hilo2, NULL, molinete1, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    pthread_mutex_destroy(&molinete);

    printf("%d\n", visitantes);

    return 0;
}