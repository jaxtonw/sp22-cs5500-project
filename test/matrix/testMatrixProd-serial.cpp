#include "../../src/matrix/matrixProd-serial.h"
#include "../../src/common/helpers.h"

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
