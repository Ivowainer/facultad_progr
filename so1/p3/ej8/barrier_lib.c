#include "barrier_lib.h"

/* Una barrera para n threads tiene una unica operacion barrier_wait() que causa que los threads se pausen hasta que todos lleguen a la barrera */

/* El flujo es: waitea y se van poniendo en el while del cond. Luego, cuando el contador es igual a N ents broadcast */
/* Si está full, entonces pueden continuar (variable de condicion) */

void barrier_init(barrier_t *b, int n)
{
    b->n = n;
    b->contador = 0;
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->is_full_cond, NULL);
}

void barrier_wait(barrier_t *b)
{
    pthread_mutex_lock(&b->mutex);

    b->contador++;
    if (b->contador == b->n)
    {
        pthread_cond_broadcast(&b->is_full_cond);
    }
    else
    {
        while (b->contador < b->n)
            pthread_cond_wait(&b->is_full_cond, &b->mutex);
    }

    pthread_mutex_unlock(&b->mutex);
}