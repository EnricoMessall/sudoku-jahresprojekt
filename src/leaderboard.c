#include "database.c"

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