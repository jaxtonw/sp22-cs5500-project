#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <vector>

// Convert from/to double/uint64/uint8[4] 
// MPI sucks for trying to send multiple
// datatypes, use this to pack variables in
// the space of other variables
union dblUnion
{
    double dbl;
    uint64_t uint64;
    int64_t int64;
    uint8_t uint8[sizeof(double)];
};

void printVector(std::vector<double> vec);
void printVector(double *vec, int size);
void printVectorHorizontal(double *vec, int size);
void printMatrix2D(double *matrix, int m, int n);
bool isPowerOfTwo(int value);
void printDblUnion(dblUnion u);

#endif