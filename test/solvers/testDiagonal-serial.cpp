#include "diagonalSolver-serial.h"

#define SIZE 5

int main(int argc, char **argv) {
    
    Matrix A(SIZE);
    for (int i = 0; i < SIZE; i++) {
        MathVector newVec(SIZE);
        newVec[i] = i+1;
        A[i] = newVec;
    }

    MathVector b(SIZE);
    for (int i = 0; i < SIZE; i++) {
        b[i] = 1;
    }

    MathVector sol = diagonalSolverSerial(A, b);

    for (int i = 0; i < sol.size(); i++) {
        std::cout << "sol[" << i << "] = " << sol[i] << std::endl;
    }
    
    return 0;
}