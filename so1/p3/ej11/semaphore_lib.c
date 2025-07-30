#include "semaphore_lib.h"

void sem_init(semaphore_t *sem, int value)
{
    sem->contador = value;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->non_zero_cond, NULL);
}

void sem_wait(semaphore_t *sem)
{
    pthread_mutex_lock(&sem->mutex);
    while (sem->contador == 0)
        pthread_cond_wait(&sem->non_zero_cond, &sem->mutex);

    sem->contador--;
    pthread_mutex_unlock(&sem->mutex);
}

void sem_post(semaphore_t *sem)
{
    pthread_mutex_lock(&sem->mutex);
    sem->contador++;
    pthread_cond_signal(&sem->non_zero_cond);
    pthread_mutex_unlock(&sem->mutex);
}