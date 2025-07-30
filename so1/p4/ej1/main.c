#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 10;
#pragma omp parallel firstprivate(i)
    {
        // variable i is initialized to its original value
        printf("thread %d: i = %d\n", omp_get_thread_num(), i);
        i = 1000;
    }
    printf("firstprivate i = %d\n", i);
}