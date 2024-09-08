#include <iostream>
#include <string>

#define MAX_NUMEROS 10

// Función para separar números de una cadena y almacenarlos en un arreglo
void separarNumeros(const std::string& cadena, int numeros[], int& numNumeros) {
    numNumeros = 0;
    std::string temp = "";
    for (char c : cadena) {
        if (c == ' ' || c == '|') {
            if (!temp.empty()) {
                numeros[numNumeros++] = std::stoi(temp);
                temp = "";
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        numeros[numNumeros++] = std::stoi(temp);
    }
}

// Función para calcular los puntos de una raspadita
int calcularPuntos(const int ganadores[], int numGanadores, const int nuestros[], int numNuestros) {
    int puntos = 0;
    bool encontrado[MAX_NUMEROS] = {false};

    // Verificar coincidencias
    for (int i = 0; i < numNuestros; ++i) {
        for (int j = 0; j < numGanadores; ++j) {
            if (nuestros[i] == ganadores[j]) {
                if (!encontrado[j]) {
                    encontrado[j] = true;
                    puntos = (puntos == 0) ? 1 : puntos * 2;
                }
                break;
            }
        }
    }

    return puntos;
}

int main() {
    int ganadores[MAX_NUMEROS];
    int nuestros[MAX_NUMEROS];
    int numGanadores, numNuestros;

    int totalPuntos = 0;
    int opcion;

    do {
        std::cout << "\nMenú:" << std::endl;
        std::cout << "1. Añadir raspadita" << std::endl;
        std::cout << "2. Mostrar total de puntos" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Selecciona una opción: ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer de entrada

        if (opcion == 1) {
            std::string entrada;
            std::cout << "Introduce los números ganadores y los nuestros separados por una barra vertical (|): ";
            std::getline(std::cin, entrada);

            // Separar los números en las listas de ganadores y nuestros
            size_t pos = entrada.find('|');
            if (pos == std::string::npos) {
                std::cout << "Formato de entrada incorrecto." << std::endl;
                continue;
            }

            std::string ganadoresStr = entrada.substr(0, pos);
            std::string nuestrosStr = entrada.substr(pos + 1);

            separarNumeros(ganadoresStr, ganadores, numGanadores);
            separarNumeros(nuestrosStr, nuestros, numNuestros);

            int puntos = calcularPuntos(ganadores, numGanadores, nuestros, numNuestros);
            totalPuntos += puntos;

            std::cout << "\nDetalles de la raspadita:" << std::endl;
            std::cout << "Números ganadores: ";
            for (int i = 0; i < numGanadores; ++i) {
                std::cout << ganadores[i] << " ";
            }
            std::cout << std::endl;

            std::cout << "Nuestros números: ";
            for (int i = 0; i < numNuestros; ++i) {
                std::cout << nuestros[i] << " ";
            }
            std::cout << std::endl;

            std::cout << "Puntos obtenidos: " << puntos << std::endl;
        } else if (opcion == 2) {
            std::cout << "El total de puntos es: " << totalPuntos << std::endl;
        } else if (opcion != 3) {
            std::cout << "Opción inválida. Por favor, selecciona una opción válida." << std::endl;
        }
    } while (opcion != 3);

    return 0;
}
