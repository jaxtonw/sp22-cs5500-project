#include "../../src/common/helpers.h"
#include <chrono>
#include <iostream>

int main(int argc, char **argv)
{
    
    const size_t COLUMNS = 2400;
    const size_t ROWS = COLUMNS;
    const size_t TOTAL = COLUMNS * ROWS;

    double *B = new double[TOTAL];
    double *y = new double[COLUMNS];

    for (size_t i = 0; i < TOTAL; i++)
    {
        B[i] = (double)i;
        if (i < COLUMNS)
        {
            y[i] = (double)i;
        }
    }
    // random_shuffle(A, A + ROWS * COLUMNS);
    // random_shuffle(x, x + COLUMNS);

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < ROWS; i++)
    {
        y[i] = 0;
        for (size_t j = 0; j < COLUMNS; j++)
        {
            y[i] += B[i * COLUMNS + j] * y[j];
        }
    }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start);

    // std::cout << "Result is ";
    // printVector(y, COLUMNS);
    std::cout << duration.count() << std::endl;
}