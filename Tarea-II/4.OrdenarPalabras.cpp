#include <iostream>

#define MAX_NODOS 10
#define MAX_CLAVE 100
#define MAX_VALOR 256

using namespace std;

struct Nodo {
    char clave[MAX_CLAVE];
    char valor[MAX_VALOR];

    Nodo() {}
    Nodo(const char* c, const char* v) {
        // Copiar clave
        int i = 0;
        while (c[i] != '\0' && i < MAX_CLAVE - 1) {
            clave[i] = c[i];
            ++i;
        }
        clave[i] = '\0';

        // Copiar valor
        int j = 0;
        while (v[j] != '\0' && j < MAX_VALOR - 1) {
            valor[j] = v[j];
            ++j;
        }
        valor[j] = '\0';
    }
};

// Función para imprimir los nodos
void imprimirNodos(Nodo nodos[], int numNodos) {
    for (int i = 0; i < numNodos; ++i) {
        cout << nodos[i].clave << ": " << nodos[i].valor << endl;
    }
}

// Función de comparación para ordenar por clave (de la Z a la A)
bool compararPorClave(const Nodo& a, const Nodo& b) {
    int i = 0;
    while (a.clave[i] != '\0' && b.clave[i] != '\0') {
        if (a.clave[i] > b.clave[i]) return true;  // Orden descendente
        if (a.clave[i] < b.clave[i]) return false; // Orden ascendente
        ++i;
    }
    // Si una clave es un prefijo de la otra, la más corta debe ir después
    return a.clave[i] != '\0' && b.clave[i] == '\0';
}

// Función de ordenación por burbuja
void ordenarNodos(Nodo nodos[], int numNodos) {
    for (int i = 0; i < numNodos - 1; ++i) {
        for (int j = 0; j < numNodos - i - 1; ++j) {
            if (compararPorClave(nodos[j], nodos[j + 1])) {
                // Intercambiar nodos[j] y nodos[j + 1]
                Nodo temp = nodos[j];
                nodos[j] = nodos[j + 1];
                nodos[j + 1] = temp;
            }
        }
    }
}

int main() {
    Nodo nodos[MAX_NODOS];
    int numNodos;

    cout << "Introduce el número de nodos (máximo " << MAX_NODOS << "): ";
    cin >> numNodos;
    cin.ignore(); // Limpiar el buffer de entrada

    if (numNodos > MAX_NODOS) {
        cout << "El número de nodos excede el máximo permitido. Se ajustará a " << MAX_NODOS << "." << endl;
        numNodos = MAX_NODOS;
    }

    for (int i = 0; i < numNodos; ++i) {
        cout << "Nodo " << (i + 1) << endl;

        cout << "Introduce la clave (palabra): ";
        cin.getline(nodos[i].clave, MAX_CLAVE);

        cout << "Introduce el valor (definición): ";
        cin.getline(nodos[i].valor, MAX_VALOR);
    }

    // Imprimir nodos antes de ordenar
    cout << "\nAntes de ordenar:" << endl;
    imprimirNodos(nodos, numNodos);

    // Ordenar los nodos por clave (palabra) en orden descendente
    ordenarNodos(nodos, numNodos);

    // Imprimir nodos después de ordenar
    cout << "\nDespués de ordenar:" << endl;
    imprimirNodos(nodos, numNodos);

    return 0;
}
