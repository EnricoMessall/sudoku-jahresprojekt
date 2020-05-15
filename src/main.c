#include <stdio.h>
#include <string.h>
#include <time.h>

#include "database.c"

//TODO: When finished, speak with Nicolas about pushing project to github repo
int main(void)
{
    int code = 0;

    // DUMMY data
    LeaderBoardElement leaderBoardElement;
    strcpy(leaderBoardElement.user, "test");
    leaderBoardElement.difficulty = EASY;
    leaderBoardElement.time = (long)time(NULL);

    if (save(leaderBoardElement) == LEADERBOARD_OK)
        printf("Smooth execution!\n");
    else
        code = ON_SAVE_ERROR;

    return code;
}