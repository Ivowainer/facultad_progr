#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_VISITANTE 200000

int visitantes = 0;

void *molinete1(void *p)
{
    for (int i = 0; i < N_VISITANTE; i++)
    {
        visitantes++;
    }
    return p;
}

void *molinete2(void *p)
{
    for (int i = 0; i < N_VISITANTE; i++)
    {
        visitantes = visitantes + 2;
    }
    return p;
}

int main()
{
    pthread_t hilo1;
    pthread_t hilo2;
    pthread_create(&hilo1, NULL, molinete1, NULL);
    pthread_create(&hilo2, NULL, molinete2, NULL);

    /* pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL); */

    printf("VISITANTES: %d\n", visitantes);

    return 0;
}