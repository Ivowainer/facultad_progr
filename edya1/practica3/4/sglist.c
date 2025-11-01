#include <stdio.h>
#include <stdlib.h>
#include "sglist.h"

SGList *list_create()
{
    SGList *newList = malloc(sizeof(SGList));
    newList->first = NULL;
    newList->last = NULL;
}

void list_add_end(SGList *list, void *data, CopyFunc copy)
{
    SGNode *newNode = malloc(sizeof(SGNode));
    newNode->data = copy(data);
    newNode->next = NULL;

    if (list->first == NULL && list->last == NULL)
    {
        list->first = newNode;
        list->last = newNode;
        return;
    }

    SGNode *aux = list->first;
    for (; aux->next != NULL; aux = aux->next)
        ;

    aux->next = newNode;
    list->last = newNode;
}

void list_map(SGList *list, VisitorFunc visitor)
{
    for (SGNode *aux = list->first; aux != NULL; aux = aux->next)
        visitor(aux->data);
}