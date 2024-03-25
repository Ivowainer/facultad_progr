#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contacto
{
    char nombre[10];
    char telefono[10];
    unsigned int edad;
} Contacto;

typedef struct Agenda
{
    int cant;
    Contacto contactos[];
} Agenda;

Contacto crear_contacto()
{
    Contacto nuevo_contacto;

    printf("Coloque el nombre de la persona: ");
    scanf("%s", &nuevo_contacto.nombre);

    printf("Coloque el telefono de la persona: ");
    scanf("%s", &(nuevo_contacto.telefono));

    printf("Coloque el edad de la persona: ");
    scanf("%d", &(nuevo_contacto.edad));

    return nuevo_contacto;
}

void actualizar_edad(Contacto *contacto)
{
    printf("Ingrese la nueva edad del contacto: ");
    scanf("%d", &(contacto->edad));
}

void alta_contacto(Agenda *agenda)
{
    for (int i = 0; i < agenda->cant; i++)
        agenda->contactos[i] = crear_contacto();
}

void modificar_edad(Agenda *agenda)
{
    char nombre[10];

    printf("\nNombre de la persona para buscar: ");
    scanf("%s", &nombre);

    int i = 0;
    while (i < 2 && strcmp(agenda->contactos[0].nombre, nombre))
        i++;

    if (i >= 2)
        printf("No se encontro el contacto");
    else
        actualizar_edad(&(agenda->contactos[i]));
}

int main()
{
    /* Contacto contacto = crear_contacto();
    printf("Edad antes: %d\n", contacto.edad);

    actualizar_edad(&contacto);
    printf("Edad despues: %d", contacto.edad); */

    Agenda *agenda = malloc(sizeof(Agenda));
    agenda->cant = 3;

    alta_contacto(agenda);
    modificar_edad(agenda);
    return 0;
}