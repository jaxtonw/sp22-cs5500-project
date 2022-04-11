#ifndef DIAGONALSOLVER_H
#define DIAGONALSOLVER_H

#include <vector>
#include <math.h>
#include <iostream>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

MathVector diagonalSolver(Matrix matrixA, MathVector vectorB);

#endif