#ifndef GAME_H_
#define GAME_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Solver.h"

/*
 * return a pointer to cell <x,y>
 */
Cell* boardCellAccess(int x, int y);

/*
 * return a pointer to cell <x,y>
 */
Cell* solutionCellAccess(int x, int y);

/*
 * print "Exiting...\n" and exit program
 */
void printExitAndExit();

void CreateBoard(int blockNumOfRows, int blockNumOfCols, int numOfFixed);

void set(int x, int y, int z);

void hint(int x, int y);

void validate();

void restart();

void exitGame();

bool endGame();

void printBoard();

void invalidCommand();

#endif /* GAME_H_ */
