#include "Registro.h"
#include <fstream>
#include <sstream>

using namespace std;

class ListaRegistros
{
public:
    Registro *cabeza;

    // Constructor para inicializar la lista
    ListaRegistros() : cabeza(nullptr) {}

    // Método para leer el archivo CSV y crear registros dinámicamente
    void leerArchivoCSV(const string &rutaArchivo)
    {
        ifstream archivo(rutaArchivo);
        if (!archivo.is_open())
        {
            cerr << "No se pudo abrir el archivo." << endl;
            return;
        }

        string linea;
        bool esPrimeraLinea = true;
        int numColumnas = 0;
        Registro *actual = nullptr;

        // Leer el archivo línea por línea
        while (getline(archivo, linea))
        {
            stringstream ss(linea);
            string valor;

            // Si es la primera línea, contamos las columnas (encabezados)
            if (esPrimeraLinea)
            {
                while (getline(ss, valor, ','))
                {
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
            for (int i = 0; i < numColumnas; ++i)
            {
                getline(ss, nuevoRegistro->valores[i], ',');
            }

            // Conectar el nuevo registro a la lista
            if (cabeza == nullptr)
            {
                cabeza = nuevoRegistro; // Primer registro en la lista
            }
            else
            {
                actual->siguiente = nuevoRegistro; // Conectar al siguiente nodo
            }
            actual = nuevoRegistro; // Actualizar el puntero actual
        }

        archivo.close();
    }

    // Método para imprimir toda la lista de registros
    void imprimirLista(int numcolumnas, string *columnas) const
    {

        // imprimir las columnas seleccionadas
        for (int i = 0; i < numcolumnas; ++i)
        {
            // imprimir el nombre de la columna
            cout << columnas[i] << "\n"
                 << endl;

            Registro *actual = cabeza;

            // Encontrar la columna seleccionada en la primera linea
            int contador = 0;
            for (int j = 0; j < numcolumnas; ++j)
            {
                // si el valor de la columna no es igual a la columna seleccionada se aumenta el contador
                if (actual->valores[j] != columnas[i])
                {
                    contador++;
                }
                else
                {
                    break;
                }
            }
            // saltarse la primera linea
            actual = actual->siguiente;

            // Imprimir los registros uno por uno usando el contador para saber que columna imprimir
            while (actual != nullptr)
            {
                actual->imprimir2(contador);
                actual = actual->siguiente;
            }
            cout << endl;
        }
        cout << endl;
    }
};
