//TODO: Speak about changes to base.h
/**
 * Header Guard, prevents this header file from being inlcuded more than once
 * See for mor Info: 
 *      http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node90.html
 *      https://stackoverflow.com/a/30877548
*/
#ifndef BASE_H
#define BASE_H

// Header Contents
#define EASY 0
#define MEDIUM 1
#define HARD 2

#define USERNAME_MAX_LENGTH 16

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
    int rank;
    char user[USERNAME_MAX_LENGTH];
    int score;
} LeaderBoardElement;

// Help Module Interface
Sudoku getHelp(Sudoku sudoku);

// Generator Module Interface
Sudoku createNew();

// Gamerules Module Interface
char *fetchGameRules();

// Leaderboard Modul Interface
LeaderBoardElement *getLeaderBoardElements(int difficulty);
int save(Sudoku sudoku, char user[USERNAME_MAX_LENGTH]);

#endif