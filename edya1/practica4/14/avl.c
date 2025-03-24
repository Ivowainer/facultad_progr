#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

AVL avl_create() { return NULL; }

static AVL avl_rotate_simple_l(AVL tree)
{
    AVL aux = tree->right->left;
    AVL a = tree->right;

    tree->right->left = tree;
    tree->right = aux;

    return a;
}

static AVL avl_rotate_simple_r(AVL tree)
{
    AVL aux = tree->left->right;
    AVL a = tree->left;

    tree->left->right = tree;
    tree->left = aux;

    return a;
}

int avl_balance_factor(AVL tree)
{
    if (tree == NULL)
        return 1;

    return avl_altura(tree->left) - avl_altura(tree->right);
}

static AVL avl_balancear(AVL tree)
{
    int factor_root = avl_balance_factor(tree);

    if (factor_root > 1) // está desbalanceado por izquierda
    {
        if (avl_balance_factor(tree->left) == -1) // Rotacion doble
            tree->left = avl_rotate_simple_l(tree->left);

        tree = avl_rotate_simple_r(tree);
    }

    if (factor_root < -1) // desbalanceado por derecha
    {
        if (avl_balance_factor(tree->right) == 1) // Rotacion doble
            tree->right = avl_rotate_simple_r(tree->right);

        tree = avl_rotate_simple_l(tree);
    }

    return tree;
}

AVL avl_insert(AVL tree, void *data, FuncCopy copy, FuncComp comp)
{
    if (tree == NULL)
    {
        AVL newNode = malloc(sizeof(AVLNode));
        newNode->data = copy(data);
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->prev = NULL;

        return newNode;
    }
    else if (comp(data, tree->data) < 0) // data < tree->data
    {
        tree->left = avl_insert(tree->left, data, copy, comp);
        tree->left->prev = tree;
    }
    else if (comp(data, tree->data) > 0) // data > tree->data
    {
        tree->right = avl_insert(tree->right, data, copy, comp);
        tree->right->prev = tree;
    }

    return avl_balancear(tree);
}

void avl_map(AVL tree, AVLOrder order, FuncVisit visit)
{
    if (tree != NULL)
    {
        if (order == AVL_PRE)
            visit(tree->data);
        avl_map(tree->left, order, visit);
        if (order == AVL_IN)
            visit(tree->data);
        avl_map(tree->right, order, visit);
        if (order == AVL_POST)
            visit(tree->data);
    }
}

int max(int a, int b)
{
    if (a > b)
        return a;

    return b;
}

int avl_altura(AVL tree)
{
    if (tree == NULL)
        return -1;

    int izq = avl_altura(tree->left);
    int der = avl_altura(tree->right);

    return 1 + max(izq, der);
}

static AVL minimum_left_root(AVL tree)
{
    if (tree->left != NULL)
    {
        if (tree->left->left == NULL)
            return tree;
        return minimum_left_root(tree->left);
    }

    return tree;
}

static AVL avl_delete_node(AVL tree, FuncDestr destr)
{
    if (tree->left && tree->right)
    {
        AVL minimum_root = minimum_left_root(tree->right);

        AVL aux;

        if (minimum_root->left == NULL)
        {
            aux = minimum_root;
            aux->right = NULL;
        }
        else
        {
            aux = minimum_root->left;

            minimum_root->left = aux->right;
            aux->right = tree->right;
        }

        aux->left = tree->left;
        return aux;
    }
    else if (tree->left)
        return tree->left;
    else if (tree->right)
        return tree->right;

    return NULL;
}

AVL avl_delete(AVL tree, void *data, FuncComp comp, FuncDestr destr)
{
    if (tree == NULL)
        return NULL;

    if (comp(data, tree->data) == 0)
    {
        /* printf("DATA: %d\n", *(int *)tree->left->data); */
        AVL aux = tree;

        tree = avl_delete_node(tree, destr);

        destr(aux->data);
        free(aux);

        return avl_balancear(tree);
    }
    else if (comp(data, tree->data) < 0)
        tree->left = avl_delete(tree->left, data, comp, destr);
    else
        tree->right = avl_delete(tree->right, data, comp, destr);

    return avl_balancear(tree);
}