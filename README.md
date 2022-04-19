# Spring 2022 CS 5500 Final Project - SPLARF


## Series and Parallel Linear Algebra Routines and Functions

This library provides Linear Algebra functions and routines performed both serially and in parallel utilizing MPI. The goal is to provide a low-end static C++ library for high performance Linear Algebra operations, and study the benefits of parallelization.

## Sample File

A small sample of what SPLARF can do is shown in [sample.cpp](sample.cpp). Here's an example for compiling and running the file:

```shell
mpicxx sample.cpp ./src/common/*.cpp ./src/matrix/*.cpp;
mpirun -np 4 $PWD/a.out;
Matrix A is: 
| 12 8 4 3 |
| 3 17 14 7 |
| 9 8 10 6 |
| 4 9 5 11 |
| 7 3 13 4 |
| 3 9 5 14 |
Matrix B is: 
| 5 19 |
| 6 15 |
| 7 8 |
| 3 9 |
Matrix product is: 
| 145 407 |
| 236 487 |
| 181 425 |
| 142 350 |
| 156 318 |
| 146 358 |
```

For more examples, see the [files in the test](./test/) directory, which have direct examples and the correct results.

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
