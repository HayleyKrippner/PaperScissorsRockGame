/** @file   mainGameDisplay.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The game display module for 'Rock, Paper,  Scissors'.
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20

/**
 * This function initlises the system, required aspects of tinygl and
 * the navigation switch used for displaying text on the LED matrix.
 * INPUT: N/A
 * OUTPUT: N/A
 */
void mainGameDisplay_init(void)
{
    system_init();                        // Initialise the system
    tinygl_init(PACER_RATE);              // Initialise tinygl
    tinygl_font_set(&font5x7_1);          // Set the font for tinygl
    tinygl_text_speed_set(MESSAGE_RATE);  // Set the speed for tinygl
    navswitch_init ();                    // Initialise the navigation switch
}

/**
 * This function displays the given character.
 * INPUT: character, the character as a char to be displayed on the LED
 *                   matrix.
 * OUTPUT: N/A
 */
void mainGameDisplay_displayChar(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}

/**
 * This function displays the message at the end of the game, based on
 * the final game score.
 * INPUT: whoWon, the player who won the game as an int, where 0 refers
 *                to the opponent winning and 1 refers to the player
 *                winning.
 * OUTPUT: N/A
 */
void mainGameDisplay_displayDecision(int whoWon)
{
    mainGameDisplay_init();
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    if (whoWon == 1) {
        tinygl_draw_message("YOU WON ! THANKS FOR PLAYING\0",tinygl_point (0, 0), 3);
    } else if (whoWon == 0) {
        tinygl_draw_message("YOU LOST ! THANKS FOR PLAYING\0",tinygl_point (0, 0), 3);
    }

    pacer_init (PACER_RATE);

    while(1) {
        pacer_wait();
        tinygl_update();
    }
}
