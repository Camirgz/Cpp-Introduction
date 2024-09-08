#include <iostream>

#define MAX_RASPAS 6
#define MAX_NUMEROS 5
#define MAX_LINEA 200

using namespace std;

// Función para contar los números ganadores y calcular los puntos
int calcularPuntos(const int ganadores[], const int nuestros[], int numGanadores, int numNuestros) {
    int puntos = 0;
    bool encontrado[MAX_NUMEROS] = {false};

    for (int i = 0; i < numNuestros; ++i) {
        for (int j = 0; j < numGanadores; ++j) {
            if (nuestros[i] == ganadores[j]) {
                if (!encontrado[j]) {
                    puntos += 1;
                    encontrado[j] = true;
                } else {
                    puntos *= 2;
                }
            }
        }
    }

    return puntos;
}

// Función para procesar la entrada y analizar las raspaditas
void procesarRaspaditas() {
    const int numRaspas = MAX_RASPAS;
    int ganadores[MAX_NUMEROS];
    int nuestros[MAX_NUMEROS];
    int numGanadores, numNuestros;
    int totalPuntos = 0;

    for (int i = 0; i < numRaspas; ++i) {
        // Leer y procesar la lista de números ganadores
        cout << "Introduce los números ganadores de la raspa " << (i + 1) << " separados por espacio: ";
        numGanadores = 0;
        while (cin >> ganadores[numGanadores] && numGanadores < MAX_NUMEROS) {
            numGanadores++;
            if (cin.get() == '\n') break;
        }

        // Leer y procesar la lista de nuestros números
        cout << "Introduce tus números para la raspa " << (i + 1) << " separados por espacio: ";
        numNuestros = 0;
        while (cin >> nuestros[numNuestros] && numNuestros < MAX_NUMEROS) {
            numNuestros++;
            if (cin.get() == '\n') break;
        }

        // Calcular los puntos
        int puntos = calcularPuntos(ganadores, nuestros, numGanadores, numNuestros);
        totalPuntos += puntos;

        // Mostrar resultados
        cout << "La tarjeta " << (i + 1) << " tiene " << numGanadores << " números ganadores (";
        for (int j = 0; j < numGanadores; ++j) {
            cout << ganadores[j];
            if (j < numGanadores - 1) cout << ", ";
        }
        cout << ") y " << numNuestros << " números nuestros (";
        for (int j = 0; j < numNuestros; ++j) {
            cout << nuestros[j];
            if (j < numNuestros - 1) cout << ", ";
        }
        cout << "). Por lo que vale " << puntos << " puntos." << endl;
    }

    // Mostrar el total de puntos
    cout << "El total de puntos de la pila de raspaditas es: " << totalPuntos << endl;
}

int main() {
    int opcion;

    do {
        cout << "\nMenú:" << endl;
        cout << "1. Introducir raspaditas y calcular puntos" << endl;
        cout << "2. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                procesarRaspaditas();
                break;

            case 2:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción inválida. Por favor, selecciona una opción válida." << endl;
        }

    } while (opcion != 2);

    return 0;
}
