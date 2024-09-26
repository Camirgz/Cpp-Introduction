// main.cpp
#include "../include/ConsultaSQL.h"
#include "ListaRegistros.cpp"
#include <iostream>

using namespace std;

int main() { 
 ConsultaSQL consulta;
    // Ejemplo de entrada de consulta SQL
    string entradaConsulta;
    cout<<"===Bienvenido al simulador de SQL==="<<endl;
    cout << "Ingrese su consulta SQL: "<< endl;
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

    cout << "===Gracias===" <<endl; 

    return 0;
}
