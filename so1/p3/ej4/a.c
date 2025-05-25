#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define M 5
#define N 5
#define ARRLEN 10240

/*
    Podriamos tener un semaforo inicializado en 1. Si un escritor se mete a modificar, el escritor.post().
    Entonces: los lectores deberían hacer

    Podriamos tener cond_non_can_write, donde el escritor se quede esperando a ser despertado.

    int reading = 0;
    sem_init(&sem_escritores, 0, 1);

    escritores:
        sem_wait(&sem_escritores); // se queda esperando el semaforo  de los escritores

        tomar(mutex)

        while(reading != 0)
            cond_wait(&cond_non_can_write, &mutex); // mientras haya gente leyendo, espero

        escribir();
        reading++;

        soltar(mutex)

        sem_post(&sem_escritores);

        cond_signal(&cond_non_can_read); // <-- despierta a algun lector que esté esperando

    lectores: (¿como evito que lectores puedan leer mientras otro escribe)
        tomar(lock);
        while(reading == 0)
            cond_wait(&cond_non_can_read, &mutex);  // mientras haya un escritor, espero

        leer();
        reading--;


*/
int arr[ARRLEN];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *escritor(void *arg)
{
    int i;
    int num = arg - (void *)0;
    while (1)
    {
        sleep(random() % 3);
        printf("Escritor %d escribiendo\n", num);
        for (i = 0; i < ARRLEN; i++)
            arr[i] = num;
    }
    return NULL;
}

void *lector(void *arg)
{
    int v, i;
    int num = arg - (void *)0;
    while (1)
    {
        sleep(random() % 3);
        v = arr[0];
        for (i = 1; i < ARRLEN; i++)
        {
            if (arr[i] != v)
                break;
        }
        if (i < ARRLEN)
            printf("Lector %d, error de lectura\n", num);
        else
            printf("Lector %d, dato %d\n", num, v);
    }
    return NULL;
}

int main()
{
    pthread_t lectores[M], escritores[N];
    int i;
    for (i = 0; i < M; i++)
        pthread_create(&lectores[i], NULL, lector, i + (void *)0);
    for (i = 0; i < N; i++)
        pthread_create(&escritores[i], NULL, escritor, i + (void *)0);
    pthread_join(lectores[0], NULL); /* Espera para siempre */
    return 0;
}