# Spring 2022 CS 5500 Final Project - SPLARF


## Series and Parallel Linear Algebra Routines and Functions

This library provides Linear Algebra functions and routines performed both serially and in parallel utilizing MPI. The goal is to provide a low-end static C++ library for high performance Linear Algebra operations, and study the benefits of parallelization.

## Implemented Operations

- Matrix
  - Transpose
  - Addition
    - Matrix
    - Scalar
  - Subtraction
    - Matrix
    - Scalar
  - Product
    - Matrix
    - Vector
  - Elementwise Product
    - Matrix
    - Scalar
  - LU Factorization
  - L Solver
  - U Solver
  - D Solver
- Vector
  - Addition
    - Vector
    - Scalar
  - Subtraction
    - Vector
    - Scalar
  - Dot Product
    - Vector
  - Elementwise Product
    - Vector
    - Scalar

## Doxygen Docs

Doxygen documentation has been provided in the docs folder. Launch index.html in doc/html for full code documentation.

### Generating Doxygen Documentation

1. Install doxygen for your OS
2. In the root folder, run `doxygen Doxyfile`

## MPI Installation

The code in this repository requires MPI to run. The code has been tested with OpenMPI 4.1.2 on Ubuntu and Windows.

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
*   Sander Burton
*   Max Clark
*   James Sanford-Luevano
*   Jaxton Winder
