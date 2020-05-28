#include <gui-konsole.c>
#include <leaderboard.c>
#include <string.h>
#include <generator.c>

int compareStrings(char * str1, char * str2);

#define STATE_LEADERBOARD 2
#define STATE_MAIN 0
#define STATE_GAME 1

int main() {
    clearConsole();
    Sudoku sudoku;
    int state = 0;
    while((1)) {
        switch(state) {
            case STATE_MAIN: {
                Menu menu = getMenu(STATE_MAIN, 0);
                printMenu(menu);
                Command command = getMenuSelection(menu);
                if(strcmp("Leaderboard Menu", command.name) == 0) {
                    clearConsole();
                    state = 2;
                } else if(strcmp("New Game", command.name) == 0) {
                    clearConsole();
                    sudoku = createNew(getDifficulty());
                    clearConsole();
                    sudoku.helpCounter = 0;
                    state = 1;
                } else if(strcmp("Exit", command.name) == 0) {
                    clearConsole();
                    exit(0);
                } else if(strcmp("Print Rules", command.name) == 0) {
                    clearConsole();
                    printRules();
                }
                break;
            }
            case STATE_GAME: {
                if(isSolved(sudoku) == 1) {
                    //solved
                    LeaderBoardElement element = {
                        .difficulty = sudoku.difficulty,
                        .time = calculateScore(sudoku)
                    };

                    printWin(sudoku.difficulty, element.time);
                    getUsername(element.user);

                    save(element);
                    state = 0;
                } else {
                    //not solved
                    printField(sudoku);
                    Change change = getChange();

                    if(change.changeState == CHANGESTATE_NOTHING) {
                        sudoku.field[change.fieldChange.x][change.fieldChange.y][1] = change.fieldChange.value;
                        clearConsole();
                    } else if(change.changeState == CHANGESTATE_MENU) {
                        clearConsole();
                        Menu menu = getMenu(STATE_GAME, 1);
                        printMenu(menu);
                        Command command = getMenuSelection(menu);
                        if(strcmp("Game Hint", command.name) == 0) {
                            clearConsole();
                            printField(sudoku);
                            int coordinates[2];
                            getHintCoordinates(coordinates);
                            sudoku.field[coordinates[0]][coordinates[1]][1] = sudoku.field[coordinates[0]][coordinates[1]][0];
                            sudoku.helpCounter++;
                            clearConsole();
                        } else if(strcmp("Exit", command.name) == 0) {
                            exit(0);
                        } else if(strcmp("Back", command.name) == 0) {
                            clearConsole();
                            continue;
                        } else if(strcmp("New Game", command.name) == 0) {
                            clearConsole();
                            sudoku = createNew(getDifficulty());
                            clearConsole();
                            sudoku.helpCounter = 0;
                        } else if(strcmp("Quit Game", command.name) == 0) {
                            clearConsole();
                            state = 0;
                        } else if(strcmp("Print Rules", command.name) == 0) {
                            clearConsole();
                            printRules();
                        }
                    }
                }
                break;
            }
            case STATE_LEADERBOARD: {
                Menu menu = getMenu(STATE_LEADERBOARD, 1);
                printMenu(menu);
                Command command = getMenuSelection(menu);

                if(strcmp("Back", command.name) == 0) {
                    clearConsole();
                    state = 0;
                } else if(strcmp("Exit", command.name) == 0) {
                    exit(0);
                } else if(strcmp("Print Leaderboard", command.name) == 0) {
                    clearConsole();
                    int difficulty = getDifficulty();
                    clearConsole();
                    LeaderBoardElement * elements = getLeaderBoardElements(difficulty);
                    if(strcmp(elements[0].user, "") == 0) {
                        //TODO keine elemente
                        printLeaderboard(NULL, 0);
                    } else {
                        printLeaderboard(elements, 10);
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