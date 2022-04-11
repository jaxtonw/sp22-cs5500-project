#ifndef LOWERTRIANGLESOLVER_H
#define LOWERTRIANGLESOLVER_H

#include <vector>
#include <math.h>
#include <iostream>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

MathVector lowerTriangularSolver(Matrix matrixA, MathVector vectorB);

#endif