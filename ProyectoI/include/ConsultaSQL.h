#ifndef CONSULTA_SQL_H
#define CONSULTA_SQL_H

#include <iostream>
#include <string>
#include "Registro.h"
#include "ListaRegistros.h"

using namespace std;

class ConsultaSQL {
public:
    static const int MAX_COLUMNAS = 100;
    string archivo;                  // Nombre del archivo extraído de la consulta (con la ruta completa)
    string columnas[10];             // Arreglo para almacenar hasta 10 columnas
    int numColumnas;                 // Número de columnas seleccionadas
    bool seleccionarTodas; 
    ListaRegistros lista;

    ConsultaSQL();

    void procesarConsulta(const std::string& consulta);
    bool consulta();
    void procesarDistinct(const std::string& columnasStr);
    void recorrer() const;
};

#endif // CONSULTA_SQL_H
