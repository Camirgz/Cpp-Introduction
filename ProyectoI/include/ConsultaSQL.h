#ifndef CONSULTA_SQL_H
#define CONSULTA_SQL_H

#include <iostream>
#include <string>
using namespace std;

class ConsultaSQL {
public:
    string archivo;                  // Nombre del archivo extraído de la consulta (con la ruta completa)
    string columnas[10]; // Arreglo para almacenar hasta 10 columnas
    int numColumnas;                      // Número de columnas seleccionadas
    bool seleccionarTodas; 

    ConsultaSQL();

    void procesarConsulta(const std::string& consulta);
    bool consulta();
};

#endif
