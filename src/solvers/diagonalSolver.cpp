#include "diagonalSolver.h"

MathVector diagonalSolver(Matrix diagMatrixA, MathVector vectorB) {
    MathVector solution(vectorB.size());
    
    for (int i = 0; i < diagMatrixA.size(); i++) {
        solution[i] = vectorB[i] / diagMatrixA[i][i];
    }

    return solution;
}
