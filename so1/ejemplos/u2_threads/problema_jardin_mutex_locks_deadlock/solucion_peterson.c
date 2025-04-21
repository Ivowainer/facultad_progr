/*
    1. Mutex es un problema
    2. Se busca resolver race coindition limitando la region critica (donde se modifica algo de memoria compartida) para que acceda un unico proceso
    3. Se resuelve con LOCK

    Propiedad Safety
    Queremos que a lo sumo un proceso acceda a la seccion critica. Para eso se codeo un Lock

    Usar turnos secuencializa el programa y perdemos paralelismo

    Propiedad liveness
        Ausencia de Deadlock: Si hay procesos intentado tomar/soltar a un
        lock, algún proceso va a tomar/soltar el lock.
        Es decir, hay que garantizar que no quede bloqueado el thread sin poder avanzar, cuando en realidad no deberia por que quedarse bloqueado.

    Solucion NO TAN REAL: algoritmo PETERSON
        - Mezcla de turnos y banderas
        - Ausencia de inanicion: siempre que un proceso quiera entrar a una zona critica, lo va hacer
        - Ausencia de Deadlock: Si tengo p1, p2 y p3, no me asegura que p3 ejecute
        SOLO SIRVE PARA DOS PROCESOS
        ADEMAS, este algoritmo fue pensado para un solo nucleo. Ahora trabajamos con multiprocesadores y cada uno tiene una unidad de cache.
        Ademas, se puede dar la situacion de que las instrucciones se ejecuten fuera de orden por optimizaciones de la CPU. Esto incluso sucede en sistemas de un solo procesador

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N_VISITANTES 500000
int visitante = 0;

int flag[2] = {0, 0};
// 0: no tengo intencion de entrar a la RC
// 1: tengo intencion de entrar a la RC
int turno = 0;

void *molinete1(void *ptr)
{
    for (int i = 0; i < N_VISITANTES; i++)
    {
        // lock
        flag[0] = 1;
        turno = 2;
        while (flag[1] == 1 && turno == 2)
        {
            ;
        }
        // region critica
        visitante++;
        // fin region critica - unlock

        // printf("m1: visitantes: %d\n", visitante);
        flag[0] = 0;
    }

    return ptr;
}
void *molinete2(void *ptr)
{
    for (int i = 0; i < N_VISITANTES; i++)
    {
        // lock
        flag[1] = 1;
        turno = 1;
        while (flag[0] == 1 && turno == 1)
        {
            ;
        }
        // region critica
        visitante++;
        // fin region critica - unlock

        // printf("m2: visitantes: %d\n", visitante);
        // sleep(0.001);
        flag[1] = 0;
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