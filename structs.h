/**
 * 
 * Este archivo contiene todas las estructuras que se utilizaran durante la ejecucion
 * del programa.
 * 
 */

#ifndef H_STRUCTS
#define H_STRUCTS

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

#endif