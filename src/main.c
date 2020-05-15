#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"
#include "base.h"

#define DATABASE "Sudoku.db"
#define TABLE_USERS "users"
#define TABLE_SCORE "userScore"

#define TBL_USERS_COLUMN_PK_ID "ID"
#define TBL_USERS_COLUMN_Nickname "Nickname"

#define TBL_SCORE_COLUMN_PK_ID "ID"
#define TBL_SCORE_COLUMN_FK_UserID "UserID"
#define TBL_SCORE_COLUMN_Time "Time"
#define TBL_SCORE_COLUMN_Difficulty "Difficulty"

void createTableIfNotExists(sqlite3 *db, char *statement, char *table, char *err_msg);
int insertIntoTable(sqlite3 *db, char *user, char *table, char *err_msg);
void dbExecutionResult(int code, sqlite3 *db, char *err_msg);

//TODO: change DB structure, no score, instead long time (unix-timestamp e.g. 123414913L )
//TODO: When finished, speak with Nicolas about pushing project to github repo
int main(void)
{
    LeaderBoardElement leaderBoardElement;
    strcpy(leaderBoardElement.user, "Bob");
    if (save(leaderBoardElement) == 0)
        printf("Smooth execution!\n");
    return 0;
}

int save(LeaderBoardElement leaderBoardElement)
{
    sqlite3 *db;
    char *err_msg = NULL;

    int result = sqlite3_open(DATABASE, &db);

    if (result != SQLITE_OK)
    {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        exit(-1);
    }

    char *sqlCreateTableUsers = "CREATE TABLE IF NOT EXISTS %s("
                                "   ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "   Nickname VARCHAR(16) NOT NULL"
                                ");";

    char *sqlCreateTableScores = "CREATE TABLE IF NOT EXISTS %s("
                                 " ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 " UserID INTEGER NOT NULL,"
                                 " Score INTEGER NOT NULL,"
                                 " Difficulty INTEGER NOT NULL,"
                                 " UNIQUE (UserID, Difficulty) ON CONFLICT REPLACE CONSTRAINT users_userScore FOREIGN KEY(UserID) REFERENCES users(ID) ON UPDATE CASCADE ON DELETE CASCADE"
                                 ");";

    // Create Tables If not Exist
    createTableIfNotExists(db, sqlCreateTableUsers, TABLE_USERS, err_msg);
    createTableIfNotExists(db, sqlCreateTableScores, TABLE_SCORE, err_msg);

    // Save user
    insertIntoTable(db, leaderBoardElement.user, TABLE_USERS, err_msg);
    insertIntoTable(db, leaderBoardElement.user, TABLE_SCORE, err_msg);

    sqlite3_close(db);

    return 0;
}

void createTableIfNotExists(sqlite3 *db, char *statement, char *table, char *err_msg)
{
    int result = SQLITE_ERROR;

    // Create table Statement
    char *sql = sqlite3_mprintf(
        statement,
        table);

    result = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
    dbExecutionResult(result, db, err_msg);
}

int insertIntoTable(sqlite3 *db, char *userName, char *table, char *err_msg)
{
    char *statement;
    if (strcmp(table, TABLE_USERS) == 0)
    {
        strcpy(statement, sqlite3_mprintf("INSERT INTO %s (%s, %s) VALUES (%s, '%s');", TABLE_USERS, TBL_USERS_COLUMN_PK_ID, TBL_USERS_COLUMN_Nickname, "NULL", userName));
    }
    else if (strcmp(table, TABLE_SCORE) == 0)
    {
        strcpy(statement, sqlite3_mprintf("INSERT INTO %s (%s, %s, %s, %s) VALUES (%s, (SELECT %s FROM %s WHERE %s = '%s'), %d, %d);", TABLE_SCORE,
                                          TBL_SCORE_COLUMN_PK_ID, TBL_SCORE_COLUMN_FK_UserID, TBL_SCORE_COLUMN_Time, TBL_SCORE_COLUMN_Difficulty,
                                          "NULL", TBL_USERS_COLUMN_PK_ID, TABLE_USERS, TBL_USERS_COLUMN_Nickname, userName, 99, 0));
    }
    else
    {
        printf("\nCould save user.\n");
        return 1;
    }

    int result = sqlite3_exec(db, statement, NULL, NULL, &err_msg);
    dbExecutionResult(result, db, err_msg);
    return 0;
}

// Exits Program if Execution Result is not OK
void dbExecutionResult(int code, sqlite3 *db, char *err_msg)
{
    if (code != SQLITE_OK)
    {
        printf("SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        exit(-1);
    }
}