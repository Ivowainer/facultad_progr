#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *direccion;
    int capacidad;
} ArregloEnteros;

ArregloEnteros *arreglo_enteros_crear(int capacidad)
{
    ArregloEnteros *arreglo = malloc(sizeof(ArregloEnteros));
    arreglo->capacidad = capacidad;

    return arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros *arreglo)
{
    free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros *arreglo, int pos)
{
    return arreglo->direccion[pos];
}

void arreglo_enteros_escribir(ArregloEnteros *arreglo, int pos, int dato)
{
    arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros *arreglo)
{
    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros *arreglo)
{
    for (int i = 0; i < arreglo->capacidad; i++)
        printf("%d", arreglo->direccion[i]);
}

int main()
{
    ArregloEnteros *array = arreglo_enteros_crear(5);

    for (int i = 0; i < array->capacidad - 1; i++)
        array->direccion[i] = 4;

    array->direccion[3] = 5;

    arreglo_enteros_imprimir(array);

    return 0;
}