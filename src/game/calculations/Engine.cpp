#include <array>
#include <bit>
#include "../helpers/ChessPosition.h"
#include "Engine.h"\

static double miniMax(ChessPosition position, unsigned int depth)
{

}

static double count(ChessPosition &position)
{
    int score = 0;
    for (size_t i = 0; i < std::size(position.pieces); ++i) {
        U64 value = *position.pieces[i];
        int count = std::popcount(value);
        char firstWord[16];
        getFirstWord(s_pieceNames[i], firstWord, sizeof(firstWord));
        const int pieceValue = s_pieceValues[i];

        if (std::strcmp(firstWord, "White") != 0)
        {
            count = 0 - count;
        }

        score += count * pieceValue;
    }

    return score;
}

double Evaluate(ChessPosition position)
{
    double startingScore = count(position);

    return startingScore;
}

static char* getFirstWord(const char* str, char* buffer, int bufferSize) {
    int i = 0;
    while (str[i] != ' ' && str[i] != '\0' && i < bufferSize - 1) {
        buffer[i] = str[i];
        ++i;
    }
    buffer[i] = '\0';
    return buffer;
}
