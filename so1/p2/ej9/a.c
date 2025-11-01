#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_VISITANTES 200000

int visitantes = 0;

void *molinete(void *p)
{
    for (int i = 0; i < MAX_VISITANTES; i++)
        visitantes++;

    return NULL;
}

int main()
{
    pthread_t hilo1;
    pthread_t hilo2;

    pthread_create(&hilo1, NULL, molinete, NULL);
    pthread_create(&hilo2, NULL, molinete, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("%d\n", visitantes);

    return 0;
}