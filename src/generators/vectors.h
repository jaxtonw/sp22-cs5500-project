#ifndef VECTORGENERATOR_H
#define VECTORGENERATOR_H

#include <vector>
#include <math.h>
#include <iostream>
#include <random>

#include "../common/types.h"

MathVector generateRandomVector(int n, double maxMagnitude=1.0);

#endif