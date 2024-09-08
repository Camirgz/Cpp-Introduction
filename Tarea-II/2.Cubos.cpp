#include <iostream>

#define MAX_JUEGOS 5
#define MAX_CONJUNTOS 3
#define MAX_CARACTERES 200

using namespace std;

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
void procesarEntrada(const char* entrada, int juegos[MAX_JUEGOS][MAX_CONJUNTOS][3], int& numJuegos) {
    int conjuntoID = 0;
    const char* start = entrada;

    while (conjuntoID < MAX_CONJUNTOS && *start != '\0') {
        int rojos = 0, verdes = 0, azules = 0;
        int cantidad = 0;
        bool enCantidad = false;

        while (*start != '\0' && *start != ';') {
            if (*start >= '0' && *start <= '9') {
                if (!enCantidad) {
                    cantidad = 0;
                    enCantidad = true;
                }
                cantidad = cantidad * 10 + (*start - '0');
            } else {
                if (enCantidad) {
                    enCantidad = false;
                    if (*start == 'r') {
                        if (*(start + 1) == 'o' && *(start + 2) == 'j' && *(start + 3) == 'o') {
                            rojos += cantidad;
                            start += 4;
                        }
                    } else if (*start == 'v') {
                        if (*(start + 1) == 'e' && *(start + 2) == 'r' && *(start + 3) == 'd' && *(start + 4) == 'e') {
                            verdes += cantidad;
                            start += 6;
                        }
                    } else if (*start == 'a') {
                        if (*(start + 1) == 'z' && *(start + 2) == 'u' && *(start + 3) == 'l' && *(start + 4) == 'e') {
                            azules += cantidad;
                            start += 5;
                        }
                    }
                }
            }
            ++start;
        }

        juegos[numJuegos][conjuntoID][0] = rojos;
        juegos[numJuegos][conjuntoID][1] = verdes;
        juegos[numJuegos][conjuntoID][2] = azules;

        if (*start == ';') ++start; // Avanzar el puntero después de ";"
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
    char entrada[MAX_CARACTERES];

    do {
        cout << "\nMenú:" << endl;
        cout << "1. Añadir juego" << endl;
        cout << "2. Mostrar juegos" << endl;
        cout << "3. Calcular juegos válidos" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1: {
                // Añadir un nuevo juego
                if (numJuegos < MAX_JUEGOS) {
                    cout << "Introduce los conjuntos del juego separados por punto y coma. Cada cantidad seguida del color, separados por coma." << endl;
                    cout << "Ejemplo: 3 azul, 4 rojo; 1 rojo, 2 verde, 6 azul; 2 verde" << endl;
                    cout << "Introduce los datos del juego: ";
                    cin.getline(entrada, MAX_CARACTERES);

                    procesarEntrada(entrada, juegos, numJuegos);
                    ++numJuegos;
                } else {
                    cout << "Límite de juegos alcanzado." << endl;
                }
                break;
            }

            case 2: {
                // Mostrar todos los juegos
                for (int i = 0; i < numJuegos; ++i) {
                    cout << "Juego " << (i + 1) << ":" << endl;
                    for (int j = 0; j < MAX_CONJUNTOS; ++j) {
                        cout << "Conjunto " << (j + 1) << ": ";
                        cout << juegos[i][j][0] << " rojos, " << juegos[i][j][1] << " verdes, " << juegos[i][j][2] << " azules" << endl;
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
                
                cout << "La suma de los ID de los juegos posibles es: " << sumaIDPosibles << endl;
                break;
            }

            case 4:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción inválida. Por favor, selecciona una opción válida." << endl;
        }

    } while (opcion != 4);

    return 0;
}
