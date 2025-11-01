#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

/*
    P -> hay pan en la mesa
    M -> hay manteca en la mesa
*/
int P = 0;
int M = 0;
pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void *proceso_b(void *ptr)
{
    sleep(1);
    pthread_mutex_lock(&lk);
    P = 1;
    pthread_cond_signal(&cv); // <-- Acá es el problema, libera el recurso y fuerza a que haya busy waiting en procesoa
    M = 1;
    pthread_mutex_unlock(&lk);
    return NULL;
}

/* Lo que pasa es que proceso_b le manda la señal, el proceso_a trata de tomar el lock luego de ser despertado por el signal pero no puede porque está tomado por el proceso_b, entonces se queda en un busy waiting a que el proceso_b libere el lock, quemando CPU */
void *proceso_a(void *ptr)
{
    pthread_mutex_lock(&lk);
    while (!P && !M)
    {
        printf("me ejecuté\n");
        pthread_cond_wait(&cv, &lk);
    }

    pthread_mutex_unlock(&lk);

    printf("P: %d, M: %d\n", P, M);

    if (!P || !M)
        printf("ROMPO LA CASA!, estado INACEPTABLE\n");
    else
        printf("No rompí la casa!\n");

    return NULL;
}

int main()
{
    pthread_t procesoa;
    pthread_t procesob;

    pthread_create(&procesoa, NULL, proceso_a, NULL);
    pthread_create(&procesob, NULL, proceso_b, NULL);

    pthread_join(procesoa, NULL);
    pthread_join(procesob, NULL);
    printf("Fin!\n");
    return 0;
}