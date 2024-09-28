#include "../include/ConsultaSQL.h"
#include "../include/ListaRegistros.h"
#include <iostream>

using namespace std;

int main()
{
    ConsultaSQL consulta;
    // Ejemplo de entrada de consulta SQL
    string entradaConsulta;
    cout << "===Bienvenido al simulador de SQL===" << endl;
    cout << "Ingrese su consulta SQL: " << endl;
    getline(cin, entradaConsulta);

    // Procesar la consulta
    consulta.procesarConsulta(entradaConsulta);

   

    // Crear la lista de registros y leer el archivo
    

    // Imprimir los registros según la consulta
 

    cout << "===Gracias===" << endl;

    return 0;
}
