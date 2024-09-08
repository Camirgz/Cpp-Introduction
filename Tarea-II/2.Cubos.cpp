#include <iostream>
#include <string>

#define MAX_JUEGOS 5
#define MAX_CONJUNTOS 3
#define MAX_CARACTERES 200

using namespace std;

// Función para dividir un string por un delimitador
void split(const std::string &str, char delimiter, std::string result[], int &size) {
    size = 0;  // Reiniciamos el tamaño de resultado
    std::string temp = "";
    for (char ch : str) {
        if (ch == delimiter) {
            if (!temp.empty()) {
                result[size++] = temp;  // Añadimos la subcadena a resultado
                temp = "";  // Reiniciamos el temporal
            }
        } else {
            temp += ch;  // Añadimos el caracter a la subcadena temporal
        }
    }
    if (!temp.empty()) {
        result[size++] = temp;  // Añadimos la última subcadena si existe
    }
}

// Función para calcular si el juego es posible dado un conjunto de cubos
bool esJuegoPosible(int juegos[MAX_JUEGOS][MAX_CONJUNTOS][3], int juegoID, int maxRojos, int maxVerdes, int maxAzules) {
    int totalRojos = 0, totalVerdes = 0, totalAzules = 0;

    for (int i = 0; i < MAX_CONJUNTOS; ++i) {
        int rojos = juegos[juegoID][i][0];
        int verdes = juegos[juegoID][i][1];
        int azules = juegos[juegoID][i][2];

        totalRojos += rojos;
        totalVerdes += verdes;
        totalAzules += azules;

        if (totalRojos > maxRojos || totalVerdes > maxVerdes || totalAzules > maxAzules) {
            return false; // Si las cantidades totales exceden, el juego es imposible
        }
    }
    return true; // Todos los conjuntos son posibles
}

// Función para analizar y extraer los valores de entrada
void procesarEntrada(const string &entrada, int juegos[MAX_JUEGOS][MAX_CONJUNTOS][3], int juegoID) {
    string semicolonSplit[10], commaSplit[10], spaceSplit[10];
    int semiSize = 0, commaSize = 0, spaceSize = 0;

    // Dividimos el string por ";"
    split(entrada, ';', semicolonSplit, semiSize);

    // Procesamos cada bloque separado por ";"
    for (int i = 0; i < semiSize && i < MAX_CONJUNTOS; i++) {
        // Dividimos cada bloque por ","
        split(semicolonSplit[i], ',', commaSplit, commaSize);

        int conjuntoRojos = 0, conjuntoVerdes = 0, conjuntoAzules = 0;

        // Procesamos cada sub-bloque separado por ","
        for (int j = 0; j < commaSize; j++) {
            // Dividimos por espacio para separar la cantidad del color
            split(commaSplit[j], ' ', spaceSplit, spaceSize);

            if (spaceSize == 2) {  // Comprobamos que haya cantidad y color
                int quantity = std::stoi(spaceSplit[0]);  // Convertimos la cantidad a entero
                std::string color = spaceSplit[1];

                if (color == "azul" || color == "azules") {
                    conjuntoAzules += quantity;  // Sumamos la cantidad
                } else if (color == "rojo" || color == "rojos") {
                    conjuntoRojos += quantity;
                } else if (color == "verde" || color == "verdes") {
                    conjuntoVerdes += quantity;
                }
            } else {
                // Input inválido si no hay cantidad o color
                cout << "Formato de entrada inválido." << endl;
                return;
            }
        }

        // Añadimos los valores del conjunto al juego
        juegos[juegoID][i][0] = conjuntoRojos;
        juegos[juegoID][i][1] = conjuntoVerdes;
        juegos[juegoID][i][2] = conjuntoAzules;
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
                    cout << "Juego añadido exitosamente." << endl;
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
