#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "menu_login.h"

int buscar_usuario(Usuario usuario, Usuario usuarios[MAX_USUARIOS], int cantidad);

// FUNCION PRINCIPAL

int inicio_de_sesion(Usuario &usuario, int tipo, Usuario usuarios[MAX_USUARIOS], int cantidad)
{
    /**
     * INT DE RETORNO:
     * 
     * 0 - Se inicio sesion correctamente y se devolvió usuario
     * 1 - No existe el usuario
     * 2 - El usuario ingresado no coincide con el tipo
     * 3 - Usuarios esta vacio
     * 
     */

    Usuario usuario_ingresado;
    int seleccion = 1;
    int estado_de_usuario;

    bool ejecutar = true;
    char opcion[36];
    
    usuario_ingresado.tipo = tipo;

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

    estado_de_usuario = buscar_usuario(usuario_ingresado, usuarios, cantidad);
    
    if (estado_de_usuario == 0)
    {
        usuario = usuario_ingresado;
        return 0;
    }
    else
        return estado_de_usuario;
}

// FUNCIONES SECUNDARIAS

int buscar_usuario(Usuario usuario, Usuario usuarios[MAX_USUARIOS], int cantidad)
{
    /**
     * INT DE RETORNO:
     * 
     * 0 - Se encontro el usuario
     * 1 - No se encontro el usuario
     * 2 - Se encontro el usuario pero coincide el tipo
     * 3 - Usuarios está vacio
     * 
     */

    if (cantidad == 0)
        return 3;

    for (int x = 0; x < cantidad; x++)
    {
        if (strcmp(usuario.usuario, usuarios[x].usuario) == 0 && strcmp(usuario.contrasena, usuarios[x].contrasena) == 0)
        {
            if (usuario.tipo == usuarios[x].tipo)
                return 0;
            else
                return 2;
        }
    }
}
