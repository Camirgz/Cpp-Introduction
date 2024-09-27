#ifndef LISTAREGISTROS_H
#define LISTAREGISTROS_H

#include "Registro.h"
#include <fstream>
#include <sstream>

using namespace std;

class ListaRegistros {
public:
    Registro *cabeza;
    
    ListaRegistros() : cabeza(nullptr) {};
    void leerArchivoCSV(const string &rutaArchivo);
    void imprimirLista(int numcolumnas, string *columnas, bool imprimirTodas) const;
};

#endif // LISTAREGISTROS_H
