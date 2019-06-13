#include "Solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* if succeed return true and update the solution
 * else return false and doesn't change solution
 */
bool backtrack(Cell **board, Cell **solution, SolverType type, int blockNumOfCells, int blockNumRow, int blockNumCol)
{
	int i, j, numOfOptions, option/*, q*/;
	bool success = false;
	Cell *cell;
	int arr[9] = {0};
	int *options;
	options = arr;
#ifdef DEBUG
	printf("backtrack variables set\nblockNumOfCells: %d\n", blockNumOfCells);
#endif
	for (i = 0; i < blockNumOfCells; i++)
	{
		for (j = 0; j < blockNumOfCells; j++)
		{

			cell = &board[i][j];
			if (cell->value == 0)
			{
				numOfOptions = allValidCellSol(board, options, blockNumOfCells, blockNumRow, blockNumCol, cell, i, j, true);
#ifdef DEBUG
	/*scanf("%d", &q);
	printf("i:%d, j:%d, numOfOptions:%d, options: ", i, j, numOfOptions);
	printIntArray(options);
	printf("\n");*/
#endif
				while (numOfOptions > 0)
				{
					switch (type)
					{
					case Deterministic:
						option = deterChoice(options);
						break;
					case Randomized:
						option = randomChoice(options, numOfOptions);
						break;
					}
					numOfOptions--;
#ifdef DEBUG
					/*printf("option: %d\n", option);*/
#endif
					cell->value = option;
					success = backtrack(board, solution, type, blockNumOfCells, blockNumRow, blockNumCol);
					if (success)
					{
						cell->value = 0;
						return true;
					}
				}
				cell->value = 0;
				return false;
			}
		}
	}
#ifdef DEBUG
	/*printf("middle backtrack");*/
#endif
	for (i = 0; i < blockNumOfCells; i++)
	{
		for (j = 0; j < blockNumOfCells; j++)
		{
			solution[i][j].value = board[i][j].value;
		}
	}
	return true;
}

int deterChoice(int *options)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if (options[i] == 1)
		{
			options[i] = 0;
			i++;
			return i;
		}
	}
	return 0;
}


int randomChoice(int *options, int numOfOptions)

{
	int r, i, count = 0;

	if (numOfOptions == 1){
		r = 0;
	}
	else{
		r = rand() % numOfOptions;
	}

	for (i = 0; i < 9; i++)
	{
		if (options[i] == 1)
		{
			if (count == r)
			{
				options[i] = 0;
				i++;
				return i;
			}
			count++;
		}
	}
	return 0;
}

/*
 * @pre: options is an array of size 9 and initialized to 0s
 * x - row
 * y - col
 */
int allValidCellSol(Cell **board, int *options, int blockNumOfCells, int blockNumRows, int blockNumCols, Cell *cell, int x, int y, bool isZeroBased)
{
	/*int a[9] = {1,2,3,4,5,6,7,8,9};
	int* p=a;
	if (board[0][0].value==cells[0].value)
		return p;
	else
		return p;*/

	int i;
	int cnt = 0;

	for (i = 0; i < 9; i++)
	{
		if (validCellSol(board, blockNumOfCells, blockNumRows, blockNumCols, cell, y, x, i + 1, isZeroBased) == true) {
			options[i] = 1;
			cnt++;
		}
	}

	return cnt;
}

/*
 * Generates a board with x empty cells randomly where x=numOfEmptyCells
 * blockNumOfCells is also num of cells in row/column
 */
void generator(Cell **board, Cell **solution, int blockNumOfCells, int numOfFixed)
{
	/*int temp = board[0][0].value, temp2 = solution[0][0].value;
	 board[0][0].value = temp;
	 solution[0][0].value = temp2;
	 numOfFixed++;
	 return;*/

	int i, j, k, randCol, randRow;


	for (i = 0; i < blockNumOfCells; i++)
	{
		for (j = 0; j < blockNumOfCells; j++)
		{
			board[i][j].value = 0;
			board[i][j].fixed = false;
		}
	}

	for (k = 0; k < numOfFixed; k++) {
		do {
			randCol = rand() % blockNumOfCells;
			randRow = rand() % blockNumOfCells;
		} while (board[randRow][randCol].fixed == true);
		board[randRow][randCol].value = solution[randRow][randCol].value;
		board[randRow][randCol].fixed = true;
	}
}

/*
 * return true if z is a valid solution to cell (x,y)
 * return false otherwise
 * blockNumOfCells is also num of cells in row/column
 * x - col
 * y - row
 */
bool validCellSol(Cell **board, int blockNumOfCells, int blockNumRows, int blockNumCols, Cell *cell, int x, int y, int z, bool isZeroBased)
{
	/*x++;
	y++;
	z++;
	if (board[0][0].value==cell[0].value)
		return true;
	else
		return true;*/

	/* if x,y are 1-based, change them to 0-based */
	if (!isZeroBased)
	{
		x--;
		y--;
	}

	if (!(cell->fixed) && z==0)
		return true;
	if (!(cell->fixed) && !valueInRow(board, blockNumOfCells, x, y, z) && !valueInColumn(board, blockNumOfCells, x, y, z) && !valueInBlock(board, blockNumRows, blockNumCols, x, y, z))
		return true;
	return false;
}

/*
 * @pre: x,y are 0-based
 * x - column
 * y - row
 * z - value to check
 */
bool valueInRow(Cell **board, int numOfCellsInRow, int x, int y, int z)
{
	int j;

	for (j = 0; j < numOfCellsInRow; j++)
	{
		if (board[y][j].value == z && j != x) /* z in row y in column!=x */
			return true;
	}
	return false;
}

/*
 * @pre: x,y are 0-based
 * x - column
 * y - row
 * z - value to check
 */
bool valueInColumn(Cell **board, int numOfCellsInCol, int x, int y, int z)
{
	int i;

	for (i = 0; i < numOfCellsInCol; i++)
	{
		if (board[i][x].value == z && i != y) /* z in column x in row!=y */
			return true;
	}
	return false;
}

/*
 * @pre: x,y are 0-based
 * x - column
 * y - row
 * z - value to check
 */
bool valueInBlock(Cell **board, int blockNumRows, int blockNumCols, int x, int y, int z)
{
	int i, j, firstRow, firstCol;

	firstRow = firstRowInBlock(y, blockNumRows); /* index of first row in the block */
	firstCol = firstColInBlock(x, blockNumCols); /* index of first column in the block */

	for (i = firstRow; i < firstRow + blockNumRows; i++)
	{
		for (j = firstCol; j < firstCol + blockNumCols; j++)
		{
			if (board[i][j].value == z && i != y && j != x) /* z in the block */
				return true;
		}
	}

	return false;
}

/*
 * @pre: row is 0-based
 */
int firstRowInBlock(int row, int blockNumRows)
{
	return (row / blockNumRows) * blockNumRows;
}

/*
 * @pre: col is 0-based
 */
int firstColInBlock(int col, int blockNumCols)
{
	return (col / blockNumCols) * blockNumCols;
}
