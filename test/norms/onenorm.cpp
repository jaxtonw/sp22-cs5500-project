#include "../../src/common/helpers.h"
#include "../../src/norms/onenorm.h"
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    std::vector<double> testVec;
    for (int i=0; i < 5; i++) {
        testVec.push_back(1.0);
    }

    std::cout << "Test Vector ";
    printVector(testVec);

    std::cout << "One norm result: oneNorm(testVec) = " << oneNorm(testVec) << std::endl;

    return 0;
}
