//
// Created by enrico on 19.05.20.
//

#include "generator.h"

int matchLine(int direction, int number, int fields[9][9]){
    if(direction == 0){
        int startBox = (number / 3) - 1, nextBox = startBox + 3, lastBox = nextBox + 3;
        int lineFields[3][] = {fields[startBox], fields[nextBox], fields[lastBox]};
    }
}

int matchBox(const int fields[9]) {
    int count = 0;
    for (int number = 1; number <= 9; number++){
        count = 0;
        for (int field = 0; field < 9; field++) {
            int fieldValue = fields[field];
            if (number == fieldValue) count++;
        }
        if (count > 1 || count == 0) break;
    }
    return count == 0 ? 2 : count - 1;
}

int fullMatch(int fields[9][9]){
    //Does all lines and boxes match?
}

Sudoku generateRandom(int difficulty){

}

