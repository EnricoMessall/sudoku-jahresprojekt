#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "dbHelper.h"
#include "sqlite3.h"
#include "database.h"
#include "statements.h"

SQLite3Context connectToDB(void) {
    SQLite3Context db;
    db.err_msg = NULL;

    db.connection_state = sqlite3_open(DATABASE, &db.connection);

    if (db.connection_state != SQLITE_OK)
        printf("\nError[%i]; Could not open Database: %s\n", db.connection_state, sqlite3_errmsg(db.connection));

    return db;
}

int disconnectFromDB(SQLite3Context db) {
    free(db.err_msg);
    sqlite3_close(db.connection);

    return db.connection_state;
}

void setFK_ON(SQLite3Context db) {
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, SQL_STATEMENT_PRAGMA_TURN_FOREIGN_KEYS_ON, NULL, NULL, &db.err_msg);
}

void dbCheckExecutionState(SQLite3Context db) {
    if (db.connection_state != SQLITE_OK)
        printf("\nSQL Error[%i]: %s\n", db.connection_state, db.err_msg);
}