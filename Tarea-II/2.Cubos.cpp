#include <iostream>

#define MAX_JUEGOS 5
#define MAX_CONJUNTOS 3
#define MAX_LINEA 200

// Función para calcular si el juego es posible dado un conjunto de cubos
bool esJuegoPosible(int juegos[MAX_JUEGOS][MAX_CONJUNTOS][3], int juegoID, int maxRojos, int maxVerdes, int maxAzules) {
    for (int i = 0; i < MAX_CONJUNTOS; ++i) {
        int rojos = juegos[juegoID][i][0];
        int verdes = juegos[juegoID][i][1];
        int azules = juegos[juegoID][i][2];

        if (rojos > maxRojos || verdes > maxVerdes || azules > maxAzules) {
            return false; // Si algún conjunto excede la cantidad, el juego es imposible
        }
    }
    return true; // Todos los conjuntos son posibles
}

// Función para analizar y extraer los valores de entrada
void procesarEntrada(const std::string& entrada, int juegos[MAX_JUEGOS][MAX_CONJUNTOS][3], int& numJuegos) {
    int conjuntoID = 0;
    size_t start = 0;
    size_t end;

    while (conjuntoID < MAX_CONJUNTOS && (end = entrada.find(';', start)) != std::string::npos) {
        std::string conjunto = entrada.substr(start, end - start);
        size_t colorStart = 0;
        size_t colorEnd;

        while ((colorEnd = conjunto.find(',', colorStart)) != std::string::npos) {
            std::string colorInfo = conjunto.substr(colorStart, colorEnd - colorStart);
            size_t spacePos = colorInfo.find(' ');
            int cantidad = std::stoi(colorInfo.substr(0, spacePos));
            std::string color = colorInfo.substr(spacePos + 1);

            if (color.find("rojo") != std::string::npos) {
                juegos[numJuegos][conjuntoID][0] += cantidad;
            } else if (color.find("verde") != std::string::npos) {
                juegos[numJuegos][conjuntoID][1] += cantidad;
            } else if (color.find("azul") != std::string::npos) {
                juegos[numJuegos][conjuntoID][2] += cantidad;
            }

            colorStart = colorEnd + 1;
        }

        // Procesar el último color
        std::string colorInfo = conjunto.substr(colorStart);
        size_t spacePos = colorInfo.find(' ');
        int cantidad = std::stoi(colorInfo.substr(0, spacePos));
        std::string color = colorInfo.substr(spacePos + 1);

        if (color.find("rojo") != std::string::npos) {
            juegos[numJuegos][conjuntoID][0] += cantidad;
        } else if (color.find("verde") != std::string::npos) {
            juegos[numJuegos][conjuntoID][1] += cantidad;
        } else if (color.find("azul") != std::string::npos) {
            juegos[numJuegos][conjuntoID][2] += cantidad;
        }

        start = end + 1;
        ++conjuntoID;
    }
}

int main() {
    const int maxRojos = 12;
    const int maxVerdes = 13;
    const int maxAzules = 14;

    int juegos[MAX_JUEGOS][MAX_CONJUNTOS][3] = {0}; // Inicializar con ceros
    int numJuegos = 0;
    int opcion;
    std::string entrada;

    do {
        std::cout << "\nMenú:" << std::endl;
        std::cout << "1. Añadir juego" << std::endl;
        std::cout << "2. Mostrar juegos" << std::endl;
        std::cout << "3. Calcular juegos válidos" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Selecciona una opción: ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1: {
                // Añadir un nuevo juego
                if (numJuegos < MAX_JUEGOS) {
                    std::cout << "Introduce los conjuntos del juego separados por punto y coma. Cada cantidad seguida del color, separados por coma." << std::endl;
                    std::cout << "Ejemplo: 3 azul, 4 rojo; 1 rojo, 2 verde, 6 azul; 2 verde" << std::endl;
                    std::cout << "Introduce los datos del juego: ";
                    std::getline(std::cin, entrada);

                    procesarEntrada(entrada, juegos, numJuegos);
                    ++numJuegos;
                } else {
                    std::cout << "Límite de juegos alcanzado." << std::endl;
                }
                break;
            }

            case 2: {
                // Mostrar todos los juegos
                for (int i = 0; i < numJuegos; ++i) {
                    std::cout << "Juego " << (i + 1) << ":" << std::endl;
                    for (int j = 0; j < MAX_CONJUNTOS; ++j) {
                        std::cout << "Conjunto " << (j + 1) << ": ";
                        std::cout << juegos[i][j][0] << " rojos, " << juegos[i][j][1] << " verdes, " << juegos[i][j][2] << " azules" << std::endl;
                    }
                }
                break;
            }

            case 3: {
                // Calcular y mostrar juegos válidos
                int sumaIDPosibles = 0;
                
                for (int i = 0; i < numJuegos; ++i) {
                    if (esJuegoPosible(juegos, i, maxRojos, maxVerdes, maxAzules)) {
                        sumaIDPosibles += (i + 1);
                    }
                }
                
                std::cout << "La suma de los ID de los juegos posibles es: " << sumaIDPosibles << std::endl;
                break;
            }

            case 4:
                std::cout << "Saliendo del programa." << std::endl;
                break;

            default:
                std::cout << "Opción inválida. Por favor, selecciona una opción válida." << std::endl;
        }

    } while (opcion != 4);

    return 0;
}
