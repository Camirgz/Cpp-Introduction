#include <iostream>

int main() {
    // Definición de la cantidad máxima de cubos en la bolsa
    const int maxRojos = 12;
    const int maxVerdes = 13;
    const int maxAzules = 14;

    // Definición de los juegos y los cubos revelados en cada conjunto
    int juegos[5][3][3] = {
        {{4, 0, 3}, {1, 2, 6}, {0, 2, 0}},  // Juego 1: 3 conjuntos
        {{1, 2, 1}, {1, 3, 4}, {1, 1, 0}},  // Juego 2: 3 conjuntos
        {{20, 13, 6}, {4, 0, 5}, {1, 5, 0}}, // Juego 3: 3 conjuntos
        {{3, 3, 6}, {6, 3, 0}, {14, 15, 0}}, // Juego 4: 3 conjuntos
        {{1, 2, 6}, {3, 1, 2}, {0, 0, 0}}   // Juego 5: 3 conjuntos
    };

    int sumaIDPosibles = 0; // Para acumular la suma de los ID de los juegos posibles.

    // Procesar cada juego
    for (int juegoID = 0; juegoID < 5; juegoID++) {
        bool esPosible = true;  // Suponemos que el juego es posible

        // Revisamos cada conjunto en el juego
        for (int conjuntoID = 0; conjuntoID < 3; conjuntoID++) {
            int rojos = juegos[juegoID][conjuntoID][0];
            int verdes = juegos[juegoID][conjuntoID][1];
            int azules = juegos[juegoID][conjuntoID][2];

            // Comprobar si algún conjunto sobrepasa la cantidad disponible
            if (rojos > maxRojos || verdes > maxVerdes || azules > maxAzules) {
                esPosible = false;  // Si algún conjunto excede, el juego es imposible
                break;
            }
        }

        // Si el juego es posible, agregamos su ID (juegoID + 1) a la suma total
        if (esPosible) {
            sumaIDPosibles += (juegoID + 1);
        }
    }

    // Imprimir la suma de los ID de los juegos posibles
    std::cout << "La suma de los ID de los juegos posibles es: " << sumaIDPosibles << std::endl;

    return 0;
}
