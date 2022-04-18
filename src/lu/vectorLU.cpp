#include "vectorLU.h"

LUPair vectorLU(Matrix matrixA) {
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

        for (int i = diagIndx + 1; i < N; i++) {
            double rowFactor = matrixU[i][diagIndx] / diagFactor;
            matrixL[i][diagIndx] = rowFactor;
            matrixU[i][diagIndx] = 0;

            // updating u row by row has a bug...
            for (int j = diagIndx + 1; j < N; j++) {
                // it's a SAXPY!
                matrixU[i][j] = matrixU[i][j] - rowFactor * matrixU[diagIndx][j];
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