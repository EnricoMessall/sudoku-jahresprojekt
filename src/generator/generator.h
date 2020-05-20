//
// Created by enrico on 19.05.20.
//

#ifndef JAHRESPROJEKT_GENERATOR_H
#define JAHRESPROJEKT_GENERATOR_H

#include "base.h"
int matchLine(int direction, int number, int fields[9][9]);
int matchBox(int fields[9]);
int fullMatch(int fields[9][9]);
fields[9][9] generateRandom(int difficulty);

#endif //JAHRESPROJEKT_GENERATOR_H
