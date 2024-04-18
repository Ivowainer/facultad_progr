#include <stdio.h>
#include <stdlib.h>
#include "./slist/slist.h"

int compare_func(int n1, int n2)
{
    if (n1 == n2)
        return 1;

    return 0;
}

int compare_func2(int n1, int n2)
{
    if (n1 > n2)
        return -1;

    return 0;
}

int main()
{
    SNode *list1 = NULL;
    SNode *list2 = NULL;
    SNode *list3 = NULL;

    slist_add(&list1, 5);
    slist_add(&list1, 4);

    slist_add(&list2, 9);
    slist_add(&list2, 8);

    slist_add(&list3, 9);
    slist_add(&list3, 5);
    slist_add(&list3, 8);
    slist_add(&list3, 3);

    /* slist_concatenar(&list1, list2); */

    /* slist_insertar(&list1, 6, 2);
    slist_insertar(&list1, 3, 2); */

    /* slist_eliminar(&list1, 8); */

    /* slist_contiene(list1, 8); */

    /* SNode *new_list_intersect = slist_intersecar_custom(list1, list3, &compare_func); */

    /* slist_ordenar(list1, &compare_func2); */
    slist_add_final(&list1, 6);
    slist_add_final(&list1, 7);
    slist_add_final(&list1, 8);

    SNode *list4 = slist_intercalar(list1, list2);

    slist_imprimir(list4);
    /* printf("\n%d", slist_indice(list1, 10));
    printf("\n%d", slist_indice(list1, 5)); */

    /* printf("%d", slist_longitud(list)); */

    return 0;
}