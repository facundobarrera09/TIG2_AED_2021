#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "structs.h"
#include "menu.h"
#include "error.h"
#include "usuarios.h"

void visualizar_lista();
void llamar_paciente();
void buscar_historial();

Sesion sesion;
Fecha hoy;

int main()
{
    Menu menu;
    Profesional profesionales[MAX_PROF];
	Usuario usuarios[MAX_USUARIOS];
	int cant_usuarios, cant_prof;
	int estado;
	Error *error_inicio;
    hoy = obtener_fecha_actual();
	
	estado=leer_usuarios(usuarios,cant_usuarios);
	
	if(estado!=0)
	{
		printf("Error-no se encontraron usuarios");
		return 1;
	}
	else
	{
		while(true)
		{
			estado = inicio_de_sesion(sesion.usuario,COD_PROF,usuarios,cant_usuarios,error_inicio);
			if (estado!=0)
			{
				mostrar_errores(error_inicio);
				continue;
			}
			else
            {
                estado = leer_profesionales(profesionales, cant_prof);
                if (estado == 0)
                {
                    estado = buscar_profesional(sesion.datos_prof, profesionales, cant_prof, sesion.usuario.usuario);
                    if (estado != 0)
                    {
                        printf("No se encontro un profesional asociado al usuario");
                        return 1;
                    }
                }
                else
                {
                    printf("No se pudo leer archivo de profesionales");
                    return 1;
                }
                
			    break;
            }
		}
	}
	
	int opcion;

    modificar_dato(menu, "largo", "11");
    modificar_dato(menu, "ancho", "65");
    modificar_dato(menu, "margen", "4");

    // Titulo
    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Profesionales");

    // Opciones y valores
    modificar_dato(menu, "opcion", "1-1 - Visualizar lista de espera");
    modificar_dato(menu, "opcion", "2-2 - Llamar al siguiente paciente");
    modificar_dato(menu, "opcion", "3-3 - Obtener historial de un paciente");
    modificar_dato(menu, "opcion", "4-");
    modificar_dato(menu, "opcion", "5-0 - Salir");

    // Controles
    modificar_dato(menu, "control", "Seleccione una opcion");
    
    do {
        mostrar_menu(menu);
        printf("\n> ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                visualizar_lista();
                break;
            case 2:
                llamar_paciente();
                break;
            case 3:
                buscar_historial();
                break;
        }

        printf("\n");
        system("pause");

    } while (opcion != 0);

    return 0;
}

void visualizar_lista()
{
    Menu lista;
    int largo = 6;

    Cliente clientes[MAX_CLIENTES], pendientes[MAX_TURNOS], cliente;
    int cant_clientes, cant_pendientes;

    char buffer[50];
    int estado;

    // Lista de turnos pendientes
    modificar_dato(lista, "ancho", "65");
    modificar_dato(lista, "margen", "4");
    modificar_dato(lista, "titulo", "Atenciones pendientes");
    modificar_dato(lista, "control", "Enter para continuar");

    // Principal
    leer_clientes(clientes, cant_clientes);
    estado = leer_turnos(pendientes, cant_pendientes);
    if (estado == 0)
    {
        largo += cant_pendientes;
        itoa(largo, buffer, 10);
        modificar_dato(lista, "largo", buffer);

        for (int x = 0; x <= cant_pendientes; x++)
        {
            if (x == cant_pendientes)
            {
                strcpy(buffer, "");
                itoa(x, buffer, 10);
                strcat(buffer, "-");
                modificar_dato(lista, "opcion", buffer);

                break;
            }

            int sig = 0;

            strcpy(buffer, "");
            itoa(x, &buffer[sig++], 10);
            if (x > 9) sig++;
            strcat(buffer, "-"); sig++;
            itoa(x, &buffer[sig++], 10);
            if (x > 9) sig++;

            strcat(buffer, " - Nombre: ");
            sig = strlen(buffer);
            buscar_cliente(cliente, clientes, cant_clientes, pendientes[x].dni);
            strcat(buffer, cliente.nombre);

            strcat(buffer, " - DNI: ");
            sig = strlen(buffer);
            itoa(pendientes[x].dni, &buffer[sig], 10);

            modificar_dato(lista, "opcion", buffer);
        }
    
        mostrar_menu(lista);
    }
    else
        printf("No hay turnos");
}

void llamar_paciente()
{
    Menu datos_paciente;

    Cliente turnos[MAX_TURNOS], paciente;
    Informe informes[MAX_INFORMES], datos_informe;
    int cant_turnos, cant_informes;

    Error *errores;

    int estado, opcion;
    char buffer[100] = "";

    // Menu de datos del paciente
    modificar_dato(datos_paciente, "largo", "flex");
    modificar_dato(datos_paciente, "largo", "10");
    modificar_dato(datos_paciente, "ancho", "65");
    modificar_dato(datos_paciente, "margen", "4");
    modificar_dato(datos_paciente, "titulo", "Datos del paciente");
    modificar_dato(datos_paciente, "opcion", "0-Nombre");
    modificar_dato(datos_paciente, "opcion", "1-DNI");
    modificar_dato(datos_paciente, "opcion", "2-Domicilio");
    modificar_dato(datos_paciente, "opcion", "3-Edad");
    modificar_dato(datos_paciente, "opcion", "4-Peso");
    modificar_dato(datos_paciente, "control", "Enter para continuar");

    // Mostrar datos en pantalla
    estado = leer_turnos(turnos, cant_turnos);

    if (estado == 0)
    {
        paciente = turnos[0];
        //borrar_turno();

        // Actualizar menu
        strcpy(buffer, "0-");
        strcat(buffer, paciente.nombre);
        modificar_dato(datos_paciente, "valor", buffer);

        strcpy(buffer, "1-");
        itoa(paciente.dni, &buffer[2], 10);
        modificar_dato(datos_paciente, "valor", buffer);

        strcpy(buffer, "2-");
        strcat(buffer, paciente.domicilio);
        modificar_dato(datos_paciente, "valor", buffer);

        strcpy(buffer, "3-");
        itoa(obtener_edad(paciente.fecha_nacimiento, hoy), &buffer[2], 10);
        modificar_dato(datos_paciente, "valor", buffer);

        strcpy(buffer, "4-");
        snprintf(&buffer[2], (sizeof buffer)-2, "%f", paciente.peso);
        modificar_dato(datos_paciente, "valor", buffer);

        mostrar_menu(datos_paciente);
        printf("\n");
        system("pause");
    
        // Crear informe
        while (true)
        {
            datos_informe.dni_cliente = paciente.dni;
            datos_informe.id_profesional = sesion.datos_prof.id_profesional;
            datos_informe.fecha = hoy;

            estado = crear_informe(datos_informe, informes, cant_informes, errores);

            if (estado != 0)
            {
                printf("\n");
                mostrar_errores(errores);
                printf("\n");
                printf("Desea intentar de nuevo? [s/n]: ");
                _flushall();
                opcion = getchar();

                if (opcion == 's' || opcion == 'S')
                    continue;
                else
                    break;
            }
            else
            {
                borrar_turno();
                printf("\nInforme registrado con exito\n");
                break;
            }
        }
    }
    else if (estado == 1)
    {
        printf("No hay pacientes en la fila de espera\n");
    }
    else 
    {
        printf("Error al leer el archivo de turnos\n");
    }
}

void buscar_historial()
{
    Menu listado, informe;
    int largo = 7;

    Profesional profesionales[MAX_PROF], prof;
    Informe informes[MAX_INFORMES], historial[MAX_INFORMES];
    Cliente clientes[MAX_CLIENTES], cliente;
    int cant_prof, cant_informes, cant_historial = 0, cant_clientes;
    int dni_cliente;

    char buffer[MAX_LONG_INFORME+5];

    char entrada[10] = "";
    int estado, opcion;
    bool ejecutar = true;

    // Listado de informes
    modificar_dato(listado, "largo", "7");
    modificar_dato(listado, "ancho", "65");
    modificar_dato(listado, "margen", "4");
    modificar_dato(listado, "titulo", "Listado de informes");
    modificar_dato(listado, "control", "Seleccione una opcion");
    modificar_dato(listado, "control", "EX para salir");

    // Informe seleccionado
    modificar_dato(informe, "largo", "flex");
    modificar_dato(informe, "largo", "11");
    modificar_dato(informe, "ancho", "65");
    modificar_dato(informe, "margen", "4");

    modificar_dato(informe, "opcion", "0-ID del profesional");
    modificar_dato(informe, "opcion", "1-DNI del cliente");
    modificar_dato(informe, "opcion", "2-Fecha");
    modificar_dato(informe, "opcion", "3-Informe");
    modificar_dato(informe, "opcion", "4-");
    modificar_dato(informe, "valor", "0-");
    modificar_dato(informe, "valor", "1-");
    modificar_dato(informe, "valor", "2-");
    modificar_dato(informe, "valor", "3-");

    modificar_dato(informe, "control", "Enter para continuar");

    // Principal
    leer_profesionales(profesionales, cant_prof);
    leer_clientes(clientes, cant_clientes);
    estado = leer_informes(informes, cant_informes);
    if (estado == 0)
    {
        printf("\nIngrese el DNI del paciente: ");
        scanf("%d", &dni_cliente);

        // Buscar informes
        for (int x = 0; x < cant_informes; x++)
        {
            if (informes[x].dni_cliente == dni_cliente)
            {
                historial[cant_historial] = informes[x];
                cant_historial++;
                largo++;
            }
        }

        // Generar lista de informes
        if (cant_historial == 0)
        {
            modificar_dato(listado, "opcion", "0-No se encontraron informes");
            modificar_dato(listado, "opcion", "1-");
        }
        else
        {
            for (int x = 0; x <= cant_historial; x++)
            {
                if (x == cant_historial)
                {
                    strcpy(buffer, "");
                    itoa(x, buffer, 10);
                    strcat(buffer, "-");
                    modificar_dato(listado, "opcion", buffer);

                    break;
                }

                int sig = 0;

                strcpy(buffer, "");
                itoa(x, &buffer[sig++], 10);
                if (x > 9) sig++;
                strcat(buffer, "-"); sig++;
                itoa(x, &buffer[sig++], 10);
                if (x > 9) sig++;
                strcat(buffer, " - Fecha: ");
                sig = strlen(buffer);

                fecha_a_cadena(historial[x].fecha, &buffer[sig]);
                strcat(buffer, " - Prof: ");
                sig = strlen(buffer);

                buscar_profesional(prof, profesionales, cant_prof, historial[x].id_profesional);
                strcat(buffer, prof.nombre);

                modificar_dato(listado, "opcion", buffer);
            }
        }

        itoa(largo, buffer, 10);
        modificar_dato(listado, "largo", buffer);

        // Mostrar informe y solicitar entrada
        if (cant_historial != 0)
        {
            while (ejecutar)
            {
                mostrar_menu(listado);
                printf("\n> ");
                scanf("%s", entrada);

                if (strcmp(entrada, "EX") == 0)
                {
                    ejecutar = false;
                    break;
                }
                else
                {
                    opcion = atoi(entrada);
                    if (opcion >= cant_historial) continue;

                    buscar_cliente(cliente, clientes, cant_clientes, historial[opcion].dni_cliente);
                    buscar_profesional(prof, profesionales, cant_prof, historial[opcion].id_profesional);
                    eliminar_cadenas(informe.titulo);

                    strcpy(buffer, "Informe de ");
                    strcat(buffer, cliente.nombre);
                    modificar_dato(informe, "titulo", buffer);

                    strcpy(buffer, "Prof: ");
                    strcat(buffer, prof.nombre);
                    modificar_dato(informe, "titulo", buffer);

                    strcpy(buffer, "0-");
                    itoa(historial[opcion].id_profesional, &buffer[2], 10);
                    modificar_dato(informe, "valor", buffer);

                    strcpy(buffer, "1-");
                    itoa(historial[opcion].dni_cliente, &buffer[2], 10);
                    modificar_dato(informe, "valor", buffer);

                    strcpy(buffer, "2-");
                    fecha_a_cadena(historial[opcion].fecha, &buffer[2]);
                    modificar_dato(informe, "valor", buffer);

                    strcpy(buffer, "3-");
                    strcat(buffer, historial[opcion].informe);
                    modificar_dato(informe, "valor", buffer);

                    mostrar_menu(informe);
                    printf("\n");
                    system("pause");
                }
            }
        }
        else
            mostrar_menu(listado);
    }
    else
        printf("No existen informes o no se pudo leer el archivo\n");
}
