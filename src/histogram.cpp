#include "../include/histogram.h"
#include <omp.h>
#include <iostream>

//Implementation using Atomic
void calculateHistogramAtomic(const std::vector<Pixel>& image){
    int histogramRed[256] = {0};
    int histogramGreen[256] = {0};
    int histogramBlue[256] = {0};

    #pragma omp parallel for
    for (size_t i = 0; i < image.size(); i++){
        int red = image[i].r;
        int green = image[i].g;
        int blue = image[i].b;

        #pragma omp atomic
        histogramRed[red]++;

        #pragma omp atomic
        histogramGreen[green]++;

        #pragma omp atomic
        histogramBlue[blue]++;
    }
}


//Implementation using Local Variables
void calculateHistogramReduction(const std::vector<Pixel>& image){
    int histogramRed[256] = {0};
    int histogramGreen[256] = {0};
    int histogramBlue[256] = {0};

    #pragma omp parallel for reduction(+:histogramRed[:256], histogramGreen[:256], histogramBlue[:256])
    for (size_t i = 0; i < image.size(); i++){
        int red = image[i].r;
        int green = image[i].g;
        int blue = image[i].b;

        histogramRed[red]++;
        histogramGreen[green]++;
        histogramBlue[blue]++;
    }
}