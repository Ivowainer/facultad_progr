/*
    1. Mutex es un problema
    2. Se busca resolver race coindition limitando la region critica (donde se modifica algo de memoria compartida) para que acceda un unico proceso
    3. Se resuelve con LOCK


    Propiedad Safety
    Queremos que a lo sumo un proceso acceda a la seccion critica. Para eso se codeo un Lock

    SOlucion 1:  Usamos una flag

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int visitante = 0;
int flag = 0;
// 0 la region critica esta desocupada
// 1 la region critica esta ocupada

void *molinete1(void *ptr)
{
    for (int i = 0; i < 200000; i++)
    {
        // lock
        while (flag){;}
        flag = 1;
        // region critica
        visitante++;
        // fin region critica
        flag = 0;
    }

    return ptr;
}

void *molinete2(void *ptr)
{
    for (int i = 0; i < 200000; i++)
    {
        // lock
        while (flag){;}
        flag = 1; // <--- asignacion en C no es atomica
        // region critica
        visitante++;
        // fin region critica, unlock
        flag = 0;
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