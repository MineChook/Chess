#include "helpers/ChessPosition.h"

class GameState
{
    bool whitesTurn = true;
    bool gameOver = false;
    bool passAndPlay = false;
    unsigned int turn = 1;
    unsigned int maxTurns;
    ChessPosition chessPosition = ChessPosition();

    bool homeScreen = true;
    bool playScreen = false;
    bool analysis = false;


public:
    explicit GameState(int maxTurns)
    {
        this->maxTurns = maxTurns;
    }

    bool IsWhitesTurn()
    {
        return whitesTurn;
    }

    bool IsGameOver()
    {
        return gameOver;
    }

    void changeTurn()
    {
        whitesTurn = !whitesTurn;
    }

    void GameOver()
    {
        gameOver = true;
    }
};
