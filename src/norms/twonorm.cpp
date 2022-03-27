#include "twonorm.h"

double twoNorm(std::vector<double> vec) {
    double result = 0;
    for (double item: vec) {
        result += item * item;
    } 
    return sqrt(result);
}