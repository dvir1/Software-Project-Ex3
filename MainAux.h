#ifndef MAINAUX_H_
#define MAINAUX_H_

#include <stdio.h>
#include <stdbool.h>
#define DEBUG

typedef enum {Deterministic, Randomized} SolverType;

typedef struct {
	bool fixed;
	int value;
} Cell;

#endif /* MAINAUX_H_ */
