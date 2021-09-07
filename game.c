/** @file   game.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The game module which is the entry point for starting the
            game of 'Rock, Paper,  Scissors'.
*/

#include "system.h"
#include "mainGame.h"

/**
 * The main method for the game.
 * INPUT: N/A
 * OUTPUT: 0 as an int, when the game application is terminated.
 */
int main (void)
{
    system_init ();

    while (1) {
        mainGame_start();
    }

    return 0;
}
