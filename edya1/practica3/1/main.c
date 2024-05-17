#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main()
{
    Stack stack = stack_create(5);
    stack_push(stack, 6);
    stack_push(stack, 7);
    stack_push(stack, 8);
    stack_pop(stack);
    stack_push(stack, 9);
    stack_print(stack);

    stack_destroy(stack);
    stack_print(stack);

    /* ARRAY VERIFICACION
    for (int i = 0; i < arr->size; i++)
        int_array_write(arr, i, i + 1);

    int_array_print(arr);
    int_array_adjust(arr);

    for (int i = 5; i < arr->size; i++)
        int_array_write(arr, i, i + 1);

    printf("\n");
    int_array_print(arr); */

    return 0;
}