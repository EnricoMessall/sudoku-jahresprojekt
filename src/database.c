#include "dbHelper.h"
#include "dbHelper.c"

int deleteUser(const char *userName)
{
    SQLite3Context db = connectToDB();

    setFK_ON(db);

    if (db.connection_state == SQLITE_OK)
    {
        char *sql = SQL_STATEMENT_DELETE_FROM_TBL_USERS(userName);
        db.connection_state = sqlite3_exec(db.connection, sql, NULL, NULL, &db.err_msg);
        sql = NULL;
    }
    else
        return SQLITE_ERROR;

    dbCheckExecutionState(db);

    return disconnectFromDB(db);
}

// Saves the User's Scorestate in the Database.
// NOTE: On first Error encountered while saving, any subsequent operation will be skipped
// and a Errormessage will be displayed to the console.
int save(LeaderBoardElement leaderBoardElement)
{
    SQLite3Context db = connectToDB();

    // Check if connection was successful
    if (db.connection_state != SQLITE_OK)
        return SQLITE_ERROR;

    // Create Tables If not Exist. Both tables are required to save a user completely.
    createTableIfNotExists(db, SQL_STATEMENT_CREATE_TBL_USERS);
    createTableIfNotExists(db, SQL_STATEMENT_CREATE_TBL_SCORES);

    // Save User using Macro BUILDSQL_*() to build the SQL Statement
    insertIntoTable(db, BUILDSQL_USERS(SQL_STATEMENT_INSERT_INTO_TBL_USERS, leaderBoardElement));
    insertIntoTable(db, BUILDSQL_SCORES(SQL_STATEMENT_INSERT_INTO_TBL_SCORES, leaderBoardElement));

    dbCheckExecutionState(db);

    return disconnectFromDB(db);
}

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