#include <string.h>

#include "dbHelper.h"
#include "dbHelper.c"

#include "leaderboard.h"

static LeaderBoardElement elements[MAX_LEADERBOARD_ELEMENTS];

// Creates a SQLite3 Sudoku.db table based on the passed sql statement,
// as long as the Database Connection State did not encounter any Errors before.
void createTableIfNotExists(SQLite3Context db, const char *sql)
{
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, sql, NULL, NULL, &db.err_msg);
}

// Inserts a Row into a Sudoku.db table, as long as the Database Connection State did not encounter any Errors before.
void insertIntoTable(SQLite3Context db, const char *sql)
{
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, sql, NULL, NULL, &db.err_msg);
}

LeaderBoardElement *selectRecords(SQLite3Context db, int difficulty)
{
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, SQL_STATEMENT_SELECT_USER_RECORDS_WITH_DIFFICULTY(difficulty), callback, 0, &db.err_msg);

    return elements;
}

int callback(void *NotUsed, int noColumns, char **strArrRows,
             char **strArrColNames)
{
    LeaderBoardElement element;
    strcpy(element.user, strArrRows[0] ? strArrRows[0] : "NULL");
    element.time = strArrRows[1] ? strtol(strArrRows[1], NULL, 10) : -1;
    element.difficulty = strArrRows[2] ? atoi(strArrRows[2]) : -1;

    // Add to the static LeaderBoardElement array
    if (strcmp(element.user, "NULL") != 0 && element.time != -1 && element.difficulty != -1)
        add(element);

    return 0;
}

static void add(LeaderBoardElement element)
{
    static int i = 0;
    elements[i] = element;
    i++;
}