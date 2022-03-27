
#include "../../src/common/helpers.h"
#include "../../src/norms/twonorm.h"
#include <vector>
#include <iostream>
#include <math.h>

int main(int argc, char** argv) {
    std::vector<double> testVec;
    for (int i=0; i < 5; i++) {
        testVec.push_back(1.0);
    }

    std::cout << "Test Vector ";
    printVector(testVec);

    std::cout << "Two norm result: twoNorm(testVec) = " << twoNorm(testVec) << std::endl;

    return 0;
}
