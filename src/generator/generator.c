//
// Created by enrico on 19.05.20.
//

#include "generator.h"

int matchLine(int direction, int number, int fields[9][9]){
    int addition = direction == VERTICAL_LINE ? 3 : 1;
    int startBox;

    if(number <= 3) startBox = 0;
    else if(number <= 6) startBox = 1 * (direction == VERTICAL_LINE ? 1 : 3);
    else if(number <= 9) startBox = 2 * (direction == VERTICAL_LINE ? 1 : 3);
    else startBox = 0;

    int field = number % 3;
    if(field == 0) field = 3;
    field--;

    int nextBox = startBox + addition, lastBox = nextBox + addition;
    int lineFields[9] = {fields[startBox][field], fields[startBox][addition + field], fields[startBox][(2 * addition) + field],
                         fields[nextBox][field], fields[nextBox][addition + field], fields[nextBox][(2 * addition) + field],
                         fields[lastBox][field], fields[lastBox][addition + field], fields[lastBox][(2 * addition) + field]};
    printf("\n\nDirection: %d\nField: %d\nBoxes: %d, %d, %d\nPositions: %d, %d, %d\nValues: %d, %d, %d, %d, %d, %d, %d, %d, %d\n\n",
            direction, field, startBox, nextBox, lastBox, field, addition + field, (2 * addition) + field,
            lineFields[0],lineFields[1],lineFields[2],lineFields[3],lineFields[4],lineFields[5],lineFields[6],lineFields[7],lineFields[8]);
    return matchBox(lineFields);
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
    for(int i = 0; i < 9 ; i++){
        int match = matchBox(fields[i]);
        if(match != 0) return match;
    }

    for(int i = 1; i <= 9; i++){
        int match = matchLine(VERTICAL_LINE, i, fields);
        if(match != 0) return match;
    }

    for(int i = 1; i <= 9; i++){
        int match = matchLine(HORIZONTAL_LINE, i, fields);
        if(match != 0) return match;
    }

    return 0;
}

Sudoku generateRandom(int difficulty){
    int array[2][9][9] = {};
    int match = 1;
    while(match != 0){
        for(int i = 0; i < 9; i++){
            for(int i2 = 0; i2 < 9; i2++){
                int random = (rand() % 9) + 1;
                array[0][i][i2] = random;
                printf("%d\n", random);
            }
        }

        printf("Matching");
        match = fullMatch(array[0]);
    }

    Sudoku sudoku = {.field = array, .difficulty = difficulty, .helpCounter = 0, .startTime = 0};
    return sudoku;
}

