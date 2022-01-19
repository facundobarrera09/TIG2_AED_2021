#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "structs.h"
#include "usuarios.h"

void centro_estetica_admin(Error *&errores);
void listar_atenciones();

int main()
{
    Error *errores, error;

    // Funcion principal
    centro_estetica_admin(errores);

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
void centro_estetica_admin(Error *&errores)
{
    /**
     * Funcion principal del programa CentroEstetica-admin.cpp
     * Se encarga de todo lo relacionado a esta sección del programa y retorna una pila de errores fatales
     * de los cuales el programa no se puede recuperar por si solo.
     * 
     */

    Menu menu;
    Sesion sesion;
    Fecha hoy = obtener_fecha_actual();

    Usuario usuarios[MAX_USUARIOS];
    int cant_usuarios;

    int contador = 0;

    errores = NULL;
    Error *errores_creacion;
    bool ejecutar = true;
    int estado, opcion;

    // Verificar si existen usuarios
    while (true)
    {
        // Leer usuarios de usuarios.dat
        estado = leer_usuarios(usuarios, cant_usuarios);

        if (estado != 0)
        {
            // Si usuarios.dat esta vacio, solicitar crear usuario
            if (estado == 1)
            {
                system("cls");
                printf("\nNo se encontraron usuarios administradores en el archivo \"usuarios.dat\", desea crear uno? [s/n] ");
                _flushall();
                opcion = getchar();

                // Crear usuario
                if (opcion == 's' || opcion == 'S')
                {
                    for (int x = 0; x < 3; x++)
                    {
                        estado = crear_usuario(usuarios, cant_usuarios, COD_ADMIN, errores_creacion);
                        if (estado != 0)
                        {
                            printf("Error durante la creacion de usuario. ESTADO=%d\n", estado);
                            if (estado == 1)
                            {
                                mostrar_errores(errores_creacion);
                                x--;
                            }
                            system("pause");
                        }
                        else
                        {
                            printf("Usuario creado con exito\n");
                            system("pause");
                            break;
                        }
                    }
                }
                else if (opcion == 'n' || opcion == 'N')
                {
                    insertar_error(errores, C_INICIO_NO_USUARIOS);
                    return;
                }
            }
            else
            {
                insertar_error(errores, C_INICIO_NO_ARCHIVO);
                return;
            }
        }
        else
            break;
    }

    // Iniciar sesion
    while (true)
    {
        estado = inicio_de_sesion(sesion.usuario, COD_ADMIN, usuarios, cant_usuarios, errores);

        if (estado != 0)
        {
            printf("INICIO DE SESION:\n");
            mostrar_errores(errores);
            system("pause");
        }
        else
            break;
    }

    // Mostrar menu
    modificar_dato(menu, "largo", "11");
    modificar_dato(menu, "ancho", "65");
    modificar_dato(menu, "margen", "2");

    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Administracion");

    modificar_dato(menu, "opcion", "1-1 - Crear usuario");
    modificar_dato(menu, "opcion", "2-2 - Visualizar atenciones por profesional");
    modificar_dato(menu, "opcion", "3-3 - Visualizar ranking de profesionales");
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
        case 1: // Crear usuario
            while (true)
            {
                if (errores_creacion != NULL) eliminar_errores(errores_creacion);
                estado = crear_usuario(usuarios, cant_usuarios, errores_creacion);

                if (estado != 0)
                {
                    mostrar_errores(errores_creacion);
                    system("pause");
                }
                else
                    break;
                
                mostrar_menu(menu);
                printf("\nUsuario creado con exito\n");
            }
            break;

        case 2: // Visualizar atenciones por profesional
            listar_atenciones();
            break;

        case 3: // Visualizar ranking
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

// Funciones de menu
void listar_atenciones()
{
    Profesional profesionales[MAX_PROF];
    Informe informes[MAX_INFORMES];
    int cant_prof, cant_informes, contador;

    Menu menu;
    Fecha hoy = obtener_fecha_actual();
    char buffer[100];

    modificar_dato(menu, "largo", "10");
    modificar_dato(menu, "ancho", "65");
    modificar_dato(menu, "margen", "2");
    
    modificar_dato(menu, "titulo", "Listado de atenciones de profesionales");

    if (leer_profesionales(profesionales, cant_prof) == 0)
    {
        if (leer_informes(informes, cant_informes) == 0)
        {
            for (int x = 0; x < cant_prof; x++)
            {
                contador = 0;
                for (int y = 0; y < cant_informes; y++)
                {
                    if (informes[y].id_profesional == profesionales[x].id_profesional)
                        if (informes[y].fecha.mes == hoy.mes && informes[y].fecha.anio == hoy.anio)
                            contador++;
                }

                itoa(x, buffer, sizeof(buffer));
                strcat(buffer, "-");
                strcat(buffer, profesionales[x].nombre);
                modificar_dato(menu, "opcion", buffer);

                strcpy(buffer, "");
                itoa(x, buffer, sizeof(buffer));
                strcat(buffer, "-");
                if (x < 10)
                    itoa(contador, &buffer[2], sizeof(buffer-2));
                else
                    itoa(contador, &buffer[3], sizeof(buffer-2));
                modificar_dato(menu, "valor", buffer);
            }
        }
        else
            modificar_dato(menu, "opcion", "0-No se encontraron informes registrados");
    }
    else
        modificar_dato(menu, "opcion", "0-No se encontraron profesionales registrados");

    mostrar_menu(menu);
}
