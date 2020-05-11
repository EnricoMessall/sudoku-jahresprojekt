#include <stdio.h>

int printField(int field[9][9][2]) {
    printf("  | A B C | D E F | G H I\n");
    printf("-------------------------\n");
    for(int y = 0; y < 9; y++) {
        if(y != 0 && y % 3 == 0) {
            printf("-------------------------\n");
        }
        printf("%i | ", y+1);
        for(int x = 0; x < 9; x++) {
            if(x != 0 && x % 3 == 0) {
                printf("| ");
            }
            printf("%i ", field[x][y][1]);
        }
        printf("\n");
    }
}  