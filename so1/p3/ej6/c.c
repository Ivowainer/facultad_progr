#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/* El pusher se encarga de detectar los dos ingredientes que están sobre la mesa y despertar al fumador correcto */

sem_t tabaco, papel, fosforos, otra_vez;
sem_t f1_sem, f2_sem, f3_sem;

volatile int isTabaco = 0, isPapel = 0, isFosforo = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *pusher1(void *ptr)
{
    while (1)
    {
        sem_wait(&tabaco);
        pthread_mutex_lock(&mutex);
        if (isPapel) // ¿hay papel?
        {
            isPapel = 0;       // consume el papel
            sem_post(&f1_sem); // el que tiene fósforos puede fumar
        }
        else if (isFosforo)
        {
            isFosforo = 0;
            sem_post(&f2_sem);
        }
        else
            // Si no hay papel ni fosforo, entonces significa que otro lo consumió, por lo tanto habilito el recurso, el tabaco
            isTabaco = 1;
        pthread_mutex_unlock(&mutex);
    }
}

void *pusher2(void *ptr)
{
    while (1)
    {
        sem_wait(&papel);
        pthread_mutex_lock(&mutex);
        if (isTabaco)
        {
            isTabaco = 0;
            sem_post(&f1_sem);
        }
        else if (isFosforo)
        {
            isFosforo = 0;
            sem_post(&f3_sem);
        }
        else
            isPapel = 1;
        pthread_mutex_unlock(&mutex);
    }
}

void *pusher3(void *ptr)
{
    while (1)
    {
        sem_wait(&fosforos);
        pthread_mutex_lock(&mutex);
        if (isTabaco)
        {
            isTabaco = 0;
            sem_post(&f2_sem);
        }
        else if (isPapel)
        {
            isPapel = 0;
            sem_post(&f3_sem);
        }
        else
            isFosforo = 1;
        pthread_mutex_unlock(&mutex);
    }
}

void agente()
{
    while (1)
    {
        sem_wait(&otra_vez);
        int caso = random() % 3;
        if (caso != 0)
            sem_post(&fosforos);
        if (caso != 1)
            sem_post(&papel);
        if (caso != 2)
            sem_post(&tabaco);
    }
}

void fumar(int fumador)
{
    printf("Fumador %d: Puf! Puf! Puf!\n", fumador);
}

// Tiene fosforo, le falta tabaco y papel
void *fumador1(void *arg)
{
    while (1)
    {
        sem_wait(&f1_sem);
        fumar(1);
        sem_post(&otra_vez);
    }
}

// Tiene papel, le falta fosforo y tabaco
void *fumador2(void *arg)
{
    while (1)
    {
        sem_wait(&f2_sem);
        fumar(2);
        sem_post(&otra_vez);
    }
}

// Tiene tabaco, le falta papel y fosforo
void *fumador3(void *arg)
{
    while (1)
    {
        sem_wait(&f3_sem);
        fumar(3);
        sem_post(&otra_vez);
    }
}

int main()
{
    pthread_t s1, s2, s3;
    pthread_t p1, p2, p3;

    sem_init(&tabaco, 0, 0);
    sem_init(&papel, 0, 0);
    sem_init(&fosforos, 0, 0);
    sem_init(&otra_vez, 0, 1);

    sem_init(&f1_sem, 0, 0);
    sem_init(&f2_sem, 0, 0);
    sem_init(&f3_sem, 0, 0);

    pthread_create(&s1, NULL, fumador1, NULL);
    pthread_create(&s2, NULL, fumador2, NULL);
    pthread_create(&s3, NULL, fumador3, NULL);

    pthread_create(&p1, NULL, pusher1, NULL);
    pthread_create(&p2, NULL, pusher2, NULL);
    pthread_create(&p3, NULL, pusher3, NULL);
    agente();
    return 0;
}
