/** @file   gameLogic.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The game logic module which determines the winner of the
            round of 'Rock, Paper,  Scissors'.
*/

#include "system.h"
#include "gameLogic.h"

/**
 * This function determines the winning of the round that has just
 * concluded.
 * INPUT: playersMove, the player's chosen move (either 'R', 'P' or 'S')
 *                     as a char.
 *        opponentsMove, the opponent's chosen move (either 'R', 'P' or
 *                       'S') as a char.
 * OUTPUT: decision, the outcome of the round as a char (either 'D' for
 *                   draw, 'W' for win or 'L' for lose).
 */
char gameLogic_determineWinner(char playersMove, char opponentsMove)
{
    char decision = ' ';

    if ((opponentsMove == 'R' && playersMove == 'R') ||
        (opponentsMove == 'P' && playersMove == 'P') ||
        (opponentsMove == 'S' && playersMove == 'S')) {

        /* The player and their opponent draw*/
        decision = 'D';

    } else if ((opponentsMove == 'R' && playersMove == 'P') ||
               (opponentsMove == 'P' && playersMove == 'S') ||
               (opponentsMove == 'S' && playersMove == 'R')) {

        /* The player wins and the opponent looses*/
        decision = 'W';

    } else if ((opponentsMove == 'R' && playersMove == 'S') ||
               (opponentsMove == 'P' && playersMove == 'R') ||
               (opponentsMove == 'S' && playersMove == 'P'))  {

        /* The opponent wins and the player looses*/
        decision = 'L';
    }
    return decision;
}
