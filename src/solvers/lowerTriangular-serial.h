#ifndef LOWERTRIANGLESOLVERSERIAL_H
#define LOWERTRIANGLESOLVERSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

MathVector lowerTriangularSolverSerial(Matrix matrixA, MathVector vectorB);

#endif