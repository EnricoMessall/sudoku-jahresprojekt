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

SQLite3Context connectToDB(void);
int disconnectFromDB(SQLite3Context);
void setFK_ON(SQLite3Context);
void dbCheckExecutionState(SQLite3Context);

#endif