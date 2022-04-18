#include "../../src/lu/luFact-serial.h"
#include "../../src/generators/squareMatrices.h"
#include "../../src/common/helpers.h"

#define SIZE 8

Matrix serialSquareMatrixProduct(Matrix matrixA, Matrix matrixB) {
    // A and B must be same dimensions and both square
    int N = matrixA.size();
    Matrix myMatrix(N);

    for (int row = 0; row < N; row++) {
        myMatrix[row].resize(N);

        for (int col = 0; col < N; col++) {
            double result = 0;
            for (int k = 0; k < N; k++) {
                result += matrixA[row][k] * matrixB[k][col];
            }
            myMatrix[row][col] = result;
        }
    }

    return myMatrix;
}

int main(int argc, char **argv)
{
    Matrix originalL = generateUnitLowerTriangularMatrix(SIZE, SIZE); 
    std::cout << "Original L:" << std::endl;
    printMatrix(originalL);

    Matrix originalU = generateUpperTriangularMatrix(SIZE, SIZE);
    std::cout << "Original U:" << std::endl;
    printMatrix(originalU);

    Matrix testMatrix = serialSquareMatrixProduct(originalL, originalU);
    std::cout << "originalL * originalU = testMatrix:" << std::endl;
    printMatrix(testMatrix);

    LUPair luResult;
    luResult = luFactorizationSerial(testMatrix);

    std::cout << "Decomposed L:" << std::endl;
    printMatrix(luResult.first);

    std::cout << "Decomposed U:" << std::endl;
    printMatrix(luResult.second);

    return 0;
}
