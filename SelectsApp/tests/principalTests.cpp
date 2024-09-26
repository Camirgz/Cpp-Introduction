#include <iostream>
#include <controller.h>
#include "tests.h"

using namespace std;

int main(){

	int procesadores = 5;
	ProcesadorConsulta* procesadoresConsulta[] = {
		new FiltracionArchivo(),
		new FiltracionColumnas(),
		new FiltracionFilas(),
		new AplicacionClausula(),
		new TransformacionJSON()
	};

    // Casos de prueba:
    string casoPrueba1 = "SELECT cedula,nombre,correo FROM Personas";
    string casoPrueba2 = "SELECT cedula,nombre FROM Personas";
    string casoPrueba3 = "SELECT cedula FROM Personas";
	
	Consulta c1 = Consulta(casoPrueba1);
	Consulta c2 = Consulta(casoPrueba2);
	Consulta c3 = Consulta(casoPrueba3);
	
	//for(ProcesadorConsulta procesador : procesadoresConsulta){
	for(int i = 0; i < procesadores; i++){
		ProcesadorConsulta* procesador = procesadoresConsulta[i];
		procesador->procesar(c1);
		procesador->procesar(c2);
		procesador->procesar(c3);
	}

	if(c1.resultadoJSON.compare("") != 0){
		if(assertContains("{cedula: 2, nombre: b, correo: b}", c1.resultadoJSON)){
			color("green", "casoPrueba1 OK", true);
		}
	}
    else{
        color("red", "casoPrueba1 ERROR", true);
    }

	if(c2.resultadoJSON.compare("") != 0){
		if(assertContains("{cedula: 2, nombre: b}", c2.resultadoJSON)){
			color("green", "casoPrueba2 OK", true);
		}
	}
    else{
        color("red", "casoPrueba2 ERROR", true);
    }

	if(c3.resultadoJSON.compare("") != 0){
		if(assertContains("{cedula: 2}", c3.resultadoJSON)){
			color("green", "casoPrueba3 OK", true);
		}
	}
    else{
        color("red", "casoPrueba3 ERROR", true);
    }
	
	for(int i = 0; i < procesadores; i++){
		delete procesadoresConsulta[i];
	}

    return 0;
}





