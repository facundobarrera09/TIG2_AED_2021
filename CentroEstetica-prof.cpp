#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "structs.h"
#include "menu.h"
#include "error.h"
#include "usuarios.h"

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

    modificar_dato(menu, "largo", "10");
    modificar_dato(menu, "ancho", "65");
    modificar_dato(menu, "margen", "4");

    // Titulo
    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Profesionales");

    // Opciones y valores
    modificar_dato(menu, "opcion", "0-1 - Llamar al siguiente paciente");
    modificar_dato(menu, "opcion", "1-2 - Obtener historial de un paciente");
    modificar_dato(menu, "opcion", "2-");
    modificar_dato(menu, "opcion", "3-0 - Salir");

    // Controles
    modificar_dato(menu, "control", "Seleccione una opcion");
    
    do {
        mostrar_menu(menu);
        printf("\n> ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                llamar_paciente();
                break;
            case 2:
                buscar_historial();
                break;
        }

        printf("\n");
        system("pause");

    } while (opcion != 0);

    return 0;
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
                mostrar_errores(errores);
                printf("\n\n");
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

}
