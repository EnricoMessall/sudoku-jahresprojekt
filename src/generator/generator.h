//
// Created by enrico on 19.05.20.
//

#ifndef JAHRESPROJEKT_GENERATOR_H
#define JAHRESPROJEKT_GENERATOR_H

#define VERTICAL_LINE 0
#define HORIZONTAL_LINE 1

#include "base.h"
#include <stdlib.h>
#include <stdio.h>
int matchLine(int direction, int x, int y, int width, int number, int fields[9][9]);
void matchBox(int x, int y, const int fields[9][9], int zone[3][3]);
Sudoku generateRandom(int difficulty);

#endif //JAHRESPROJEKT_GENERATOR_H
