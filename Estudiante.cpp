#include "Estudiante.h"
#include <sstream>
#include <ctime>

// Constructor: inicializa los datos basicos del estudiante
Estudiante::Estudiante(std::string ced, std::string nom, std::string ape, std::string fecha)
    : cedula(ced), nombres(nom), apellidos(ape), fechaNacimiento(fecha) {}

// Calcula la edad a partir de la fecha de nacimiento (D/M/A)
int Estudiante::edad() {
    // Extrae dia, mes y anio desde el string
    int dia, mes, anio;
    char sep1, sep2;
    std::istringstream ss(fechaNacimiento);
    ss >> dia >> sep1 >> mes >> sep2 >> anio;

    // Obtiene la fecha actual del sistema
    time_t t = time(nullptr);
    tm* hoy = localtime(&t);

    // Calcula edad base
    int e = hoy->tm_year + 1900 - anio;

    // Ajusta si aun no ha cumplido anios este anio
    if ((mes > hoy->tm_mon + 1) || (mes == hoy->tm_mon + 1 && dia > hoy->tm_mday))
        e--;
    return e;
}

// Calcula el promedio de notas del estudiante
float Estudiante::promedio() {
    // Si no hay notas, retorna 0
    if(notas.empty()) return 0;

    // Suma todas las notas
    float suma = 0;
    for(float n : notas) suma += n;

    // Retorna promedio
    return suma / notas.size();
}
