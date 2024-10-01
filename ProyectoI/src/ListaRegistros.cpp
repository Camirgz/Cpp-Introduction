#include "../include/ListaRegistros.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Método para leer el archivo CSV y crear registros dinámicamente
void ListaRegistros::leerArchivoCSV(const string &rutaArchivo)
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
void ListaRegistros::imprimirLista(int numcolumnas, string *columnas, bool imprimirTodas) const
{
    if (imprimirTodas)
    {
        Registro *actual = cabeza;
        while (actual != nullptr)
        {
            actual->imprimir();
            actual = actual->siguiente;
        }
    }
    else
    {
        // Imprimir las columnas seleccionadas
        for (int i = 0; i < numcolumnas; ++i)
        {
            // Imprimir el nombre de la columna
            cout << columnas[i] << "\n"
                 << endl;

            Registro *actual = cabeza;

            // Encontrar la columna seleccionada en la primera línea
            int contador = 0;
            for (int j = 0; j < numcolumnas; ++j)
            {
                // Si el valor de la columna no es igual a la columna seleccionada se aumenta el contador
                if (actual->valores[j] != columnas[i])
                {
                    contador++;
                }
                else
                {
                    break;
                }
            }

            // Saltarse la primera línea
            actual = actual->siguiente;

            // Imprimir los registros uno por uno usando el contador para saber qué columna imprimir
            while (actual != nullptr)
            {
                actual->imprimir2(contador);
                actual = actual->siguiente;
            }

            cout << endl;
        }
    }
}

Registro *cabeza; // Puntero a la cabeza de la lista enlazada

// Método para obtener los valores de una columna específica
string *obtenerValoresColumna(const string &nombreColumna, int &tamanio)
{
    if (cabeza == nullptr)
    {
        return nullptr; // Si la lista está vacía, retornar nullptr
    }

    // Encontrar el índice de la columna
    Registro *actual = cabeza;
    int indiceColumna = -1;

    for (int i = 0; i < actual->numColumnas; ++i)
    {
        if (actual->valores[i] == nombreColumna)
        {
            indiceColumna = i;
            break;
        }
    }

    if (indiceColumna == -1)
    {
        cerr << "Error: Columna no encontrada." << endl;
        return nullptr;
    }

    // Contar el número de registros (filas)
    int totalFilas = 0;
    actual = actual->siguiente; // Saltarse la primera fila (cabecera)
    while (actual != nullptr)
    {
        totalFilas++;
        actual = actual->siguiente;
    }

    // Crear el array para almacenar los valores
    string *valoresColumna = new string[totalFilas];
    actual = cabeza->siguiente; // Saltarse la cabecera

    int fila = 0;
    while (actual != nullptr)
    {
        valoresColumna[fila++] = actual->valores[indiceColumna];
        actual = actual->siguiente;
    }

    tamanio = totalFilas; // Devolver el tamaño del array
    return valoresColumna;
};

#include <iostream>
#include <string>
using namespace std;

class ListaRegistros {
public:
    // Método para obtener los nombres de las columnas solicitadas
    string* obtenerColumnas(const string& consultaSQL, int& numColumnas) {
        // Posicionar el puntero justo después de 'SELECT'
        size_t inicioCols = consultaSQL.find("SELECT");
        if (inicioCols == string::npos) {
            cerr << "Error: Consulta inválida." << endl;
            return nullptr;
        }

        // Saltar cualquier variación como DISTINCT o funciones (MIN, MAX, etc.)
        inicioCols = consultaSQL.find_first_not_of(" ", inicioCols + 6);
        
        // Manejar funciones como MIN, MAX, COUNT, SUM, AVG que podrían aparecer antes de las columnas
        size_t desdePos = consultaSQL.find("FROM", inicioCols);
        if (desdePos == string::npos) {
            cerr << "Error: Consulta inválida." << endl;
            return nullptr;
        }

        // Extraer las columnas entre SELECT y FROM
        string columnas = consultaSQL.substr(inicioCols, desdePos - inicioCols);
        
        // Limpiar y eliminar posibles funciones y paréntesis
        string funciones[] = {"MIN(", "MAX(", "COUNT(", "SUM(", "AVG("};
        for (const string& func : funciones) {
            size_t posFunc = columnas.find(func);
            while (posFunc != string::npos) {
                size_t finFunc = columnas.find(')', posFunc);
                columnas.erase(posFunc, (finFunc - posFunc) + 1);  // Borra toda la función
                posFunc = columnas.find(func);  // Buscar siguiente instancia
            }
        }

        // Separar las columnas por comas
        numColumnas = 1;  // Mínimo una columna
        for (char& ch : columnas) {
            if (ch == ',') {
                numColumnas++;  // Contar el número de columnas
            }
        }

        // Crear el array dinámico para almacenar los nombres de columnas
        string* nombresColumnas = new string[numColumnas];

        // Separar cada columna eliminando espacios en blanco
        size_t posInicio = 0, posComa = 0;
        for (int i = 0; i < numColumnas; ++i) {
            posComa = columnas.find(',', posInicio);
            string columna = columnas.substr(posInicio, posComa - posInicio);
            
            // Eliminar espacios en blanco al inicio y fin
            size_t inicio = columna.find_first_not_of(" ");
            size_t fin = columna.find_last_not_of(" ");
            nombresColumnas[i] = columna.substr(inicio, fin - inicio + 1);

            posInicio = posComa + 1;
        }

        return nombresColumnas;
    }
};

