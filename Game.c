#include <stdio.h>
#include <stdlib.h>

/*
 * print "Exiting...\n" and exit program
 */
void printExitAndExit() {
	printf("Exiting...\n");
	exit(0);
}

void CreateBoard(int blockNumRow, int blockNumCol, int numOfFixed) {
	printf("CreateBoard params: %d, %d, %d", blockNumRow, blockNumCol, numOfFixed);
}

void set(int x, int y, int z) {
	printf("set params: %d, %d, %d", x, y, z);
}

void hint(int x, int y) {
	printf("set hint: %d, %d", x, y);
}

void validate() {

}

void restart() {

}

void exitGame() {

}
