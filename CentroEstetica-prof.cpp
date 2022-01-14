#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

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
    arch=fopen("pacientes.dat","wb");
    if (arch==NULL)
        exit(1);
    fclose(arch);
    continuar();
}


void cargar()
{
    FILE *arch;
    arch=fopen("pacientes.dat","ab");
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
	
	arch=fopen("pacientes.dat","rb");
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
    arch=fopen("pacientes.dat","r+b");
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



void modificacionhistoriaclinica()
{
	char histclinic [1000];
    FILE *arch;
    arch=fopen("pacientes.dat","r+b");
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
    
    arch=fopen("pacientes.dat","r+b");
    
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
    
	arch=fopen("pacientes.dat","r+b");
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
    int opcion;
    do {
        printf("1 - Crear un archivo  \"pacientes.dat\"\n");
        printf("2 - Carga de paciente\n");
        printf("3 - Listado completo.\n");
        printf("4 - Consulta por su doc.\n");
        printf("5 - Modificacion de direccion. \n");
        printf("6 - Modificacion Historia clinica. \n");
        printf("7 - Borrar paciente.\n");
        printf("8 - Finalizar\n\n");
        printf("Ingrese su opcion:");
        scanf("%i",&opcion);
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
            case 6:modificacionhistoriaclinica();
            		break;
            case 7:borrapaciente();
            		break;
            
          		//	break;
        }
    } while (opcion!=8);
    return 0;
}
