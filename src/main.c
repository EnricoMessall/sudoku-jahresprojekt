//
// Created by Nicolas on 11.05.2020.
//

#include <stdio.h>
#include "generator/generator.c"

int main() {
    int array[9][9] = {
            {1,2,3,7,8,9,4,5,6},
            {4,5,6,1,2,3,7,8,9},
            {7,8,9,4,5,6,1,2,3},
            {5,1,2,9,3,4,8,6,7},
            {6,4,7,8,1,5,9,3,2},
            {9,3,8,2,6,7,5,1,4},
            {2,4,8,3,9,5,6,7,1},
            {3,7,1,2,6,4,5,9,8},
            {6,9,5,8,7,1,3,4,2}
    };


    printf("%d\n", fullMatch(array));

    /*Sudoku sudoku = generateRandom(2);

    for(int i = 0; i < 9; i++){
        for(int i2 = 0; i2 < 9; i2++){
            printf("%d, ", sudoku.field[0][i][i2]);
        }
    }*/

    return 0;
}
