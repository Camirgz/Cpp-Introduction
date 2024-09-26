#include <controller.h>

string ProcesadorConsulta::rutaDB = "C:/SelectsApp/db/";

int FiltracionArchivo::procesar(Consulta& consulta){
	string patron = "FROM ";
    int inicio = consulta.consulta.find(patron);
	if(inicio == -1) return -1;
	inicio += patron.length();
	
	patron = " ";
    int final = consulta.consulta.find(patron, inicio);
	if(final == -1) return -1;
	
	consulta.nombre = consulta.consulta.substr(inicio, final - inicio);
	
	string rutaArchivo = ProcesadorConsulta::rutaDB + consulta.nombre + ".csv";
	
	consulta.cargar(rutaArchivo);
	
	return 0;
}

int FiltracionColumnas::procesar(Consulta& consulta){
	return 0;
}

int FiltracionFilas::procesar(Consulta& consulta){
	return 0;
}

int AplicacionClausula::procesar(Consulta& consulta){
	return 0;
}

int TransformacionJSON::procesar(Consulta& consulta){
	return 0;
}