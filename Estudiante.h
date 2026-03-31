#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include <vector>

// Clase que representa a un estudiante con datos personales y notas
class Estudiante {
public:
    // Atributos publicos del estudiante
    std::string cedula;
    std::string nombres;
    std::string apellidos;
    std::string fechaNacimiento; // Formato D/M/A
    std::vector<float> notas;

    // Constructor vacio
    Estudiante() {}

    // Constructor con parametros
    Estudiante(std::string ced, std::string nom, std::string ape, std::string fecha);

    // Calcula edad del estudiante
    int edad();

    // Calcula promedio de notas
    float promedio();
};

#endif
