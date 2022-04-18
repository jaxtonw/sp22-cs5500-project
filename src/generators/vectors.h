/**
 * @file vectors.h
 * @brief Interface for function to generate random vector of numbers
 * 
 */
#ifndef VECTORGENERATOR_H
#define VECTORGENERATOR_H

#include <vector>
#include <math.h>
#include <iostream>
#include <random>

#include "../common/types.h"

/**
 * @brief Generate a vector of random values
 * 
 * @param n Size of vector to generate
 * @param maxMagnitude The maximum magnitude a given element in the vector can have
 * @return MathVector The randomly generated vector to return
 */
MathVector generateRandomVector(int n, double maxMagnitude=1.0);

#endif