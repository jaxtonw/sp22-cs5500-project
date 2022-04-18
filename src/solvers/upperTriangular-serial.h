/**
 * @file upperTriangular-serial.h
 * @brief Interface for serial upper triangular solver function
 * 
 */
#ifndef UPPERTRIANGLESOLVERSERIAL_H
#define UPPERTRIANGLESOLVERSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>

#include "../common/types.h"

/**
 * @brief Produce a solution to Ax=b when A is an upper triangular matrix
 * 
 * @param matrixA The upper triangular matrix A in Ax=b
 * @param vectorB The vector b in Ax=b
 * @return MathVector The solution vector x in Ax=b
 */
MathVector upperTriangularSolverSerial(Matrix matrixA, MathVector vectorB);

#endif