#include <stdio.h>
#include <stdlib.h>
#include "./dlist.h"

DList *create_list(int dato)
{
    DNode *newNode = malloc(sizeof(DNode));
    newNode->dato = dato;
    newNode->next = NULL;
    newNode->prev = NULL;

    DList *newList = malloc(sizeof(DList));

    newList->first = newNode;
    newList->last = newNode;

    return newList;
}

void add_final(DList *list, int dato)
{
    DNode *newNode = malloc(sizeof(DNode));
    newNode->dato = dato;
    newNode->next = NULL;
    newNode->prev = list->last;

    list->last->next = newNode;

    list->last = newNode;
}

void add_start(DList *list, int dato)
{
    DNode *newNode = malloc(sizeof(DNode));
    newNode->dato = dato;
    newNode->prev = NULL;
    newNode->next = list->first;

    list->first->prev = newNode;

    list->first = newNode;
}

void print_list(DList *list)
{
    DNode *aux = list->first;

    while (aux != NULL)
    {
        printf("%d ", aux->dato);
        aux = aux->next;
    }
}

void recorrer_list_last(DList *list, int (*FuncVisitante)(int))
{
    DNode *newNode = list->first;
}

void recorrer_list(DListOrdenDeRecorrido orden, DList *list, int (*FuncVisitante)(int *))
{
    DNode *aux;

    if (orden == DLIST_RECORRIDO_HACIA_ADELANTE)
    {
        aux = list->first;
        while (aux != NULL)
        {
            (*FuncVisitante)(&(aux->dato));
            aux = aux->next;
        }
    }
    else if (orden == DLIST_RECORRIDO_HACIA_ATRAS)
    {
        aux = list->last;
        while (aux != NULL)
        {
            (*FuncVisitante)(&(aux->dato));
            aux = aux->prev;
        }
    }
}