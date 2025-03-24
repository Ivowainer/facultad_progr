#include "bheap.h"
#include <stdio.h>
#include <stdlib.h>

BHeap bheap_create(int length, FuncComp comp)
{
    BHeap bheap = malloc(sizeof(struct _BHeap));
    bheap->arr = malloc(sizeof(void *) * length + 1);
    bheap->last = 1;
    bheap->length = length + 1;
    bheap->comp = comp;

    return bheap;
}

static void swap(void **arr, int pos1, int pos2)
{
    void *aux = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = aux;
}

void bheap_insert(BHeap bheap, void *data, FuncCopy copy, FuncComp comp)
{
    if (bheap->last == bheap->length)
        bheap->arr = realloc(bheap->arr, sizeof(void *) * bheap->length * 2);

    int pos = bheap->last;
    bheap->arr[pos] = copy(data);

    int father = bheap->last / 2;

    // mientras el actual sea mayor que el padre
    while (comp(bheap->arr[father], data) < 0 && pos > 1)
    {
        swap(bheap->arr, father, pos);
        pos = pos / 2;
        father = father / 2;
    }

    bheap->last++;
}

void bheap_map(BHeap bheap, FuncVisit visit)
{
    for (int i = 1; i <= bheap->last - 1; i++)
        visit(bheap->arr[i]);

    printf("\n");
}

static int bheap_find_pos(BHeap bheap, void *data, FuncComp comp)
{
    int i = 1;
    while (i <= bheap->last - 1 && comp(bheap->arr[i], data))
        i++;

    return i != bheap->length ? i : -1;
}

void bheap_delete(BHeap bheap, FuncDestr destr, FuncComp comp)
{
    destr(bheap->arr[1]);
    bheap->arr[1] = bheap->arr[--bheap->last];

    int k = 1;
    int r = k * 2;
    int l = (k * 2) + 1;

    while (l < bheap->last)
    {

        if (comp(bheap->arr[r], bheap->arr[l]) > 0)
        {
            swap(bheap->arr, r, k);
            k = k * 2;
        }
        else
        {
            swap(bheap->arr, l, k);
            k = (k * 2) + 1;
        }

        r = k * 2;
        l = (k * 2) + 1;
    }
}

void bheap_dfs_aux(BHeap bheap, int pos, FuncVisit visit)
{
    if (pos >= bheap->last)
        return;

    visit(bheap->arr[pos]);
    bheap_dfs_aux(bheap, pos * 2, visit);
    bheap_dfs_aux(bheap, (pos * 2) + 1, visit);
}

void bheap_dfs(BHeap bheap, BHEAP_DFS recorrido, FuncVisit visit)
{
    bheap_dfs_aux(bheap, 1, visit);
}