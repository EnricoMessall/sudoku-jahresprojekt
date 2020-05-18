#include <stdio.h>
#include <string.h>
#include <time.h>

#include "leaderboard.h"
#include "leaderboard.c"

//TODO: When finished, speak with Nicolas about pushing project to github repo
//TODO: Organize #includes
//TODO: Put every files in src/ but main.c and base.h into src/leaderboard/
int main(void)
{
    srand(time(NULL));

    int code = LEADERBOARD_OK;

    // DUMMY data
    LeaderBoardElement easy_test;
    strcpy(easy_test.user, "test");
    easy_test.difficulty = EASY;
    easy_test.time = (long)time(NULL) + rand();

    LeaderBoardElement easy_bob;
    strcpy(easy_bob.user, "bob");
    easy_bob.difficulty = EASY;
    easy_bob.time = (long)time(NULL) + rand();

    LeaderBoardElement easy_haxor;
    strcpy(easy_haxor.user, "haxor");
    easy_haxor.difficulty = EASY;
    easy_haxor.time = (long)time(NULL) + rand();

    LeaderBoardElement medium_test;
    strcpy(medium_test.user, "test");
    medium_test.difficulty = MEDIUM;
    medium_test.time = (long)time(NULL) + rand();

    LeaderBoardElement medium_bob;
    strcpy(medium_bob.user, "bob");
    medium_bob.difficulty = MEDIUM;
    medium_bob.time = (long)time(NULL) + rand();

    LeaderBoardElement medium_haxor;
    strcpy(medium_haxor.user, "haxor");
    medium_haxor.difficulty = MEDIUM;
    medium_haxor.time = (long)time(NULL) + rand();

    LeaderBoardElement hard_test;
    strcpy(hard_test.user, "test");
    hard_test.difficulty = HARD;
    hard_test.time = (long)time(NULL) + rand();

    LeaderBoardElement hard_bob;
    strcpy(hard_bob.user, "bob");
    hard_bob.difficulty = HARD;
    hard_bob.time = (long)time(NULL) + rand();

    LeaderBoardElement hard_haxor;
    strcpy(hard_haxor.user, "haxor");
    hard_haxor.difficulty = HARD;
    hard_haxor.time = (long)time(NULL) + rand();

    LeaderBoardElement elements[9] = {easy_test, easy_bob, easy_haxor, medium_test, medium_bob, medium_haxor, hard_test, hard_bob, hard_haxor};

    for (int i = 0; i < 9; i++)
    {
        if (save(elements[i]) == LEADERBOARD_OK)
            printf("User %s saved successfully.\n", elements[i].user);
        else
        {
            printf("Failed saving User %s in the database.\n", elements[i].user);
            code = ON_SAVE_ERROR;
        }
    }

    LeaderBoardElement *list = getLeaderBoardElements(HARD);
    if (list != NULL)
    {
        for (int i = 0; i < MAX_LEADERBOARD_ELEMENTS; i++)
        {
            if (list[i].user[0] != '\0')
            {
                printf("\n");
                printf("Nickname: %s\n", list[i].user);
                printf("Time: %ld\n", list[i].time);
                printf("Difficulty: %i\n", list[i].difficulty);
            }
        }
    }

    return code;
}