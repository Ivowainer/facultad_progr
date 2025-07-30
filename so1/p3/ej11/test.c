#include "semaphore_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

semaphore_t sem;

void *t1_func(void *ptr)
{
    printf("T1: Me quedo esperando al semaforo!\n");
    sem_wait(&sem);
    printf("T1: Ahora me ejecuto, el semaforo lo consumí\n");

    return NULL;
}

void *t2_func(void *ptr)
{
    sleep(1);
    printf("T2: Aumento el semaforo porque soy un crack\n");
    sem_post(&sem);

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    sem_init(&sem, 0);

    pthread_create(&t1, NULL, t1_func, NULL);
    pthread_create(&t2, NULL, t2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}