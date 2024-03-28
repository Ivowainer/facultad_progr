#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float mediana(float *arr, int length)
{
    if (length % 2 == 0)
        return (arr[length / 2] + arr[(length / 2) - 1]) / 2;

    return arr[length / 2];
}

int string_len(char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++)
        ;

    return i;
}

void swap(char *p1, char *p2)
{
    char *aux = p1;

    *p1 = *p2;
    *p2 = *aux;
}

void string_reverse(char *str)
{
    int length = string_len(str);

    for (int i = 0; i < length / 2; i++)
    {
        char aux = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = aux;
    }
}

int string_concat(char *str1, char *str2, int max)
{
    int i = 0;
    for (; str1[i] != '\0'; i++)
        ;

    int j = 0;

    while (j < max && str2[j] != '\0')
    {
        str1[i + j] = str2[j];
        j++;
    }

    str1[i + j] = '\0';

    return j;
}

int string_compare(char *str1, char *str2)
{
    int str1cant = 0;
    for (int i = 0; i < string_len(str1); i++)
        str1cant += str1[i];

    int str2cant = 0;
    for (int j = 0; j < string_len(str2); j++)
        str2cant += str2[j];

    if (str1cant < str2cant)
        return -1;
    else if (str1cant == str2cant)
        return 0;
    else
        return 1;
}

/* int string_subcadena(char *str1, char *str2)
{
    int j = 0;
    char *concurrect_character = malloc(sizeof(string_len(str1))); // Guarda las posiciones en las que coincide la primera letra de str2 con str1

    for (int i = 0; i < string_len(str1); i++)
    {
        if (str1[i] == str2[0])
        {
            concurrect_character[j] = (char)i;
            j += 1;
        };
    }

    concurrect_character[j + 1] = '\0';

    printf("%d ", string_len(concurrect_character));
    // Si es impar no agrega el '\0', sino si
} */

int string_subcadena(char *str1, char *str2)
{
    // Retorna la ocurrencia, si no existe -1
    int str1_len = string_len(str1);
    int str2_len = string_len(str2);

    int i = 0;
    int j = 0;
    while (i < str1_len && j < str2_len)
    {
        if (str1[i] == str2[0] && str1[i + j] == str2[j])
        {
            while (j < str2_len && str1[i + j] == str2[j])
            {
                j++;
            }
        }
        else
        {
            j = 0;
            i++;
        }
    }

    if (j >= str2_len - 1)
        return i;

    return -1;
}

void string_unir(char *arregloStrings[], int n, char *sep, char *res)
{
    /* concatene las n cadenas del arreglo arregloStrings */
    /* separandolas por la cadena sep */
    /* almacenando el resultado en res */
    int sep_len = string_len(sep);

    for (int i = 0; i < n; i++)
    {
        int MAX = string_len(arregloStrings[i]) + sep_len;
        string_concat(res, arregloStrings[i], MAX);
        string_concat(res, sep, MAX);
    }

    printf("%s", res);
}

int main()
{
    /* 1.
    float medio[] = {-1.0, 2.2, 2.9, 3.1}; // -1.0, 2.2, 2.9, 3.1, 3.5, length = 5
    printf("%f", mediana(medio, 4)); */

    /* 2.
        char str[] = "hola";
        a. printf("%d", string_len(str));
        b.  char str[] = "autos";
            printf("%s", str);
            string_reverse(str)
            printf("%s", str);
        c.  char str1[] = "hola";
            char str2[] = " como estas paso los 10 caracteres";
            printf("%d", string_concat(str1, str2, 10));
        d.  char str1[] = "hola";
            char str2[] = "como estas";
            printf("%d", string_compare(str1, str2));
        e.  char str1[] = "asfwkcasasasuhf";
            char str2[] = "casas";
            printf("%d", string_subcadena(str1, str2));
        f.  char *str1 = "hola";
            char *str2 = "test";
            char *str3 = "uno";
            char *arregloString[] = {str1, str2, str3};

            char *sep = " ";

            char *res = malloc(sizeof(char) * 100);
            res[0] = '\0';

            string_unir(arregloString, 3, sep, res);  */

    return 0;
}