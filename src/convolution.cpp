#include "../include/convolution.h"

// Tarea B: Filtro de Convolución 2D Pesado (Desenfoque Gaussiano 5x5)
void aplicarFiltroConvolucion(const std::vector<Pixel>& origen, std::vector<Pixel>& destino) {
    // Matriz de desenfoque Gaussiano 5x5 (pesada)
    const float kernel[5][5] = {
        {1/273.f, 4/273.f,  7/273.f,  4/273.f,  1/273.f},
        {4/273.f, 16/273.f, 26/273.f, 16/273.f, 4/273.f},
        {7/273.f, 26/273.f, 41/273.f, 26/273.f, 7/273.f},
        {4/273.f, 16/273.f, 26/273.f, 16/273.f, 4/273.f},
        {1/273.f, 4/273.f,  7/273.f,  4/273.f,  1/273.f}
    };

    // Recorremos la imagen ignorando los bordes exteriores para el kernel 5x5
    for (int y = 2; y < HEIGHT - 2; ++y) {
        for (int x = 2; x < WIDTH - 2; ++x) {
            float sumR = 0, sumG = 0, sumB = 0;

            // Multiplicamos la vecindad de píxeles por el kernel
            for (int ky = -2; ky <= 2; ++ky) {
                for (int kx = -2; kx <= 2; ++kx) {
                    int pixelIdx = (y + ky) * WIDTH + (x + kx);
                    float kVal = kernel[ky + 2][kx + 2];

                    sumR += origen[pixelIdx].r * kVal;
                    sumG += origen[pixelIdx].g * kVal;
                    sumB += origen[pixelIdx].b * kVal;
                }
            }

            int idx = y * WIDTH + x;
            destino[idx] = { (unsigned char)sumR, (unsigned char)sumG, (unsigned char)sumB };
        }
    }
}