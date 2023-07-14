#include <iostream>
#include <random>
#include <omp.h>

int main() {
    int numThreads;
    int numPontos;
    int numPontosCirculo = 0;

    std::cout << "Digite o numero de threads: ";
    std::cin >> numThreads;

    std::cout << "Digite o numero de pontos a serem gerados por thread: ";
    std::cin >> numPontos;

    // Inicialização do gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // Início da região paralela
    #pragma omp parallel num_threads(numThreads)
    {
        int pontosCirculoLocal = 0;

        // Gerar pontos aleatórios e contar quantos estão dentro do círculo
        #pragma omp for
        for (int i = 0; i < numThreads * numPontos; i++) {
            double x = dis(gen);
            double y = dis(gen);

            if (x * x + y * y <= 1) {
                pontosCirculoLocal++;
            }
        }

        // Adicionar pontos do thread local à variável compartilhada
        #pragma omp atomic
        numPontosCirculo += pontosCirculoLocal;
    }
    // Fim da região paralela

    // Calcular o valor estimado de π
    double pi = 4.0 * numPontosCirculo / (numThreads * numPontos);

    std::cout << "O valor estimado de pi é: " << pi << std::endl;

    return 0;
}
