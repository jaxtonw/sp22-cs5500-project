#include "lowerTriangular.h"

#define SIZE 5

int main(int argc, char **argv) {
    
    Matrix A(SIZE);
    for (int i = 0; i < SIZE; i++) {
        MathVector newVec(SIZE);
        for (int k = 0; k < SIZE; k++) { 
            if (k <= i) 
                newVec[k] = 1;
            else
                newVec[k] = 0;
        }
        A[i] = newVec;
    }

    MathVector b(SIZE);
    for (int i = 0; i < SIZE; i++) {
        b[i] = i * i;
    }

    MathVector sol = lowerTriangularSolver(A, b);

    for (int i = 0; i < sol.size(); i++) {
        std::cout << "sol[" << i << "] = " << sol[i] << std::endl;
    }
    
    return 0;
}