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
 */
void getCommand();

#endif /* PARSER_H_ */
