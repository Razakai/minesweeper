//Author Sean Adam Holland
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "game_function.h"




void display(int grid[][DIM], int length)
{
     int arrSize = length;
     char star = 42; // 42 is char for *
     char charBomb = 66;
     printf("\n   A B C D");
     for(int i = 0; i < arrSize; i ++) // prints row A, B, C, D
        {
            if(i == 0)
            {
                printf("\nA: ");
            }
            else if(i == 1)
            {
                printf("\nB: ");
            }
            else if(i == 2)
            {
                printf("\nC: ");
            }
            else if(i == 3)
            {
                printf("\nD: ");
            }






            for(int row = 0; row < arrSize; row++)
            {
                if(grid[i][row] == -1)
                    printf("%c ", star); // prints *


                else if(grid[i][row] == BOMB)
                    printf("%c ", charBomb); // prints B


                else
                    printf("%d ", grid[i][row]); // prints already guessed number


            }






        }
}

update_known_info(int row, int col, int bomb_info[][DIM], int known[][DIM], struct locations bombs[], int numBombs)
{



    if((row < DIM && col < DIM) && (row >=0 && col >= 0))
    {
        bool bombLocated = false;
        for(int i = 0; i < numBombs; i++) // loops through bombs to see if co-ordinates hold a bomb
        {
            if(bombs[i].x == row && bombs[i].y == col)
            {
                known[row][col] = BOMB;
                bombLocated = true;
                break;
            }
        }
        if(bombLocated == false)
            known[row][col] = bomb_info[row][col]; // copies bomb_info to known
    }





}

void check_found(int row, int col, struct locations bombs[], int numBombs) // checks if co-ordinates have hit a bomb
{
    for(int i = 0; i < numBombs; i++)
    {
        if(row == bombs[i].x && col == bombs[i].y)
            bombs[i].found = true;

    }


}

char get_user_char() // get user input
{
    char input = getchar();
    getchar();
    return input;

}


void start_game(int known_location[][DIM], int size, int bomb_location[][DIM], struct locations bombs[], int numBombs)
{
     int hints = 5;

    //clues
    char clue;
    bool clueBool = false;
    while(clueBool == false)
    {
        printf("Do you want 2 clues? y/n\n");
         char temp = get_user_char();
         if(temp == 121 || temp == 89 || temp == 110 || temp == 78)
            {
                 clue = temp;
                 clueBool = true;
            }
        else
            printf("Sorry only the letters y and n are accepted please try again!\n");


    }


    if(clue == 121 || clue == 89)
    {
        hints = 3;

    // generates random co-ordinates for the clues
        time_t t;

    //Intializes random number generator
        srand((unsigned) time(&t));


        int previousRow;
        int previousColumn;
        int i = 0;
        while(i < 2){
            int row = rand() % 4;

            int col = rand() % 4;
            bool match = false; // if match == true, that co-ordinate has aleady been picked
             for(int i = 0; i < numBombs; i ++)
                {
                    if(row == bombs[i].x && col == bombs[i].y)
                        match = true;
                }

            if(match == false)
                if(row != previousRow && col != previousColumn)
                    {
                        update_known_info(row, col, bomb_location, known_location, bombs, numBombs);
                        previousRow = row;
                        previousColumn = col;
                        i++;
                    }




        }
    }

    enum game_status  {STILL_ALIVE, GAME_OVER};
    enum game_status status = STILL_ALIVE;


    while(status == 0) // phase 1
    {
        display(known_location, size);
        printf("\nrow:\n");
        int row = get_user_char() - 97;
        printf("\ncolumn:\n");
        int col = get_user_char() - 97;
        if(row < 0 || row > 3 || col < 0 || col > 3)
            {
                printf("Sorry you entered an invalid character for row and/or column, please enter only lower case\n");
                continue;
            }
        check_found(row, col, bombs, numBombs);
        for(int i = 0; i < numBombs; i++) // checks if bomb is hit
        {
            if(bombs[i].found == true)
                status = 1; // status 1 bomb hit
        }


        if(status == 0)
        {
             update_known_info(row, col, bomb_location, known_location, bombs, numBombs);
            hints--;
            printf("tries left %d\n", hints);
        }



        if(status == 1)
        {
            printf("\nBANG YOU HIT A BOMB\n     GAME OVER");
        }
        if(hints == 0) // if hints == 0 you ran out of hints and begin phase 2
        {
            printf("\nyou used up all your tries\n   phase two commences");
            break;
        }
    }
    int number_found = 0;

    if(status == 0) // phase 2
    {
        for(int i = 1; i <= numBombs; i++)
        {
            display(known_location, size);
            printf("\nbomb %d location details:\nrow:\n", i);
            int row = get_user_char() - 97;
            printf("\nbomb %d location details:\ncolumn:\n", i);
            int col = get_user_char() - 97;


            for(int i = 0; i < numBombs; i++)
            {
                if(bombs[i].x == row && bombs[i].y == col)
                    if(bombs[i].found == true) // if == true, bomb has already been found
                    {
                         printf("Sorry that bomb has already been found");

                    }
                    else // bomb hasent been found yet
                    {
                         check_found(row, col, bombs, numBombs);
                         number_found ++;
                         update_known_info(row, col, bomb_location, known_location, bombs, numBombs);
                    }

            }

        }

    }
        if(number_found != numBombs)

            printf("\nyou didnt locate all the bombs\n       GAME OVER");

        else

            printf("\nCongradulations, you've located all the bombs");

}

