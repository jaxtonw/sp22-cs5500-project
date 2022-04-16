#ifndef UPPERTRIANGLESOLVER_H
#define UPPERTRIANGLESOLVER_H

#include <vector>
#include <math.h>
#include <iostream>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

MathVector upperTriangularSolver(Matrix matrixA, MathVector vectorB);

#endif