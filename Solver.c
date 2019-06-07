#include "Solver.h"

/* if succeed return true and update the solution
 * else return false and doesn't change solution
 */
bool backtrack(Cell** board, Cell** solution, SolverType type) {
	if (board[0][0].value==solution[0][0].value && type==Deterministic)
		return true;
	else
		return false;
}

int deterChoice(int* possibilities) {
	if (possibilities[0]==1)
		return 0;
	else
		return 0;
}

int randomChoice(int* possibilities) {
	if (possibilities[0]==1)
			return 0;
		else
			return 0;
}

/*
 * @pre: options is an array of size 9 and initialized to 0s
 */
void allValidCellSol(Cell** board, int options[], int blockNumOfCells, int blockNumRows, int blockNumCols, Cell* cell, int x, int y, bool isZeroBased) {
	/*int a[9] = {1,2,3,4,5,6,7,8,9};
	int* p=a;
	if (board[0][0].value==cells[0].value)
		return p;
	else
		return p;*/

	int i;

	for (i=0; i<9; i++) {
		if (validCellSol(board, blockNumOfCells, blockNumRows, blockNumCols, cell, x, y, i+1, isZeroBased)==true)
			options[i] = 1;
	}
}

/*
 * Generates a board with x empty cells randomly where x=numOfEmptyCells
 * blockNumOfCells is also num of cells in row/column
 */
void generator(Cell** board, Cell** solution, int numOfCells, int blockNumOfCells, int numOfEmptyCells) {
	/*int temp = board[0][0].value, temp2 = solution[0][0].value;
	 board[0][0].value = temp;
	 solution[0][0].value = temp2;
	 numOfFixed++;
	 return;*/

	int i, j, k, r;

	/* Intializes random number generator */
	srand(time(NULL));

	for (i = 0; i < blockNumOfCells; i++) {
		for (j = 0; j < blockNumOfCells; j++) {
			board[i][j].value = solution[i][j].value;
			board[i][j].fixed = true;
		}
	}

	for (k = 0; k < numOfEmptyCells; k++) {
		r = rand() % numOfCells;
		board[(int) (r / blockNumOfCells)][r % blockNumOfCells].value = 0;
		board[(int) (r / blockNumOfCells)][r % blockNumOfCells].fixed = false;
	}
}

/*
 * return true if z is a valid solution to cell (x,y)
 * return false otherwise
 * blockNumOfCells is also num of cells in row/column
 */
bool validCellSol(Cell** board, int blockNumOfCells, int blockNumRows, int blockNumCols, Cell* cell, int x, int y, int z, bool isZeroBased) {
	/*x++;
	y++;
	z++;
	if (board[0][0].value==cell[0].value)
		return true;
	else
		return true;*/

	/* if x,y are 1-based, change them to 0-based */
	if (!isZeroBased) {
		x--;
		y--;
	}

	if (!(cell->fixed) && !valueInRow(board, blockNumOfCells, x, y, z) && !valueInColumn(board, blockNumOfCells, x,y,z) && !valueInBlock(board, blockNumRows, blockNumCols, x,y,z))
		return true;
	return false;
}

/*
 * @pre: x,y are 0-based
 * x - column
 * y - row
 * z - value to check
 */
bool valueInRow(Cell** board, int numOfCellsInRow, int x, int y, int z) {
	int j;

	for (j=0; j<numOfCellsInRow; j++) {
		if (board[y][j].value == z && j!=x) /* z in row y in column!=x */
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
bool valueInColumn(Cell** board, int numOfCellsInCol, int x, int y, int z) {
	int i;

	for (i=0; i<numOfCellsInCol; i++) {
		if (board[i][x].value == z && i!=y) /* z in column x in row!=y */
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
bool valueInBlock(Cell** board, int blockNumRows, int blockNumCols, int x, int y, int z) {
	int i, j, firstRow, firstCol;

	firstRow=firstRowInBlock(y, blockNumRows); /* index of first row in the block */
	firstCol=firstColInBlock(x, blockNumCols); /* index of first column in the block */

	for(i=firstRow; i<firstRow+blockNumRows; i++) {
		for(j=firstCol; j<firstCol+blockNumCols; j++) {
			if (board[i][j].value==z && i!=y && j!=x) /* z in the block */
				return true;
		}
	}

	return false;
}

/*
 * @pre: row is 0-based
 */
int firstRowInBlock(int row, int blockNumRows) {
	return floor(row/blockNumRows)*blockNumRows;
}

/*
 * @pre: col is 0-based
 */
int firstColInBlock(int col, int blockNumCols) {
	return floor(col/blockNumCols)*blockNumCols;
}
