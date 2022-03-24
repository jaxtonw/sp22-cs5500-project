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

double pNorm(std::vector<double> vec, double p) {
    double result = 0;
    for (double item: vec) {
        result += pow(item, p);
    } 
    return pow(result, 1/p);
}

int main(int argc, char** argv) {
    std::vector<double> testVec;
    for (int i=0; i < 5; i++) {
        testVec.push_back(1.0);
    }

    std::cout << "Test Vector ";
    printVector(testVec);

    std::cout << "p norm result (p=1): pNorm(testVec, 1) = " << pNorm(testVec, 1) << std::endl;
    std::cout << "p norm result (p=2): pNorm(testVec, 2) = " << pNorm(testVec, 2) << std::endl;
    std::cout << "p norm result (p=3): pNorm(testVec, 3) = " << pNorm(testVec, 3) << std::endl;
    std::cout << "p norm result (p=4): pNorm(testVec, 4) = " << pNorm(testVec, 4) << std::endl;
    std::cout << "p norm result (p=5): pNorm(testVec, 5) = " << pNorm(testVec, 5) << std::endl;


    return 0;
}
