#include "pnorm-serial.h"

double pNormSerial(std::vector<double> vec, double p) {
    double result = 0;
    for (double item: vec) {
        result += pow(abs(item), p);
    } 
    return pow(result, 1/p);
}
