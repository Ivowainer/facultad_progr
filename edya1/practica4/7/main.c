#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

void *copy_int(void *data)
{
    int *n = malloc(sizeof(int));
    *n = *(int *)data;

    return n;
}

/* Toma el nodo a añadir y luego el actual */
// Primer dato es mayor, retorna derecha
int comp_int(void *a, void *b)
{
    int nodeToAdd = *(int *)a;
    int node = *(int *)b;
    if (nodeToAdd == node)
        return 0;
    else if (nodeToAdd > node)
        return 1;

    return -1;
}

void print_int(void *data)
{
    if (data == NULL)
        return;
    printf("%d ", *(int *)data);
}

void destroy_int(void *data)
{
    free(data);
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
    int dato9 = 9;
    int dato10 = 10;

    BSTree tree = bstree_create();
    tree = bstree_insert(tree, &dato4, copy_int, comp_int);
    tree = bstree_insert(tree, &dato6, copy_int, comp_int);
    tree = bstree_insert(tree, &dato5, copy_int, comp_int);
    tree = bstree_insert(tree, &dato10, copy_int, comp_int);
    tree = bstree_insert(tree, &dato8, copy_int, comp_int);
    tree = bstree_insert(tree, &dato9, copy_int, comp_int);
    tree = bstree_insert(tree, &dato2, copy_int, comp_int);
    tree = bstree_insert(tree, &dato3, copy_int, comp_int);
    tree = bstree_insert(tree, &dato1, copy_int, comp_int);

    BSTree tree4 = malloc(sizeof(BSTNode));
    tree4->left = malloc(sizeof(BSTNode));
    tree4->left->left = malloc(sizeof(BSTNode));
    tree4->left->right = malloc(sizeof(BSTNode));
    tree4->right = malloc(sizeof(BSTNode));

    tree4->right->left = NULL;
    tree4->right->right = NULL;
    tree4->left->left->left = NULL;
    tree4->left->left->right = NULL;
    tree4->left->right->left = NULL;
    tree4->left->right->right = NULL;

    tree4->data = copy_int(&dato5);
    tree4->left->data = copy_int(&dato4);
    tree4->left->left->data = copy_int(&dato2);
    tree4->left->right->data = copy_int(&dato6);
    tree4->right->data = copy_int(&dato7);

    printf("Arbol original: ");
    bstree_map(tree, BTREE_MAP_PRE, print_int);

    tree = bstree_delete(tree, &dato6, comp_int, destroy_int);

    printf("Arbol sin el 6: ");
    bstree_map(tree, BTREE_MAP_PRE, print_int);

    printf("6 elemento menor: ");
    print_int(bstree_k_esimo_menor(tree, 6));
    printf("\n");

    printf("El arbol es valido: %d", btree_validar(tree4, comp_int));

    printf("\nDato encontrado: ");
    print_int(btree_search(tree, &dato6, comp_int));

    return 0;
}