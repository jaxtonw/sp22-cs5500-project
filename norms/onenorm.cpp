#include <vector>
#include <iostream>

void printVector(std::vector<double> vec) {
    std::cout << "[\n";
    for (double item : vec) {
        std::cout << "  " << item << std::endl;
    }
    std::cout << "]" << std::endl;
}

double oneNorm(std::vector<double> vec) {
    double result = 0;
    for (double item: vec) {
        result += item;
    } 
    return result;
}

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
