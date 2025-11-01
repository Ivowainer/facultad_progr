#include <stdio.h>
#include <stdlib.h>
#include "./glist.h"

int *copy_int(int *dato)
{
    int *new_dato = malloc(sizeof(int));
    *new_dato = *dato;

    return new_dato;
}

void print_int(void *dato)
{
    printf("%d ", *(int *)dato);
}

void sumar_int(void *dato)
{
    *(int *)dato = *(int *)dato + 1;
}

int predicado_int(void *dato)
{
    int num_parse = *(int *)(dato);
    if (num_parse % 2 == 0)
        return 1;

    return 0;
}

int main()
{
    int dato = 5;
    int dato2 = 4;
    int dato3 = 6;
    int dato4 = 7;
    int dato5 = 8;

    GList *list = create_list(&dato, (CopyFunc)copy_int);

    add_list_first(list, &dato2, (CopyFunc)copy_int);
    add_list_last(list, &dato3, (CopyFunc)copy_int);
    add_list_last(list, &dato4, (CopyFunc)copy_int);
    add_list_last(list, &dato5, (CopyFunc)copy_int);

    /* recorrer_list(list, sumar_int); */
    recorrer_list(list, print_int);

    printf("\n");
    GList *list2 = glist_filtrar(list, (CopyFunc)copy_int, &predicado_int);
    recorrer_list(list2, print_int);

    return 0;
}