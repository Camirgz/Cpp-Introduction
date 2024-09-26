#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#define MAX_COL 10

using namespace std;

class Fila{
  public:
    virtual void* get() = 0;
	virtual void* next() = 0;
};

class Tabla{
  public:
    string nombre;
	string columnas[MAX_COL];
	Fila* filas;
	int nColumnas;
	int nFilas;
	
	string rutaArchivo;
	
	Tabla();
	~Tabla();
	
	virtual int cargar(string rutaArchivo);
    virtual int insertar(Fila* fila);
    virtual string toString();
};

class FiltroFilas{
  public:
    string columna;
	string operacion;
	string valor;
};

class Clausula{
  public:
    string clausula;
	string columna;
};

class Consulta : public Tabla{
  public:
    string consulta;
	FiltroFilas filtro1, filtro2;
	Clausula clasula;
	string resultadoJSON;
	
	Consulta(string consulta);
};

#endif