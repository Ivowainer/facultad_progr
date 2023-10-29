#include <stdio.h>
#include <math.h>

void ej1()
{

    int n;
    printf("Numero: ");
    scanf("%d", &n);

    if (n < 1 || n > 6)
    {
        printf("Número incorrecto");
        return;
    }

    switch (n)
    {
    case 1:
        printf("El numero opuesto es SEIS");
        break;
    case 2:
        printf("El numero opuesto es CINCO");
        break;
    case 3:
        printf("El numero opuesto es CUATRO");
        break;
    case 4:
        printf("El numero opuesto es TRES");
        break;
    case 5:
        printf("El numero opuesto es DOS");
        break;
    case 6:
        printf("El numero opuesto es UNO");
        break;
    }
}
/* EJ2 */
void ej2()
{
    int hab;
    printf("Ingrese numero de habitacion: ");
    scanf("%d", &hab);

    printf("Azul, Roja, Verde, Rosa, Gris \n ");

    switch (hab)
    {
    case 1:
        printf("Camas: 2, Planta: Primera");
        break;
    case 2:
        printf("Camas: 1, Planta: Primera");
        break;
    case 3:
        printf("Camas: 3, Planta: Segunda");
        break;
    case 4:
        printf("Camas: 2, Planta: Segunda");
        break;
    case 5:
        printf("Camas: 1, Planta: Tercera");
        break;
    default:
        printf("Número no asociado a habitación.");
        break;
    }
}

/* EJ3 */
void ej3()
{
    float sum1 = 0.0;
    float sum2 = 0.0;
    float sum3 = 0.0;
    float sum4 = 0.0;

    for (int n = 1; n <= 100; n++)
    {
        sum1 += (1.0 / n);
    }

    for (int k = 1; k <= 30; k++)
    {
        sum2 += (1.0 / k * k);
    }

    for (int j = 1; j <= 25; j++)
    {
        sum3 += (1.0 / pow(j, j));
    }

    for (int i = 2; i <= 10; i++)
    {
        sum4 += (i + 1) * i;
    }

    printf("Primer sum: %f", sum1);
    printf("\nSegunda sum: %f", sum2);
    printf("\nTercera sum: %f", sum3);
}

/* EJ 4 */
void ej4()
{
    int a, b, c;

    for (a = 1; a <= 20; a++)
    {
        for (b = 1; b <= 30; b++)
        {
            c = a * a + b * b;

            int sqrt_c = (int)sqrt(c);

            if (sqrt_c * sqrt_c == c)
            {
                printf("Terna pitagorica: a = %d, b = %d, c = %d\n", a, b, sqrt_c);
            }
        }
    }
}

/* EJ 6 */
#define n_secreto 130

void ej6()
{
    int intentos = 15;

    int n;
    printf("Ingrese un numero: ");
    scanf("%d", &n);

    while (intentos > 1 && n != n_secreto)
    {
        printf("-------------- \n");
        if (n > n_secreto)
        {
            printf("El numero que ingresaste es mayor al Numero Secreto \n");
        }
        else
        {
            printf("El numero que ingresaste es menor al Numero Secreto \n");
        }

        intentos--;
        printf("Intentos restantes: %d", intentos);
        printf("\n--------------");

        printf("\nIngrese un numero: ");
        scanf("%d", &n);
    }

    if (intentos > 0)
    {
        printf("Felicidades, ganaste, el numero era %d", n_secreto);
    }
    else
    {
        printf("Perdiste, te quedaste sin intentos");
    }
}

/* EJ 7 */
int length(char text[])
{
    int i = 0;
    while (text[i] != '\0')
    {
        i++;
    }

    return i;
}

int esMayus(char c)
{
    if (c >= 65 && c <= 90)
    {
        return 1;
    }
    return 0;
}

void ej7()
{
    char text[] = "bucle";
    int n = 5;
    char l = 'T';

    char palabra_formada[length(text) + 1];

    for (int i = 0; i < length(text); i++)
    {
        palabra_formada[i] = text[i];
        palabra_formada[i + 1] = '\0';

        printf("%s %d %c\n", palabra_formada, n, l);

        if (esMayus(l))
        {
            l = l + 31;
        }
        else
        {
            l = l - 33;
        }

        n--;
    }
}

void ej8()
{
    int i = 0;

    int n;
    printf("El valor inicial es: ");
    scanf("%d", &n);

    if (n < 1)
    {
        printf("Error");
        return;
    }

    while (n != 1)
    {
        if (n % 2 == 0)
        {
            n = n / 2;
            printf("\nEl siguiente valor es %d", n);
        }
        else
        {

            n = (n * 3) + 1;
            printf("\nEl siguiente valor es %d", n);
        }

        i++;
    }

    printf("\nValor final %d, nUmero de pasos 19.", n);
}

/* EJ 9 */
void ej9()
{
    int arr[100];

    for (int i = 0; i <= 100; i++)
    {
        arr[i] = i;

        printf("%d ", arr[i]);
    }
}

/* EJ 10 */
void ej10()
{
    int n = 200;
    int arr[51];

    int index = 0;

    for (int i = 0; n >= 100; i++)
    {
        if (n % 2 == 0)
        {
            arr[index] = n;
            index++;
        }
        n--;
    }

    for (int i = 0; i < 51; i++)
    {
        printf("%d ", arr[i]);
    }
}

void ej11()
{
    int arr[17];
    int index = 0;

    for (int i = 50; i > 0; i--)
    {
        if (i % 3 == 0)
        {
            arr[index] = i;
            index++;
        }
    }

    for (int i = 0; i < index; i++)
    {
        printf("%d ", arr[i]);
    }
}

void ej12()
{
    int arr[10];
    int n;
    int iterator = 0;

    printf("Escribe numeros: ");
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Escribe un numero n: ");
    scanf("%d", &n);

    while (iterator < 10 && arr[iterator] != n)
        iterator++;

    if (iterator >= 10)
    {
        printf("-1");
        return;
    }

    printf("Posicion: %d", iterator);
}

void ej13()
{
    int sum = 0;

    int n;
    printf("Numero entre [5, 100]: ");
    scanf("%d", &n);

    if (n < 5 || n > 100)
    {
        printf("Error");
        return;
    }

    int arr[n];

    printf("Ingrese numeros: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    if (sum > 30)
    {
        printf("Mayor a 30");
    }
    else
    {
        printf("Menor a 30");
    }
}

void ej14()
{
    int numeros[100] = {0};

    int arr[100];
    int index = 0;
    int n;

    printf("Ingrese enteros (ingrese un numero negativo para detenerse):\n");
    while (n > -1)
    {
        scanf("%d", &n);
        arr[index] = n;
        numeros[n]++;
        index++;
    }

    int maxVeces = 0;
    int maxValue = numeros[0];
    for (int i = 0; i < 10; i++)
    {
        if (numeros[i] > maxVeces)
        {
            maxValue = i;
            maxVeces = numeros[i];
        }
    }

    printf("El valor es: %d, y aparecio un total de veces: %d", maxValue, maxVeces);
}

/* EJ 15 */
int ej15(int arr[], int length)
{
    int sum = 0;

    for (int i = 0; i < length; i++)
    {
        sum += arr[i];
    }

    printf("%d", sum);
    return sum;
}

/* EJ 16 */
int ej16(int arr[], int length)
{
    int final = 1;

    for (int i = 0; i < length; i++)
    {
        if (arr[i] % 2 == 0)
        {
            final *= arr[i];
        }
    }

    printf("%d", final);
    return final;
}

/* EJ 18 */
void ej18(char string[], char l)
{
    int i = 0;

    while (i < length(string) && string[i] != l)
        i++;

    if (i >= length(string))
    {
        printf("Master, no lo contiene");
    }
    else
    {
        printf("Master, si lo tiene");
    }
}

/* EJ 19 */
void ej19(char string[], char l)
{
    int contador = 0;

    for (int i = 0; i < length(string); i++)
    {
        if (string[i] == l)
            contador++;
    }

    printf("Apariciones: %d", contador);
}

void ej20()
{
    int n;
    printf("Elige la longitud de la palabra: ");
    scanf("%d", &n);
    char string[n];

    printf("Palabra: ");
    scanf("%s", string);

    for (int i = n; i >= 0; i--)
    {
        printf("%c", string[i]);
    }
}

/* EJ 21 */
void ej21(char string[])
{
    int iterator = 0;

    char palabra_formada[length(string)];

    for (int i = 0; i <= length(string); i++)
    {
        palabra_formada[i] = string[length(string) - i];
    }

    while (iterator < length(string) && string[iterator] != palabra_formada[iterator])
        iterator++;

    if (iterator >= length(string))
        printf("Es capicua");
    else
        printf("No es capicua");
}

/* EJ 22 */
void ej22(char string[])
{
    int i = 0;

    int arr[26] = {0};

    for (int i = 0; i < length(string); i++)
    {
        arr[122 - string[i]] = 1;
    }

    while (i < length(string) && arr[i] != 0)
        i++;

    if (i >= length(string))
        printf("Es pangrama");
    else
        printf("No es pangrama");
}

/* EJ 23 */
void ej23(char string1[], char string2[])
{
    /* "casa" en "casas" */
    int i = 0;

    while (i < length(string1) && string1[i] == string2[i])
        i++;

    if (i >= length(string1))
        printf("Esta contenida");
    else
        printf("No esta contenida");
}

int main()
{
    int arr[4] = {1, 2, 3, 4};

    /* ej1(); */
    /* ej2(); */
    /* ej3(); */
    /* ej4(); */
    /* ej6(); */
    /* ej7(); */
    /* ej8(); */
    /* ej9(); */
    /* ej10(); */
    /* ej11(); */
    /* ej12(); */
    /* ej13(); */
    /* ej14(); */
    /* ej15(arr, 4); */
    /* ej16(arr, 4); */
    /* ej18("hola", 's'); */
    /* ej19("holaoo", 'o'); */
    /* ej20(); */
    /* ej21("ojo"); */
    /* ej22("el veloz murcielago hindu comia feliz cardillo y kiwi la cigea tocaba el saxofon detras del palenque de paja"); */
    ej23("casa", "casas");
    return 0;
}