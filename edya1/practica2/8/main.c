#include <stdio.h>
#include <stdlib.h>
#include "./sglist.h"

void print_int(int *dato)
{
    printf("%d ", *(dato));
}

int *copy_int(int *dato)
{
    int *num = malloc(sizeof(int));
    *num = *dato;
    return num;
}

void destroy(SGNode *node)
{
    free(node);
}

int compar_int(int *dato1, int *dato2)
{
    if (*dato1 < *dato2)
        return -1;
    else if (*dato1 == *dato2)
        return 0;
    else
        return 1;
}

int main()
{
    int dato = 5;
    int dato2 = 4;
    int dato3 = 6;
    int dato4 = 8;
    int dato5 = 9;

    int dato6 = 7;

    SGList *list = sglist_crear();

    add_first_list(list, &dato, (CopyFunc)copy_int);
    add_first_list(list, &dato2, (CopyFunc)copy_int);
    add_last_list(list, &dato3, (CopyFunc)copy_int);
    add_last_list(list, &dato4, (CopyFunc)copy_int);
    add_last_list(list, &dato5, (CopyFunc)copy_int);

    recorrer_list(list, (VisitorFunc)print_int);
    printf("\n");

    sglist_insertar(list, &dato6, (CopyFunc)copy_int, (CompFunc)compar_int);

    printf("\n");
    recorrer_list(list, (VisitorFunc)print_int);

    sglist_destruir(list, &destroy);
    return 0;
}