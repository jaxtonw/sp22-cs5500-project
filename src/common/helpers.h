#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>

void printVector(std::vector<double> vec);
void printVector(double *vec, int size);
void printVectorHorizontal(double *vec, int size);
void printMatrix2D(double *matrix, int m, int n);
bool isPowerOfTwo(int value);

#endif