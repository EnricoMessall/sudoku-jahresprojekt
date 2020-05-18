#include <commands.h>
#include <base.h>


#define CHANGESTATE_NOTHING 0
#define CHANGESTATE_MENU 1

typedef struct fieldChange {
    int x;
    int y;
    int value;
} FieldChange;

typedef struct change {
    int changeState;
    FieldChange fieldChange;
} Change;

void printField(Sudoku sudoku);

void printLeaderboard(LeaderBoardElement *leaderBoardElement, int amount);

void printMenu(Menu menu);

Command getMenuSelection(Menu menu);

/*
    Description:
        Asks the user for a difficulty
    Value:
        The difficulty
*/
int getDifficulty(void);

/*
    Description:
        Returns the Change
*/
Change getChange(void);

void getHintCoordinates(int * coordinates);