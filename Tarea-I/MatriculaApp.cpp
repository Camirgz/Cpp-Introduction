#include <iostream>
#include <stdlib.h>

#define MAX_REGISTROS 100

using namespace std;

/*************** Modelo ***************/
class Curso{
  public:
    int codigo;
	string nombre;
	int creditos;
	int cupos;
	
	Curso(){}
	Curso(int codigo, string nombre, int creditos, int cupos);
};

Curso::Curso(int codigo, string nombre, int creditos, int cupos){
	this->codigo = codigo;
	this->nombre = nombre;
	this->creditos = creditos;
	this->cupos = cupos;
}

class Estudiante{
  public:
    int carnet;
	string nombre;
	string apellidos;
	string correo;
	
	Estudiante(){}
	Estudiante(int carnet, string nombre, string apellidos, string correo);
};

Estudiante::Estudiante(int carnet, string nombre, string apellidos, string correo){
	this->carnet = carnet;
	this->nombre = nombre;
	this->apellidos = apellidos;
	this->correo = correo;
}

class Matricula{
  public:
    int codCurso;
	int carnetEst;
	string fechaMatricula;
	string estadoMatricula;
	
	Matricula(){}
	Matricula(int codCurso, int carnetEst, string fechaMatricula, string estadoMatricula);
};

Matricula::Matricula(int codCurso, int carnetEst, string fechaMatricula, string estadoMatricula){
	this->codCurso = codCurso;
	this->carnetEst = carnetEst;
	this->fechaMatricula = fechaMatricula;
	this->estadoMatricula = estadoMatricula;
}


/*************** Controlador ***************/
class Controlador{
  public:
    static Curso cursos[MAX_REGISTROS];
	static Estudiante estudiantes[MAX_REGISTROS];
	static Matricula matricula[MAX_REGISTROS];
	
	static int indiceCursos; // indice para la "tabla" de cursos
	static int indiceEstudiantes; // indice para estudiantes
	static int indiceMatricula; // indice para matricula
	
	static bool IngresarCurso(string nombre, int creditos, int cupos);
	static bool IngresarEstudiante(string nombre, string apellidos, string correo);
	static bool IngresarMatricula(int codCurso, int carnetEst);
	
	//static ??? CursoMasMatriculado();
	//static ??? EstudianteConMasCreditos();
};

Curso Controlador::cursos[MAX_REGISTROS];
Estudiante Controlador::estudiantes[MAX_REGISTROS];
Matricula Controlador::matricula[MAX_REGISTROS];

int Controlador::indiceCursos = 0;
int Controlador::indiceEstudiantes = 0;
int Controlador::indiceMatricula = 0;

bool Controlador::IngresarCurso(string nombre, int creditos, int cupos){
	if(Controlador::indiceCursos == MAX_REGISTROS){
		return false;
	}
	
	int nuevoCodigo = Controlador::indiceCursos + 1;
	Curso nuevoCurso = Curso(nuevoCodigo, nombre, creditos, cupos);
	Controlador::cursos[Controlador::indiceCursos] = nuevoCurso;
	Controlador::indiceCursos++;
	return true;
}

bool Controlador::IngresarEstudiante(string nombre, string apellidos, string correo){
	if(Controlador::indiceEstudiantes == MAX_REGISTROS){
		return false;
	}
	
	int nuevoCarnet = Controlador::indiceEstudiantes + 1;
	Estudiante nuevoEstudiante = Estudiante(nuevoCarnet, nombre, apellidos, correo);
	Controlador::estudiantes[Controlador::indiceEstudiantes] = nuevoEstudiante;
	Controlador::indiceEstudiantes++;
	return true;

}

bool Controlador::IngresarMatricula(int codCurso, int carnetEst){
}


/*************** Vista ***************/
class GUI{
	public:
	  static void MenuPrincipal();
	  static void MenuCursos();
	  static void MenuIngresarCurso();
	  static void MenuMostrarCursos();
	  static void MenuEstudiantes();
	  static void MenuIngresarEstudiante();
	  static void MenuMostrarEstudiantes();
};

void GUI::MenuPrincipal(){
	while(true){
		system("cls"); // clear en Unix
		cout<<"Sistema de Matricula"<<endl;
		cout<<"1. Cursos"<<endl;
		cout<<"2. Estudiantes"<<endl;
		cout<<"3. Matricula"<<endl;
		cout<<"4. Salir"<<endl;
		
		int opcion = 0;
		cin>>opcion;
		cin.ignore(); // cuando leemos int, "borremos" la entrada
		
		if(opcion == 1){
			GUI::MenuCursos();
		}
		else if(opcion == 2){
			GUI::MenuEstudiantes();
		}
		else if(opcion == 4){
			break;
		}
	
	}	
}

void GUI::MenuCursos(){
    bool continuar = true;
	while(continuar){
		system("cls");
		cout<<"Sistema de Matricula - Cursos"<<endl;
		cout<<"1. Ingresar Curso"<<endl;
		cout<<"2. Mostrar Cursos"<<endl;
		cout<<"3. Regresar"<<endl;
			
		int opcion = 0;
		cin>>opcion;
		cin.ignore();
		
		if(opcion == 1){
			GUI::MenuIngresarCurso();
		}
		else if(opcion == 2){
			GUI::MenuMostrarCursos();
		}
		else if(opcion == 3){
			continuar=false;
		}
	}
}

void GUI::MenuIngresarCurso(){
	cout<<"Digite el nombre del curso"<<endl;
	string nombre;
	getline(cin, nombre, '\n');
	cout<<"Digite la cantidad de creditos del curso"<<endl;
	int creditos;
	cin>>creditos;
	cin.ignore();
	cout<<"Digite la cantidad de cupos del curso"<<endl;
	int cupos;
	cin>>cupos;
	cin.ignore();
	
	bool respuesta = Controlador::IngresarCurso(nombre, creditos, cupos);
	
	cout<<"Resultado del ingreso: "<<respuesta<<endl;
	system("pause");
}

void GUI::MenuMostrarCursos(){
	system("cls");
	for(int i = 0; i < Controlador::indiceCursos; i++){
		Curso c = Controlador::cursos[i];
		cout<<"Codigo: "<<c.codigo;
		cout<<", nombre: "<<c.nombre;
		cout<<", creditos: "<<c.creditos;
		cout<<", cupos: "<<c.cupos<<endl;
	}
	system("pause");
}

void GUI::MenuEstudiantes(){
    bool seguir = true;
	while(seguir){
		system("cls");
		cout<<"Sistema de Matricula - Estudiantes"<<endl;
		cout<<"1. Ingresar Estudiante"<<endl;
		cout<<"2. Mostrar Estudiantes"<<endl;
		cout<<"3. Regresar"<<endl;
			
		int opcion = 0;
		cin>>opcion;
		cin.ignore();
		
		if(opcion == 1){
			GUI::MenuIngresarEstudiante();
		}
		else if(opcion == 2){
			GUI::MenuMostrarEstudiantes();
		}
		else if(opcion == 3){
			seguir = false;
		}
	}
}

void GUI::MenuIngresarEstudiante(){
	cout<<"Digite el nombre del estudiante"<<endl;
	string nombre;
	getline(cin, nombre, '\n');
	cout<<"Digite los apellidos del estudiante"<<endl;
	string apellidos;
	getline(cin, apellidos, '\n');
	cout<<"Digite el correo del estudiante"<<endl;
	string correo;
	getline(cin, correo, '\n');
	
	bool respuesta = Controlador::IngresarEstudiante(nombre, apellidos, correo);
	
	cout<<"Resultado del ingreso: "<<respuesta<<endl;
	system("pause");
}

void GUI::MenuMostrarEstudiantes(){
	system("cls");
	for(int i = 0; i < Controlador::indiceEstudiantes; i++){
		Estudiante e = Controlador::estudiantes[i];
		cout<<"Carnet: "<<e.carnet;
		cout<<", nombre: "<<e.nombre;
		cout<<", apellidos: "<<e.apellidos;
		cout<<", correo: "<<e.correo<<endl;
	}
	system("pause");
}

int main(){	
	GUI::MenuPrincipal();	
	return 0;	
}
