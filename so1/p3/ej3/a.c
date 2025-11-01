#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define M 5
#define N 5
#define SZ 8

/*
 * El buffer guarda punteros a enteros, los
 * productores los consiguen con malloc() y los
 * consumidores los liberan con free()
 */
int *buffer[SZ];

int in = 0, out = 0;
sem_t sem_libres;
sem_t sem_ocupados;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void enviar(int *p)
{
    sem_wait(&sem_libres);
    pthread_mutex_lock(&mutex);
    buffer[in] = p;
    in = (in + 1) % SZ;

    pthread_mutex_unlock(&mutex);
    sem_post(&sem_ocupados);
    return;
}

int *recibir()
{
    sem_wait(&sem_ocupados);
    pthread_mutex_lock(&mutex);
    int *item = buffer[out];
    out = (out + 1) % SZ;
    pthread_mutex_unlock(&mutex);
    sem_post(&sem_libres);

    return item;
}

void *prod_f(void *arg)
{
    int id = arg - (void *)0;
    while (1)
    {
        sleep(random() % 3);

        int *p = malloc(sizeof *p);
        *p = random() % 100;
        printf("Productor %d: produje %p->%d\n", id, p, *p);
        enviar(p);
    }
    return NULL;
}

void *cons_f(void *arg)
{
    int id = arg - (void *)0;
    while (1)
    {
        sleep(random() % 3);

        int *p = recibir();
        printf("Consumidor %d: obtuve %p->%d\n", id, p, *p);
        free(p);
    }
    return NULL;
}

int main()
{
    pthread_t productores[M], consumidores[N];
    int i;

    sem_init(&sem_libres, 0, SZ);
    sem_init(&sem_ocupados, 0, 0);

    for (i = 0; i < M; i++)
        pthread_create(&productores[i], NULL, prod_f, i + (void *)0);

    for (i = 0; i < N; i++)
        pthread_create(&consumidores[i], NULL, cons_f, i + (void *)0);

    pthread_join(productores[0], NULL); /* Espera para siempre */
    return 0;
}