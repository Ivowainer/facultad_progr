#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *hola(void *p)
{
    printf("HELLO WORLD %d\n", *(int *)p);
}

int main()
{
    pthread_t hilo;
    int p = 1;
    pthread_create(&hilo, NULL, hola, &p);
    sleep(1);
    return 0;
}