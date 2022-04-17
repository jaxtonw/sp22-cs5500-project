#include "vectors.h"

MathVector generateRandomVector(int n, double maxMagnitude) {
    MathVector myVector(n);

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> dist(-1 * maxMagnitude, maxMagnitude);


    for (int i = 0; i < n; i++) {
        myVector[i] = dist(engine);
    }

    return myVector;
}

