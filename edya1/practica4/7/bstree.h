#ifndef __BTREE_H__
#define __BTREE_H__

typedef struct _BSTNode
{
    void *data;
    struct _BSTNode *left;
    struct _BSTNode *right;
} BSTNode;

typedef BSTNode *BSTree;

typedef void (*FuncVisit)(void *);
typedef void *(*FuncCopy)(void *);
typedef void (*FuncDestroy)(void *);
// m > n -1, m < n 1
typedef int (*FuncComp)(void *, void *);

typedef enum
{
    BTREE_MAP_IN,  /** Inorden */
    BTREE_MAP_PRE, /** Preorden */
    BTREE_MAP_POST /** Postorden */
} BSTreeMap;

BSTree bstree_create();

BSTree bstree_insert(BSTree tree, void *data, FuncCopy copy, FuncComp comp);
void bstree_map(BSTree tree, BSTreeMap order, FuncVisit visit);
BSTree bstree_delete(BSTree tree, void *data, FuncComp comp, FuncDestroy destr);

void *bstree_k_esimo_menor(BSTree tree, int k);
int btree_validar(BSTree tree, FuncComp comp);

void *btree_search(BSTree tree, void *data, FuncComp comp);

#endif