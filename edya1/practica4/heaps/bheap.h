#ifndef __BHEAP_H__
#define __BHEAP_H__

typedef int (*FuncComp)(void *a, void *b);
typedef void *(*FuncCopy)(void *data);
typedef void (*FuncVisit)(void *data);
typedef void (*FuncDestr)(void *data);

typedef struct _BHeap
{
    void **arr;
    int length;
    int last;
    FuncComp comp;
} *BHeap;

typedef enum BHEAP_DFS
{
    PREODER,
    INORDER,
    POSTORDER
} BHEAP_DFS;

BHeap bheap_create(int length, FuncComp comp);
void bheap_insert(BHeap bheap, void *data, FuncCopy copy, FuncComp comp);
void bheap_map(BHeap bheap, FuncVisit visit);
void bheap_delete(BHeap bheap, FuncDestr destr, FuncComp comp);
void bheap_dfs(BHeap bheap, BHEAP_DFS recorrido, FuncVisit vist);
#endif