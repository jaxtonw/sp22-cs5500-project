/**
 * @file types.h
 * @brief Provides an interface for common types used in this library
 * 
 */
#ifndef MATRIX_VECTOR_TYPES_H
#define MATRIX_VECTOR_TYPES_H

/**
 * @brief A MathVector is shorthand for a vector of doubles
 * 
 */
using MathVector = std::vector<double>;
/**
 * @brief A Matrix is shorthand for a vector of MathVectors
 * 
 */
using Matrix = std::vector<MathVector>;

#endif