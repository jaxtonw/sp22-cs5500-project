#include "../../src/generators/squareMatrices.h"
#include "../../src/generators/vectors.h"

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
    Matrix a = generateRandomMatrix(5);
    Matrix diagA = generateDiagonalMatrix(5);
    Matrix lowerTriangularA = generateLowerTriangularMatrix(5);
    Matrix upperTriangularA = generateUpperTriangularMatrix(5);
    MathVector randomVec = generateRandomVector(5);


    std::cout << "Matrix A (random matrix)" << std::endl;
    printMatrix(a);

    std::cout << "Matrix diagA (random diagonal matrix)" << std::endl;
    printMatrix(diagA);

    std::cout << "Matrix lowerTriangularA (random lower triangular matrix)" << std::endl;
    printMatrix(lowerTriangularA);

    std::cout << "Matrix upperTriangularA (random upper triangular matrix)" << std::endl;
    printMatrix(upperTriangularA);

    std::cout << "Random vector generated:" << std::endl;
    printVector(randomVec);

    return 0;
}