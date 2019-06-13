#include "Game.h"

Cell **board;
Cell **solution;
int numOfEmptyCells;
int blockNumRow;
int blockNumCol;
int numOfCells;
int blockNumOfCells;

/*
 * return a pointer to cell <x,y>
 */
Cell *boardCellAccess(int x, int y)
{
	int row = y - 1;
	int col = x - 1;
	return (&(board[row][col]));
}

/*
 * return a pointer to cell <x,y>
 */
Cell *solutionCellAccess(int x, int y)
{
	int row = y - 1;
	int col = x - 1;
	return (&(solution[row][col]));
}

/*
 * print "Exiting...\n" and exit program
 */
void printExitAndExit()
{
	printf("Exiting...\n");
	exit(0);
}

/*
 * create the board and print it
 */
void CreateBoard(int blockNumOfRows, int blockNumOfCols, int numOfFixed)
{
	int i, j;

	blockNumCol = blockNumOfCols;
	blockNumRow = blockNumOfRows;
	blockNumOfCells = blockNumCol * blockNumRow;
	numOfCells = blockNumOfCells * blockNumOfCells;
	numOfEmptyCells = numOfCells - numOfFixed;
	board = (Cell **)calloc(blockNumOfCells, sizeof(Cell *));
	if (board == 0) { /* calloc failed */
		printf("Error: calloc has failed\n");
		exit(0);
	}
	for (i = 0; i < blockNumOfCells; i++)
	{
		board[i] = (Cell *)calloc(blockNumOfCells, sizeof(Cell));
		if (board[i] == 0) { /* calloc failed */
			printf("Error: calloc has failed\n");
			for (j=0; j<i; j++) {
				free(board[j]);
			}
			free(board);
			exit(0);
		}
	}
	solution = (Cell **)calloc(blockNumOfCells, sizeof(Cell *));
	if (solution == 0) { /* calloc failed */
		printf("Error: calloc has failed\n");
		for (j=0; j<blockNumOfCells; j++) {
			free(board[j]);
		}
		free(board);
		exit(0);
	}
	for (i = 0; i < blockNumOfCells; i++)
	{
		solution[i] = (Cell *) calloc(blockNumOfCells, sizeof(Cell));
		if (solution[i] == 0) { /* calloc failed */
			printf("Error: calloc has failed\n");
			for (j = 0; j < i; j++) {
				free(solution[j]);
			}
			free(solution);
			for (j = 0; j < blockNumOfCells; j++) {
				free(board[j]);
			}
			free(board);
			exit(0);
		}
	}


	/*
	 * generate solution and board, then print the board
	 */
	backtrack(board, solution, Randomized, blockNumOfCells, blockNumRow, blockNumCol);
	generator(board, solution, blockNumOfCells, numOfFixed);
	printBoard();
}

/*
 * make set move
 */
void set(int x, int y, int z)
{
	Cell *cell;
	if (endGame())
	{
		invalidCommand();
		return;
	}
	cell = boardCellAccess(x, y);
	if (cell->fixed)
	{
		printf("Error: cell is fixed\n");
		return;
	}

	if (!validCellSol(board, blockNumOfCells, blockNumRow, blockNumCol, cell, x, y, z, false))
	{
		printf("Error: value is invalid\n");
		return;
	}
	if (cell->value == 0)
	{
		if (z != 0)
		{
			numOfEmptyCells--;
		}
	}
	else
	{
		if (z == 0)
		{
			numOfEmptyCells++;
		}
	}
	cell->value = z;
	printBoard();
	if (endGame())
	{
		printf("Puzzle solved successfully\n");
	}

	return;
}

/*
 * make hint move
 */
void hint(int x, int y)
{
	Cell *cell;
	if (endGame())
	{
		invalidCommand();
		return;
	}
	cell = solutionCellAccess(x, y);
	printf("Hint: set cell to %d\n", cell->value);

	return;
}

/*
 * make validate move, validate the board
 */
void validate()
{
	bool success;
	if (endGame())
	{
		invalidCommand();
		return;
	}
	success = backtrack(board, solution, Deterministic, blockNumOfCells, blockNumRow, blockNumCol);
	if (success)
	{
		printf("Validation passed: board is solvable\n");
	}
	else
	{
		printf("Validation failed: board is unsolvable\n");
	}
	return;
}

/*
 * make exit move, exit the game
 */
void exitGame()
{
	int j;
	for (j = 0; j < blockNumOfCells; j++) {
		free(board[j]);
		free(solution[j]);
	}
	free(board);
	free(solution);
	return;
}

/*
 * check if game ended
 */
bool endGame()
{
	return numOfEmptyCells == 0;
}

/*
 * print the board
 */
void printBoard()
{
	Cell *cell;
	int cellRow, cellCol;
	int i, j, k, r, l;
	int M = blockNumRow; /*num of blocks in a row*/
	int N = blockNumCol; /*num of cells in a block row*/
	int C = 3;			 /*num of chars every cell take to print*/
	int numOfdashes = M * (N * C + 2) + 1;

	for (l = 0; l < numOfdashes; l++)
	{
		printf("-");
	}
	printf("\n");

	for (k = 0; k < N; k++)
	{ /*for every row of blocks*/
		for (r = 0; r < M; r++)
		{ /*for every row of a block*/
			for (j = 0; j < M; j++)
			{ /*for every col of blocks*/
				printf("| ");
				for (i = 0; i < N; i++)
				{ /*for every col of a block*/
					cellRow = (k * M) + r + 1;
					cellCol = (j * N) + i + 1;
					cell = boardCellAccess(cellCol, cellRow);
					if (cell->fixed)
					{
						printf(".");
					}
					else
					{
						printf(" ");
					}
					if (cell->value == 0)
					{
						printf("  ");
					}
					else
					{
						printf("%d ", cell->value);
					}
				}
			}
			printf("|\n");
		}
		for (l = 0; l < numOfdashes; l++)
		{
			printf("-");
		}
		printf("\n");
	}
	return;
}

/*
 * print invalid command
 */
void invalidCommand()
{
	printf("Error: invalid command\n");
	return;
}
