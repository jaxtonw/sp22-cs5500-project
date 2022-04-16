#include "lowerTriangular.h"

MathVector lowerTriangularSolver(Matrix matrixA, MathVector vectorB) {
    MathVector solution(vectorB.size());
    
    for (int i = 0; i < matrixA.size(); i++) {
        if (matrixA[i][i] == 0) {
            if (vectorB[i] == 0) {
                solution[i] = 0;
            }
            else {
                std::cout << "This matrix is not solveable." << std::endl;
                std::exit(1);
            }
        }
        else {
            solution[i] = vectorB[i] / matrixA[i][i];
        }
        for (int k = i; k < matrixA.size(); k++) {
            vectorB[k] = vectorB[k] - matrixA[k][i] * solution[i]; 
        }
    }

    return solution;
}
