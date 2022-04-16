#ifndef DIAGONALSOLVERSERIAL_H
#define DIAGONALSOLVERSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

MathVector diagonalSolverSerial(Matrix matrixA, MathVector vectorB);

#endif