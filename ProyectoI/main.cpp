// main.cpp
#include "consulta_sql.h"
#include "lista_registros.cpp"
#include <iostream>

int main() {
    std::ConsultaSQL consulta;

    // Ejemplo de entrada de consulta SQL
    std::string entradaConsulta;
    std::cout << "Ingrese su consulta SQL: ";
    getline(std::cin, entradaConsulta);

    // Procesar la consulta
    consulta.procesarConsulta(entradaConsulta);

    // Imprimir los detalles de la consulta
    consulta.imprimirConsulta();

    // Crear la lista de registros y leer el archivo
    std::ListaRegistros lista;
    lista.leerArchivoCSV(consulta.archivo);

    // Imprimir los registros según la consulta
    std::cout << "Resultado de la consulta:" << std::endl;
    lista.imprimirLista();

    return 0;
}
