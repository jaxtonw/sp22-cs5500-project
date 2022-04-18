/**
 * @file lowerTriangular-serial.h
 * @brief Interface for serial lower triangular solver function
 * 
 */
#ifndef LOWERTRIANGLESOLVERSERIAL_H
#define LOWERTRIANGLESOLVERSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>

#include "../common/types.h"

/**
 * @brief Produce a solution to Ax=b when A is a lower triangular matrix
 * 
 * @param matrixA The lower triangular matrix A in Ax=b
 * @param vectorB The vector b in Ax=b
 * @return MathVector The solution vector x in Ax=b
 */
MathVector lowerTriangularSolverSerial(Matrix matrixA, MathVector vectorB);

#endif