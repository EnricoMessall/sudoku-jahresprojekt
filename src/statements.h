/**
 * Header Guard, prevents this header file from being inlcuded more than once
 * See for mor Info: 
 *      http://faculty.cs.niu.edu/~mcmahon/CS241/c241man/node90.html
 *      https://stackoverflow.com/a/30877548
*/
#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "base.h"
#include "database.h"
#include "sqlite3.h"

// SQL CREATE
#define SQL_STATEMENT_CREATE_TBL_USERS sqlite3_mprintf("CREATE TABLE IF NOT EXISTS %s(ID INTEGER PRIMARY KEY AUTOINCREMENT, Nickname VARCHAR(16) NOT NULL, UNIQUE (Nickname));", TABLENAME_USERS)
#define SQL_STATEMENT_CREATE_TBL_SCORES sqlite3_mprintf("CREATE TABLE IF NOT EXISTS %s(ID INTEGER PRIMARY KEY AUTOINCREMENT, UserID INTEGER NOT NULL, Time INTEGER NOT NULL, Difficulty INTEGER NOT NULL, UNIQUE (UserID, Difficulty) ON CONFLICT REPLACE CONSTRAINT users_userScore FOREIGN KEY(UserID) REFERENCES users(ID) ON UPDATE CASCADE ON DELETE CASCADE);", TABLENAME_SCORES)

// SQL INSERT
#define SQL_STATEMENT_INSERT_INTO_TBL_USERS "INSERT INTO %s (%s, %s) VALUES (%s, '%s')"
#define SQL_STATEMENT_INSERT_INTO_TBL_SCORES "INSERT INTO %s (%s, %s, %s, %s) VALUES (%s, (SELECT %s FROM %s WHERE %s = '%s'), %d, %d)"

// SQLite3 PRAGMA
#define SQL_STATEMENT_PRAGMA_TURN_FOREIGN_KEYS_ON "PRAGMA foreign_keys = ON"

// MACRO (see https://www.tutorialspoint.com/cprogramming/c_preprocessors.htm for more info)
#define BUILDSQL_USERS(sql, element) (sqlite3_mprintf(sql, TABLENAME_USERS, TBL_USERS_COLUMN_PK_ID, TBL_USERS_COLUMN_Nickname, "NULL", element.user))
#define BUILDSQL_SCORES(sql, element) (sqlite3_mprintf(sql, TABLENAME_SCORES, TBL_SCORE_COLUMN_PK_ID, TBL_SCORE_COLUMN_FK_UserID, TBL_SCORE_COLUMN_Time, TBL_SCORE_COLUMN_Difficulty, "NULL", TBL_USERS_COLUMN_PK_ID, TABLENAME_USERS, TBL_USERS_COLUMN_Nickname, element.user, element.time, element.difficulty))

#endif