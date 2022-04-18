/**
 * @file luFact-serial.h
 * @brief Interface for a serial LU Factorization algorithm
 * 
 */

#ifndef LUFACTSERIAL_H
#define LUFACTSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>
// To assuredly have std::pair, incase compiler doesn't automatically include utility
#include <utility>
#include <algorithm>

#include "../common/types.h"

/**
 * @brief Define a std::pair of matrices that represent our L and U matrices we get back
 * 
 */
using LUPair = std::pair<Matrix, Matrix>;

/**
 * @brief When given a matrix A that can be lu factorized without pivoting, 
 *  return two matrices, L and U, that are the result of factorizing matrix A
 * 
 * @param matrixA Given matrix to factorize
 * @return LUPair Pair of matrices that represent L and U, where LUPair.first is L and LUPair.second is U
 */
LUPair luFactorizationSerial(Matrix matrixA);

#endif