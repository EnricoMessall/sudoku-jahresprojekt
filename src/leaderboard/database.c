#include <string.h>

#include "dbHelper.h"
#include "dbHelper.c"

#include "leaderboard.h"

// Global Array of LeaderBoardElement Items, scoped to this file only
static LeaderBoardElement elements[MAX_LEADERBOARD_ELEMENTS];

void createTableIfNotExists(SQLite3Context db, const char *sql) {
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, sql, NULL, NULL, &db.err_msg);
}

void insertIntoTable(SQLite3Context db, const char *sql) {
    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, sql, NULL, NULL, &db.err_msg);
}

LeaderBoardElement *selectRecords(SQLite3Context db, int difficulty) {
    // Reset array
    memset(elements, 0, MAX_LEADERBOARD_ELEMENTS * (sizeof(elements[0])));

    if (db.connection_state == SQLITE_OK)
        db.connection_state = sqlite3_exec(db.connection, SQL_STATEMENT_SELECT_USER_RECORDS_WITH_DIFFICULTY(difficulty), callback, 0, &db.err_msg);
    else
        return NULL;
    return elements;
}

int callback(void *NotUsed, int nColumns, char **strArrRows,
             char **strArrColNames) {
    LeaderBoardElement element;
    strcpy(element.user, strArrRows[0] ? strArrRows[0] : "NULL");
    element.time = strArrRows[1] ? strtol(strArrRows[1], NULL, 10) : -1;
    element.difficulty = strArrRows[2] ? atoi(strArrRows[2]) : -1;

    // Add to the static LeaderBoardElement array, if is a valid element
    if (strcmp(element.user, "NULL") != 0 && element.time != -1 && element.difficulty != -1)
        add(element);

    return 0;
}

static void add(LeaderBoardElement element) {
    static int i = 0;
    // Reset i if Array is Empty
    if (i > 0 && strcmp(elements[0].user, "") == 0 && elements[0].time == 0)
        i = 0;
    if(i < MAX_LEADERBOARD_ELEMENTS)
        elements[i] = element;
    i++;
}