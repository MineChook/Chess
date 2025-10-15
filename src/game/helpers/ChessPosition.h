#pragma once
#define U64 unsigned long long
#include <vector>
#include "Move.h"

#define Moves std::vector<Move>

class ChessPosition
{
public:

    U64 whitePawns{}, whiteKnights{}, whiteBishops{}, whiteRooks{}, whiteKing{}, whiteQueens{};
    U64 blackPawns{}, blackKnights{}, blackBishops{}, blackRooks{}, blackKing{}, blackQueens{};
    U64* pieces[12]{};

    ChessPosition();
    ChessPosition(
        U64 whitePawns, U64 whiteKnights, U64 whiteBishops, U64 whiteRooks, U64 whiteKing, U64 whiteQueens,
        U64 blackPawns, U64 blackKnights, U64 blackBishops, U64 blackRooks, U64 blackKing, U64 blackQueens
    );
    void setToStartingPosition();

    Moves getPossibleMoves();

    static ChessPosition ChessPositiconvertFromPGN();
};
