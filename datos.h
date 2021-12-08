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
    int estado = -1;

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
            estado = 0;
        else
            estado = 1;
    }
    else
        estado = 2;

    fclose(archivo);

    return estado; 
}

int escribir_usuario(Usuario usuario)
{
    /**
     * INT DE RETORNO
     *  0 - Escritura correcta (se escribio el usuario)
     *  1 - Escritura incorrecta (no se pudo escribir en el archivo)
     *  2 - Escritura incorrecta (no se pudo abrir el archivo)
     */

    int estado = -1;

    FILE *archivo = fopen(USUARIOS_DAT, "ab");

    if (archivo != NULL)
    {
        if (fwrite(&usuario, sizeof(Usuario), 1, archivo) != 0)
            estado = 0;
        else
            estado = 1;
    }
    else
        estado = 2;

    fclose(archivo);

    return estado;
}

#endif