#include "matrixProd-serial.h"

Matrix matrixProductSerial(Matrix matrixA, Matrix matrixB) {
    int N, M, K;
    // matrixA is of dimension NxM
    // matrixB is of dimesnion MxK 
    N = matrixA.size();
    M = matrixB.size(); // Must also be equivelant to matrixA[0].size()
    K = matrixB[0].size();
    Matrix newMatrix(N);

    for (int row = 0; row < N; row++) {
        newMatrix[row].resize(K);
        for (int col = 0; col < K; col++) {
            double result = 0;
            for (int m = 0; m < M; m++) {
                result += matrixA[row][m] * matrixB[m][col];
            }
            newMatrix[row][col] = result;
        }
    }
    return newMatrix;
}
