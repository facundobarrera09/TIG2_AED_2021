#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "datos.h"
#include "menu_login.h"
#include "error.h"

int buscar_usuario(Usuario usuario, Usuario usuarios[MAX_USUARIOS], int cantidad);
int cantidad_mayusculas(const char cadena[]);
int cantidad_digitos(const char cadena[]);

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
    int seleccion = 2;
    int estado_de_usuario;

    bool ejecutar = true;
    char entrada[36];
    
    usuario_ingresado.tipo = tipo;
    
    reestablecer_menu();
    actualizar_menu(0, MENU1);
    actualizar_menu(1, "Inicio de sesion");

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        mostrar_menu(seleccion);
        scanf("%s", entrada);

        if (strcmp(entrada, "NX") == 0)
        {
            if (seleccion == 2) seleccion = 3;
            else seleccion = 2;
        }
        else if (strcmp(entrada, "OK") == 0)
        {
            strcpy(usuario_ingresado.usuario, menu.usuario);
            strcpy(usuario_ingresado.contrasena, menu.contrasena);
            ejecutar = false;
        }
        else
        {
            actualizar_menu(seleccion, entrada);
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

int crear_usuario(Usuario usuarios[MAX_USUARIOS], int &cantidad, Error *&e)
{
    /**
     * INT DE RETORNO
     * 
     * 0 - Usuario creado y almacenado con exito
     * 1 - Se ingresaron datos invalidos
     * 2 - No hay mas espacio
     * 3 - Error al escribir el usuario
     * 
     */

    Usuario usuario_ingresado;
    int seleccion = 2;

    Error *errores = NULL;

    bool ejecutar = true;
    char entrada[36];

    reestablecer_menu();
    actualizar_menu(0, MENU2);
    actualizar_menu(1, "Creacion de usuario");

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        mostrar_menu(seleccion);
        scanf("%s", entrada);

        if (strcmp(entrada, "NX") == 0)
        {
            if (seleccion < 4) seleccion++;
            else seleccion = 2;
        }
        else if (strcmp(entrada, "OK") == 0)
        {
            strcpy(usuario_ingresado.usuario, menu.usuario);
            strcpy(usuario_ingresado.contrasena, menu.contrasena);

            if (strcmp(menu.tipo, "ADMIN") == 0)
                usuario_ingresado.tipo = 1;
            else if (strcmp(menu.tipo, "PROF") == 0)
                usuario_ingresado.tipo = 2;
            else if (strcmp(menu.tipo, "ASIST") == 0)
                usuario_ingresado.tipo = 3;
            else
                usuario_ingresado.tipo = 0;
            
            ejecutar = false;
        }
        else
        {
            actualizar_menu(seleccion, entrada);
        }

        system("cls");
    }

    // Verificar que los datos sean correctos
    if (strcmp(usuario_ingresado.usuario, "") == 0 || strcmp(usuario_ingresado.contrasena, "") == 0 || usuario_ingresado.tipo == 0)
        return 1;

        // Verificacion de nombre de usuario
    if (strlen(usuario_ingresado.usuario) < 6 || strlen(usuario_ingresado.usuario) > 10)
        insertar_error(errores, C_USUARIO_TAMANO);
    if (usuario_ingresado.usuario[0] < 97 || usuario_ingresado.usuario[0] > 122)
        insertar_error(errores, C_USUARIO_NO_MINUS);
    if (cantidad_mayusculas(usuario_ingresado.usuario) < 2)
        insertar_error(errores, C_USUARIO_NO_MAYUS);
    if (cantidad_digitos(usuario_ingresado.usuario) > 3)
        insertar_error(errores, C_USUARIO_EXCESO_DIGITOS);

        // Verificación de existencia
    int estado = buscar_usuario(usuario_ingresado, usuarios, cantidad);
    if (estado == 0 || estado == 2)
        insertar_error(errores, C_USUARIO_EXISTENTE);

        // Si hay errores, retornar
    if (errores != NULL)
    {
        e = errores;
        return 1;
    }
    
    // Crear usuario
        // Verificar si hay espacio
    if (cantidad+1 == MAX_USUARIOS)
        return 2;

        // Añadir usuario a arreglo
    cantidad++;
    usuarios[cantidad] = usuario_ingresado;
    
        // Escribir usuario en archivo
    if (escribir_usuario(usuario_ingresado) != 0)
    {
        memset(&usuarios[cantidad--], '\0', sizeof(Usuario));
        return 3;
    }

    return 0;
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

    return -1;
}

int cantidad_mayusculas(const char cadena[])
{
    int cantidad = 0;

    for (int x = 0; x < strlen(cadena); x++)
        if (cadena[x] > 65 && cadena[x] < 90)
            cantidad++;

    return cantidad;
}

int cantidad_digitos(const char cadena[])
{
    int cantidad = 0;

    for (int x = 0; x < strlen(cadena); x++)
        if (cadena[x] > 48 && cadena[x] < 57)
            cantidad++;

    return cantidad;
}
