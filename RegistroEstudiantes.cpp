#include "RegistroEstudiantes.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;

const int MAX_ESTUDIANTES = 20;
const int MAX_NOTAS = 7;

// Limpia el buffer de entrada para evitar errores
void RegistroEstudiantes::limpiar() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Valida que la cedula tenga 10 digitos numericos
bool RegistroEstudiantes::validarCedula(string ced) {
    if(ced.length()!=10) return false;
    for(char c : ced) if(!isdigit(c)) return false;
    return true;
}

// Valida formato y valores de fecha (D/M/A)
bool RegistroEstudiantes::validarFecha(string fecha) {
	// Verifica formato
    if(fecha.length()!=10 || fecha[2]!='/' || fecha[5]!='/') return false;
	// Extrae valores
	int dia, mes, anio;
    char sep1, sep2;
    istringstream ss(fecha);
    ss >> dia >> sep1 >> mes >> sep2 >> anio;
    if(ss.fail()) return false;
    // Verifica rango de fecha
    if(anio<1900 || anio>2100 || mes<1 || mes>12) return false;
    // Ajusta dias por mes y anio bisiesto
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if((anio%4==0 && anio%100!=0) || (anio%400==0)) diasMes[1]=29;
    // Verifica dia valido
    return dia>=1 && dia<=diasMes[mes-1];
}

// Busca estudiante por cedula y retorna posicion
int RegistroEstudiantes::buscarPorCedula(string ced) {
    for(int i=0;i<estudiantes.size();i++)
        if(estudiantes[i].cedula==ced) return i;
    return -1;
}

vector<Estudiante>& RegistroEstudiantes::getEstudiantes() {
    return estudiantes;
}

// Muestra todos los estudiantes registrados
void RegistroEstudiantes::mostrarEstudiantes() {
	// Verifica si hay estudiantes
    if(estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }
    cout << "\n=== LISTADO DE ESTUDIANTES ===\n";
    // Recorre y muestra informacion
    for(int i=0;i<estudiantes.size();i++){
        Estudiante &e = estudiantes[i];
        // Muestra datos y promedio
        cout << i+1 << ". " << e.nombres << " " << e.apellidos
             << " | CI: " << e.cedula
             << " | Edad: " << e.edad()
             << " | Notas: ";
        // Muestra notas
        if(e.notas.empty()) cout << "Sin notas";
        else{
            for(int j=0;j<e.notas.size();j++){
                cout << j+1 << ":" << fixed << setprecision(2) << e.notas[j];
                if(j!=e.notas.size()-1) cout<<" | ";
            }
        }
        cout << " | Promedio actual: " << fixed << setprecision(2) << e.promedio();
        // Calcula cuantas notas faltan
		int faltan = MAX_NOTAS - e.notas.size();
        if(faltan>0) cout << " | Faltan " << faltan << " nota(s)";
        else cout << " | Todas las notas registradas";
        cout << endl;
    }
}

// Agrega nuevos estudiantes
void RegistroEstudiantes::agregarEstudiante() {
	// Controla limite maximo
    while(estudiantes.size() < MAX_ESTUDIANTES) {
        string ced, nom, ape, fecha;
        // Valida cedula unica y correcta
        do{
            cout << "Ingrese cedula (10 digitos): ";
            cin >> ced;
            if(!validarCedula(ced)) cout << "Cedula invalida.\n";
            else if(buscarPorCedula(ced)!=-1) cout << "Cedula ya registrada.\n";
        }while(!validarCedula(ced) || buscarPorCedula(ced)!=-1);
        limpiar();
        cout << "Ingrese nombres: "; getline(cin, nom);
        cout << "Ingrese apellidos: "; getline(cin, ape);
        do{
            cout << "Ingrese fecha de nacimiento (DD/MM/AAAA): ";
            getline(cin, fecha);
            if(!validarFecha(fecha)) cout << "Fecha invalida.\n";
        }while(!validarFecha(fecha));

        // Inserta estudiante en el vector
        estudiantes.push_back(Estudiante(ced,nom,ape,fecha));
        cout << "Estudiante agregado correctamente.\n";

        char resp;
        cout << "Desea agregar otro estudiante? (s/n): "; cin >> resp;
        if(resp!='s' && resp!='S') break;
    }
    if(estudiantes.size()>=MAX_ESTUDIANTES) cout << "Se alcanzo el maximo de estudiantes.\n";
}

// Modifica los datos de un estudiante existente
void RegistroEstudiantes::modificarEstudiante() {
	// Verifica si hay estudiantes registrados
    if(estudiantes.empty()) { cout << "No hay estudiantes registrados.\n"; return; }
    // Bucle para permitir modificar varios estudiantes
	while(true){
        // Muestra la lista de estudiantes
        mostrarEstudiantes();
        int pos;
        // Solicita la posición del estudiante
		cout << "Ingrese numero del estudiante: "; cin >> pos;
        // Valida entrada (número válido dentro del rango)
		if(cin.fail() || pos<1 || pos>estudiantes.size()){ limpiar(); cout << "Numero invalido.\n"; return; }
        // Ajusta índice (de humano a índice de vector)
		pos--; 
		limpiar();

        // Permite modificar nombres y apellidos
		cout << "Ingrese nuevos nombres: "; getline(cin, estudiantes[pos].nombres);
        cout << "Ingrese nuevos apellidos: "; getline(cin, estudiantes[pos].apellidos);
        // Validación de nueva fecha de nacimiento
		string fecha;
        do{
            cout << "Ingrese nueva fecha (D/M/A): "; getline(cin,fecha);
            if(!validarFecha(fecha)) cout << "Fecha invalida.\n";
        }while(!validarFecha(fecha));
        // Validación de nueva fecha de nacimiento
		estudiantes[pos].fechaNacimiento = fecha;
        cout << "Estudiante modificado correctamente.\n";

        char resp; cout << "Desea modificar otro? (s/n): "; cin >> resp;
        if(resp!='s' && resp!='S') break;
    }
}

void RegistroEstudiantes::eliminarEstudiante() {
    if(estudiantes.empty()) { cout << "No hay estudiantes.\n"; return; }
    while(true){
        mostrarEstudiantes();
        int pos;
        cout << "Ingrese numero del estudiante: "; cin >> pos;
        if(cin.fail() || pos<1 || pos>estudiantes.size()){ limpiar(); cout << "Numero invalido.\n"; return; }
        char confirm; cout << "Seguro? (s/n): "; cin >> confirm;
        if(confirm=='s'||confirm=='S'){
            cout << "Estudiante eliminado: " << estudiantes[pos-1].nombres<<" "<<estudiantes[pos-1].apellidos<<"\n";
            estudiantes.erase(estudiantes.begin()+pos-1);
        }else cout<<"Operacion cancelada.\n";

        char resp; cout<<"Desea eliminar otro? (s/n): "; cin>>resp;
        if(resp!='s' && resp!='S') break;
        if(estudiantes.empty()){ cout<<"No hay mas estudiantes.\n"; break; }
    }
}
