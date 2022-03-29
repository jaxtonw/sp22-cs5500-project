#include "onenorm-serial.h"

double oneNorm(std::vector<double> vec) {
    double result = 0;
    for (double item: vec) {
        result += item;
    } 
    return result;
}