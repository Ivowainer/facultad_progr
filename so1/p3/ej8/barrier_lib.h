#include <semaphore.h>
#include <pthread.h>

typedef struct
{
    int n;        // n threads que espero que lleguen
    int contador; // contador, cuando contador == n entonces broadcast
    pthread_mutex_t mutex;
    pthread_cond_t is_full_cond;
} barrier_t;

void barrier_init(barrier_t *b, int n);
void barrier_wait(barrier_t *b);