#ifndef GAME_STATE_H
#define GAME_STATE_H


#include <memory>

#include <SDL3/SDL.h>

#include "Renderer.h"

class GameState {
    public:
        // Main loop functions
        virtual void update(double deltaTime, const bool* keyboardState) = 0;
        virtual void render(Renderer& renderer) = 0;
        virtual std::unique_ptr<GameState> handleEvent(SDL_Event* event) = 0;

        // Make sure to call child destructors
        virtual ~GameState() = default;
};


#endif