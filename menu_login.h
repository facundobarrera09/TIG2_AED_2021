#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Menu
{
    char usuario[11] = "", b1[36] = "";
    char contrasena[33] = "", b2[36] = "";
};

Menu menu; // Variable global de MENU

void mostrar_menu(int seleccion)
{
    /**
     * Muestra el menu de inicio de sesion
     * 
     * seleccion: variable que identifica que miembro se quiere modificar
     *
     * printf(m_inicio, "\xAF",     "USUARIO",          "\b",                   "\x20", "CONTRASEÑA", "\b");
     *                  flecha                          borrado de espacios      IDEM
     *                              texto de usuario
     */
    const char m_inicio[] = "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA                Inicio de Sesion                  \xBA\n\xBA                                                  \xBA\n\xBA   %s Usuario: %s                                    %s\xBA\n\xBA   %s Contrase\xA4 \ba: %s                                 %s\xBA\n\xBA                               NX para siguiente  \xBA\n\xBA                               OK para terminar   \xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n> ";
    
    if (seleccion == 1)
        printf(m_inicio, "\xAF", menu.usuario, menu.b1, "\x20", menu.contrasena, menu.b2);
    else
        printf(m_inicio, "\x20", menu.usuario, menu.b1, "\xAF", menu.contrasena, menu.b2);
}

void actualizar_menu(int seleccion, const char dato[])
{
    /**
     * Actualiza los valores en MENU para su uso durante la ejecucion de mostrar_menu()
     * 
     * seleccion: variable que identifica que miembro se quiere modificar
     * 
     */
    
    int pos = 0;
    char b[36] = "";

    if (seleccion == 1)
    {
        strcpy(menu.usuario, dato);
        for (int x = 0; x < strlen(dato) && x < 36; x++)
            b[pos++] = '\b';
        strcpy(menu.b1, b);
    }
    else if (seleccion == 2)
    {
        strcpy(menu.contrasena, dato);
        strcpy(menu.b2, "");
        for (int x = 0; x < strlen(dato) && x < 36; x++)
            b[pos++] = '\b';
        strcpy(menu.b2, b);
    }
}

/*
  : 32  , 20
ñ : 164 , A4
» : 175 , AF
║ : 186 , BA
╗ : 187 , BB
╝ : 188 , BC
╚ : 200 , C8
╔ : 201 , C9
═ : 205 , CD


\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB
\n\xBA                Inicio de Sesion                  \xBA
\n\xBA                                                  \xBA
\n\xBA   %s Usuario: %s                                    %s\xBA
\n\xBA   %s Contrase\xA4 \ba: %s                                 %s\xBA
\n\xBA                               NX para siguiente  \xBA
\n\xBA                               OK para terminar   \xBA
\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC
\n
\n> 

*/