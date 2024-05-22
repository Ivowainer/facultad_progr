#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct _QNode
{
    void *data;
    struct _QNode *next;
} QNode;

typedef struct
{
    QNode *first;
    QNode *last;
} Queue;

typedef void *(CopyFunc)(void *);
typedef void (*VisitorFunc)(void *);
typedef void (*DestroyerFunc)(void *);

Queue *queue_create();
void queue_enqueue(Queue *queue, void *data, CopyFunc copy);
void queue_dequeue(Queue *queue, DestroyerFunc destroy);
void *queue_first(Queue *q);
void queue_map(Queue *queue, VisitorFunc visit);

int queue_is_empty(Queue *q);

#endif