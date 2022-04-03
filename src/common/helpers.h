/**
 * @file
 * 
 * Helper functions for working with matrices and vectors.
 *
 * This header file describes the interface for each of our helpers, these may be useful when debugging
 * and testing functions from the SPLARF library.
 */
#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>

/**
 * @brief A union used to bytewise convert a 
 * double/uint64/int64/uint8* back and forth.
 * Used for MPI to allow for indexes to be packed
 * into doubles without loss. 
 */
union dblUnion
{
    double dbl;
    uint64_t uint64;
    int64_t int64;
    uint8_t uint8[sizeof(double)];
};

/**
 * Prints a vector to standard out
 *
 * @param vec a std::vector of doubles
 * @return nothing
 */
void printVector(std::vector<double> vec);

/**
 * Prints a vector to standard out vertically
 *
 * @param vec a pointer to the array of doubles
 * @param size integer representing the size of the vector
 * @return nothing
 */
void printVector(double *vec, int size);

/**
 * Prints a vector to standard out horizontally
 *
 * @param vec a pointer to the array of doubles
 * @param size integer representing the size of the vector
 * @return nothing
 */
void printVectorHorizontal(double *vec, int size);

/**
 * Prints 2D a matrix to standard out
 *
 * @param matrix a pointer to the 2d array of doubles
 * @param m number of rows in the matrix
 * @param n number of columns in the matrix
 * @return nothing
 */
void printMatrix2D(double *matrix, int m, int n);

/**
 * Returns whether a positive value is a power of two
 *
 * @param value The value to check
 * @return true If the value is a power of 2
 * @return false If the value is not a power of 2
 */
bool isPowerOfTwo(int value);


/**
 * @brief Prints the current value of a dblUnion as
 *        a double, uint64, int64, and uint8* of size 8
 * 
 * @param u The dblUnion to print
 */
void printDblUnion(dblUnion u);

#endif