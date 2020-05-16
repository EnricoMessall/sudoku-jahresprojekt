#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "sqlite3.h"
#include "database.h"
#include "leaderboard.h"
#include "statements.h"

SQLite3Context connectToDB()
{
    SQLite3Context db;
    db.err_msg = NULL;

    db.connection_state = sqlite3_open(DATABASE, &db.connection);

    if (db.connection_state != SQLITE_OK)
        printf("\nError[%i]; Could not open Database: %s\n", db.connection_state, sqlite3_errmsg(db.connection));

    return db;
}

int disconnectFromDB(SQLite3Context db)
{
    free(db.err_msg);
    sqlite3_close(db.connection);

    return db.connection_state;
}

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

// In order for Foreign Key Constraints to work properly SQLite3
// requires this option to be activated each new Connection via a simple Statement.
// This function activates the SQLite3 FK Constraint feature for this Session.
void setFK_ON(SQLite3Context db)
{
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, SQL_STATEMENT_PRAGMA_TURN_FOREIGN_KEYS_ON, NULL, NULL, &db.err_msg);
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

// Checks the Database Execution State and on Error, prints the Errormessage & Errornumber to the console.
void dbCheckExecutionState(SQLite3Context db)
{
    if (db.connection_state != SQLITE_OK)
        printf("\nSQL Error[%i]: %s\n", db.connection_state, db.err_msg);
}