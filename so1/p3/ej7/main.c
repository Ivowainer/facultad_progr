#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define B 2
#define K (2 * B)

/*
    Veamos que funciona sin usar mutex porque estamos simulando usar uno con el while. Si bien se genera un Busy-waiting, eso no significa que no funcione.
    Además, ambos procesos acceden a un unico recurso s y r por su cuenta, pero protege al ques i comparten, el buf

    No sé admiten más procesos, pues ahí habrían dos procesos que modificar s y r concurrentemente, por lo tanto se genera un race condition
*/

volatile int s = 0, r = 0, buf[B];

static inline int diff() { return (K + s - r) % K; }

void *prod(void *_arg)
{
    int cur = 0;
    while (1)
    {
        while (diff() == B)
            ;
        buf[s % B] = cur++;
        s = (s + 1) % K;
    }
}

void *cons(void *_arg)
{
    int cur;
    while (1)
    {
        while (diff() == 0)
            ;
        cur = buf[r % B];
        r = (r + 1) % K;
        printf("Leí %d\n", cur);
    }
}

int main()
{
    pthread_t prod_t, cons_t;
    pthread_create(&prod_t, NULL, prod, NULL);
    pthread_create(&cons_t, NULL, cons, NULL);

    pthread_join(cons_t, NULL);
    pthread_join(prod_t, NULL);
    return 0;
}
