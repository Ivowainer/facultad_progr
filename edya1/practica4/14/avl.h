#include "tipos.h"

#ifndef __AVL_H__
#define __AVL_H__

typedef struct _AVLNode
{
    struct _AVLNode *left, *right, *prev;
    void *data;
} AVLNode;

typedef AVLNode *AVL;

typedef enum
{
    AVL_PRE,
    AVL_IN,
    AVL_POST,
} AVLOrder;

// a < b : -1, a > b 1: a == b 0
AVL avl_create();

AVL avl_insert(AVL tree, void *data, FuncCopy copy, FuncComp comp);
void avl_map(AVL tree, AVLOrder recorrido, FuncVisit visit);
int avl_altura(AVL tree);

int avl_factor_balance(AVL tree);

AVL avl_delete(AVL tree, void *data, FuncComp comp, FuncDestr destr);

#endif