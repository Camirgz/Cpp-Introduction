#include <model.h>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class FilaNodo : public Fila{
  public:
	string datos[MAX_COL];
	FilaNodo* sig;
	
	FilaNodo(string datos[]){
		for(int i = 0; i < MAX_COL; i++) this->datos[i] = datos[i];
		this->sig = NULL;
	}
	
	void* get(){
		return this;
	}
	
	void* next(){
		return sig;
	}
};

int split(string texto, string patron, string resultado[], int max){
    int contador = 0;
    size_t inicio = 0;
    size_t buscar = texto.find(patron);

    while(buscar != std::string::npos){
        if(contador >= max){
            break;
        }
        
        resultado[contador] = texto.substr(inicio, buscar - inicio);
        contador++;
        
        inicio = buscar + patron.length();
        buscar = texto.find(patron, inicio);
    }
	
    if(contador < max){
        resultado[contador] = texto.substr(inicio);
        contador++;
    }

    return contador;
}

bool leerLinea(ifstream& archivo, string& linea){
	stringstream ss;
	char character;
	
	if(!archivo.is_open()) return false;
    bool leido = false;
	while(archivo.get(character)){
		leido = true;
		if(character == '\r' || character == '\n') break;
		ss << character;
	}
	linea = ss.str();
	
	return leido ? true : false;
}

Tabla::Tabla(){
	filas = NULL;
	nColumnas = 0;
	nFilas = 0;
}

Tabla::~Tabla(){
	FilaNodo* it = (FilaNodo*)this->filas;
	while(it != NULL){
		FilaNodo* liberar = it;
		it = it->sig;
		delete liberar;
	}
}

int Tabla::cargar(string rutaArchivo){

	ifstream archivo(rutaArchivo.c_str(), ios::in | ios::binary);
  
	if(archivo.is_open()){

		string linea;
		if(leerLinea(archivo, linea)){
			split(linea, ",", columnas, MAX_COL);
			// ya que sabemos cuantas columnas hay, actualizar el valor en la app
			for(int i = 0; i < MAX_COL; i++){
				string c = columnas[i];
				if(c.compare("") == 0){
					nColumnas = i;
					break;
				}
			}
		}	
	
		this->filas = NULL;
		
		while(leerLinea(archivo, linea)){
			if(linea.compare("") == 0) continue;
			
			string datos[MAX_COL];
			split(linea, ",", datos, MAX_COL);
			
			FilaNodo* fila = new FilaNodo(datos);
			
			if(this->filas == NULL){
				this->filas = fila;
			}
			else{
				FilaNodo* it = (FilaNodo*)this->filas;
				while(it->sig != NULL) it = it->sig;
				it->sig = fila;
			}
		}
		
		archivo.close();
		
		return 0;
	}
  
	return -1;
}

int Tabla::insertar(Fila* fila){
	return 0;
}

string Tabla::toString(){
	stringstream ss;
	//for(string columna : columnas){
	for(int i = 0; i < nColumnas; i++){
		string columna = columnas[i];
		if(columna.compare("") == 0) continue;
		ss << columna << ", ";
	}
	ss << "\n";
	
	FilaNodo* it = filas != NULL ? (FilaNodo*)filas : NULL;
	while(it != NULL){
		
		//for(string dato : it->datos){
		for(int i = 0; i < nColumnas; i++){
			string dato = it->datos[i];
			ss << dato << ", ";
		}
		ss << "\n";
		
		it = it->next() != NULL ? (FilaNodo*)it->next() : NULL;
	}
	
	return ss.str();
}

Consulta::Consulta(string consulta) : consulta(consulta){
}
