#include <string.h>

#include "dbHelper.h"
#include "dbHelper.c"

#include "leaderboard.h"

// Global Array of LeaderBoardElement Items, scoped to this file only
static LeaderBoardElement elements[MAX_LEADERBOARD_ELEMENTS];

// Creates a SQLite3 Sudoku.db table based on the passed sql statement,
// as long as the Database Connection State did not encounter any Errors before.
void createTableIfNotExists(SQLite3Context db, const char *sql) {
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, sql, NULL, NULL, &db.err_msg);
}

// Inserts a Row into a Sudoku.db table, as long as the Database Connection State did not encounter any Errors before.
void insertIntoTable(SQLite3Context db, const char *sql) {
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, sql, NULL, NULL, &db.err_msg);
}

// Selects all the Records from the SQLite3 Sudoku.db based on the provided difficulty and as the Database Connection State did not encounter any Errors before.
// Returns either a ordered Array of LeaderBoardElement Items or a NULL on Error to the Database Connection State.
LeaderBoardElement *selectRecords(SQLite3Context db, int difficulty) {
    // Reset array
    memset(elements, 0, MAX_LEADERBOARD_ELEMENTS * (sizeof(elements[0])));

    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, SQL_STATEMENT_SELECT_USER_RECORDS_WITH_DIFFICULTY(difficulty), callback, 0, &db.err_msg);
    else
        return NULL;
    return elements;
}

// SQLite3 Callback Function.
// Called multiple times in the caller Function, for each resultung row in the SELECT Statement.
int callback(void *NotUsed, int nColumns, char **strArrRows,
             char **strArrColNames) {
    LeaderBoardElement element;
    strcpy(element.user, strArrRows[0] ? strArrRows[0] : "NULL");
    element.time = strArrRows[1] ? strtol(strArrRows[1], NULL, 10) : -1;
    element.difficulty = strArrRows[2] ? atoi(strArrRows[2]) : -1;

    // Add to the static LeaderBoardElement array, if is a valid element
    if (strcmp(element.user, "NULL") != 0 && element.time != -1 && element.difficulty != -1)
        add(element);

    return 0;
}

// Adds an LeaderBoardElement to the global static LeaderBoardElement Array named 'elements'.
// This Function is also only scoped to this File and keeps its changed State through each invocation.
static void add(LeaderBoardElement element) {
    static int i = 0;
    // Reset i if Array is Empty
    if (i > 0 && strcmp(elements[0].user, "") == 0 && elements[0].time == 0)
        i = 0;
    if(i < MAX_LEADERBOARD_ELEMENTS)
        elements[i] = element;
    i++;
}