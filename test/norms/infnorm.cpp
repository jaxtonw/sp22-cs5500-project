#include "../../src/common/helpers.h"
#include "../../src/norms/infnorm.h"
#include <vector>
#include <iostream>
#include <math.h>

int main(int argc, char** argv) {
    std::vector<double> testVec;
    for (int i=0; i < 5; i++) {
        testVec.push_back((double)i);
    }

    std::cout << "Test Vector ";
    printVector(testVec);

    std::cout << "Inf norm result: infNorm(testVec) = " << infNorm(testVec) << std::endl;

    return 0;
}
