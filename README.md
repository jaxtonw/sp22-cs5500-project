# Spring 2022 CS 5500 Final Project - SPLARF

## Series and Parallel Linear Algebra Routines and Functions

This library provides Linear Algebra functions and routines performed both serially and in parallel utilizing MPI. The goal is to provide a low-end static C++ library for high performance Linear Algebra operations, and study the benefits of parallelization.

## Implemented Operations

-   [Transpose](./src/arithmetic/arithmetic.cpp)
-   [ElementMultiply](./src/arithmetic/arithmetic.cpp)
-   [Addition](./src/arithmetic/arithmetic.cpp)
-   [Subtraction](./src/arithmetic/arithmetic.cpp)
-   [Matrix-Vector Product](./src/matrix/vectorProd.cpp)
-   [Matrix-Matrix Product](./src/matrix/matrixProd.cpp)
-   [Vector-Vector Product](./src/vector/dotProd.cpp)

## MPI Installation

The code in this repository requires MPI to run.

### MPI Ubuntu Installation (including WSL)

-   `apt update`
-   `apt install openmpi-bin`

## Testing

A makefile has been provided to perform test automation.

-   `make buildtest`
    -   Builds the tests with `mpicxx` and stores them in ./testbuild/
-   `make runtest`
    -   Runs the tests in ./testbuild/ with MPI and compares the .result file located at ./test/xxx/\<test-to-run\>.o.result against the result ./testresult/test/xxx/\<test-to-run\>.o.result

See the [test README](./test/README.md) for more information.
## Authors

-   Sander Burton
-   Max Clark
-   James Sanford-Luevano
-   Jaxton Winder
