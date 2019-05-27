#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Game.h"
#include "SPBufferset.h"

/*
 * Check whether numOfFixed is between 0 and MAX_CELL_NUM
 * Return true if it is
 */
bool isValidNumOfFixed(int numOfFixed) {
	return 0 <= numOfFixed && numOfFixed <= 80;
}

/*
 * Ask for number of fixed cells and initialize the board
 */
void start() {
	int numOfFixed, numOfScanned;

	while (true) {
		printf("Please enter a number of cells to fill [0-80]:\n");
		numOfScanned = scanf("%d", &numOfFixed);
		if (feof(stdin)) {
			printExitAndExit();
		}
		if (numOfScanned==1 && isValidNumOfFixed(numOfFixed))
			break;
	}

}

/*
 * Read command line from user and execute it
 */
void getCommand() {

}
