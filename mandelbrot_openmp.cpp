#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

// Dimensiones configurables (Cambia a 7680 y 4320 para el 8K final)
const int WIDTH = 7680;  
const int HEIGHT = 4320; 
const int MAX_ITER = 300; // Máximo de iteraciones para Mandelbrot

struct Pixel {
    unsigned char r, g, b;
};

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

// Función auxiliar para guardar el archivo final en formato PPM
void guardarImagenPPM(const std::string& nombreArchivo, const std::vector<Pixel>& imagen) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    archivo << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
    archivo.write((char*)imagen.data(), imagen.size() * sizeof(Pixel));
}

int main() {
    std::cout << "Iniciando procesamiento secuencial (" << WIDTH << "x" << HEIGHT << ")..." << std::endl;
    
    // Almacenamiento de las imágenes en memoria
    std::vector<Pixel> imgOriginal(WIDTH * HEIGHT);
    std::vector<Pixel> imgFiltrada(WIDTH * HEIGHT);

    // Medición de la Tarea A
    auto startA = std::chrono::high_resolution_clock::now();
    generarMandelbrot(imgOriginal);
    auto endA = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffA = endA - startA;
    std::cout << "-> Tarea A (Mandelbrot) completada en: " << diffA.count() << " segundos." << std::endl;

    // Medición de la Tarea B
    auto startB = std::chrono::high_resolution_clock::now();
    aplicarFiltroConvolucion(imgOriginal, imgFiltrada);
    auto endB = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffB = endB - startB;
    std::cout << "-> Tarea B (Convolucion) completada en: " << diffB.count() << " segundos." << std::endl;

    // Guardar los resultados finales en el disco
    guardarImagenPPM("mandelbrot_original.ppm", imgOriginal);
    guardarImagenPPM("mandelbrot_filtrado.ppm", imgFiltrada);
    
    std::cout << "¡Proceso terminado! Imagenes guardadas exitosamente." << std::endl;
    return 0;
}