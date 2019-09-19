//Author Sean Adam Holland
#include <stdio.h>
#include <stdlib.h>
#include "game_function.h"

int main()
{
    int num_of_bombs;
    bool boolBombs = false; // false while user hasent entered a valid number of bombs
    while(boolBombs == false)
    {
        printf("how many bombs 2, 3, 4?\n");
        char charBomb = get_user_char();

         int numBomb = charBomb - 48; // minus 48 brings char 0 to decimal 0
         if(numBomb > 1 &&  numBomb < 5) // numBomb between 2 and 4 inclusive
         {
             num_of_bombs = numBomb;
             boolBombs = true;
         }
         else
            printf("Sorry invalid character input, please try again!\n");
    }


    struct locations* bombs = (struct locations * ) malloc(sizeof(struct locations) * num_of_bombs);

    time_t t;
    srand((unsigned) time(&t));
    int allocateBombs = 0;
    int bRow, bCol;
    while(allocateBombs < num_of_bombs) // generates random co-ordinates for bombs
    {
        bool match = false;
        int col = rand() % 4; // %4 as the array is length 4 (0, 1, 2 ,3)
        int row = rand() % 4;
        for(int i = 0; i < num_of_bombs; i ++)
        {
             if(row == bombs[i].x && col == bombs[i].y)
                match = true; // if the co-ordinates have already been picked the bomb co-ordinate is randomised again

        }
        if(match == false)
        {
            printf("Bomb %d: row %d column %d\n", allocateBombs, row, col);
            bombs[allocateBombs].x = row;
            bombs[allocateBombs].y  = col;
            bombs[allocateBombs].found = false;
            allocateBombs++;
        }


    }

    int bomb_location_info[4][4] = {1,1,1,0,
                                    1,0,2,1,
                                    1,1,2,0,
                                    0,0,1,1};

    int known_location_info[4][4] = {-1,-1,-1,-1,
                                    -1,-1,-1,-1,
                                    -1,-1,-1,-1,
                                    -1,-1,-1,-1};

    int size = sizeof(known_location_info[DIM])/4;


    start_game(known_location_info, size, bomb_location_info, bombs, num_of_bombs);


    free(bombs);
    return 0;
}
