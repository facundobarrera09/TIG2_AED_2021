#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "menu_login.h"

int inicio_de_sesion(Usuario &usuario, Usuario usuarios[MAX_USUARIOS], int cantidad)
{
    Usuario usuario_ingresado;
    int seleccion = 1;

    bool ejecutar = true;
    char opcion[36];

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");

        mostrar_menu(seleccion);
        scanf("%s", opcion);

        if (strcmp(opcion, "NX") == 0)
        {
            if (seleccion == 1) seleccion = 2;
            else seleccion = 1;
        }
        else if (strcmp(opcion, "OK") == 0)
        {
            strcpy(usuario_ingresado.usuario, menu.usuario);
            strcpy(usuario_ingresado.contrasena, menu.contrasena);
            ejecutar = false;
        }
        else
        {
            actualizar_menu(seleccion, opcion);
        }

        system("cls");
    }

    // Verificar que los datos sean correctos
    if (strcmp(usuario_ingresado.usuario, "") == 0 || strcmp(usuario_ingresado.contrasena, "") == 0)
        return 1;

    // Verificar que el usuario exista


    return 0;
}

bool existe_usuario();
