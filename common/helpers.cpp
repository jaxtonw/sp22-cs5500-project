#include "./helpers.h"

void printVector(double vec[], int size) {
    std::cout << "[\n";
    for (int i = 0; i < size; i++) {
        std::cout << " " << vec[i] << std::endl;
    }
    std::cout << "]" << std::endl;
}
