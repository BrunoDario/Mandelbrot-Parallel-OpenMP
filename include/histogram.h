#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include "utils.h"
#include <vector>

void calculateHistogramAtomic(const std::vector<Pixel>& image);
void calculateHistogramReduction(const std::vector<Pixel>& image);

#endif