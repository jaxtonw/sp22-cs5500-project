#include "pnorm.h"

double pNorm(std::vector<double> vec, double p) {
    double result = 0;
    for (double item: vec) {
        result += pow(item, p);
    } 
    return pow(result, 1/p);
}
