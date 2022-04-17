#ifndef VECTORGENERATOR_H
#define VECTORGENERATOR_H

#include <vector>
#include <math.h>
#include <iostream>
#include <random>

using MathVector = std::vector<double>;
using Matrix = std::vector<MathVector>;

MathVector generateRandomVector(int n, double maxMagnitude=1.0);

#endif