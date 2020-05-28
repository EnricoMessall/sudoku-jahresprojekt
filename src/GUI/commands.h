#define CATEGORY_GENERAL 1
#define CATEGORY_MAIN 2
#define CATEGORY_GAME 3
#define CATEGORY_LEADERBOARD 4

#define COMMAND_MAX_CATEGORIES 2

#define COMMAND_LENGTH_NAME 32
#define COMMAND_LENGTH_DESCRIPTION 256

typedef struct command {
    char name[COMMAND_LENGTH_NAME];
    char description[COMMAND_LENGTH_DESCRIPTION];
    int categories[COMMAND_MAX_CATEGORIES];
    int selection;
} Command;

typedef struct menu {
    Command *commands;
    int commandAmount;
    int state;
} Menu;

// Array of all valid commands, order in array defines print order
Command VALID_COMMANDS[] = {
    // GAME
    {
        "New Game",
        "Starts a new game with the given difficulty (0-2)",
        {CATEGORY_GAME, CATEGORY_MAIN}
    },
    {
        "Game Hint",
        "Shows a hint for the given field",
        {CATEGORY_GAME}
    },
    {
        "Print Rules",
        "Prints the rules of sudoku",
        {CATEGORY_GAME, CATEGORY_MAIN}
    },
    {
        "Quit Game",
        "Quits the current game and goes back to the main menu.",
        {CATEGORY_GAME}
    },
    // MAIN 
    {
        "Leaderboard Menu",
        "Displays the leaderboard",
        {CATEGORY_MAIN}
    },
    // LEADERBOARD
    {
        "Print Leaderboard",
        "Prints the leaderboard after the users entered the difficulty",
        {CATEGORY_LEADERBOARD}
    },
    // GENERAL
    {
        "Exit",
        "Closes the game.",
        {CATEGORY_GENERAL}
    },
};

Command COMMAND_BACK = {
    "Back",
    "Goes back to the previous menu",
    {}
};