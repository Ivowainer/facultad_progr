
#include "btree.h"
#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

BTree btree_create() { return NULL; }

BTree btree_join(void *data, BTree left, BTree right, CopyFunc copy)
{
    BTNode *btnode = malloc(sizeof(BTNode));
    btnode->data = copy(data);
    btnode->left = left;
    btnode->right = right;

    return btnode;
}

void preorder(BTree tree, VisitorFunc visit)
{
    if (tree == NULL)
        return;

    visit(tree->data);
    preorder(tree->left, visit);
    preorder(tree->right, visit);
}

void *fake_copy(void *data)
{
    return data;
}

void fake_destro(void *data)
{
    return;
}

void print_tree(void *data)
{
    printf("%d ", (*(BTree *)data)->data);
}

void print_stack_tree(void *data)
{
    printf("%d ", *(int *)((BTree)data)->data);
}

// .C
void preorder_iterative(BTree tree, VisitorFunc visit)
{
    BTree aux = tree;

    Stack *stack = stack_create();

    visit(tree->data);
    stack_push(stack, aux->right, fake_copy);
    stack_push(stack, aux->left, fake_copy);

    while (!stack_is_empty(stack))
    {
        aux = stack_top(stack);
        stack_pop(stack, fake_destro);

        visit(aux->data);

        if (aux->right != NULL)
            stack_push(stack, aux->right, fake_copy);

        if (aux->left != NULL)
            stack_push(stack, aux->left, fake_copy);
    }
}

void inorder(BTree tree, VisitorFunc visit)
{
    if (tree == NULL)
        return;

    inorder(tree->left, visit);
    visit(tree->data);
    inorder(tree->right, visit);
}

void postorder(BTree tree, VisitorFunc visit)
{
    if (tree == NULL)
        return;

    postorder(tree->left, visit);
    postorder(tree->right, visit);
    visit(tree->data);
}

void btree_map(BTree tree, BTreeOrdenDeRecorrido map, VisitorFunc visit)
{
    if (map == BTREE_RECORRIDO_PRE)
        preorder(tree, visit);
    else if (map == BTREE_RECORRIDO_PRE_ITERATIVE)
        preorder_iterative(tree, visit);
    else if (map == BTREE_RECORRIDO_IN)
        inorder(tree, visit);
    else if (map == BTREE_RECORRIDO_POST)
        postorder(tree, visit);
}

int btree_nodes(BTree tree)
{
    if (tree == NULL)
        return 0;

    return 1 + btree_nodes(tree->left) + btree_nodes(tree->right);
}

int btree_search(BTree tree, void *data, CompFunc comp)
{
    if (tree == NULL)
        return 0;

    if (comp(tree->data, data))
        return 1;

    return btree_search(tree->left, data, comp) || btree_search(tree->right, data, comp);
}

BTree btree_copy(BTree tree, CopyFunc copy)
{
    if (tree == NULL)
        return btree_create();

    return btree_join(tree->data, btree_copy(tree->left, copy), btree_copy(tree->right, copy), copy);
}

int max(int n1, int n2)
{
    if (n1 > n2)
        return n1;

    return n2;
}

int btree_height(BTree tree)
{
    if (tree == NULL)
        return -1;

    int alt_izq = btree_height(tree->left);
    int alt_der = btree_height(tree->right);

    if (alt_izq > alt_der)
        return alt_izq + 1;

    return alt_der + 1;
    /* if (tree == NULL)
        return 0;
    return 1 + max(btree_height(tree->left), btree_height(tree->right)); */
}

int btree_nodes_depth(BTree tree, int depth)
{
    if (tree == NULL)
        return 0;

    if (depth == 0)
        return 1;

    int cant_izq = btree_nodes_depth(tree->left, depth - 1);
    int cant_der = btree_nodes_depth(tree->right, depth - 1);

    return cant_izq + cant_der;
}

int btree_depth_aux(BTree tree, void *data, CompFunc comp, int depth)
{
    if (tree == NULL)
        return 0;
    if (comp(tree->data, data))
        return depth;

    return btree_depth_aux(tree->left, data, comp, depth + 1) + btree_depth_aux(tree->right, data, comp, depth + 1);
}

int btree_depth(BTree tree, void *data, CompFunc comp)
{
    int depth = btree_depth_aux(tree, data, comp, 0);
    return btree_nodes_depth(tree, depth);
    /* if (tree == NULL)
        return -1;
    if (comp(tree->data, data))
        return 0;
    int izq = btree_depth(tree->left, data, comp);
    int der = btree_depth(tree->right, data, comp);
    if (izq != -1)
        return izq + 1;
    if (der != -1)
        return der + 1;
    return -1; */
}

int btree_sum(BTree tree)
{
    if (tree == NULL)
        return 0;

    return *(int *)tree->data + btree_sum(tree->left) + btree_sum(tree->right);
}

// 4. a
void preorder_extra(BTree tree, void *extra, FuncionVisitanteExtra visit)
{
    if (tree == NULL)
        return;

    visit(tree->data, extra);
    preorder_extra(tree->left, extra, visit);
    preorder_extra(tree->right, extra, visit);
}
void btree_recorrer_extra(BTree tree, BTreeOrdenDeRecorrido order, FuncionVisitanteExtra visit, void *extra)
{
    if (order == BTREE_RECORRIDO_PRE)
        preorder_extra(tree, extra, visit);
}

// 5. a
void btree_bfs(BTree tree, VisitorFunc visit)
{
    for (int i = 0; i <= btree_height(tree); i++)
    {
        btree_visit_nodes_depth(tree, visit, i);
    }
}

void btree_visit_nodes_depth(BTree tree, VisitorFunc visit, int depth)
{
    if (tree == NULL)
        return;
    if (depth == 0)
        visit(tree->data);

    btree_visit_nodes_depth(tree->left, visit, depth - 1);
    btree_visit_nodes_depth(tree->right, visit, depth - 1);
}

void btree_bfs_iterative(BTree tree, VisitorFunc visit)
{
    BTree aux = tree;
    Queue *q = queue_create();

    visit(aux->data);
    queue_enqueue(q, aux->left, fake_copy);
    queue_enqueue(q, aux->right, fake_copy);

    while (!queue_is_empty(q))
    {
        aux = queue_first(q);
        queue_dequeue(q, fake_destro);
        visit(aux->data);

        if (aux->left != NULL)
            queue_enqueue(q, aux->left, fake_copy);
        if (aux->right != NULL)
            queue_enqueue(q, aux->right, fake_copy);
    }
}