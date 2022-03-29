
#include "infnorm-serial.h"

double infNormSerial(std::vector<double> vec) {
    double result = 0;
    for (double item: vec) {
        if (abs(item) > result) {
            result = abs(item);
        }
    }
    return result;
}
