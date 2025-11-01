#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue queue_create()
{
    Queue queue = malloc(sizeof(SGList));

    queue->first = NULL;
    queue->last = NULL;

    return queue;
}

void queue_enqueue(Queue queue, void *data, CopyFunc copy)
{
    list_add_end(queue, data, copy);
}

int queue_is_empty(Queue queue)
{
    return queue->first == NULL && queue->last == NULL;
}

void queue_dequeue(Queue queue)
{
    if (queue_is_empty(queue))
        return;

    SGNode *aux = queue->first->next;
    free(queue->first->data);
    free(queue->first);

    queue->first = aux;
}

void queue_destroy(Queue queue, DestroyFunc destroy);

void *queue_start(Queue queue)
{
}

void queue_map(Queue queue, VisitorFunc visitor);