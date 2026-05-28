# Nombre del programa final
TARGET = mandelbrot_openmp

# Compilador y banderas (flags) de optimizacion y OpenMP
CXX = g++
CXXFLAGS = -fopenmp -O3 -Wall

# Todos los archivos .cpp que se deben compilar juntos
SRCS = main.cpp src/mandelbrot.cpp src/convolution.cpp

# Regla principal: construye el programa
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Regla para limpiar los binarios y volver a empezar
clean:
	rm -f $(TARGET)