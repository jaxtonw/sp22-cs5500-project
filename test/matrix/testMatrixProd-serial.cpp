#include "../../src/matrix/matrixProd-serial.h"

void printVector(std::vector<double> vec)
{
    std::cout << "[";
    for (double item : vec)
    {
        std::cout << "  " << item;
    }
    std::cout << "]" << std::endl;
}

void printMatrix(Matrix a) {
    for (auto v : a) {
        printVector(v);
    }
}

int main() {
    Matrix a(5);
    for (int i = 0; i < 5; i++) {
        a[i] = std::vector<double> {1, 2, 3};
    }

    Matrix b(3);

    for(int i = 0; i < 3; i++) {
        b[i] = std::vector<double> {2, 1};
    }

    std::cout << "Matrix A:" << std::endl;
    printMatrix(a);
    std::cout << "Matrix B:" << std::endl;
    printMatrix(b);

    Matrix result = matrixProductSerial(a, b);

    std::cout << "Matrix A*B:" << std::endl;
    printMatrix(result);

    return 0;
}
