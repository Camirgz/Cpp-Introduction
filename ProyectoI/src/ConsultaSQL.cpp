#include "../include/ConsultaSQL.h"

using namespace std;
ConsultaSQL ::ConsultaSQL() : numColumnas(0), seleccionarTodas(false) {}

// Método para procesar la consulta SQL
void ConsultaSQL :: procesarConsulta(const string& consulta) {
    
    // Variables de apoyo
    size_t posSelect = consulta.find("SELECT ");
    size_t posFrom = consulta.find(" FROM ");

    if (posSelect == string::npos || posFrom == string::npos) {
        cerr << "Error: La consulta SQL no es válida." << endl;
        return;
    }

    // Extraer las columnas entre SELECT y FROM
    string columnasStr = consulta.substr(posSelect + 7, posFrom - (posSelect + 7));

    

    if (columnasStr == "*") {
        seleccionarTodas = true;
    } else {
        seleccionarTodas = false;
        size_t start = 0;
        size_t end = 0;
        numColumnas = 0;

        // Extraer las columnas separadas por comas
        while ((end = columnasStr.find(", ", start)) != string::npos) {
            columnas[numColumnas] = columnasStr.substr(start, end - start);
            numColumnas++;
            start = end + 2;  // Avanzar después de la coma y el espacio
        }
        // Última columna (o única columna si no hay comas)
        columnas[numColumnas++] = columnasStr.substr(start);
        cout << "\nNumero de columnas: " << numColumnas << endl;
    }

    // Extraer el nombre del archivo después de FROM
    string archivoStr = consulta.substr(posFrom + 6); // 6 caracteres de " FROM "

    // Añadir la ruta de ../db/ al nombre del archivo
    archivo = "../db/" + archivoStr;
}

bool ConsultaSQL :: consulta()  {
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
