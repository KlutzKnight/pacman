#include "Game.h"

#include <iostream>
#include <stdexcept>

int main() {
    try {
        Game game;
        game.run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}