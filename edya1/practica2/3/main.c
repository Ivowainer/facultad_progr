#include <stdio.h>
#include <stdlib.h>

typedef struct _SNode
{
    int dato;
    struct _SNode *sig;
} SNode;

typedef struct
{
    SNode *primero;
    SNode *ultimo;
} SList;

SList *slist_crear(int dato)
{
    SList *newList = malloc(sizeof(SList));

    SNode *newNode = malloc(sizeof(SNode));
    newNode->dato = dato;
    newNode->sig = NULL;

    newList->primero = newNode;
    newList->ultimo = newNode;

    return newList;
}

void slist_agregar_inicio(SList *list, int dato)
{
    SNode *newNode = malloc(sizeof(SNode));
    newNode->dato = dato;
    newNode->sig = list->primero;

    list->primero = newNode;
}

void slist_agregar_final(SList *list, int dato)
{
    SNode *newNode = malloc(sizeof(SNode));
    newNode->dato = dato;
    newNode->sig = NULL;

    list->ultimo->sig = newNode;
    list->ultimo = newNode;
}

void print_list(SList *list)
{
    SNode *aux = list->primero;

    while (aux != NULL)
    {
        printf("%d ", aux->dato);
        aux = aux->sig;
    }
}

int main()
{
    SList *list = slist_crear(5);

    slist_agregar_inicio(list, 4);
    slist_agregar_inicio(list, 3);

    slist_agregar_final(list, 6);
    slist_agregar_final(list, 7);

    print_list(list);

    return 0;
}