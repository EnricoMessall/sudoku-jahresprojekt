#include <base.h>
#include <stdlib.h>
#include <time.h>

#define AMOUNT_EASY 24
#define AMOUNT_MEDIUM 18
#define AMOUNT_HARD 12

int numberAllowed(int field[9][9], int x, int y, int value);
void getZone(int field[9][9], int x, int y, int zone[3][3]);
Sudoku createNew(int difficulty);
int calculateScore(Sudoku sudoku);
int isSolved(Sudoku sudoku);