#ifndef H_CE_ERROR
#define H_CE_ERROR

#include <stdio.h>

struct Error
{
    int codigo;
    char descripcion[100];
    Error *sig = NULL;
};

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
const char C_USUARIO_EXISTENTE[] = "Ya existe un usuario con ese nombre";
const char C_USUARIO_NO_MAYUS[] = "Debe tener al menos letras 2 mayusculas";
const char C_USUARIO_NO_MINUS[] = "Debe comenzar con una letra minuscula";
const char C_USUARIO_EXCESO_DIGITOS[] = "No debe tener mas de 3 digitos";
const char C_USUARIO_TAMANO[] = "Debe tener entre 6 y 10 caracteres";
//          Contraseña
const char C_CONTRASENA_FALTAN_CARACTERES[] = "Debe contener una letra mayuscula, una minuscula, y un digito";
const char C_CONTRASENA_CARACTERES_INVALIDOS[] = "Debe ser alfanumerica (unicamente letras y numeros)";
const char C_CONTRASENA_CARACTERES_CONSECUTIVOS[] = "No debe tener 2 letras alfabeticamente consecutivas";
const char C_CONTRASENA_DIGITOS_CONSECUTIVOS[] = "No debe tener 3 numeros consecutivos";
const char C_CONTRASENA_TAMANO[] = "Debe tener entre 6 y 32 caracteres";

Error obtener_error()
{

}

#endif