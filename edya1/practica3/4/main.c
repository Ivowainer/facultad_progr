#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void *copy_int(void *data)
{
    int *n = malloc(sizeof(int));
    *n = *(int *)data;

    return n;
}

void print_int(void *data)
{
    printf("%d ", *(int *)data);
}

int main()
{
    int data1 = 76;
    int data2 = 5;
    int data3 = 81;
    int data4 = 45;
    int data5 = 12;

    Queue queue = list_create();
    queue_enqueue(queue, &data1, copy_int);
    queue_enqueue(queue, &data2, copy_int);
    queue_enqueue(queue, &data3, copy_int);
    queue_enqueue(queue, &data4, copy_int);
    queue_enqueue(queue, &data5, copy_int);

    queue_dequeue(queue);
    queue_dequeue(queue);
    queue_dequeue(queue);
    queue_dequeue(queue);
    queue_dequeue(queue);
    queue_dequeue(queue);

    printf("hola");
    list_map(queue, &print_int);

    return 0;
}