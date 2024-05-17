#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

Stack stack_create(int size)
{
    Stack stack = malloc(sizeof(_Stack));
    stack->arr = int_array_create(size);
    stack->last = 0;

    return stack;
}

void stack_push(Stack stack, int dato)
{
    if (stack->last == stack->arr->size - 1)
    {
        int_array_adjust(stack->arr);
        stack->arr->dir[stack->last] = dato;
        stack->last++;
        return;
    }

    stack->arr->dir[stack->last] = dato;
    stack->last++;
}

void stack_pop(Stack stack)
{
    stack->last--;
}

void stack_print(Stack stack)
{
    for (int i = 0; i < stack->last; i++)
        printf("%d ", stack->arr->dir[i]);

    printf("\n");
}

int stack_top(Stack stack) { return stack->arr->dir[stack->last - 1]; }

int stack_is_empty(Stack stack) { return stack->last == 0; }

void stack_destroy(Stack stack)
{
    free(stack->arr->dir);
    free(stack->arr);
    free(stack);
}