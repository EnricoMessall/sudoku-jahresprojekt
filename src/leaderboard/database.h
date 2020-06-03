/**
 * Header Guard, prevents this header file from being inlcuded more than once
 * See for mor Info: 
 *      http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node90.html
 *      https://stackoverflow.com/a/30877548
*/
#ifndef DATABASE_H
#define DATABASE_H

#include "dbHelper.h"
#include "base.h"

#define DATABASE "Sudoku.db"
#define TABLENAME_USERS "users"
#define TABLENAME_SCORES "userScore"

#define TBL_USERS_COLUMN_PK_ID "ID"
#define TBL_USERS_COLUMN_Nickname "Nickname"

#define TBL_SCORE_COLUMN_PK_ID "ID"
#define TBL_SCORE_COLUMN_FK_UserID "UserID"
#define TBL_SCORE_COLUMN_Time "Time"
#define TBL_SCORE_COLUMN_Difficulty "Difficulty"
#define TBL_SCORE_COLUMN_Date "Date"

// Creates a SQLite3 Sudoku.db table based on the passed sql statement,
// as long as the Database Connection State did not encounter any Errors before.
void createTableIfNotExists(SQLite3Context db, const char *sql);
// Inserts a Row into a Sudoku.db table, as long as the Database Connection State did not encounter any Errors before.
void insertIntoTable(SQLite3Context db, const char *sql);
// Selects all the Records from the SQLite3 Sudoku.db based on the provided difficulty and as the Database Connection State did not encounter any Errors before.
// Returns either a ordered Array of LeaderBoardElement Items or a NULL on Error to the Database Connection State.
LeaderBoardElement *selectRecords(SQLite3Context db, int difficulty);
// SQLite3 Callback Function.
// Called multiple times in the caller Function, for each resultung row in the SELECT Statement.
int callback(void *NotUsed, int nColumns, char **strArrRows, char **strArrColNames);
// Adds an LeaderBoardElement to the global static LeaderBoardElement Array named 'elements'.
// This Function is also only scoped to this File and keeps its changed State through each invocation.
static void add(LeaderBoardElement element);

#endif