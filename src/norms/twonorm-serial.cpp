#include "twonorm-serial.h"

double twoNormSerial(std::vector<double> vec) {
    double result = 0;
    for (double item: vec) {
        result += item * item;
    } 
    return sqrt(result);
}