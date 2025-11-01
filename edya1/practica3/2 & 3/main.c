#include <stdio.h>
#include <stdlib.h>

#include "sglist.h"

void *copy_func_int(void *dato)
{
    int *new = malloc(sizeof(int));
    *new = *(int *)dato;

    return new;
}

void print_int(void *dato)
{
    printf("%d ", *(int *)dato);
}

int main()
{
    Stack *stack = stack_create();

    int dato = 6;
    int dato2 = 7;
    int dato3 = 8;

    stack_push(stack, &dato, &copy_func_int);
    stack_push(stack, &dato2, &copy_func_int);
    stack_push(stack, &dato3, &copy_func_int);

    stack_map(stack, &print_int);

    // EJ 3
    printf("\n");

    SGList *list = list_reverse(stack, &copy_func_int);
    stack_map(list, &print_int);

    stack_destroy(stack);
    stack_destroy(list);
    return 0;
}