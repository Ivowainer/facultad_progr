#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int palo;
    int num;
} Carta;

typedef struct
{
    Carta mazo[48];
} Mazo;

void llenar(Mazo *mazo)
{
    /* for (int i = 0; i < 4; i++)
    {
    } */

    for (int i = 0; i < 48; i++)
    {
        if (i <= 11)
        {
            Carta nuevaCarta;
            nuevaCarta.num = i + 1;
            nuevaCarta.palo = 1;
            mazo->mazo[i] = nuevaCarta;
        }
        else if (i <= 23)
        {
            Carta nuevaCarta;
            nuevaCarta.num = i - 11;
            nuevaCarta.palo = 2;
            mazo->mazo[i] = nuevaCarta;
        }
        else if (i <= 35)
        {
            Carta nuevaCarta;
            nuevaCarta.num = i - 23;
            nuevaCarta.palo = 3;
            mazo->mazo[i] = nuevaCarta;
        }
        else if (i <= 47)
        {
            Carta nuevaCarta;
            nuevaCarta.num = i - 35;
            nuevaCarta.palo = 4;
            mazo->mazo[i] = nuevaCarta;
        }
    }
}

void imprimirMazo(Mazo *mazo)
{
    for (int i = 0; i < 48; i++)
    {
        printf("\nPalo: %d, Num: %d", mazo->mazo[i].palo, mazo->mazo[i].num);
    }
}

Carta azar(Mazo *mazo)
{
    srand(time(NULL));
    return mazo->mazo[rand() % 48];
}

int main()
{
    Mazo *mazo = malloc(sizeof(Mazo));

    llenar(mazo);

    /* imprimirMazo(mazo); */

    Carta cartaAzar = azar(mazo);

    printf("Palo: %d, Num: %d", cartaAzar.palo, cartaAzar.num);
    return 0;
}