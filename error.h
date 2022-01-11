#ifndef H_CE_ERROR
#define H_CE_ERROR

#include <stdio.h>
#include <string.h>

// Codigos de error

//      Creacion de usuario
const int C_CREACION_VACIO = 100;
//          Nombre
const int C_USUARIO_EXISTENTE = 101;
const int C_USUARIO_NO_MAYUS = 102;
const int C_USUARIO_NO_MINUS = 103;
const int C_USUARIO_EXCESO_DIGITOS = 104;
const int C_USUARIO_TAMANO = 105;
//          Contraseña
const int C_CONTRASENA_FALTAN_CARACTERES = 200;
const int C_CONTRASENA_CARACTERES_INVALIDOS = 201;
const int C_CONTRASENA_CARACTERES_CONSECUTIVOS = 202;
const int C_CONTRASENA_DIGITOS_CONSECUTIVOS = 203;
const int C_CONTRASENA_TAMANO = 204;
//      Inicio de sesion
const int C_INICIO_NO_ARCHIVO = 300;
const int C_INICIO_NO_USUARIOS = 301;
const int C_INICIO_NO_EXISTE_USUARIO = 302;
const int C_INICIO_NO_COINCIDE_TIPO = 303;
const int C_INICIO_NO_COINCIDE_CONTRASENA = 304;

// Descripción de error

//      Creacion de usuario
const char D_CREACION_VACIO[] = "El usuario no puede contener campos vacios";
//          Nombre
const char D_USUARIO_EXISTENTE[] = "Ya existe un usuario con ese nombre";
const char D_USUARIO_NO_MAYUS[] = "Debe tener al menos letras 2 mayusculas";
const char D_USUARIO_NO_MINUS[] = "Debe comenzar con una letra minuscula";
const char D_USUARIO_EXCESO_DIGITOS[] = "No debe tener mas de 3 digitos";
const char D_USUARIO_TAMANO[] = "Debe tener entre 6 y 10 caracteres";
//          Contraseña
const char D_CONTRASENA_FALTAN_CARACTERES[] = "Debe contener una letra mayuscula, una minuscula, y un digito";
const char D_CONTRASENA_CARACTERES_INVALIDOS[] = "Debe ser alfanumerica (unicamente letras y numeros)";
const char D_CONTRASENA_CARACTERES_CONSECUTIVOS[] = "No debe tener 2 letras alfabeticamente consecutivas";
const char D_CONTRASENA_DIGITOS_CONSECUTIVOS[] = "No debe tener 3 numeros consecutivos";
const char D_CONTRASENA_TAMANO[] = "Debe tener entre 6 y 32 caracteres";
//      Inicio de sesion
const char D_INICIO_NO_ARCHIVO[] = "No se pudo abrir el archivo \"usuarios.dat\"";
const char D_INICIO_NO_USUARIOS[] = "No existen usuarios";
const char D_INICIO_NO_EXISTE_USUARIO[] = "No se encontro el usuario";
const char D_INICIO_NO_COINCIDE_TIPO[] = "El usuario ingresado no coincide con el tipo";
const char D_INICIO_NO_COINCIDE_CONTRASENA[] = "La contraseña ingresada es incorrecta";

// Errores

struct Error
{
    int codigo = 0;
    char descripcion[100];
    Error *sig = NULL;
};

void obtener_descripcion_de_error(int codigo, char buffer[])
{
    switch (codigo)
    {
    case C_CREACION_VACIO:
        strcpy(buffer, D_CREACION_VACIO);
        break;

    case C_USUARIO_EXISTENTE:
        strcpy(buffer, D_USUARIO_EXISTENTE);
        break;
    case C_USUARIO_NO_MAYUS:
        strcpy(buffer, D_USUARIO_NO_MAYUS);
        break;
    case C_USUARIO_NO_MINUS:
        strcpy(buffer, D_USUARIO_NO_MINUS);
        break;
    case C_USUARIO_EXCESO_DIGITOS:
        strcpy(buffer, D_USUARIO_EXCESO_DIGITOS);
        break;
    case C_USUARIO_TAMANO:
        strcpy(buffer, D_USUARIO_TAMANO);
        break;

    case C_CONTRASENA_FALTAN_CARACTERES:
        strcpy(buffer, D_CONTRASENA_FALTAN_CARACTERES);
        break;
    case C_CONTRASENA_CARACTERES_INVALIDOS:
        strcpy(buffer, D_CONTRASENA_CARACTERES_INVALIDOS);
        break;
    case C_CONTRASENA_CARACTERES_CONSECUTIVOS:
        strcpy(buffer, D_CONTRASENA_CARACTERES_CONSECUTIVOS);
        break;
    case C_CONTRASENA_DIGITOS_CONSECUTIVOS:
        strcpy(buffer, D_CONTRASENA_DIGITOS_CONSECUTIVOS);
        break;
    case C_CONTRASENA_TAMANO:
        strcpy(buffer, D_CONTRASENA_TAMANO);
        break;

    case C_INICIO_NO_ARCHIVO:
        strcpy(buffer, D_INICIO_NO_ARCHIVO);
        break;
    case C_INICIO_NO_USUARIOS:
        strcpy(buffer, D_INICIO_NO_USUARIOS);
        break;
    case C_INICIO_NO_EXISTE_USUARIO:
        strcpy(buffer, D_INICIO_NO_EXISTE_USUARIO);
        break;
    case C_INICIO_NO_COINCIDE_TIPO:
        strcpy(buffer, D_INICIO_NO_COINCIDE_TIPO);
        break;
    case C_INICIO_NO_COINCIDE_CONTRASENA:
        strcpy(buffer, D_INICIO_NO_COINCIDE_CONTRASENA);
        break;
    }
}

void insertar_error(Error *&error, int codigo)
{
    Error *ultimo = error;

    if (error == NULL) 
    {
        error = new Error;
        error->codigo = codigo;
        obtener_descripcion_de_error(codigo, error->descripcion);
    }
    else
    {
        while (ultimo->sig != NULL) ultimo = ultimo->sig;

        ultimo->sig = new Error;
        ultimo = ultimo->sig;
        ultimo->codigo = codigo;
        obtener_descripcion_de_error(codigo, ultimo->descripcion);
    }
}
Error obtener_error(Error *&errores)
{
    Error error, *p;

    if (errores != NULL)
    {
        error.codigo = errores->codigo;
        strcpy(error.descripcion, errores->descripcion);
        error.sig = NULL;

        p = errores->sig;
        delete(errores);
        errores = p;
    }

    return error;
}
void eliminar_errores(Error *&error)
{
    Error *p;

    while (error != NULL)
    {
        p = error->sig;
        delete(error);
        error = p;
    }
}

void mostrar_errores(Error *&errores)
{
    Error e;

    if (errores != NULL)
    {
        e = obtener_error(errores);
        while (e.codigo != 0)
        {
            printf("ERROR %d: %s\n", e.codigo, e.descripcion);
            e = obtener_error(errores);
        }
    }
}

#endif