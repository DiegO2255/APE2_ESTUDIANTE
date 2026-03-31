#include "RegistroNotas.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Constructor: recibe referencia de RegistroEstudiantes
RegistroNotas::RegistroNotas(RegistroEstudiantes &r) : regEst(r) {}

// Muestra notas y promedio de un estudiante
void RegistroNotas::mostrarNotasEstudiante(Estudiante &e){
    // Verifica si hay notas
	if(e.notas.empty()) cout<<"Sin notas";
    else{
    	// Recorre y muestra cada nota
		for(int i=0;i<e.notas.size();i++){
            cout<<i+1<<":"<<fixed<<setprecision(2)<<e.notas[i];
            if(i!=e.notas.size()-1) cout<<" | ";
        }
    }
    // Muestra promedio
    cout<<" | Promedio actual: "<<fixed<<setprecision(2)<<e.promedio()<<endl;
}

// Permite agregar, modificar y eliminar notas
void RegistroNotas::gestionarNotas(){
    while(true){
        string ced; cout<<"Ingrese cedula (0 para salir): "; cin>>ced;
        if(ced=="0") break;
        // Busca estudiante por cédula
        int pos = regEst.buscarPorCedula(ced);
        // Si no existe, continúa
        if(pos==-1){ cout<<"Estudiante no encontrado.\n"; continue; }
        // Accede al estudiante
        Estudiante &e = regEst.getEstudiantes()[pos];
        int opcion;
        do{
            cout<<"\n=== GESTION DE NOTAS ===\n";
            cout<<"Estudiante: "<<e.nombres<<" "<<e.apellidos<<" | Edad: "<<e.edad()<<endl;
            cout<<"Notas actuales: "; mostrarNotasEstudiante(e);
            cout<<"Opciones:\n1.Agregar\n2.Modificar\n3.Eliminar\n0.Volver\nIngrese opcion: "; cin>>opcion;
        	// Menú de opciones de notas
			switch(opcion){
                case 1: { //Agregar nota
                    if(e.notas.size()>=7) cout<<"Maximo notas alcanzado.\n";
                    else{
                        float n; cout<<"Ingrese nota (0-10): "; cin>>n;
                        if(cin.fail()){ cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout<<"Entrada invalida.\n"; }
                        else if(n<0||n>10) cout<<"Nota invalida.\n";
                        else { e.notas.push_back(n); cout<<"Nota agregada.\n"; mostrarNotasEstudiante(e); }
                    }
                    break;
                }
                case 2: { //Modificar nota
                    int i; cout<<"Numero de nota a modificar: "; cin>>i;
                    if(i>=1 && i<=e.notas.size()){
                        cout<<"Nota actual: "<<fixed<<setprecision(2)<<e.notas[i-1]<<endl;
                        float n; cout<<"Ingrese nueva nota: "; cin>>n;
                        if(cin.fail()){ cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n'); cout<<"Entrada invalida.\n"; }
                        else if(n>=0&&n<=10){ e.notas[i-1]=n; cout<<"Nota modificada.\n"; mostrarNotasEstudiante(e); }
                        else cout<<"Nota invalida.\n";
                    }else cout<<"Numero invalido.\n"; break;
                }
                case 3: { //Eliminar nota
                    int i; cout<<"Numero de nota a eliminar: "; cin>>i;
                    if(i>=1 && i<=e.notas.size()){
                        cout<<"Nota eliminada: "<<fixed<<setprecision(2)<<e.notas[i-1]<<endl;
                        e.notas.erase(e.notas.begin()+i-1);
                        mostrarNotasEstudiante(e);
                    }else cout<<"Numero invalido.\n"; break;
                }
            }
        }while(opcion!=0);
    }
}

// Calcula promedio de un estudiante específico
void RegistroNotas::promedioEstudiante(){
	// Busca estudiante y muestra su promedio
    string ced; cout<<"Ingrese cedula: "; cin>>ced;
    int pos = regEst.buscarPorCedula(ced);
    if(pos==-1){ cout<<"Estudiante no encontrado.\n"; return; }
    Estudiante &e = regEst.getEstudiantes()[pos];
    cout<<"Nombre: "<<e.nombres<<" "<<e.apellidos<<" | Edad: "<<e.edad()<<" | Promedio: "<<fixed<<setprecision(2)<<e.promedio()<<endl;
}

// Calcula promedio general del curso
void RegistroNotas::promedioCurso(){
	// Suma todas las notas de todos los estudiantes
    // Calcula promedio total
    float suma=0; int total=0;
    for(Estudiante &e: regEst.getEstudiantes()){
        for(float n: e.notas){ suma+=n; total++; }
    }
    if(total==0) cout<<"No hay calificaciones.\n";
    else cout<<"Promedio del curso: "<<fixed<<setprecision(2)<<suma/total<<endl;
}
