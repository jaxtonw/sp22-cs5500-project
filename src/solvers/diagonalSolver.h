#ifndef DIAGONALSOLVER_H
#define DIAGONALSOLVER_H

#include <vector>
#include <math.h>
#include <iostream>

typedef std::vector<double> MathVector;
typedef std::vector<MathVector> Matrix;

MathVector diagonalSolver(Matrix matrixA, MathVector vectorB);

#endif