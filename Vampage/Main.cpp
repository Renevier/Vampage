#include "pch.h"
#include "Game.h"

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    Game game;
    game.Run();

    return 0;
}