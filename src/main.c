#include <stdio.h>
#include <string.h>
#include <time.h>

#include "leaderboard.h"

#include "database.c"

//TODO: When finished, speak with Nicolas about pushing project to github repo
int main(void)
{
    int code = LEADERBOARD_OK;

    // DUMMY data
    LeaderBoardElement test;
    strcpy(test.user, "test");
    test.difficulty = EASY;
    test.time = (long)time(NULL);

    LeaderBoardElement bob;
    strcpy(bob.user, "bob");
    bob.difficulty = EASY;
    bob.time = (long)time(NULL);

    LeaderBoardElement haxor;
    strcpy(haxor.user, "haxor");
    haxor.difficulty = EASY;
    haxor.time = (long)time(NULL);

    LeaderBoardElement elements[3] = {test,
                                      bob,
                                      haxor};

    // for (int i = 0; i < 3; i++)
    // {
    //     if (save(elements[i]) == LEADERBOARD_OK)
    //         printf("User %s saved successfully.\n", elements[i].user);
    //     else
    //     {
    //         printf("Failed saving User %s in the database.\n", elements[i].user);
    //         code = ON_SAVE_ERROR;
    //     }
    // }

    // deleteUser(elements[0].user);
    // deleteUser(elements[1].user);
    // deleteUser(elements[2].user);

    return code;
}