#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/*
    a. Se genera Hold-n-wait, por ejemplo:
        el fumador1 consigue tabaco y le falta papel
        el fumador2 consigue fosforo y le falta tabaco
    Entonces ambos se quedan esperando a que les llegue el recurso faltante, pero no se ejecutará nunca el "fumar" ni aumentará "otra vez"

    b. No, no se pueden ordenar, pues seguirá habiendo el mismo problema. El problema es como acceden al recurso, no el orden
*/

sem_t tabaco, papel, fosforos, otra_vez;

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
        sem_wait(&tabaco);
        sem_wait(&papel);
        fumar(1);
        sem_post(&otra_vez);
    }
}

// Tiene papel, le falta fosforo y tabaco
void *fumador2(void *arg)
{
    while (1)
    {
        sem_wait(&fosforos);
        sem_wait(&tabaco);
        fumar(2);
        sem_post(&otra_vez);
    }
}

// Tiene tabaco, le falta papel y fosforo
void *fumador3(void *arg)
{
    while (1)
    {
        sem_wait(&papel);
        sem_wait(&fosforos);
        fumar(3);
        sem_post(&otra_vez);
    }
}

int main()
{
    pthread_t s1, s2, s3;

    sem_init(&tabaco, 0, 0);
    sem_init(&papel, 0, 0);
    sem_init(&fosforos, 0, 0);
    sem_init(&otra_vez, 0, 1);

    pthread_create(&s1, NULL, fumador1, NULL);
    pthread_create(&s2, NULL, fumador2, NULL);
    pthread_create(&s3, NULL, fumador3, NULL);
    agente();
    return 0;
}
