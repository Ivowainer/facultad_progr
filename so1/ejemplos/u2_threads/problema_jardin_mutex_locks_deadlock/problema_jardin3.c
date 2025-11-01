/*
    1. Mutex es un problema
    2. Se busca resolver race coindition limitando la region critica (donde se modifica algo de memoria compartida) para que acceda un unico proceso
    3. Se resuelve con LOCK


    Propiedad Safety
    Queremos que a lo sumo un proceso acceda a la seccion critica. Para eso se codeo un Lock

    Solucion 2:  Usar turnos

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N_VISITANTES 2000
int visitante = 0;

int turno = 0;

void *molinete1(void *ptr)
{
    for (int i = 0; i < N_VISITANTES; i++)
    {
        // lock
        turno=2;
        while(turno==2){;}
        // region critica
        visitante++;
        // fin region critica - unlock

        //printf("m2: visitantes: %d\n", visitante);
        turno=2;
        
    }

    return ptr;
}

void *molinete2(void *ptr)
{
    for (int i = 0; i < N_VISITANTES; i++)
    {
        // lock
        turno=1;
        while(turno==1){;}
        // region critica
        visitante++;
        // fin region critica - unlock

        //printf("m1: visitantes: %d\n", visitante);
        turno=1;
    }

    return ptr;
}

int main()
{
    int v = 0;
    pthread_t m1;
    pthread_t m2;

    pthread_create(&m1, NULL, molinete1, &v);
    pthread_create(&m2, NULL, molinete2, &v);

    pthread_join(m1, NULL);
    pthread_join(m2, NULL);

    printf("visitantes: %d\n", visitante);
    return 0;
}