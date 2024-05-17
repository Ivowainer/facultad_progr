#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void llenar_matriz_nula(int rows, int cols, int matriz[rows][cols])
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matriz[i][j] = 0;
}

void llenar_matriz(int rows, int cols, int matriz[rows][cols], FILE *archivo_entrada, char aux[3], int i)
{
    int aux_coords = 0;
    while (fscanf(archivo_entrada, "%s", aux) != EOF)
    {
        int num_parse = (int)strtol(aux, NULL, 10);

        if (i % 2 == 0)
            aux_coords = num_parse;
        else
        {
            matriz[aux_coords][num_parse] = 1;
        }

        i++;
    }
}

void print_matriz(int rows, int cols, int matriz[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        if (i < 10)
            printf("%d.  ", i);
        else
            printf("%d. ", i);

        for (int j = 0; j < cols; j++)
            printf("%d ", matriz[i][j]);

        printf("\n");
    }
}

void generar_archivo_salida(FILE *salida_archivo, int rows, int cols, int matriz[rows][cols])
{
    char aux[3];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sprintf(aux, "%d", matriz[i][j]);
            fputs(aux, salida_archivo);
        }

        if (i + 1 != rows)
            fputs("\n", salida_archivo);
    }
}

int main()
{
    FILE *archivo_entrada = fopen("./entry.txt", "r");
    FILE *archivo_salida = fopen("./exit.txt", "w+");

    char aux[3]; // max: 15, total de caracteres: 2 + 1 '\0'
    int i = 0;
    int rows = 0;
    int cols = 0;

    int objetivo_coords[2];

    // Recorrer archivo hasta declarar la matriz, rows y cols
    while (i < 4 && fscanf(archivo_entrada, "%s", aux) != EOF)
    {
        int num_parse = (int)strtol(aux, NULL, 10);
        if (i == 0)
            rows = num_parse;
        else if (i == 1)
            cols = num_parse;
        else if (i == 2)
            objetivo_coords[0] = num_parse;
        else if (i == 3)
            objetivo_coords[1] = num_parse;
        i++;
    }

    int matriz[rows][cols];
    llenar_matriz_nula(rows, cols, matriz);
    matriz[objetivo_coords[0]][objetivo_coords[1]] = 2;

    llenar_matriz(rows, cols, matriz, archivo_entrada, aux, i);

    generar_archivo_salida(archivo_salida, rows, cols, matriz);

    fclose(archivo_entrada);
    fclose(archivo_salida);
    return 0;
}