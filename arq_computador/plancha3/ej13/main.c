#include <stdio.h>

unsigned long fact1(unsigned long);
unsigned long fact2(unsigned long);

unsigned long fact2(unsigned long x)
{
    unsigned long acc = 1;
    for (; x > 1; x--)
    {
        acc *= x;
    }
    return acc;
}

unsigned long fact1(unsigned long x)
{
    if (x <= 1)
    {
        return x;
    }
    return x * fact1(x - 1);
}

int main(void)
{
    unsigned long x;
    scanf("%lu", &x);
    printf("fact1: %lu\n", fact1(x));
    printf("fact2: %lu\n", fact2(x));
    return 0;
}