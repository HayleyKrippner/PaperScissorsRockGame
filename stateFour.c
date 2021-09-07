/** @file   stateFour.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The module for the fourth state of the game. It checks if
            the game should end.
*/

#include "system.h"
#include "stateFour.h"

/**
 * This functions checks whether one of the players has won 3 games.
 * It returns 0 if this is false and 1 if the game is true.
 * INPUT: numOfRounds, the number of total rounds as an int.
 *        playerGamesWon, the pointer to the number of games the player
 *        has won as an int.
 *        opponentGamesWon, the pointer to the number of games the
 *        opponent has won as an int.
 * OUTPUT: N/A
 */
int stateFour_start(int numOfRounds, int* playerGamesWon, int* opponentGamesWon)
{
    int hasEnded = 0;
    if (*playerGamesWon == numOfRounds || *opponentGamesWon == numOfRounds) {
        hasEnded = 1;
    }
    return hasEnded;
}
