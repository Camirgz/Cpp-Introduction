// main.cpp
#include "Registro.h"
#include "ListaRegistros.cpp"
#include <iostream>

int main() {
    std::ListaRegistros lista;
    lista.leerArchivoCSV("Personas.csv");  // Ruta del archivo CSV

    // Imprimir la lista completa
    lista.imprimirLista();

    return 0;
}
