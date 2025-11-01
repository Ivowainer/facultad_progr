#include "bstree.h"
#include <stdio.h>
#include <stdlib.h>

BSTree bstree_create() { return NULL; }

BSTree bstree_insert(BSTree tree, void *data, FuncCopy copy, FuncComp comp)
{
    if (tree == NULL)
    {
        tree = malloc(sizeof(BSTNode));
        tree->data = copy(data);
        tree->left = NULL;
        tree->right = NULL;
    }
    else if (comp(data, tree->data) < 0)
        tree->left = bstree_insert(tree->left, data, copy, comp);
    else
        tree->right = bstree_insert(tree->right, data, copy, comp);

    return tree;
}

void preorder(BSTree tree, FuncVisit visit)
{
    if (tree == NULL)
        return;

    visit(tree->data);
    preorder(tree->left, visit);
    preorder(tree->right, visit);
}

void inorder(BSTree tree, FuncVisit visit)
{
    if (tree == NULL)
        return;

    inorder(tree->left, visit);
    visit(tree->data);
    inorder(tree->right, visit);
}

void bstree_map(BSTree tree, BSTreeMap order, FuncVisit visit)
{
    if (order == BTREE_MAP_PRE)
        preorder(tree, visit);
    else if (order == BTREE_MAP_IN)
        inorder(tree, visit);

    printf("\n");
}

/* EJERCICIO 9 */
BSTree minimum_left_padre(BSTree tree)
{
    if (tree->left != NULL)
    {
        if (tree->left->left == NULL)
            return tree;
        return minimum_left_padre(tree->left);
    }
    else
        return tree;
}

BSTree deleteNode(BSTree tree, FuncDestroy destr)
{
    if (tree == NULL || (!tree->left && !tree->right)) // es una hoja
        return NULL;

    if (tree->right && tree->left)
    {
        BSTree minimum_padre = minimum_left_padre(tree->right);

        BSTree minimum = minimum_padre->left ? minimum_padre->left : minimum_padre;

        minimum_padre->left = deleteNode(minimum_padre->left, destr);

        minimum->left = tree->left;

        if (tree->right == minimum)
            minimum->right = tree->right->right;
        else
            minimum->right = tree->right;

        destr(tree->data);
        free(tree);

        return minimum;
    }
    else if (tree->right)
        return tree->right;
    else if (tree->left)
        return tree->left;
}

BSTree bstree_delete(BSTree tree, void *data, FuncComp comp, FuncDestroy destr)
{
    if (tree == NULL)
        return NULL;
    if (comp(data, tree->data) == 0)
    {
        tree = deleteNode(tree, destr);
        return tree;
    }
    else if (comp(data, tree->data) > 0)
        tree->right = bstree_delete(tree->right, data, comp, destr);
    else
        tree->left = bstree_delete(tree->left, data, comp, destr);
}

// 10.

void inorder_traversal(BSTree tree, int *k, void **result)
{
    if (tree == NULL || *result != NULL)
        return;

    inorder_traversal(tree->left, k, result);

    (*k)--;

    if (*k == 0)
    {
        *result = tree->data;
        return;
    }

    inorder_traversal(tree->right, k, result);
}

void *bstree_k_esimo_menor(BSTree tree, int k)
{
    void *result = NULL;

    inorder_traversal(tree, &k, &result);

    return result;
}

int min(int a, int b)
{
    if (a > b)
        return b;

    return a;
}

// Ej 11.

int btree_validar_aux(BSTree tree, BSTree root, FuncComp comp, int isLeft)
{
    if (tree == NULL)
        return 1;

    if ((isLeft && comp(tree->data, root->data) > 0) || (!isLeft && comp(tree->data, root->data) < 0))
        return 0;

    return btree_validar_aux(tree->left, root, comp, isLeft) && btree_validar_aux(tree->right, root, comp, isLeft);
}

/* int btree_validar(BSTree tree, FuncComp comp)
{

    return btree_validar_aux(tree->left, tree, comp, 1) && btree_validar_aux(tree->right, tree, comp, 0);
} */

int btree_validar(BSTree tree, FuncComp comp)
{
    if (tree == NULL)
        return 1;

    int izq = btree_validar(tree->left, comp);

    if (tree->left && tree->right)
    {
    }
    /* if(comp(tree->data, )) */

    int der = btree_validar(tree->right, comp);

    return izq == der;
}

// extra

void *btree_search(BSTree tree, void *data, FuncComp comp)
{
    if (!tree)
        return NULL;

    if (comp(tree->data, data) == 0)
        return tree->data;

    void *izq = btree_search(tree->left, data, comp);
    void *der = btree_search(tree->right, data, comp);

    return izq ? izq : der;
}