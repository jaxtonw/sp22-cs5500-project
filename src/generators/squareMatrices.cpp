#include "squareMatrices.h"

Matrix generateRandomMatrix(int n, double maxMagnitude) {
    Matrix myMatrix(n);

    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_real_distribution<double> dist(-1 * maxMagnitude, maxMagnitude);

    for (int i = 0; i < n; i++) {
        myMatrix[i].resize(n);

        for (int j = 0; j < n; j++) {
            myMatrix[i][j] = dist(engine);
        }
    }

    return myMatrix;
}

Matrix generateDiagonalMatrix(int n, double maxMagnitude) {
    Matrix myMatrix(n);

    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_real_distribution<double> dist(-1 * maxMagnitude, maxMagnitude);

    for (int i = 0; i < n; i++) {
        myMatrix[i].resize(n);
        myMatrix[i][i] = dist(engine);
    }

    return myMatrix;
}

Matrix generateLowerTriangularMatrix(int n, double maxMagnitude) {
    Matrix myMatrix(n);

    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_real_distribution<double> dist(-1 * maxMagnitude, maxMagnitude);

    for (int i = 0; i < n; i++) {
        myMatrix[i].resize(n);
        for (int k = 0; k <= i; k++)
            myMatrix[i][k] = dist(engine);
    }

    return myMatrix;
}

Matrix generateUpperTriangularMatrix(int n, double maxMagnitude) {
    Matrix myMatrix(n);

    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_real_distribution<double> dist(-1 * maxMagnitude, maxMagnitude);

    for (int i = 0; i < n; i++) {
        myMatrix[i].resize(n);
        for (int k = i; k < n; k++)
            myMatrix[i][k] = dist(engine);
    }

    return myMatrix;
}