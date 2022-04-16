#ifndef UPPERTRIANGLESOLVERSERIAL_H
#define UPPERTRIANGLESOLVERSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

MathVector upperTriangularSolverSerial(Matrix matrixA, MathVector vectorB);

#endif