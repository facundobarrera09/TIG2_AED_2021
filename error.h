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
//          Datos del profesional
const int C_USUARIO_PROF = 250;
//      Inicio de sesion
const int C_INICIO_NO_ARCHIVO = 300;
const int C_INICIO_NO_USUARIOS = 301;
const int C_INICIO_NO_EXISTE_USUARIO = 302;
const int C_INICIO_NO_COINCIDE_TIPO = 303;
const int C_INICIO_NO_COINCIDE_CONTRASENA = 304;
//      Creacion de cliente
const int C_CLIENTE_DNI_VACIO = 400;
const int C_CLIENTE_NOMBRE_VACIO = 401;
const int C_CLIENTE_EXISTE = 402;
//      Creacion de profesional
const int C_PROF_VACIO = 450;
const int C_PROF_USUARIO_EXISTE = 451;
const int C_PROF_DNI_EXISTE = 452;
const int C_PROF_ID_EXISTE = 453;
//      Creacion de informe
const int C_INFORME_CLI_VACIO = 500;
const int C_INFORME_PROF_VACIO = 501;
const int C_INFORME_VACIO = 502;
const int C_INFORME_CLIENTE_NO_EXISTE = 503;
const int C_INFORME_PROF_NO_EXISTE = 504;

// Descripción de error

//      Creacion de usuario
const char D_CREACION_VACIO[] = "El usuario no puede contener campos vacios";
//          Nombre
const char D_USUARIO_EXISTENTE[] = "Ya existe un usuario con ese nombre";
const char D_USUARIO_NO_MAYUS[] = "El usuario debe tener al menos letras 2 mayusculas";
const char D_USUARIO_NO_MINUS[] = "El usuario debe comenzar con una letra minuscula";
const char D_USUARIO_EXCESO_DIGITOS[] = "El usuario no debe tener mas de 3 digitos";
const char D_USUARIO_TAMANO[] = "El usuario debe tener entre 6 y 10 caracteres";
//          Contraseña
const char D_CONTRASENA_FALTAN_CARACTERES[] = "La contrase\xA4 \ba debe contener una letra mayuscula, una minuscula, y un digito";
const char D_CONTRASENA_CARACTERES_INVALIDOS[] = "La contrase\xA4 \ba debe ser alfanumerica (unicamente letras y numeros)";
const char D_CONTRASENA_CARACTERES_CONSECUTIVOS[] = "La contrase\xA4 \ba no debe tener 2 letras alfabeticamente consecutivas";
const char D_CONTRASENA_DIGITOS_CONSECUTIVOS[] = "La contrase\xA4 \ba no debe tener 3 numeros consecutivos";
const char D_CONTRASENA_TAMANO[] = "La contrase\xA4 \ba debe tener entre 6 y 32 caracteres";
//          Datos del profesional
const char D_USUARIO_PROF[] = "No se pudo crear el profesional asociado al usuario";
//      Inicio de sesion
const char D_INICIO_NO_ARCHIVO[] = "No se pudo abrir el archivo \"usuarios.dat\"";
const char D_INICIO_NO_USUARIOS[] = "No existen usuarios";
const char D_INICIO_NO_EXISTE_USUARIO[] = "No se encontro el usuario";
const char D_INICIO_NO_COINCIDE_TIPO[] = "El usuario ingresado no coincide con el tipo";
const char D_INICIO_NO_COINCIDE_CONTRASENA[] = "La contrase\xA4 \ba ingresada es incorrecta";
//      Creacion de cliente
const char D_CLIENTE_DNI_VACIO[] = "El numero de DNI no puede ser nulo";
const char D_CLIENTE_NOMBRE_VACIO[] = "El nombre no puede ser nulo";
const char D_CLIENTE_EXISTE[] = "El DNI ingresado le pertenece a otro cliente";
//      Creacion de profesional
const char D_PROF_VACIO[] = "El nombre, DNI, id, y usuario no pueden estar vacios";
const char D_PROF_USUARIO_EXISTE[] = "El usuario ingresado ya esta asociado a otro profesional";
const char D_PROF_DNI_EXISTE[] = "El DNI ingresado le pertenece a otro profesional";
const char D_PROF_ID_EXISTE[] = "El ID ingresado le pertenece a otro profesional";
//      Creacion de informe
const char D_INFORME_CLI_VACIO[] = "No existen clientes registrados";
const char D_INFORME_PROF_VACIO[] = "No existen profesionales registrados";
const char D_INFORME_VACIO[] = "El ID del profesional, DNI del cliente, y el informe, no pueden ser nulos";
const char D_INFORME_CLIENTE_NO_EXISTE[] = "El DNI del cliente no se encuentra registrado";
const char D_INFORME_PROF_NO_EXISTE[] = "El ID del profesional no se encuentra registrado";

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

    case C_USUARIO_PROF:
        strcpy(buffer, D_USUARIO_PROF);
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

    case C_CLIENTE_DNI_VACIO:
        strcpy(buffer, D_CLIENTE_DNI_VACIO);
        break;
    case C_CLIENTE_NOMBRE_VACIO:
        strcpy(buffer, D_CLIENTE_NOMBRE_VACIO);
        break;
    case C_CLIENTE_EXISTE:
        strcpy(buffer, D_CLIENTE_EXISTE);
        break;
    
    case C_PROF_DNI_EXISTE:
        strcpy(buffer, D_PROF_DNI_EXISTE);
        break;
    case C_PROF_ID_EXISTE:
        strcpy(buffer, D_PROF_ID_EXISTE);
        break;
    case C_PROF_VACIO:
        strcpy(buffer, D_PROF_VACIO);
        break;
    case C_PROF_USUARIO_EXISTE:
        strcpy(buffer, D_PROF_USUARIO_EXISTE);
        break;
    
    case C_INFORME_CLI_VACIO:
        strcpy(buffer, D_INFORME_CLI_VACIO);
        break;
    case C_INFORME_PROF_VACIO:
        strcpy(buffer, D_INFORME_PROF_VACIO);
        break;
    case C_INFORME_CLIENTE_NO_EXISTE:
        strcpy(buffer, D_INFORME_CLIENTE_NO_EXISTE);
        break;
    case C_INFORME_PROF_NO_EXISTE:
        strcpy(buffer, D_INFORME_PROF_NO_EXISTE);
        break;
    case C_INFORME_VACIO:
        strcpy(buffer, D_INFORME_VACIO);
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