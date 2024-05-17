#include <stdio.h>
#include <stdlib.h>
#include "intarray.h"

IntArray *int_array_create(int size)
{
    IntArray *arr = malloc(sizeof(IntArray));

    arr->dir = malloc(sizeof(int) * size);
    arr->size = size;

    return arr;
}

void int_array_write(IntArray *arr, int pos, int dato)
{
    arr->dir[pos] = dato;
}

void int_array_print(IntArray *arr)
{
    for (int i = 0; i < arr->size; i++)
        printf("%d ", arr->dir[i]);
}

void int_array_destroy(IntArray *arr)
{
    free(arr->dir);
    free(arr);
}

void int_array_adjust(IntArray *arr)
{
    int new_size = arr->size * 2;

    arr->dir = realloc(arr->dir, sizeof(int) * new_size);
    arr->size = new_size;
}