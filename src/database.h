/**
 * Header Guard, prevents this header file from being inlcuded more than once
 * See for mor Info: 
 *      http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node90.html
 *      https://stackoverflow.com/a/30877548
*/
#ifndef DATABASE_H
#define DATABASE_H

#include "base.h"
#include "sqlite3.h"

#define DATABASE "Sudoku.db"
#define TABLENAME_USERS "users"
#define TABLENAME_SCORES "userScore"

#define TBL_USERS_COLUMN_PK_ID "ID"
#define TBL_USERS_COLUMN_Nickname "Nickname"

#define TBL_SCORE_COLUMN_PK_ID "ID"
#define TBL_SCORE_COLUMN_FK_UserID "UserID"
#define TBL_SCORE_COLUMN_Time "Time"
#define TBL_SCORE_COLUMN_Difficulty "Difficulty"

typedef struct db
{
    sqlite3 *connection;
    char *err_msg;
    int connection_state;
} SQLite3Context;

SQLite3Context connectToDB(void);
int disconnectFromDB(SQLite3Context);
void setFK_ON(SQLite3Context);
int deleteUser(const char *);
void createTableIfNotExists(SQLite3Context, const char *);
void insertIntoTable(SQLite3Context, const char *);
void dbCheckExecutionState(SQLite3Context);

#endif