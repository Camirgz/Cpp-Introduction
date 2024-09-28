#include "../include/ConsultaSQL.h"

using namespace std;

ConsultaSQL::ConsultaSQL() : numColumnas(0), seleccionarTodas(false) {}

// Método para procesar la consulta SQL
void ConsultaSQL::procesarConsulta(const string& consulta) {
    
    // Variables de apoyo
    size_t posSelect = consulta.find("SELECT ");
    size_t posFrom = consulta.find(" FROM ");
    size_t posDistinct = consulta.find("SELECT DISTINCT ");
    size_t posMin = consulta.find("SELECT MIN");
    size_t posMax = consulta.find("SELECT MAX");
    size_t posCount = consulta.find("SELECT COUNT");
    size_t posSum = consulta.find("SELECT SUM");
    size_t posAvg = consulta.find("SELECT AVG");
    string comando;

    string columnasStr = "";

    if (posSelect == string::npos || posFrom == string::npos) {
        cerr << "Error: La consulta SQL no es válida." << endl;
        return;
    }
    string archivoStr = consulta.substr(posFrom + 6); // 6 caracteres de " FROM "

    // Añadir la ruta de ../db/ al nombre del archivo
    archivo = "../db/" + archivoStr;

    lista.leerArchivoCSV(archivo);
    
    if (posDistinct != string::npos) {
        columnasStr = consulta.substr(posSelect + 16, posFrom - (posSelect + 16));    
        procesarDistinct(columnasStr);  // Llamar al método para manejar DISTINCT
        return;
    }  
    else if (posMin != string::npos) {
         columnasStr = consulta.substr(posSelect + 10, posFrom - (posSelect + 10));    

    } else if (posMax != string::npos) {
         columnasStr = consulta.substr(posSelect + 10, posFrom - (posSelect + 10));    
    } else if (posCount != string::npos) {
         columnasStr = consulta.substr(posSelect + 12, posFrom - (posSelect + 12));    
    } else if (posSum != string::npos) {
         columnasStr = consulta.substr(posSelect + 10, posFrom - (posSelect + 10));    
    } else if (posAvg != string::npos) {
         columnasStr  = consulta.substr(posSelect + 10, posFrom - (posSelect + 10));    
    } 


    // Extraer las columnas entre SELECT y FROM
    columnasStr = consulta.substr(posSelect + 7, posFrom - (posSelect + 7));

    if (columnasStr == "*") {
        seleccionarTodas = true;
        numColumnas = 0; // No necesitamos contar las columnas si seleccionamos todas
    } else {
        seleccionarTodas = false;
        size_t start = 0;
        size_t end = 0;
        numColumnas = 0;

        // Extraer las columnas individuales
        while ((end = columnasStr.find(",", start)) != string::npos) {
            columnas[numColumnas++] = columnasStr.substr(start, end - start);
            start = end + 1;  // Avanzar al siguiente carácter después de la coma
        }
        columnas[numColumnas++] = columnasStr.substr(start); // Para la última columna
    }
    
    cout << "columnasStr: " << columnasStr << " num columnas " << numColumnas << endl;
    for (int i = 0; i < numColumnas; ++i) {
        cout << "columnas[" << i << "]: " << columnas[i] << endl;
    }
    lista.imprimirLista(numColumnas, columnas, seleccionarTodas);
}

void ConsultaSQL::procesarDistinct(const std::string& columnasStr) {
    const int MAX_UNICOS = 1000;  // Límite de valores únicos
    std::string valoresUnicos[MAX_UNICOS]; // Arreglo estático para almacenar filas únicas
    int totalUnicos = 0;  // Contador de filas únicas almacenadas

    // Comprobar si se seleccionaron todas las columnas
    if (columnasStr == "*") {
        seleccionarTodas = true;
    } else {
        seleccionarTodas = false;

        // Extraer columnas individuales
        size_t start = 0;
        size_t end = 0;
        numColumnas = 0;

        while ((end = columnasStr.find(",", start)) != std::string::npos) {
            columnas[numColumnas++] = columnasStr.substr(start, end - start);
            start = end + 2;  // Avanzar al siguiente carácter después de la coma
        }
        columnas[numColumnas++] = columnasStr.substr(start); // Para la última columna
    }

    // Obtener los nombres de las columnas desde la cabeza
    if (lista.cabeza != nullptr) {
        Registro* cabeza = lista.cabeza;
        for (int i = 0; i < cabeza->numColumnas; ++i) {
            std::string nombreColumna = cabeza->valores[i];
            // Aquí se pueden almacenar los nombres de las columnas si es necesario
        }
    }

    // Recorrer los registros y extraer valores únicos
    Registro* actual = lista.cabeza; // Comenzamos desde la cabeza
    while (actual != nullptr) {
        // Crear una cadena que represente la fila actual
        std::string filaActual;
        for (int i = 0; i < actual->numColumnas; ++i) {
            filaActual += actual->valores[i] + "|"; // Usar un delimitador para unir los valores
        }

        // Verificar si la fila actual ya está en el arreglo de valores únicos
        bool esDuplicado = false;
        for (int j = 0; j < totalUnicos; ++j) {
            if (valoresUnicos[j] == filaActual) {
                esDuplicado = true;
                break;
            }
        }

        // Si no es duplicado, lo agregamos al arreglo y lo imprimimos
        if (!esDuplicado && totalUnicos < MAX_UNICOS) {
            valoresUnicos[totalUnicos++] = filaActual;
            std::cout << filaActual << std::endl; // Imprimir la fila completa
        }

        actual = actual->siguiente; // Avanzamos al siguiente registro
    }
}



bool ConsultaSQL::consulta() {
    cout << "Archivo: " << archivo << endl;
    if (seleccionarTodas) {
        cout << "Columnas: Todas (*)" << endl;
    } else {
        cout << "Columnas seleccionadas: ";
        for (int i = 0; i < numColumnas; ++i) {
            cout << columnas[i] << " ";
        }
        cout << "\n" << endl;
    }
    return true;
}
