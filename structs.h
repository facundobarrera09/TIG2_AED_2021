/**
 * 
 * Este archivo contiene todas las estructuras que se utilizaran durante la ejecucion
 * del programa.
 * 
 */

#ifndef H_STRUCTS
#define H_STRUCTS

#include <time.h>

// CONSTANTES
//      Direcciones de archivos
const char USUARIOS_DAT[] = "./binarios/usuarios.dat";
const char PROFESIONALES_DAT[] = "./binarios/profesionales.dat";
const char CLIENTES_DAT[] = "./binarios/clientes.dat";
const char INFORMES_DAT[] = "./binarios/informes.dat";
const char TURNOS_DAT[] = "./binarios/turnos.dat";
const char TURNOS_AUX_DAT[] = "./binarios/turnos_aux.dat";

//      Codigos de tipo de usuario
const int COD_ADMIN = 1;
const int COD_PROF = 2;
const int COD_ASIST = 3;

//      Valores maximos
const int MAX_USUARIOS = 100;
const int MAX_PROF = 100;
const int MAX_INFORMES = 100;
const int MAX_CLIENTES = 100;
const int MAX_TURNOS = 100;

const int MAX_LONG_INFORME = 380;
const int MAX_TAMANO_DATO = 380;

// Estructuras comunes
struct Fecha
{
    int dia, mes, anio;
};

struct Usuario
{
    char usuario[11];
    char contrasena[33];
    int tipo;
};

struct Profesional
{
    char usuario[11];
    char nombre[60];
    int id_profesional;
    int dni;
    char telefono[25];
};

struct Cliente
{
    int dni;
    char nombre[60];
    char domicilio[60];
    char localidad[60];
    Fecha fecha_nacimiento;
    float peso;
    char telefono[25];
};

struct Informe
{
    int id_profesional;
    Fecha fecha;
    int dni_cliente;
    char informe[380];
};

struct Sesion
{
    Usuario usuario;
    Profesional datos_prof;
};

// Listas
struct ListaCadenas
{
    int id;
    char cadena[MAX_TAMANO_DATO];
    ListaCadenas *ant, *sig;
};

int tamano_cadenas(ListaCadenas *lista)
{
    int tam = 0;
    while (lista != NULL) 
    {
        tam++;
        lista = lista->sig;
    }
    return tam;
}
void insertar_cadena(ListaCadenas *&lista, const char cadena[], int pos)
{
    ListaCadenas *n, *p, *s, *a;
    n = new ListaCadenas;

    n->id = pos;
    strcpy(n->cadena, cadena);
    n->sig = NULL;
    n->ant = NULL;

    if (lista == NULL)
    {
        lista = n;
    }
    else
    {
        // Buscando elemento a reemplazar (p sera NULL si es el ultimo elemento)
        p = lista;
        while (p != NULL)
        {
            if (pos > p->id)
            {
                a = p;
                p = p->sig;
            }
            else
                break;  
        }
    
        // Reemplazar elemento
        if (p != NULL)
        {
            a = p->ant;

            if (a != NULL) a->sig = n; 
            else lista = n;             // Si es el primero, modificar la variable lista
            n->ant = a;
            n->sig = p;
            p->ant = n;

            while (p != NULL)
            {
                p->id++;
                p = p->sig;
            }
        }
        // Colocar elemento al final
        else
        {
            a->sig = n;
            n->ant = a;
        }
    }
}
void insertar_cadena(ListaCadenas *&lista, const char cadena[])
{
    insertar_cadena(lista, cadena, tamano_cadenas(lista));
}
int modificar_cadena(ListaCadenas *lista, const char cadena[], int pos)
{
    /*
    * 0 - Se encontro
    * 1 - No se encontro
    */

    while (lista != NULL)
    {
        if (lista->id == pos)
        {
            strcpy(lista->cadena, cadena);
            return 0;
        }

        lista = lista->sig;
    }

    return 1;
}
int obtener_cadena(ListaCadenas *lista, int pos, char buffer[])
{
    /*
    * 0 - Se encontro
    * 1 - No se encontro
    */
    strcpy(buffer, "");

    while (lista != NULL)
    {
        if (lista->id == pos)
        {
            strcpy(buffer, lista->cadena);
            return 0;
        }
        else
            lista = lista->sig;
    }

    return 1;
}
void eliminar_cadenas(ListaCadenas *&lista)
{
    ListaCadenas *n, *p = lista;
    
    while (p != NULL)
    {
        n = p->sig;
        delete p;
        p = n;
    }

    lista = NULL;
}
void mostrar_cadenas (ListaCadenas *lista)
{
    while (lista != NULL)
    {
        printf("%d - %d - %s - %d - %d\n", lista->id, lista, lista->cadena, lista->ant, lista->sig);

        lista = lista->sig;
    }
}

// Funciones de Fecha
Fecha obtener_fecha(const char cadena[])
{
    Fecha fecha;
    char buffer[10] = "";
    int sig = 0;

    // Dia
    if (cadena[sig+1] == '/')
        memcpy(buffer, cadena, 1);
    else
    {
        memcpy(buffer, cadena, 2);
        sig++;
    }
    fecha.dia = atoi(buffer);
    sig += 2;

    // Mes
    if (cadena[sig+1] == '/')
    {
        memcpy(buffer, &cadena[sig], 1);
    }
    else
    {
        memcpy(buffer, &cadena[sig], 2);
        sig++;
    }
    fecha.mes = atoi(buffer);
    sig += 2;

    // Año
    memcpy(buffer, &cadena[sig], 4);
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
void fecha_a_cadena(Fecha fecha, char cadena[])
{
    int sig = 0;

    itoa(fecha.dia, &cadena[sig++], 10);
    if (fecha.dia > 9) sig++;
    cadena[sig++] = '/';

    itoa(fecha.mes, &cadena[sig++], 10);
    if (fecha.mes > 9) sig++;
    cadena[sig++] = '/';

    itoa(fecha.anio, &cadena[sig++], 10);
}
int obtener_edad(Fecha nacimiento, Fecha actual)
{
    int edad = 0;

    edad = actual.anio - nacimiento.anio;

    if (actual.mes < nacimiento.mes || (actual.mes == nacimiento.mes && actual.dia < nacimiento.dia))
        edad--;

    return edad;
}

#endif