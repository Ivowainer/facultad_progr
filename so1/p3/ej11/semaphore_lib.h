#include <pthread.h>

typedef struct
{
    int contador;
    pthread_cond_t non_zero_cond;
    pthread_mutex_t mutex;
} semaphore_t;

void sem_init(semaphore_t *sem, int value);
void sem_wait(semaphore_t *sem);
void sem_post(semaphore_t *sem);