#include <iostream>

#define MAX_SIZE 10  // Definir un tamaño máximo para la lista

using namespace std;

// Función para transmutar la lista de caracteres
void transmutarLista(char lista[], int tamaño) {
    bool cambiado;

    do {
        cambiado = false;
        for (int i = 0; i < tamaño - 1; ++i) {
            // Transmutar si dos celdas consecutivas son iguales
            if (lista[i] != ' ' && lista[i] == lista[i + 1]) {
                char siguienteLetra = lista[i] + 1;
                if (siguienteLetra > 'K') {
                    siguienteLetra = 'A';  // Volver a 'A' si excede 'K'
                }
                lista[i] = siguienteLetra;
                lista[i + 1] = ' '; // Dejar la segunda celda vacía
                cambiado = true;
                break;  // Solo se realiza una transmutación por iteración
            }
        }
    } while (cambiado);  // Continuar mientras haya transmutaciones

    // Reorganizar la lista para mover todas las letras al principio
    int j = 0;
    for (int i = 0; i < tamaño; ++i) {
        if (lista[i] != ' ' && lista[i] != '\0') {
            lista[j++] = lista[i];
        }
    }
    while (j < tamaño) {
        lista[j++] = ' ';
    }
}

// Función para imprimir la lista
void imprimirLista(const char lista[], int tamaño) {
    for (int i = 0; i < tamaño; ++i) {
        cout << "[" << lista[i] << "] ";
    }
    cout << endl;
}

int main() {
    char lista[MAX_SIZE];
    int tamaño;

    cout << "Introduce el tamaño de la lista (máximo " << MAX_SIZE << "): ";
    cin >> tamaño;
    cin.ignore(); // Limpiar el buffer de entrada

    if (tamaño > MAX_SIZE) {
        cout << "El tamaño excede el máximo permitido. Se ajustará a " << MAX_SIZE << "." << endl;
        tamaño = MAX_SIZE;
    }

    cout << "Introduce los elementos de la lista (A-K o espacio en blanco): " << endl;
    for (int i = 0; i < tamaño; ++i) {
        cin >> lista[i];
    }

    // Transmutar la lista
    transmutarLista(lista, tamaño);

    // Imprimir la lista después de la transmutación
    cout << "Lista después de la transmutación:" << endl;
    imprimirLista(lista, tamaño);

    return 0;
}
