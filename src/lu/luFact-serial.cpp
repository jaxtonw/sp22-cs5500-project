#include "luFact-serial.h"

LUPair luFactorizationSerial(Matrix matrixA) {
    int N = matrixA.size();
    Matrix matrixL(N);
    Matrix matrixU(N);

    for (int i = 0; i < N; i++) {
        matrixL[i].resize(N); // maybe set L[i][i] = 1.0 here?
        matrixU[i] = matrixA[i];
    }

    for (int diagIndx = 0; diagIndx < N; diagIndx++) {
        matrixL[diagIndx][diagIndx] = 1;
        double diagFactor = matrixU[diagIndx][diagIndx];

        for (int row = diagIndx + 1; row < N; row++) {
            // Can spread this work between processors!
            double rowFactor = matrixU[row][diagIndx] / diagFactor;
            matrixL[row][diagIndx] = rowFactor;
            matrixU[row][diagIndx] = 0;

            for (int col = diagIndx + 1; col < N; col++) {
                // This operation is a SAXPY! (Scalar a * vector x + vector y)
                // can parallelize this too!
                // a = - rowFactor
                // x = matrixU[diagIndx] // row diagIndx
                // y = matrixU[row]
                matrixU[row][col] = matrixU[row][col] - rowFactor * matrixU[diagIndx][col];
            }
        }        
    }


    LUPair LAndU;
    // L is in LAndU[0]
    LAndU.first = std::move(matrixL);
    // U is in LAndU[1]
    LAndU.second = std::move(matrixU);

    return LAndU;
}