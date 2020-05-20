#include <gui-konsole.c>
#include <leaderboard.c>
#include <string.h>
#include <stdio.h>

int compareStrings(char * str1, char * str2);

#define STATE_LEADERBOARD 2
#define STATE_MAIN 0
#define STATE_GAME 1

int main() {
    Sudoku sudoku;
    sudoku.difficulty = 0;

    for(int y = 0; y < 9; y++) {
        for(int x = 0; x < 9; x++) {
            sudoku.field[x][y][1] = 0;
            sudoku.field[x][y][0] = 0;
        }
    }
    int state = 0;


    LeaderBoardElement element = {
        1,
        1010L,
        "Test"
    };

    LeaderBoardElement element2 = {
        1,
        1010L,
        "Hans"
    };

    save(element);
    save(element2);

    while((1)) {
        switch(state) {
            case STATE_MAIN: {
                Menu menu = getMenu(STATE_MAIN, 0);
                printMenu(menu);
                Command command = getMenuSelection(menu);
                if(compareStrings("Leaderboard Menu", command.name)) {
                    state = 2;
                } else if(compareStrings("New Game", command.name)) {
                    sudoku.difficulty = getDifficulty();

                    for(int y = 0; y < 9; y++) {
                        for(int x = 0; x < 9; x++) {
                            sudoku.field[x][y][1] = 0;
                            sudoku.field[x][y][0] = 0;
                        }
                    }

                    state = 1;
                } else if(compareStrings("Exit", command.name)) {
                        exit(0);
                }
                break;
            }
            case STATE_GAME: {
                printField(sudoku);
                Change change = getChange();
                if(change.changeState == CHANGESTATE_NOTHING) {
                    sudoku.field[change.fieldChange.x][change.fieldChange.y][1] = change.fieldChange.value;
                } else if(change.changeState == CHANGESTATE_MENU) {
                    Menu menu = getMenu(STATE_GAME, 1);
                    printMenu(menu);
                    Command command = getMenuSelection(menu);
                    if(compareStrings("Game Hint", command.name)) {
                        int coordinates[2];
                        getHintCoordinates(coordinates);
                        printHintDialog(coordinates, sudoku.field[coordinates[0]][coordinates[1]][1], sudoku.field[coordinates[0]][coordinates[1]][0]);
                        sudoku.field[coordinates[0]][coordinates[1]][1] = sudoku.field[coordinates[0]][coordinates[1]][0];
                    } else if(compareStrings("Exit", command.name)) {
                        exit(0);
                    } else if(compareStrings("Back", command.name)) {
                        continue;
                    }
                }
                break;
            }
            case STATE_LEADERBOARD: {
                Menu menu = getMenu(STATE_LEADERBOARD, 1);
                printMenu(menu);
                Command command = getMenuSelection(menu);

                if(compareStrings("Back", command.name)) {
                    state = 0;
                } else if(compareStrings("Exit", command.name)) {
                    exit(0);
                } else if(compareStrings("Print Leaderboard", command.name)) {
                    int difficulty = getDifficulty();
                    LeaderBoardElement * elements = getLeaderBoardElements(difficulty);
                    if(strcmp(elements[0].user, "") == 0 && 1 == 0) {
                        //TODO keine elemente
                        printLeaderboard(NULL, 0);
                    } else {
                        printf("%i", elements[0].difficulty);
                        printLeaderboard(elements, 10);
                        //TODO return anzahl
                    }
                }
                break;
            }
        }
    }
    return 0;
}

int compareStrings(char * str1, char * str2) {
    if(strlen(str1) == strlen(str2)) {
        for(int i = 0; i < strlen(str1); i++) {
            if(str1[i] != str2[i]) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}