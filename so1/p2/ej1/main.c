#include <stdio.h>
#include <stdlib.h>

/*
    Lo que pasa, es que en el if modificamos encontrado. En cambio, con la otra opción estamos modificando la variable por cada iteración
*/

int main()
{
    int encontrado = 0;

    int A[10] = {1, 2, 3, 1, 2, 42, 6, 2, 1, 4};
    for (int i = 0; i < 10; i++)
    {
        /* if (A[i] == 42)
        {
            encontrado = 1;
            break;
        } */
        encontrado = encontrado || (A[i] == 42); // <-- opción pete
    }

    printf("ENCONTRADO: %d\n", encontrado);

    return 0;
}