#include <gui.h>
#include <stdio.h>
#include <stdlib.h>

/*
    description:
        prints the given field in the console
    variables:
        field[9][9]:
            the sudoku field
*/
void printField(Sudoku sudoku) {
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
            printf("%i ", sudoku.field[x][y][1]);
        }
        printf("\n");
    }
}  

/*
    description:
        WARNING: don't call this, use printMenu() instead;
        prints all menu entries of a category
    variables:
        the category which commands should be printed
*/
void printMenuEntries(int category) {
    int commandCounter = 1;
    for(int i = 0; i < sizeof(VALID_COMMANDS)/sizeof(VALID_COMMANDS[0]); i++) {
        for(int j = 0; j < COMMAND_MAX_CATEGORIES; j++) {
            if(VALID_COMMANDS[i].categories[j] == CATEGORY_GENERAL || VALID_COMMANDS[i].categories[j] == category) {
                printf("[%i]: %s\n", commandCounter, VALID_COMMANDS[i].name);
                VALID_COMMANDS[i].tempValue = commandCounter;
                commandCounter++;
            }
        }
    }
}

/*
    descrption:
        prints the menu in console depending of the state
    variables:
        state:
            0 = no game in progress / main menu
            1 = game in progress / game menu
            2 = leaderboards menu
*/
void printMenu(int state) {
    switch(state) {
        case 0: {
            printf("###### Main Menu ######\n");
            printMenuEntries(CATEGORY_MAIN);
            break;
        };
        case 1: {
            printf("###### Game Menu ######\n");
            printMenuEntries(CATEGORY_GAME);          
            break;
        };
        case 2: {
            printf("## Leaderboards Menu ##\n");
            printMenuEntries(CATEGORY_LEADERBOARD);
            break;
        }
        default: {
            printf("Error: illegal gamestate!");
            exit(-1);
        }
    }
}

/*
    TODO
*/
void printCommandHelp(int state) {
    //TODO
}

/*
    description:
        prints the leaderboard in the console
*/
void printLeaderboard(void) {
    //TODO
}

/*
    description:
        reads the userinput in the console;
        checks if its a valid command
*/
char* getUserInput(void) {
    //TODO
}
