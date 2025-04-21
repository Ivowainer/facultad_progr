#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_VISITANTES 20000

int visitantes = 0;

void *proc1(void *arg)
{
    int i;
    int id = arg - (void *)0;
    for (i = 0; i < N_VISITANTES; i++)
    {
        int c;
        c = visitantes;
        sleep(0.1); // Hace cambio de contexto y no llega a actualizar 'c'
        visitantes = c + 1;
    }
    return NULL;
}

int main()
{
    pthread_t hilo1;
    pthread_t hilo2;

    pthread_create(&hilo1, NULL, proc1, NULL);
    pthread_create(&hilo2, NULL, proc1, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("%d\n", visitantes);
    return 0;
}