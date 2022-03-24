#include <vector>
#include <iostream>
#include <math.h>

void printVector(std::vector<double> vec) {
    std::cout << "[\n";
    for (double item : vec) {
        std::cout << "  " << item << std::endl;
    }
    std::cout << "]" << std::endl;
}

double infNorm(std::vector<double> vec) {
    double result = 0;
    for (double item: vec) {
        if (abs(item) > result) {
            result = abs(item);
        }
    }
    return result;
}

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
