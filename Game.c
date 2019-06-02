#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MainAux.h"
#include "Solver.h"

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
Cell* boardCellAccess(int x, int y){
	/*int row = (y-1)*blockNumOfCells;*/
	int row = y-1;
	int col = x-1;
	/*return (&(board[row+col]));*/
	return (&(board[row][col]));
}

/* 
 * return a pointer to cell <x,y> 
 */
Cell* solutionCellAccess(int x, int y){
	/*int row = (y-1)*blockNumOfCells;*/
	int row = y-1;
	int col = x-1;
	/*return (&(solution[row+col]));*/
	return (&(solution[row][col]));
}

/*
 * print "Exiting...\n" and exit program
 */
void printExitAndExit() {
	printf("Exiting...\n");
	exit(0);
}

void CreateBoard(int blockNumOfRows, int blockNumOfCols, int numOfFixed) {
	int i;
	blockNumCol = blockNumOfCols;
	blockNumRow = blockNumOfRows;
	blockNumOfCells = blockNumCol*blockNumRow;
	numOfCells = blockNumOfCells*blockNumOfCells;
	numOfEmptyCells = numOfCells - numOfFixed;
	board = (Cell**)calloc(blockNumOfCells, sizeof(Cell*));
	for (i=0; i<blockNumOfCells; i++){
		board[i] = (Cell*)calloc(blockNumOfCells, sizeof(Cell));
	}
	solution = (Cell**)calloc(blockNumOfCells, sizeof(Cell*));
	for (i=0; i<blockNumOfCells; i++){
		solution[i] = (Cell*)calloc(blockNumOfCells, sizeof(Cell));
	}
	generator(board, solution, numOfFixed);
	printf("CreateBoard params: %d, %d, %d", blockNumRow, blockNumCol, numOfFixed);
}

void set(int x, int y, int z) {
	Cell *cell;
	if (endGame()){
		invalidCommand();
		return;
	}
	cell = boardCellAccess(x, y);
	if (cell->fixed){
		printf("Error: cell is fixed\n");
		return;
	}
	if (!validCellSol(board, cell, x, y, z)){
		printf("ErrorL value is invalid\n");
		return;
	}
	if (cell->value==0){
		if (z!=0){
			numOfEmptyCells--;
		}
	}
	else {
		if (z==0){
			numOfEmptyCells++;
		}
	}
	cell->value = z;
	printBoard();
	if (endGame()){
		printf("Puzzle solved successfully\n");
	}
	printf("set params: %d, %d, %d", x, y, z);
	return;
}

void hint(int x, int y) {
	Cell *cell;
	if (endGame()){
		invalidCommand();
		return;
	}
	cell = solutionCellAccess(x, y);
	printf("Hint: set cell to %d\n", cell->value);
	printf("set hint: %d, %d", x, y);
	return;
}

void validate() {
	bool success;
	if (endGame()){
		invalidCommand();
		return;
	}
	success = backtrack(board, solution, Deterministic);
	if (success){
		printf("Validation passed: board is solvable\n");
	}
	else{
		printf("Validation failed: board is unsolvable\n");
	}
	return;
}

void exitGame() {
	free(board);
	free(solution);
	return;
}

bool endGame() {
	return numOfEmptyCells==0;
}

void printBoard(){
	Cell *cell;
	int cellRow, cellCol;
	int i, j, k, r, l;
	int M = blockNumRow; /*num of blocks in a row*/
	int N = blockNumCol; /*num of cells in a block row*/
	int C = 3; /*num of chars every cell take to print*/
	int numOfdashes = M*(N*C+2)+1;
	
	for (l=0, l<numOfdashes, l++){
		printf("-");
	}
	printf("\n");

	for (k=0, k<N, k++){ /*for every row of blocks*/
		for (r=0, r<M, r++){ /*for every row of a block*/
			for (j=0, j<M, j++){ /*for every col of blocks*/
				printf("| ");
				for (i=0; i<N, i++){ /*for every col of a block*/
					cellRow = (k*M)+r+1;
					cellCol = (j*N)+i+1;
					cell = boardCellAccess(cellCol, cellRow);
					if (cell->fixed){
						printf(".");
					}
					else {
						printf(" ");
					}
					printf("%d ", cell->value);
				}
			}
			printf("|\n");
		}
		for (l=0, l<numOfdashes, l++){
			printf("-");
		}
		printf("\n");
	}
	return;
}

void invalidCommand(){
	printf("Error: invalid command/n");
	return;
}