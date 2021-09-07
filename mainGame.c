/** @file   mainGame.c
    @author Hayley Krippner & Nitish Singh
    @date   12 October 2020
    @brief  The main game module for 'Rock, Paper,  Scissors' where the
            players can play for the first to 3 games.
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "../fonts/font5x7_1.h"
#include "mainGameDisplay.h"
#include "timer.h"
#include "stateOne.h"
#include "stateTwo.h"
#include "stateThree.h"
#include "stateFour.h"
#include "stateFive.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

/**
 * This function initialises the game.
 * INPUT: N/A
 * OUTPUT: N/A
 */
void mainGame_init(void)
{
    mainGameDisplay_init(); //Initialise LED matrix display and tinygl
    ir_uart_init ();    // Initialise IR driver
}

/**
 * This function updates the state of the game.
 * The game states are:
 * 1 = waiting for players to both confirm they want to start the game.
 * 2 = waiting for both players to confirm move.
 * 3 = determine outcome and display it.
 * 4 = check if game should end.
 * 5 = game has ended.
 * INPUT: gameState, the current state of the game as an int between 0
 *        and 5.
 *        playersMove, the pointer to the move the player chose for the
 *        current round as a char (either 'R', 'P' or 'S').
 *        opponentsMove, the pointer to the move the opponent chose for
 *        the current round as a char (either 'R', 'P' or
 *        'S').
 *        numOfRounds, the number of total rounds as an int.
 *        playerGamesWon, the pointer to the number of games the player
 *        has won as an int.
 *        opponentGamesWon, the pointer to the number of games the
 *        opponent has won as an int.
 * OUTPUT: N/A
 */
void updateGameState(int gameState, char* playersMove,
                     char* opponentsMove, int numOfRounds,
                     int* playerGamesWon, int* opponentGamesWon)
{
    int endGame = 0;

    switch(gameState) {
    case 1:
        /*
         * Enter the state of waiting for players to both confirm they
         * want to start the game.
         */
        stateOne_start();
        gameState = 2;
        updateGameState(gameState, playersMove, opponentsMove,
                        numOfRounds, playerGamesWon, opponentGamesWon);
        break;
    case 2:
        /*
         * Enter the state of waiting for both players to confirm their
         * move in the current round.
         */
        stateTwo_start(playersMove, opponentsMove);
        gameState = 3;
        updateGameState(gameState, playersMove, opponentsMove,
                        numOfRounds, playerGamesWon, opponentGamesWon);
        break;
    case 3:
        /*
         * Enter the state of determining the round's outcome and
         * displaying it.
         */
        stateThree_start(playersMove, opponentsMove,
                         playerGamesWon, opponentGamesWon);
        gameState = 4;
        updateGameState(gameState, playersMove, opponentsMove,
                        numOfRounds, playerGamesWon, opponentGamesWon);
        break;
    case 4:
        /*
         * Enter the state of checking whether the game should end.
         */
        endGame = stateFour_start(numOfRounds, playerGamesWon,
                                  opponentGamesWon);
        if (endGame == 1) {
            gameState = 5;
        } else {
            gameState = 2;
        }
        updateGameState(gameState, playersMove, opponentsMove,
                        numOfRounds, playerGamesWon, opponentGamesWon);
        break;
    case 5:
        /* Enter the state for ending the game.
         */
        stateFive_start(playerGamesWon, opponentGamesWon);
        break;
    }
}

/**
 * This function starts the game.
 * INPUT: N/A
 * OUTPUT: N/A
 */
void mainGame_start(void)
{
    mainGame_init();

    int gameState = 1;
    char playersMove = ' ';
    char opponentsMove = ' ';
    int numOfRounds = 51;           //The ASCII value for 3
    int playerGamesWon = 48;        //The ASCII value for 0
    int opponentGamesWon = 48;      //The ASCII value for 0

    pacer_init (PACER_RATE);

    while(1) {
        pacer_wait();
        tinygl_update();
        updateGameState(gameState, &playersMove, &opponentsMove,
                        numOfRounds, &playerGamesWon, &opponentGamesWon);
    }
}
