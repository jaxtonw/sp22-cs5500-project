#include "lowerTriangular.h"

MathVector lowerTriangularSolver(Matrix matrixA, MathVector vectorB) {
    MathVector solution(vectorB.size());
    
    for (int i = 0; i < matrixA.size(); i++) {
        solution[i] = vectorB[i] / matrixA[i][i];
        for (int k = i; k < matrixA.size(); k++) {
            vectorB[k] = vectorB[k] - matrixA[k][i] * solution[i]; 
        }
    }

    return solution;
}
