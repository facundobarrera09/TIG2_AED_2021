#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structs.h"
#include "usuarios.h"

void centro_estetica_asist(Error *&errores);
void dar_alta();
void registrar_turno_de_cliente();
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
        estado = crear_sesion(sesion, COD_ASIST, usuarios, cant_usuarios, errores);

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
        printf("\n> ");
        scanf("%d", &opcion);

        printf("\n");

        switch (opcion)
        {
        case 1: // Dar de alta un cliente
            dar_alta();
            break;

        case 2: // Registrar un turno
            registrar_turno_de_cliente();
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

void registrar_turno_de_cliente()
{
    Cliente clientes[MAX_CLIENTES];
    int cantidad;
    Error *errores;

    if (leer_clientes(clientes, cantidad) == 0)
        if (registrar_turno(clientes, cantidad, errores) != 0)
        {
            printf("\n");
            mostrar_errores(errores);
        }
        else;
    else
        printf("Error leyendo clientes\n");
}

void obtener_informe()
{
    Menu menu, listado, informe_encontrado;

    Informe informes[MAX_INFORMES];
    Profesional profesionales[MAX_PROF];
    Cliente clientes[MAX_CLIENTES];
    int cant_informes, cant_prof, cant_clientes;

    int dni_cliente, id_prof;
    Fecha fecha_informe;
    Informe informe;
    
    int seleccion = 0;
    char entrada[50] = "", buffer[55] = "";
    bool ejecutar = true, encontrado = false;

    modificar_dato(menu, "largo", "11");
    modificar_dato(menu, "ancho", "65");
    modificar_dato(menu, "margen", "4");

    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Busqueda de informes");

    modificar_dato(menu, "opcion", "0-DNI del cliente");
    modificar_dato(menu, "opcion", "1-ID del profesional");
    modificar_dato(menu, "opcion", "2-Fecha de emision de informe");
    modificar_dato(menu, "valor", "0-");
    modificar_dato(menu, "valor", "1-");
    modificar_dato(menu, "valor", "2-");
    modificar_dato(menu, "seleccion", "0");

    modificar_dato(menu, "control", "LS para listar prof.");
    modificar_dato(menu, "control", "AN para anterior    ");
    modificar_dato(menu, "control", "OK para terminar    ");

    // Leer archivos e informar si hay errores
    if (leer_informes(informes, cant_informes) == 0 && leer_profesionales(profesionales, cant_prof) == 0 && leer_clientes(clientes, cant_clientes) == 0)
    {
        // Llenar listado de profesionales
        itoa(cant_prof+5, buffer, 10);
        modificar_dato(listado, "largo", buffer);
        modificar_dato(listado, "ancho", "65");
        modificar_dato(listado, "margen", "4");
        modificar_dato(listado, "titulo", "Listado de profesionales");
        for (int x = 0; x < cant_prof; x++)
        {
            strcpy(buffer, "");
            itoa(x, buffer, 10);
            strcat(buffer, "-");
            if (cant_prof > 9)
                itoa(profesionales[x].id_profesional, &buffer[3], 10);
            else
                itoa(profesionales[x].id_profesional, &buffer[2], 10);
            strcat(buffer, " - ");
            strcat(buffer, profesionales[x].nombre);

            modificar_dato(listado, "opcion", buffer);
        }
        modificar_dato(listado, "control", "Cualquier tecla para continuar");

        // Mostrar menu y pedir ingreso de datos
        while (ejecutar)
        {
            mostrar_menu(menu);
            printf("\n> ");
            scanf("%s", entrada);

            if (strcmp(entrada, "LS") == 0)
            {
                mostrar_menu(listado);
                system("pause > nul");
            }
            else if (strcmp(entrada, "AN") == 0)         // Opcion anterior
            {
                if (seleccion == 0) seleccion = 2;
                else seleccion--;

                itoa(seleccion, buffer, 10);
                modificar_dato(menu, "seleccion", buffer);
            }
            else if (strcmp(entrada, "OK") == 0)    // Confirmar y terminar
            {
                obtener_cadena(menu.valores, 0, buffer);
                dni_cliente = atoi(buffer);
                obtener_cadena(menu.valores, 1, buffer);
                id_prof = atoi(buffer);
                obtener_cadena(menu.valores, 2, buffer);
                fecha_informe = obtener_fecha(buffer);

                ejecutar = false;
            }
            else
            {
                strcpy(buffer, "");
                itoa(seleccion, buffer, 10);
                strcat(buffer, "-");
                strcat(buffer, entrada);
                modificar_dato(menu, "valor", buffer);
                
                if (seleccion == 2) seleccion = 0;
                else seleccion++;

                itoa(seleccion, buffer, 10);
                modificar_dato(menu, "seleccion", buffer);
            }
        }
    
        // Buscar informe
        for (int x = 0; x < cant_informes; x++)
        {
            if (informes[x].dni_cliente == dni_cliente && informes[x].id_profesional == id_prof)
                if (informes[x].fecha.anio == fecha_informe.anio)
                    if (informes[x].fecha.mes == fecha_informe.mes)
                        if (informes[x].fecha.dia == fecha_informe.dia)
                        {
                            informe = informes[x];
                            encontrado = true;
                            break;
                        }
        }

        // Mostrar resultado de busqueda
        modificar_dato(informe_encontrado, "largo", "12");
        modificar_dato(informe_encontrado, "ancho", "65");
        modificar_dato(informe_encontrado, "margen", "4");
        modificar_dato(informe_encontrado, "titulo", "Centro de Estetica");
        modificar_dato(informe_encontrado, "titulo", "Resultado de busqueda");

        if (encontrado)
        {
            modificar_dato(informe_encontrado, "opcion", "0-ID del profesional");
            modificar_dato(informe_encontrado, "opcion", "1-DNI del cliente");
            modificar_dato(informe_encontrado, "opcion", "2-Fecha");
            modificar_dato(informe_encontrado, "opcion", "3-Informe");
            
            strcpy(buffer, "0-");
            itoa(informe.id_profesional, &buffer[2], 10);
            modificar_dato(informe_encontrado, "valor", buffer);
            
            strcpy(buffer, "1-");
            itoa(informe.dni_cliente, &buffer[2], 10);
            modificar_dato(informe_encontrado, "valor", buffer);
            
            strcpy(buffer, "2-");
            fecha_a_cadena(informe.fecha, &buffer[2]);
            modificar_dato(informe_encontrado, "valor", buffer);
            
            strcpy(buffer, "3-");
            strcat(buffer, informe.informe);
            modificar_dato(informe_encontrado, "valor", buffer);
        }
        else
        {
            modificar_dato(informe_encontrado, "opcion", "0-No se encontro el informe");
        }

        mostrar_menu(informe_encontrado);
    }
    else
        printf("No existen informes, profesionales o clientes registrados\n");
}