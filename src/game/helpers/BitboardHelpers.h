#pragma once

#include <vector>
#include <string>

inline int squareIndex(char file, int rank) {
    return (rank - 1) * 8 + (file - 'a');
}

inline uint64_t generateBitboard(const std::vector<std::string>& squares) {
    uint64_t bitboard = 0;
    for (const auto& sq : squares) {
        if (sq.length() != 2) continue;
        char file = sq[0];
        int rank = sq[1] - '0';
        int idx = squareIndex(file, rank);
        bitboard |= (1ULL << idx);
    }
    return bitboard;
}