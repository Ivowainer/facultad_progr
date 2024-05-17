#include <stdio.h>
#include <stdlib.h>

#include "sglist.h"

Stack *stack_create()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->last = NULL;
    stack->start = NULL;
}

void stack_push(Stack *stack, void *dato, CopyFunc copy)
{
    SGNode *newNode = malloc(sizeof(SGNode));
    newNode->dato = copy(dato);
    newNode->next = NULL;

    if (stack->last == NULL && stack->start == NULL)
    {
        stack->start = newNode;
        stack->last = newNode;
        return;
    }

    stack->last->next = newNode;
    stack->last = newNode;
}

void stack_pop(Stack *list)
{
    if (list->last == NULL && list->start == NULL)
        return;

    if (list->start == list->last)
    {
        stack_destroy(list);
        return;
    }

    SGNode *aux = list->start;

    for (; aux->next != list->last; aux = aux->next)
        ;

    free(list->last);
    list->last = aux;
    aux->next = NULL;
}

void stack_destroy(Stack *stack)
{
    for (SGNode *aux = stack->start; aux != NULL; aux = aux->next)
        free(aux->dato);

    free(stack->last);
    free(stack->start);
    free(stack);
}

void stack_map(Stack *stack, VisitorFunc visitor)
{
    for (SGNode *aux = stack->start; aux != NULL; aux = aux->next)
        visitor(aux->dato);
}

void *stack_top(Stack *stack)
{
    return stack->last->dato;
}

// EJ 3
SGList *list_reverse(SGList *list, CopyFunc func)
{
    SGList *newList = stack_create();
    Stack *stack = stack_create();

    int i = 0;

    for (SGNode *aux = list->start; aux != NULL; aux = aux->next)
    {
        stack_push(stack, aux->dato, func);
        i++;
    }

    for (; i != 0; i--)
    {
        stack_push(newList, stack_top(stack), func);
        stack_pop(stack);
    }

    return newList;
}