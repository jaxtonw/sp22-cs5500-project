#include "onenorm-serial.h"

double oneNormSerial(std::vector<double> vec) {
    double result = 0;
    for (double item: vec) {
        result += item;
    } 
    return result;
}