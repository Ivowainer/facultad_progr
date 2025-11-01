#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define N_SILLAS 10
#define N_CLIENTES 100

/*
    - Si no hay clientes para atender, el barbero se pone a dormir
    - Si un cliente llega y todas las sillas est´an ocupadas, se va
    - Si el barbero est´a ocupado pero hay sillas disponibles, se sienta en una y espera a ser atendido
    - Si el barbero est´a dormido, despierta al barbero
*/

/* FLUJO:
    Cliente ve si hay sillas de espera ->
    postea el clientes_disponibles_sem y waitea el barbero_disponible_sem ->

*/

sem_t sillas_disponibles_sem;
sem_t clientes_disponibles_sem;
sem_t barbero_disponible_sem;
sem_t pago_sem;

void me_cortan()
{
    printf("CLIENTE: Me están cortando!\n");
}

void cortando()
{
    printf("BARBERO: Cortando!\n");
}

void pagando()
{
    printf("CLIENTE: Pagando\n");
    sem_post(&pago_sem);
}

void me_pagan()
{
    sem_wait(&pago_sem);
    printf("BARBERO: Me pagan\n");
}

void *cliente(void *ptr)
{
    if (sem_trywait(&sillas_disponibles_sem) < 0)
    {
        printf("CLIENTE: No hay sillas, me voy!\n");
        return NULL;
    }

    sem_post(&clientes_disponibles_sem);
    sem_wait(&barbero_disponible_sem);

    me_cortan();
    pagando();
}

void *barbero(void *ptr)
{
    while (1)
    {
        sem_wait(&clientes_disponibles_sem);
        printf("======== SE SENTÓ CLIENTE NUEVO ========\n");

        sem_post(&barbero_disponible_sem);

        cortando();
        me_pagan();
        sem_post(&sillas_disponibles_sem);
    }
}

int main()
{
    sem_init(&clientes_disponibles_sem, 0, 0);
    sem_init(&sillas_disponibles_sem, 0, N_SILLAS);
    sem_init(&barbero_disponible_sem, 0, 0);

    sem_init(&pago_sem, 0, 0);

    pthread_t clientes_t[N_CLIENTES];
    pthread_t barbero_t;

    for (int i = 0; i < N_CLIENTES; i++)
        pthread_create(&clientes_t[i], NULL, cliente, NULL);

    pthread_create(&barbero_t, NULL, barbero, NULL);
    pthread_join(barbero_t, NULL);
    return 0;
}