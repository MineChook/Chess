#include "ChessPosition.h"

#include "../helpers/BitboardHelpers.h"
#include <vector>

#define U64 unsigned long long
#define Moves std::vector<Move>

ChessPosition::ChessPosition(
    U64 whitePawns,
    U64 whiteKnights,
    U64 whiteBishops,
    U64 whiteRooks,
    U64 whiteKing,
    U64 whiteQueens,
    U64 blackPawns,
    U64 blackKnights,
    U64 blackBishops,
    U64 blackRooks,
    U64 blackKing,
    U64 blackQueens
)
{
    this->whitePawns = whitePawns;
    this->whiteKnights = whiteKnights;
    this->whiteBishops = whiteBishops;
    this->whiteRooks = whiteRooks;
    this->whiteKing = whiteKing;
    this->whiteQueens = whiteQueens;
    this->blackPawns = blackPawns;
    this->blackKnights = blackKnights;
    this->blackBishops = blackBishops;
    this->blackRooks = blackRooks;
    this->blackKing = blackKing;
    this->blackQueens = blackQueens;

    pieces[0] = &this->whitePawns;
    pieces[1] = &this->whiteKnights;
    pieces[2] = &this->whiteBishops;
    pieces[3] = &this->whiteRooks;
    pieces[4] = &this->whiteKing;
    pieces[5] = &this->whiteQueens;
    pieces[6] = &this->blackPawns;
    pieces[7] = &this->blackKnights;
    pieces[8] = &this->blackBishops;
    pieces[9] = &this->blackRooks;
    pieces[10] = &this->blackKing;
    pieces[11] = &this->blackQueens;
}

ChessPosition::ChessPosition()
{
    setToStartingPosition();

    pieces[0] = &this->whitePawns;
    pieces[1] = &this->whiteKnights;
    pieces[2] = &this->whiteBishops;
    pieces[3] = &this->whiteRooks;
    pieces[4] = &this->whiteKing;
    pieces[5] = &this->whiteQueens;
    pieces[6] = &this->blackPawns;
    pieces[7] = &this->blackKnights;
    pieces[8] = &this->blackBishops;
    pieces[9] = &this->blackRooks;
    pieces[10] = &this->blackKing;
    pieces[11] = &this->blackQueens;
}

void ChessPosition::setToStartingPosition()
{
    whitePawns   = generateBitboard({"a2","b2","c2","d2","e2","f2","g2","h2"});
    whiteRooks   = generateBitboard({"a1","h1"});
    whiteKnights = generateBitboard({"b1","g1"});
    whiteBishops = generateBitboard({"c1","f1"});
    whiteQueens  = generateBitboard({"d1"});
    whiteKing    = generateBitboard({"e1"});

    blackPawns   = generateBitboard({"a7","b7","c7","d7","e7","f7","g7","h7"});
    blackRooks   = generateBitboard({"a8","h8"});
    blackKnights = generateBitboard({"b8","g8"});
    blackBishops = generateBitboard({"c8","f8"});
    blackQueens  = generateBitboard({"d8"});
    blackKing    = generateBitboard({"e8"});
}

Moves ChessPosition::getPossibleMoves()
{
    Moves moves;

    // implement stuff.
}