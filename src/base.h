/**
 * Header Guard, prevents this header file from being inlcuded more than once
 * See for mor Info: 
 *      http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node90.html
 *      https://stackoverflow.com/a/30877548
*/
#ifndef BASE_H
#define BASE_H

#define EASY 0
#define MEDIUM 1
#define HARD 2

#define USER_NAME_MAX_LENGTH 16

#define STATE_MAIN 0
#define STATE_GAME 1
#define STATE_LEADERBOARD 2

typedef struct sudoku
{
    // First layer = Generator; Second layer = User; Last Array Dimension => [2]
    int field[9][9][2];
    int difficulty;
    long startTime;
    int helpCounter;
} Sudoku;

typedef struct leaderBoardElement
{
    int difficulty;
    long time;
    char user[USER_NAME_MAX_LENGTH];
} LeaderBoardElement;

Sudoku getHelp(Sudoku sudoku);
Sudoku createNew(int difficulty);
LeaderBoardElement *getLeaderBoardElements(int difficulty);
char *fetchGameRules();
// Calls save()
int calculateScore(Sudoku sudoku);
int save(LeaderBoardElement element);

#endif