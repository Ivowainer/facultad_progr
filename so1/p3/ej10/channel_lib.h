#include <pthread.h>
#include <semaphore.h>

typedef struct
{
    int value;
    sem_t writers, readers;
    pthread_mutex_t mutex;
} channel_t;

void channel_init(channel_t *c);
void chan_write(channel_t *c, int v);
int chan_read(channel_t *c);