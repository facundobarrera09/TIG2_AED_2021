#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "datos.h"
#include "menu.h"
#include "error.h"

int buscar_usuario(Usuario usuario, Usuario usuarios[MAX_USUARIOS], int cantidad);
int cantidad_mayusculas(const char cadena[]);
int cantidad_digitos(const char cadena[]);
bool contiene_caracteres_necesarios(const char cadena[]);
bool contiene_caracteres_invalidos(const char cadena[]);
int digitos_consecutivos(const char cadena[]);
int caracteres_consecutivos(const char cadena[]);
bool es_dni_unico(Cliente clientes[MAX_CLIENTES], int cantidad, int dni);

// FUNCIONES PRINCIPALES
int crear_cliente(Cliente clientes[MAX_CLIENTES], int &cantidad, Error *errores)
{
    /**
     * INT DE RETORNO
     * 
     * 0 - Cliente creado y almacenado con exito
     * 1 - Se ingresaron datos invalidos
     * 2 - No hay mas espacio
     * 3 - Error al escribir el cliente
     * 
     */

    Menu menu;
    Cliente cliente;
    int seleccion = 0;
    errores = NULL;

    bool ejecutar = true;
    char entrada[36], buffer[100];

    // Establecer configuracion de la ventana
    modificar_dato(menu, "largo", "12");
    modificar_dato(menu, "ancho", "52");
    modificar_dato(menu, "margen", "2");
    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Cargar datos del cliente");

    modificar_dato(menu, "opcion", "0-DNI");
    modificar_dato(menu, "opcion", "1-Nombre completo");
    modificar_dato(menu, "opcion", "2-Domicilio");
    modificar_dato(menu, "opcion", "3-Localidad");
    modificar_dato(menu, "opcion", "4-Fecha de nacimiento");
    modificar_dato(menu, "opcion", "5-Peso");
    modificar_dato(menu, "opcion", "6-Telefono");
    modificar_dato(menu, "valor", "0-");
    modificar_dato(menu, "valor", "1-");
    modificar_dato(menu, "valor", "2-");
    modificar_dato(menu, "valor", "3-");
    modificar_dato(menu, "valor", "4-");
    modificar_dato(menu, "valor", "5-");
    modificar_dato(menu, "valor", "6-");

    modificar_dato(menu, "seleccion", "0");

    modificar_dato(menu, "control", "NX para siguiente");
    modificar_dato(menu, "control", "OK para terminar ");

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        mostrar_menu(menu);
        printf("\n> ");
        _flushall();
        gets(entrada);

        if (strcmp(entrada, "NX") == 0)         // Siguiente opcion
        {
            if (seleccion == 6) seleccion = 0;
            else seleccion++;

            itoa(seleccion, buffer, sizeof(buffer));
            modificar_dato(menu, "seleccion", buffer);
        }
        else if (strcmp(entrada, "OK") == 0)    // Confirmar y terminar
        {
            obtener_cadena(menu.valores, 0, buffer);
            cliente.dni = atoi(buffer);
            obtener_cadena(menu.valores, 1, buffer);
            strcpy(cliente.nombre, buffer);
            obtener_cadena(menu.valores, 2, buffer);
            strcpy(cliente.domicilio, buffer);
            obtener_cadena(menu.valores, 3, buffer);
            strcpy(cliente.localidad, buffer);
            obtener_cadena(menu.valores, 4, buffer);
            cliente.fecha_nacimiento = obtener_fecha(buffer);
            obtener_cadena(menu.valores, 5, buffer);
            cliente.peso = atof(buffer);
            obtener_cadena(menu.valores, 6, buffer);
            strcpy(cliente.telefono, buffer);

            ejecutar = false;
        }
        else
        {
            strcpy(buffer, "");
            itoa(seleccion, buffer, sizeof(buffer));
            strcat(buffer, "-");
            strcat(buffer, entrada);
            modificar_dato(menu, "valor", buffer);
        }
    }

    // Validar los datos
    if (cliente.dni == 0)
        insertar_error(errores, C_CLIENTE_DNI_VACIO);
    if (strcmp(cliente.nombre, "") == 0)
        insertar_error(errores, C_CLIENTE_NOMBRE_VACIO);
    if (!es_dni_unico(clientes, cantidad, cliente.dni))
        insertar_error(errores, C_CLIENTE_EXISTE);
    
    if (errores != NULL)
        return 1;

    // Añadir cliente a arreglo
        // Verificar si hay espacio
    if (cantidad+1 == MAX_CLIENTES)
        return 2;

        // Añadir cliente a arreglo
    cantidad++;
    clientes[cantidad] = cliente;
    
        // Escribir usuario en archivo
    if (escribir_cliente(cliente) != 0)
    {
        memset(&clientes[cantidad--], '\0', sizeof(Cliente));
        return 3;
    }

    return 0;
}

int crear_profesional(Profesional profesionales[MAX_PROF], int &cantidad, Error *errores)
{
    Menu menu;
    Profesional prof;
    int seleccion = 0;
    errores = NULL;

    bool ejecutar = true;
    char entrada[36], buffer[100];

    // Establecer configuracion de la ventana
    modificar_dato(menu, "largo", "12");
    modificar_dato(menu, "ancho", "52");
    modificar_dato(menu, "margen", "2");
    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Cargar datos del cliente");

    modificar_dato(menu, "opcion", "0-Usuario");
    modificar_dato(menu, "opcion", "1-Nombre completo");
    modificar_dato(menu, "opcion", "2-Id del profesional");
    modificar_dato(menu, "opcion", "3-DNI");
    modificar_dato(menu, "opcion", "4-Telefono");
    modificar_dato(menu, "valor", "0-");
    modificar_dato(menu, "valor", "1-");
    modificar_dato(menu, "valor", "2-");
    modificar_dato(menu, "valor", "3-");
    modificar_dato(menu, "valor", "4-");

    modificar_dato(menu, "seleccion", "0");

    modificar_dato(menu, "control", "NX para siguiente");
    modificar_dato(menu, "control", "OK para terminar ");

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        mostrar_menu(menu);
        printf("\n> ");
        _flushall();
        gets(entrada);

        if (strcmp(entrada, "NX") == 0)         // Siguiente opcion
        {
            if (seleccion == 4) seleccion = 0;
            else seleccion++;

            itoa(seleccion, buffer, sizeof(buffer));
            modificar_dato(menu, "seleccion", buffer);
        }
        else if (strcmp(entrada, "OK") == 0)    // Confirmar y terminar
        {
            obtener_cadena(menu.valores, 0, buffer);
            strcpy(prof.usuario, buffer);
            obtener_cadena(menu.valores, 1, buffer);
            strcpy(prof.nombre, buffer);
            obtener_cadena(menu.valores, 2, buffer);
            prof.id_profesional = atoi(buffer);
            obtener_cadena(menu.valores, 3, buffer);
            prof.dni = atoi(buffer);
            obtener_cadena(menu.valores, 4, buffer);
            strcpy(prof.telefono, buffer);

            ejecutar = false;
        }
        else
        {
            strcpy(buffer, "");
            itoa(seleccion, buffer, sizeof(buffer));
            strcat(buffer, "-");
            strcat(buffer, entrada);
            modificar_dato(menu, "valor", buffer);
        }
    }

}

int inicio_de_sesion(Usuario &usuario_buf, int tipo, Usuario usuarios[MAX_USUARIOS], int cantidad, Error *&errores)
{
    /**
     * INT DE RETORNO:
     * 
     * 0 - Se inicio sesion correctamente y se devolvió usuario
     * 1 - No existe el usuario
     * 2 - El usuario ingresado no coincide con el tipo
     * 3 - No coincide la contraseña
     * 4 - Usuarios esta vacio
     * 
     */
    Menu menu;
    Usuario usuario;
    int seleccion = 0;
    int estado_de_usuario;
    errores = NULL;

    bool ejecutar = true;
    char entrada[36], buffer[100];
    
    usuario.tipo = tipo;

    // Establecer configuracion de la ventana
    modificar_dato(menu, "largo", "8");
    modificar_dato(menu, "ancho", "52");
    modificar_dato(menu, "margen", "2");
    modificar_dato(menu, "titulo", "Inicio de sesion");

    modificar_dato(menu, "opcion", "0-Usuario");
    modificar_dato(menu, "opcion", "1-Contrasena");
    modificar_dato(menu, "valor", "0- ");
    modificar_dato(menu, "valor", "1- ");

    modificar_dato(menu, "seleccion", "0");

    modificar_dato(menu, "control", "NX para siguiente");
    modificar_dato(menu, "control", "OK para terminar ");

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        mostrar_menu(menu);
        printf("\n> ");
        scanf("%s", entrada);

        if (strcmp(entrada, "NX") == 0)         // Siguiente opcion
        {
            if (seleccion == 0) seleccion = 1;
            else seleccion = 0;

            itoa(seleccion, buffer, sizeof(buffer));
            modificar_dato(menu, "seleccion", buffer);
        }
        else if (strcmp(entrada, "OK") == 0)    // Confirmar y terminar
        {
            obtener_cadena(menu.valores, 0, buffer);
            strcpy(usuario.usuario, buffer);
            obtener_cadena(menu.valores, 1, buffer);
            strcpy(usuario.contrasena, buffer);

            ejecutar = false;
        }
        else
        {
            strcpy(buffer, "");
            itoa(seleccion, buffer, sizeof(seleccion));
            strcat(buffer, "-");
            strcat(buffer, entrada);
            modificar_dato(menu, "valor", buffer);
        }
    }

    // Verificar que los datos sean correctos
    if (strcmp(usuario.usuario, "") == 0 || strcmp(usuario.contrasena, "") == 0)
    {
        insertar_error(errores, C_CREACION_VACIO);    
        return 1;
    }

    // Verificar que el usuario exista

    estado_de_usuario = buscar_usuario(usuario, usuarios, cantidad);
    
    switch (estado_de_usuario)
    {
    case 0:
        usuario_buf = usuario;
        return 0;
    case 1:
        insertar_error(errores, C_INICIO_NO_COINCIDE_CONTRASENA);
        return 3;
    case 2:
        insertar_error(errores, C_INICIO_NO_COINCIDE_TIPO);
        return 2;
    case 3:
        insertar_error(errores, C_INICIO_NO_EXISTE_USUARIO);
        return 1;
    case 4:
        insertar_error(errores, C_INICIO_NO_USUARIOS);
        return 4;
    }

    return -1;
}

int crear_usuario(Usuario usuarios[MAX_USUARIOS], int &cantidad, int tipo, Error *&errores)
{
    /**
     * INT DE RETORNO
     * 
     * 0 - Usuario creado y almacenado con exito
     * 1 - Se ingresaron datos invalidos
     * 2 - No hay mas espacio
     * 3 - Error al escribir el usuario
     * 
     */

    Menu menu;
    Usuario usuario;
    int seleccion = 0;
    errores = NULL;

    bool ejecutar = true;
    char entrada[36], buffer[100];

    // Establecer configuracion de la ventana
    modificar_dato(menu, "largo", "9");
    modificar_dato(menu, "ancho", "52");
    modificar_dato(menu, "margen", "2");
    modificar_dato(menu, "titulo", "Creacion de usuario");

    modificar_dato(menu, "opcion", "0-Usuario");
    modificar_dato(menu, "opcion", "1-Contrasena");
    modificar_dato(menu, "opcion", "2-Tipo (ADMIN, PROF, ASIST)");
    modificar_dato(menu, "valor", "0- ");
    modificar_dato(menu, "valor", "1- ");
    modificar_dato(menu, "valor", "2- ");

    modificar_dato(menu, "seleccion", "0");

    modificar_dato(menu, "control", "NX para siguiente");
    modificar_dato(menu, "control", "OK para terminar ");

    if (tipo != 0)
    {
        usuario.tipo = tipo;
        if (tipo == COD_ADMIN)
            modificar_dato(menu, "valor", "2-ADMIN");
        if (tipo == COD_PROF)
            modificar_dato(menu, "valor", "2-PROF");
        if (tipo == COD_ASIST)
            modificar_dato(menu, "valor", "2-ASIST");
    }

    // Pedir ingreso de datos
    while (ejecutar)
    {
        system("cls");
    
        mostrar_menu(menu);
        printf("\n> ");
        scanf("%s", entrada);

        if (strcmp(entrada, "NX") == 0)
        {
            if (tipo == 0)
            {
                if (seleccion < 2) seleccion++;
                else seleccion = 0;
            }
            else
            {
                if (seleccion < 1) seleccion++;
                else seleccion = 0;
            }

            itoa(seleccion, buffer, sizeof(buffer));
            modificar_dato(menu, "seleccion", buffer);
        }
        else if (strcmp(entrada, "OK") == 0)
        {
            obtener_cadena(menu.valores, 0, buffer);
            strcpy(usuario.usuario, buffer);

            obtener_cadena(menu.valores, 1, buffer);
            strcpy(usuario.contrasena, buffer);

            obtener_cadena(menu.valores, 2, buffer);
            if (strcmp(buffer, "ADMIN") == 0)
                usuario.tipo = COD_ADMIN;
            else if (strcmp(buffer, "PROF") == 0)
                usuario.tipo = COD_PROF;
            else if (strcmp(buffer, "ASIST") == 0)
                usuario.tipo = COD_ASIST;
            else
                usuario.tipo = 0;
            
            ejecutar = false;
        }
        else
        {
            strcpy(buffer, "");
            itoa(seleccion, buffer, sizeof(buffer));
            strcat(buffer, "-");
            strcat(buffer, entrada);
            modificar_dato(menu, "valor", buffer);
        }

        system("cls");
    }

    // Verificar que los datos sean correctos
        // Verificar que los datos no esten vacios
    if (strcmp(usuario.usuario, "") == 0 || strcmp(usuario.contrasena, "") == 0 || usuario.tipo == 0)
    {
        insertar_error(errores, C_CREACION_VACIO);
        return 1;
    }

        // Verificar de nombre de usuario
    if (strlen(usuario.usuario) < 6 || strlen(usuario.usuario) > 10)
        insertar_error(errores, C_USUARIO_TAMANO);
    if (usuario.usuario[0] < 97 || usuario.usuario[0] > 122)
        insertar_error(errores, C_USUARIO_NO_MINUS);
    if (cantidad_mayusculas(usuario.usuario) < 2)
        insertar_error(errores, C_USUARIO_NO_MAYUS);
    if (cantidad_digitos(usuario.usuario) > 3)
        insertar_error(errores, C_USUARIO_EXCESO_DIGITOS);

        // Verificar si el nombre de usuario existe
    int estado = buscar_usuario(usuario, usuarios, cantidad);
    if (estado == 0 || estado == 1 || estado == 2)
        insertar_error(errores, C_USUARIO_EXISTENTE);

        // Verificar contraseña
    if (strlen(usuario.contrasena) < 6 || strlen(usuario.contrasena) > 32)
        insertar_error(errores, C_CONTRASENA_TAMANO);
    if (!contiene_caracteres_necesarios(usuario.contrasena))
        insertar_error(errores, C_CONTRASENA_FALTAN_CARACTERES);
    if (contiene_caracteres_invalidos(usuario.contrasena))
        insertar_error(errores, C_CONTRASENA_CARACTERES_INVALIDOS);
    if (digitos_consecutivos(usuario.contrasena) > 3)
        insertar_error(errores, C_CONTRASENA_DIGITOS_CONSECUTIVOS);
    if (caracteres_consecutivos(usuario.contrasena))
        insertar_error(errores, C_CONTRASENA_CARACTERES_CONSECUTIVOS);

    // Si hay errores, retornar
    if (errores != NULL)
    {
        //e = errores;
        return 1;
    }
    
    // Crear usuario
        // Verificar si hay espacio
    if (cantidad+1 == MAX_USUARIOS)
        return 2;

        // Añadir usuario a arreglo
    cantidad++;
    usuarios[cantidad] = usuario;
    
        // Escribir usuario en archivo
    if (escribir_usuario(usuario) != 0)
    {
        memset(&usuarios[cantidad--], '\0', sizeof(Usuario));
        return 3;
    }

    return 0;
}

int crear_usuario(Usuario usuarios[MAX_USUARIOS], int &cantidad, Error *&errores)
{
    return crear_usuario(usuarios, cantidad, 0, errores);
}

// FUNCIONES SECUNDARIAS

int buscar_usuario(Usuario usuario, Usuario usuarios[MAX_USUARIOS], int cantidad)
{
    /**
     * INT DE RETORNO:
     * 
     * 0 - Se encontro el usuario
     * 1 - Se encontro el usuario, no coincide la contraseña
     * 2 - Se encontro el usuario, no coincide el tipo
     * 3 - No se encontro el usuario
     * 4 - Usuarios está vacio
     * 
     */

    if (cantidad == 0)
        return 4;

    for (int x = 0; x < cantidad; x++)
    {
        if (strcmp(usuario.usuario, usuarios[x].usuario) == 0)
            if (usuario.tipo == usuarios[x].tipo)
                if (strcmp(usuario.contrasena, usuarios[x].contrasena) == 0)
                    return 0;
                else
                    return 1;
            else
                return 2;
    }

    return 3;
}

int cantidad_mayusculas(const char cadena[])
{
    int cantidad = 0;

    for (int x = 0; x < strlen(cadena); x++)
        if (cadena[x] >= 65 && cadena[x] <= 90)
            cantidad++;

    return cantidad;
}

int cantidad_digitos(const char cadena[])
{
    int cantidad = 0;

    for (int x = 0; x < strlen(cadena); x++)
        if (cadena[x] > 48 && cadena[x] < 57)
            cantidad++;

    return cantidad;
}

bool contiene_caracteres_necesarios(const char cadena[])
{
    bool mayus = false, minus = false, num = false;

    for (int x = 0; x < strlen(cadena); x++)
    {
        if (cadena[x] >= 65 && cadena[x] <= 90)
            mayus = true;
        if (cadena[x] >= 97 && cadena[x] <= 122)
            minus = true;
        if (cadena[x] >= 48 && cadena[x] <= 57)
            num = true;

        if (mayus && minus && num)
            break;
    }

    return (mayus && minus && num);
}

bool contiene_caracteres_invalidos(const char cadena[])
{
    bool contiene = false;

    for (int x = 0; x < strlen(cadena); x++)
    {
        if (!((cadena[x] >= 65 && cadena[x] <= 90) || (cadena[x] >= 97 && cadena[x] <= 122) || (cadena[x] >= 48 && cadena[x] <= 57)))
        {
            contiene = true;
            break;
        }
    }

    return contiene;
}

int digitos_consecutivos(const char cadena[])
{
    int consecutivos = 0, consecutivos_final = 0;
    char anterior = cadena[0];

    for (int x = 1; x < strlen(cadena); x++)
    {
        if (cadena[x] >= 48 && cadena[x] <= 57)
        {
            if (anterior >= 48 && anterior <= 57)
                if (cadena[x] == anterior + 1)
                {
                    consecutivos++;
                    if (consecutivos > consecutivos_final)
                        consecutivos_final = consecutivos;
                }
                else
                    consecutivos = 1;
            else 
                consecutivos = 1;
        }
        else
            consecutivos = 0;

        anterior = cadena[x];
    }
    
    return consecutivos_final;
}

int caracteres_consecutivos(const char cadena[])
{
    int consecutivos = 0, consecutivos_final = 0;
    char anterior = cadena[0];

    for (int x = 1; x < strlen(cadena); x++)
    {
        if ((cadena[x] >= 65 && cadena[x] <= 90) || (cadena[x] >= 97 && cadena[x] <= 122))
        {
            if ((anterior >= 65 && anterior <= 90) || (anterior >= 97 && anterior <= 122))
                if (cadena[x] == anterior + 1 || cadena[x] == anterior + 32 + 1 || cadena[x] == anterior - 32 + 1)
                {
                    consecutivos++;
                    if (consecutivos > consecutivos_final)
                        consecutivos_final = consecutivos;
                }
                else
                    consecutivos = 1;
            else 
                consecutivos = 1;
        }
        else
            consecutivos = 0;

        anterior = cadena[x];
    }
    
    return consecutivos_final;
}

bool es_dni_unico(Cliente clientes[MAX_CLIENTES], int cantidad, int dni)
{
    bool encontrado = false;

    for (int x = 0; x < cantidad; x++)
        if (clientes[x].dni == dni)
        {
            encontrado = true;
            break;
        }

    return encontrado;
}
