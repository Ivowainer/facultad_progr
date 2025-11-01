#include "channel_lib.h"
#include <pthread.h>
/* Que sea síncrono implica que no solo el lector espera al escritor (obviamente) sino que el escritor no avanza hasta que haya aparecido un lector */

/* Quiero leer algo que todavia no fue escrito -> me quedo esperando */
/* Quiero escribir para alguien que no está -> me quedo esperando */

void channel_init(channel_t *c)
{
    pthread_cond_init(&c->no_readers, NULL);
    pthread_cond_init(&c->no_writers, NULL);
    pthread_mutex_init(&c->mutex, NULL);
    c->waiting_readers = 0;
    c->waiting_writers = 0;
    c->hasValue = 0;
}

void chan_write(channel_t *c, int v)
{
    /* El escritor no avanza hasta que no aparezca algún lector */ /* Y si hay 3 lectores y 2 escritores summoneado? Se quedará esperando el lector a q haya algo para leer */

    pthread_mutex_lock(&c->mutex);
    c->waiting_writers++;
    while (c->waiting_readers == 0)
        pthread_cond_wait(&c->no_readers, &c->mutex);

    c->value = v;
    c->hasValue = 1;

    c->waiting_writers--;
    pthread_cond_signal(&c->no_writers);
    pthread_mutex_unlock(&c->mutex);
}

/* El problema surge si se ejecuta primer chan_write pero no hay lectores. Cuando haya lectores querrá leer un valor que todavia no fue escrito, pues la señal la tira luego */
int chan_read(channel_t *c)
{
    volatile int value;

    pthread_mutex_lock(&c->mutex);
    c->waiting_readers++;

    pthread_cond_signal(&c->no_readers);

    while (c->waiting_writers == 0 || c->hasValue == 0)
        pthread_cond_wait(&c->no_writers, &c->mutex);

    value = c->value;

    c->waiting_readers--;
    c->hasValue = 0;

    pthread_mutex_unlock(&c->mutex);

    return value;
}
