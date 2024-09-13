#include <iostream>
#include <string>

using namespace std;

const int MAX_SIZE = 100; // Definimos un tamaño máximo para el arreglo

void transmutarAK(string input[], int size) {
    string result[MAX_SIZE] = { " " }; // Arreglo para almacenar el resultado
    bool transmuted[MAX_SIZE] = { false }; // Marcar celdas transmutadas
    int index = 0;

    for (int i = 0; i < size; ++i) {
        if (i < size - 1 && input[i] == input[i + 1] && !transmuted[i] && !transmuted[i + 1]) {
            // Transmutar
            char nextChar = input[i][0] + 1; // Siguiente letra
            result[index++] = string(1, nextChar);
            transmuted[i] = true;
            transmuted[i + 1] = true;
            i++; // Saltar la siguiente celda que ya fue transmutada
        } else if (!transmuted[i]) {
            // Mantener el carácter si no fue transmutado
            result[index++] = input[i];
        }
    }

    // Reorganizar letras al inicio
    string finalResult[MAX_SIZE] = { " " };
    for (int i = 0; i < index; ++i) {
        finalResult[i] = result[i];
    }

    // Si no hubo transmutación ni reordenamiento, imprimir lista vacía
    if (index == 0) {
        cout << "Resultado: []" << endl;
        return;
    }

    // Imprimir el resultado final
    cout << "Resultado: [";
    for (int i = 0; i < size; ++i) {
        if (finalResult[i] != " ") {
            cout << finalResult[i];
            if (i < size - 1) {
                cout << ", ";
            }
        }
    }
    cout << "]" << endl;
}

int main() {
    string input[MAX_SIZE];
    int size;

    cout << "Ingrese el número de elementos (máximo " << MAX_SIZE << "): ";
    cin >> size;

    cout << "Ingrese los elementos (letras de 'A' a 'K' o espacios):" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> input[i];
    }

    transmutarAK(input, size);

    return 0;
}
