#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_VISITANTES 200000

int visitantes = 0;

void *molinete(void *p)
{
    for (int i = 0; i < MAX_VISITANTES; i++)
        visitantes++;
}

int main()
{
    pthread_t hilo;
    pthread_create(&hilo, NULL, molinete, NULL);
    pthread_join(hilo, NULL);

    printf("%d\n", visitantes);
    return 0;
}