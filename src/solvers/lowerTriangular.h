#ifndef LOWERTRIANGLESOLVER_H
#define LOWERTRIANGLESOLVER_H

#include <vector>
#include <math.h>
#include <iostream>

typedef std::vector<double> MathVector;
typedef std::vector<MathVector> Matrix;

MathVector lowerTriangularSolver(Matrix matrixA, MathVector vectorB);

#endif