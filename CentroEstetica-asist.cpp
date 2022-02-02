#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structs.h"
#include "usuarios.h"

void centro_estetica_asist(Error *&errores);
void dar_alta();
void registrar_turno();
void obtener_informe();

int main()
{
    Error *errores, error;

    // Funcion principal
    centro_estetica_asist(errores);

    // Mostrar errores en pantalla
    if (errores != NULL)
    {
        system("cls");
        printf("\n\tERROR FATAL - El programa no puede continuar ejecutandose:\n");
        error = obtener_error(errores);
        while (error.codigo != 0)
        {
            printf("\t - %d: %s\n", error.codigo, error.descripcion);
            error = obtener_error(errores);
        }

        return 1;
    }

    return 0;
}

// FUNCION PRINCIPAL
void centro_estetica_asist(Error *&errores)
{
    /**
     * Funcion principal del programa CentroEstetica-asist.cpp
     * Se encarga de todo lo relacionado a esta sección del programa y retorna una pila de errores fatales
     * de los cuales el programa no se puede recuperar por si solo.
     * 
     */

    Menu menu;
    Sesion sesion;
    Fecha hoy = obtener_fecha_actual();

    Usuario usuarios[MAX_USUARIOS];
    Cliente clientes[MAX_CLIENTES];
    int cant_usuarios, cant_clientes;

    int contador = 0;

    errores = NULL;
    Error *errores_creacion = NULL;
    bool ejecutar = true;
    int estado, opcion;

    // Verificar si existen usuarios
    while (true)
    {
        // Leer usuarios de usuarios.dat
        estado = leer_usuarios(usuarios, cant_usuarios);

        if (estado != 0)
        {
            // Si usuarios.dat esta vacio, terminar programa
            if (estado == 1)
                insertar_error(errores, C_INICIO_NO_USUARIOS);
            else
                insertar_error(errores, C_INICIO_NO_ARCHIVO);

            return;
        }
        else
            break;
    }

    // Iniciar sesion
    while (true)
    {
        estado = inicio_de_sesion(sesion.usuario, COD_ASIST, usuarios, cant_usuarios, errores);

        if (estado != 0)
        {
            printf("\nError durante el inicio de sesion:\n");
            mostrar_errores(errores);
            printf("\n");
            system("pause");
        }
        else
            break;
    }

    // Mostrar menu
    modificar_dato(menu, "largo", "11");
    modificar_dato(menu, "ancho", "65");
    modificar_dato(menu, "margen", "4");

    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Recepcion");

    modificar_dato(menu, "opcion", "1-1 - Dar de alta a un cliente");
    modificar_dato(menu, "opcion", "2-2 - Registrar un turno");
    modificar_dato(menu, "opcion", "3-3 - Obtener informe");
    modificar_dato(menu, "opcion", "4-");
    modificar_dato(menu, "opcion", "5-0 - Salir");

    modificar_dato(menu, "seleccion", "0");

    modificar_dato(menu, "control", "Seleccione un numero");

    while (ejecutar)
    {
        mostrar_menu(menu);
        printf("\n\n> ");
        scanf("%d", &opcion);

        printf("\n");

        switch (opcion)
        {
        case 1: // Dar de alta un cliente
            dar_alta();
            break;

        case 2: // Registrar un turno
            registrar_turno();
            break;

        case 3: // Obtener informe
            obtener_informe();
            break;

        case 0:
            printf("Programa terminado\n");
            ejecutar = false;
            break;
        
        default:
            break;
        }

        printf("\n");
        system("pause");
    }
}

void dar_alta()
{
    Cliente clientes[MAX_CLIENTES];
    int cantidad;
    Error *errores;

    int estado;
    int opcion, ejecutar = true;

    estado = leer_clientes(clientes, cantidad);

    if (estado != 2)
    {
        while (ejecutar)
        {
            estado = crear_cliente(clientes, cantidad, errores);

            if (estado != 0)
            {
                mostrar_errores(errores);
                printf("\n");
                printf("Desea intentar de nuevo? [s/n] ");
                _flushall();
                opcion = getchar();

                if (opcion != 's' && opcion != 'S')
                    ejecutar = false;
            }
            else 
                break;
        }
    }
}

void registrar_turno()
{

}

void obtener_informe()
{

}