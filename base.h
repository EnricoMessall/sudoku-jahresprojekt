#define EASY 0
#define MEDIUM 1
#define HARD 2

#define USER_LENGTH 16

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
    char user[USER_LENGTH];
} LeaderBoardElement;

Sudoku getHelp(Sudoku sudoku);
Sudoku createNew();
LeaderBoardElement *getLeaderBoardElements(int difficulty);
char *fetchGameRules();
// Calls save()
int calculateScore(Sudoku sudoku, char user[USER_LENGTH]);
int save(LeaderBoardElement element);
