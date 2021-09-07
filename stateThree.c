/** @file   stateThree.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The module for the third state of the game. It determines
            the outcome and displays it.
*/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"
#include "mainGameDisplay.h"
#include "gameLogic.h"
#include "stateThree.h"

/**
 * This function calculates the round's outcome and displays the result
 * on each board.
 * The outcome options are:
 * Win = 'W'
 * Draw = 'D'
 * Lose = 'L'
 * INPUT: playersMove, the pointer to the player's chosen move (either
 *        'R', 'P' or 'S') as a char.
 *        opponentsMove, the point to the opponent's chosen move (either
 *        'R', 'P' or 'S') as a char.
 *        playerGamesWon, the pointer to the number of games the player
 *        has won as an int.
 *        opponentGamesWon, the pointer to the number of games the
 *        opponent has won as an int.
 * OUTPUT: N/A
 */
void stateThree_start(char* playersMove,
                      char* opponentsMove,
                      int* playerGamesWon,
                      int* opponentGamesWon)
{
    int playersOutcomeSent = 0;
    int opponentsOutcomeReceived = 0;
    int count = 49;

    /*
     * Calculate the winner of the current round
     */
    char roundOutcome = gameLogic_determineWinner(*playersMove,
                        *opponentsMove);
    mainGameDisplay_displayChar(roundOutcome);

    while (count > 48 || playersOutcomeSent != 1 ||
            opponentsOutcomeReceived != 1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        /*
         * Display the score upon the first NAVSWITCH_WEST event for each
         * player.
         */
        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (count == 49) {
                int currentPlayerScore = *playerGamesWon;
                int currentOpponentScore = *opponentGamesWon;

                /*
                 * Update the score.
                 */
                if (roundOutcome == 'W') {
                    currentPlayerScore++;
                    *playerGamesWon = currentPlayerScore;
                } else if (roundOutcome == 'L') {
                    currentOpponentScore++;
                    *opponentGamesWon = currentOpponentScore;
                }
            }
            mainGameDisplay_displayChar(*playerGamesWon);
            count--;
        }

        /*
         * Start the next round upon a NAVSWITCH_PUSH event
         */
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(1);
            playersOutcomeSent = 1;
        }

        if (ir_uart_read_ready_p()) {
            int response = ir_uart_getc();
            if (response != 0) {
                opponentsOutcomeReceived = 1;
            }
        }
    }
}
