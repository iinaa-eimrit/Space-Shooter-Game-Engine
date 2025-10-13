#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cstdlib>
#include <ctime>

int main()
{
    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // Create game instance
    Game game;
    
    // Game loop
    while (game.isRunning())
    {
        game.update();
        game.render();
    }
    
    return 0;
}