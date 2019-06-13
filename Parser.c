#include "Parser.h"

/*
 * Check whether numOfFixed is between minNum and maxNum
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
	}

	if (numOfScanned == EOF) {
		printExitAndExit();
	}

	CreateBoard(3, 3, numOfFixed);
}

/*
 * enum of command types as described in PDF
 */
typedef enum {
	Set, Hint, Validate, Restart, Exit, Invalid
} commandType;

/*
 * identify the command type
 */
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
 * get arguments of command from user
 */
int parseArgument() {
	char *token;
	token = strtok(NULL, " \t\r\n");
	if (token!=NULL)
		return atoi(token);
	else
		return 0;
}

/*
 * Read command line from user and execute it
 */
bool getCommand(bool firstCommand) {
	bool lastCommandInGame = false;
	char *command;
	char *fgetsRetVal;
	char exitStr[] = "exit";
	char c, line[1024];
	int x, y, z;

	/* init command*/
	command = NULL;

	/* we have to use x,y,z. otherwise it makes an error of unused variables */
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

	/* check for error in input */
	fgetsRetVal = fgets(line, 1024, stdin);
	if (fgetsRetVal != NULL) {
		command = strtok(line, " \t\r\n");
	}
	else {
		if (feof(stdin))
			command = exitStr;
		else if (ferror(stdin)) {
			printf("Error: fgets has failed\n");
			exit(0);
		}
	}
	if (command==NULL)
		return lastCommandInGame;

	/* execute the command */
	switch (getCommandType(command)) {
	case Hint:
		x = parseArgument();
		y = parseArgument();
		if (isNumInRange(x, 1, 9) && isNumInRange(y, 1, 9)) {
			hint(x, y);
		}
		else {
			invalidCommand();
		}
		break;
	case Set:
		x = parseArgument();
		y = parseArgument();
		z = parseArgument();
		if (isNumInRange(x, 1, 9) && isNumInRange(y, 1, 9)) {
			set(x, y, z);
		}
		else {
			invalidCommand();
		}
		break;
	case Validate:
		validate();
		break;
	case Restart:
		exitGame();
		lastCommandInGame = true;
		break;
	case Exit:
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
