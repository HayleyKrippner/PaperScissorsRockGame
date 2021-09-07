/** @file   stateOne.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The module for the first state of the game. This is waiting
            for players to both confirm they want to start the game.
*/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"
#include "mainGameDisplay.h"
#include "stateOne.h"

/**
 * This function starts state one.
 * It ensures both players are ready to start the game.
 * The players must first push the navigation switch to start the pregame.
 * They need can confirm they are ready to start the round by by counting
 * done from 3 to 0 using the west navigation switch.
 * INPUT: N/A
 * OUTPUT: N/A
 */
void stateOne_start(void)
{
    /*
     * Display '*' as the start symbol.
     */
    mainGameDisplay_displayChar('*');

    /*
     * Get users to confirm before choosing R, P or S.
     */
    getPlayerConfirmations();

    /*
     * Prompt the user to use the count down.
     */
    mainGameDisplay_displayChar('<');

    /*
     * The manual countdown from 3 to 0 in order to begin the first game
     * round.
     */
    pregameCountdown();
}

/**
 * This functions get users to confirm before choosing R, P or S.
 * INPUT: N/A
 * OUTPUT: N/A
 */
void getPlayerConfirmations(void)
{

    int isPlayerActive = 0;
    int isOpponentActive = 0;

    while (isPlayerActive == 0 || isOpponentActive == 0) {

        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        /*
         * Push to confirm the player wants to begin and send this to
         * the opponent.
         */
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(1);
            isPlayerActive = 1;
        }

        /*
         * Recieve IR confirmation that the opponent is ready to begin.
         */
        if (ir_uart_read_ready_p()) {
            isOpponentActive = ir_uart_getc();
            isOpponentActive = 1;
        }
    }
}

/**
 * This functions is for the manual countdown from 3 to 0 in order to
 * begin the first game round.
 * INPUT: N/A
 * OUTPUT: N/A
 */
void pregameCountdown(void)
{
    int isPlayerReady = 0;
    int isOpponentReady = 0;
    int count = 52;                    // The ASCII value for 4.

    while (count > 48 || isPlayerReady != 1 || isOpponentReady != 1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        /*
         * The player moves west on the navigation switch to display
         * their score so far after the round that has just finished.
         * They then move west once again to start the next round.
         */
        if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            count--;
            if (count >= 48) {
                mainGameDisplay_displayChar(count); // Display current score
            } else {
                mainGameDisplay_displayChar(48);
            }
        }

        /*
         * Transmit that the player wants to begin over IR on a
         * NAVSWITCH_PUSH event.
         */
        if (navswitch_push_event_p (NAVSWITCH_PUSH) && count <= 48) {
            ir_uart_putc(1);
            isPlayerReady = 1;
        }

        /* Recieve confirmation that opponent is ready to begin
         * over IR on a NAVSWITCH_PUSH event.
         */
        if (ir_uart_read_ready_p() && count <= 48) {
            isOpponentReady = ir_uart_getc();
            isOpponentReady = 1;
        }
    }
}
