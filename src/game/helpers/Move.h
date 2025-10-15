#pragma once
#include "Piece.h"

class Move
{
    std::string startingPosition;
    std::string endingPosition;
    bool takes;
    Pieces piece_;

    Move(std::string startingPosition, std::string endingPosition, bool takes, Pieces piece_)
    {
        this->startingPosition = startingPosition;
        this->endingPosition = endingPosition;
        this->takes = takes;
        this->piece_ = piece_;
    }

public:
    std::string getChessNotation()
    {
        std::string chessNotation = "";
    }
};
