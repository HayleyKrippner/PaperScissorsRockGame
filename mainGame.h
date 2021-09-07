void mainGame_init(void);

void mainGame_start(void);

void updateGameState(int gameState, int* playersMove, int* opponentsMove, int* numOfRounds, int* playerGamesWon, int* opponentGamesWon);

void stateOne_start(void);

void getPlayerMovesState(char* playersMove, char* opponentsMove);

void selectMoves(char* playersMove, char* opponentsMove);

void getMovesSelectionConfirmations(char* playersMove, char* opponentsMove, int* hasSent, int* hasReceived);

void enterCalcAndDisplayOutcomeState(char* playersMove, char* opponentsMove);

void updateScore(int* playerGamesWon, int* opponentGamesWon, char* roundOutcome);

int checkEndGame(int* numOfRounds, int* playerGamesWon, int* opponentGamesWon);

void enterEndGameState(int* numOfRounds, int* playerGamesWon, int* opponentGamesWon);



