#include <iostream>
#include <cmath>
#include <omp.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

double calcularPi(double a, double b, int numIntervalos) {
    double h = (b - a) / numIntervalos;
    double soma = 0.0;

    #pragma omp parallel for reduction(+:soma)
    for (int i = 0; i < numIntervalos; i++) {
        double x1 = a + i * h;
        double x2 = a + (i + 1) * h;
        double area = (f(x1) + f(x2)) * h / 2.0;
        soma += area;
    }

    return soma;
}

int main() {
    double a = 0.0;  // Limite inferior
    double b = 1.0;  // Limite superior
    int numIntervalos;

    std::cout << "Digite o numero de intervalos: ";
    std::cin >> numIntervalos;

    double pi = calcularPi(a, b, numIntervalos);

    std::cout << "O valor de pi é: " << pi << std::endl;

    return 0;
}
