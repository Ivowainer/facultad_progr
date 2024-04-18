#include <stdio.h>
#include <stdlib.h>
#include "./dlist.h"

int sumar(int *n)
{
    *n = *n + 1;
}

int main()
{
    DList *list = create_list(5);

    add_final(list, 6);
    add_start(list, 4);

    recorrer_list(DLIST_RECORRIDO_HACIA_ATRAS, list, &sumar);

    print_list(list);

    return 0;
}