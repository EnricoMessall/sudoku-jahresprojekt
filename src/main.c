//
// Created by Nicolas on 11.05.2020.
//

#include <stdio.h>
#include "generator/generator.c"

int main() {
    int array[9][9] = {
            {0,2,3,7,8,9,4,5,6},
            {7,5,6,0,2,3,7,8,9},
            {5,8,9,4,5,6,1,2,3},
            {4,0,2,9,3,4,8,6,7},
            {6,4,7,8,0,5,9,3,2},
            {1,3,8,2,6,7,5,1,4},
            {0,4,8,3,9,5,6,7,0},
            {3,7,1,2,6,1,5,9,8},
            {8,9,5,8,7,0,3,4,1}
    };
    int zone[3][3];
    matchBox(3, 3, array, zone);
    for(int xtemp = 0; xtemp < 3; xtemp++) {
        for(int ytemp = 0; ytemp < 3; ytemp++) {
            if(zone[xtemp][ytemp] == 1) printf("Box Contains 1\n");
        }
    }

    Sudoku sudoku = generateRandom(HARD);

    for(int x = 0; x < 9; x++){
        int printArray[9];
        for(int y = 0; y < 9; y++){
            printArray[y] = sudoku.field[x][y][1];
        }

        printf("%d %d %d | %d %d %d | %d %d %d\n", printArray[0], printArray[1], printArray[2], printArray[3],
               printArray[4], printArray[5], printArray[6], printArray[7], printArray[8]);
    }

    return 0;
}
