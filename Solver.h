#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdbool.h>

/* if succeed return true and update the solution
 * else return false and doesn't change solution
 */
bool backtrack(Cell** board, Cell** solution, SolverType type);

int deterChoice(int* possibilities);

int randomChoice(int* possibilities);

int* allValidCellSol(Cell** board, Cell* cells);

void generator(Cell** board, Cell** solution, int numOfFixed);

/* 
 * return true if z is a valid solution to cell (x,y)
 * return false otherwise
 */
bool validCellSol(Cell** board, Cell* cell, int x, int y, int z);

#endif /* SOLVER_H_ */
