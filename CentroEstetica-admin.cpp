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
        printf("ERROR FATAL:\n\n");
        error = obtener_error(errores);
        while (error.codigo != 0)
        {
            printf(" - %d: %s\n", error.codigo, error.descripcion);
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

    estado = leer_usuarios(usuarios, cantidad);
    if (estado != 0)
    {
        if (estado == 1)
        {
            printf("No se encontraron usuarios administradores en el archivo \"usuarios.dat\", desea crear uno? [s/n] ");
            opcion = getchar();

            if (opcion == 's' || opcion == 'S')
            {
                estado = crear_usuario(usuarios, cantidad, errores_creacion);
                if (estado != 0)
                {
                    if (estado == 1)
                    {
                        error = obtener_error() //TERMINAR
                    }
                }
            }
        }
        else
        {
            insertar_error(errores, 300);
            return;
        }
    }

    inicio_de_sesion(sesion.usuario, COD_ADMIN, usuarios, cantidad);
}