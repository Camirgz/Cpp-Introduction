#include <iostream>
#include <string>

const int MAX_SIZE = 100; // Definimos un tamaño máximo para el arreglo

void transmutarAK(std::string input[], int size) {
    std::string result[MAX_SIZE] = { " " }; // Arreglo para almacenar el resultado
    bool transmuted[MAX_SIZE] = { false }; // Marcar celdas transmutadas
    int index = 0;

    for (int i = 0; i < size; ++i) {
        if (i < size - 1 && input[i] == input[i + 1] && !transmuted[i] && !transmuted[i + 1]) {
            // Transmutar
            char nextChar = input[i][0] + 1; // Siguiente letra
            result[index++] = std::string(1, nextChar);
            transmuted[i] = true;
            transmuted[i + 1] = true;
            i++; // Saltar la siguiente celda que ya fue transmutada
        } else if (!transmuted[i]) {
            // Mantener el carácter si no fue transmutado
            result[index++] = input[i];
        }
    }

    // Reorganizar letras al inicio
    std::string finalResult[MAX_SIZE] = { " " };
    for (int i = 0; i < index; ++i) {
        finalResult[i] = result[i];
    }

    // Si no hubo transmutación ni reordenamiento, imprimir lista vacía
    if (index == 0) {
        std::cout << "Resultado: []" << std::endl;
        return;
    }

    // Imprimir el resultado final
    std::cout << "Resultado: [";
    for (int i = 0; i < size; ++i) {
        if (finalResult[i] != " ") {
            std::cout << finalResult[i];
            if (i < size - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::string input[MAX_SIZE];
    int size;

    std::cout << "Ingrese el número de elementos (máximo " << MAX_SIZE << "): ";
    std::cin >> size;

    std::cout << "Ingrese los elementos (letras de 'A' a 'K' o espacios):" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cin >> input[i];
    }

    transmutarAK(input, size);

    return 0;
}