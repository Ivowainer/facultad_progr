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
int full = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_non_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_non_empty = PTHREAD_COND_INITIALIZER;

/* tomo el lock, me fijo que el buffer no esté lleno
    1. Si está lleno, entonces suelto el lock y me quedo esperando a que deje de estarlo (me avisará otro hilo que consuma con signal)
    2. Si no está lleno, aumenta full y le avisa al que esté esperando a que no esté vacio que ya no lo está
*/
void enviar(int *p)
{
    pthread_mutex_lock(&mutex);

    while (full == SZ)
        pthread_cond_wait(&cond_non_full, &mutex);
    buffer[in] = p;
    full++;
    in = (in + 1) % SZ;
    pthread_cond_signal(&cond_non_empty);

    pthread_mutex_unlock(&mutex);
    return;
}

int *recibir()
{
    pthread_mutex_lock(&mutex);

    while (full == 0)
        pthread_cond_wait(&cond_non_empty, &mutex);

    int *ptr = buffer[out];
    full--;
    out = (out + 1) % SZ;

    pthread_cond_signal(&cond_non_full);

    pthread_mutex_unlock(&mutex);
    return ptr;
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

    for (i = 0; i < M; i++)
        pthread_create(&productores[i], NULL, prod_f, i + (void *)0);

    for (i = 0; i < N; i++)
        pthread_create(&consumidores[i], NULL, cons_f, i + (void *)0);

    pthread_join(productores[0], NULL); /* Espera para siempre */
    return 0;
}