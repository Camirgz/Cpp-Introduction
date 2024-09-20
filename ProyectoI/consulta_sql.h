// consulta_sql.h
#ifndef CONSULTA_SQL_H
#define CONSULTA_SQL_H

#include <iostream>
#include <string>

namespace std {
    class ConsultaSQL {
    public:
        string archivo;            // Nombre del archivo extraído de la consulta
        string columnas[10];       // Arreglo para almacenar hasta 10 columnas
        int numColumnas;           // Número de columnas seleccionadas
        bool seleccionarTodas;     // Bandera para indicar si se seleccionan todas las columnas

        // Constructor
        ConsultaSQL() : numColumnas(0), seleccionarTodas(false) {}

        // Método para procesar la consulta SQL
        void procesarConsulta(const string& consulta) {
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
                    columnas[numColumnas++] = columnasStr.substr(start, end - start);
                    start = end + 2;  // Avanzar después de la coma y el espacio
                }
                // Última columna (o única columna si no hay comas)
                columnas[numColumnas++] = columnasStr.substr(start);
            }

            // Extraer el nombre del archivo después de FROM
            archivo = consulta.substr(posFrom + 6); // 6 caracteres de " FROM "
        }

        // Método para imprimir los detalles de la consulta
        void imprimirConsulta() const {
            cout << "Archivo: " << archivo << endl;
            if (seleccionarTodas) {
                cout << "Columnas: Todas (*)" << endl;
            } else {
                cout << "Columnas seleccionadas: ";
                for (int i = 0; i < numColumnas; ++i) {
                    cout << columnas[i];
                    if (i < numColumnas - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
    };
}

#endif
