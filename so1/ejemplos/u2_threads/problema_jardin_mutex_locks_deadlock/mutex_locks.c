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
    
    Solucion REAL: algoritmo de la panaderia 
    Busy Waiting -> Implementamos este tipo de waiting en el algoritmo de peterson y de la panaderia,
    consumiendo recursos de procesador. Esto es muy costoso. Para evitarlo, usamos mutex locks
    El mutex debe ser creado en el main (es global) 
    Se define un MUTEX por region critica


    DEADLOCK: ningun proceso avanza porque necesita un recurso que otro proceso ya tiene,
    y se forma un ciclo donde los procesos se bloquean mutuamente de esta forma
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_VISITANTES 100

int visitante = 0;

pthread_mutex_t mutex_visitante = PTHREAD_MUTEX_INITIALIZER;

void *molinete1(void *ptr)
{
    for (int i = 0; i < N_VISITANTES; i++)
    {
        // lock
        pthread_mutex_lock(&mutex_visitante);
        // region critica
        visitante++;
        // fin region critica - unlock
        
        pthread_mutex_unlock(&mutex_visitante);
        printf("m1: visitantes: %d\n", visitante);
    }

    return ptr;
}
void *molinete2(void *ptr)
{
    for (int i = 0; i < N_VISITANTES; i++)
    {
        // lock
        pthread_mutex_lock(&mutex_visitante);
        // region critica
        visitante++;
        // fin region critica - unlock
        pthread_mutex_unlock(&mutex_visitante);
        
        printf("m2: visitantes: %d\n", visitante);
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

    pthread_mutex_destroy(&mutex_visitante);

    printf("visitantes: %d\n", visitante);
    return 0;
}