#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

#define VISITANTE_MAX 200000

int visitante = 0;

int intencion[2] = {0, 0};
int turno = 0;

void *molinete1(void *args)
{
    for (int i = 0; i < VISITANTE_MAX; i++)
    {
        intencion[0] = 1;
        turno = 1;
        while (intencion[1] == 1 && turno == 1)
            ;
        visitante++;

        printf("m2: visitantes: %d\n", visitante);
        intencion[0] = 0;
    }
    return args;
}
void *molinete2(void *args)
{

    for (int i = 0; i < VISITANTE_MAX; i++)
    {
        intencion[1] = 1;
        turno = 0;
        while (intencion[0] == 1 && turno == 0)
            ;

        visitante++;
        printf("m1: visitantes: %d\n", visitante);

        intencion[1] = 0;
    }
    return args;
}

int main()
{
    pthread_t hilo1, hilo2;
    pthread_create(&hilo1, NULL, molinete1, NULL);
    pthread_create(&hilo2, NULL, molinete1, NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("VISITANTE: %d\n", visitante);
    return 0;
}