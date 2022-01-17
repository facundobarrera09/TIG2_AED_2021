/**
 * 
 * Este archivo contiene todas las estructuras que se utilizaran durante la ejecucion
 * del programa.
 * 
 */

#ifndef H_STRUCTS
#define H_STRUCTS

// Estructuras comunes
struct Fecha
{
    int dia, mes, anio;
};

struct Usuario
{
    char usuario[10];
    char contrasena[32];
    int tipo;
};

struct Profesional
{
    char usuario[10];
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

struct Turno
{
    int id_profesional;
    Fecha fecha;
    int dni_cliente;
    char informe[380];
};

struct Sesion
{
    Usuario usuario;
};

// Funciones de fecha
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

// Listas
struct ListaCadenas
{
    int id;
    char cadena[100];
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
}
void mostrar_cadenas (ListaCadenas *lista)
{
    while (lista != NULL)
    {
        printf("%d - %d - %s - %d - %d\n", lista->id, lista, lista->cadena, lista->ant, lista->sig);

        lista = lista->sig;
    }
}

// Direcciones de archivos
const char USUARIOS_DAT[] = "./binarios/usuarios.dat";
const char PROFESIONALES_DAT[] = "./binarios/profesionales.dat";
const char CLIENTES_DAT[] = "./binarios/clientes.dat";
const char TURNOS_DAT[] = "./binarios/turnos.dat";

// Codigos de tipo de usuario
const int COD_ADMIN = 1;
const int COD_PROF = 2;
const int COD_ASIST = 3;

// Valores maximos
const int MAX_USUARIOS = 100;
const int MAX_PROF = 100;

#endif