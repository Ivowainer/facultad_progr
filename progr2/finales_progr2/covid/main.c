#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PISOS_MIN 1
#define PISOS_MAX 3
#define OFI_MIN 1
#define OFI_MAX 3
#define ESC_MIN 1
#define ESC_MAX 3

typedef struct
{
    int pisos;
    int max;
    int min;
    int escritorios;
} Empr;

int check_empr(Empr empr)
{
    if (empr.pisos < 1 || empr.pisos > 3 || empr.min < 2 || empr.max > 10 || empr.escritorios < 1 || empr.escritorios > 3)
    {
        printf("Error en los maximos y minmos del archivo entrada\n");
        return 0;
    }

    return 1;
}

Empr create_empr(FILE *f_entry)
{
    Empr empr;
    char aux[3]; // 3 debido a la longitud del numero maximo, "10" + '\0'
    int i = 0;

    while (fscanf(f_entry, "%s", aux) != EOF)
    {
        int num_parse = (int)strtol(aux, NULL, 10);
        if (i == 0)
            empr.pisos = num_parse;
        else if (i == 1)
            empr.min = num_parse;
        else if (i == 2)
            empr.max = num_parse;
        else if (i == 3)
            empr.escritorios = num_parse;

        i++;
    }

    return empr;
}

void print_matriz(int rows, int matriz[rows][4])
{
    for (int i = 0; i < rows; i++)
    {
        if (i < 10)
            printf("%d.  ", i);
        else
            printf("%d. ", i);

        for (int j = 0; j < 4; j++)
            printf("%d ", matriz[i][j]);

        printf("\n");
    }
}

void llenar_matriz_nula(int rows, int matriz[rows][4])
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < 4; j++)
            matriz[i][j] = 0;
}

void llenar_matriz(int rows, int matriz[rows][4], int matriz_ofi[], Empr empr)
{

    int persona = 1;
    int piso_iterator = 0;

    int min_interval = 0;
    int max_interval = matriz_ofi[piso_iterator] * empr.escritorios;
    while (piso_iterator < empr.pisos)
    {
        int escr_iterator = 1;
        int escr_iterator_val = 0;

        for (int j = min_interval; j < max_interval; j++)
        {
            matriz[j][0] = piso_iterator;
            matriz[j][1] = escr_iterator_val;

            if (rand() % 2)
            {
                matriz[j][2] = persona;
                persona++;
            }
            else
                matriz[j][2] = 0;

            if (matriz[j][2] == 0)
                matriz[j][3] = -1;
            else
                matriz[j][3] = rand() % 2;

            if (escr_iterator == empr.escritorios)
            {
                escr_iterator = 1;
                escr_iterator_val++;
            }
            else
                escr_iterator++;
        }

        min_interval = max_interval;
        max_interval = matriz_ofi[piso_iterator + 1] * empr.escritorios + min_interval;

        piso_iterator++;
    }
}

void write_exit_file(FILE *exit_file, int rows, int matriz[rows][4])
{
    char aux[25];
    for (int i = 0; i < rows; i++)
    {
        if (matriz[i][2] != 0)
            sprintf(aux, "%d %d Persona%d %d\n", matriz[i][0], matriz[i][1], matriz[i][2], matriz[i][3]);
        else
            sprintf(aux, "%d %d NADIE %d\n", matriz[i][0], matriz[i][1], matriz[i][3]);

        fputs(aux, exit_file);
    }
}

int main()
{
    srand(time(NULL));

    FILE *f_entry = fopen("./entry.txt", "r");
    FILE *f_exit = fopen("./exit.txt", "w+");

    Empr empr = create_empr(f_entry);

    if (!check_empr(empr))
        return -1;

    // Generar matriz de ofi
    int matriz_ofi[empr.pisos];
    int rows = 0;

    for (int i = 0; i < empr.pisos; i++)
    {
        matriz_ofi[i] = rand() % (empr.max - empr.min + 1) + empr.min;
        rows += matriz_ofi[i] * empr.escritorios;
    }

    int matriz[rows][4];

    llenar_matriz(rows, matriz, matriz_ofi, empr);

    write_exit_file(f_exit, rows, matriz);

    return 0;
}