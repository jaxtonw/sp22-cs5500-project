# Matrix Operations

This folder contains linear algebra operations related to matrices

## Implemented Operations

- [Vector Product]](./vectorProd.cpp)

## Running Tests

- `mpicxx src/common/*elpers.cpp src/matrix/vectorProd.cpp src/matrix/<test-file>.cpp`
  - Produces a.out in root directory
- `mpirun -np <cores> $PWD/a.out`
