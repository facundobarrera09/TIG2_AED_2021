#ifndef H_MENU
#define H_MENU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Menu
{
    int largo = 0, ancho = 0;
    int margen = 0;
    char titulo[100];
    char opciones[10][100];
    int seleccion = -1;
};

Menu menu;

void modificar_dato(const char dato[], const char valor[])
{
    /**
     * 
    */

    char temp[2];

    if (strcmp(dato, "largo") == 0) menu.largo = atoi(valor);
    if (strcmp(dato, "ancho") == 0) menu.ancho = atoi(valor);
    if (strcmp(dato, "margen") == 0) menu.margen = atoi(valor);
    if (strcmp(dato, "seleccion") == 0) menu.seleccion = atoi(valor);
    if (strcmp(dato, "titulo") == 0) strcpy(menu.titulo, valor);
    if (strcmp(dato, "opcion") == 0)
    {
        memcpy(temp, valor, 1);
        memcpy(menu.opciones[atoi(temp)], &valor[3], sizeof(menu.opciones[0]));
    }
}

void mostrar_menu()
{
    system("cls");

    int imprimir = 1, ultimo_imprimir = 0, pos = 0; // Define que parametro se va a imprimir

    // Valores por defecto ante entradas no validas o nulas
    if (menu.largo < 2) menu.largo = 20;
    if (menu.ancho < 2) menu.ancho = 70;

    // Borde superior
    printf("\xC9");
    for (int x = 0; x < menu.ancho-2; x++) printf("\xCD");
    printf("\xBB\n");

    // Laterales
    for (int x = 0; x < menu.largo-2; x++)
    {
        // Lateral izquierdo
        printf("\xBA"); 

        // Medio
        for (int y = 0; y < menu.ancho-2; y++)
        {
            // Titulo
            if (x == 1 && y >= (menu.ancho/2) && imprimir == 1)
            {
                for (int z = 0; z < ((strlen(menu.titulo)/2) + (strlen(menu.titulo)%2) + ((menu.ancho/2)%2)); z++) printf("\b");
                printf("%s", menu.titulo);

                y += ((strlen(menu.titulo)/2) - ((menu.ancho/2)%2));

                imprimir++;
            }

            // Opciones
            if (x > 2 && (y > menu.margen && y < menu.ancho-menu.margen) && imprimir == 2)
            {
                if (ultimo_imprimir != imprimir)
                {
                    char selec[2];
                    if (menu.seleccion == pos) strcpy(selec, "\xAF");

                    printf("%s %s", selec, menu.opciones[pos++]);

                    ultimo_imprimir = imprimir;
                    imprimir++;
                }
            }

            // Espacios en blanco
            printf(" ");
        }

        // Lateral derecho
        printf("\xBA\n");
    }
    
    // Borde inferior
    printf("\xC8");
    for (int x = 0; x < menu.ancho-2; x++) printf("\xCD");
    printf("\xBC\n");
}

#endif