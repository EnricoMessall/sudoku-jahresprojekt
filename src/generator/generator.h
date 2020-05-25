//
// Created by enrico on 19.05.20.
//

#ifndef JAHRESPROJEKT_GENERATOR_H
#define JAHRESPROJEKT_GENERATOR_H

#define VERTICAL_LINE 0
#define HORIZONTAL_LINE 1

#include "base.h"
#include <stdlib.h>
int matchLine(int direction, int number, int fields[9][9]);

/**
 * Returns an number between 0 and 2
 * 0 = Box Matches has no number twice
 * 1 = Box Does Not Match
 * 2 = Box has an empty field
 * @param fields Box Array
 * @return Match Status
 */
int matchBox(const int fields[9]);
int fullMatch(int fields[9][9]);
Sudoku generateRandom(int difficulty);

#endif //JAHRESPROJEKT_GENERATOR_H
