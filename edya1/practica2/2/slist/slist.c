#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

void slist_add(SNode **node, int dato)
{
    SNode *newNode = malloc(sizeof(SNode));
    newNode->dato = dato;
    newNode->sig = *node;

    *node = newNode;
}

void slist_add_final(SNode **list, int dato)
{
    SNode *newNode = malloc(sizeof(SNode));
    newNode->sig = NULL;
    newNode->dato = dato;

    SNode *aux = *list;
    for (; aux->sig != NULL; aux = aux->sig)
        ;

    aux->sig = newNode;
}

int slist_longitud(SNode *node)
{
    SNode *aux = node;
    int i = 0;

    while (aux->sig != NULL)
    {
        i++;
        aux = aux->sig;
    }

    i += 1;
    return i;
}

void slist_concatenar(SNode **list1, SNode *list2)
{

    // Itera hasta el ultimo elemento de list1, es decir, es NULL y a ese mismo le asigna el primero de list2
    SNode *aux = *list1;
    while (aux->sig != NULL)
    {
        aux = aux->sig;
    }

    // Ahora aux es el nodo NULL, entonces se le asigna al siguiente el primero de list2
    aux->sig = list2;
}

void slist_imprimir(SNode *list)
{
    SNode *aux = list;

    printf("%d ", aux->dato);

    while (aux->sig != NULL)
    {
        aux = aux->sig;
        printf("%d ", aux->dato);
    }
}

void slist_insertar(SNode **list, int dato, int pos)
{
    if (pos >= slist_longitud(*list) || pos < 1)
    {
        printf("No se pudo completar la operacion");
        return;
    }

    SNode *newNode = malloc(sizeof(SNode));
    newNode->dato = dato;

    SNode *aux = *list;
    int i = 1;

    while (i != pos)
    {
        i++;
        aux = aux->sig;
    }

    newNode->sig = aux->sig;
    aux->sig = newNode;
}

void slist_eliminar(SNode **list, int dato)
{
    SNode *aux = *list;
    SNode *prev = NULL;

    while (aux != NULL && aux->dato != dato)
    {
        prev = aux;
        aux = aux->sig;
    }

    if (aux == NULL)
    {
        printf("No se pudo encontrar el valor");
        return;
    }

    prev->sig = aux->sig;
    free(aux);
}

int slist_contiene(SNode *list, int dato)
{
    SNode *aux = list;

    while (aux != NULL && aux->dato != dato)
        aux = aux->sig;

    if (aux == NULL)
        return 0;

    return 1;
}

int slist_indice(SNode *list, int dato)
{
    SNode *aux = list;
    int i = 0;

    while (aux != NULL && aux->dato != dato)
    {
        i++;
        aux = aux->sig;
    }

    if (aux == NULL)
        return -1;

    return i;
}

SNode *slist_intersecar(SNode *list1, SNode *list2)
{
    SNode *newList = NULL;

    SNode *aux1 = list1;

    SNode *prev_aux2 = list2;

    int long1 = slist_longitud(list1);
    int long2 = slist_longitud(list2);

    for (int i = 1; i <= long1; i++)
    {
        /* for (int j = 1; j <= long2; j++)
        {
            if (aux1->dato == aux2->dato && !slist_contiene(newList, aux1->dato))
            {
                slist_add(&newList, aux1->dato);
            }

            aux2 = aux2->sig;

            if (j == long2)
                aux2 = prev_aux2;
        } ERA RE BURRO PERO AHORA NO 🫢🫢*/
        if (slist_contiene(list2, aux1->dato) && !slist_contiene(newList, aux1->dato))
            slist_add(&newList, aux1->dato);

        aux1 = aux1->sig;
    }

    return newList;
}

SNode *slist_intersecar_custom(SNode *list1, SNode *list2, compare_function compare_function)
{
    SNode *newList = NULL;

    SNode *aux1 = list1;
    SNode *aux2 = list2;

    SNode *prev_aux2 = list2;

    int long1 = slist_longitud(list1);
    int long2 = slist_longitud(list2);

    for (int i = 1; i <= long1; i++)
    {
        for (int j = 1; j <= long2; j++)
        {
            if ((*compare_function)(aux1->dato, aux2->dato))
            {
                slist_add(&newList, aux1->dato);
            }

            aux2 = aux2->sig;

            if (j == long2)
                aux2 = prev_aux2;
        }

        aux1 = aux1->sig;
    }

    return newList;
}

void slist_ordenar(SNode *list, compare_function2 func)
{
    for (SNode *node = list; node->sig != NULL; node = node->sig)
    {
        for (SNode *node2 = node->sig; node2 != NULL; node2 = node2->sig)
        {
            if (func(node->dato, node2->dato) == -1)
            {
                int aux = node->dato;
                node->dato = node2->dato;
                node2->dato = aux;
            }
        }
    }
}

SNode *slist_intercalar(SNode *list1, SNode *list2)
{
    SNode *newList = malloc(sizeof(SNode));
    newList->dato = list1->dato;
    newList->sig = NULL;

    SNode *aux = list1->sig;
    SNode *aux2 = list2;
    int i = 1;

    while (aux != NULL)
    {
        if (aux2 == NULL)
        {
            slist_add_final(&newList, aux->dato);
            aux = aux->sig;
        }
        else if (i % 2 == 0)
        {
            slist_add_final(&newList, aux->dato);
            aux = aux->sig;
        }
        else
        {
            slist_add_final(&newList, aux2->dato);
            aux2 = aux2->sig;
        }

        i++;
    }

    return newList;
}