#include <stdio.h>
#include <stdlib.h>
#include "./glist.h"

GList *create_list(void *dato, CopyFunc copy)
{
    GList *list = malloc(sizeof(GList));

    GNode *newNode = malloc(sizeof(GNode));
    newNode->dato = copy(dato);
    newNode->next = NULL;

    list->first = newNode;
    list->last = newNode;

    return list;
}

void add_list_first(GList *list, void *dato, CopyFunc copy)
{
    GNode *newNode = malloc(sizeof(GNode));
    newNode->dato = copy(dato);
    newNode->next = list->first;

    list->first = newNode;
}

void add_list_last(GList *list, void *dato, CopyFunc copy)
{
    GNode *newNode = malloc(sizeof(GNode));
    newNode->dato = copy(dato);
    newNode->next = NULL;

    list->last->next = newNode;
    list->last = newNode;
}

void recorrer_list(GList *list, VisitorFunc visitor)
{
    GNode *aux = list->first;

    while (aux != NULL)
    {
        visitor(aux->dato);
        aux = aux->next;
    }
}

GList *glist_filtrar(GList *list, CopyFunc copy, Predicado predicado)
{
    GNode *aux = list->first;

    GList *newList = malloc(sizeof(GList));
    newList->first = NULL;
    newList->last = NULL;

    while (aux != NULL)
    {
        if (predicado(aux->dato))
        {

            if (newList->first == NULL && newList->last == NULL)
            {
                GNode *newNode = malloc(sizeof(GNode));
                newNode->dato = copy(aux->dato);
                newNode->next = NULL;

                newList->first = newNode;
                newList->last = newNode;
            }
            else
                add_list_last(newList, aux->dato, copy);
        }
        aux = aux->next;
    }

    return newList;
}