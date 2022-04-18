/**
 * @file diagonalSolver-serial.h
 * @brief Interface for a serial diagonal solver function
 * 
 */

#ifndef DIAGONALSOLVERSERIAL_H
#define DIAGONALSOLVERSERIAL_H

#include <vector>
#include <math.h>
#include <iostream>

#include "../common/types.h"

/**
 * @brief Produce a solution to Ax=b when A is a diagonal matrix
 * 
 * @param matrixA The diagonal matrix A in Ax=b
 * @param vectorB The vector b in Ax=b
 * @return MathVector The solution vector x in Ax=b
 */
MathVector diagonalSolverSerial(Matrix matrixA, MathVector vectorB);

#endif