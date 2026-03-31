#ifndef REGISTROESTUDIANTES_H
#define REGISTROESTUDIANTES_H

#include "Estudiante.h"
#include <vector>
#include <string>

// Clase que gestiona la lista de estudiantes
class RegistroEstudiantes {
private:
    // Vector que almacena estudiantes
    std::vector<Estudiante> estudiantes;

    // Limpia entrada de datos
    void limpiar();

    // Validaciones de datos
    bool validarCedula(std::string ced);
    bool validarFecha(std::string fecha);

public:
    // Busca estudiante por cédula
    int buscarPorCedula(std::string ced);

    // Operaciones CRUD
    void mostrarEstudiantes();
    void agregarEstudiante();
    void modificarEstudiante();
    void eliminarEstudiante();

    // Devuelve referencia al vector
    std::vector<Estudiante>& getEstudiantes();
};

#endif
