#include "../include/mandelbrot.h"


// Tarea A: Generación del Conjunto de Mandelbrot

void generarMandelbrot(std::vector<Pixel>& imagen) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // Mapear las coordenadas del píxel al plano complejo (-2.0 a 1.0, -1.2 a 1.2)
            double cr = -2.0 + (x * 3.0 / WIDTH);
            double ci = -1.2 + (y * 2.4 / HEIGHT);

            double zr = 0.0, zi = 0.0;
            int iter = 0;

            // Algoritmo matemático del fractal
            while (zr * zr + zi * zi <= 4.0 && iter < MAX_ITER) {
                double temp = zr * zr - zi * zi + cr;
                zi = 2.0 * zr * zi + ci;
                zr = temp;
                iter++;
            }

            // Iluminación/Color básico basado en las iteraciones
            int idx = y * WIDTH + x;
            if (iter == MAX_ITER) {
                imagen[idx] = {0, 0, 0}; // Fondo negro si cae dentro del conjunto
            } else {
                // Paleta de colores en degradado azul/blanco
                unsigned char c = (iter * 255) / MAX_ITER;
                imagen[idx] = { (unsigned char)(c * 0.3), (unsigned char)(c * 0.6), c };
            }
        }
    }
}