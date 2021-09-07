=== ROCK PAPER AND SCISSOR ===

Contributors: Hayley Krippner, Nitish Singh
Last Modified: 12 October 2020

Requirements: Two Atmega32u2 microcontrollers
How to run:   For each microcontroller in Terminal -> make clean
                                                   -> make program


=== Description ===

 Rock, Paper and Scissor is a two player board game designed in the C
 programming language. The game is played on two Atmega32u2
 microcontrollers. The players use the navigation switch to select their
 moves (i.e. R for Rock, P for Paper or S Scissor) and confirm their
 moves. The selected moves are compared and the outcome is displayed on
 the 5x7 LED matrix. The game continues until one of the players wins
 three rounds.


=== How to play ===

1. At the start, the game is in State 1 where the led matrix displays
    a "*". The players are required to push the navigation switch, once
    each, to check if both players are active. The users then proceed to
    a manual countdown from three to zero to confirm that they are ready
    to begin the first round of the game. The players can count down by
    pressing the west side of the navigation switch three times.
    Once both players count down to zero, both players need to push the
    nagivation switch down to confirm.


2. After both players have pushed the navigation switch, the game
   proceeds to State 2 where the led matrix displays the moves
   (i.e. R, P, S) that the players can select. The players can choose
   different moves by pushing to east (S), north(R) or south(P) on the
   navigation switch. To confirm the player's move, the player must push
   down on the navigation switch to proceed to the next game state.


3. The game is now in State 3, where the outcome of the moves is
   calculated and displayed (i.e. W for win and L for Lose). The user
   then needs to press west to display their current number of games won
   To play another round, the players need to confirm by pushing the
   navigation switch down.


4  The game proceeds to State 4 where a check is done of whether the
   game should end. The game ends when one of the players has won three
   rounds. If the game does not end, the game returns to State 2 and the
   score is updated at the end of each round. If the game ends, the game
   proceeds to State 5.


5. In State 5, the LED matrix displays scrolling "YOU WIN!" or
   "YOU LOSE!" text for the respective player, followed by a
   "THANKS FOR PLAYING" message.




