#ifndef H_DATOS
#define H_DATOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

int leer_usuarios(Usuario usuarios[MAX_USUARIOS], int &cantidad)
{
    /**
     * INT DE RETORNO
     *  0 - Lectura correcta (existen usuarios)
     *  1 - Lectura incorrecta (no existen usuarios)
     *  2 - Lectura incorrecta (no se pudo abrir el archivo)
     */

    cantidad = 0;
    Usuario usuario;
    FILE *archivo = fopen(USUARIOS_DAT, "rb");

    if (archivo != NULL)
    {
        for (int x = 0; x < MAX_USUARIOS; x++)
        {
            if (fread(&usuario, sizeof(Usuario), 1, archivo) != 0)
            {
                usuarios[x] = usuario;
                cantidad++;
            }
        }

        if (cantidad != 0)
            return 0;
        else
            return 1;
    }
    else
        return 2; 
}

#endif