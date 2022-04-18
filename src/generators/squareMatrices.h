/**
 * @file squareMatrices.h
 * @brief Provides an interfact for functions to generate various square matrices
 */
#ifndef SQUAREMATRICES_H
#define SQUAREMATRICES_H

#include <vector>
#include <math.h>
#include <iostream>
#include <random>

#include "../common/types.h"

/**
 * @brief Generate square NxN matrix of random values
 * 
 * @param n Size of NxN matrix to generate 
 * @param maxMagnitude Maximum magnitude of any randomly generated element 
 * @return Matrix Square matrix of size NxN filled with random values
 */
Matrix generateRandomMatrix(int n, double maxMagnitude=1.0);

/**
 * @brief Generate square diagonal NxN matrix of random values
 * 
 * @param n Size of NxN matrix to generate 
 * @param maxMagnitude Maximum magnitude of any randomly generated element 
 * @return Matrix Diagonal matrix of size NxN filled with random values
 */
Matrix generateDiagonalMatrix(int n, double maxMagnitude=1.0);

/**
 * @brief Generate square Lower Triangular NxN matrix of random values
 * 
 * @param n Size of NxN matrix to generate 
 * @param maxMagnitude Maximum magnitude of any randomly generated element 
 * @return Matrix Lower Triangular matrix of size NxN filled with random values
 */
Matrix generateLowerTriangularMatrix(int n, double maxMagnitude=1.0);

/**
 * @brief Generate square *unit* Lower Triangular NxN matrix of random values
 *          Unit lower triangular matrices have 1's on the diagonal
 *
 * @param n Size of NxN matrix to generate 
 * @param maxMagnitude Maximum magnitude of any randomly generated element 
 * @return Matrix Unit Lower Triangular matrix of size NxN filled with random values
 */
Matrix generateUnitLowerTriangularMatrix(int n, double maxMagnitude=1.0);

/**
 * @brief Generate square Upper Triangular NxN matrix of random values
 * 
 * @param n Size of NxN matrix to generate 
 * @param maxMagnitude Maximum magnitude of any randomly generated element 
 * @return Matrix Upper Triangular matrix of size NxN filled with random values
 */
Matrix generateUpperTriangularMatrix(int n, double maxMagnitude=1.0);

#endif