#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdbool.h>

bool backtrack(Cell* board, SolverType type, int seed);

int deterChoice(int* possibilities);

int randomChoice(int* possibilities);

int* validCellSol(Cell* cells);

void generator(Cell* board, Cell* solution, int numOfFixed);

#endif /* SOLVER_H_ */
