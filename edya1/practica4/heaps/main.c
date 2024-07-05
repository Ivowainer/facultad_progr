#include <stdio.h>
#include <stdlib.h>

#include "bheap.h"

int comp_int(void *n, void *m)
{
    int a = *(int *)n;
    int b = *(int *)m;
    if (a == b)
        return 0;
    else if (a < b)
        return -1;
    else
        return 1;
}

void *copy_int(void *data)
{
    int *n = malloc(sizeof(int));
    *n = *(int *)data;
    return n;
}

void print_int(void *data) { printf("%d ", *(int *)data); }

void destry_int(void *n)
{
    free(n);
}

int main()
{
    int dato10 = 10;
    int dato15 = 15;
    int dato16 = 16;
    int dato18 = 18;
    int dato19 = 19;
    int dato20 = 20;
    int dato23 = 23;
    int dato25 = 25;
    int dato30 = 30;

    BHeap bheap = bheap_create(8, comp_int);
    bheap_insert(bheap, &dato10, copy_int, comp_int);
    bheap_insert(bheap, &dato20, copy_int, comp_int);
    bheap_insert(bheap, &dato15, copy_int, comp_int);
    bheap_insert(bheap, &dato25, copy_int, comp_int);
    bheap_insert(bheap, &dato30, copy_int, comp_int);
    bheap_insert(bheap, &dato16, copy_int, comp_int);
    bheap_insert(bheap, &dato18, copy_int, comp_int);
    bheap_insert(bheap, &dato19, copy_int, comp_int);

    bheap_map(bheap, print_int);
    bheap_dfs(bheap, PREODER, print_int);
    /* bheap_delete(bheap, destry_int, comp_int);
    bheap_map(bheap, print_int); */
    return 0;
}