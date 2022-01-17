#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <string.h>
#include <iostream>
#include "structs.h"
#include "menu.h"
#include "error.h"
#include "usuarios.h"

typedef struct {
    char nombre[40];
    char direccion[40];
    int doc;
    char historia[100];
} tpaciente;


void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}

void crear()
{
    FILE *arch;
    arch=fopen(CLIENTES_DAT,"wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
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
            itoa(seleccion, buffer, sizeof(seleccion));
            strcat(buffer, "-");
            strcat(buffer, entrada);
            modificar_dato(menu, "valor", buffer);
        }
    }
}

void listado()
{
	tpaciente paciente,v[100],aux;
	FILE *arch;
	int i,n,b;
	
	arch=fopen(CLIENTES_DAT,"rb");
        if (arch==NULL)
        exit(1);
   
    fread(&paciente, sizeof(tpaciente), 1, arch);
    while (feof(arch)==0)//paso a un vector el archivo
    {
    	v[i]=paciente;
    	i++;
    	fread(&paciente, sizeof(tpaciente), 1, arch);
    }
    n=i;
    
	//ordeno alfabeticament el vecctor
		 
        do
        {
        	b=0;
        	for(i=0;i<n-1;i++)
        	{
        		if(strcmp(v[i].nombre,v[i+1].nombre)>0)
        		{
        			aux=v[i];
        			v[i]=v[i+1];
        			v[i+1]=aux;
        			b=1;
        		}
        	}
        }
    	while (b==1);
    	
    rewind(arch);
    for(i=0; i<n; i++)
    {
    	paciente=v[i];
    	fwrite(&paciente,sizeof(tpaciente),1,arch);
    }
    
   // getch ();
    
    rewind(arch);
   fread(&paciente, sizeof(tpaciente), 1, arch);
   	printf("\nLista de pacientes\n");
	printf("\nApellido/nom\t\tDocumento\tDireccion\n");
	printf("**********************************************************\n");
	while(!feof(arch))
    {
        printf("%s\t\t%d\t\t%s\n%s\n\n", paciente.nombre, paciente.doc, paciente.direccion,paciente.historia);
        fread(&paciente, sizeof(tpaciente), 1, arch);
    }
    fclose(arch);
    continuar();
}

void consulta()
{
	char histclinic [1000];
	int ag;
    FILE *arch;
    arch=fopen(CLIENTES_DAT,"r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el documento a consultar:");
    int docu;
    scanf("%i", &docu);
    tpaciente paciente;
    int existe=0;
    fread(&paciente, sizeof(tpaciente), 1, arch);
    while(!feof(arch))
    {
        if (docu==paciente.doc)
        {
           printf("%s, %s, %d\n%s", paciente.nombre, paciente.direccion, paciente.doc,paciente.historia);
           existe=1;
           break;
        }
        fread(&paciente, sizeof(tpaciente), 1, arch);
    }
    if (existe==0)
        printf("No existe dicho doc\n");
        printf("\n\n\n");
        printf("Desea agregar historia clinica? : 1 <--para si  /  0<--para No.\n");
        scanf("%d", &ag);
        
        if(ag==1)
        {
        	fflush(stdin);
           printf("Ingrese nueva historia clinica:");
           gets(histclinic);
           strcat(paciente.historia, "\n" );
 			strcat(paciente.historia, histclinic );
           //scanf("%f",&paciente.direccion);
           int pos=ftell(arch)-sizeof(tpaciente);
           fseek(arch,pos,SEEK_SET);
           fwrite(&paciente, sizeof(tpaciente), 1, arch);
           printf("\nSe agrego historia clinica.\n\n");
        }
        fread(&paciente, sizeof(tpaciente), 1, arch);
    fclose(arch);
    continuar();
}



void modificacionInforme()
{
	char histclinic [1000];
    FILE *arch;
    arch=fopen(CLIENTES_DAT,"r+b");
    if (arch==NULL)
        exit(1);
    printf("Ingrese el documento a modificar:");
    int docu;
    scanf("%d", &docu);
    tpaciente paciente;
    int existe=0;
    fread(&paciente, sizeof(tpaciente), 1, arch);
    while(!feof(arch))
    {
        if (docu==paciente.doc)
        {
           printf("%i %s %0.2f\n", paciente.nombre, paciente.direccion, paciente.doc);
           fflush(stdin);
           printf("Ingrese nueva historia clinica:");
           gets(histclinic);
           strcat(paciente.historia, "\n" );
 			strcat(paciente.historia, histclinic );
           //scanf("%f",&paciente.direccion);
           int pos=ftell(arch)-sizeof(tpaciente);
           fseek(arch,pos,SEEK_SET);
           fwrite(&paciente, sizeof(tpaciente), 1, arch);
           printf("Se agrego historia clinica.\n");
           existe=1;
           break;
        }
        fread(&paciente, sizeof(tpaciente), 1, arch);
    }
    if (existe==0)
        printf("No existe el documento\n");
    fclose(arch);
    continuar();
}

void modificacionDireccion()
{
    FILE *arch;
    
    arch=fopen(CLIENTES_DAT,"r+b");
    
    if (arch==NULL)
        exit(1);
    printf("Ingrese el documento a modificar:");
    int docu;
    scanf("%d", &docu);
    tpaciente paciente;
    int existe=0;
    fread(&paciente, sizeof(tpaciente), 1, arch);
    while(!feof(arch))
    {
        if (docu==paciente.doc)
        {
           printf("%i %s %0.2f\n", paciente.nombre, paciente.direccion, paciente.doc);
           printf("Ingrese nuevo direccion:");
           scanf("%f",&paciente.direccion);
           int pos=ftell(arch)-sizeof(tpaciente);
           fseek(arch,pos,SEEK_SET);
           fwrite(&paciente, sizeof(tpaciente), 1, arch);
           printf("Se modifico la direccion.\n");
           existe=1;
           break;
        }
        fread(&paciente, sizeof(tpaciente), 1, arch);
    }
    if (existe==0)
        printf("No existe el documento\n");
    fclose(arch);
    continuar();
}

void borrapaciente()
{

	bool band;
	FILE *arch;
	FILE *aux;// archivo para guardar datos sin el paciente a borrar
    
	arch=fopen(CLIENTES_DAT,"r+b");
    aux=fopen("auxiliar.dat","w+b");
   // if (arch==NULL)
     //   exit(1);
        
    printf("Ingrese el documento a borrar:");
    int docu;
    scanf("%d", &docu);
    tpaciente paciente;
    int existe=0;
    fread(&paciente, sizeof(tpaciente),1,arch);
    band=false;
    while(!feof(arch))
	{
		if(paciente.doc!=docu)
		
		fwrite(&paciente,sizeof(tpaciente),1,aux);
		
		else
		band=true;
		
		fread(&paciente,sizeof(tpaciente),1,arch);
	}
	fclose (arch);
	fclose (aux);
	
	if(band==true)
	{
		printf("\nPaciente borrado.\n\n");
		remove("pacientes.dat");
		rename("auxiliar.dat","pacientes.dat");
	}
	else
	printf("\nPaciente no encontrado\n\n");
}


int main()
{
	
    Menu menu;
	Sesion sesion;
	Usuario usuarios[MAX_USUARIOS];
	int cantidad;
	int estado;
	Error *error_inicio;
	
	estado=leer_usuarios(usuarios,cantidad);
	
	if(estado!=0)
	{
		printf("Error-no se encontraron usuarios");
		return 1;
	}
	else
	{
		while(true)
		{
			estado=inicio_de_sesion(sesion.usuario,COD_PROF,usuarios,cantidad,error_inicio);
			if (estado!=0)
			{
				mostrar_errores(error_inicio);
			
				continue;
				
			}
			else
			break;
		}
	}
	
	int opcion;
     
	
    modificar_dato(menu, "largo", "14");
    modificar_dato(menu, "ancho", "71");
    modificar_dato(menu, "margen", "2");

    // Titulo
    modificar_dato(menu, "titulo", "Centro de Estetica");
    modificar_dato(menu, "titulo", "Menu de Profesionales");

    // Opciones y valores
    modificar_dato(menu, "opcion", "0-1-Crear archivo");
    modificar_dato(menu, "opcion", "1-2-Cargar cliente");
    modificar_dato(menu, "opcion", "2-3-listar clientes");
    modificar_dato(menu, "opcion", "3-4-Consultar cliente por DNI");
    modificar_dato(menu, "opcion", "4-5-Modificar direccion");
    modificar_dato(menu, "opcion", "5-6-Agregar informe");
    modificar_dato(menu, "opcion", "6-7-borrar cliente");
    modificar_dato(menu, "opcion", "7- ");
    modificar_dato(menu, "opcion", "8-8-Salir");
    
    do {
    mostrar_menu(menu);

        scanf("%d",&opcion);

        switch (opcion) {
            case 1:
                    crear();
                   break;
            case 2:
                    escribir_cliente(crear_cliente());
                   break;
            case 3:listado();
                   break;
            case 4:consulta();
                   break;
            case 5:modificacionDireccion();
                   break;
            case 6:modificacionInforme();
            		break;
            case 7:borrapaciente();
            		break;
            
          		//	break;
        }
    } while (opcion!=8);
    return 0;
}
