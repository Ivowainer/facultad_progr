#include <stdio.h>
#include <stdlib.h>
#include "./cdlist.h"

DList *create_list(int dato)
{
    DNode *newNode = malloc(sizeof(newNode));
    DList *newList = malloc(sizeof(DList));

    newNode->dato = dato;
    newNode->next = newNode;
    newNode->prev = newNode;

    newList->first = newNode;
    newList->last = newNode;

    return newList;
}

void add_final(DList *list, int dato)
{
    DNode *newNode = malloc(sizeof(DNode));
    newNode->dato = dato;
    newNode->prev = list->last;
    newNode->next = list->first;

    list->first->prev = newNode;
    list->last->next = newNode;
    list->last = newNode;
}

void add_start(DList *list, int dato)
{
    DNode *newNode = malloc(sizeof(DNode));
    newNode->dato = dato;
    newNode->prev = list->last;
    newNode->next = list->first;

    list->last->next = newNode;
    list->first->prev = newNode;
    list->first = newNode;
}

void print_list(DList *list)
{
    DNode *aux = list->first;
    do
    {
        printf("%d ", aux->dato);
        aux = aux->next;
    } while (aux != list->first);
}

void cdlist_recorrer(DList *list, void (*FuncVisitante)(int *))
{
    DNode *aux = list->first;

    do
    {
        FuncVisitante(&(aux->dato));
        aux = aux->next;
    } while (aux != list->first);
}