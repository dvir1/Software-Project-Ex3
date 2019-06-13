#ifndef MAINAUX_H_
#define MAINAUX_H_

#include <stdio.h>
#include <stdbool.h>

typedef enum {Deterministic, Randomized} SolverType;

typedef struct {
	bool fixed;
	int value;
} Cell;

#endif /* MAINAUX_H_ */
