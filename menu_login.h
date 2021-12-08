#ifndef H_MENU_LOGIN
#define H_MENU_LOGIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char MENU1[] = "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA                         %s%s                         %s\xBA\n\xBA                                                  \xBA\n\xBA   %s Usuario: %s                                    %s\xBA\n\xBA   %s Contrase\xA4 \ba: %s                                 %s\xBA\n\xBA                               NX para siguiente  \xBA\n\xBA                               OK para terminar   \xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n> ";
const char MENU2[] = "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA                         %s%s                         %s\xBA\n\xBA                                                  \xBA\n\xBA   %s Usuario: %s                                    %s\xBA\n\xBA   %s Contrase\xA4 \ba: %s                                 %s\xBA\n\xBA   %s Tipo (ADMIN, PROF, ASIST): %s               %s\xBA\n\xBA                               NX para siguiente  \xBA\n\xBA                               OK para terminar   \xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n> ";

struct Menu
{
    char formato[1000];
    char titulo[20] = "",       b01[18] = "", b02[18] = "";
    char usuario[11] = "",      b1[36] = "";
    char contrasena[33] = "",   b2[36] = "";
    char tipo[10] = "",         b3[10] = "";
};

Menu menu; // Variable global de MENU

void reestablecer_menu()
{
    strcpy(menu.titulo, "");
    strcpy(menu.b01, "");
    strcpy(menu.b02, "");
    strcpy(menu.usuario, "");
    strcpy(menu.b1, "");
    strcpy(menu.contrasena, "");
    strcpy(menu.b2, "");
}

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
    char m_inicio[1000];
    strcpy(m_inicio, menu.formato);
    if (seleccion == 2)
        printf(m_inicio, menu.b01, menu.titulo, menu.b02, "\xAF", menu.usuario, menu.b1, "\x20", menu.contrasena, menu.b2);
    else if (seleccion == 3)
        printf(m_inicio, menu.b01, menu.titulo, menu.b02, "\x20", menu.usuario, menu.b1, "\xAF", menu.contrasena, menu.b2);
    else if (seleccion == 4)
        printf(m_inicio, menu.b01, menu.titulo, menu.b02, "\x20", menu.usuario, menu.b1, "\x20", menu.contrasena, menu.b2, "\xAF", menu.tipo, menu.b3);
    
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

    if (seleccion == 0)
    {
        strcpy(menu.formato, dato);
    }
    else if (seleccion == 1)
    {
        strcpy(menu.titulo, dato);
        for (int x = 0; x < ((strlen(dato)/2)+(strlen(dato)%2)) && x < 18; x++)
        {
            menu.b01[pos] = '\b';
            menu.b02[pos++] = '\b';
            if (x == (strlen(dato)/2)+(strlen(dato)%2)-1 && strlen(dato)%2 != 0)
                menu.b02[pos-1] = '\0';
        }
    }
    else if (seleccion == 2)
    {
        strcpy(menu.usuario, dato);
        for (int x = 0; x < strlen(dato) && x < 36; x++)
            b[pos++] = '\b';
        strcpy(menu.b1, b);
    }
    else if (seleccion == 3)
    {
        strcpy(menu.contrasena, dato);
        strcpy(menu.b2, "");
        for (int x = 0; x < strlen(dato) && x < 36; x++)
            b[pos++] = '\b';
        strcpy(menu.b2, b);
    }
    else if (seleccion == 4)
    {
        strcpy(menu.tipo, dato);
        strcpy(menu.b3, "");
        for (int x = 0; x < strlen(dato) && x < 10; x++)
            b[pos++] = '\b';
        strcpy(menu.b3, b);
    }
}

/*

    B10   Hex
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
\n\xBA                         %s%s                         %s\xBA
\n\xBA                                                  \xBA
\n\xBA   %s Usuario: %s                                    %s\xBA
\n\xBA   %s Contrase\xA4 \ba: %s                                 %s\xBA
\n\xBA                               NX para siguiente  \xBA
\n\xBA                               OK para terminar   \xBA
\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC
\n
\n> 

\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB
\n\xBA                         %s%s                         %s\xBA
\n\xBA                                                  \xBA
\n\xBA   %s Usuario: %s                                    %s\xBA
\n\xBA   %s Contrase\xA4 \ba: %s                                 %s\xBA
\n\xBA   %s Tipo (ADMIN, PROF, ASIST): %s               %s\xBA
\n\xBA                               NX para siguiente  \xBA
\n\xBA                               OK para terminar   \xBA
\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC
\n
\n> 

*/

#endif