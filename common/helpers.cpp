#include "./helpers.h"

void printVector(double vec[], int size) {
    std::cout << "[" << std::endl;;
    for (int i = 0; i < size; i++) {
        std::cout << " " << vec[i] << std::endl;
    }
    std::cout << "]" << std::endl;
}

void printMatrix2D(double *A, int m, int n) {
    for (size_t i = 0; i < m; i++)
    {
        std::cout << "| ";
        for (size_t j = 0; j < n; j++)
        {
            std::cout << A[i * n + j] << " ";
        }
        
        std::cout << "|" << std::endl;
    }
}
