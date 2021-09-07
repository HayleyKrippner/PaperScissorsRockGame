/** @file   stateFive.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The module for the fifth state of the game. It is the end of
            the game state.
*/

#include "system.h"
#include "mainGameDisplay.h"
#include "stateFive.h"

/**
 * This functions enters the state for the end game.
 * If the player has won, then the winning display is displayed.
 * If th player hast lost, then the loosing display is displayed.
 * INPUT: playerGamesWon, the pointer to the number of games the player
 *        has won as an int.
 *        opponentGamesWon, the pointer to the number of games the
 *        opponent has won as an int.
 * OUTPUT: N/A
 */
void stateFive_start(int* playerGamesWon, int* opponentGamesWon)
{
    int playerWon = 0;

    if (*playerGamesWon > *opponentGamesWon) {
        playerWon = 1;
        mainGameDisplay_displayDecision(playerWon);
    } else if (*playerGamesWon < *opponentGamesWon) {
        mainGameDisplay_displayDecision(playerWon);
    }
}
