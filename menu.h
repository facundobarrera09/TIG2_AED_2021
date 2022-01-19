#ifndef H_MENU
#define H_MENU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

struct Menu
{
    int largo = 0, ancho = 0;
    int margen = 0;
    int seleccion = -1;
    ListaCadenas *titulo = NULL;
    ListaCadenas *opciones = NULL;
    ListaCadenas *valores = NULL;
    ListaCadenas *controles = NULL;
};

void modificar_dato(Menu &menu, const char dato[], const char valor[])
{
    /**
     * 
    */

    int aux = 0;
    char temp[5] = "";

    if (strcmp(dato, "largo") == 0) menu.largo = atoi(valor);
    if (strcmp(dato, "ancho") == 0) menu.ancho = atoi(valor);
    if (strcmp(dato, "margen") == 0) menu.margen = atoi(valor);
    if (strcmp(dato, "seleccion") == 0) menu.seleccion = atoi(valor);
    if (strcmp(dato, "titulo") == 0) insertar_cadena(menu.titulo, valor);
    if (strcmp(dato, "control") == 0) insertar_cadena(menu.controles, valor);
    if (strcmp(dato, "opcion") == 0)
    {
        if (valor[1] == '-')
            aux = 1;
        else if (valor[2] == '-')
            aux = 2;

        memcpy(temp, valor, aux);

        if (modificar_cadena(menu.opciones, &valor[aux+1], atoi(temp)) == 1)
            insertar_cadena(menu.opciones, &valor[aux+1], atoi(temp));
    }
    if (strcmp(dato, "valor") == 0)
    {
        if (valor[1] == '-')
            aux = 1;
        else if (valor[2] == '-')
            aux = 2;

        memcpy(temp, valor, aux);

        if (modificar_cadena(menu.valores, &valor[aux+1], atoi(temp)) == 1)
            insertar_cadena(menu.valores, &valor[aux+1], atoi(temp));
    }
}

void mostrar_menu(Menu menu)
{
    system("cls");

    int imprimir = 0, ultimo_imprimir = -1, pos_opcion = 0, pos = 0; // Define que parametro se va a imprimir
    int linea_opcion = 1, linea_control = 1;                                          // En que linea se imprimen los controles
    
    ListaCadenas *aux_titulos = menu.titulo;
    ListaCadenas *aux_opciones = menu.opciones;
    ListaCadenas *aux_controles = menu.controles;
    char buffer[100] = "";

    // Valores por defecto ante entradas no validas o nulas
    if (menu.largo < 2) menu.largo = 20;
    if (menu.ancho < 2) menu.ancho = 70;
    if (menu.margen < 1) menu.margen = 1;

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
            if (x >= 0 && y >= (menu.ancho/2))
            {
                if (aux_titulos != NULL && ultimo_imprimir != imprimir)
                {
                    for (int z = 0; z < ((strlen(aux_titulos->cadena)/2) + (strlen(aux_titulos->cadena)%2) + ((menu.ancho/2)%2)); z++) printf("\b");
                    printf("%s", aux_titulos->cadena);

                    y += ((strlen(aux_titulos->cadena)/2) - ((menu.ancho/2)%2));

                    aux_titulos = aux_titulos->sig;
                    ultimo_imprimir = imprimir;
                    linea_opcion++;
                    linea_control++;
                }
            }

            // Opciones
            if (x >= linea_opcion && (y >= menu.margen && y < menu.ancho-menu.margen))
            {
                if (aux_opciones != NULL && ultimo_imprimir != imprimir)
                {
                    char selec[4] = "";
                    if (menu.seleccion == aux_opciones->id) strcpy(selec, "\xAF");
                    else strcpy(selec, " ");

                    printf("\b\b%s %s", selec, aux_opciones->cadena);
                
                    if (obtener_cadena(menu.valores, aux_opciones->id, buffer) == 0)
                    {
                        printf(": %s", buffer);
                        y += 2 + strlen(buffer);
                    }

                    y += strlen(aux_opciones->cadena);

                    aux_opciones = aux_opciones->sig;
                    ultimo_imprimir = imprimir;
                    linea_control++;
                }
            }

            // Controles
            if (x >= linea_control && y >= menu.ancho-4)
            {
                if (aux_controles != NULL && ultimo_imprimir != imprimir)
                {
                    for (int borrar = 0; borrar < strlen(aux_controles->cadena); borrar++) printf("\b");

                    printf("%s", aux_controles->cadena);

                    aux_controles = aux_controles->sig;
                    ultimo_imprimir = imprimir;
                }
            }

            // Espacios en blanco
            printf(" ");
        }
        
        imprimir++;

        // Lateral derecho
        printf("\xBA\n");
    }
    
    // Borde inferior
    printf("\xC8");
    for (int x = 0; x < menu.ancho-2; x++) printf("\xCD");
    printf("\xBC\n");

    // DEBUG
    //printf("  imprimir=%d, ultimo_imprimir=%d, pos_opcion=%d, pos_control=%d\n\n", imprimir, ultimo_imprimir, pos_opcion, pos);
}

#endif