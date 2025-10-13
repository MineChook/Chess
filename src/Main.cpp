#include <spdlog/spdlog.h>

#include "game/Game.h"

#define U64 unsigned long long

int main()
{
    // Testing logger
    spdlog::info("Welcome to the chess!");

    // Start Game
    if (!StartGame())
    {
        return -1;
    }
}