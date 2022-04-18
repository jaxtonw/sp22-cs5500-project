#ifndef LUFACTSERIAL_H
#define LUFACTSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>
// To assuredly have std::pair, incase compiler doesn't automatically include utility
#include <utility>
#include <algorithm>

#include "../common/types.h"
using LUPair = std::pair<Matrix, Matrix>;

LUPair luFactorizationSerial(Matrix matrixA);

#endif