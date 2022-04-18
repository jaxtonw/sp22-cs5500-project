#include <iostream>
#include <chrono>
using namespace std;

/**
 * computes the dot product in serial
 *
 * @param x Input Vector 1
 * @param y Input Vector 2
 * @param range sub-range (inclusive) of original vectors to compute dot product for - [start, end]
 * @return the resulting sub dot product (scalar)
 */
double dotProduct(double *x, double *y, size_t length)
{
    double result = 0;
    for (unsigned int i = 0; i <= length; i++)
    {
        result += x[i] * y[i];
    }
    return result;
}

double benchMark(double *x, double *y, size_t length) {

    cout << "Computing dot product between vectors of size " << length << endl;


    auto start = chrono::system_clock::now();
    double result = dotProduct(x, y, length);
    chrono::duration<double> totalTime = chrono::system_clock::now() - start;

    cout << "Done in " << totalTime.count() << " seconds." << std::endl;

    return totalTime.count();
}

int main(int argc, char **argv)
{
    double x[] = {1.0, 2.0, 3.0, 4.0};
    double y[] = {1.0, 2.0, 3.0, 4.0};
	size_t length = 4;
    benchMark(x, y, length);

    double a[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    double b[] = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0};
	length = 15;
    benchMark(a, b, length);

    double e[] = {};
    double f[] = {};
	length = 0;
    benchMark(e, f, length);

    length = 100000;
    double g[length];
    double h[length];
    for (unsigned int i = 0; i < length; i++) {
        g[i] = (i + 31) * i % 37 + 1; // Kind of random test values (more like hashed values)
        h[i] = ((i + 1) * i / 2) % 37;
    }
    
	benchMark(g, h, length);
}

