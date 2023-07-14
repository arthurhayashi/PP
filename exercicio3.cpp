#include <iostream>
#include <omp.h>

using namespace std;
// Função para calcular o máximo divisor comum (MDC)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para obter a fração irreduzível
std::pair<int, int> makeFractionIrreducible(int num1, int num2) {
    int divisor = gcd(num1, num2);
    return std::make_pair(num1 / divisor, num2 / divisor);
}
// Função para obter a soma dos divisores do número desejado
int sumfividors(int num){
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= num; i++) {
        for (int j = num; j >= 1; j--) {
            if (i*j == num && i != j) {
                sum += i + j;
            }
        }
    }
    return sum/2;
}

int main() {
    int num1, num2;
    cout << "Digite dois numeros para comparar" << endl;
    std::cin >> num1 >> num2;
    int sum1 = sumfividors(num1);
    int sum2 = sumfividors(num2);
    std::pair<int, int> fraction1 = makeFractionIrreducible(sum1, num1);
    std::pair<int, int> fraction2 = makeFractionIrreducible(sum2, num2);

    if (fraction1 == fraction2) {
        std::cout << "Sao numeros amigos" << std::endl;
    } else {
        std::cout << "Nao sao numeros amigos" << std::endl;
    }

    return 0;
}
