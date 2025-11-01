#include <stdio.h>
#include <stdlib.h>

static inline void incl(int *a, int *b)
{
    asm("incl %0" : "+m"(*a) : : "memory");
}

int main()
{
    int a = 1;
    int b = 1;
    incl(&a, &b);
    a = 3;

    printf("%d\n", a);
    return 0;
}