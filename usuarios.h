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
bool contiene_caracteres_necesarios(const char cadena[]);
bool contiene_caracteres_invalidos(const char cadena[]);
int digitos_consecutivos(const char cadena[]);
int caracteres_consecutivos(const char cadena[]);

// FUNCION PRINCIPAL

int inicio_de_sesion(Usuario &usuario, int tipo, Usuario usuarios[MAX_USUARIOS], int cantidad, Error *&errores)
{
    /**
     * INT DE RETORNO:
     * 
     * 0 - Se inicio sesion correctamente y se devolvió usuario
     * 1 - No existe el usuario
     * 2 - El usuario ingresado no coincide con el tipo
     * 3 - No coincide la contraseña
     * 4 - Usuarios esta vacio
     * 
     */

    Menu menu;
    Usuario usuario_ingresado;
    int seleccion = 0;
    int estado_de_usuario;
    eliminar_errores(errores);

    bool ejecutar = true;
    char entrada[36];
    
    usuario_ingresado.tipo = tipo;

    modificar_dato(menu, "largo", "9");
    modificar_dato(menu, "ancho", "52");
    modificar_dato(menu, "titulo", "Inicio de sesion");

    modificar_dato(menu, "opcion", "0-Usuario");
    modificar_dato(menu, "opcion", "1-Contrasena");
    modificar_dato(menu, "valor", "0- ");
    modificar_dato(menu, "valor", "1- ");

    modificar_dato(menu, "seleccion", "0");

    modificar_dato(menu, "control", "NX para siguiente");
    modificar_dato(menu, "control", "OK para terminar ");

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        mostrar_menu(menu);
        printf("\n> ");
        scanf("%s", entrada);

        if (strcmp(entrada, "NX") == 0)
        {
            if (seleccion == 2) seleccion = 3;
            else seleccion = 2;
        }
        else if (strcmp(entrada, "OK") == 0)
        {
            strcpy(usuario_ingresado.usuario, menu_login.usuario);
            strcpy(usuario_ingresado.contrasena, menu_login.contrasena);
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
    {
        insertar_error(errores, C_CREACION_VACIO);    
        return 1;
    }

    // Verificar que el usuario exista

    estado_de_usuario = buscar_usuario(usuario_ingresado, usuarios, cantidad);
    
    switch (estado_de_usuario)
    {
    case 0:
        usuario = usuario_ingresado;
        return 0;
    case 1:
        insertar_error(errores, C_INICIO_NO_COINCIDE_CONTRASENA);
        return 3;
    case 2:
        insertar_error(errores, C_INICIO_NO_COINCIDE_TIPO);
        return 2;
    case 3:
        insertar_error(errores, C_INICIO_NO_EXISTE_USUARIO);
        return 1;
    case 4:
        insertar_error(errores, C_INICIO_NO_USUARIOS);
        return 4;
    }

    return -1;
}

int crear_usuario(Usuario usuarios[MAX_USUARIOS], int &cantidad, int tipo, Error *&errores)
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

    //Error *errores = NULL;
    eliminar_errores(errores);

    bool ejecutar = true;
    char entrada[36];

    reestablecer_menu();
    actualizar_menu(0, MENU2);
    actualizar_menu(1, "Creacion de usuario");

    if (tipo != 0)
    {
        usuario_ingresado.tipo = tipo;
        if (tipo == COD_ADMIN)
            actualizar_menu(4, "ADMIN");
        if (tipo == COD_PROF)
            actualizar_menu(4, "PROF");
        if (tipo == COD_ASIST)
            actualizar_menu(4, "ASIST");
    }

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        n_mostrar_menu(seleccion);
        scanf("%s", entrada);

        if (strcmp(entrada, "NX") == 0)
        {
            if (tipo == 0)
            {
                if (seleccion < 4) seleccion++;
                else seleccion = 2;
            }
            else
            {
                if (seleccion < 3) seleccion++;
                else seleccion = 2;
            }
        }
        else if (strcmp(entrada, "OK") == 0)
        {
            strcpy(usuario_ingresado.usuario, menu_login.usuario);
            strcpy(usuario_ingresado.contrasena, menu_login.contrasena);

            if (strcmp(menu_login.tipo, "ADMIN") == 0)
                usuario_ingresado.tipo = COD_ADMIN;
            else if (strcmp(menu_login.tipo, "PROF") == 0)
                usuario_ingresado.tipo = COD_PROF;
            else if (strcmp(menu_login.tipo, "ASIST") == 0)
                usuario_ingresado.tipo = COD_ASIST;
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
        // Verificar que los datos no esten vacios
    if (strcmp(usuario_ingresado.usuario, "") == 0 || strcmp(usuario_ingresado.contrasena, "") == 0 || usuario_ingresado.tipo == 0)
    {
        insertar_error(errores, C_CREACION_VACIO);
        return 1;
    }

        // Verificar de nombre de usuario
    if (strlen(usuario_ingresado.usuario) < 6 || strlen(usuario_ingresado.usuario) > 10)
        insertar_error(errores, C_USUARIO_TAMANO);
    if (usuario_ingresado.usuario[0] < 97 || usuario_ingresado.usuario[0] > 122)
        insertar_error(errores, C_USUARIO_NO_MINUS);
    if (cantidad_mayusculas(usuario_ingresado.usuario) < 2)
        insertar_error(errores, C_USUARIO_NO_MAYUS);
    if (cantidad_digitos(usuario_ingresado.usuario) > 3)
        insertar_error(errores, C_USUARIO_EXCESO_DIGITOS);

        // Verificar si el nombre de usuario existe
    int estado = buscar_usuario(usuario_ingresado, usuarios, cantidad);
    if (estado == 0 || estado == 1 || estado == 2)
        insertar_error(errores, C_USUARIO_EXISTENTE);

        // Verificar contraseña
    if (strlen(usuario_ingresado.contrasena) < 6 || strlen(usuario_ingresado.contrasena) > 32)
        insertar_error(errores, C_CONTRASENA_TAMANO);
    if (!contiene_caracteres_necesarios(usuario_ingresado.contrasena))
        insertar_error(errores, C_CONTRASENA_FALTAN_CARACTERES);
    if (contiene_caracteres_invalidos(usuario_ingresado.contrasena))
        insertar_error(errores, C_CONTRASENA_CARACTERES_INVALIDOS);
    if (digitos_consecutivos(usuario_ingresado.contrasena) > 3)
        insertar_error(errores, C_CONTRASENA_DIGITOS_CONSECUTIVOS);
    if (caracteres_consecutivos(usuario_ingresado.contrasena))
        insertar_error(errores, C_CONTRASENA_CARACTERES_CONSECUTIVOS);

    // Si hay errores, retornar
    if (errores != NULL)
    {
        //e = errores;
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

int crear_usuario(Usuario usuarios[MAX_USUARIOS], int &cantidad, Error *&errores)
{
    return crear_usuario(usuarios, cantidad, 0, errores);
}

// FUNCIONES SECUNDARIAS

int buscar_usuario(Usuario usuario, Usuario usuarios[MAX_USUARIOS], int cantidad)
{
    /**
     * INT DE RETORNO:
     * 
     * 0 - Se encontro el usuario
     * 1 - Se encontro el usuario, no coincide la contraseña
     * 2 - Se encontro el usuario, no coincide el tipo
     * 3 - No se encontro el usuario
     * 4 - Usuarios está vacio
     * 
     */

    if (cantidad == 0)
        return 4;

    for (int x = 0; x < cantidad; x++)
    {
        if (strcmp(usuario.usuario, usuarios[x].usuario) == 0)
            if (usuario.tipo == usuarios[x].tipo)
                if (strcmp(usuario.contrasena, usuarios[x].contrasena) == 0)
                    return 0;
                else
                    return 1;
            else
                return 2;
    }

    return 3;
}

int cantidad_mayusculas(const char cadena[])
{
    int cantidad = 0;

    for (int x = 0; x < strlen(cadena); x++)
        if (cadena[x] >= 65 && cadena[x] <= 90)
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

bool contiene_caracteres_necesarios(const char cadena[])
{
    bool mayus = false, minus = false, num = false;

    for (int x = 0; x < strlen(cadena); x++)
    {
        if (cadena[x] >= 65 && cadena[x] <= 90)
            mayus = true;
        if (cadena[x] >= 97 && cadena[x] <= 122)
            minus = true;
        if (cadena[x] >= 48 && cadena[x] <= 57)
            num = true;

        if (mayus && minus && num)
            break;
    }

    return (mayus && minus && num);
}

bool contiene_caracteres_invalidos(const char cadena[])
{
    bool contiene = false;

    for (int x = 0; x < strlen(cadena); x++)
    {
        if (!((cadena[x] >= 65 && cadena[x] <= 90) || (cadena[x] >= 97 && cadena[x] <= 122) || (cadena[x] >= 48 && cadena[x] <= 57)))
        {
            contiene = true;
            break;
        }
    }

    return contiene;
}

int digitos_consecutivos(const char cadena[])
{
    int consecutivos = 0, consecutivos_final = 0;
    char anterior = cadena[0];

    for (int x = 1; x < strlen(cadena); x++)
    {
        if (cadena[x] >= 48 && cadena[x] <= 57)
        {
            if (anterior >= 48 && anterior <= 57)
                if (cadena[x] == anterior + 1)
                {
                    consecutivos++;
                    if (consecutivos > consecutivos_final)
                        consecutivos_final = consecutivos;
                }
                else
                    consecutivos = 1;
            else 
                consecutivos = 1;
        }
        else
            consecutivos = 0;

        anterior = cadena[x];
    }
    
    return consecutivos_final;
}

int caracteres_consecutivos(const char cadena[])
{
    int consecutivos = 0, consecutivos_final = 0;
    char anterior = cadena[0];

    for (int x = 1; x < strlen(cadena); x++)
    {
        if ((cadena[x] >= 65 && cadena[x] <= 90) || (cadena[x] >= 97 && cadena[x] <= 122))
        {
            if ((anterior >= 65 && anterior <= 90) || (anterior >= 97 && anterior <= 122))
                if (cadena[x] == anterior + 1 || cadena[x] == anterior + 32 + 1 || cadena[x] == anterior - 32 + 1)
                {
                    consecutivos++;
                    if (consecutivos > consecutivos_final)
                        consecutivos_final = consecutivos;
                }
                else
                    consecutivos = 1;
            else 
                consecutivos = 1;
        }
        else
            consecutivos = 0;

        anterior = cadena[x];
    }
    
    return consecutivos_final;
}

