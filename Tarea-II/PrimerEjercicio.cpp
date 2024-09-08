#include <iostream>

// Función para calcular la calibración de una línea
int obtenerCalibracion(const char* linea) {
    char primerDigito = '\0';
    char ultimoDigito = '\0';

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

    // Si no se encontraron dígitos, retornar 0
    return 0;
}

int main() {
    const char* lineas[] = {
        "1abc2",
        "pqr3stu8vwx",
        "a1b2c3d4e5f",
        "treb7uchet",
        nullptr 
    };

    int sumaTotal = 0;

    // Procesar cada línea y calcular la suma total
    for (int i = 0; lineas[i] != nullptr; ++i) {
        int calibracion = obtenerCalibracion(lineas[i]);
        std::cout << "Calibración para la línea '" << lineas[i] << "': " << calibracion << std::endl;
        sumaTotal += calibracion;
    }

    std::cout << "Suma total de valores de calibración: " << sumaTotal << std::endl;

    return 0;
}
