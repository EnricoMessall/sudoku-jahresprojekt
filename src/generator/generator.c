//
// Created by enrico on 19.05.20.
//

#include "generator.h"

int matchLine(int direction, int x, int y, int width, int number, int fields[9][9][2]){
    int count = 0;
    for(int i = 0; i < width; i++){
        int fieldValue = fields[direction == VERTICAL_LINE ? x : i][direction == HORIZONTAL_LINE ? y : i][0];
        if(fieldValue == number) count++;
    }

    return count == 0 ? 2 : count - 1;
}

void matchBox(int x, int y, const int fields[9][9][2], int zone[3][3]) {
    int xmultiplier = x/3;
    int ymultiplier = y/3;
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            zone[x][y] = fields[x + (3 * xmultiplier)][y + (3 * ymultiplier)][0];
        }
    }
}

int numberAllowed(int fields[9][9][2], int x, int y, int number){
    int vertical = matchLine(VERTICAL_LINE, x, y, 9, number, fields);
    if(vertical != 2) return 1;

    int horizontal = matchLine(HORIZONTAL_LINE, x, y, 9, number, fields);
    if(horizontal != 2) return 1;

    int zone[3][3];
    matchBox(x, y, fields, zone);
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            if(zone[x][y] == number) return 1;
        }
    }

    return 0;
}

void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

static int getRandomNumber() {
    int array[9] = {1, 2, 3, 4, 5 , 6, 7, 8, 9};
    shuffle(array, 9);
    return array[0];
}

int doGenerate(int array[9][9][2]){
    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            array[x][y][0] = 0;
        }
    }

    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            int numberAllowedValue = 1;
            int number = 1;

            int z = 0;
            while(numberAllowedValue != 0) {
                number = getRandomNumber();
                numberAllowedValue = numberAllowed(array, x, y, number);
                z++;
                if(z > 20) return 1;
            }
            array[x][y][0] = number;
        }
    }

    return 0;
}

Sudoku generateRandom(int difficulty){
    int array[9][9][2] = {};

    while(doGenerate(array) != 0);

    Sudoku sudoku = {.field = array, .difficulty = difficulty, .helpCounter = 0, .startTime = 0};

    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            sudoku.field[x][y][0] = array[x][y][0];
        }
    }

    int fieldsLeft = 0;
    switch(difficulty) {
        case EASY: {
            fieldsLeft = AMOUNT_EASY;
            break;
        }
        case MEDIUM: {
            fieldsLeft = AMOUNT_MEDIUM;
            break;
        }
        case HARD: {
            fieldsLeft = AMOUNT_HARD;
            break;
        }
    }

    for(int i = 0; i < fieldsLeft; i++) {
        int x = getRandomNumber();
        int y = getRandomNumber();

        if(sudoku.field[x][y][1] == 0) {
            sudoku.field[x][y][1] = sudoku.field[x][y][0];
        } else i--;
    }

    return sudoku;
}

