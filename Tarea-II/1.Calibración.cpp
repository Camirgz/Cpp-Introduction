#include <iostream>

#define MAX_LINEAS 100
#define LONGITUD_MAX 100

// Función para calcular la calibración de una línea
int obtenerCalibracion(char* linea) {
    char primerDigito = '\0';
    char ultimoDigito = '\0'; // Especificar que es 0 (número)

    // Encontrar el primer dígito
    for (int i = 0; linea[i] != '\0'; ++i) {
        if (linea[i] >= '0' && linea[i] <= '9') {  // Verificar si es un dígito
            primerDigito = linea[i];
            break;
        }
    }

    // Encontrar el último dígito
    for (int i = 0; linea[i] != '\0'; ++i) {
        if (linea[i] >= '0' && linea[i] <= '9') {
            ultimoDigito = linea[i];
        }
    }

    // Si se encontraron ambos dígitos, combinar para formar el número de dos dígitos
    if (primerDigito != '\0' && ultimoDigito != '\0') {
        int numeroCalibrado = (primerDigito - '0') * 10 + (ultimoDigito - '0');
        return numeroCalibrado;
    }

    return 0;
}

int main() {
    char lineas[MAX_LINEAS][LONGITUD_MAX];
    int numLineas = 0;
    int opcion;
    int sumaTotal = 0;

    std::cout << "--- Bienvenido al programa de calibración ---" << std::endl;

    do {
        std::cout << "\nMenú:" << std::endl;
        std::cout << "1. Añadir línea" << std::endl;
        std::cout << "2. Mostrar líneas" << std::endl;
        std::cout << "3. Realizar calibraciones" << std::endl;
        std::cout << "4. Reiniciar líneas" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Selecciona una opción: ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                if (numLineas < MAX_LINEAS) {
                    std::cout << "Introduce una línea: ";
                    std::cin.getline(lineas[numLineas], LONGITUD_MAX);
                    ++numLineas;
                } else {
                    std::cout << "Límite de líneas alcanzado." << std::endl;
                }
                break;

            case 2:
                std::cout << "Líneas almacenadas:" << std::endl;
                for (int i = 0; i < numLineas; ++i) {
                    std::cout << i + 1 << ". " << lineas[i] << std::endl;
                }
                break;
            
            case 3:
                sumaTotal = 0; // Reiniciar suma total para nuevas calibraciones
                for (int i = 0; i < numLineas; ++i) {
                    int calibracion = obtenerCalibracion(lineas[i]);
                    std::cout << "Calibración para la línea '" << lineas[i] << "': " << calibracion << std::endl;
                    sumaTotal += calibracion;
                }
                std::cout << "Suma total de valores de calibración: " << sumaTotal << std::endl;
                break;

            case 4:
                numLineas = 0; // Reiniciar el contador de líneas
                std::cout << "Las líneas han sido reiniciadas." << std::endl;
                break;

            case 5:
                std::cout << "--- Gracias! ---" << std::endl;
                break;

            default:
                std::cout << "Opción inválida. Por favor, selecciona una opción válida." << std::endl;
        }

    } while (opcion != 5);

    return 0;
}
