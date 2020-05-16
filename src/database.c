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