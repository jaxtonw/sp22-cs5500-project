#ifndef SQUAREMATRICES_H
#define SQUAREMATRICES_H

#include <vector>
#include <math.h>
#include <iostream>
#include <random>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

Matrix generateRandomMatrix(int n, double maxMagnitude=1.0);
Matrix generateDiagonalMatrix(int n, double maxMagnitude=1.0);
Matrix generateLowerTriangularMatrix(int n, double maxMagnitude=1.0);
Matrix generateUnitLowerTriangularMatrix(int n, double maxMagnitude=1.0);
Matrix generateUpperTriangularMatrix(int n, double maxMagnitude=1.0);

#endif