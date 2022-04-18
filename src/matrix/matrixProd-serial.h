/**
 * @file matrixProd-serial.h
 * Interface for matrix multiplication in serial.
 */
#ifndef MATRIX_PROD_SERIAL_H
#define MATRIX_PROD_SERIAL_H

#include <vector>
#include <iostream>
#include "../common/types.h"

/**
 * Multiply matrix A by matrix B, and get a resulting matrix back
 * Works with rectangle matrices such that col dimension of matrixA 
 *   and row dimension of matrixB match  
 * 
 * @param matrixA The left matrix to multiply of size MxN
 * @param matrixB The right matrix to multiply NxK
 * @return Matrix Resultant matrix of multiplying matrices AB of size MxK
 */
Matrix matrixProductSerial(Matrix matrixA, Matrix matrixB);

#endif