#include "channel_lib.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

channel_t canal;

void *reader(void *arg)
{
    int id = *(int *)arg;
    printf("Reader %d esperando...\n", id);
    int v = chan_read(&canal);
    printf("Reader %d leyó: %d\n", id, v);
    return NULL;
}

void *writer(void *arg)
{
    int v = *(int *)arg;
    printf("Writer escribiendo: %d\n", v);
    chan_write(&canal, v);
    printf("Writer terminó de escribir: %d\n", v);
    return NULL;
}

int main()
{
    channel_init(&canal);

    pthread_t r1, r2, w1;
    int reader_ids[2] = {1, 2};
    int val = 42;

    pthread_create(&r1, NULL, reader, &reader_ids[0]);
    sleep(1); // Asegura que el lector se bloquee antes que el escritor
    pthread_create(&w1, NULL, writer, &val);
    sleep(1);
    pthread_create(&r2, NULL, reader, &reader_ids[1]);

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);

    return 0;
}
