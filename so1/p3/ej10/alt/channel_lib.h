#include <pthread.h>

typedef struct
{
    int value;
    int waiting_writers;
    int waiting_readers;
    int hasValue;
    pthread_cond_t no_readers;
    pthread_cond_t no_writers;
    pthread_mutex_t mutex;
} channel_t;

void channel_init(channel_t *c);
void chan_write(channel_t *c, int v);
int chan_read(channel_t *c);