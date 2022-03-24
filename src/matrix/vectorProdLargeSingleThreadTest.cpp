#include "../common/helpers.h"
#include <algorithm>
#include <chrono>
#include <iostream>

#define COLUMNS 512
#define ROWS COLUMNS

using namespace std::chrono;
using namespace std;

int main(int argc, char **argv)
{
    double A[ROWS * COLUMNS];
    double x[COLUMNS];
    double y[ROWS];

    for (size_t i = 0; i < ROWS * COLUMNS; i++)
    {
        A[i] = (double)i;
        if (i < COLUMNS)
        {
            x[i] = (double)i;
        }
    }

    // random_shuffle(A, A + ROWS * COLUMNS);
    // random_shuffle(x, x + COLUMNS);

    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < ROWS; i++)
    {
        y[i] = 0;
        for (size_t j = 0; j < COLUMNS; j++)
        {
            y[i] += A[i * COLUMNS + j] * x[j];
        }
    }

    auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);

    // cout << "Result is ";
    // printVector(y, COLUMNS);
    cout << duration.count() << endl;
}