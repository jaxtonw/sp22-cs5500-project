#include "../../src/lu/luFact-serial.h"
#include "../../src/generators/squareMatrices.h"
#include "../../src/common/helpers.h"
#include <chrono>

#define SIZE 2000
#define TEST_SIZE 10

Matrix serialSquareMatrixProduct(Matrix matrixA, Matrix matrixB)
{
    // A and B must be same dimensions and both square
    int N = matrixA.size();
    Matrix myMatrix(N);

    for (int row = 0; row < N; row++)
    {
        myMatrix[row].resize(N);

        for (int col = 0; col < N; col++)
        {
            double result = 0;
            for (int k = 0; k < N; k++)
            {
                result += matrixA[row][k] * matrixB[k][col];
            }
            myMatrix[row][col] = result;
        }
    }

    return myMatrix;
}

int main(int argc, char **argv)
{
    int64_t totalTime;
    std::cout << "starting lu factorial serial test for " << SIZE << "x" << SIZE << " matrix" << std::endl;
    for (size_t i = 0; i < TEST_SIZE; i++)
    {
        Matrix originalL = generateUnitLowerTriangularMatrix(SIZE, SIZE);
        Matrix originalU = generateUpperTriangularMatrix(SIZE, SIZE);
        Matrix testMatrix = serialSquareMatrixProduct(originalL, originalU);

        LUPair luResult;

        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

        luResult = luFactorizationSerial(testMatrix);

        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

        totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }

    return 0;
}
