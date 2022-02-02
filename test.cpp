#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structs.h"
#include "usuarios.h"
#include "error.h"
#include "menu.h"

void test0();   // inicio de sesion
void test1();   // creacion de usuario
void test2();   // errores
void test3();   // memcpy tests
void test4();   // menu
void test5();   // lista_cadenas
void test6();   // crear cliente
void test7();   // fecha actual
void test8();   // crear profesional
void test9();   // atoi
void test10();  // crear informe
void test11();  // cadena mas grande
void test12();  // crear turno
void test13();  // borrar turno

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

    case 8:
        test8();
        break;

    case 9:
        test9();
        break;

    case 10:
        test10();
        break;

    case 11:
        test11();
        break;

    case 12:
        test12();
        break;

    case 13:
        test13();
        break;
    }
}

void test0()
{
    Usuario usuarios[MAX_USUARIOS], usuario;
    Error *errores;
    int cantidad = 3, tipo = 1, estado;

    if (leer_usuarios(usuarios, cantidad) == 0)
    {
        estado = inicio_de_sesion(usuario, tipo, usuarios, cantidad, errores);

        printf("estado=%d\n", estado);
        mostrar_errores(errores);
    }
    else
        printf("ERROR - No existen usuarios o no se puede leer el archivo\n");
}

void test1()
{
    Error *errores = NULL;
    Usuario usuarios[MAX_USUARIOS];
    int cantidad = 0;

    if (leer_usuarios(usuarios, cantidad) == 0)
    {
        int status1 = crear_usuario(usuarios, cantidad, errores);

        printf("ESTADOS:\n\tstatus1=%d\n\n", status1);

        if (errores != NULL) mostrar_errores(errores);
    }

    printf("\n");

    for (int x = 0; x < cantidad; x++)
    {
        printf("Usuario %d:\n", x);
        printf(" - Usuario: %s\n", usuarios[x].usuario);
        printf(" - Contrasena: %s\n", usuarios[x].contrasena);
        printf(" - Tipo: ");
        if (usuarios[x].tipo == COD_ADMIN) printf("ADMIN\n");
        if (usuarios[x].tipo == COD_PROF) printf("PROF\n");
        if (usuarios[x].tipo == COD_ASIST) printf("ASIST\n");
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
    modificar_dato(menu, "margen", "4");

    // Titulo
    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Creacion de usuarios");

    // Opciones y valores
    modificar_dato(menu, "opcion", "0-Nombre");
    modificar_dato(menu, "opcion", "1-Contrasena");
    modificar_dato(menu, "opcion", "2-Tipo");
    modificar_dato(menu, "opcion", "13-Salir");

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
    Error *errores;
    Cliente clientes[MAX_CLIENTES];
    int cantidad, estado;

    if (leer_clientes(clientes, cantidad) != 2)
    {
        estado = crear_cliente(clientes, cantidad, errores);
        printf("\nestado=%d\n\n", estado);

        if (estado != 0)
        {
            mostrar_errores(errores);
            printf("\n");
        }
    }
    else
        printf("Error al leer archivo\n");

    for (int x = 0; x < cantidad; x++)
    {
        printf("Cliente %d:\n", x);
        printf(" - DNI: %d\n", clientes[x].dni);
        printf(" - Nombre: %s\n", clientes[x].nombre);
        printf(" - Domicilio: %s\n", clientes[x].domicilio);
        printf(" - Localidad: %s\n", clientes[x].localidad);
        printf(" - Nacimiento: %d/%d/%d\n", clientes[x].fecha_nacimiento.dia, clientes[x].fecha_nacimiento.mes, clientes[x].fecha_nacimiento.anio);
        printf(" - Peso: %.2f\n", clientes[x].peso);
        printf(" - Telefono: %s\n", clientes[x].telefono);
    }
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

void test8()
{
    Error *errores;
    Profesional profesionales[MAX_PROF];
    int cantidad, estado;

    if (leer_profesionales(profesionales, cantidad) != 2)
    {
        estado = crear_profesional(profesionales, cantidad, errores);
        printf("\nestado=%d\n\n", estado);

        if (estado != 0)
        {
            mostrar_errores(errores);
            printf("\n");
        }
    }
    else
        printf("Error al leer archivo\n");

    for (int x = 0; x < cantidad; x++)
    {
        printf("Profesional %d:\n", x);
        printf(" - ID: %d\n", profesionales[x].id_profesional);
        printf(" - DNI: %d\n", profesionales[x].dni);
        printf(" - Nombre: %s\n", profesionales[x].nombre);
        printf(" - Usuario: %s\n", profesionales[x].usuario);
        printf(" - Telefono: %s\n", profesionales[x].telefono);
    }
}

void test9()
{
    char cadena[] = "";
    int numero = -1;

    numero = atoi(cadena);

    printf("%d", numero);
}

void test10()
{
    Error *errores;
    Informe informes[MAX_INFORMES];
    int cantidad, estado;

    if (leer_informes(informes, cantidad) != 2)
    {
        estado = crear_informe(informes, cantidad, errores);
        printf("\nestado=%d\n\n", estado);

        if (estado != 0)
        {
            mostrar_errores(errores);
            printf("\n");
        }
    }
    else
        printf("Error al leer archivo\n");

    for (int x = 0; x < cantidad; x++)
    {
        printf("Profesional %d:\n", x);
        printf(" - ID del profesional: %d\n", informes[x].id_profesional);
        printf(" - DNI del cliente: %d\n", informes[x].dni_cliente);
        printf(" - Fecha: %d/%d/%d\n", informes[x].fecha.dia, informes[x].fecha.mes, informes[x].fecha.anio);
        printf(" - Informe: %s\n", informes[x].informe);
    }
}

void test11()
{
    const char cad1[] = "10", cad2[] = "11", cad3[] = "09";

    if (cad1 < cad2)
        printf("10 < 11\n");
    else
        printf("11 < 10\n"); // este
        
    if (cad2 < cad3)
        printf("11 < 9\n");
    else
        printf("9 < 11\n");  // este
        
    if (cad1 < cad3)
        printf("10 < 9\n");
    else
        printf("9 < 10\n");  // este

    if ('0' < '1')
        printf("0 < 1\n");   // este
    else
        printf("0 > 1\n");

    printf("%d\n", strcmp(cad1, cad2)); // -1
    printf("%d\n", strcmp(cad2, cad3)); //  1
    printf("%d\n", strcmp(cad1, cad3)); //  1
    printf("%d\n", strcmp(cad2, cad1)); //  1
    printf("%d\n", strcmp(cad3, cad2)); // -1
    printf("%d\n", strcmp(cad3, cad1)); // -1
}

void test12()
{
    Error *errores;
    Cliente turnos[MAX_TURNOS], clientes[MAX_CLIENTES];
    int cant_turnos, cant_clientes, estado;

    leer_clientes(clientes, cant_clientes);

    if (leer_turnos(turnos, cant_turnos) != 2)
    {
        estado = registrar_turno(clientes, cant_clientes, errores);
        printf("\nestado=%d\n\n", estado);

        if (estado != 0)
        {
            mostrar_errores(errores);
            printf("\n");
        }
    }
    else
        printf("Error al leer archivo\n");

    for (int x = 0; x < cant_turnos; x++)
    {
        printf("Turno %d:\n", x);
        printf(" - DNI del cliente: %d\n", turnos[x].dni);
        printf(" - Nombre del cliente: %s\n", turnos[x].nombre);
    }
}

void test13()
{
    Error *errores;
    Cliente turnos[MAX_TURNOS], clientes[MAX_CLIENTES];
    int cant_turnos, cant_clientes, estado;

    if (leer_turnos(turnos, cant_turnos) != 0)
        printf("Error al leer archivo\n");

    for (int x = 0; x < cant_turnos; x++)
    {
        printf("Turno %d:\n", x);
        printf(" - DNI del cliente: %d\n", turnos[x].dni);
        printf(" - Nombre del cliente: %s\n", turnos[x].nombre);
    }

    printf("\nBorrando turno\n\n");
    borrar_turno();

    if (leer_turnos(turnos, cant_turnos) != 0)
        printf("Error al leer archivo\n");

    for (int x = 0; x < cant_turnos; x++)
    {
        printf("Turno %d:\n", x);
        printf(" - DNI del cliente: %d\n", turnos[x].dni);
        printf(" - Nombre del cliente: %s\n", turnos[x].nombre);
    }
}


