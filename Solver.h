#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "MainAux.h"

/* if succeed return true and update the solution
 * else return false and doesn't change solution
 */
bool backtrack(Cell** board, Cell** solution, SolverType type, int blockNumOfCells, int blockNumRows, int blockNumCols);

int deterChoice(int* options);

int randomChoice(int* options, int numOfOptions);

int allValidCellSol(Cell** board, int options[], int blockNumOfCells, int blockNumRows, int blockNumCols, Cell* cell, int x, int y, bool isZeroBased);

void generator(Cell** board, Cell** solution, int blockNumOfCells, int numOfFixed);

/*
 * return true if z is a valid solution to cell (x,y)
 * return false otherwise
 */
bool validCellSol(Cell** board, int blockNumOfCells, int blockNumRows, int blockNumCols, Cell* cell, int x, int y, int z, bool isZeroBased);

bool valueInRow(Cell** board, int numOfCellsInRow, int x, int y, int z);

bool valueInColumn(Cell** board, int numOfCellsInRow, int x, int y, int z);

bool valueInBlock(Cell** board, int blockNumRows, int blockNumCols, int x, int y, int z);

int firstRowInBlock(int row, int blockNumRows);

int firstColInBlock(int col, int blockNumCols);

#endif /* SOLVER_H_ */
