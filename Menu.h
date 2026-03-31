#ifndef MENU_H
#define MENU_H

#include "RegistroEstudiantes.h"
#include "RegistroNotas.h"

// Clase que controla la interaccion con el usuario mediante menus
class Menu {
private:
    // Registro de estudiantes
    RegistroEstudiantes regEst;

    // Registro de notas asociado a estudiantes
    RegistroNotas regNotas;

    // Submenu para estudiantes
    void menuEstudiantes();

public:
    // Constructor
    Menu();

    // Ejecuta  menu principal
    void ejecutar();
};

#endif
