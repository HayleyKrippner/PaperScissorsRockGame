/** @file   stateTwo.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The module for the second state of the game. This is waiting
            for both players to confirm move..
*/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"
#include "mainGameDisplay.h"
#include "stateTwo.h"

/**
 * This function allows the players to choose their move and confirms
 * that both players have choose their move.
 * INPUT: playersMove, the pointer to the player's chosen move (either
 *        'R', 'P' or 'S') as a char.
 *        opponentsMove, the point to the opponent's chosen move (either
 *        'R', 'P' or 'S') as a char.
 * OUTPUT: N/A
 */
void stateTwo_start(char* playersMove, char* opponentsMove)
{
    int hasSent = 0;
    int hasReceived = 0;

    /*
     * Prompt the user to choose their move
     */
    mainGameDisplay_displayChar('>');

    while (hasSent == 0 || hasReceived == 0) {

        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        /*
        * Player selects R (ROCK), P (PAPER) or S (SCISSOR) as their
        * move on a NAVSWITCH events.
        */
        selectMoves(playersMove);

        /*
         * Get users to confirm before choosing R, P or S
         */
        getMovesSelectionConfirmations(playersMove, opponentsMove, &hasSent, &hasReceived);


    }
}

/**
 * This function allows the user to select their desired move from R
 * (ROCK), P (PAPER) or S (SCISSOR) as their move on a NAVSWITCH events.
 * INPUT: playersMove, the pointer to the player's chosen move (either
 *        'R', 'P' or 'S') as a char.
 * OUTPUT: N/A
 */
void selectMoves(char* playersMove)
{
    char tempMove = ' ';

    /*
    * Player selects rock as their move on a NAVSWITCH_NORTH event.
    */
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        tempMove = 'R';
        *playersMove = tempMove;
        mainGameDisplay_displayChar(*playersMove);
    }

    /*
     * Player selects paper as their move on a NAVSWITCH_SOUTH event.
     */
    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        tempMove = 'P';
        *playersMove = tempMove;
        mainGameDisplay_displayChar(*playersMove);
    }

    /*
     * Player selects scissors as their move on a NAVSWITCH_EAST event.
     */
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        tempMove = 'S';
        *playersMove = tempMove;
        mainGameDisplay_displayChar(*playersMove);
    }

}

/**
 * This function get the players to confirm their move.
 * INPUT: playersMove, the pointer to the player's chosen move (either
 *        'R', 'P' or 'S') as a char.
 *        opponentsMove, the point to the opponent's chosen move (either
 *        'R', 'P' or 'S') as a char.
 *        hasSent, the pointer to the value of whether the current player's
 *        move has been sent to the other player's microcontroller as an
 *        int. If it is 0, it has been sent, and if it is 1 then it has
 *        not been sent.
 *        hasReceived, the pointer to the value of whether the
 *        opponent's move has been recieved by the other player's
 *        microcontroller as an int. If it is 0, it has been sent, and
 *        if it is 1 then it has not been sent.
 * OUTPUT: N/A
 */
void getMovesSelectionConfirmations(char* playersMove, char* opponentsMove, int* hasSent, int* hasReceived)
{

    ir_uart_init ();            // Initialise IR driver.

    /*
     * Transmit that the player has confirmed move over IR on a
     * NAVSWITCH_PUSH event.
     */
    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        ir_uart_putc(*playersMove);
        *hasSent = 1;
    }

    /*
     * Recieve confirmation that opponent has chosen the character
     * over IR on a NAVSWITCH_PUSH event.
     */
    if (ir_uart_read_ready_p()) {
        char incomingChar = ir_uart_getc();
        if (incomingChar == 'R' || incomingChar == 'P' ||
                incomingChar == 'S') {
            *opponentsMove = incomingChar;
            *hasReceived = 1;
        }
    }
}
