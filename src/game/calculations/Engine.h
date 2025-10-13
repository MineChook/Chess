#pragma once
#include "../helpers/ChessPosition.h"
#include "../helpers/Color.h"

double Evaluate(ChessPosition position);

static const char* s_pieceNames[12] = {
    "White Pawns", "White Knights", "White Bishops", "White Rooks", "White King", "White Queens",
    "Black Pawns", "Black Knights", "Black Bishops", "Black Rooks", "Black King", "Black Queens"
};

static const int s_pieceValues[12] = {
    1, 3, 3, 5, 0, 9, 1, 3, 3, 5, 0, 9
};

static double count(ChessPosition &position);
