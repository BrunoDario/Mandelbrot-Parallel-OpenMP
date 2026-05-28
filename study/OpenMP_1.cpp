#include <iostream>
#include <omp.h>
#include <unistd.h>

int main(){
    long long suma_total = 0;


    double tiempo_inicio = omp_get_wtime();


    #pragma omp parallel for reduction(+:suma_total) schedule(guided, 10)
    for (int i=1; i <= 10000000; i++){

        if (i > 80){
            usleep(10000);
        }

        suma_total += i * i;
    }

    double tiempo_final = omp_get_wtime();
    double tiempo_total = tiempo_final - tiempo_inicio;


    std::cout << "La suma de los cuadrados es: " << suma_total << "\n";
    std::cout << "Tiempo de ejecucion: " << tiempo_total << " segundos.\n";
    return 0;
}