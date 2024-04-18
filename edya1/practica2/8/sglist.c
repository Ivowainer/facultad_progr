#include <stdio.h>
#include <stdlib.h>

#include "sglist.h"

SGList *sglist_crear()
{
    SGList *newList = malloc(sizeof(SGList));

    newList->tail = NULL;
    newList->head = NULL;

    return newList;
}

void add_first_list(SGList *list, void *dato, CopyFunc copy)
{
    SGNode *newNode = malloc(sizeof(SGNode));
    newNode->dato = copy(dato);

    if (list->head == NULL && list->tail == NULL)
    {
        newNode->next = NULL;
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    newNode->next = list->head;
    list->head = newNode;
}

void add_last_list(SGList *list, void *dato, CopyFunc copy)
{
    SGNode *newNode = malloc(sizeof(SGNode));
    newNode->dato = copy(dato);
    newNode->next = NULL;

    if (list->head == NULL && list->tail == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    list->tail->next = newNode;
    list->tail = newNode;
}

void recorrer_list(SGList *list, VisitorFunc visitor)
{
    SGNode *aux = list->head;

    while (aux != NULL)
    {
        visitor(aux->dato);
        aux = aux->next;
    }
}

void sglist_destruir(SGList *list, DestroyFunc destroy)
{
    SGNode *aux = list->head;

    while (aux != NULL)
    {
        SGNode *destroy_node = aux;
        aux = aux->next;
        destroy(destroy_node);
    }
}

void sglist_insertar(SGList *list, void *dato, CopyFunc copy, CompFunc comp)
{
    SGNode *newNode = malloc(sizeof(SGNode));
    newNode->dato = copy(dato);

    SGNode *aux = list->head;

    while (aux->next != NULL && comp(aux->next->dato, dato) < 0)
    {
        aux = aux->next;
    }

    if (aux->next == NULL)
    {
        list->tail->next = newNode;
        list->tail = newNode;

        return;
    }

    newNode->next = aux->next;
    aux->next = newNode;
}