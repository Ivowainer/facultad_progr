#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

void *copy_int(void *data)
{
    int *n = malloc(sizeof(int));
    *n = *(int *)data;

    return n;
}

void print_int(void *data)
{
    printf("%d ", *(int *)data);
}

void print_int_extra(void *data, void *extra)
{
    printf("%d, Extra: %d\n", *(int *)data, *(int *)extra);
}

void destroyer_int(void *data)
{
    free(data);
}

int comp_int(void *data1, void *data2)
{
    if (*(int *)data1 == *(int *)data2)
        return 1;

    return 0;
}

int main()
{
    int dato1 = 1;
    int dato2 = 2;
    int dato3 = 3;
    int dato4 = 4;
    int dato5 = 5;
    int dato6 = 6;
    int dato7 = 7;
    int dato8 = 8;

    /* Queue *q = queue_create();
    queue_enqueue(q, &dato1, copy_int);
    queue_enqueue(q, &dato4, copy_int);
    queue_enqueue(q, &dato5, copy_int);
    queue_enqueue(q, &dato2, copy_int);
    queue_dequeue(q, destroyer_int);
    queue_dequeue(q, destroyer_int);

    queue_map(q, print_int);
    printf("%d", queue_is_empty(q)); */

    BTree ll = btree_join(&dato1, btree_create(), btree_create(), copy_int);
    BTree lrr = btree_join(&dato6, btree_create(), btree_create(), copy_int);
    BTree lr = btree_join(&dato5, btree_create(), lrr, copy_int);
    BTree l = btree_join(&dato2, ll, lr, copy_int);

    BTree rl = btree_join(&dato7, btree_create(), btree_create(), copy_int);
    BTree r = btree_join(&dato3, rl, btree_create(), copy_int);

    BTree root = btree_join(&dato4, l, r, copy_int);

    btree_map(root, BTREE_RECORRIDO_PRE, print_int);
    printf("\nCantidad de nodos: %d ", btree_nodes(root));
    printf("\nSe ha encontrado el num %d: %d", 2, btree_search(root, &dato2, comp_int));

    BTree tree = btree_copy(root, copy_int);
    printf("\nEl nuevo arbol: ");
    btree_map(tree, BTREE_RECORRIDO_PRE_ITERATIVE, print_int);

    printf("\nLa altura del arbol: %d", btree_height(root));
    printf("\nCant. nodos en profunidad %d: %d", 2, btree_nodes_depth(root, 2));
    printf("\nCant. nodos con dato %d: %d", dato1, btree_depth(root, &dato1, comp_int));
    printf("\nCant. datos de los nodos: %d", btree_sum(root));

    printf("\nBFS: ");
    // btree_bfs(tree, print_int);
    btree_bfs_iterative(root, print_int);
    return 0;
}