#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define M 5
#define N 5
#define ARRLEN 10240

/*
    Podriamos tener un semaforo inicializado en 1. Si un escritor se mete a modificar, el escritor.post().
    Entonces: los lectores deberían hacer

    Podriamos tener cond_non_can_write, donde el escritor se quede esperando a ser despertado.

    int reading = 0;

    escritores:
        sem_wait(&sem_escritores); // se queda esperando el semaforo  de los escritores




    reading++;

    Podriamos tener una variable de condicion, is_non_writing_cond, entonces, si un escritor se mete a modificar, la cond
*/
sem_t sem;

void *rutina(void *arg)
{
    sem_wait(&sem);
    printf("hola\n");
    return NULL;
}

int main()
{
    sem_init(&sem, 0, 1);
    pthread_t test;
    pthread_create(&test, NULL, rutina, NULL);
    pthread_join(test, NULL);
    return 0;
}