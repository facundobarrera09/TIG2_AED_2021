#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "usuarios.h"

void centro_estetica_admin(Error *&errores);

int main()
{
    Error *errores, error;
    centro_estetica_admin(errores);

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

void centro_estetica_admin(Error *&errores)
{
    Sesion sesion;
    Usuario usuarios[MAX_USUARIOS];
    int cantidad;

    int estado, opcion;
    errores = NULL;
    Error *errores_creacion, error;

    // Verificar si existen usuarios
    while (true)
    {
        // Leer usuarios de usuarios.dat
        estado = leer_usuarios(usuarios, cantidad);

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
                        estado = crear_usuario(usuarios, cantidad, errores_creacion);
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
        estado = inicio_de_sesion(sesion.usuario, COD_ADMIN, usuarios, cantidad);
    }
}