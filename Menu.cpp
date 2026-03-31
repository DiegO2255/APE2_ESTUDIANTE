#include "Menu.h"
#include <iostream>
using namespace std;

// Constructor: inicializa RegistroNotas con referencia a RegistroEstudiantes
Menu::Menu() : regNotas(regEst) {}

// Submenu para gestionar estudiantes
void Menu::menuEstudiantes(){
    int op2;
    do{
    	
        // Muestra opciones de gestion de estudiantes
        cout<<"\n=== SUBMENU ESTUDIANTES ===\n";
        cout<<"1.Mostrar estudiantes\n2.Agregar estudiante\n3.Modificar estudiante\n4.Eliminar estudiante\n0.Volver al menu principal\nOpcion: "; cin>>op2;
        
        // Ejecuta accion segun opcion seleccionada
		switch(op2){
            case 1: regEst.mostrarEstudiantes(); break;
            case 2: regEst.agregarEstudiante(); break;
            case 3: regEst.modificarEstudiante(); break;
            case 4: regEst.eliminarEstudiante(); break;
        }
    }while(op2!=0);
}

// Menu principal
void Menu::ejecutar(){
    int op;
    do{
    	
        // Muestra opciones principales del sistema
        cout<<"\n=== GESTOR DE ESTUDIANTES ===\n";
        cout<<"1.Estudiantes\n2.Registro de calificaciones\n3.Promedio de un estudiante\n4.Promedio del curso\n0.Salir\nOpcion: "; cin>>op;

        // Controla flujo del programa
		switch(op){
            case 1: menuEstudiantes(); break;
            case 2: regNotas.gestionarNotas(); break;
            case 3: regNotas.promedioEstudiante(); break;
            case 4: regNotas.promedioCurso(); break;
        }
    }while(op!=0);
}
