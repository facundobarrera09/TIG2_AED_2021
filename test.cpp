#include <stdio.h>
#include <string.h>
#include <time.h>

#include "structs.h"
#include "funciones_structs.h"
#include "usuarios.h"
#include "error.h"
#include "menu.h"

void test0(); // inicio de sesion
void test1(); // creacion de usuario
void test2(); // errores
void test3(); // memcpy tests
void test4(); // menu
void test5(); // lista_cadenas
void test6(); // crear cliente
void test7(); // fecha actual

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

    case 3:
        test3();
        break;

    case 4:
        test4();
        break;

    case 5:
        test5();
        break;
    
    case 6:
        test6();
        break;
    
    case 7:
        test7();
        break;
    }
}

void test0()
{
    Usuario usuarios[MAX_USUARIOS], usuario;
    Error *errores;
    int cantidad = 3, tipo = 1, estado;

    strcpy(usuarios[0].usuario, "facundo");
    strcpy(usuarios[1].usuario, "lucia");
    strcpy(usuarios[2].usuario, "carla");

    strcpy(usuarios[0].contrasena, "facundo");
    strcpy(usuarios[1].contrasena, "lucia");
    strcpy(usuarios[2].contrasena, "carla");

    usuarios[0].tipo = 1;
    usuarios[1].tipo = 1;
    usuarios[2].tipo = 2;

    estado = inicio_de_sesion(usuario, tipo, usuarios, cantidad, errores);

    printf("estado=%d\n", estado);
    mostrar_errores(errores);
}

void test1()
{
    Error e, *e1 = NULL, *e2 = NULL, *e3 = NULL;
    Usuario usuarios[MAX_USUARIOS];
    int cantidad = 0;

    leer_usuarios(usuarios, cantidad);

    int status1 = crear_usuario(usuarios, cantidad, e1);
    int status2 = crear_usuario(usuarios, cantidad, e2);
    int status3 = crear_usuario(usuarios, cantidad, COD_ASIST, e3);

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

void test3()
{
    char cad1[11] = "Hola mundo", cad2[10] = "Facundo";

    printf("%s\n", cad1);

    memcpy(&cad1[5], cad2, sizeof(cad1));

    printf("%s\n", cad1);
    printf("%s\n", cad2);
}

void test4()
{
    Menu menu;

    // Aspecto fisico
    modificar_dato(menu, "largo", "12");
    modificar_dato(menu, "ancho", "71");
    modificar_dato(menu, "margen", "2");

    // Titulo
    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Creacion de usuarios");

    // Opciones y valores
    modificar_dato(menu, "opcion", "0-Nombre");
    modificar_dato(menu, "opcion", "1-Contrasena");
    modificar_dato(menu, "opcion", "2-Tipo");
    modificar_dato(menu, "opcion", "3-Salir");

    modificar_dato(menu, "valor", "0-Facundo");
    modificar_dato(menu, "valor", "1-bArr3ra");
    modificar_dato(menu, "valor", "2-ADMIN");

    modificar_dato(menu, "seleccion", "0");

    // Control del usuario
    modificar_dato(menu, "control", "NX para siguiente");
    modificar_dato(menu, "control", "OK para terminar ");

    mostrar_menu(menu);
}

void test5()
{
    ListaCadenas *lista = NULL, *p,*lista2 = NULL;
    char buffer[100] = "";

    // insercion
    insertar_cadena(lista, "hola");
    insertar_cadena(lista, "chau");
    insertar_cadena(lista, "buenas tardes");

    mostrar_cadenas(lista);
    printf("\n");

    insertar_cadena(lista, "intermedio", 1);

    mostrar_cadenas(lista);
    printf("\n");

    insertar_cadena(lista, "comienzo", 0);

    mostrar_cadenas(lista);
    printf("\n");

    insertar_cadena(lista, "excedido", 11);

    mostrar_cadenas(lista);
    printf("\n\n");

    // insersion a posicion en lista vacia
    insertar_cadena(lista2, "hola en 3", 3);
    insertar_cadena(lista2, "chau en 0", 0);

    mostrar_cadenas(lista2);
    printf("\n\n");

    // busqueda
    for (int x = 0; x < 13; x++)
    {
        if (obtener_cadena(lista, x, buffer) == 0)
            printf("Se encontro la cadena en la pos %d: %s\n", x, buffer);
        else
            printf("No se encontro la cadena en la pos %d\n", x);
    }
}

void test6()
{
    escribir_cliente(crear_cliente());
}

void test7()
{
    char buffer[100];
    Fecha hoy;
    time_t t;
    struct tm *tm;

    t = time(NULL);
    tm = localtime(&t);

    strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm);
    hoy = obtener_fecha(buffer);

    printf("fecha actual=%s\n", buffer);
}
