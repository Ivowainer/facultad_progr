#include <semaphore.h>
#include <pthread.h>

typedef struct
{
    int waiting;
    int waiting_quantity;
    sem_t sem;
} cond_t;

void cond_init(cond_t *cond);
void cond_wait(cond_t *cond, pthread_mutex_t *mutex);
void cond_signal(cond_t *cond);
