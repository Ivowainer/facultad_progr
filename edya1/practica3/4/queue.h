#include "sglist.h"

typedef SGList *Queue;

typedef void (*DestroyFunc)(void *data);

Queue queue_create();
void queue_destroy(Queue queue, DestroyFunc destroy);
int queue_is_empty(Queue queue);
void *queue_start(Queue queue);
void queue_enqueue(Queue queue, void *data, CopyFunc copy);
void queue_dequeue(Queue queue);

void queue_map(Queue queue, VisitorFunc visitor);
