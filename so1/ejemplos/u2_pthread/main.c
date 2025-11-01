#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *hola(void *p)
{
    printf("HOLA! hola jajajas %d\n", *(int *)p);
    *(int *)p += 1;
    return p;
}

int main()
{
    pthread_t hilo;
    int p = 1;

    void *j = malloc(sizeof(int));

    pthread_create(&hilo, NULL, hola, &p);
    pthread_join(hilo, &j);

    p = *(int *)j;

    printf("%d\n", p);
    return 0;
}