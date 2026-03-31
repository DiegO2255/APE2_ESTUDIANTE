#ifndef REGISTRONOTAS_H
#define REGISTRONOTAS_H

#include "RegistroEstudiantes.h"

// Clase que gestiona las calificaciones de los estudiantes
class RegistroNotas {
private:
    // Referencia al registro de estudiantes
    RegistroEstudiantes &regEst;

    // Muestra notas de un estudiante
    void mostrarNotasEstudiante(Estudiante &e);

public:
    // Constructor con referencia
    RegistroNotas(RegistroEstudiantes &r);

    // Gestión completa de notas
    void gestionarNotas();

    // Promedio individual
    void promedioEstudiante();

    // Promedio general del curso
    void promedioCurso();
};

#endif
