#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "dbHelper.h"
#include "sqlite3.h"
#include "database.h"
#include "statements.h"

// Connects to the SQLite3 DB.
// Returns a SQLite3Context struct that holds the Connection informations.
SQLite3Context connectToDB(void)
{
    SQLite3Context db;
    db.err_msg = NULL;

    db.connection_state = sqlite3_open(DATABASE, &db.connection);

    if (db.connection_state != SQLITE_OK)
        printf("\nError[%i]; Could not open Database: %s\n", db.connection_state, sqlite3_errmsg(db.connection));

    return db;
}

// Disconnects from the current SQLite3 session.
// Returns the last DB connection state such as SQLITE_OK or SQLITE_ERROR.
int disconnectFromDB(SQLite3Context db)
{
    free(db.err_msg);
    sqlite3_close(db.connection);

    return db.connection_state;
}

// In order for Foreign Key Constraints to work properly SQLite3
// requires this option to be activated each new Connection via a simple Statement.
// This function activates the SQLite3 FK Constraint feature for this Session.
void setFK_ON(SQLite3Context db)
{
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, SQL_STATEMENT_PRAGMA_TURN_FOREIGN_KEYS_ON, NULL, NULL, &db.err_msg);
}

// Checks the Database Execution State and on Error, prints the Errormessage & Errornumber to the console.
void dbCheckExecutionState(SQLite3Context db)
{
    if (db.connection_state != SQLITE_OK)
        printf("\nSQL Error[%i]: %s\n", db.connection_state, db.err_msg);
}