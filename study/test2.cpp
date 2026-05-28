#include <iostream>
#include <omp.h>

int main() {
    int cuenta_libros = 0;

    // Ponemos a trabajar a todos los hilos sobre la misma variable compartida
    #pragma omp parallel for
    for (int i = 0; i < 100000; i++) {
        cuenta_libros++; // <- ¡Peligro! Condición de carrera pura
    }

    std::cout << "Libros contados: " << cuenta_libros << " (Deberían ser 100000)\n";
    return 0;
}