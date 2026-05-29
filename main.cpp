#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>


// Include the modules
#include "include/utils.h"
#include "include/mandelbrot.h"
#include "include/convolution.h"
#include "include/histogram.h"





// Función auxiliar para guardar el archivo final en formato PPM
void guardarImagenPPM(const std::string& nombreArchivo, const std::vector<Pixel>& imagen) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    archivo << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
    archivo.write((char*)imagen.data(), imagen.size() * sizeof(Pixel));
}

int main() {
    std::cout << "Iniciando procesamiento paralelo (" << WIDTH << "x" << HEIGHT << ")..." << std::endl;
    
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

    // Task C: Histogram
    std::cout<<"\ncalculating Histograms. . ."<< std::endl;

    auto startC = std::chrono::high_resolution_clock::now();
    calculateHistogramAtomic(imgFiltrada);
    auto endC = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffC = endC - startC;
    std::cout<<"-> Histogram (Atomic) completed in: "<< diffC.count() << " seconds."<<std::endl;

    auto startC2 = std::chrono::high_resolution_clock::now();
    calculateHistogramReduction(imgFiltrada);
    auto endC2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffC2 = endC2 - startC2;
    std::cout<<"-> Histogram (Reduction) completed in: "<< diffC2.count() << " seconds."<<std::endl;


    // Guardar los resultados finales en el disco
    guardarImagenPPM("output/mandelbrot_original.ppm", imgOriginal);
    guardarImagenPPM("output/mandelbrot_filtrado.ppm", imgFiltrada);
    
    std::cout << "\n\n¡Proceso terminado! Imagenes guardadas exitosamente." << std::endl;
    return 0;
}