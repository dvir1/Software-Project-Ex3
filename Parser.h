#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Game.h"

/*
 * Ask for number of fixed cells and initialize the board
 */
void start();

/*
 * Read command line from user and execute it
 * bool firstCommand - indicator of first command after choosing number of fixed cells
 */
void getCommand(bool firstCommand);

#endif /* PARSER_H_ */
