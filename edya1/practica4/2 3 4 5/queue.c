#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *queue_create()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last = NULL;
    return queue;
}

void queue_enqueue(Queue *queue, void *data, CopyFunc copy)
{
    QNode *newNode = malloc(sizeof(QNode));
    newNode->data = copy(data);
    newNode->next = NULL;

    if (queue->first == NULL)
    {
        queue->first = newNode;
        queue->last = newNode;
        return;
    }

    queue->last->next = newNode;
    queue->last = newNode;
}

void queue_dequeue(Queue *queue, DestroyerFunc destroy)
{
    QNode *aux = queue->first;

    if (aux == NULL)
        return;

    queue->first = aux->next;

    destroy(aux);
}

void *queue_first(Queue *q)
{
    return q->first->data;
}

void queue_map(Queue *queue, VisitorFunc visit)
{
    QNode *aux = queue->first;
    while (aux != NULL)
    {
        visit(aux->data);
        aux = aux->next;
    }
}

int queue_is_empty(Queue *q)
{
    if (q->first == NULL)
        return 1;

    return 0;
}