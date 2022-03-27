# Automated Test Folder

## Overview

1. Test is compiled with mpicxx
2. Output file is ran with `mpirun -np 4`
3. STDOUT from 2 is compared with test's result file

## Test Structure

Tests should follow the folder structure as ./src

## Results File

Each *.cpp requires a file called *.cpp.o.result. This result file will be compared against the output from the test run. The make function quits upon the first result file that does not match.

## Test Compilation

Tests are compiled with all *.cpp files found in src using `mpicxx -DMAKE_TEST <src-cpps> <test-cpp>` and saved to ./testbuild with the same folder format as ./test.

## Test Runs

All tests are run with MPI. Use the `MAKE_TEST` definition to wrap a single threaded test with MPI.

```cpp
int main(int argc, char **argv)
{
#ifdef MAKE_TEST
    MPI_Init(&argc, &argv);
    int rank, commSize = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank)
    {
#endif
        std::vector<double> testVec;
        for (int i = 0; i < 5; i++)
        {
            testVec.push_back((double)i);
        }

        std::cout << "Test Vector ";

        printVector(testVec);

        std::cout << "Inf norm result: infNorm(testVec) = " << infNorm(testVec) << std::endl;

#ifdef MAKE_TEST
    }
#endif

    return 0;
}
```

### Excluding Tests

To exclude a test, use the `.c++` file type.