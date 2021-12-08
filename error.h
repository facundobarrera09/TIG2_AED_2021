#ifndef H_CE_ERROR
#define H_CE_ERROR

#include <stdio.h>
#include <string.h>

struct Error
{
    int codigo = 0;
    char descripcion[100];
    Error *sig = NULL;
};

void insertar_error(Error *&error, int codigo, const char descripcion[])
{
    Error *ultimo = error;

    if (error == NULL) 
    {
        error = new Error;
        error->codigo = codigo;
        strcpy(error->descripcion, descripcion);
    }
    else
    {
        while (ultimo->sig != NULL) ultimo = ultimo->sig;

        ultimo->sig = new Error;
        ultimo = ultimo->sig;
        ultimo->codigo = codigo;
        strcpy(ultimo->descripcion, descripcion);
    }
}
Error obtener_error(Error *&errores)
{
    Error error, *p;

    if (errores != NULL)
    {
        error = *errores;
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

// Codigos de error

//      Creacion de usuario
//          Nombre
const int C_USUARIO_EXISTENTE = 100;
const int C_USUARIO_NO_MAYUS = 101;
const int C_USUARIO_NO_MINUS = 102;
const int C_USUARIO_EXCESO_DIGITOS = 103;
const int C_USUARIO_TAMANO = 104;
//          Contraseña
const int C_CONTRASENA_FALTAN_CARACTERES = 200;
const int C_CONTRASENA_CARACTERES_INVALIDOS = 201;
const int C_CONTRASENA_CARACTERES_CONSECUTIVOS = 202;
const int C_CONTRASENA_DIGITOS_CONSECUTIVOS = 203;
const int C_CONTRASENA_TAMANO = 204;

// Descripción de error
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

#endif