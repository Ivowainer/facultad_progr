#include <stdio.h>
#include <stdlib.h>

void ej1()
{
    int a = 1;
    int b = 2;
    char text[5] = "hola";
    printf("El puntero de a: %p y su valor: %d\n", &a, a);
    printf("El puntero de b: %p y su valor: %d\n", &b, b);
    printf("Direcciones, h: %p, o: %p, l: %p, a: %p", &text, &text[1], &text[2], &text[3]);
}

void set_first(int arr[])
{
    printf("Primer elemento del array: %d\n", *arr);
    *arr = 0;
    printf("Se modifica el primer elemento por: %d", *arr);
}

void set_int(int *n)
{
    if (*n != 0)
        *n = 1;
    else
        *n = 0;
}

void swap(int *n1, int *n2)
{
    int aux = *n1;

    *n1 = *n2;
    *n2 = aux;
}

char *get_new_line()
{
    int defaultSize = 10;
    int i = 0;

    char *text = malloc(sizeof(char) * defaultSize);
    scanf("%c", &text[i]);

    while (text[i] != '\n')
    {
        i++;

        if (i >= defaultSize - 1)
        {
            defaultSize *= 2;
            text = realloc(text, sizeof(char) * defaultSize);
        }

        scanf("%c", &text[i]);
    }

    text[i + 1] = '\0';

    return text;
}

int sum_one(int n)
{
    return ++n;
}

int apply(int (*sum)(int), int n)
{
    return (*sum)(n);
}

int replace_it(int n)
{
    if (n != 0)
        return 1;
    else
        return 0;
}

void apply_in(int (*replace)(int), int *n)
{
    *n = (*replace)(*n);
}

typedef void (*VisitorFunc)(int *);

void recorre(VisitorFunc func, int *arr, int length)
{
    for (int i = 0; i < length; i++)
        (*func)(&arr[i]);
}

VisitorFunc funcVisitor(int *n)
{
    *n = *n + 1;
}

typedef struct Punto
{
    int x;
    int y;
} Punto;

void calcularMedio(Punto punto1, Punto punto2)
{
    int x = ((punto1.x + punto2.x) / 2);
    int y = ((punto1.y + punto2.y) / 2);

    printf("El punto x: %d, el punto y: %d", x, y);
}

int main()
{
    /* ej1(); */

    // ej 2
    /* int arr[2] = {2, 3};
    set_first(arr); */

    // ej 3
    /* int n = 0;
    set_int(&n);
    printf("%d", n); */

    // ej 4
    /* int n1 = 5;
    int n2 = 6;
    printf("n1: %d n2: %d\n", n1, n2);
    swap(&n1, &n2);
    printf("n1: %d n2: %d", n1, n2); */

    // ej 6
    /* printf("%s", get_new_line()); */

    // ej 8
    /* a. printf("%d", apply(&sum_one, 3)); */
    /* b.  int n = 2;
        printf("Antes: %d", n);
        apply_in(&replace_it, &n);
        printf("Despues: %d", n);*/
    /* c. const int length = 6;
    int arr[6] = {1, 2, 3, 4, 5};
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    }
    recorre(&funcVisitor, arr, length);
    printf("\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arr[i]);
    } */

    /* ej 12.
    Punto p1;
    p1.x = 11;
    p1.y = 11;

    Punto p2;
    p2.x = 5;
    p2.y = 5;
    calcularMedio(p1, p2); */

    return 0;
}