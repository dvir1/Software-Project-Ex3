#include "Game.h"

Cell **board;
Cell **solution;
int numOfEmptyCells;
int blockNumRow;
int blockNumCol;
int numOfCells;
int blockNumOfCells;

#ifdef DEBUG
int calcCol(int i)
{
	int j = 0;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 3;
	else if (i == 2)
		j = 6;
	else if (i == 3)
		j = 1;
	else if (i == 4)
		j = 4;
	else if (i == 5)
		j = 7;
	else if (i == 6)
		j = 2;
	else if (i == 7)
		j = 5;
	else if (i == 8)
		j = 8;

	return j;
}

void generatorTest(int numOfFixed)
{
	int i = 0, j = 0, k = 1, l = 0, r = 0;

	for (i = 0; i < 9; i++)
	{
		for (k = 1; k <= 9; k++)
		{
			j = calcCol(i);
			solution[i][(j + k - 1) % 9].value = k;
			board[i][(j + k - 1) % 9].value = k;
			board[i][(j + k - 1) % 9].fixed = true;
			/*board[i][(j + k - 1) % 9].fixed = rand()%2==0?true:false;
				board[i][(j + k - 1) % 9].value = board[i][(j + k - 1) % 9].fixed==true?k:0;*/
		}
	}

	for (l = 0; l < 81 - numOfFixed; l++)
	{
		r = rand() % 81;
		board[(int)(r / 9)][r % 9].value = 0;
		board[(int)(r / 9)][r % 9].fixed = false;
	}
}

void generateSolution()
{
	int i = 0, j = 0, k = 1;

	for (i = 0; i < 9; i++)
	{
		for (k = 1; k <= 9; k++)
		{
			j = calcCol(i);
			solution[i][(j + k - 1) % 9].value = k;
		}
	}
}
#endif
/*
 * return a pointer to cell <x,y>
 */
Cell *boardCellAccess(int x, int y)
{
	/*int row = (y-1)*blockNumOfCells;*/
	int row = y - 1;
	int col = x - 1;
	/*return (&(board[row+col]));*/
	return (&(board[row][col]));
}

/*
 * return a pointer to cell <x,y>
 */
Cell *solutionCellAccess(int x, int y)
{
	/*int row = (y-1)*blockNumOfCells;*/
	int row = y - 1;
	int col = x - 1;
	/*return (&(solution[row+col]));*/
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

void CreateBoard(int blockNumOfRows, int blockNumOfCols, int numOfFixed)
{
	int i, j;
#ifdef DEBUG
	printf("Create Board start\n");
#endif
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

#ifdef DEBUG
	printf("memory allocated\n");
	/*generatorTest(numOfFixed);*/
	/*generateSolution();*/
#endif
	backtrack(board, solution, Randomized, blockNumOfCells, blockNumRow, blockNumCol);
#ifdef DEBUG
	printf("solution created\n");
#endif
	generator(board, solution, blockNumOfCells, numOfFixed);
	printBoard();
#ifdef DEBUG
	printf("board generated\n");
	printf("CreateBoard params: %d, %d, %d", blockNumRow, blockNumCol, numOfFixed);
#endif
}

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

	/*printf("set params: %d, %d, %d", x, y, z);*/
	return;
}

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

	/*printf("set hint: %d, %d", x, y);*/
	return;
}

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

bool endGame()
{
	return numOfEmptyCells == 0;
}

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

void invalidCommand()
{
	printf("Error: invalid command\n");
	return;
}
