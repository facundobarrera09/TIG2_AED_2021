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


void cargar()
{
    FILE *arch;
    arch=fopen(CLIENTES_DAT,"ab");
    if (arch==NULL)
        exit(1);
    tpaciente paciente;
    fflush(stdin);
    printf("Ingrese Apellido y Nombre:");
   gets(paciente.nombre);
   strupr(paciente.nombre);//pone todo el nombre en mayuscula
    fflush(stdin);
    printf("Ingrese direccion:");
    gets(paciente.direccion);
    printf("Ingrese documento:");
    scanf("%d",&paciente.doc);
    fflush(stdin);
	printf("Ingrese historia clinica:");
    gets(paciente.historia);
    
    fwrite(&paciente, sizeof(tpaciente), 1, arch);
    fclose(arch);
   printf("\n\n");
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
    do {
	
    Menu menu;

   
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
    

    mostrar_menu(menu);
	
	
   

        scanf("%d",&opcion);

        switch (opcion) {
            case 1:crear();
                   break;
            case 2:cargar();
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
