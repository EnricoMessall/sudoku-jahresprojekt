/**
 * Header Guard, prevents this header file from being inlcuded more than once
 * See for mor Info: 
 *      http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node90.html
 *      https://stackoverflow.com/a/30877548
*/
#ifndef DATABASE_HELPER_H
#define DATABASE_HELPER_H

#include "sqlite3.h"

typedef struct db
{
    sqlite3 *connection;
    char *err_msg;
    int connection_state;
} SQLite3Context;

// Connects to the SQLite3 DB.
// Returns a SQLite3Context struct that holds the Connection informations.
SQLite3Context connectToDB(void);
// Disconnects from the current SQLite3 session.
// Returns the last DB connection state such as SQLITE_OK or SQLITE_ERROR.
int disconnectFromDB(SQLite3Context db);
// In order for Foreign Key Constraints to work properly SQLite3
// requires this option to be activated each new Connection via a simple Statement.
// This function activates the SQLite3 FK Constraint feature for this Session.
void setFK_ON(SQLite3Context db);
// Checks the Database Execution State and on Error, prints the Errormessage & Errornumber to the console.
void dbCheckExecutionState(SQLite3Context db);

#endif