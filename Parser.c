#include "Parser.h"

/*
 * Check whether numOfFixed is between 0 and maxCellNum
 * Return true if it is
 */
bool isNumInRange(int num, int minNum, int maxNum) {
	return (minNum <= num && num <= maxNum);
}

/*
 * Ask for number of fixed cells and initialize the board
 */
void start() {
	int numOfFixed=0, numOfScanned=0;

	while (!((numOfScanned==EOF) || (numOfScanned == 1 && isNumInRange(numOfFixed, 0, 80)))) {
		fflush(stdin);
		fflush(stdout);
		printf("Please enter the number of cells to fill [0-80]:\n");
		numOfScanned = scanf("%d", &numOfFixed);
		if (numOfScanned == 1 && !isNumInRange(numOfFixed, 0, 80)) {
			printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
		}
#ifdef DEBUG
		printf("numOfScanned=%d, numOfFixed=%d\n", numOfScanned, numOfFixed);
#endif
	}

	if (numOfScanned == EOF) {
		printExitAndExit();
	}

	CreateBoard(3, 3, numOfFixed);
}

typedef enum {
	Set, Hint, Validate, Restart, Exit, Invalid
} commandType;

commandType getCommandType(char* command) {
	if (strcmp(command, "set") == 0) {
		return Set;
	}
	if (strcmp(command, "hint") == 0) {
		return Hint;
	}
	if (strcmp(command, "validate") == 0) {
		return Validate;
	}
	if (strcmp(command, "restart") == 0) {
		return Restart;
	}
	if (strcmp(command, "exit") == 0) {
		return Exit;
	}
	return Invalid;
}

/*
 * Read command line from user and execute it
 */
bool getCommand(bool firstCommand) {
	bool lastCommandInGame = false;
	char *command;
	char c, line[1024];
	int x, y, z;

	/* we have to use x,y,z */
	x = 0;
	y = 0;
	z = 0;
	if (x == y)
		z = 1;
	if (z == 1)
		x = y;

	/* last scanf leaves a \n so we need to read it from the buffer, otherwise fgets won't wait for user command.
	 * then we have to use c */
	if (firstCommand==true) {
		c = getchar();
		if (c == '\n')
			x=0;
		firstCommand=false;
	}
	fgets(line, 1024, stdin);
	command = strtok(line, " \t\r\n");
#ifdef DEBUG
	printf("%s, %d\n", command, getCommandType(command));
#endif

	switch (getCommandType(command)) {
	case Set:
		x = atoi(strtok(NULL, " "));
		y = atoi(strtok(NULL, " "));
		z = atoi(strtok(NULL, " "));
#ifdef DEBUG
		printf("command is Set, x=%d, y=%d, z=%d\n", x, y, z);
#endif
		if (isNumInRange(x, 1, 9) && isNumInRange(y, 1, 9)) {
			set(x, y, z);
		}
		else {
			invalidCommand();
		}
		break;
	case Hint:
		x = atoi(strtok(NULL, " "));
		y = atoi(strtok(NULL, " "));
#ifdef DEBUG
		printf("command is Hint, x=%d, y=%d\n", x, y);
#endif
		if (isNumInRange(x, 1, 9) && isNumInRange(y, 1, 9)) {
			hint(x, y);
		}
		else {
			invalidCommand();
		}
		break;
	case Validate:
#ifdef DEBUG
		printf("command is Validate\n");
#endif
		validate();
		break;
	case Restart:
#ifdef DEBUG
		printf("command is Restart\n");
#endif
		exitGame();
		lastCommandInGame = true;
		break;
	case Exit:
#ifdef DEBUG
		printf("command is Exit\n");
#endif
		exitGame();
		lastCommandInGame = true;
		printExitAndExit();
		break;
	default:
		invalidCommand();
		break;
	}

	return lastCommandInGame;
}
