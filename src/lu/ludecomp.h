#ifndef LU_DECOMP_H
#define LU_DECOMP_H

#include <vector>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>

#define MCW MPI_COMM_WORLD

std::pair<std::vector<std::vector<double>>,
          std::vector<std::vector<double>>>
ludecomp(int rank, int size,
         std::vector<std::vector<double>> a);

#endif