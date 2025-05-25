#include <semaphore.h>
#include <pthread.h>
#include "cond_lib.h"

void cond_init(cond_t *cond)
{
    sem_init(&cond->sem, 0, 0);
}

/* Llega, si el sem es 0, entonces se queda en un while y libera el mutex, cuando postean el sem sería una signal */
void cond_wait(cond_t *cond, pthread_mutex_t *external_mutex)
{
    pthread_mutex_unlock(&external_mutex);
    sem_wait(&cond->sem);
    pthread_mutex_lock(&external_mutex);
}

void cond_signal(cond_t *cond)
{
    sem_post(&cond->sem);
}