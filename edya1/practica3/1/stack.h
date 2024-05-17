#include "intarray.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _Stack
{
    IntArray *arr;
    int last;
} _Stack;

typedef _Stack *Stack;

Stack stack_create(int size);
void stack_push(Stack stack, int dato);
void stack_pop(Stack stack);

void stack_print(Stack stack);
int stack_top(Stack stack);
int stack_is_empty(Stack stack);
void stack_destroy(Stack stack);