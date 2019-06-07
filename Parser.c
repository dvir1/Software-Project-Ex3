#include "Parser.h"

/*
 * Check whether numOfFixed is between 0 and maxCellNum
 * Return true if it is
 */
bool isValidNumOfFixed(int numOfFixed, int maxCellNum) {
	return (0 <= numOfFixed && numOfFixed <= maxCellNum);
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
#ifdef DEBUG
		printf("numOfScanned=%d, numOfFixed=%d\n", numOfScanned, numOfFixed);
#endif
		if (numOfScanned == 1 && isValidNumOfFixed(numOfFixed, 80))
			break;
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
		set(x, y, z);
		break;
	case Hint:
		x = atoi(strtok(NULL, " "));
		y = atoi(strtok(NULL, " "));
#ifdef DEBUG
		printf("command is Hint, x=%d, y=%d\n", x, y);
#endif
		hint(x, y);
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
