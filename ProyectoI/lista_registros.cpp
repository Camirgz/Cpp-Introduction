// lista_registros.cpp
#include "registro.h"
#include <fstream>
#include <sstream>

namespace std {
    class ListaRegistros {
    public:
        Registro* cabeza;

        // Constructor para inicializar la lista
        ListaRegistros() : cabeza(nullptr) {}

        // Método para leer el archivo CSV y crear registros dinámicamente
        void leerArchivoCSV(const std::string& rutaArchivo) {
            std::ifstream archivo(rutaArchivo);
            if (!archivo.is_open()) {
                std::cerr << "No se pudo abrir el archivo." << std::endl;
                return;
            }

            std::string linea;
            bool esPrimeraLinea = true;
            int numColumnas = 0;
            Registro* actual = nullptr;

            // Leer el archivo línea por línea
            while (getline(archivo, linea)) {
                std::stringstream ss(linea);
                std::string valor;

                // Si es la primera línea, contamos las columnas (encabezados)
                if (esPrimeraLinea) {
                    while (getline(ss, valor, ',')) {
                        numColumnas++;
                    }
                    esPrimeraLinea = false;
                    continue;
                }

                // Crear un nuevo objeto Registro con el número de columnas
                Registro* nuevoRegistro = new Registro(numColumnas);

                // Volver a procesar la línea para asignar los valores
                ss.clear();
                ss.str(linea);
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
        void imprimirLista() const {
            Registro* actual = cabeza;
            while (actual != nullptr) {
                actual->imprimir();
                actual = actual->siguiente; // Pasar al siguiente nodo
            }
        }
    };
}
