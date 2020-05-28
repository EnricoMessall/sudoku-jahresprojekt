#include <generator.h>

/*
    returns:
        0 = not allowed;
        1 = allowed
*/
int numberAllowed(int field[9][9], int x, int y, int value) {
    //Vertical
    for(int i = 0; i < 9; i++) {
        if(field[x][i] == value) return 0;
    }

    //Horizontal
    for(int i = 0; i < 9; i++) {
        if(field[i][y] == value) return 0;
    }

    //Zone
    int zone[3][3];
    getZone(field, x, y, zone);
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            if(zone[x][y] == value) return 0;
        }
    }

    return 1;
}

void getZone(int field[9][9], int x, int y, int zone[3][3]) {
    if(x <= 2) {
        if(y <= 2) {
            //Oben links
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x][y];
                }
            }
        } else if (y <= 5) {
            //Mitte links
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x][y + 3];
                }
            }
        } else {
            //Unten links
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x][y + 6];
                }
            }
        }
    } else if(x <= 5) {
        if(y <= 2) {
            //Oben mitte
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x + 3][y];
                }
            }
        } else if (y <= 5) {
            //Mitte mitte
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x + 3][y + 3];
                }
            }
        } else {
            //unten mitte
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x + 3][y + 6];
                }
            }
        }
    } else {
        if(y <= 2) {
            //rechts oben
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x + 6][y];
                }
            }
        } else if (y <= 5) {
            //rechts mitte
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x + 6][y + 3];
                }
            }
        } else {
            //rechts unten
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    zone[x][y] = field[x + 6][y + 6];
                }
            }
        }
    }

}

static int getRandomNumber() {
    static int x = 0;
    if(x == 0) {
        srand((unsigned int)time(NULL));
        x = 1;
    }
    return rand() % 9 + 1;
}

Sudoku createNew(int difficulty) {
    int field[9][9];
    loop:
    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            field[x][y] = 0;
        }
    }
    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            int numberAllowedValue = 0;
            int number = 0;
            
            int z = 0;
            while(numberAllowedValue == 0) {
                number = getRandomNumber();
                numberAllowedValue = numberAllowed(field, x, y, number);
                z++;
                if(z > 50) goto loop; //aua
            }
            field[x][y] = number;
        }
    }
    Sudoku sudoku;
    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            sudoku.field[x][y][0] = field[x][y];
            sudoku.field[x][y][1] = 0;
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
        int x = rand() % 9;
        int y = rand() % 9;

        if(sudoku.field[x][y][1] == 0) {
            sudoku.field[x][y][1] = sudoku.field[x][y][0];
        } else i--;
    }

    sudoku.startTime = (long)time(NULL);
    sudoku.difficulty = difficulty;
    return sudoku;
}

int calculateScore(Sudoku sudoku) {
    return time(NULL) - sudoku.startTime + (sudoku.helpCounter * 30);
}

int isSolved(Sudoku sudoku) {
    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            if(sudoku.field[x][y][1] != sudoku.field[x][y][0]) return 0;
        }
    }
    return 1;
}