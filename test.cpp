#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "usuarios.h"
#include "error.h"

void test0(); // inicio de sesion
void test1(); // creacion de usuario
void test2(); // errores

int main()
{
    int TEST = 0;
    printf("Ingrese valor a testear: ");
    scanf("%d", &TEST);

    switch (TEST)
    {
    case 0:
        test0();
        break;
    
    case 1:
        test1();
        break;

    case 2:
        test2();
        break;
    }
}

void test0()
{
    Usuario usuarios[MAX_USUARIOS], usuario;
    int cantidad = 3, tipo = 1;

    strcpy(usuarios[0].usuario, "facundo");
    strcpy(usuarios[1].usuario, "lucia");
    strcpy(usuarios[2].usuario, "carla");

    strcpy(usuarios[0].contrasena, "facundo");
    strcpy(usuarios[1].contrasena, "lucia");
    strcpy(usuarios[2].contrasena, "carla");

    usuarios[0].tipo = 1;
    usuarios[1].tipo = 1;
    usuarios[2].tipo = 2;

    inicio_de_sesion(usuario, tipo, usuarios, cantidad);
}

void test1()
{
    Error e, *e1 = NULL, *e2 = NULL, *e3 = NULL;
    Usuario usuarios[MAX_USUARIOS];
    int cantidad = 0;

    leer_usuarios(usuarios, cantidad);

    int status1 = crear_usuario(usuarios, cantidad, e1);
    int status2 = crear_usuario(usuarios, cantidad, e2);
    int status3 = crear_usuario(usuarios, cantidad, e3);

/*
faC12Bar
NX
123ab
NX
ADMIN
OK
Fac123barerr
NX
1234.aB
NX
PROF
OK
lUC1aBarr
NX
aM3h2dI
NX
ASIST
OK

*/

    printf("ESTADOS:\n\tstatus1=%d\n\tstatus2=%d\n\tstatus3=%d\n", status1, status2, status3);

    printf("\nUsuario 1:\n");
    if (e1 != NULL)
    {
        e = obtener_error(e1); 
        while (e.codigo != 0)
        {
            printf("ERROR %d: %s\n", e.codigo, e.descripcion);
            e = obtener_error(e1); 
        }
    }

    printf("\nUsuario 2:\n");
    if (e2 != NULL)
    {
        e = obtener_error(e2); 
        while (e.codigo != 0)
        {
            printf("ERROR %d: %s\n", e.codigo, e.descripcion);
            e = obtener_error(e2); 
        }
    }

    printf("\nUsuario 3:\n");
    if (e3 != NULL)
    {
        e = obtener_error(e3); 
        while (e.codigo != 0)
        {
            printf("ERROR %d: %s\n", e.codigo, e.descripcion);
            e = obtener_error(e3); 
        }
    }
}

void test2()
{
    Error *errores = NULL, *e, error;

    if (true)
    {
        insertar_error(errores, C_USUARIO_TAMANO);
        insertar_error(errores, C_USUARIO_NO_MINUS);
        insertar_error(errores, C_USUARIO_EXISTENTE);
    }

    if (errores != NULL)
    {
        error = obtener_error(errores);
        while (error.codigo != 0)
        {
            printf("ERROR %d: %s\n", error.codigo, error.descripcion);
            error = obtener_error(errores);
        }

        printf("Recorriendo cola:");
        e = errores;
        while (e != NULL)
        {
            printf("ERROR %d: %s\n", e->codigo, e->descripcion);
            e = e->sig;
        }
    }
}



