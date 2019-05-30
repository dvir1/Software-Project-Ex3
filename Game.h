#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>

/*
 * print "Exiting...\n" and exit program
 */
void printExitAndExit();

void CreateBoard(int blockNumRow, int blockNumCol, int numOfFixed);

void set(int x, int y, int z);

void hint(int x, int y);

void validate();

void restart();

void exitGame();

bool endGame();

#endif /* GAME_H_ */
