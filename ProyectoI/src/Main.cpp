// main.cpp
#include "../include/ConsultaSQL.h"
#include "ListaRegistros.cpp"
#include <iostream>

using namespace std;

int main() {
 ConsultaSQL consulta;
    // Ejemplo de entrada de consulta SQL
    string entradaConsulta;
    cout << "Ingrese su consulta SQL: ";
    getline(cin, entradaConsulta);

   
    // Procesar la consulta
    consulta.procesarConsulta(entradaConsulta);

    consulta.consulta();
    
    // Crear la lista de registros y leer el archivo
    ListaRegistros lista;
    lista.leerArchivoCSV(consulta.archivo);

    // Imprimir los registros según la consulta
    cout << "Resultado de la consulta:\n" << endl;
    lista.imprimirLista(consulta.numColumnas, consulta.columnas);

    return 0;
}
