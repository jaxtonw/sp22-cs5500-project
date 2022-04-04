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
*   Sander Burton
*   Max Clark
*   James Sanford-Luevano
*   Jaxton Winder
