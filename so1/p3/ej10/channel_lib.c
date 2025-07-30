#include "channel_lib.h"
#include <pthread.h>
/* Que sea síncrono implica que no solo el lector espera al escritor (obviamente) sino que el escritor no avanza hasta que haya aparecido un lector */

/* Quiero leer algo que todavia no fue escrito -> me quedo esperando */
/* Quiero escribir para alguien que no está -> me quedo esperando */

void channel_init(channel_t *c)
{
    pthread_mutex_init(&c->mutex, NULL);
    sem_init(&c->readers, 0, 0);
    sem_init(&c->writers, 0, 0);
}

void chan_write(channel_t *c, int v)
{
    /* El escritor no avanza hasta que no aparezca algún lector */ /* Y si hay 3 lectores y 2 escritores summoneado? Se quedará esperando el lector a q haya algo para leer */
    sem_wait(&c->readers);
    pthread_mutex_lock(&c->mutex);
    c->value = v;
    pthread_mutex_unlock(&c->mutex);
    sem_post(&c->writers);
}

/* El problema surge si se ejecuta primer chan_write pero no hay lectores. Cuando haya lectores querrá leer un valor que todavia no fue escrito, pues la señal la tira luego */
int chan_read(channel_t *c)
{
    volatile int value;
    sem_post(&c->readers);
    sem_wait(&c->writers);
    value = c->value;

    return value;
}
