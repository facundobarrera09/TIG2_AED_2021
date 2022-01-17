#ifndef H_FUNCIONES_STRUCTS
#define H_FUNCIONES_STRUCTS

#include "structs.h"
#include "menu.h"

// Funciones de estructura
Fecha obtener_fecha(const char cadena[])
{
    Fecha fecha;
    char buffer[10] = "";

    memcpy(buffer, cadena, 2);
    fecha.dia = atoi(buffer);
    memcpy(buffer, &cadena[3], 2);
    fecha.mes = atoi(buffer);
    memcpy(buffer, &cadena[6], 4);
    fecha.anio = atoi(buffer);

    return fecha;
}
Fecha obtener_fecha_actual()
{
    char buffer[100];
    Fecha hoy;
    time_t t;
    struct tm *tm;
    t = time(NULL);
    tm = localtime(&t);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm);
    hoy = obtener_fecha(buffer);

    return hoy;
}
Cliente crear_cliente()
{
    Menu menu;
    Cliente cliente;
    int seleccion = 0;

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

            printf("cadena=%s\n", buffer);
        }

        printf("seleccion=%d\n", seleccion);

        system("pause");
    }
}

#endif