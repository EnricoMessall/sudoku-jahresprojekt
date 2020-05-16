#include <commands.h>
#include <base.h>

#define CHANGESTATE_NOTHING 0
#define CHANGESTATE_GAME_NEW 1
#define CHANGESTATE_GAME_QUIT 2
#define CHANGESTATE_REQUEST_HINT 3
#define CHANGESTATE_REQUEST_DESCRIPTION 4

typedef struct fieldChange {
    int location[2];
    int change;
} FieldChange;

typedef struct change {
    int changeState;
    FieldChange fieldChange;
} Change;

void printField(Sudoku sudoku);

void printLeaderboard(LeaderBoardElement *leaderBoardElement);

void printMenu(int state);

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
