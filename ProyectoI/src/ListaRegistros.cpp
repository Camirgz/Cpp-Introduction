#include "../include/ListaRegistros.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


// Método para leer el archivo CSV y crear registros dinámicamente
void ListaRegistros::leerArchivoCSV(const string &rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    bool esPrimeraLinea = true;
    int numColumnas = 0;
    Registro *actual = nullptr;

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string valor;

        // Si es la primera línea, contamos las columnas (encabezados)
        if (esPrimeraLinea) {
            while (getline(ss, valor, ',')) {
                numColumnas++;
            }
            esPrimeraLinea = false;

            // Resetear el stream para procesar la primera línea de nuevo
            ss.clear();
            ss.str(linea);
        }

        // Crear un nuevo objeto Registro con el número de columnas
        Registro *nuevoRegistro = new Registro(numColumnas);

        // Asignar los valores de la línea actual al nuevo registro
        for (int i = 0; i < numColumnas; ++i) {
            getline(ss, nuevoRegistro->valores[i], ',');
        }

        // Conectar el nuevo registro a la lista
        if (cabeza == nullptr) {
            cabeza = nuevoRegistro; // Primer registro en la lista
        } else {
            actual->siguiente = nuevoRegistro; // Conectar al siguiente nodo
        }
        actual = nuevoRegistro; // Actualizar el puntero actual
    }

    archivo.close();
}

// Método para imprimir toda la lista de registros
void ListaRegistros::imprimirLista(int numcolumnas, string *columnas, bool imprimirTodas) const {
    if (imprimirTodas) {
        Registro *actual = cabeza;
        while (actual != nullptr) {
            actual->imprimir();
            actual = actual->siguiente;
        }
    } else {
        // Imprimir las columnas seleccionadas
        for (int i = 0; i < numcolumnas; ++i) {
            // Imprimir el nombre de la columna
            cout << columnas[i] << ":\n";

            Registro *actual = cabeza;

            // Imprimir los registros uno por uno
            while (actual != nullptr) {
                // Encontrar el índice de la columna seleccionada
                int contador = 0;
                for (int j = 0; j < numcolumnas; ++j) {
                    if (j == i) {
                        cout << actual->valores[j] << endl; // Imprimir valor de la columna seleccionada
                        break;
                    }
                    contador++;
                }
                actual = actual->siguiente;
            }
            cout << endl;
        }
    }
}
