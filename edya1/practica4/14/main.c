#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

void *copy_int(void *data)
{
    int *p = malloc(sizeof(int));
    *p = *(int *)data;

    return p;
}

int comp_int(void *data1, void *data2)
{
    int a = *(int *)data1;
    int b = *(int *)data2;

    if (a < b)
        return -1;
    else if (a > b)
        return 1;

    return 0;
}

void destr_int(void *data) { free(data); }

void visit_int(void *data) { printf("%d ", *(int *)data); }

int main()
{
    int data1 = 1, data2 = 2, data3 = 3, data4 = 4, data5 = 5, data6 = 6, data7 = 7, data8 = 8, data9 = 9, data10 = 10;
    int data11 = 11, data12 = 12, data13 = 13, data14 = 14, data15 = 15, data16 = 16, data17 = 17, data18 = 18, data19 = 19, data20 = 20;
    int data21 = 21, data22 = 22, data23 = 23, data24 = 24, data25 = 25, data26 = 26, data27 = 27, data28 = 28, data29 = 29, data30 = 30;

    AVL tree = avl_create();

    /* tree = avl_insert(tree, &data10, copy_int, comp_int);
    tree = avl_insert(tree, &data20, copy_int, comp_int);
    tree = avl_insert(tree, &data15, copy_int, comp_int);
    tree = avl_insert(tree, &data25, copy_int, comp_int);
    tree = avl_insert(tree, &data30, copy_int, comp_int);
    tree = avl_insert(tree, &data16, copy_int, comp_int);
    tree = avl_insert(tree, &data18, copy_int, comp_int);
    tree = avl_insert(tree, &data19, copy_int, comp_int); */

    /* tree = avl_insert(tree, &data15, copy_int, comp_int);
    tree = avl_insert(tree, &data8, copy_int, comp_int);
    tree = avl_insert(tree, &data20, copy_int, comp_int);
    tree = avl_insert(tree, &data23, copy_int, comp_int);
    tree = avl_insert(tree, &data17, copy_int, comp_int);
    tree = avl_insert(tree, &data7, copy_int, comp_int);
    tree = avl_insert(tree, &data2, copy_int, comp_int);
    tree = avl_insert(tree, &data9, copy_int, comp_int);
    tree = avl_insert(tree, &data12, copy_int, comp_int);
    tree = avl_insert(tree, &data6, copy_int, comp_int);
    tree = avl_insert(tree, &data4, copy_int, comp_int);
    tree = avl_insert(tree, &data13, copy_int, comp_int);
    tree = avl_insert(tree, &data1, copy_int, comp_int);

    tree = avl_delete(tree, &data9, comp_int, destr_int);
    tree = avl_delete(tree, &data13, comp_int, destr_int);
    tree = avl_delete(tree, &data20, comp_int, destr_int); */

    tree = avl_insert(tree, &data2, copy_int, comp_int);
    tree = avl_insert(tree, &data6, copy_int, comp_int);
    tree = avl_insert(tree, &data4, copy_int, comp_int);
    avl_map(tree, AVL_PRE, visit_int);
    return 0;
}