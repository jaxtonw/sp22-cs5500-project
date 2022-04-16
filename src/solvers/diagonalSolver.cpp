#include "diagonalSolver.h"

MathVector diagonalSolver(Matrix diagMatrixA, MathVector vectorB) {
    MathVector solution(vectorB.size());
    
    for (int i = 0; i < diagMatrixA.size(); i++) {
        if (diagMatrixA[i][i] == 0) {
            if (vectorB[i] == 0) {
                solution[i] = 0;
            }
            else {
                std::cout << "This matrix is not solveable." << std::endl;
                std::exit(1);
            }
        } 
        else {
            solution[i] = vectorB[i] / diagMatrixA[i][i];
        }
    }

    return solution;
}
