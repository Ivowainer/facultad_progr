#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct
{
    int rows;
    int cols;
} Tablero;

Tablero create_tablero(FILE *entry_file)
{
    char aux[3]; // 2 digitos, longitud 3

    Tablero tablero;
    fscanf(entry_file, "%s", aux);
    tablero.rows = strtol(aux, NULL, 10);
    fscanf(entry_file, "%s", aux);
    tablero.cols = strtol(aux, NULL, 10);

    return tablero;
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

void generate_exit_file(FILE *exit_file, int rows, int matriz[rows][4], Tablero tab)
{
    char aux[10];
    sprintf(aux, "%d %d", tab.rows, tab.cols);
    fputs(aux, exit_file);
    fputs("\n", exit_file);

    for (int i = 0; i < rows; i++)
    {
        char aux[10];

        for (int j = 0; j < 4; j++)
        {
            sprintf(aux, "%d ", matriz[i][j]);
            fputs(aux, exit_file);
        }

        fputs("\n", exit_file);
    }
}

int main()
{
    srand(time(NULL));
    FILE *entry_file = fopen("./entry.txt", "r");
    FILE *exit_file = fopen("./exit.txt", "w+");

    // Definir tablero
    Tablero tablero = create_tablero(entry_file);

    // Genera cantida aleatoria de barcos, luego, por cada una de esa n va a ejecutar fcsanf
    int n_cantidad_barcos = rand() % (tablero.cols - (int)(floor(tablero.rows / 3)) + 1) + (int)(floor(tablero.rows / 3));

    int barcos[n_cantidad_barcos][4];

    for (int i = 0; i < n_cantidad_barcos; i++)
    {
        char aux[10];
        int n = (rand() % 2) + 1;
        int j = 0;

        for (int j = 0; j < n; j++)
            fgets(aux, 10, entry_file);

        while (fscanf(entry_file, "%s", aux) != EOF && j < 4)
        {
            barcos[i][j] = strtol(aux, NULL, 10);
            j++;
        }
    }

    /* print_matriz(n_cantidad_barcos, barcos); */
    generate_exit_file(exit_file, n_cantidad_barcos, barcos, tablero);

    fclose(entry_file);
    return 0;
}