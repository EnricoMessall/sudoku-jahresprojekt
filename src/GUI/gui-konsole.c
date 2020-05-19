#include <gui.h>
#include <stdio.h>
#include <stdlib.h>

/*
    description:
        parses the given difficulty to a char array
    variables:
        difficulty:
            0 = EASY
            1 = MEDIUM
            2 = HARD
    returns:
        the char* version of the given difficulty
*/
char* parseDifficulty(int difficulty) {
    switch(difficulty) {
        case EASY: {
            return "EASY";
        }
        case MEDIUM: {
            return "MEDIUM";
        }
        case HARD: {
            return "HARD";
        }
        default: {
            printf("ERROR: Unknown Difficulty!");
            exit(-2);
        }
    }
}

/*
    description:
        prints the given field in the console
    variables:
        field[9][9]:
            the sudoku field
*/
void printField(Sudoku sudoku) {
    printf("===================================\n");
    printf("||      Difficulty: %6s       ||\n", parseDifficulty(sudoku.difficulty));
    printf("===================================\n");
    printf("||   | A B C | D E F | G H I |   ||\n");
    printf("|| ----------------------------- ||\n");
    for(int y = 0; y < 9; y++) {
        if(y != 0 && y % 3 == 0) {
            printf("|| ----------------------------- ||\n");
        }
        printf("|| %i | ", y+1);
        for(int x = 0; x < 9; x++) {
            if(x != 0 && x % 3 == 0) {
                printf("| ");
            }
            if(sudoku.field[x][y][1] == 0) {
                printf(". ");
            } else {
                printf("%i ", sudoku.field[x][y][1]);
            }
        }
        printf("| %i ||\n", y+1);
    }
    printf("|| ----------------------------- ||\n");
    printf("||   | A B C | D E F | G H I |   ||\n");
    printf("==================================\n");
}  

void printHintDialog(int coordinates[2], int old, int new) {
    char oldChar = '.';
    if(old != 0) {
        oldChar = old + 48;
    }
    printf("Value at X:%i,Y:%i was changed: %c --> %i\n", coordinates[0], coordinates[1], oldChar, new);
}

/*
    description:
        asks the user for coordinates
    variables:
        coordinates:
            a 2 dim int array which is changed acording to the user input
*/
void getHintCoordinates(int coordinates[2]) {
    char input[3];
    coordinates[0] = -1;
    coordinates[1] = -1;
    do {
        printf("Please enter Coordinates (Example: A1)\n");
        printf("Input: ");
        scanf("%3s", input);
        if(sizeof(input) > 0) {
            // X Handling
            if(input[0] >= 65 && input[0] <= 73) {
                coordinates[0] = input[0] - 65;
            } else if(input[0] >= 97 && input[0] <= 105) {
                coordinates[0] = input[0] - 97;
            } 

            // Y Handling
            if(input[1] >= 49 && input[1] <= 57) {
                coordinates[1] = input[1] - 48 - 1; //PrintField has y + 1
            }
        }
    } while(coordinates[0] == -1 || coordinates[1] == -1);
}

/*
    description:
        asks the user which command should be selected an returns it
    variables:
        menu:
            the menu which should be used
    returns:
        the selected command
*/
Command getMenuSelection(Menu menu) {
    int menuSelection = 0;
    do {
        printf("Input (1-%i): ", menu.commandAmount);
        scanf("%i", &menuSelection);
    } while(menuSelection < 1 || menuSelection > menu.commandAmount);
    return menu.commands[menuSelection-1];
}

/*
    description:
        Returns the menu corresponding to the state

    variables:
        state:
            which menu should be genereated
        back:
            0 = without back option
            1 = with back option
    return:

*/
Menu getMenu(int state, int back) {
    Command * commands = malloc(sizeof(VALID_COMMANDS));
    int amount = 0;
    for(int i = 0; i < sizeof(VALID_COMMANDS)/sizeof(VALID_COMMANDS[0]); i++) {
        for(int j = 0; j < COMMAND_MAX_CATEGORIES; j++) {
            if(VALID_COMMANDS[i].categories[j] == CATEGORY_GENERAL || VALID_COMMANDS[i].categories[j] == state + 2) { //+2 = CATEGORY THRESHHOLD
                commands[amount] = VALID_COMMANDS[i];
                commands[amount].selection = amount + 1;
                amount++;
            }
        }
    }
    //if back command should be enabled
    if((back)) {
        commands[amount] = COMMAND_BACK;
        commands[amount].selection = amount+1;
        amount++;
    }
    Menu menu = {
        commands,
        amount,
        state
    };
    return menu;
}

/*
    descrption:
        prints the menu in console depending of the state
    variables:
        menu:
            The menu which is printed
*/
void printMenu(Menu menu) {
    switch(menu.state) {
        case 0: {
            printf("###### Main Menu ######\n");
            break;
        };
        case 1: {
            printf("###### Game Menu ######\n");
            break;
        };
        case 2: {
            printf("## Leaderboards Menu ##\n");
            break;
        }
        default: {
            printf("Error: illegal gamestate!");
            exit(-1);
        }
    }
    for(int i = 0; i < menu.commandAmount; i++) {
        printf("[%i] %s\n", i+1, menu.commands[i].name);
    }
}

/*
    description:
        parses the time to a human readable one
    variables:
        time:
            the time as long in milliseconds
    returns:
        the time as float in seconds
*/
float parseTime(long time) {
    float tmp = time;
    return tmp / 1000;
}

/*
    description:
        prints the leaderboard in the console
    variables:
        *leadBoardElement:
            a pointer to the leaderboardelements
        amount:
            amount of leaderboardelements which were represented by the pointer
*/
void printLeaderboard(LeaderBoardElement *leaderBoardElement, int amount) {
    if(amount > 0) {
        printf("==============================================\n");
        printf("|| LEADERBOARD | Difficulty: %6s         ||\n", parseDifficulty(leaderBoardElement[0].difficulty));
        printf("==============================================\n");
        printf("|| %5s | %16s | %13s ||\n", "PLACE", "USERNAME", "TIME (in sec)");
        for(int i = 0; i < amount; i++) {
            if(i % 10 == 0) {
                printf("|| ------|------------------|-------------- ||\n");
            }
            printf("|| %4i. | %16s | %13.4f ||\n", i+1, leaderBoardElement[i].user, parseTime(leaderBoardElement[i].time));
        }
        printf("==============================================\n");
    } else {
        printf("No records in leaderboard for selected difficulty found!\n");
    }
}

/*
    description:
        asks the user for a difficulty and checks the input
    return:
        the difficulty:
            0 = EASY
            1 = MEDIUM
            2 = HARD
    
*/
int getDifficulty(void) {
    int difficulty = 0;
    do {
        printf("Difficulties:\n");
        printf("[1] EASY\n");
        printf("[2] MEDIUM\n");
        printf("[3] HARD\n\nPlease select difficulty: ");
        scanf("%i", &difficulty);
    } while(difficulty != 1 && difficulty != 2 && difficulty != 3);
    return difficulty - 1;
}

/*
    description:
       returns a change after a dialog with the user
    returns:
        returns a change with changestate 1 if user requested the menu
        returns a change with a fieldChange if the user entered Coordinates
*/
Change getChange(void) {
    char input[5];
    int x = -1;
    int y = -1;
    int value = -1;
    do {
        printf("Please enter Coordinates (Example: A1-2) or 'm' for menu\n");
        printf("Input: ");
        scanf("%5s", input);
        if(sizeof(input) > 0) {
            //menu
            if(input[0] == 'm') {
                Change change = {
                    .changeState = CHANGESTATE_MENU
                };
                return change;
            }

            // X Handling
            if(input[0] >= 65 && input[0] <= 73) {
                x = input[0] - 65;
            } else if(input[0] >= 97 && input[0] <= 105) {
                x = input[0] - 97;
            } 

            // Y Handling
            if(input[1] >= 49 && input[1] <= 57) {
                y = input[1] - 48 - 1; //PrintField has y + 1
            }

            if(input[3] >= 49 && input[3] <= 57) {
                value = input[3] - 48;
            }
        }
    } while(x == -1 || y == -1 || value == -1);

    FieldChange fieldChange = {
        x,
        y,
        value
    };
    Change change = {
        CHANGESTATE_NOTHING,
        fieldChange
    };
    return change;
}
