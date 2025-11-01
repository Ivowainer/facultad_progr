#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *stack_create()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->first = NULL;
    stack->last = NULL;

    return stack;
}

void stack_push(Stack *stack, void *data, CopyFunc copy)
{
    SNode *newNode = malloc(sizeof(SNode));
    newNode->data = copy(data);
    newNode->next = NULL;

    if (stack->first == NULL)
    {
        stack->last = newNode;
        stack->first = newNode;
        return;
    }

    stack->last->next = newNode;
    stack->last = newNode;
}

void stack_map(Stack *stack, VisitorFunc visitor)
{
    for (SNode *aux = stack->first; aux != NULL; aux = aux->next)
        visitor(aux->data);
}

void stack_pop(Stack *stack, DestroyerFunc destr)
{
    if (stack->first == stack->last)
    {
        stack->last = NULL;
        stack->first = NULL;
        return;
    }

    SNode *aux = stack->first;

    for (; aux->next != stack->last; aux = aux->next)
        ;

    destr(stack->last->data);
    aux->next = NULL;
    stack->last = aux;
}

int stack_is_empty(Stack *stack)
{
    return stack->first == NULL && stack->last == NULL;
}

void *stack_top(Stack *stack)
{
    return stack->last->data;
}