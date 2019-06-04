#include "MainAux.h"
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

int* allValidCellSol(Cell** board, Cell* cells) {
	int a[9] = {1,2,3,4,5,6,7,8,9};
	int* p=a;
	if (board[0][0].value==cells[0].value)
		return p;
	else
		return p;
}

void generator(Cell** board, Cell** solution, int numOfFixed) {
	int temp = board[0][0].value, temp2 = solution[0][0].value;
	board[0][0].value = temp;
	solution[0][0].value = temp2;
	numOfFixed++;
	return;
}

/*
 * return true if z is a valid solution to cell (x,y)
 * return false otherwise
 */
bool validCellSol(Cell** board, Cell* cell, int x, int y, int z) {
	x++;
	y++;
	z++;
	if (board[0][0].value==cell[0].value)
		return true;
	else
		return true;
}
